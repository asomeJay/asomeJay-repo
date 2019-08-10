#include <stdio.h>

int main(void)
{
	int big = 0;
	int i = 0, count;
	char s[1000001];
	int length[26] = { 0 };
	
	scanf("%s", s);		//input of string

	while (s[i] != '\0')
	{
		if (s[i] >= 'a')
		{
			s[i] -= 32;
		}
		int cut = s[i] - 'A';
		length[cut]++;
		i++;
	}
	//big quantity, count : thumb numb
	for (int j = 0; j < 26; j++)
	{
		if (big < length[j])
		{
			big = length[j];
			count = j;
		}
	}

	for (int m = 0; m < 26; m++)
	{
		if ((big == length[m]) && (m != count))
		{
			count = -2;
			break;
		}
	}
	printf("%c", count + 65);
	// compare with each other for finding most used alphabet. 
	
}