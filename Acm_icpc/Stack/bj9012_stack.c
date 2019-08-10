#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
	char data;
	struct StackNode *next;
}StackNode;

typedef struct LinkedStack {
	StackNode *top;
}LinkedStack;

void push(LinkedStack *s, char c);
char pop(LinkedStack *s);
void init(LinkedStack *s);
int is_empty(LinkedStack *s);
int comparison(char a, char b);

int main(void)
{
	LinkedStack *line = (LinkedStack *)malloc(sizeof(LinkedStack));
	init(line);
	char s[40];
	scanf("%s", s);

	int mul = 1, count = 0, hab = 0;
	int flag = 0, size = 0;
	int store[20] = { 0 };
	for (int i = 0; s[i] != '\0'; i++)
	{
		char buf = s[i];
		char imsi, imsi_imsi;
		push(line, buf);
		size++;
		if (buf == '(' || buf == '[')
		{
			flag = 1;
			if (buf == '(')
				mul *= 2;
			else
				mul *= 3;
		}
		else
		{
			if ((imsi = pop(line)) == '\0')
			{
				printf("0\n");
				return 0;
			}
			size--;
			if (flag == 1)
			{
				store[count++] = mul;
				flag = 0;
			}
			if (imsi == ')')
				mul /= 2;
			else
				mul /= 3;
			imsi_imsi = imsi;
			imsi = pop(line);
			if (comparison(imsi, imsi_imsi) == 0)
			{
				printf("0\n");
				return 0;
			}
			size--;
		}
	}

	if (size != 0)
	{
		printf("0\n");
		return 0;
	}
	for (int i = 0; store[i] != 0; i++)
		hab += store[i];

	printf("%d\n", hab);
	return 0;
}

void push(LinkedStack *s, char c)
{
	StackNode *ne = (StackNode *)malloc(sizeof(StackNode));
	ne->next = s->top;
	ne->data = c;
	s->top = ne;
	s->top->next = ne->next;
	return;
}

char pop(LinkedStack *s)
{
	if (is_empty(s) == 0) return '\0';
	char c;
	StackNode *del = (StackNode *)malloc(sizeof(StackNode));
	del = s->top;
	del->data = s->top->data;
	del->next = s->top->next;
	s->top = s->top->next;
	c = del->data;
	free(del);
	return c;
}

void init(LinkedStack *s)
{
	s->top = NULL;
	return;
}

int is_empty(LinkedStack *s)
{
	if (s->top == NULL)
		return 0;
	return 1;
}

int comparison(char a, char b)
{
	if (a == '(' && b == ')')
		return 1;
	else if (a == '[' && b == ']')
		return 1;
	else
		return 0;
}
