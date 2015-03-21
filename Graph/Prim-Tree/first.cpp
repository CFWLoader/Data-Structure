#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
using namespace std;

typedef struct Graph_Node
{
	int node_info;
	struct Graph_Node* next;
	Graph_Node()
	{
		node_info=-1;
		next=0;
	}
}GN;

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

class Graph
{
private:
	bool** link_array;
	GN* link_list;
	int node_counter;
	bool* visited;
	void Depth_First_Search(int start_node);
	void Depth_First_Search_L(int start_node);
public:
	Graph();
	Graph(int reference);
	bool Establish_the_link_array(int nc);
	bool Change_the_array_to_list();
	bool Show_the_link_array();
	bool Show_the_link_list();
	bool DFS_Trigger(int start_node);
	bool DFS_Trigger_List_Ver(int start_node);
	bool Save_the_link_array_to_file();
	bool Save_the_link_list_to_file();
	bool Read_the_link_array_from_file();
	bool Read_the_link_list_from_file();
	bool BFS_Trigger(int start_node);
	bool BFS_Trigger_List_Ver(int start_node);
};

int main()
{
	Graph G;
//	G.Establish_the_link_array(10);
//	G.Show_the_link_array();
//	G.Save_the_link_array_to_file();
//	G.Read_the_link_array_from_file();
//	G.Show_the_link_array();
//	G.Show_the_link_array();
//	G.Change_the_array_to_list();
//	G.Show_the_link_list();
//	G.Save_the_link_list_to_file();
	G.Read_the_link_list_from_file();
	G.Show_the_link_list();
//	G.BFS_Trigger(0);
	G.BFS_Trigger_List_Ver(9);
//	G.DFS_Trigger(0);
//	G.DFS_Trigger_List_Ver(0);
	return 0;
}

Graph::Graph()
{
	link_list=0;
	link_array=0;
	visited=0;
	node_counter=0;
}

Graph::Graph(int reference)
{
	node_counter=reference;
	link_array=0;
	link_list=0;
	visited=0;
}

bool Graph::Establish_the_link_array(int nc)
{
	if(nc<1)return false;
	if(node_counter!=nc)node_counter=nc;
	link_array=new bool*[node_counter];
	srand(time(0));
	for (int i = 0; i < node_counter; ++i)
	{
		link_array[i]=new bool[node_counter];
	}
	for (i = 0; i < node_counter; ++i)
	{
		for (int j = 0; j < node_counter; ++j)
		{
			if(j==i)
			{
				link_array[i][j]=false;
				continue;
			}
			link_array[i][j]=rand()%2;
		}
	}
	return true;
}

bool Graph::Change_the_array_to_list()
{
	if(link_array==0)
	{
		cout<<"THe link_array hasn't been established."<<endl;
		return false;
	}
	link_list=new GN[node_counter];
	for (int i = 0; i < node_counter; ++i)
	{
		GN* temp=&link_list[i];
		temp->node_info=i;
		for (int j = 0; j < node_counter; ++j)
		{
			if(link_array[i][j]==true)
			{
				temp->next=new GN;
				temp=temp->next;
				temp->node_info=j;
			}
		}
	}
	for (i = 0; i < node_counter; ++i)
	{
		delete[] link_array[i];
	}
	link_array=0;
	return true;
}

bool Graph::Show_the_link_array()
{
	if(link_array==0)
	{
		cout<<"THe link_array hasn't been established."<<endl;
		return false;
	}
	cout<<"   ";
	for (int i = 0; i < node_counter; ++i)
	{
		cout.width(3);
		cout<<i;
	}
	cout<<endl;
	for (i = 0; i < node_counter; ++i)
	{
		cout.width(3);
		cout<<i;
		for (int j = 0; j < node_counter; ++j)
		{
			cout.width(3);
			cout<<link_array[i][j];
		}
		cout<<endl;
	}
	return true;
}

bool Graph::Show_the_link_list()
{
	if(link_list==0)
	{
		cout<<"The link_list hasn't been established."<<endl;
		return false;
	}
	for (int i = 0; i < node_counter; ++i)
	{
		GN* viewer=&link_list[i];
		while(viewer!=0)
		{
			cout<<viewer->node_info<<" ";
			viewer=viewer->next;
		}
		cout<<endl;
	}
	return true;
}

bool Graph::DFS_Trigger(int start_node)
{
	if(start_node<0||start_node>=node_counter)
	{
		cout<<"Invalid Node."<<endl;
		return false;
	}
	visited=new bool[node_counter];
	for(int i=0;i<node_counter;i++)visited[i]=false;
	cout<<"The result of DFS:"<<endl;
	Depth_First_Search(start_node);
	cout<<endl;
	return true;
}

void Graph::Depth_First_Search(int start_node)
{
	if(!visited[start_node])
	{
		cout<<start_node<<" ";
		visited[start_node]=true;
	}
	for(int i=0;i<node_counter;i++)
	{
		if(link_array[start_node][i]==true&&visited[i]==false)
			Depth_First_Search(i);
	}
}

bool Graph::DFS_Trigger_List_Ver(int start_node)
{
	if(start_node<0||start_node>=node_counter)
	{
		cout<<"Invalid Node."<<endl;
		return false;
	}
	visited=new bool[node_counter];
	for(int i=0;i<node_counter;i++)visited[i]=false;
	cout<<"The result of DFS:"<<endl;
	Depth_First_Search_L(start_node);
	cout<<endl;
	return true;
}

void Graph::Depth_First_Search_L(int start_node)
{
	if(!visited[start_node])
	{
		cout<<start_node<<" ";
		visited[start_node]=true;
	}
	GN* Orderer=&link_list[start_node];
	while(Orderer)
	{
		if(Orderer->next&&!visited[Orderer->next->node_info])
			Depth_First_Search_L(Orderer->next->node_info);
		Orderer=Orderer->next;
	}
}

bool Graph::Save_the_link_array_to_file()
{
	ofstream out;
	out.open("Link_Array.txt",ios_base::binary);
	if(!out.is_open())
	{
		cout<<"Open Save File Failed(Write)."<<endl;
		return false;
	}
	out<<node_counter<<endl;
	for(int i=0;i<node_counter;i++)
	{
		for(int j=0;j<node_counter;j++)
		{
			out<<link_array[i][j]<<" ";
		}
		out<<endl;
	}
	out.close();
	return true;
}

bool Graph::Read_the_link_array_from_file()
{
	ifstream in;
	in.open("Link_Array.txt",ios_base::binary);
	if(!in.is_open())
	{
		cout<<"Open Save File Failed(Read)."<<endl;
		return false;
	}
	in>>node_counter;
	link_array=new bool*[node_counter];
	for(int i=0;i<node_counter;i++)link_array[i]=new bool[node_counter];
	for(i=0;i<node_counter;i++)
	{
		for(int j=0;j<node_counter;j++)
		{
			in>>link_array[i][j];
		}
	}
	in.close();
	return true;
}

bool Graph::Save_the_link_list_to_file()
{
	ofstream out;
	out.open("Link_List.txt",ios_base::binary);
	if(!out.is_open())
	{
		cout<<"Open Save File Failed(Write)."<<endl;
		return false;
	}
	out<<node_counter<<endl;
	for(int i=0;i<node_counter;i++)
	{
		GN* ptr=link_list[i].next;
		while(ptr)
		{
			out<<ptr->node_info<<" ";
			ptr=ptr->next;
		}
		out<<-1<<endl;
	}
	out.close();
	return true;
}

bool Graph::Read_the_link_list_from_file()
{
	ifstream in;
	in.open("Link_List.txt",ios_base::binary);
	if(!in.is_open())
	{
		cout<<"Open Save File Failed(Read)."<<endl;
		return false;
	}
	in>>node_counter;
	link_list=new GN[node_counter];
	for(int i=0;i<node_counter;i++)
	{
		GN* ptr=&link_list[i];
		ptr->node_info=i;
		int temp;
		in>>temp;
		while(temp!=-1)
		{
			ptr->next=new GN;
			ptr=ptr->next;
			ptr->node_info=temp;
			in>>temp;
		}
	}
	in.close();
	return true;
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
		rear->CLI=wait;
		front=rear;
		counter++;
		return true;
	}
	rear->next=new qnode;
	rear=rear->next;
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
	if(front!=rear)
	{
		front=front->next;
		delete temprec;
		temprec=0;
	}
	else
	{
		delete front;
		front=0;
		rear=0;
	}
	counter--;
	return temp;
}


template<typename _T>
int myqueue<_T>::get_the_queue_length()
{
	return counter;
}

bool Graph::BFS_Trigger(int start_node)
{
	if(start_node<0||start_node>=node_counter)
	{
		cout<<"Invalid node."<<endl;
		return false;
	}
	visited=new bool[node_counter];
	for(int vi=0;vi<node_counter;vi++)visited[vi]=false;
	myqueue<int> mq;
	mq.En_queue(start_node);
	visited[start_node]=true;
	cout<<"The result of BFS:"<<endl;
	while(!mq.Is_Empty())
	{
		int cur_node=mq.Get_queue();
		cout<<cur_node<<" ";	
		for (int i = 0; i < node_counter; ++i)
		{
			if(link_array[cur_node][i]&&!visited[i])
			{
				mq.En_queue(i);
				visited[i]=true;
			}
		}
	}
	cout<<endl;
	return true;
}

bool Graph::BFS_Trigger_List_Ver(int start_node)
{
	if(start_node<0||start_node>=node_counter)
	{
		cout<<"Invalid node."<<endl;
		return false;
	}
	visited=new bool[node_counter];
	for(int vi=0;vi<node_counter;vi++)visited[vi]=false;
	myqueue<int> mq;
	mq.En_queue(start_node);
	visited[start_node]=true;
	cout<<"The result of BFS:"<<endl;
	while(!mq.Is_Empty())
	{
		int cur_node=mq.Get_queue();
		cout<<cur_node<<" ";
		GN* ptr=&link_list[cur_node];
		while(ptr)
		{
			if(ptr->next&&!visited[ptr->next->node_info])
			{
				mq.En_queue(ptr->next->node_info);
				visited[ptr->next->node_info]=true;
			}
			ptr=ptr->next;
		}
	}
	cout<<endl;
	return true;
}