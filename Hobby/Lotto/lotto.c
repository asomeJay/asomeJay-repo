#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define Max_size 844
void merge_sort(int a[][7], int b[][7], int row);
void sort(int a[][7], int b[][7], int row);
int mini(int a, int b);

int main(void)
{
	
	FILE *fp, *fb;
	fp = fopen("lotto.txt", "r");
	fb = fopen("lotto_search.txt", "w");
	srand(time(NULL));
	int count = 0, limit = 7, ticket = 0;
	int a_rand[Max_size][7];
	int b_rand[Max_size][7];
	int lotto[Max_size][7];
	long double sum_ticket = 0, sum_money = 0;
		while (count == 0)
		{
			ticket += Max_size;
			for (int i = 0; i < Max_size; i++)
			{
				for (int j = 0; j < limit; j++)
					a_rand[i][j] = (rand() % 45) + 1;

				merge_sort(a_rand, b_rand, i);
				for (int m = 0; m < 7; m++)
					if (a_rand[i][m] == a_rand[i][m + 1])
					{
						i--;
						break;
					}
			}
			for (int q = 0; q < Max_size; q++)
			{
				fscanf(fp, "%d	%d	%d	%d	%d	%d	%d", &lotto[q][0], &lotto[q][1], &lotto[q][2], &lotto[q][3], &lotto[q][4], &lotto[q][5], &lotto[q][6]);
				for (int i = 0; i < Max_size; i++)
				{
					if (lotto[q][0] != a_rand[i][0])
						continue;
					else if (lotto[q][1] != a_rand[i][1])
						continue;
					else if (lotto[q][2] != a_rand[i][2])
						continue;
					else if (lotto[q][3] != a_rand[i][3])
						continue;
					else if (lotto[q][4] != a_rand[i][4])
						continue;
					else if (lotto[q][5] != a_rand[i][5])
						continue;
					else if (lotto[q][6] != a_rand[i][6])
						continue;
					count++;
				}
			}
		}
	
		printf("\nyou need ticket %d\n", ticket);
		printf("and you need money %d won", ticket * 1000);
	
	return 0;
}

void merge_sort(int a[][7], int b[][7], int row)
{
	
	for (int width = 1; width < 7; width *= 2)
	{
		for (int k = 0; k < 7; k += 2 * width)
		{
			int ileft = k, iright = mini(k + width, 7), limit = mini(k + 2 * width, 7);
			for (int m = k; m < limit; m++)
			{
				if (ileft < k+width && (iright >= limit || a[row][ileft] < a[row][iright]))
					b[row][m] = a[row][ileft++];

				else
					b[row][m] = a[row][iright++];
			}
		}
		sort(a, b, row);
	}
	return;
}

void sort(int a[][7], int b[][7], int row)
{
	for (int i = 0; i < 7; i++)
		a[row][i] = b[row][i];

	return;
}

int mini(int a, int b)
{
	return (a < b ? a : b);
}
