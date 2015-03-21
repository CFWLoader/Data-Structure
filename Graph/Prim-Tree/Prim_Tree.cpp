// Prim_Tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"Basic_Graph.h"
#include<Stack>

int main()
{
	Graph G;
//	int node_num;
//	cin>>node_num;
//	G.Establish_the_link_array(node_num,'c');
//	G.Show_the_link_array();
//	G.Establish_the_vertex_relation_ndir();
//	G.Show_the_Vertex_list();
//	G.Generate_a_graph_with_weight(node_num,'m');
	G.Read_the_weight_array_from_file();
	G.Modify_the_weight_array();
	G.Show_the_weight_array();
	G.Generate_the_Prim_Tree(0);
//	G.Save_the_weight_array_to_file();
	system("PAUSE");
}

/*bool Graph::Generate_the_Prim_Tree(int start_node)
{
	if(weight_array==0)
	{
		cout<<"The Weight_array haven't been generated."<<endl;
		return false;
	}
	if(start_node>=node_counter)
	{
		cout<<"Invalid node."<<endl;
		return false;
	}
	int i,j,added_counter=1,total_weight=0;
	int cur_node=start_node;
	visited=new bool[node_counter];
	for(i=0;i<node_counter;i++)visited[i]=false;
	visited[cur_node]=true;
	stack<int> mys;
	while(added_counter<=node_counter)
	{
		int min=0;
		bool got=false;
		for(i=0;i<node_counter;i++)
		{
			if(i==cur_node||visited[i])continue;
			if(weight_array[cur_node][i]>0&&weight_array[cur_node][min]==0)min=i,got=true;
			if(weight_array[cur_node][i]>0&&weight_array[cur_node][i]<weight_array[cur_node][min])min=i,got=true;
		}
		cout<<"(v"<<cur_node+1<<","<<"v"<<min+1<<")  "<<"MY (v"<<cur_node<<","<<"v"<<min<<") "<<"Min is visited?"<<visited[min]<<endl;
		total_weight+=weight_array[cur_node][min];
		weight_array[cur_node][min]=0;
		weight_array[min][cur_node]=0;
		if(got)
		{	
			visited[cur_node]=true;
			mys.push(cur_node);
			cur_node=min;
			added_counter++;
		}
		else
			cur_node=mys.top();
	}
	return true;
}*/

bool Graph::Modify_the_weight_array()
{
	if(!weight_array)return false;
	int i,j;
	for(i=0;i<node_counter;i++)
	{
		for(j=0;j<node_counter;j++)
		{
			if(i!=j&&weight_array[i][j]==0)weight_array[i][j]=10;
		}
	}
	return 0;
}

bool Graph::Generate_the_Prim_Tree(int start_node)
{
	if(weight_array==0)
	{
		cout<<"The Weight_array haven't been generated."<<endl;
		return false;
	}
	if(start_node>=node_counter)
	{
		cout<<"Invalid node."<<endl;
		return false;
	}
	int i,j,added_counter=1,total_weight=0;
	CL=new CloseEdge[node_counter];
	for(i=0;i<node_counter;i++)if(i!=start_node)
	{
		CL[i].adjvex=start_node;
		CL[i].lowcost=weight_array[start_node][i];
	}
	CL[start_node].adjvex=-1;
	CL[start_node].lowcost=0;
	for(i=1;i<node_counter;i++)
	{
/*		cout<<"Current Lowcost:"<<endl;
		int t;
		for(t=0;t<node_counter;t++)if(t!=start_node)
		{
			cout<<"dir: "<<CL[t].adjvex<<" cost: "<<CL[t].lowcost<<" ";
		}
		cout<<endl;*/
		int min=0;
		for(j=0;j<node_counter;j++)
		{
			if(j!=start_node&&(CL[j].lowcost!=0)&&((CL[j].lowcost<CL[min].lowcost)||CL[min].lowcost==0))
				min=j;
		}
//		cout<<"("<<CL[min].adjvex+1<<","<<min+1<<")"<<" Testdata "<<"("<<CL[min].adjvex<<","<<min<<")"<<endl;
		cout<<"("<<CL[min].adjvex+1<<","<<min+1<<")"<<endl;
		total_weight+=CL[min].lowcost;
		CL[min].lowcost=0;
		for(j = 0; j < node_counter; ++j)
		{
			if (weight_array[min][j] < CL[j].lowcost)
			{
			  CL[j].adjvex = min;
			  CL[j].lowcost = weight_array[min][j]; 
			}
		}
	}
	cout<<"Total Weight:"<<total_weight<<endl;
	return true;
}

/*int Graph::Prim_Tree_Order(int start_node)
{
	if(visited[start_node])return 0;
	visited[start_node]=true;
	int i=0,min=0,weight=0;
	bool changed;
	while(1)
	{
		changed=false;
		for(i=0;i<node_counter;i++)
		{
			if(weight_array[start_node][i]>0&&!visited[i]&&((weight_array[start_node][i]<weight_array[start_node][min]||visited[min])||(weight_array[start_node][min]==0)))min=i,changed=true;
		}
		if(!changed)break;
		if(!visited[min])
		{
			cout<<"(v"<<start_node<<",v"<<min<<")"<<"  Path Weight: "<<weight_array[start_node][min]<<endl;
			weight=weight+weight_array[start_node][i]+Prim_Tree_Order(min);
		}
	}
	return weight;
}*/











/*TNode& Graph::Generate_a_Prim_Tree(int start_node)
{
	if(array_weight==0)
	{
		throw "The array_weight haven't been established.";
	}
	TNode* P_Tree=new TNode;
	P_Tree->node_info=start_node;
}*/