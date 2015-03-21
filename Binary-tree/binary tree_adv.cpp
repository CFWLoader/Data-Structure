#include<iostream>
#include<cstdlib>
using namespace std;

typedef struct Binary_Tree
{
	char key;
	struct Binary_Tree *lchild,*rchild;
}bintree,*treenode;

class My_bintree
{
private:
	treenode root;

	void preorder_assist(bintree *ptr)
	{
		if(ptr)
		{
			cout<<ptr->key<<endl;
			preorder_assist(ptr->lchild);
			preorder_assist(ptr->rchild);
		}
	}

	void establish_the_tree_assist(treenode &ptr)
	{
		char temp;
		cin>>temp;
		if(temp=='.')return;
		else
		{
			ptr=new bintree;
			ptr->key=temp;
			ptr->lchild=ptr->rchild=0;
			establish_the_tree_assist(ptr->lchild);
			establish_the_tree_assist(ptr->rchild);
		}
	}

public:
	My_bintree::My_bintree()
	{
		root=0;
	}

	void establish_the_tree()
	{
		establish_the_tree_assist(root);
	}

	void preorder()
	{
		bintree *ptr=root;
		preorder_assist(ptr);
	}
};

int main()
{
	My_bintree test;
	test.establish_the_tree();
	test.preorder();
	return 0;
}
