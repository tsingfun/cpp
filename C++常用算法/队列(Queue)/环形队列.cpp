#include<iostream>
#include<windows.h>
using namespace std;
class queue
{
	int maxsize,tag;
	int *st;
	int *front;
	int *rear;
public:
	queue(int size);
	~queue();
	int clear();
	int enqueue(const int number);
	int dequeue(int &number);
	int getfront(int &number);
	int isfull();
	int isempty();
	void show();
};
queue::queue(int size)
{
	maxsize=size;
	st=new int[maxsize];
	front=rear=st;
	tag=0;
}
queue::~queue()
{
	clear();
}
int queue::clear()
{
	if(maxsize<=0)
	{
		cout<<"wrong!"<<endl;
		return 0;
	}
	if(maxsize==1)
	{
		delete st;
	}
	else
	{
		delete []st;
	}
	tag=0;
	return 1;
}
int queue::enqueue(const int number)
{
    int *temp;
	*rear=number;
	rear=st+((rear-st+1)%maxsize);
	if(rear==front)
	{
		tag=1;
		return 1;
	}
	tag=2;
	return 1;
}
int queue::dequeue(int &number)
{
	number=*front;
	front=st+((front-st+1)%maxsize);
	if(front==rear)
	{
		tag=0;
		return 0;
	}
	tag=2;
	return 1;
}
int queue::getfront(int &number)
{
	number=*front;
	return 1;
}
int queue::isfull()
{
	if(tag==1)
	{
		return 1;
	}
	return 0;
}
int queue::isempty()
{
	if(tag==0)
	{
		return 1;
	}
	return 0;
}
void queue::show()
{
	if(isfull()==1)
	{
		cout<<"full"<<endl;
	}
	if(isempty()==1)
	{
		cout<<"empty"<<endl;
	}
	if(tag==2)
	{
		cout<<"isn't empty and isn't full"<<endl;
	}
}
int main()
{
	queue q(10);
	int i,j;
	for(i=0;i<10;i++)
	{
		q.enqueue(i);
	}
	q.show();
	q.dequeue(j);
	cout<<j<<" ";
	q.dequeue(j);
	cout<<j<<" ";
	q.show();
	q.enqueue(10);
	q.enqueue(11);
	q.show();
	for(i=0;i<10;i++)
	{
		q.dequeue(j);
		cout<<j<<" ";
	}
	q.show();
	cout<<endl;
	system("pause");
	return 0;
}
