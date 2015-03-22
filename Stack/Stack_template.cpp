//该程序实现了类模板栈
#include<iostream>
using namespace std;

template<typename T>
class Stack
{
private:
	int data_count;
	//该栈使用链表对数据进行存储
	struct data_node{
		T coredata;
		data_node* pre;
		data_node(const T& cdo):coredata(cdo),pre(0){}
	};
	data_node* cur_node;
public:
	Stack();
	bool push(const T& item);
	bool pop();
	const T& get_top() const;
	int size() const;
	bool isEmpty() const;
	bool isFull() const;
	~Stack();
};

int main()
{
	Stack<int> test_stack;
	test_stack.push(33);
	test_stack.push(55);
	test_stack.push(66);
	cout<<test_stack.size()<<endl;
	cout<<test_stack.get_top()<<endl;
	test_stack.pop();
	cout<<test_stack.get_top()<<endl;
	return 0;
}

template<typename T>
Stack<T>::Stack():data_count(0),cur_node(0){}

template<typename T>
Stack<T>::~Stack(){
	data_node* temp;
	while(cur_node){
		temp=cur_node->pre;
		delete cur_node;
		cur_node=temp;
	}
}

template<typename T>
bool Stack<T>::isEmpty() const {
	if(cur_node)return false;
	else return true;
}

template<typename T>
bool Stack<T>::isFull() const {
	return false;
}

template<typename T>
bool Stack<T>::push(const T& item){
	if(isFull()){
		cout<<"The stack is full."<<endl;
		return false;
	}
	if(!cur_node){
		cur_node=new data_node(item);
		++data_count;
		return true;
	}
	data_node* newnode=new data_node(item);
	newnode->pre=cur_node;
	cur_node=newnode;
	newnode=0;
	++data_count;
	return true;
}

template<typename T>
const T& Stack<T>::get_top() const {
	if(isEmpty()){
		cout<<"The stack is empty."<<endl;
		return T();
	}
	return cur_node->coredata;
}

template<typename T>
bool Stack<T>::pop(){
	if(isEmpty()){
		cout<<"The stack is empty."<<endl;
		return false;
	}
	data_node* temp=cur_node->pre;
	delete cur_node;
	cur_node=temp;
	temp=0;
	--data_count;
	return true;
}

template<typename T>
int Stack<T>::size() const{
	return data_count;
}