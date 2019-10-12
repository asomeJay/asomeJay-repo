#include "sameh.h"
#include "iobuffer.h"
#include "buffile.h"
#include "delim.h"
#include "varlen.h"
#include "recfile.h"
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS

#define SUBSCRIPTION_ID 16
#define NEWSAGENCY_ID 12
#define MILEAGE 10
#define STDMAXBUF 256


using namespace std;

class Subscription {
private:
	char *Subscription_ID; // 별표
	char* NewsAgency_ID;	// 공백
	string Member_ID;			// 얘가 blank 많이
	char* Mileage;			// 공백


public:
	Subscription();
	Subscription(const char* new_Subscription_ID);
	Subscription(const string new_Member_ID);
	Subscription(const Subscription& s);

	Subscription& operator = (const Subscription& s);
	bool operator == (const Subscription& s);
	bool operator != (const Subscription& s);

	friend istream& operator >> (istream& is, Subscription& s);
	friend ostream& operator << (ostream& os, Subscription& s);

	void update_subscription_id(const char* new_Subscription_ID) {
		if (strlen(new_Subscription_ID) > SUBSCRIPTION_ID)
		{
			cout << "지져스 크라이스트" << endl;
			exit(1);
		}
		strcpy(this->Subscription_ID, new_Subscription_ID);
	}
	void update_newsAgency_id(const char* new_newsAgency_ID) {
		strcpy(this->NewsAgency_ID, new_newsAgency_ID);}
	void update_name(const string new_member_id) 
	{ this->Member_ID = new_member_id; }
	void update_mileage(const char* new_mileage) { 
		strcpy(this->Mileage, new_mileage);}


	bool Pack(IOBuffer& Buffer) const;
	bool Unpack(IOBuffer&);

	bool subscription_search(string);
	int subscription_pos_search(string);
	void subscription_insert();
	void subscription_insert(Subscription& subscription);
	void subscription_delete(string);
	void subscription_update();
	int subscription_size();
	void subscription_input(Subscription& newbie, string);
	void subscription_search_choice();
	void subscription_newsagency_search(string);
	void subscription_member_search(string key);
};

istream& operator >> (istream& is, Subscription& s);
ostream& operator << (ostream& is, Subscription& s);