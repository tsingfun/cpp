#include<iostream>
#include<Windows.h>
using namespace std;
struct node
{
	node():left(NULL),right(NULL){}
	node *left,*right;
	int data;
};
class searchtree
{
	node *root;
public:
	searchtree(){root=NULL;}
	~searchtree(){dele(root);}
	void creat(node *&root);
	void dele(node *root);
	void preorder(node *root);
	int tell_search(node *root);
	node *findmin(node *root);
	node *search(node *root,int key);
	node *insert(node *&root,int key);
	node *remove(node *&rot,int key);
};
void searchtree::creat(node *&root)
{
	int number;
	cin>>number;
	if(number==-1)
		root=NULL;
	else
	{
		root=new node;
		root->data=number;
		creat(root->left);
		creat(root->right);
	}
}
int searchtree::tell_search(node *root)
{
	if(root!=NULL)
	{
		if(root->left==NULL&&root->right!=NULL&&root->data>root->right->data)
			return 0;
		if(root->left!=NULL&&root->right==NULL&&root->data<root->left->data)
			return 0;
		if(root->left!=NULL&&root->right!=NULL&&(root->data>root->right->data||root->left->data>root->data))
			return 0;
		tell_search(root->left);
		tell_search(root->right);
	}
	return 1;
}
void searchtree::dele(node *root)
{
	if(root!=NULL)
	{
		dele(root->left);
		dele(root->right);
		delete root;
		root=NULL;
	}
}
void searchtree::preorder(node *root) 
{
	if(root!=NULL)
	{
		cout<<root->data<<" ";
		preorder(root->left);
		preorder(root->right);
	}
}
node *searchtree::search(node *root,int key)
{
	node *current=root;
	while((NULL!=root)&&(key!=current->data))
	{
		if(key<current->data)
			current=search(current->left,key);
		else
			current=search(current->right,key);
	}
	return current;
}
node *searchtree::insert(node *&root,int key)
{
	if(root==NULL)
	{
		root=new node();
		root->data=key;
	}
	else
	{
		if(key>root->data)
			root->right=insert(root->right,key);
		if(key<root->data)
			root->left=insert(root->left,key);
	}
	return root;
}
node *searchtree::findmin(node *root)
{
	if(root==NULL)
		cout<<"It can't be found"<<endl;
	else
	{
		while(root->left!=NULL)
		{
			root=root->left;
		}
	}
	return root;
}
node *searchtree::remove(node *&root,int key)
{
	node *tmp;
	if(root==NULL)
		cout<<"It can't be found!"<<endl;
	else
	{
		if(key<root->data)
			root->left=remove(root->left,key);
		else if(key>root->data)
			root=remove(root->right,key);
		else
		{
			if(root->left&&root->right)
			{
				tmp=findmin(root->right);
				root->data=tmp->data;
				root->right=remove(root->right,root->data);
			}
			else
			{
				tmp=root;
				if(root->left==NULL)
					root=root->right;
				else if(root->right==NULL)
					root=root->left;
				delete tmp;
			}
		}
		return root;
	}
}
int main()
{
	searchtree tree;
	node *no;
	tree.creat(no);
	while(tree.tell_search(no)!=1)
	{
		cout<<"It's not searchtree!input again!"<<endl;
		tree.creat(no);
	}	
	tree.preorder(no);
	cout<<endl;
	cout<<tree.search(no,99)->data<<endl;
	tree.remove(no,99);
	tree.preorder(no);
	cout<<endl;
	tree.insert(no,99);
	tree.preorder(no);
	cout<<endl;
	system("pause");
	return 0;
}
