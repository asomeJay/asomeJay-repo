#include <stdio.h>

char stack[30];
int top = -1;

void push(char c);
void pop();
int	is_full();
int is_empty();
int priority(char c);
int main(void)
{
	printf("Enter your mid-fix : ");
	char hand_out, s[30];
	int i;
	scanf("%s", s);

	for (i = 0; s[i] != '\0'; i++)
	{
		hand_out = s[i];
		switch (hand_out)
		{
		case '(':
			push(hand_out);
			break;
		case ')':
			while (stack[top] != '(')
				pop();
			stack[top] = '\0';
			break;
		case '+':
			if (is_empty() == 0)
			{
				push(hand_out);
				break;
			}
			while (is_empty() != 0 && priority(stack[top]) >= priority(hand_out))
				pop();
			if (is_empty() == 0 || priority(stack[top]) < priority(hand_out))
				push(hand_out);
			break;
		case '-':
			if (is_empty() == 0)
			{
				push(hand_out);
				break;
			}
			while (is_empty() != 0 && priority(stack[top]) >= priority(hand_out))
				pop();
			if (is_empty() == 0 || priority(stack[top]) < priority(hand_out))
				push(hand_out);
			break;
		case '*':
			if (is_empty() == 0)
			{
				push(hand_out);
				break;
			}
			while (is_empty() != 0 &&  priority(stack[top]) >= priority(hand_out))
				pop();
			if (is_empty() == 0 || priority(stack[top]) < priority(hand_out))
				push(hand_out);
			break;
		case '/':
			if (is_empty() == 0)
			{
				push(hand_out);
				break;
			}
			while (is_empty() != 0 && priority(stack[top]) >= priority(hand_out))
				pop();
			if (is_empty() == 0 || priority(stack[top]) < priority(hand_out))
				push(hand_out);
			break;
		default : 
			printf("%c", hand_out);
			break;
		}
	}
	while (top != -1)
		printf("%c", stack[top--]);

	return 0;
}

void push(char c)
{
	if (is_full() == 0)
	{
		printf("push error\n");
		exit(1);
	}
	top++;
	stack[top] = c;
	return;
}
void pop()
{
	if (top == -1)
	{
		printf("pop error\n");
		exit(1);
	}
	printf("%c",stack[top]);
	stack[top] = '\0';
	top--;
}

int	is_full()
{
	if (top == 29) return 0;
	return 1;
}


int is_empty()
{
	if (top == -1) return 0;
	return 1;
}

int priority(char c)
{
	if (c == '(' || c == ')') return -1;
	if (is_empty() == 0) return 20;
	if (c == '+' || c == '-') return 0;
	else if (c == '*' || c == '/') return 1;
}