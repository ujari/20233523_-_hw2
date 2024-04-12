#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct sparse_matrix_inform {
	int row;
	int col;
	int data;
}smi;


int main()
{
	FILE* fp = fopen("data.txt", "r");//���� ������ ����
	//��� ���� �� �о����
	int row1, col1;
	fscanf(fp, "%d", &row1);
	fscanf(fp, "%d", &col1);
	int count1 = 0;
	//0�� �ƴ� ���Ұ� �� ����� Ȯ��
	for (int i = 0; i < row1 * col1; i++)
	{
		int data;
		fscanf(fp, "%d", &data);
		if (data != 0)
		{
			count1++;
		}
	}

	//B��ĵ� ���Ͱ��� ������� ����
	int col2, row2;
	fscanf(fp, "%d", &row2);
	fscanf(fp, "%d", &col2);
	int count2 = 0;
	//0�� �ƴ� ���Ұ� �� ����� Ȯ��
	for (int i = 0; i < row2 * col2; i++)
	{
		int data;
		fscanf(fp, "%d", &data);
		if (data != 0)
		{
			count2++;
		}
	}
	rewind(fp);//���������͸� �� ó������ �̵�

	/*����� ũ�⸦ �˷��ִ� �κ��� �ѱ������ ��� FSEEK �Լ��� �̿��ϴ� ����� ������
	�����Ϳ� ���� ����� �������� ������ �߱��� �� �ִ� ������ ������*/
	fscanf(fp, "%d", &row1);
	fscanf(fp, "%d", &col1);


	//�������� ���� �迭�� �����Ҵ����� ����
	smi* arr1 = (smi*)malloc(sizeof(smi) * count1);
	int n = 0;
	for (int i = 0; i < row1; i++)
	{
		for (int j = 0; j < col1; j++)
		{
			int temp;
			fscanf(fp, "%d", &temp);
			if (temp != 0)//�о�� ������ 0�� �ƴѰ�쿡 �����Ŀ� ����
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
	/////////////////////////////////////////////////////////////

	/////////////////////--A+B�� ����--////////////////////
	if (row1 == row2 && col1 == col2)//����� �տ����� ���� Ȯ��
	{
		//����� 2���� �迭�� �������� ������ ����
		int** sum = ((int**)malloc(sizeof(int*) * row1));
		for (int i = 0; i < row1; i++)
		{
			sum[i] = ((int*)malloc(sizeof(int) * col1));
			for (int j = 0; j < col1; j++)
			{
				sum[i][j] = 0;//������ �迭�� 0���� �ʱ�ȭ
			}
		}

		//����� ��� �迭�� A�迭�� +��������
		for (int i = 0; i < count1; i++)
		{
			sum[arr1[i].row][arr1[i].col] += arr1[i].data;
		}
		//�ٽ� B����� +���������� A+B������ �Ϸ� ��
		for (int i = 0; i < count2; i++)
		{
			sum[arr2[i].row][arr2[i].col] += arr2[i].data;
		}
		printf("-------- A + B ---------\n");
		printf("\n\t");
		for (int i = 0; i < row1; i++)
		{
			for (int j = 0; j < col1; j++)
			{
				printf("%d  ", sum[i][j]);
			}
			printf("\n\t");
		}

		//�޸� �Ҵ� ����
		for (int i = 0; i < row1; i++)
		{
			free(sum[i]);
		}
		free(sum);
	}
	else
	{
		printf("����� �Ұ��� �մϴ�.  ��� ���� �մ� �� ����� ��� ���� ������ ��� ���ƾ� �մϴ�.\n");
	}

	///////////////////////////////////////////////////////////

	/////////////////////--A-B�� ����--////////////////////
	if (row1 == row2 && col1 == col2)//����� �������� ���� Ȯ��
	{
		//���� ���� ����� ��� �迭�� ����
		int** sub = ((int**)malloc(sizeof(int*) * row1));
		for (int i = 0; i < row1; i++)
		{
			sub[i] = ((int*)malloc(sizeof(int) * col1));
			for (int j = 0; j < col1; j++)
			{
				sub[i][j] = 0;
			}
		}

		//A����� ����� ��� �迭�� - ������ ����
		for (int i = 0; i < count1; i++)
		{
			sub[arr1[i].row][arr1[i].col] -= arr1[i].data;
		}

		//�ٽ� B����� + ���������� A - B�� �ƴ� - A + B�������� ����

		for (int i = 0; i < count2; i++)
		{
			sub[arr2[i].row][arr2[i].col] += arr2[i].data;
		}
		printf("\n-------- A - B ---------\n");
		printf("\n\t");
		for (int i = 0; i < row1; i++)
		{
			for (int j = 0; j < col1; j++)
			{
				printf("%d  ", sub[i][j]);
			}
			printf("\n\t");
		}

		//�޸� �Ҵ� ����
		for (int i = 0; i < row1; i++)
		{
			free(sub[i]);
		}
		free(sub);

	}
	else
	{
		printf("����� �Ұ��� �մϴ�. ��� ���� ���� �� ����� ��� ���� ������ ��� ���ƾ� �մϴ�.\n");
	}

	///////////////////////////////////////////////////////////////////////

	/////////////////////--AXB�� ����--////////////////////
	if (row1 == col2)//����� �������� ���� Ȯ��
	{
		//���� ���� ����� ��� �迭�� ����
		int** mul = ((int**)malloc(sizeof(int*) * row1));
		for (int i = 0; i < row1; i++)
		{
			mul[i] = ((int*)malloc(sizeof(int) * col2));
			for (int j = 0; j < col2; j++)
			{
				mul[i][j] = 0;
			}
		}

		for (int i = 0; i < count1; i++)
		{
			for (int j = 0; j < count2; j++)
			{
				if (arr1[i].col == arr2[j].row)//arr1[i]�� ���� arr2[j]�� ���� ��ġ�� ������
				{
					mul[arr1[i].row][arr2[j].col] += arr1[i].data * arr2[j].data;//���� ����� ����
				}
			}
		}
		//�����Ŀ� ���� ������ ��� ���� ��� 0���� �������� 0��

		printf("\n-------- A X B ---------\n");
		printf("\n\t");
		for (int i = 0; i < row1; i++)
		{
			for (int j = 0; j < col2; j++)
			{
				printf("%d  ", mul[i][j]);
			}
			printf("\n\t");
		}
		//�޸� �Ҵ� ����
		for (int i = 0; i < row1; i++)
		{
			free(mul[i]);
		}
		free(mul);

	}
	else
	{
		printf("����� �Ұ��� �մϴ�. ��� ���� ���� A����� ��� B����� ���� ������ ���ƾ� �մϴ�.\n");
	}

	//�޸� ����
	free(arr1);
	free(arr2);

	return 0;

	
}