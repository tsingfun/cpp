#include<iostream>
#include<windows.h>
using namespace std;
struct node
{
	int data;
	node *next;
};
class single_list
{
	node *first;
public:
	single_list();
	~single_list(){};
	void creat();
	int show();
	int clean();
	int add(int number);
	int dele(int number);
	int search(int number);
	node *nixu(node *p);
	node *gettail()
	{
		node *tail;
		tail=first;
		while(tail->next!=0)
		{
			tail=tail->next;
		}
		return tail;
	}
	friend int link(single_list &l,single_list &k);
};
single_list::single_list()
{
	first=0;
}
void single_list::creat()
{
	int number;
	node *tail,*temp;
	cout<<"input"<<endl;
	cin>>number;
	while(number!=-1)
	{
		temp=new node;
		temp->data=number;
		temp->next=0;
		if(!first)
		{
			first=tail=temp;
		}
		else
		{
		tail->next=temp;
		tail=temp;
		}
		cin>>number;
	}
}
node * single_list::nixu(node *p)
{
	node *tail;
	if(p==first)
	{
		cout<<p->data<<" ";
		return NULL;
	}
	tail=first;
	while(tail->next!=p)
	{
		tail=tail->next;
	}
	cout<<p->data<<" ";
	nixu(tail);
}
int single_list::clean()
{
	node *tail,*de;
	tail=first;
	if(!first)
	{
		cout<<"it's hollow"<<endl;
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
int single_list::show()
{
	node *tail;
	tail=first;
	if(!tail)
	{
		cout<<"it's hollow"<<endl;
		return 0;
	}
	while(tail)
	{
		cout<<tail->data<<"  ";
		tail=tail->next;
	}
	cout<<endl;
	return 1;
}
int single_list::add(int number)
{
	node *tail,*temp;
	temp=new node;
	temp->data=number;
	if(!first)
	{
		temp->next=0;
		first=temp;
		return 1;
	}
	else
	{
		tail=first;
		if(tail->data>number)
		{
             temp->next=tail;
             first=temp;
             return 1;
         }
		while(tail->next!=0&&tail->next->data<number)
		{
			tail=tail->next;
			if(tail->next==0&&tail->data<number)
			{
				temp->next=0;
				tail->next=temp;
				return 1;
			}
		}
		temp->next=tail->next;
		tail->next=temp;
		return 1;
	}
}
int single_list::dele(int number)
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
	tail->next=tail->next->next;
	delete de;
	return 1;
}
int single_list::search(int number)
{
	node *tail;
	if(!first)
	{
		cout<<"it's hollow"<<endl;
		return 0;
	}
	tail=first;
	while(tail->data!=number)
	{
		tail=tail->next;
		if(!tail)
		{
			cout<<"not exist the number"<<endl;
			return 0;
		}
	}
}
int link(single_list &l,single_list &k)
{
	node *tail,*de;
	if(k.first==0||l.first==0)
	{
		cout<<"buxuxainglian,yigeweikongde!"<<endl;
		return 0;
	}
	tail=l.first;
	while(tail->next)
	{
		tail=tail->next;
	}
	de=tail->next;
	tail->next=k.first;
	delete de;
	return 1;
}
int main()
{
    single_list L;
	node *temp;
    L.creat();
    L.show();
	temp=L.gettail();
	L.nixu(temp);
    system("pause");
	return 0;
}
