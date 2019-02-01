#include <stdio.h>
#include <string.h>

int queue[10004] = { 0 };
int front_index = 0;
int back_index = -1;

#define size size1()
#define empty empty1()
#define	front front1()
#define back back1()
#define pop pop1()

void push(int a);
int pop1();
int size1();
int empty1();
void front1();
void back1();


int main(void)
{
	int n, for_push;
	char s[10];
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", s);
		if (strcmp(s, "push") == 0)
		{
			scanf("%d", &for_push);
			push(for_push);
		}
		else if (strcmp(s, "pop") == 0)
			pop;
		else if (strcmp(s, "size") == 0)
			size;
		else if (strcmp(s, "empty") == 0)
			empty;
		else if (strcmp(s, "front") == 0)
			front;
		else if (strcmp(s, "back") == 0)
			back;
	}
	return 0;
}

void push(int a)
{
	back_index++;
	queue[back_index] = a;
	return;
}

int pop1()
{
	if (back_index - front_index + 1 == 0)
	{
		printf("-1\n");
		return 0;
	}
	printf("%d\n", queue[front_index]);
	queue[front_index++] = 0;
	return 1;
}

int size1()
{
	printf("%d\n", back_index - front_index + 1);
	return back_index - front_index + 1;
}

int empty1()
{
	if (back_index - front_index + 1 == 0)
	{
		printf("%d\n", 1);
		return 1;
	}
	else
		printf("%d\n", 0);
	return 0;
}

void front1()
{
	if (back_index - front_index + 1 == 0)
	{
		printf("%d\n", -1);
		return;
	}
	printf("%d\n", queue[front_index]);
	return;
}

void back1()
{
	if (back_index - front_index + 1 == 0)
	{
		printf("%d\n", -1);
		return;
	}
	printf("%d\n", queue[back_index]);
	return;
}