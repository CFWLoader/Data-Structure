#ifndef BASIC_GRAPH_H_
#define BASIC_GRAPH_H_
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

typedef struct Graph_Edge
{
	int start,end;
	int weight;
	struct Graph_Edge* next;
	Graph_Edge()
	{
		start=-1;
		end=-1;
		next=0;
	}
}GE;

typedef struct
{
	int adjvex;
	int lowcost;
}CloseEdge;

/*typedef struct Prim_Tree
{
	int node_info;
	struct Prim_Tree* lchild,*rchild;
	Prim_Tree()
	{
		node_info=-1;
		lchild=0;
		rchild=0;
	}
}TNode;*/

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
	int** weight_array;
	GN* link_list;
	GE* edge_list;
	int node_counter;
	bool* visited;
	void Depth_First_Search(int start_node);
	void Depth_First_Search_L(int start_node);
	CloseEdge* CL;
public:
	Graph();
	Graph(int reference);
	bool Establish_the_link_array(int nc);
	bool Establish_the_link_array(int nc,char tag);
	bool Change_the_array_to_list();
	bool Establish_the_vertex_relation();
	bool Establish_the_vertex_relation_ndir();
	bool Show_the_Vertex_list();
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
	bool Generate_a_graph_with_weight(int reference);
	bool Show_the_weight_array();
	bool Generate_a_graph_with_weight(int reference,char manual);
	bool Save_the_weight_array_to_file();
	bool Read_the_weight_array_from_file();
	bool Generate_the_Prim_Tree(int start_node);
	bool Modify_the_weight_array();
//	TNode& Generate_a_Prim_Tree(int);
};

/*int main()
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
}*/

Graph::Graph()
{
	link_list=0;
	link_array=0;
	weight_array=0;
	visited=0;
	node_counter=0;
	edge_list=0;
	CL=0;
}

Graph::Graph(int reference)
{
	node_counter=reference;
	link_array=0;
	link_list=0;
	visited=0;
	edge_list=0;
	weight_array=0;
	CL=0;
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
	for (int i = 0; i < node_counter; ++i)
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

bool Graph::Establish_the_link_array(int nc,char tag)
{
	if(nc<1)return false;
	if(node_counter!=nc)node_counter=nc;
	link_array=new bool*[node_counter];
	srand(time(0));
	for (int i = 0; i < node_counter; ++i)
	{
		link_array[i]=new bool[node_counter];
	}
	for (int i = 0; i < node_counter; ++i)
	{
		for (int j = i; j < node_counter; ++j)
		{
			if(j==i)
			{
				link_array[i][j]=false;
				continue;
			}
			link_array[i][j]=rand()%2;
			link_array[j][i]=link_array[i][j];
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
	for (int i = 0; i < node_counter; ++i)
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
	for (int i = 0; i < node_counter; ++i)
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
	for(int i=0;i<node_counter;i++)
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

bool Graph::Generate_a_graph_with_weight(int reference)
{
	if(node_counter!=reference)node_counter=reference;
	weight_array=new int*[node_counter];
	int i,j;
	for(i=0;i<node_counter;i++)weight_array[i]=new int[node_counter];
	for(i=0;i<node_counter;i++)
	{
		for(j=0;j<node_counter;j++)
		{
			if(i==j)
				weight_array[i][j]=0;
			else
				weight_array[i][j]=rand()%30;
		}
	}
	return true;
}

bool Graph::Show_the_weight_array()
{
	if(weight_array==0)
	{
		cout<<"THe weight_array hasn't been established."<<endl;
		return false;
	}
	cout<<"   ";
	for (int i = 0; i < node_counter; ++i)
	{
		cout.width(3);
		cout<<i;
	}
	cout<<endl;
	for (int i = 0; i < node_counter; ++i)
	{
		cout.width(3);
		cout<<i;
		for (int j = 0; j < node_counter; ++j)
		{
			cout.width(3);
			cout<<weight_array[i][j];
		}
		cout<<endl;
	}
	return true;
}

bool Graph::Generate_a_graph_with_weight(int reference,char manual)
{
	if(node_counter!=reference)node_counter=reference;
	weight_array=new int*[node_counter];
	int i,j;
	for(i=0;i<node_counter;i++)weight_array[i]=new int[node_counter];
	for(i=0;i<node_counter;i++)
	{
		for(j=0;j<node_counter;j++)
		{
			cin>>weight_array[i][j];
		}
	}
	return true;
}

bool Graph::Save_the_weight_array_to_file()
{
	ofstream out;
	out.open("Weight_Array.txt",ios_base::binary);
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
			out<<weight_array[i][j]<<" ";
		}
		out<<endl;
	}
	out.close();
	return true;
}

bool Graph::Read_the_weight_array_from_file()
{
	ifstream in;
	in.open("Weight_Array.txt",ios_base::binary);
	if(!in.is_open())
	{
		cout<<"Open Save File Failed(Read)."<<endl;
		return false;
	}
	in>>node_counter;
	weight_array=new int*[node_counter];
	for(int i=0;i<node_counter;i++)weight_array[i]=new int[node_counter];
	for(int i=0;i<node_counter;i++)
	{
		for(int j=0;j<node_counter;j++)
		{
			in>>weight_array[i][j];
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

bool Graph::Establish_the_vertex_relation()
{
	if(link_array==0)
	{
		cout<<"The Link_array doesn't exist."<<endl;
		return false;
	}
	edge_list=new GE;
	GE* ptr=edge_list;
	for(int i=0;i<node_counter;i++)
	{
		for(int j=0;j<node_counter;j++)
		{
			if(link_array[i][j]==true)
			{
				ptr->next=new GE;
				ptr=ptr->next;
				ptr->start=i;
				ptr->end=j;
				ptr->weight=rand()%50;
			}
		}
	}
	ptr=edge_list;
	edge_list=edge_list->next;
	delete ptr;
	ptr=0;
	return true;
}

bool Graph::Show_the_Vertex_list()
{
	if(edge_list==0)
	{
		cout<<"The Vertex_list doesn't exist."<<endl;
		return false;
	}
	GE* ptr=edge_list;
	while(ptr)
	{
		cout<<"Start: "<<ptr->start<<" End: "<<ptr->end<<" Weight: "<<ptr->weight<<endl;
		ptr=ptr->next;
	}
	return true;
}

bool Graph::Establish_the_vertex_relation_ndir()
{
	if(link_array==0)
	{
		cout<<"The Link_array doesn't exist."<<endl;
		return false;
	}
	edge_list=new GE;
	GE* ptr=edge_list;
	for(int i=0;i<node_counter;i++)
	{
		for(int j=i;j<node_counter;j++)
		{
			if(link_array[i][j]==true)
			{
				ptr->next=new GE;
				ptr=ptr->next;
				ptr->start=i;
				ptr->end=j;
				ptr->weight=rand()%50;
			}
		}
	}
	ptr=edge_list;
	edge_list=edge_list->next;
	delete ptr;
	ptr=0;
	return true;
}
#endif