/* 암호 만들기 */

#include <iostream>
#include <algorithm>

using namespace std;

int l, c;
char character[20];
char ans[20];

void password(int depth, int);
bool char_chk();

int main(void) {
	int i, j;
	cin >> l >> c;
	//scanf("%d %d", &l, &c);

	for (i = 1; i <= c; i++) {
		//scanf("%c", &character[i]);
		cin >> character[i];
	}

	sort(character + 1, character + c + 1);

	for (i = 1; i <= c; i++) {
		ans[1] = character[i];
		password(2, i);
	}

	return 0;
}

void password(int depth, int index) {
	int i, j;

	if (depth > l) {
		if (char_chk()) {
			for (i = 1; i <= l; i++) {
				printf("%c", ans[i]);
			}
			printf("%\n");
		}
		return;
	}

	for (i = index + 1; i <= c; i++) {
		ans[depth] = character[i];
		password(depth+1, i);
	}
}

bool char_chk() {
	int consonant, collection, i, j;
	consonant = collection = 0;

	for (i = 1; i <= l; i++) {
		if (ans[i] == 'a' || ans[i] == 'e' || ans[i] == 'i' || ans[i] == 'o'
			|| ans[i] == 'u') {
			collection++;
		}
		else {
			consonant++;
		}
	}

	if (consonant >= 2 && collection >= 1) {
		return true;
	}
	return false;

}