#include <iostream>
#include <cstdio>
#define _CRT_SECURE_NO_WARNINGS
#define DIRTY 1
#define CLEAN 0
#define SHOUT 0
#define MAKEDIRT 1
using namespace std;

int main(void) {
	int numKan, numSi, start, flag, i, numInitial;
	cin >> numKan >> numSi;

	int* arrKan = (int*)malloc(sizeof(int) * numKan);

	// 칸을 채우는 과정
	flag = 0;
	for (i = 0; i < numKan; i++) {
		scanf("%d", arrKan + i);
	}

	//몇개나 청소해야하는 지 체크하는 과정
	flag = 0; numInitial = 0; start = 0;
	for (i = 0; i < numKan; i++) {
		if ((arrKan[i] == DIRTY) && (flag == 0)) {
			numInitial++;
			flag = 1;
		}
		if (arrKan[i] == CLEAN) {
			flag = 0;
		}
	}
		
	//명령어 받아들이는 과정 SHOUT 와 MAKEDIRT
	int inst, inst__;
	for (i = 0; i < numSi; i++) {
		scanf("%d", &inst);
		if (inst == SHOUT)
			printf("result : %d\n", numInitial);

		if (inst == MAKEDIRT) {
			scanf("%d", &inst__);
			inst__--;

			if (arrKan[inst__] == DIRTY)
				continue;

			arrKan[inst__] = DIRTY;

			if (inst__ - 1 < 0) {
				if (arrKan[inst__ + 1] != DIRTY)
					numInitial++;
				continue;
			}
		

		else if ((inst__ + 1) >= numKan) {
			if (arrKan[inst__ - 1] != DIRTY) {
				numInitial--;
				continue;
			}
		}
		else {
				if ((arrKan[inst__ - 1] == DIRTY) && (arrKan[inst__ + 1] == DIRTY))
					numInitial--;

				else if ((arrKan[inst__ - 1] == DIRTY) || (arrKan[inst__ + 1] == DIRTY))
					continue;

				else
					numInitial++;
			}
		}
	}
	return 0;
}