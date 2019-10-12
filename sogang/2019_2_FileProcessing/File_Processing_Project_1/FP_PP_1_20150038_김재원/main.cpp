#include "newsagency.h"
#include "member.h"
#include "Subscription.h"
#include "buffile.h"
#include "iobuffer.h"
#include "delim.h"
#include "varlen.h"
#include "recfile.h"

#include <fstream>

#define SHOWDEFINE 10

void showMember();
void showNewsAgency();
void showSubscription();
void MemberTest();
void NewsAgencyTest();
void SubscriptionTest();
void NewsAgencySubscriptionSystem();

struct indexTable {
	int recAddr;
	int recSize;
};

vector<struct indexTable> memberTable;
vector<struct indexTable> newsTable;
vector<struct indexTable> subscriptionTable;

int main(void) {
	int flag = 1;
	std::cout << "================================================" << endl;
	std::cout << "============= Welcome My Program! ==============" << endl;
	std::cout << "======= Select Menu and Enter the Number =======" << endl;
	std::cout << "=======                                  =======" << endl;
	while (1) {
		char instruction[20];
		if (flag == 1);
		else {
			std::cout << endl << endl;
			std::cout << "=================================================" << endl;
			std::cout << "=================================================" << endl;
		}
		
		flag = 0;
	std::cout << "======= 1. showMember                     =======" << endl;
	std::cout << "======= 2. showNewsAgency                 =======" << endl
			  << "======= 3. showSubscription               =======" << endl 
			  << "======= 4. MemberTest                     =======" << endl
			  << "======= 5. NewsAgencyTest                 =======" << endl 
			  << "======= 6. SubscriptionTest               =======" << endl
			  << "======= 7. NewsAgencySubscriptionSystem   =======" << endl;
	std::cout << "=================================================" << endl;
	std::cout << "=================================================" << endl;
	std::cout << "Menu Number : "; std::cin >> instruction;
		if (!strcmp(instruction, "1")) showMember();
		else if (!strcmp(instruction, "2")) showNewsAgency();
		else if (!strcmp(instruction, "3")) showSubscription();
		else if (!strcmp(instruction, "4")) MemberTest();
		else if (!strcmp(instruction, "5")) NewsAgencyTest();
		else if (!strcmp(instruction, "6")) SubscriptionTest();
		else if (!strcmp(instruction, "7"))
			NewsAgencySubscriptionSystem();
		else if (!strcmp(instruction, "quit")) break;
	}
	return 0;
}

void showMember() {
	Member member;
	string temp;
	ifstream ifs("listOfMember.txt");
	if (ifs.fail()) {
		std::cout << "listOfMember open failed" << endl;
		exit(-1);
	}
	int n;
	// 라인 수를 받는다.
	ifs >> n; 
	ifs >> member;
	for (int i = 0; i < SHOWDEFINE; i++) {
		ifs >> member;
		std::cout << member;
	}
	ifs.close();
}

void showNewsAgency() {
	NewsAgency agency;
	string temp;
	ifstream ifs("listOfNewsAgency.txt");
	if (ifs.fail()) {
		std::cout << "listOfNewsAgency open failed" << endl;
		exit(-1);
	}

	int n;
	// 라인 수를 받는다.
	ifs >> n;
	ifs >> agency;

	for (int i = 0; i < SHOWDEFINE; i++) {
		ifs >> agency;
		std::cout << agency;
	}

	ifs.close();
}

void showSubscription() {
	NewsAgency subscript;
	string temp;
	ifstream ifs("listOfSubscription.txt");
	if (ifs.fail()) {
		std::cout << "listOfSubscription open failed" << endl;
		exit(-1);
	}

	int n;
	// 라인 수를 받는다.
	ifs >> n;
	ifs >> subscript;
	for (int i = 0; i < SHOWDEFINE; i++) {
		ifs >> subscript;
		std::cout << subscript;
	}
	ifs.close();
}

void MemberTest() {
	
	ifstream ifs("listOfMember.txt");
	if (ifs.fail()) {
		std::cout << "listOfMember open Error!" << endl;
		exit(1);
	}
	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> Memberfile(buffer);
	char str[] = "fileOfMember.dat";
	Memberfile.Create(str, ios::out | ios::trunc);
	for (int i = 0; i < n; i++) {
		Member member;
		ifs >> member;
		int recaddr;
		if ((recaddr = Memberfile.Write(member)) == -1)
			std::cout << "Write Error!" << endl;
	}
	Memberfile.Close();

	Memberfile.Open(str, ios::in);
	for (int i = 0; i < 10; i++) {
		Member member;
		Memberfile.Read(member);
		std::cout << member;
	}
	ifs.close();
	Memberfile.Close();
}

void NewsAgencyTest() {
	ifstream ifs("listOfNewsAgency.txt");
	if (ifs.fail()) {
		std::cout << "listOfNewsAgency open Error!" << endl;
		exit(1);
	}
	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <NewsAgency> NewsAgencyfile(buffer);
	char str[] = "fileOfNewsAgency.dat";
	NewsAgencyfile.Create(str, ios::out | ios::trunc);
	for (int i = 0; i < n; i++) {
		NewsAgency agency;
		ifs >> agency;
		int recaddr;
		if ((recaddr = NewsAgencyfile.Write(agency)) == -1)
			std::cout << "Write Error!" << endl;
	}
	NewsAgencyfile.Close();

	NewsAgencyfile.Open(str, ios::in);
	for (int i = 0; i < 10; i++) {
		NewsAgency agency;
		NewsAgencyfile.Read(agency);
		cout << agency ;
	}
	NewsAgencyfile.Close();
}

void SubscriptionTest() {
	ifstream ifs("listOfSubscription.txt");
	if (ifs.fail()) {
		std::cout << "listOfSubscription open Error!" << endl;
		exit(1);
	}
	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Subscription> Subscriptionfile(buffer);
	char str[] = "fileOfSubscription.dat";
	Subscriptionfile.Create(str, ios::out | ios::trunc);
	for (int i = 0; i < n; i++) {
		Subscription subad;
		ifs >> subad;
		int recaddr;
		if ((recaddr = Subscriptionfile.Write(subad)) == -1)
			std::cout << "Write Error!" << endl;
	}
	Subscriptionfile.Close();

	Subscriptionfile.Open(str, ios::in);
	for (int i = 0; i < 20; i++) {
		Subscription subada;
		Subscriptionfile.Read(subada);
		cout << subada;
	}
	Subscriptionfile.Close();
}

void NewsAgencySubscriptionSystem() {
	std::cout << endl << endl;
	std::cout << "======  NewsAgencySubscription System ====== " << endl;
	std::cout << "Which menu do you want?" << endl;
	std::cout << "1. Member Operation" << endl 
			<< "2. NewsAgency Operation" << endl 
			<< "3. Subscription Operation" << endl;
	int inst;
	std::cin >> inst;
	Member member;
	NewsAgency newsagency;
	Subscription subscription;
	switch (inst) {
	case 1:
		std::cout << endl <<endl << 
			"You choice 'Member'" << endl << endl;

		std::cout << "1. Search" << endl 
			 << "2. Insert" << endl 
			 << "3. Delete" << endl 
			 << "4. Update" << endl;
		std::cin >> inst;
		if (inst == 1) {
			string want;
			std::cin >> want;
			member.member_search(want);
			cout << "If You don't have record, Search FAIL";
			return;
		}
		else if(inst == 2) {
			member.member_insert();
			return;
		}
		else if (inst == 3) {
			string key;
			std::cout << "which one you want delete?" << endl;
			std::cin >> key;
			member.member_delete(key);
			cout << "If You don't have record, DELETE FAIL";

			return;
		}
		else if (inst == 4) {
			member.member_update();
			return;
		}
		break;
	case 2:
		std::cout << endl << endl <<
			"You choice 'NewsAgency'" << endl << endl;		
		std::cout << "1. Search" << endl
				<< "2. Insert" << endl
				<< "3. Delete" << endl
				<< "4. Update" << endl;
		std::cin >> inst;
		if (inst == 1) {
			string want;
			std::cin >> want;
			newsagency.newsagency_search(want);
			cout << "If You don't have record, Search FAIL";
		}
		else if (inst == 2) {
			newsagency.newsagency_insert();
		}
		else if (inst == 3) {
			string key;
			std::cin >> key;
			newsagency.newsagency_delete(key);
			cout << "If You don't have record, DELETE FAIL";

		}
		else if (inst == 4) {
			newsagency.newsagency_update();
		}
		break;
	case 3:
		std::cout << endl << endl <<
			"You choice 'Subcription'" << endl << endl;		
		std::cout << "1. Search" << endl
			<< "2. Insert" << endl
			<< "3. Delete" << endl
			<< "4. Update" << endl;
		std::cin >> inst;
		if (inst == 1) {
			subscription.subscription_search_choice();
			cout << "If You don't have record, Search FAIL";
		}
		else if (inst == 2) {
			cout << "insert" << endl;
			subscription.subscription_insert();
		}
		else if (inst == 3) {
			cout << "delete" << endl;
			string key;
			std::cin >> key;
			subscription.subscription_delete(key);
			cout << "If You don't have record, DELETE FAIL";

		}
		else if (inst == 4) {
			cout << "update" << endl;
			subscription.subscription_update();
		}
		break;
	default:
		std::cout << "!_!_!_!_!_!_!_!_!" << endl;
		std::cout << "choice menu error" << endl;
		std::cout << "!_!_!_!_!_!_!_!_!" << endl;
	}
}

