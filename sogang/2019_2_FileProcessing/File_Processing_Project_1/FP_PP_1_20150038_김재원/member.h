#include "sameh.h"
#include "iobuffer.h"
#include "buffile.h"
#include "delim.h"
#include "varlen.h"
#include "recfile.h"
#include <iostream>

using namespace std;

#define MILEAGE_CHAR 10
#define STDMAXBUF 256

class Member {
private:
	string ID;
	string Password;
	string Name;
	string Phone_Number;
	string Address;
	char *Mileage;

public:
	Member();
	Member(const string ID);
	Member(const Member& s);

	Member& operator = (const Member& s);
	bool operator == (const Member& s);
	bool operator != (const Member& s);

	friend istream& operator >> (istream& is, Member& s);
	friend ostream& operator << (ostream& os, Member& s);

	void update_id(const string new_id) { ID = new_id; }
	void update_password(const string new_password) { Password = new_password; }
	void update_name(const string new_name) { Name = new_name; }
	void update_phoneNumber(const string new_number) {Phone_Number = new_number; }
	void update_address(const string new_address) { Address = new_address; }
	void update_mileage(const char* new_mileage) { memcpy(Mileage, new_mileage, 10); }

	bool Pack(IOBuffer& Buffer) const;
	bool Unpack(IOBuffer&);

	bool member_search(string);
	int member_pos_search(string);
	void member_insert();
	void member_insert(Member& member);
	void member_delete(string);
	void member_update();
	int member_size();
	void member_input(Member& newbie, string);

};

istream& operator >> (istream& is, Member& s);
ostream& operator << (ostream& is, Member& s);