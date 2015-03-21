#include<iostream>
#include<ctime>
using namespace std;

typedef struct link_list_node
{
	int key;
	struct link_list_node* next;
	link_list_node()
	{
		key=-256;
		next=0;
	}
}node;

class My_link_list
{
private:
	node* head;
	int length;
public:
	My_link_list()
	{
		head=0;
		length=0;
	}

	My_link_list(int n)
	{
		length=n;
		head=new node;
		node* ptr=head;
		srand((unsigned)time(0));
		head->key=rand()%201;
		for(int i=1;i<length;i++)
		{
			ptr->next=new node;
			ptr=ptr->next;
			ptr->key=rand()%201;
		}
	}

	order_the_list()                                 //遍历链表
	{
		node* ptr=head;
		while(ptr)
		{
			cout<<ptr->key<<" ";
			ptr=ptr->next;
		}
		cout<<endl;
	}

	int &operator[](int i);                          //将[]重载，使链表可以像数组一样使用；该函数只支持数据域的显示及修改。后来加入可以使链表增长的算法。

	~My_link_list()
	{
		node* temp;
		while(head)
		{
			temp=head;
			head=head->next;
			delete temp;
		}
		head=0,temp=0;
	}
};

int &My_link_list::operator[](int i)
{
	if(i<0||i>length-1)                                //判断是否在数组之内，如果没有则在链表最尾端加入新元素至链表长度能容下位置为i的元素，规则按结构体构造函数运算
	{
		node *ptr=head;
		while(ptr->next)ptr=ptr->next;
		while(length<i+1)                                //伸长链表
		{
			ptr->next=new node;
			ptr=ptr->next;
			length++;
		}
		return ptr->key;
	}
	else
	{
		node *ptr=head;
		for(int k=0;k<i;k++)
		{
			ptr=ptr->next;
		}
		return ptr->key;
	}
}

int main()
{
	My_link_list test(7);
	test.order_the_list();
	test[15]=10;
	test.order_the_list();
	cout<<test[7]<<endl;
	return 0;
}