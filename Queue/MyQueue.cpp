#include<iostream>
using namespace std;

class E_Queue
{
private:
	int queue[100];
	int front,rear;
public:
	void initialize_queue()
	{
		front=rear=0;
	}
	bool Is_Empty()
	{
		if(front==rear)
			return true;
		else
			return false;
	}
	bool Is_Full()
	{
		if(((rear+1)%100)==front)
			return true;
		else
			return false;
	}
	void add_queue(int data)
	{
		if(Is_Full())
			cout<<"The queue is full!"<<endl;
		else
		{
			rear++;
			queue[rear]=data;
		}
	}
	int pop_queue()
	{
		if(Is_Empty())
			cout<<"The queue is empty!"<<endl;
		else
		{
			front=(front+1)%100;
			return queue[front];
		}
	}
	int queue_size()
	{
		return ((100+(rear-front))%100);
	}
};

int main()
{
	E_Queue test;
	int sub;
	test.initialize_queue();
	cout<<"The queue's size: "<<test.queue_size()<<endl;
	do
	{
		cin>>sub;
		test.add_queue(sub);
	}while(sub!=0);
	while(!test.Is_Empty())
	{
		cout<<test.pop_queue()<<" "<<endl;
	}
	cout<<endl;
	return 0;
}