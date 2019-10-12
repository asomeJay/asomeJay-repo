#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#define MEMBERNUM 1000;
#define NEWSAGENCYNUM 1000;
#define SUBSCRIPTIONNUM 10000;

using namespace std;

int main(void) {
	int memberNum, newsNum, subNum, i, j, temp;
	memberNum = MEMBERNUM;
	newsNum = NEWSAGENCYNUM;
	subNum = SUBSCRIPTIONNUM;

	string member_id, member_pass, member_name, member_phone, member_addr;
	char member_mil[10];

	string news_name, news_addr;
	char news_id[12];

	char sub_id[16], sub_news[12], sub_mil[10];
	string sub_mem;

	ofstream listOfMember("listOfMember.txt");
	ofstream listOfNewsAgency("listOfNewsAgency.txt");
	ofstream listOfSubscription("listOfSubscription.txt");
	listOfMember << memberNum << endl;
	listOfNewsAgency << newsNum << endl;
	listOfSubscription << subNum << endl;

	for (i = 0; i < memberNum; i++) {
		string tp;
		member_id.clear(); member_pass.clear(); member_name.clear(); member_phone.clear(); member_addr.clear(); tp.clear();
		// id
		int lim = 8, passlim = 5, namelim = 5, phonelim = 12, addresslim = 8;
		if (i < 10) {
			lim--;
			passlim--;
			namelim--;
			phonelim--;
			addresslim--;
		}
		else if (i < 100) {
			lim--;
			passlim--;
			namelim--;
			phonelim--;
			addresslim--;
		}

		else if (i < 1000) {
			lim--;
			passlim--;
			namelim--;
			phonelim--;
			addresslim--;
		}

		for (int j = 0; j < lim; j++)
			member_id.push_back('0');
		member_id += to_string(i);
		
		listOfMember << member_id << '|';

		// password
		string pass = "pass";
		for (int j = 0; j < passlim; j++)
			member_pass.push_back('0');
		member_pass += to_string(i);

		listOfMember << member_pass << '|';

		// name
		string name = "mName";
		for (j = 0; j < namelim; j++) 
			member_name.push_back('0');
		member_name += to_string(i);

		listOfMember << member_name << '|';

		// phone number 
		for (j = 0; j < 4; j++) {
			temp = rand() % 10 + 48;
			member_phone.push_back(temp);
		}
		member_phone.push_back(45);

		for (j = 0; j < 4; j++) {
			temp = rand() % 10 + 48;
			member_phone.push_back(temp);
		}
		
		listOfMember << member_phone << '|';

		// address 
		for (j = 0; j < 10; j++) {
			int temp = rand() % 26 + 97;
			member_addr.push_back(temp);
		}
		listOfMember << member_addr << '|';

		//mileage
		for (j = 0; j < 10; j++) {
			temp = rand() % 10 + 48;
			//member_mil[j] = (char)temp;
			tp.push_back(temp);
		}
		listOfMember << tp << endl;
	}
	listOfMember.close();

	for (i = 0; i < newsNum; i++) {
		string newsId;
		newsId.clear(); news_name.clear(); news_addr.clear();
		for (j = 0; j < 12; j++) {
			temp = rand() % 10 + 48;
			newsId.push_back(temp);
		}
		listOfNewsAgency << newsId << '|';

		// news_name
		for (j = 0; j < 5; j++) {
			temp = rand() % 26 + 65;
			news_name.push_back(temp);
		}
		for (j = 0; j < 4; j++) {
			temp = rand() % 26 + 97;
			news_name.push_back(temp);
		}
		listOfNewsAgency << news_name << '|';

		// news_addr
		for (j = 0; j < 5; j++) {
			temp = rand() % 26 + 97;
			news_addr.push_back(temp);
		}
		news_addr.push_back(32);

		for (j = 0; j < 5; j++) {
			temp = rand() % 26 + 97;
			news_addr.push_back(temp);
		}

		listOfNewsAgency << news_addr << endl;
	}
	listOfNewsAgency.close();

	for (i = 0; i < subNum; i++) {
		ifstream listOfNewsAgency("listOfNewsAgency.txt");
		ifstream listOfMember("listOfMember.txt");
		
		string sub_id, sub_news, sub_mil;
		sub_id.clear(); sub_news.clear(); sub_mil.clear(); sub_mem.clear();
		for (j = 0; j < 16; j++) {
			temp = rand() % 10 + 48;
			sub_id.push_back(temp);
		}
		listOfSubscription << sub_id << '|';

		string member, Rtemp;
		temp = rand() % 1000 + 1;
		int pos;
		for (j = 0; j < temp; j++) listOfNewsAgency >> member;
		pos = member.find('|');
		Rtemp = member.substr(pos + 1, 9);
		listOfSubscription << Rtemp << '|';

		member.clear(); Rtemp.clear();
		temp = rand() % 1000 + 1;
		for (j = 0; j < temp; j++) listOfMember >> member;
		Rtemp = member.substr(0, member.find('|'));
		listOfSubscription << Rtemp << '|';

		for (j = 0; j < 10; j++) {
			temp = rand() % 10 + 48;
			sub_mil.push_back(temp);
		}
		listOfSubscription << sub_mil << endl;
		listOfNewsAgency.close();
		listOfMember.close();
	}
	listOfSubscription.close();
	return 0;
}