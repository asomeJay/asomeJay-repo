/* 괄호 추가하기 */
#include <iostream>
#include <climits>

#define MAX_EXPRESSION 25
#define ARRAY_END 100

using namespace std;

void b_tracking(int index, long long int[],int);
long long int bracket_calculation(long long int operand[], int operators, int index);
long long int total_calculation(long long int operand[]);
void insert_new_value(long long int operand[], int index, long long int sum);

long long int maxi;
long long int stri[MAX_EXPRESSION];

int main(void) {
	int i, j, n_of_string;
	maxi = LLONG_MIN;
	
	scanf("%d", &n_of_string); 
	getchar(); // 빈 공간을 하나 받아줍시다.
	/* 글자 하나씩 받아서 숫자면은 숫자로 바꿔서 집어넣고
	  연산자면 고대로 집어넣는다. */
	for (i = 0; i < n_of_string; i++) {
		j = getchar();
		if (j != '+' && j != '-' && j != '*') {
			stri[i] = j - '0';
		}
		else {
			stri[i] = j;
		}
	}

	stri[i] = ARRAY_END;

	/*연산자가 하나도 안 들어오는 케이스 */
	maxi = total_calculation(stri);
	/* 연산자가 들어왔다면 백트랙킹을 활용해서 모든 케이스 조사하기 */
	
	for (i = 1; i < n_of_string; i += 2)
		b_tracking(i, stri, n_of_string);
	
	printf("%lld", maxi);

	return 0;
}

void b_tracking(int index, long long int s[], int size) {
	if (size <= 0) return;

	int i;
	long long int now_array[MAX_EXPRESSION];
	long long int bracket_sum, operators, total_sum;

	/* 복사하기 */
	for (i = 0; i < MAX_EXPRESSION; i++)
		now_array[i] = s[i];

	operators = now_array[index];

	// 1. 괄호 주변을 하나만 계산한다.
	bracket_sum = bracket_calculation(now_array, operators, index);

	// 2 괄호 계산한 걸 집어넣는다. 
	insert_new_value(now_array, index, bracket_sum);

	// 3. 전체 연산을 수행한다.
	total_sum = total_calculation(now_array);

	// 4. 전체 연산을 수행한 결과가 역대 최고면 maxi를 갱신한다.
	if (total_sum > maxi) {
		maxi = total_sum;
	}

	// 5. 다시 백 트랙킹
	for (i = index + 2; i < size - 2; i += 2) {
		b_tracking(i, now_array, size - 2);
	}
}

/* 숫자 배열과 operator를 받아서 operator 양 옆을 계산한다. (괄호 게산이라 생각하면됨)*/
long long int bracket_calculation(long long int operand[], int operators, int index) {
	switch (operators) {
	case '+':
		return operand[index - 1] + operand[index + 1];
	case '-':
		return operand[index - 1] - operand[index + 1];
	case '*':
		return (operand[index - 1]) * (operand[index + 1]);
	}
}

long long int total_calculation(long long int operand[]){
	int i;
	long long int finals = operand[0];

	for (i = 1; operand[i] != ARRAY_END; i += 2) {
		switch (operand[i]) {
		case '+':
			finals += operand[i + 1];
			break;
		case '-':
			finals -= operand[i + 1];
			break;
		case '*':
			finals *= operand[i + 1];
			break;
		default:
			break;
		}
	}
	return finals;
}

void insert_new_value(long long int operand[], int index, long long int sum) {
	int i;
	
	for (i = index; operand[i + 2] != ARRAY_END; i++)
		operand[i] = operand[i + 2];

	operand[i] = ARRAY_END;
	operand[index - 1] = sum;
}