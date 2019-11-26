#include <iostream>

using namespace std;

int main(void) {
	int n, i, j;
	int* arr = (int*)malloc(sizeof(int) * 2000);
	cin >> n;
	
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 2; 

	for (i = 3; i < 2000; i++) 
		arr[i] = (arr[i - 1] + arr[i - 2]) % 100007;
	
	printf("%d\n", arr[n]);

	return 0;
}