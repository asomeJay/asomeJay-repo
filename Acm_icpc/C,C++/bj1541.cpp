/* 잃어버린 괄호 */

#include <iostream>
#include <string>
#include <queue>

using namespace std;

queue<int> i_q;	//여기에 각각의 부분합을 넣어줄 것입니다. 

void take_sub_sum(string);	// 부분합 구하는 function입니다. 

int	main(void) {
	string in, sub_in;
	size_t start_point, t;
	int sum = 0, minus_point; 

	start_point = minus_point = 0;
	cin >> in;	// input을 받는 구간입니다. 

	while (1) {
		// find 함수를 이용해서 minus의 위치를 얻습니다.
		while (minus_point != in.size() && in[minus_point] != '-')
			minus_point++;

		// 만약 -의 위치가 npos라면 식이 끝날 때 까지 -가 없다는 의미이므로
		// 부분합을 구해주는 take_sub_sum()을 활용합니다. 
		if (minus_point == in.size()) {
			sub_in = in.substr(start_point);
//			cout << sub_in << endl;

			take_sub_sum(sub_in);
			break;
		}

		// 만약 -의 위치를 잘 구했다면 그 - 위치 앞까지 숫자를 분절하고
		// 그 숫자 string을 integer로 변환합니다.
		sub_in = in.substr(start_point, minus_point-start_point);
//		cout << sub_in << endl;
		minus_point++;
		start_point = minus_point;
		take_sub_sum(sub_in);
	}
	
	/* q에 있는 숫자를 차례대로 꺼내면서 빼면 최소합을 완성할 수 있습니다. */

	if (!i_q.empty()) {
		sum = i_q.front();
		i_q.pop();
	}

	while (!i_q.empty()) {
		sum -= i_q.front();
		i_q.pop();
	}

	cout << sum << endl;

	return 0;
}

/* 입력받은 문자열을 '+'를 기준으로 분절한 후, stoi 함수를 이용해서 
  정수로 바꿔줍니다. 그리고 바꿔준 수를 모두 더해서 i_q에 push합니다. */

void take_sub_sum(string expression) {
	int sub_total;
	string parsed_expression, t;
	size_t start_point, plus_position;
	start_point = sub_total = 0;
	parsed_expression = expression;

	while (1) {
		// 1. find 함수를 통해서 '+'의 위치를 찾습니다.
		plus_position = parsed_expression.find("+", start_point);

		// 2. find()가 npos를 return 했다면 식이 끝난 것입니다. 
		// 그러니 남은 string을 모두 integer로 바꿔서 지금까지 누적된 sub_total에
		// 더하고, 이를 i_q에 push합니다. 그리고 return 합니다.

		if (plus_position == string::npos) {
			t = parsed_expression.substr(start_point);
			sub_total += stoi(t);
			i_q.push(abs(sub_total));
			return;
		}

		// substr()을 이용해서 '+'를 포함하지 않은 숫자 string을 얻습니다.
		// 그 후 stoi()를 이용해서 이 값을 integer로 바꿔줍니다.
		t = parsed_expression.substr(start_point, plus_position);
		start_point = plus_position + 1;
		sub_total += stoi(t);
	}
}