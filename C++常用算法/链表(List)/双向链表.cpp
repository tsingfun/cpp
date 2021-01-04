#include<iostream>
#include<windows.h>
using namespace std;
struct node
{
	int data;
	node *next;
	node *pre;
};
class two_way_list
{
	node *first;
public:
	two_way_list();
	~two_way_list(){};
	int creat();
	int clean();
	int show();
	int add(int number);
	int dele(int number);
};
two_way_list::two_way_list()
{
	first=0;
}
int two_way_list::creat()
{
	int number;
	node *tail,*temp;
	cout<<"please input"<<endl;
	cin>>number;
	while(number!=-1)
	{
		temp=new node;
		temp->data=number;
		temp->next=0;
		if(!first)
		{
			first=tail=temp;
			first->pre=0;
		}
		else
		{
			tail->next=temp;
			temp->pre=tail;
			tail=temp;
		}
		cin>>number;
	}
	return 1;
}
int two_way_list::show()
{
	node *tail,*pror;
	tail=first;
	if(!first)
	{
		cout<<"it's hollow!"<<endl;
		return 0;
	}
	while(tail!=0)
	{
		cout<<tail->data<<"  ";
		tail=tail->next;
	}
	cout<<endl;
	tail=first;
	while(tail->next!=0)
	{
		tail=tail->next;
	}
	pror=tail;
	while(pror!=0)
	{
		cout<<pror->data<<"  ";
		pror=pror->pre;
	}
	cout<<endl;
	return 1;
}
int two_way_list::clean()
{
	node *tail,*de;
	tail=first;
	if(!first)
	{
		cout<<"it's hollow!"<<endl;
		return 0;
	}
	else
	{
		while(tail)
		{
			de=tail;
			tail=tail->next;
			delete de;
		}
		first=0;
	}
	return 1;
}
int two_way_list::add(int number)
{
	node *tail,*temp;
	temp=new node;
	temp->data=number;
	if(!first)
	{
		temp->next=0;
		first=temp;
		first->pre=0;
		return 1;
	}
	else
	{
		tail=first;
		while(tail->next->data<number&&tail->next!=0)
		{
			tail=tail->next;
			if(tail->next==0&&tail->data<number)
			{
				temp->next=0;
				tail->next=temp;
				temp->pre=tail;
				return 1;
			}
		}
		temp->next=tail->next;
		tail->next->pre=temp;
		temp->pre=tail;
		tail->next=temp;
		return 1;
	}
}
int two_way_list::dele(int number)
{
	node *tail,*de;
	if(!first)
	{
		cout<<"it's hollow"<<endl;
		return 0;
	}
	tail=first;
	if(first->data==number)
	{
		de=first;
		first=first->next;
		delete de;
		first->pre=0;
		return 1;
	}
	while(tail->next->data!=number)
	{
		tail=tail->next;
		if(!tail)
		{
			cout<<"not exist the number"<<endl;
			return 0;
		}
	}
	de=tail->next;
	tail->next->next->pre=tail;
	tail->next=tail->next->next;
	delete de;
	return 1;
}
int main()
{
	two_way_list list;
	list.creat();
	list.show();
	//list.clean();
	//list.show();
	list.add(6);
	list.show();
	list.dele(6);
	list.show();
	system("pause");
	return 0;
}
