#include "newsagency.h"
#include <time.h>
#include <fstream>
#include <string>
#include "Subscription.h"


NewsAgency::NewsAgency() {
	NewsAgency_ID = (char*)malloc(sizeof(char) * (NEWSAGENCY_ID));
}

NewsAgency::NewsAgency(const string ID){
	update_newsagency_id(ID.data());
}

NewsAgency::NewsAgency(const NewsAgency& s){
	update_newsagency_id(s.NewsAgency_ID);
	update_address(s.Address);
	update_name(s.Name);
}

NewsAgency& NewsAgency::operator = (const NewsAgency& s) {
	update_newsagency_id(s.NewsAgency_ID);
	update_address(s.Address);
	update_name(s.Name);
	return *this;
}
bool NewsAgency::operator == (const NewsAgency& s) {
	return !strcmp(s.NewsAgency_ID, NewsAgency_ID);
}
bool NewsAgency::operator != (const NewsAgency& s) {
	return !strcmp(s.NewsAgency_ID, NewsAgency_ID);
}

istream& operator >> (istream& is, NewsAgency& s) {
	string st;

	is.exceptions(istream::failbit | istream::badbit);

	try {
		getline(is, st);
	}
	catch (istream::failure e) {
		cout << "istream error breaks out" << endl;
		return is;
	}

	istringstream iss(st);
	string temp;

	getline(iss, temp, '|');
	s.update_newsagency_id(temp.data());
	//cout << s.NewsAgency_ID << endl;
	getline(iss, temp, '|');
	s.update_name(temp);

	getline(iss, temp, '\n');
	s.update_address(temp);

	return is;
}
ostream& operator << (ostream& os, NewsAgency& s) {
	string newsagency(s.NewsAgency_ID, NEWSAGENCY_ID);
	os << newsagency << '|' << s.Name << '|' << s.Address << endl;

	return os;
}

bool NewsAgency::Pack(IOBuffer& Buffer) const {
	int numBytes;

	Buffer.Clear();

	string n_newsagency(NewsAgency_ID, NEWSAGENCY_ID);

	numBytes = Buffer.Pack(n_newsagency.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Name.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Address.c_str());
	if (numBytes == -1) return false;

	return true;
}

bool NewsAgency::Unpack(IOBuffer& Buffer) {
	int numBytes;
	char buf[STDMAXBUF];

	numBytes = Buffer.Unpack(this->NewsAgency_ID, strlen(this->NewsAgency_ID));
	if (numBytes == -1) return false;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Name = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Address = buf;

	return true;
}

int NewsAgency::newsagency_pos_search(string key) {
	ifstream ifs("listOfNewsAgency.txt");

	if (ifs.fail()) {
		std::cout << "listOfNewsAgency.txt open Error!" << endl;
		exit(1);
	}
	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <NewsAgency> NewsAgencyfile(buffer);
	char str[] = "fileOfNewsAgency.dat";
	NewsAgencyfile.Open(str, ios::in);

	int recaddr_before;
	for (int i = 0; i < n; i++) {
		NewsAgency newsagency;
		recaddr_before = NewsAgencyfile.Read(newsagency);
		
		string id = string(newsagency.NewsAgency_ID);
		if (!id.compare(key)) {
			cout << "key is here" << endl;
			return recaddr_before;
		}
	}
	return -1;
}

bool NewsAgency::newsagency_search(string key) {
	int recBefore = -3, recAfter;
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <NewsAgency> NewsAgencyfile(buffer);
	char str[] = "fileOfNewsAgency.dat";
	int count = 0;

	NewsAgencyfile.Open(str, ios::in);
	while(1) {
		NewsAgency agency;
		recAfter = NewsAgencyfile.Read(agency);
		
		if (recBefore == recAfter) break;
		recBefore = recAfter;
		
		string id = string(agency.NewsAgency_ID);
		if (!id.compare(key)) {

			std::cout << "==========================" << endl;
			std::cout << "Record : " << agency << endl;
			std::cout << "==========================" << endl;
			NewsAgencyfile.Close();
			return true;
		}
	}
	NewsAgencyfile.Close();
	return false;
}

void NewsAgency::newsagency_insert(NewsAgency & newsagency) {
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <NewsAgency> NewsAgencyfile(buffer);
	char str[] = "fileOfNewsAgency.dat";
	NewsAgencyfile.Open(str, ios::app);
	NewsAgencyfile.Write(newsagency);
}

void NewsAgency::newsagency_insert() {
	std::cout << "************************" << endl;
	std::cout << "NewsAgency Insert Mode" << endl;
	std::cout << "***********************" << endl;
	std::cout << "Input ID : " ;

	int memberRecordCount, memberRecordNum;
	string newNewsID;
	cin >> newNewsID;

	NewsAgency newbie;

	if (newsagency_search(newNewsID)) return;

	newbie.newsagency_input(newbie, newNewsID);

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <NewsAgency> NewsAgencyfile(buffer);
	char str[] = "fileOfNewsAgency.dat";

	NewsAgencyfile.Open(str, ios::in);
	int recBefore, checkNum = -3, recAfter, newbieSize, availSpace, sizeOfSpace;

	while(1) {
		NewsAgency checkAgency;
		recBefore = NewsAgencyfile.Read(checkAgency);

		if (checkNum == recBefore) break;
		checkNum = recBefore;

		string id = string(checkAgency.NewsAgency_ID);
		if (!((id.find("*")) == string::npos)) {
			cout << "start" << endl;
			newbieSize = newbie.newsagency_size();

			cout << "newbieSize : " << newbieSize << endl;

			recAfter = NewsAgencyfile.Read(checkAgency);
			recBefore = -4 - recBefore;

			sizeOfSpace = recAfter - recBefore;
			availSpace = sizeOfSpace - (newbieSize + 5);
			cout << "sizeOfSpace : " << sizeOfSpace << endl;
			cout << "availSpace : " << availSpace << endl;

			if (availSpace >= 0) {
				cout << "avail space entering" << endl;
				NewsAgencyfile.Close();
				NewsAgencyfile.Open(str, ios::out);
				NewsAgencyfile.Move(recBefore);
				NewsAgencyfile.Write(newbie);

				NewsAgency space; 
				string star("*"); string blank(""); string pass("");

				if (availSpace >= 8) {
					for (int i = 0; i < availSpace - 8; i++)
						pass += " ";

					space.update_newsagency_id(star.data());
					space.update_name(blank);
					space.update_address(pass);

					NewsAgencyfile.Write(space);
				}

				NewsAgencyfile.Close();

				return;
			}
			}
		}
	NewsAgencyfile.Close();
	NewsAgencyfile.Open(str, ios::app);
	NewsAgencyfile.Append(newbie);
	NewsAgencyfile.Close();
	return;
}

void NewsAgency::newsagency_delete(string key) {
	std::cout << "************************" << endl;
	std::cout << "Member Delete Processing" << endl;
	std::cout << "************************" << endl;
	std::cout << "Delete Key : " << key << endl;

	int record = -1;
	record = newsagency_pos_search(key);

	if (record == -1) return;

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <NewsAgency> NewsAgencyfile(buffer);
	char str[] = "fileOfNewsAgency.dat";
	NewsAgency temp;

	NewsAgencyfile.Open(str, ios::out);
	NewsAgencyfile.Delete(record);
	NewsAgencyfile.Close();
	
	Subscription sub;
	sub.subscription_delete(key);

	return;
}

void NewsAgency::newsagency_update() {
	std::cout << "************************" << endl;
	std::cout << "NewsAgency Update Processing" << endl;
	std::cout << "************************" << endl;
	std::cout << "Update NewsAgency ID : ";
	string key, id; cin >> key;

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <NewsAgency> NewsAgencyfile(buffer);
	char str[] = "fileOfNewsAgency.dat";
	NewsAgencyfile.Open(str, ios::in);

	int recBefore, recAfter, compare = -3, originalSize, newbieSize;
	int sizeOfSpace, availSpace;
	
	while(1) {
		NewsAgency newsagency;
		recBefore = NewsAgencyfile.Read(newsagency);
		if (compare == recBefore) break;
		compare = recBefore;
		id = string(newsagency.NewsAgency_ID);

		if (!id.compare(key)) {
			NewsAgency newbie;
			originalSize = newsagency.newsagency_size();
			newbieSize = newbie.newsagency_size();
			recAfter = NewsAgencyfile.Read(newsagency);
			newbie.newsagency_input(newbie, key);

			newbieSize = newbie.newsagency_size();
			NewsAgencyfile.Close();

			//originalSize = newsagency.newsagency_size();
			if (originalSize >= newbieSize) {
				NewsAgencyfile.Open(str, ios::out);
				recBefore -= 2;

				sizeOfSpace = recAfter - recBefore;
				availSpace = sizeOfSpace - newbieSize;

				if (availSpace >= 6) {
					NewsAgencyfile.Write(newbie, recBefore);

					NewsAgency space;
					string blank(""), star("*"), pass("");

					
					for (int i = 0; i < (availSpace - 5); i++) pass += " ";

					space.update_newsagency_id(star.data());
					space.update_name(pass);
					space.update_address(blank);
					NewsAgencyfile.Write(space);
					NewsAgencyfile.Close();

					return;
					
				}
				else {
					for (int i = 0; i < availSpace; i++)newbie.Name += " ";
					NewsAgencyfile.Write(newbie, recBefore);
					NewsAgencyfile.Close();
				}
				return;
			}
			else if (originalSize < newbieSize) {
				newsagency_delete(key);
				NewsAgencyfile.Open(str, ios::app);
				NewsAgencyfile.Write(newbie);
				NewsAgencyfile.Close();
				return;
			}
			else {
				std::cout << "error breaks out at Comparison" << endl;
				return;
			}
		}
	}
	NewsAgencyfile.Close();
	std::cout << "============================================================" << endl;
	std::cout << "=======================UPDATE ERROR=========================" << endl;
	std::cout << "====================There isn't the key=====================" << endl;
	std::cout << "============================================================" << endl;
}

int NewsAgency::newsagency_size() {
	int total = 0;
	total += string(NewsAgency_ID).size() + Name.size() + Address.size();
	return total;
}

void NewsAgency::newsagency_input(NewsAgency& newbie, string key) {
	string mem;

	newbie.update_newsagency_id(key.data());

	std::cout << "Input Name : "; cin >> mem;
	newbie.update_name(mem);

	std::cout << "Input Address : "; cin >> mem;
	newbie.update_address(mem);

	return;
}