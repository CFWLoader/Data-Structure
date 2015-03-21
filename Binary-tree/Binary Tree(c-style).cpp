#include<iostream>
#include<cstdlib>
using namespace std;

typedef struct Binary_Tree
{
	char key;
	struct Binary_Tree *lchild,*rchild;
}bintree;

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

void bin_tree_create(bintree *ptr)                           /*简化掉的bin_tree_create_for_test函数，没有了depth记录深度*/
{
	scanf("%c",&ptr->key);
//	fflush(stdin);                                            /*该代码用于清除流中的换行符，以免被递归函数赋予子树的数据区中*/
	ptr->lchild=NULL;
	ptr->rchild=NULL;
	if(ptr->key=='.')
		return;
	else
	{
//		ptr->lchild=(bintree*)malloc(sizeof(bintree));
//		ptr->rchild=(bintree*)malloc(sizeof(bintree));
		ptr->lchild=new bintree;
		ptr->rchild=new bintree;
		bin_tree_create(ptr->lchild);
		bin_tree_create(ptr->rchild);
	}
	if(ptr)
	{
		if(ptr->lchild->key=='.')
			ptr->lchild=NULL;
		if(ptr->rchild->key=='.')
			ptr->rchild=NULL;
	}
}

/*void Create_the_tree_adv(bintree *ptr)
{
	char temp;
	cin>>temp;
	if(temp=='.')ptr=NULL;
	else
	{
		if(ptr==NULL)ptr=new bintree;
		ptr->key=temp;
		Create_the_tree(ptr->lchild);
		Create_the_tree(ptr->rchild);
	}
}*/

void preorder(bintree *ptr)
{
	if(ptr)
	{
/*		cout<<ptr<<endl;
		cout<<ptr->lchild<<" "<<ptr->rchild<<endl;*/
		cout<<ptr->key<<endl;
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}

void inorder(bintree *ptr)
{
	if(ptr)
	{
		inorder(ptr->lchild);
/*		cout<<ptr<<endl;
		cout<<ptr->lchild<<" "<<ptr->rchild<<endl;*/
		cout<<ptr->key<<endl;
		inorder(ptr->rchild);
	}
}

int main()
{
	bintree *root=new bintree,*ptr;
	ptr=root;
	Create_the_tree(ptr);
//	bin_tree_create(ptr);
	ptr=root;
	preorder(ptr);
	ptr=root;
	inorder(ptr);
	return 0;
}
