#pragma once
#include <iostream>
using namespace std;
#define MaxSize 30							//稀疏矩阵中非零元素最多的个数
#define M 10
#define N 9
typedef int ElemType;
typedef struct
{
	int r;						//行号
	int c;						//列号
	ElemType d;					//元素值
}TupNode;						//三元组类型

typedef struct
{
	int rows;					//行数
	int cols;					//列数
	int nums;					//非零元素个数
	TupNode data[MaxSize];
}TSMatrix;						//三元组顺序表类型

void CreateMat(TSMatrix& t, ElemType A[M][N]);		//用稀疏矩阵创建三元组表示
bool Value(TSMatrix& t, ElemType x, int i, int j);	//三元组元素的赋值
bool GetValue(TSMatrix t, ElemType& x, int i, int j);//获得指定位置的值
void DispMat(TSMatrix t);							//输出三元组
void TranTat(TSMatrix t, TSMatrix& tb);				//转置

void CreateMat(TSMatrix& t, ElemType A[M][N])		//用稀疏矩阵创建三元组表示
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

bool Value(TSMatrix& t, ElemType x, int i, int j)	//三元组元素的赋值
{
	if (i > t.rows || j > t.cols)					//i，j超界
		return false;
	int k = 0, k1;
	while (k < t.nums && i > t.data[k].r)			//查找第i行第一个非零元素
		k++;
	while (k < t.nums && i == t.data[k].r && j > t.data[k].c)	//在第i行查找非零元素
		k++;
	if (t.data[k].r == i && t.data[k].c == j)		//存在该元素，修改值为x
		t.data[k].d = x;
	else											//不存在则后移每一个元素
	{
		for (k1 = t.nums; k1 > k; k1--)
		{
			t.data[k1].d = t.data[k1 - 1].d;
			t.data[k1].c = t.data[k1 - 1].c;
			t.data[k1].r = t.data[k1 - 1].r;
		}
		t.data[k].r = i;							//插入元素并且个数加一
		t.data[k].c = j;
		t.data[k].d = x;
		t.nums++;
	}
	return true;
}

bool GetValue(TSMatrix t, ElemType& x, int i, int j)//获得指定位置的值
{
	if (i > t.rows || j > t.cols)					//i，j超界
		return false;
	int k = 0;
	while (k < t.nums && i > t.data[k].r)			//查找第i行
		k++;
	while (k < t.nums && i == t.data[k].r && j > t.data[k].c)	//查找第i行的非零元素
		k++;
	if (i == t.data[k].r && j == t.data[k].c)		//该元素为非零元素
		x = t.data[k].d;
	else											//否则该元素为0
		x = 0;

	return true;
}

void DispMat(TSMatrix t)							//输出三元组
{
	if (t.nums <= 0)
		return;
	cout << '\t' << "-----------------" << endl;
	for (int i = 0; i < t.nums; i++)
		cout << '\t' << t.data[i].r << '\t' << t.data[i].c << '\t' << t.data[i].d << endl;
}

void TranTat(TSMatrix t, TSMatrix& tb)				//转置
{
	int k = 0;
	tb.cols = t.rows, tb.rows = t.cols, tb.nums = t.nums;
	if (t.nums != 0)
	{
		for (int i = 0; i < t.cols; i++)			//按“列”来循环
		{
			for (int j = 0; j < t.nums; j++)		//遍历每一个非零元素
			{
				if (t.data[j].c == i)				//如果是第i列的元素，存进tb
				{
					tb.data[k].r = t.data[j].c;
					tb.data[k].c = t.data[j].r;
					tb.data[k].d = t.data[j].d;
					k++;							//tb元素个数加一
				}
			}
		}
	}
}