/* BrainFuck 인터프리터 */

#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>

#define MAX_SCI 10000
#define LEFT 3
#define RIGHT 1
#define MAX_COUNT 50000000
#define MINUS 0
#define PLUS 1

using namespace std;

int sm, sc, si, pointer;
int loop_position[MAX_SCI];

void move_pointer(int dir);
void calculate(vector<int> &num_array, int mode);

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int i, nt_case;
	cin >> nt_case; // 전체 케이스가 몇 번인가 체크함. 

	for (int t = 1; t <= nt_case; t++) {
		int inst_pos, program_counter, max_ind, char_pointer, t_p;
		inst_pos = program_counter = max_ind = char_pointer = 0;

		stack<int> s_pointer;

		cin >> sm >> sc >> si;

		vector<char> code(sc);
		vector<char>input_char(si);
		vector<int>num_array(sm, 0);

		for (i = 0; i < sc; i++) {
			cin >> code[i];
			if (code[i] == '[') {
				s_pointer.push(i);
			}

			else if (code[i] == ']') {
				t_p = s_pointer.top();
				s_pointer.pop();
				loop_position[t_p] = i;
				loop_position[i] = t_p;
			}
		}

		for (i = 0; i < si; i++) cin >> input_char[i];

		while ((program_counter <= MAX_COUNT) && (inst_pos != sc)) {
			max_ind = max(max_ind, inst_pos);
			switch (code[inst_pos]) {
			case '-': calculate(num_array, MINUS);
				break;
			case '+': calculate(num_array, PLUS);
				break;
			case '<': move_pointer(LEFT);
				break;
			case '>': move_pointer(RIGHT);
				break;
			case '[':
				if (num_array[pointer] == 0) {
					inst_pos = loop_position[inst_pos];
				}
				break;
			case ']':
				if (num_array[pointer] != 0) {
					inst_pos = loop_position[inst_pos];
				}
				break;
			case ',':
				if (char_pointer == si)
					num_array[pointer] = 255;
				else
					num_array[pointer] = input_char[char_pointer++];
				break;
			}

			program_counter++;
			inst_pos++;
		}

		if (inst_pos == sc)
			cout << "Terminates\n";
		else 
			cout << "Loops " << loop_position[max_ind] << " " << max_ind << '\n';
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

void calculate(vector<int> &num_array, int mode) {
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