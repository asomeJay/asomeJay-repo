#include "sameh.h"
#include "iobuffer.h"
#include "buffile.h"
#include "delim.h"
#include "varlen.h"
#include "recfile.h"
#include <iostream>

#define NEWSAGENCY_ID 12
#define STDMAXBUF 256

using namespace std;

class NewsAgency {
private:
	char *NewsAgency_ID;
	string Name;
	string Address;

public:
	NewsAgency();
	NewsAgency(const string ID);
	NewsAgency(const NewsAgency& s);

	NewsAgency& operator = (const NewsAgency& s);
	bool operator == (const NewsAgency& s);
	bool operator != (const NewsAgency& s);

	friend istream& operator >> (istream& is, NewsAgency& s);
	friend ostream& operator << (ostream& os, NewsAgency& s);

	void update_newsagency_id(const char* new_NewsAgency_ID) {
		memcpy(this->NewsAgency_ID, new_NewsAgency_ID, NEWSAGENCY_ID);
	}
	void update_name(const string new_number) { this->Name = new_number; }
	void update_address(const string new_address) { this->Address = new_address; }

	bool Pack(IOBuffer& Buffer) const;
	bool Unpack(IOBuffer&);

	bool newsagency_search(string);
	int newsagency_pos_search(string);
	void newsagency_insert();
	void newsagency_insert(NewsAgency& newsagency);
	void newsagency_delete(string);
	void newsagency_update();
	int newsagency_size();
	void newsagency_input(NewsAgency& newbie, string);
};

istream& operator >> (istream& is, NewsAgency& s);
ostream& operator << (ostream& is, NewsAgency& s);
