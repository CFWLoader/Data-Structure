// Queue_template_test.cpp : 定义控制台应用程序的入口点。
//
#include"stdafx.h"
#include<iostream>
using namespace std;


template<typename _T>
class myqueue
{
private:
	typedef struct queue_node
	{
		_T CLI;
		struct queue_node* next;
		queue_node()
		{
			next=0;
		}
	}qnode;
	qnode* front;
	qnode* rear;
	int counter;
public:
	myqueue();
	bool Is_Empty();
	bool Is_Full();
	bool En_queue(_T wait);
	int get_the_queue_length();
	_T Get_queue();
};

int main()
{
	myqueue<char> mq;
	char data='a';
/*	while(data!='z'+1)
	{
		mq.En_queue(data);
		data++;
	}
	while(!mq.Is_Empty())cout<<mq.Get_queue()<<" ";
	cout<<endl;*/
	cout<<mq.Get_queue()<<endl;
	mq.En_queue(data+1);
	cout<<mq.Get_queue()<<endl;
	system("PAUSE");
	return 0;
}

template<typename _T>
myqueue<_T>::myqueue()
{
	front=0;
	rear=0;
	counter=0;
}

template<typename _T>
bool myqueue<_T>::Is_Empty()
{
	return counter==0;
}

template<typename _T>
bool myqueue<_T>::Is_Full()
{
	return false;
}


template<typename _T>
bool myqueue<_T>::En_queue(_T wait)
{
	if(!rear)
	{
		rear=new qnode;
/*		rear->CLI.arrive_time=wait.arrive_time;
		rear->CLI.durtime=wait.durtime;
		rear->CLI.interval=wait.interval;
		rear->CLI.leave_time=wait.leave_time;*/
		rear->CLI=wait;
		front=rear;
		counter++;
		return true;
	}
	rear->next=new qnode;
	rear=rear->next;
/*	rear->CLI.arrive_time=wait.arrive_time;
	rear->CLI.durtime=wait.durtime;
	rear->CLI.interval=wait.interval;
	rear->CLI.leave_time=wait.leave_time;*/
	rear->CLI=wait;
	counter++;
	return true;
}

template<typename _T>
_T myqueue<_T>::Get_queue()
{
	if(Is_Empty())
	{
		throw ("The stack is empty!");
	}
	qnode* temprec=front;
	_T temp=front->CLI;
	if(!(front==rear))
	{
		front=front->next;
		delete temprec;
		temprec=0;
	}
	counter--;
	return temp;
}


template<typename _T>
int myqueue<_T>::get_the_queue_length()
{
	return counter;
}