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
	FILE* fp = fopen("data.txt", "r");//파일 포인터 생성
	//행과 열의 수 읽어오기
	int row1, col1;
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

	//B행렬도 위와같은 방식으로 진행
	int col2, row2;
	fscanf(fp, "%d", &row2);
	fscanf(fp, "%d", &col2);
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
	rewind(fp);//파일포인터를 맨 처음으로 이동

	/*행렬의 크기를 알려주는 부분을 넘기기위해 사용 FSEEK 함수를 이용하는 방법도 있지만
	데이터에 따라 계산이 복잡해져 오류를 야기할 수 있는 위험이 존재함*/
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
			if (temp != 0)//읽어온 정수가 0이 아닌경우에 희소행렬에 저장
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

	/////////////////////--A+B를 진행--////////////////////
	if (row1 == row2 && col1 == col2)//행렬의 합에대한 조건 확인
	{
		//결과를 2차원 배열을 동적으로 생성해 저장
		int** sum = ((int**)malloc(sizeof(int*) * row1));
		for (int i = 0; i < row1; i++)
		{
			sum[i] = ((int*)malloc(sizeof(int) * col1));
			for (int j = 0; j < col1; j++)
			{
				sum[i][j] = 0;//생성한 배열을 0으로 초기화
			}
		}

		//결과를 담는 배열에 A배열을 +연산해줌
		for (int i = 0; i < count1; i++)
		{
			sum[arr1[i].row][arr1[i].col] += arr1[i].data;
		}
		//다시 B행렬을 +연산함으로 A+B연산이 완료 소
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

		//메모리 할당 해제
		for (int i = 0; i < row1; i++)
		{
			free(sum[i]);
		}
		free(sum);
	}
	else
	{
		printf("계산이 불가능 합니다.  행렬 간의 합는 두 행렬의 행과 열의 개수가 모두 같아야 합니다.\n");
	}

	///////////////////////////////////////////////////////////

	/////////////////////--A-B를 진행--////////////////////
	if (row1 == row2 && col1 == col2)//행렬의 차에대한 조건 확인
	{
		//위와 같이 결과를 답는 배열을 생성
		int** sub = ((int**)malloc(sizeof(int*) * row1));
		for (int i = 0; i < row1; i++)
		{
			sub[i] = ((int*)malloc(sizeof(int) * col1));
			for (int j = 0; j < col1; j++)
			{
				sub[i][j] = 0;
			}
		}

		//A행렬을 결과를 답는 배열에 - 연산을 진행
		for (int i = 0; i < count1; i++)
		{
			sub[arr1[i].row][arr1[i].col] -= arr1[i].data;
		}

		//다시 B행렬을 + 연산함으로 A - B가 아닌 - A + B연산으로 진행

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

		//메모리 할당 해제
		for (int i = 0; i < row1; i++)
		{
			free(sub[i]);
		}
		free(sub);

	}
	else
	{
		printf("계산이 불가능 합니다. 행렬 간의 차는 두 행렬의 행과 열의 개수가 모두 같아야 합니다.\n");
	}

	///////////////////////////////////////////////////////////////////////

	/////////////////////--AXB를 진행--////////////////////
	if (row1 == col2)//행렬의 곱에대한 조건 확인
	{
		//위와 같이 결과를 답는 배열을 생성
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
				if (arr1[i].col == arr2[j].row)//arr1[i]의 열과 arr2[j]의 행의 위치가 같으면
				{
					mul[arr1[i].row][arr2[j].col] += arr1[i].data * arr2[j].data;//연산 결과를 더함
				}
			}
		}
		//희소행렬에 없는 원소의 행과 열은 모드 0으로 연산결과가 0임

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
		//메모리 할당 해제
		for (int i = 0; i < row1; i++)
		{
			free(mul[i]);
		}
		free(mul);

	}
	else
	{
		printf("계산이 불가능 합니다. 행렬 간의 곱은 A행렬의 행과 B행렬의 열의 개수가 같아야 합니다.\n");
	}

	//메모리 해제
	free(arr1);
	free(arr2);

	return 0;

	
}