/* 나이순 정렬 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
int N;

class member {
public:
	int year, cnt;
	string name;
	
	void in(int a, string s, int c) {
		this->year = a;
		this->name = s;
		this->cnt = c;
	}
};

bool comp(const member a, const member b) {
	if (a.year != b.year)
		return a.year < b.year;
	else 
		return a.cnt < b.cnt;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;
	vector<member> people(N);

	
	for (int i = 0; i < N; i++) {
		int a; string s;
		cin >> a >> s;
		people[i].in(a, s, i);
	}

	sort(people.begin(), people.end(), comp);

	for (int i = 0; i < N; i++)
		cout << people[i].year << " " << people[i].name << '\n';

	return 0;
}