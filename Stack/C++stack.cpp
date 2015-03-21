#include<iostream>
using namespace std;
class Stack
{
private:
	int data_count;
	int *member_stack;
	int stack_sum;
public:
	void Stack_Creat(int n)
	{
		member_stack=(int*)malloc(n*sizeof(int));
		data_count=-1;
		stack_sum=n-1;
	}
	bool IsFull()
	{
		if(data_count==stack_sum)
			return true;
		else
			return false;
	}
	void Stack_Add(int item)
	{
		if(IsFull())
			return;
		else
			member_stack[++data_count]=item;
	}
	bool IsEmpty()
	{
		if(data_count==-1)
			return true;
		else
			return false;
	}
	void Stack_delete()
	{
		if(IsEmpty())
			return;
		else
		{
			cout<<member_stack[data_count--]<<endl;
		}
	}
};
int main()
{
	Stack test_stack;
	int value,test_data=0;
	cin>>value;
	test_stack.Stack_Creat(value);
	for(;test_data<value;test_data++)
	{
		test_stack.Stack_Add(test_data+1);
	}
	test_data--;
	for(;test_data>=0;test_data--)
	{
		test_stack.Stack_delete();
	}
	return 0;
}