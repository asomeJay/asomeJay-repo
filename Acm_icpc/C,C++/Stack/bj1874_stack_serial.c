#include <stdio.h>
char store[200050] = { 0 }; // + - ´ãÀ» ±×¸©
int stack[200050] = { 0 }; 
int stack_input[200050] = { 0 };
int count = 0;
int incle = 0;
void push(int a);
void pop();

int main(void)
{
	int n, j = 0;
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%d", &stack_input[i]);
	
	for (int i = 0; i < n; i++)
	{
		push(i+1);
		while (stack[count] == stack_input[j])
		{
			if (count == -1) break;
			pop();
			count--;
			j++;
		}
		count++;
	}
	if (stack[0] != 0) printf("NO\n");
	else
	{
		int m = 0;
		while (store[m] != '\0')
			printf("%c\n", store[m++]);
	}
	return 0;
}

void push(int a)
{
	stack[count] = a;
	store[incle++] = '+';
	return;
}

void pop()
{
	stack[count] = 0;
	store[incle++] = '-';
	return;
}
