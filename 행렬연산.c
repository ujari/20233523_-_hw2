#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
typedef struct sparse_matrix_inform {
	int row;
	int col;
	int data;
}smi;



int main()
{
	FILE* fp = fopen("data.txt", "r");
	//행과 열의 수 읽어오기
	int col1, row1;
	fscanf(fp, "%d", &row1);
	fscanf(fp, "%d", &col1);
	int count1 = 0;
	//0이 아닌 원소가 총 몇개인지 확인
	for (int i = 0; i < row1 * col1; i++)
	{
		int data;
		fscanf(fp, "%d", &data);
		if (data != 0)
		{
			count1++;
		}
	}

	///////////////////////////////////
	int col2, row2;
	fscanf(fp, "%d", &col2);
	fscanf(fp, "%d", &row2);
	int count2 = 0;
	//0이 아닌 원소가 총 몇개인지 확인
	for (int i = 0; i < row2 * col2; i++)
	{
		int data;
		fscanf(fp, "%d", &data);
		if (data != 0)
		{
			count2++;
		}
	}
	rewind(fp);
	fscanf(fp, "%d", &row1);
	fscanf(fp, "%d", &col1);
	//희소행렬을 담을 배열을 동적할당으로 생성
	smi* arr1 = (smi*)malloc(sizeof(smi) * count1);
	int n = 0;
	for (int i = 0; i < row1; i++)
	{
		for (int j = 0; j < col1; j++)
		{
			int temp;
			fscanf(fp, "%d", &temp);
			if (temp != 0)
			{
				arr1[n].col = j;
				arr1[n].row = i;
				arr1[n].data = temp;
				n++;
			}

		}

	}
	fscanf(fp, "%d", &col2);
	fscanf(fp, "%d", &row2);
	///////////////
	smi* arr2 = (smi*)malloc(sizeof(smi) * count2);

	n = 0;
	for (int i = 0; i < row2; i++)
	{
		for (int j = 0; j < col2; j++)
		{
			int temp;
			fscanf(fp, "%d", &temp);
			if (temp != 0)
			{
				arr2[n].col = j;
				arr2[n].row = i;
				arr2[n].data = temp;
				n++;
			}

		}

	}
 

	////////합
	int** sum = ((int**)malloc(sizeof(sizeof(int*) * row1)));
	for (int i = 0; i < row1; i++)
	{
		sum[i] = ((int*)malloc(sizeof(sizeof(int) * col1)));
		for (int j = 0; j < col1; j++)
		{
			sum[i][j] = 0;
		}
	}

	//a
	for (int i = 0; i < count1; i++)
	{
		sum[arr1[i].row][arr1[i].col] += arr1[i].data;
	}
	//b
	for (int i = 0; i < count2; i++)
	{
		sum[arr2[i].row][arr2[i].col] += arr2[i].data;
	}
	printf("a+b\n");
	for (int i = 0; i < row1; i++)
	{
		for (int j = 0; j < col1; j++)
		{
			printf("%d ", sum[i][j]);
		}
		printf("\n");
	}
	///////////////////차
	int** sub = ((int**)malloc(sizeof(int*) * row1));
	for (int i = 0; i < row1; i++)
	{
		sub[i] = ((int*)malloc(sizeof(int) * col1));
		for (int j = 0; j < col1; j++)
		{
			sub[i][j] = 0;
		}
	}

	//a
	for (int i = 0; i < count1; i++)
	{
		sub[arr1[i].row][arr1[i].col] -= arr1[i].data;
	}
	//b
	for (int i = 0; i < count2; i++)
	{
		sub[arr2[i].row][arr2[i].col] -= arr2[i].data;
	}
	printf("\na-b\n");
	for (int i = 0; i < row1; i++)
	{
		for (int j = 0; j < col1; j++)
		{
			printf("%d ", sub[i][j]);
		}
		printf("\n");
	}

	//free(arr1);
	//free(arr2);

	//for (int i = 0; i < row1; i++)
	//{
	//	free(sum[i]);
	//}
	//free(sum);

	//for (int i = 0; i < row1; i++)
	//{
	//	free(sub[i]);
	//}
	//free(sub);
	//return 0;

}