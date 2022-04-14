#pragma once
#include <iostream>
using namespace std;
#define MaxSize 30							//ϡ������з���Ԫ�����ĸ���
#define M 10
#define N 9
typedef int ElemType;
typedef struct
{
	int r;						//�к�
	int c;						//�к�
	ElemType d;					//Ԫ��ֵ
}TupNode;						//��Ԫ������

typedef struct
{
	int rows;					//����
	int cols;					//����
	int nums;					//����Ԫ�ظ���
	TupNode data[MaxSize];
}TSMatrix;						//��Ԫ��˳�������

void CreateMat(TSMatrix& t, ElemType A[M][N]);		//��ϡ����󴴽���Ԫ���ʾ
bool Value(TSMatrix& t, ElemType x, int i, int j);	//��Ԫ��Ԫ�صĸ�ֵ
bool GetValue(TSMatrix t, ElemType& x, int i, int j);//���ָ��λ�õ�ֵ
void DispMat(TSMatrix t);							//�����Ԫ��
void TranTat(TSMatrix t, TSMatrix& tb);				//ת��

void CreateMat(TSMatrix& t, ElemType A[M][N])		//��ϡ����󴴽���Ԫ���ʾ
{
	t.rows = M, t.cols = N, t.nums = 0;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (A[i][j] != 0)
			{
				t.data[t.nums].d = A[i][j];
				t.data[t.nums].r = i;
				t.data[t.nums].c = j;
				t.nums++;
			}
		}
	}
}

bool Value(TSMatrix& t, ElemType x, int i, int j)	//��Ԫ��Ԫ�صĸ�ֵ
{
	if (i > t.rows || j > t.cols)					//i��j����
		return false;
	int k = 0, k1;
	while (k < t.nums && i > t.data[k].r)			//���ҵ�i�е�һ������Ԫ��
		k++;
	while (k < t.nums && i == t.data[k].r && j > t.data[k].c)	//�ڵ�i�в��ҷ���Ԫ��
		k++;
	if (t.data[k].r == i && t.data[k].c == j)		//���ڸ�Ԫ�أ��޸�ֵΪx
		t.data[k].d = x;
	else											//�����������ÿһ��Ԫ��
	{
		for (k1 = t.nums; k1 > k; k1--)
		{
			t.data[k1].d = t.data[k1 - 1].d;
			t.data[k1].c = t.data[k1 - 1].c;
			t.data[k1].r = t.data[k1 - 1].r;
		}
		t.data[k].r = i;							//����Ԫ�ز��Ҹ�����һ
		t.data[k].c = j;
		t.data[k].d = x;
		t.nums++;
	}
	return true;
}

bool GetValue(TSMatrix t, ElemType& x, int i, int j)//���ָ��λ�õ�ֵ
{
	if (i > t.rows || j > t.cols)					//i��j����
		return false;
	int k = 0;
	while (k < t.nums && i > t.data[k].r)			//���ҵ�i��
		k++;
	while (k < t.nums && i == t.data[k].r && j > t.data[k].c)	//���ҵ�i�еķ���Ԫ��
		k++;
	if (i == t.data[k].r && j == t.data[k].c)		//��Ԫ��Ϊ����Ԫ��
		x = t.data[k].d;
	else											//�����Ԫ��Ϊ0
		x = 0;

	return true;
}

void DispMat(TSMatrix t)							//�����Ԫ��
{
	if (t.nums <= 0)
		return;
	cout << '\t' << "-----------------" << endl;
	for (int i = 0; i < t.nums; i++)
		cout << '\t' << t.data[i].r << '\t' << t.data[i].c << '\t' << t.data[i].d << endl;
}

void TranTat(TSMatrix t, TSMatrix& tb)				//ת��
{
	int k = 0;
	tb.cols = t.rows, tb.rows = t.cols, tb.nums = t.nums;
	if (t.nums != 0)
	{
		for (int i = 0; i < t.cols; i++)			//�����С���ѭ��
		{
			for (int j = 0; j < t.nums; j++)		//����ÿһ������Ԫ��
			{
				if (t.data[j].c == i)				//����ǵ�i�е�Ԫ�أ����tb
				{
					tb.data[k].r = t.data[j].c;
					tb.data[k].c = t.data[j].r;
					tb.data[k].d = t.data[j].d;
					k++;							//tbԪ�ظ�����һ
				}
			}
		}
	}
}