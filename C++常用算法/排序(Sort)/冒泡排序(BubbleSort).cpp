/************************************
 * 冒泡排序
 * 稳定排序，O{n} ~ O{n^2}
 * 从末尾开始，与上个元素比较并交换
 * 每轮都将能最小的元素换到首位
 *
 * https://www.tsingfun.com
 ************************************/
#include<stdio.h>
#include<stdlib.h>
/*
冒泡排序后的顺序为从小到大
*/
void Bubble_Sort(int *arr,int len)
{
	int i,j,exchange;
	for(i=0;i<len-1;i++)
		for(j=0;j<len-i-1;j++)
			if(arr[j] > arr[j+1])
			{
				exchange = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = exchange;
			}
}

int main()
{
	int num;
	printf("请输入排序的元素的个数：");
	scanf("%d",&num);

	int i;
	int *arr = (int *)malloc(num*sizeof(int));
	printf("请依次输入这%d个元素（必须为整数）：",num);
	for(i=0;i<num;i++)
		scanf("%d",arr+i);

	printf("冒泡排序后的顺序：");
	Bubble_Sort(arr,num);
	for(i=0;i<num;i++)
		printf("%d ",arr[i]);
	printf("\n");

	free(arr);
	arr = 0;
	return 0;
}