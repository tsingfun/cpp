#include<iostream>
#include<windows.h>
using namespace std;
class int_Arr
{
	int *std;
	int maxsize;
public:
	int_Arr(int size);
	~int_Arr();
	int &operator[](int i);
	int length(){return maxsize;}
};
int_Arr::int_Arr(int size)
{
	maxsize=size;
	std=new int[maxsize];
}
int_Arr::~int_Arr()
{
	delete []std;
}
int &int_Arr::operator[](int i)
{
	return std[i];
}
int SeqSearch(int_Arr &arr,int key)
{
	int i;
	for(i=0;i<arr.length()&&arr[i]!=key;i++){}
	if(i==arr.length())
		return 0;
	else
		return 1;
}
int BinSearch(int_Arr &R,int k) 
{  
	int i,mid,l=1,r=R.length();
	while(l<=r)
	{
		mid=(l+r)/2;
		if (R[mid]==k) 
			return 1;
		else if (R[mid]>k)
			r=mid-1;
		else l=mid+1;
	}
	return 0;;
}
int F(int_Arr &R,int left,int right)
{
	int temp;
	while(!(left>=right))
	{
		if(R[left]>0&&R[right]<0)
		{
			temp=R[left];
			R[left]=R[right];
			R[right]=temp;
			left++;
			right--;
		}
		else
		{
			if(R[left]<0)
			{
				left++;
			}
			if(R[right]>0)
				right--;
		}
	}
	return 1;
}
int main()
{
	int_Arr a(4);
	for(int i=0;i<10;i++)
		cin>>a[i];
	F(a,0,9);
	for(int i=0;i<10;i++)
		cout<<a[i]<<" ";
	cout<<endl;
	system("pause");
	return 0;
}
