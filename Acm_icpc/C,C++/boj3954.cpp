/* BrainFuck 인터프리터 */

#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

#define MAX_SM 100000 + 1
#define MAX_SCI 4096
#define LEFT 3
#define RIGHT 1
#define MAX_COUNT 500000000
#define MINUS 0
#define PLUS 1

using namespace std;

int sm, sc, si, pointer;
int num_array[MAX_SM];
int code_array[MAX_SCI];

void move_pointer(int dir);
void calculate(int mode);

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int i, nt_case, t_p, code_size;

	cin >> nt_case; // 전체 케이스가 몇 번인가 체크함. 

	for (int t = 1; t <= nt_case; t++) {
		int inst_pos, program_counter, max_ind, char_pointer;
		pointer = inst_pos = program_counter = max_ind = char_pointer = 0;
		string code, in;
		stack<int> s_pointer;

		cin >> sm >> sc >> si;
		cin >> code;
		cin >> in;

		for (i = 0; i < sc; i++) {
			if (code[i] == '[') {
				s_pointer.push(i);
			}

			else if (code[i] == ']') {
				t_p = s_pointer.top();
				s_pointer.pop();
				code_array[t_p] = i;
				code_array[i] = t_p;
			}
		}

		while ((program_counter <= MAX_COUNT) && (inst_pos < sc)) {
			if (max_ind < inst_pos)
				max_ind = inst_pos;

			switch (code[inst_pos]) {
			case '-': calculate(MINUS);
				break;
			case '+': calculate(PLUS);
				break;
			case '<': move_pointer(LEFT);
				break;
			case '>': move_pointer(RIGHT);
				break;
			case '[':
				if (num_array[pointer] == 0) {
					inst_pos = code_array[inst_pos];
					break;
				}
				break;
			case ']':
				if (num_array[pointer] != 0) {
					inst_pos = code_array[inst_pos];
					break;
				}
				break;
			case '.':
				break;
			case ',':
				if (char_pointer >= in.size())
					num_array[pointer] = 255;
				else
					num_array[pointer] = in[char_pointer++];
				break;
			default:
				cout << "CASE ERROR " << endl;
			}

			program_counter++;
			inst_pos++;
		}
		if (inst_pos == sc)
			cout << "Terminates\n";
		else 
			cout << "Loops " << code_array[max_ind] << " " << max_ind << '\n';
	}
	
	return 0;
}



void move_pointer(int dir) {
	if (dir == LEFT) {
		if (pointer == 0)
			pointer = sm - 1;
		else
			pointer--;
	}

	if (dir == RIGHT) {
		if (pointer == sm - 1)
			pointer = 0;
		else
			pointer++;
	}
}

void calculate(int mode) {
	switch (mode) {
	case MINUS:
		if (num_array[pointer] == 0)
			num_array[pointer] = 255;
		else
			num_array[pointer]--;
		break;
	case PLUS:
		if (num_array[pointer] == 255)
			num_array[pointer] = 0;
		else
			num_array[pointer]++;
		break;
	}
}