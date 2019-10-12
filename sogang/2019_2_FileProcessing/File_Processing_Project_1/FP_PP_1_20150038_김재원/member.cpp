#include "member.h"
#include <time.h>
#include <fstream>
#include <string>
#include "Subscription.h"

Member::Member() {
	Mileage = (char*)malloc(sizeof(char) * MILEAGE_CHAR);
}
Member::Member(const string ID) {
	update_id(ID);
}
Member::Member(const Member& s) {
	update_id(s.ID);
	update_password(s.Password);
	update_name(s.Name);
	update_phoneNumber(s.Phone_Number);
	update_address(s.Address);
	update_mileage(s.Mileage);
}

Member& Member::operator = (const Member& s) {
	update_id(s.ID);
	update_password(s.Password);
	update_name(s.Name);
	update_phoneNumber(s.Phone_Number);
	update_address(s.Address);
	update_mileage(s.Mileage);
	return *this;
}
bool Member::operator == (const Member& s) {
	return !s.ID.compare(ID);
}
bool Member::operator != (const Member& s) {
	return !s.ID.compare(ID);
}

istream& operator >> (istream& is, Member& s) {
	string st;

	is.exceptions(istream::failbit | istream::badbit);

	try {
		getline(is, st);
	}
	catch (istream::failure e) {
		std::cout << "istream error breaks out" << endl;
		return is;
	}

	istringstream iss(st);
	string temp;

	getline(iss, temp, '|');
	s.update_id(temp);

	getline(iss, temp, '|');
	s.update_password(temp);

	getline(iss, temp, '|');
	s.update_name(temp);

	getline(iss, temp, '|');
	s.update_phoneNumber(temp);

	getline(iss, temp, '|');
	s.update_address(temp);

	getline(iss, temp, '\n');
	s.update_mileage(temp.data());

	return is;
}

ostream& operator << (ostream& os, Member& m) {
	string mileage (m.Mileage, MILEAGE_CHAR);

	os << m.ID << '|' << m.Password << '|' << m.Name <<'|' << m.Phone_Number << '|' <<
		m.Address << '|' << mileage << endl;

	return os;
}

bool Member::Pack(IOBuffer& Buffer) const {
	int numBytes;

	Buffer.Clear();

	string m_mileage(Mileage, (int)strlen(Mileage));

	numBytes = Buffer.Pack(ID.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Password.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Name.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Phone_Number.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Address.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(m_mileage.c_str());
	if (numBytes == -1) return false;

	return true;
}

bool Member::Unpack(IOBuffer& Buffer) {
	int numBytes;
	char buf[STDMAXBUF];

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	ID = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Password = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Name = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Phone_Number = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Address = buf;

	numBytes = Buffer.Unpack(this->Mileage, (int)strlen(this->Mileage));
	if (numBytes == -1) return false;
	return true;
}

int Member::member_pos_search(string key) {
	ifstream ifs("listOfMember.txt");

	if (ifs.fail()) {
		std::cout << "listOfMember.txt open Error!" << endl;
		exit(1);
	}
	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');
	ifs.close();

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> Memberfile(buffer);
	char str[] = "fileOfMember.dat";
	Memberfile.Open(str, ios::in);

	int recaddr_before;
	for (int i = 0; i < n; i++) {
		Member member;
		recaddr_before = Memberfile.Read(member);
		
		string id = member.ID;
		if (!id.compare(key)) {
			Memberfile.Close();
			return recaddr_before;
		}
	}
	Memberfile.Close();
	return -1;
}

bool Member::member_search(string key) {
	ifstream ifs("listOfMember.txt");

	if (ifs.fail()) {
		std::cout << "listOfMember.txt open Error!" << endl;
		exit(1);
	}
	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> Memberfile(buffer);
	char str[] = "fileOfMember.dat";

	Memberfile.Open(str, ios::in);
	for (int i = 0; i < n; i++) {
		Member member;
		int add;
		add = Memberfile.Read(member);
		string id = member.ID;
		if (!(id.compare(key))) {
			cout << member << endl;
			cout << add << endl;
			Memberfile.Close();
			return true;
		}
	}
	Memberfile.Close();
	return false;
}

void Member::member_insert(Member & member) {
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> Memberfile(buffer);
	char str[] = "fileOfMember.dat";
	Memberfile.Open(str, ios::app);
	Memberfile.Write(member);
}

void Member::member_insert() {
	std::cout << "******************" << endl;
	std::cout << "Member Insert Mode" << endl;
	std::cout << "******************" << endl;
	std::cout << "Input ID : " ;

	int memberRecordCount, memberRecordNum;
	string newMemberID;
	cin >> newMemberID;

	Member newbie;

	if (member_search(newMemberID)) return;

	newbie.member_input(newbie, newMemberID);

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> Memberfile(buffer);
	char str[] = "fileOfMember.dat";

	Memberfile.Open(str, ios::in);
	int checkNum = -3;
	while(1) {
		Member checkMember;
		memberRecordNum = Memberfile.Read(checkMember);
		// 끝을 알려면 record address가 바뀌지 않으면 된다. 
		if (checkNum == memberRecordNum) break;
		checkNum = memberRecordNum;
		string id = string(checkMember.ID);

		if (!(id.find('*') == string::npos)) {
			Member temp;
			int afterRecordNum = Memberfile.Read(temp);
			memberRecordNum = - 4 - memberRecordNum;
			//cout << "memberRecordNum : " << memberRecordNum << endl;
			int sizeOfSpace = afterRecordNum - memberRecordNum;
			//cout << sizeOfSpace << endl;
			//cout << newbie.member_size();

			if (sizeOfSpace > newbie.member_size()) {
				Member space; 
				string star("*"); string blank(""); string pass("");

				Memberfile.Close();
				Memberfile.Open(str, ios::out);
				Memberfile.Write(newbie, memberRecordNum);
				//cout << "afterRecord : " << afterRecordNum << endl;
				//cout << "memberRecord : " << memberRecordNum << endl;
				int newStart = memberRecordNum + newbie.member_size() + 7;
				int newbieSize = newbie.member_size() + 7;
				int availSpace = sizeOfSpace - newbieSize;

				if (availSpace - 12 > 0) {
					for (int i = 0; i < availSpace - 12; i++)
						pass += " ";

					space.update_id(star);
					space.update_password(pass);
					space.update_name(blank);
					space.update_address(blank);
					space.update_mileage(blank.data());
					space.update_phoneNumber(blank);

					Memberfile.Write(space);
				}
				
				Memberfile.Close();

				return;
			}
			}
		}
	Memberfile.Close();
	Memberfile.Open(str, ios::app);
	Memberfile.Append(newbie);
	Memberfile.Close();
	return;
	
}

void Member::member_delete(string key) {
	std::cout << "************************" << endl;
	std::cout << "Member Delete Processing" << endl;
	std::cout << "************************" << endl;
	std::cout << "Delete Key : " << key << endl;

	int record = -1;
	record = member_pos_search(key);

	if (record == -1) return;

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> Memberfile(buffer);
	char str[] = "fileOfMember.dat";
	Member temp;
	
	Memberfile.Open(str, ios::out);
	Memberfile.Delete(record);
	Memberfile.Close();
	
	Subscription sub;
	sub.subscription_delete(key);
	return; 
}

void Member::member_update() {
	std::cout << "************************" << endl;
	std::cout << "Member Update Processing" << endl;
	std::cout << "************************" << endl;
	std::cout << "Update Member ID : ";
	string key, id; cin >> key;
	// 무엇을 Update 할 지 고르는 곳

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> Memberfile(buffer);
	char str[] = "fileOfMember.dat";

	Memberfile.Open(str, ios::in); // 파일 열었음

	int recBefore, recAfter, compare = -3, originalSize, newbieSize;
	int sizeOfSpace, availSpace;

	while (1) {
		Member member;
		recBefore = Memberfile.Read(member);
		if (compare == recBefore) break;
		compare = recBefore;
		id = member.ID;

		if (!id.compare(key)) {
			Member newbie;
			originalSize = member.member_size();
			recAfter = Memberfile.Read(member);
			newbie.member_input(newbie, key); // newbie에 데이터 받아

			newbieSize = newbie.member_size();
			Memberfile.Close();

			if (originalSize >= newbieSize) {
				Memberfile.Open(str, ios::out);
				recBefore -= 2;

				sizeOfSpace = recAfter - recBefore;
				availSpace = sizeOfSpace - newbieSize;

				if (availSpace >= 8) {
					Memberfile.Write(newbie, recBefore);

					Member space; 
					string blank(""); string star("*"); string pass("");
					availSpace -= 7;

					for (int i = 0; i < (availSpace - 12); i++) pass += " ";

					space.update_id(star);
					space.update_password(pass);
					space.update_name(blank);
					space.update_address(blank);
					space.update_mileage(blank.data());
					space.update_phoneNumber(blank);

					Memberfile.Write(space);
					Memberfile.Close();

					return;
					
				}
				return;
			}

			else if (originalSize < newbieSize) {
				member_delete(key);
				Memberfile.Open(str, ios::app);
				Memberfile.Write(newbie);
				Memberfile.Close();
				return;
			}

			else {
				std::cout << "error breaks out at Comparison" << endl;
				return;
			}			
		}
	}
	Memberfile.Close();
	std::cout << "============================================================" << endl;
	std::cout << "=======================UPDATE ERROR=========================" << endl;
	std::cout << "====================There isn't the key=====================" << endl;
	std::cout << "============================================================" << endl;
	return;
}

int Member::member_size() {
	int total = 0;
	total += this->ID.size() + this->Password.size() + this->Name.size() +
		this->Phone_Number.size() + this->Address.size() + strlen(Mileage);
	/*
	cout << "ID : " <<this->ID.size() << endl;
	cout << this->Password.size() << endl;
	cout << this->Name.size() << endl;
	cout << this->Phone_Number.size() << endl;
	cout << this->Address.size() << endl;
	cout << string(this->Mileage).size() << endl;
	*/
	return total;
}

void Member::member_input(Member& newbie, string key) {
	string mem;

	newbie.update_id(key);

	std::cout << "Input PassWord : "; cin >> mem;
	newbie.update_password(mem);

	std::cout << "Input Name : "; cin >> mem;
	newbie.update_name(mem);

	std::cout << "Input Phone_Number : "; cin >> mem;
	newbie.update_phoneNumber(mem);

	std::cout << "Input Address : "; cin >> mem;
	newbie.update_address(mem);

	std::cout << "Input Mileage : "; cin >> mem;
	newbie.update_mileage(mem.data());
}