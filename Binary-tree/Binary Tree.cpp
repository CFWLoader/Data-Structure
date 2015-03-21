#include<iostream>
#include<cstdlib>
using namespace std;

typedef struct Binary_Tree
{
	char key;
	struct Binary_Tree *lchild,*rchild;
}bintree;

class My_bintree
{
private:
	bintree *root;
public:
	bintree *this_ptr;
	My_bintree::My_bintree()
	{
		root=0;
	}
	My_bintree::My_bintree(int a)
	{
//		root=new bintree;
		root=(bintree*)malloc(sizeof(bintree));
		root->lchild=root->rchild=0;
	}
	void show()
	{
		cout<<root<<endl;
		cout<<root->lchild<<endl;
	}
	void point_to_the_root(bintree *ptr)
	{
		ptr=root;
	}
/*	void Create_bintree(bintree *ptr)
	{
		char temp;
		cin>>temp;
		if(temp=='.')
		{
			if(ptr==root)
			{
				delete root;
				root=0;
			}
			ptr=0;
		}
		else
		{
//			ptr=new bintree;
			ptr=(bintree*)malloc(sizeof(bintree));
//			if(root==0)root=this_ptr;
			cout<<ptr<<endl;
			ptr->key=temp;
			ptr->lchild=ptr->rchild=0;
			Create_bintree(ptr->lchild);
			Create_bintree(ptr->rchild);
		}
	}*/

	void Create_the_tree(bintree *ptr)
	{
		cin>>ptr->key;
		ptr->lchild=0;
		ptr->rchild=0;
		if(ptr->key=='.')return;
		else
		{
	//		ptr=(bintree*)malloc(sizeof(bintree));
	//		cout<<ptr<<"  "<<ptr->key<<endl;
			ptr->lchild=new bintree;
			ptr->rchild=new bintree;
			Create_the_tree(ptr->lchild);
			Create_the_tree(ptr->rchild);
		}
		if(ptr)
		{
			if(ptr->lchild->key=='.')
			{
				delete ptr->lchild;
				ptr->lchild=0;
			}
			if(ptr->rchild->key=='.')
			{
				delete ptr->rchild;
				ptr->rchild=0;
			}
		}
	}

	void preorder(bintree *ptr)
	{
		if(ptr)
		{
			cout<<ptr<<endl;
			cout<<ptr->key<<endl;
			preorder(ptr->lchild);
			preorder(ptr->rchild);
		}
	}
};

int main()
{
	My_bintree test(1);
//	test.show();
//	test.Create_bintree(test.this_ptr);
	test.point_to_the_root(test.this_ptr);
//	test.Create_bintree(test.this_ptr);
	test.Create_the_tree(test.this_ptr);
	test.point_to_the_root(test.this_ptr);
	test.preorder(test.this_ptr);
	test.show();
	return 0;
}
