#include <iostream>

using namespace std;

int main() {
	int input;
	cout << "IP와 DNS 서버 주소를 자동으로 설정하려면 1 아니면 0을 입력하세요" << endl;
	cin >> input;

	if (input == 1) { // 서버 주소 자동 설정


	} 
	else { // 서버 주소 일일이 쳐야함
		int IP, subnet, gateway;
		int dns;

		cin >> IP >> subnet >> gateway;
		cin >> dns;

		//bat 파일에 집어넣어서 실행만 시키면 끝

	}
	return 0;
}