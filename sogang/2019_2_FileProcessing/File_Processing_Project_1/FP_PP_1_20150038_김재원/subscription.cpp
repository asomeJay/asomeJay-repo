#include "Subscription.h"
#include <time.h>
#include <fstream>
#include <string>

Subscription::Subscription() {
	Subscription_ID = (char*)malloc(sizeof(char) * SUBSCRIPTION_ID);
	NewsAgency_ID = (char*)malloc(sizeof(char) * NEWSAGENCY_ID);
	Mileage = (char*)malloc(sizeof(char) * MILEAGE);
}
Subscription::Subscription(const char* new_Subscription_ID) {
	Subscription_ID = (char*)malloc(sizeof(char) * SUBSCRIPTION_ID);
	NewsAgency_ID = (char*)malloc(sizeof(char) * NEWSAGENCY_ID);
	Mileage = (char*)malloc(sizeof(char) * MILEAGE);
	update_subscription_id(new_Subscription_ID);
}
Subscription::Subscription(const string new_Member_ID) {
	Subscription_ID = (char*)malloc(sizeof(char) * SUBSCRIPTION_ID);
	NewsAgency_ID = (char*)malloc(sizeof(char) * NEWSAGENCY_ID);
	Mileage = (char*)malloc(sizeof(char) * MILEAGE);
	update_name(new_Member_ID);
}
Subscription::Subscription(const Subscription& s) {
	Subscription_ID = (char*)malloc(sizeof(char) * SUBSCRIPTION_ID);
	NewsAgency_ID = (char*)malloc(sizeof(char) * NEWSAGENCY_ID);
	Mileage = (char*)malloc(sizeof(char) * MILEAGE);
	update_subscription_id(s.Subscription_ID);
	update_newsAgency_id(s.NewsAgency_ID);
	update_name(s.Member_ID);
	update_mileage(s.Mileage);
}

Subscription& Subscription::operator = (const Subscription& s) {
	update_subscription_id(s.Subscription_ID);
	update_newsAgency_id(s.NewsAgency_ID);
	update_name(s.Member_ID);
	update_mileage(s.Mileage);

	return *this;
}
bool Subscription::operator == (const Subscription& s) {
	return !strcmp(s.Subscription_ID, Subscription_ID) &
		!strcmp(s.NewsAgency_ID, NewsAgency_ID) &
		!Member_ID.compare(s.Member_ID);
}
bool Subscription::operator != (const Subscription& s) {
	return !strcmp(s.Subscription_ID, Subscription_ID) |
		!strcmp(s.NewsAgency_ID, NewsAgency_ID) |
		!Member_ID.compare(s.Member_ID);
}

istream& operator >> (istream& is, Subscription& s) {
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
	s.update_subscription_id(temp.data());

	getline(iss, temp, '|');
	s.update_newsAgency_id(temp.data());

	getline(iss, temp, '|');
	s.update_name(temp);

	getline(iss, temp, '\n');
	s.update_mileage(temp.data());	

	return is;
}
ostream& operator << (ostream& os, Subscription& s) {
	string sub(s.Subscription_ID, strlen(s.Subscription_ID));
	string news(s.NewsAgency_ID, strlen(s.NewsAgency_ID));
	string mil(s.Mileage, strlen(s.Mileage));

	os << sub << '|' << news << '|' << s.Member_ID << '|' << mil << endl;

	return os;
}

bool Subscription::Pack(IOBuffer& Buffer) const {
	int numBytes;

	Buffer.Clear();

	string s_sub(this->Subscription_ID, (int)strlen(Subscription_ID));
	string s_new(this->NewsAgency_ID, (int)strlen(NewsAgency_ID));
	string s_mil(this->Mileage, (int)strlen(Mileage));
	numBytes = Buffer.Pack(s_sub.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(s_new.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Member_ID.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(s_mil.c_str());
	if (numBytes == -1) return false;

	return true;
}

bool Subscription::Unpack(IOBuffer& Buffer) {
	int numBytes;
	char buf[STDMAXBUF];

	numBytes = Buffer.Unpack(Subscription_ID, (int)strlen(Subscription_ID));
	if (numBytes == -1) return false;

	numBytes = Buffer.Unpack(NewsAgency_ID, (int)strlen(NewsAgency_ID));
	if (numBytes == -1) return false;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	this->Member_ID = buf;

	numBytes = Buffer.Unpack(Mileage, (int)strlen(Mileage));
	if (numBytes == -1) return false;
	
	return true;
}

int Subscription::subscription_pos_search(string key) {
	ifstream ifs("listOfSubscription.txt");

	if (ifs.fail()) {
		std::cout << "listOfSubscription.txt open Error!" << endl;
		exit(1);
	}
	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Subscription> Subscriptionfile(buffer);
	char str[] = "fileOfSubscription.dat";
	Subscriptionfile.Open(str, ios::in);

	int recaddr_before;
	for (int i = 0; i < n; i++) {
		Subscription subscription;
		recaddr_before = Subscriptionfile.Read(subscription);

		string id = string(subscription.Subscription_ID);
		if (!id.compare(key)) {
			return recaddr_before;
		}
	}
	return -1;
}
void Subscription::subscription_search_choice() {
	std::cout << endl;
	cout << "============================" << endl;
	cout << "Which ID you choice for Search?" << endl;
	int choice;
	cout << "============================" << endl;
	cout << "1. Subscription ID   " << endl;
	cout << "2. NewsAgency ID     " << endl;
	cout << "3. Member_ID         " << endl;
	cin >> choice;

	if (choice == 1) { // Subscription ID
		string want;
		std::cin >> want;
		subscription_search(want);
	}
	else if (choice == 2) { // NewsAgency ID
		string want;
		std::cin >> want;
		subscription_newsagency_search(want);
	}
	else if (choice == 3) { // Member ID
		string want;
		std::cin >> want;
		subscription_member_search(want);
	}
	return;
}
bool Subscription::subscription_search(string key) {
	int recBefore = -3, recAfter;
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Subscription> Subscriptionfile(buffer);
	char str[] = "fileOfSubscription.dat";

	Subscriptionfile.Open(str, ios::in);
	int count = 0;
	while(1) {			
		Subscription subscription;
		recAfter = Subscriptionfile.Read(subscription);
		if (recBefore == recAfter) break;
		recBefore = recAfter;

		string id = string(subscription.Subscription_ID);
		if (!id.compare(key)) {
			std::cout << "==========================" << endl;
			std::cout << "Record : " << subscription << endl;
			std::cout << "==========================" << endl;
			Subscriptionfile.Close();
			return true;
		}
	}
	Subscriptionfile.Close();
	return false;
}

void Subscription::subscription_insert(Subscription& subscription) {
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Subscription> Subscriptionfile(buffer);
	char str[] = "fileOfSubscription.dat";
	Subscriptionfile.Open(str, ios::app);
	Subscriptionfile.Write(subscription);
}

void Subscription::subscription_insert() {
	std::cout << "========================" << endl;
	std::cout << "Subscription Insert Mode" << endl;
	std::cout << "========================" << endl;
	std::cout << "Input ID :  ";

	int subRecordCount, subRecordNum;
	string newSubID;
	cin >> newSubID;

	Subscription newbie;
	if (subscription_search(newSubID)) return;
	newbie.subscription_input(newbie, newSubID.data());

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Subscription> Subscriptionfile(buffer);
	char str[] = "fileOfSubscription.dat";

	Subscriptionfile.Open(str, ios::in);
	int recBefore, checkNum = -3, recAfter, newbieSize, availSpace, sizeOfSpace;

	while (1) {
		Subscription checkAgency;
		recBefore = Subscriptionfile.Read(checkAgency);

		if (checkNum == recBefore) break;
		checkNum = recBefore;

		string id = string(checkAgency.Subscription_ID);
		if (!((id.find("*")) == string::npos)) {
			newbieSize = newbie.subscription_size();
			recAfter = Subscriptionfile.Read(checkAgency);
			recBefore = -4 - recBefore;

			sizeOfSpace = recAfter - recBefore;
			availSpace = sizeOfSpace - (newbieSize + 6);

			if (availSpace >= 0) {
				Subscriptionfile.Close();
				Subscriptionfile.Open(str, ios::out);
				Subscriptionfile.Move(recBefore);
				Subscriptionfile.Write(newbie);

				Subscription space;
				string star("*"); string blank(""); string pass("");

				if (availSpace >= 8) {
					for (int i = 0; i < availSpace - 8; i++)
						pass += " ";

					space.update_subscription_id(star.data());
					space.update_name(pass);
					space.update_newsAgency_id(blank.data());
					space.update_mileage(blank.data());

					Subscriptionfile.Write(space);
				}

				Subscriptionfile.Close();

				return;
			}
		}
	}
	Subscriptionfile.Close();
	Subscriptionfile.Open(str, ios::app);
	Subscriptionfile.Append(newbie);
	Subscriptionfile.Close();
	return;
}

void Subscription::subscription_delete(string key) {
	std::cout << "==============================" << endl;
	std::cout << "Subscription Delete Processing" << endl;
	std::cout << "==============================" << endl;
	std::cout << "Delete ID : " << key << endl;

	int record = -1;
	while ((record = subscription_pos_search(key)) != -1) {
		DelimFieldBuffer buffer('|', STDMAXBUF);
		RecordFile <Subscription> Subscriptionfile(buffer);
		char str[] = "fileOfSubscription.dat";

		Subscriptionfile.Open(str, ios::out);
		Subscriptionfile.Delete(record);
		Subscriptionfile.Close();
	}
	cout << "Delete End" << endl;
	return;
}

void Subscription::subscription_update() {
	std::cout << endl;
	std::cout << "==============================" << endl;
	std::cout << "Subscription Update Processing" << endl;
	std::cout << "==============================" << endl;
	std::cout << "Update Subscription ID : ";
	string key, id; cin >> key;

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Subscription> Subscriptionfile(buffer);
	char str[] = "fileOfSubscription.dat";
	Subscriptionfile.Open(str, ios::in);

	int recBefore, recAfter, compare = -3, originalSize, newbieSize;
	int sizeOfSpace, availSpace;
	int count = 0;
	while (1) {
		Subscription subscript;
		recBefore = Subscriptionfile.Read(subscript);

		if (compare == recBefore) break;
		compare = recBefore;

		id = string(subscript.Subscription_ID);

		if (!id.compare(key)) {
			Subscription newbie;
			originalSize = subscript.subscription_size();
			recAfter = Subscriptionfile.Read(subscript);
			newbie.subscription_input(newbie, key);
			newbieSize = newbie.subscription_size();

			Subscriptionfile.Close();

			if (originalSize >= newbieSize) {
				Subscriptionfile.Open(str, ios::out);
				recBefore -= 2;

				sizeOfSpace = recAfter - recBefore;
				availSpace = sizeOfSpace - newbieSize;

				if (availSpace >= 6) {
					Subscriptionfile.Write(newbie, recBefore);

					Subscription space;
					string blank(""), star("*"), pass("");

					for (int i = 0; i < (availSpace - 15); i++) pass += " ";

					space.update_subscription_id(star.data());
					space.update_name(pass);
					space.update_mileage(blank.data());
					space.update_newsAgency_id(blank.data());

					Subscriptionfile.Write(space);
					Subscriptionfile.Close();

					return;
				}
				else {
					for (int i = 0; i < availSpace; i++)newbie.Member_ID += " ";
					Subscriptionfile.Write(newbie, recBefore);
					Subscriptionfile.Close();
				}
				return;
			}
			else if (originalSize < newbieSize) {
				subscription_delete(key);
				Subscriptionfile.Open(str, ios::app);
				Subscriptionfile.Write(newbie);
				Subscriptionfile.Close();
				return;
			}
			else {
				std::cout << "error breaks out at Comparison" << endl;
				return;
			}
		}
	}
	Subscriptionfile.Close();
	std::cout << "============================================================" << endl;
	std::cout << "=======================UPDATE ERROR=========================" << endl;
	std::cout << "====================There isn't the key=====================" << endl;
	std::cout << "============================================================" << endl;
}

int Subscription::subscription_size() {
	int total = 0;
	total += string(Subscription_ID).size() + string(NewsAgency_ID).size()
		+ string(Mileage).size() + Member_ID.size();
	return total;
}

void Subscription::subscription_input(Subscription& newbie, string key) {
	string mem;

	newbie.update_subscription_id(key.data());

	std::cout << "Input NewsAgency ID : "; cin >> mem;
	newbie.update_newsAgency_id(mem.data());

	std::cout << "Input Member ID : "; cin >> mem;
	newbie.update_name(mem);

	std::cout << "Input Mileage : "; cin >> mem;
	newbie.update_mileage(mem.data());
};

void Subscription::subscription_newsagency_search(string key) {
	int recBefore = -3, recAfter;
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Subscription> Subscriptionfile(buffer);
	char str[] = "fileOfSubscription.dat";

	Subscriptionfile.Open(str, ios::in);
	while (1) {
		Subscription subscription;
		recAfter = Subscriptionfile.Read(subscription);

		if (recBefore == recAfter) break;
		recBefore = recAfter;

		string id = string(subscription.NewsAgency_ID);
		if (!id.compare(key)) {
			std::cout << "==========================" << endl;
			std::cout << "Record : " << subscription << endl;
			std::cout << "==========================" << endl;
			Subscriptionfile.Close();
			return;
		}
	}
	Subscriptionfile.Close();
	return;
}

void Subscription::subscription_member_search(string key) {
	int recBefore = -3, recAfter;
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Subscription> Subscriptionfile(buffer);
	char str[] = "fileOfSubscription.dat";

	Subscriptionfile.Open(str, ios::in);
	while (1) {
		Subscription subscription;
		recAfter = Subscriptionfile.Read(subscription);

		if (recBefore == recAfter) break;
		recBefore = recAfter;

		string id = subscription.Member_ID;
		if (!id.compare(key)) {
			std::cout << "==========================" << endl;
			std::cout << "Record : " << subscription << endl;
			std::cout << "==========================" << endl;
			Subscriptionfile.Close();
			return;
		}
	}
	Subscriptionfile.Close();
	std::cout << "There isn't the key" << endl;
	return;
}
