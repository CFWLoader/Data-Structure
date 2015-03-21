#include<iostream>
#include<cstdlib>
#include<fstream>
using namespace std;

typedef struct huffman_tree
{
	char key;
	float weight;
//	struct huffman_tree *parent,*lchild,*rchild;
	int parent,lchild,rchild;                                    /*建立哈夫曼树用的数组树，因而指针要改变成int型*/
}hfmtree;

/*typedef struct characters_code
{
	char ch;
	char *code;
}c_code;*/

class MyFunction                                                                     /*由于涉及二级指针才能正常使用私有成员（将其值赋予外部指针），于是暂时采用数据外部化，这个class只提供函数功能*/
{
private:
public:
	void save_the_original_data()                                                      /*建立暗码的资料并存储在文件之中*/
	{
		ofstream fout;
		fout.open("hfmTree.txt",ios_base::out|ios_base::binary);
		int n;
		cout<<"How many characters do you want to save?"<<endl;
		cin>>n;
		hfmtree *save=new hfmtree[n];
		for(int i=0;i<n;i++)
		{
			cout<<"Character:"<<endl;
			cin>>save[i].key;
			cout<<"weight"<<endl;
			cin>>save[i].weight;
			save[i].parent=save[i].lchild=save[i].rchild=0;
		}
		fout<<n<<endl;
		for(i=0;i<n;i++)
		{
			fout<<save[i].key<<" "<<save[i].weight<<endl;                                 /*weight是暗码的权重，在建立哈夫曼数中提供元素排在数的哪个位置提供重要参考*/
		}
		fout.close();
	}

	void read_the_oringinal_data(hfmtree **test,int *count)                               /*从文件中读取暗码的资料，涉及二级指针才能将这个指针正确赋值并返回到main函数中*/
	{
		ifstream fin;
		fin.open("hfmTree.txt",ios_base::in|ios_base::binary);
		int n;
		hfmtree *array;
		fin>>*count;
		n=*count;
		array=new hfmtree[n];
		for(int i=0;i<n;i++)
		{
			fin>>array[i].key>>array[i].weight;
//			cout<<array[i].key<<" "<<array[i].weight<<endl;
			array[i].parent=array[i].lchild=array[i].rchild=0;
		}
		*test=array;
		fin.close();
	}

	hfmtree* form_a_huffman_tree(const hfmtree *ohfm,int n)                            /*根据暗码的资料建立哈夫曼数*/
	{
		hfmtree *tree;
		int count=2*n-1;
		tree=new hfmtree[count];
		for(int i=0;i<n;i++)
		{
			tree[i].key=ohfm[i].key;
			tree[i].weight=ohfm[i].weight;
			tree[i].parent=0;
			tree[i].lchild=0;
			tree[i].rchild=0;
		}
		for(i=n;i<count;i++)
		{
			tree[i].parent=tree[i].lchild=tree[i].rchild=0;
		}
		for(i=n;i<count;i++)
		{
			int min1,min2,sel=0;
			while(tree[sel].parent!=0&&sel<i)sel++;
			min1=sel;
			for(int j=0;j<i;j++)
			{
				if(tree[min1].weight>tree[j].weight&&tree[j].parent==0)
					min1=j;
			}
//			cout<<min1<<" "<<tree[min1].weight<<endl;
			tree[i].lchild=min1;
			tree[min1].parent=i;
			while(tree[sel].parent!=0&&sel<i)sel++;
			min2=sel;
			for(j=0;j<i;j++)
			{
				if(tree[min2].weight>tree[j].weight&&tree[j].parent==0)
					min2=j;
			}
//			cout<<min2<<" "<<tree[min2].weight<<endl;
			tree[i].rchild=min2;
			tree[min2].parent=i;
			tree[i].weight=tree[min1].weight+tree[min2].weight;
//			cout<<i<<"lchild:"<<tree[i].lchild<<"rchild:"<<tree[i].rchild<<endl;
		}
/*		for(i=0;i<count;i++)cout<<i<<"parent:"<<tree[i].parent<<"lchild:"<<tree[i].lchild<<"rchild:"<<tree[i].rchild<<endl;*/
		return tree;
	}

	char* read_the_text()
	{
		char* k;
		k=new char[100];
		ifstream fin;
		fin.open("ToBeTran.txt");
		fin>>k;
		return k;
	}

	char* Encoding(char* mother,hfmtree* tree,int edge)
	{
		int count=0,code_count=0;
		char *code;
		code=new char[200];
		while(mother[count]!='\0')
		{
			int rec,temp_count=0,char temp[4];
			for(rec=0;rec<edge&&mother[count]!=tree[rec].key;rec++);
			while(tree[rec].parent!=-1)
			{
				int pare;
				pare=tree[rec].parent;
				if(tree[pare].lchild==rec)
				{
//					code[code_count++]='0';
					temp[temp_count++]='0';
				}
				else
				{
//					code[code_count++]='1';
					temp[temp_count++]='1';
				}
				rec=pare;
			}
			temp_count--;
			while(temp_count>=0)
			{
				code[code_count++]=temp[temp_count--];
			}
			count++;
		}
		code[code_count]='\0';
		return code;
	}

	char* Decoding(char *code,hfmtree *tree,int root)
	{
		char *text;
		text=new char[100];
		int code_count=0,count=0;
		while(code[code_count]!='\0')
		{
			int tree_count=root-1;
			while(tree[tree_count].lchild!=0)
			{
				if(code[code_count++]=='0')
					tree_count=tree[tree_count].lchild;
				else
					tree_count=tree[tree_count].rchild;
			}
			text[count++]=tree[tree_count].key;
		}
		text[count]='\0';
		return text;
	}

	void save_the_code(char *code)
	{
		ofstream fout;
		fout.open("TextFile.txt");
		fout<<code<<endl;
		fout.close();
	}

	char* read_the_code()
	{
		char *code;
		code=new char[200];
		ifstream fin;
		fin.open("TextFile.txt");
		fin>>code;
		fin.close();
		return code;
	}

};
	
int main()
{
	MyFunction test;
	hfmtree *cdata=0,*root=0;
	int n;
	char *text,*coded,*for_com;
	int selection;
sta1:	cout<<"Which function do you want to use?"<<endl<<"1.Put in the secret characters' information."<<endl<<"2.Form the Huffman Tree about secret characters."<<endl;
	cout<<"3.Encode the text from file and save the codes."<<endl<<"4.Decode the codes from file."<<endl;
	cin>>selection;
	switch(selection)
	{
	case 1:
		{
			test.save_the_original_data();
			break;
		}
	case 2:
		{
			test.read_the_oringinal_data(&cdata,&n);
			root=test.form_a_huffman_tree(cdata,n);
			root[2*n-2].parent=-1;
			break;
		}
	case 3:
		{
			text=test.read_the_text();
			cout<<text<<endl;
			if(cdata==0)
			{
				cout<<"Please put in the secret characters' information at first."<<endl;
				break;
			}
			coded=test.Encoding(text,root,2*n-1);
			test.save_the_code(coded);
			break;
		}
	case 4:
		{
			coded=test.read_the_code();
			cout<<coded<<endl;
			if(cdata==0)
			{
				cout<<"Please put in the secret characters' information at first."<<endl;
				break;
			}
			for_com=test.Decoding(coded,root,2*n-1);
			cout<<for_com<<endl;
			break;
		}
	default:cout<<"Wrong selection!"<<endl;
	}
	cout<<"Do you want to continue?(y\\n)"<<endl;
	char chose;
	cin>>chose;
	if(chose=='y')goto sta1;
/*	test.read_the_oringinal_data(&cdata,&n);*/
/*	for(int i=0;i<n;i++)
	{
		cout<<cdata[i].key<<" "<<cdata[i].weight<<endl;
		cout<<cdata[i].parent<<" "<<cdata[i].lchild<<" "<<cdata[i].rchild<<endl;
	}*/
/*	root=test.form_a_huffman_tree(cdata,n);
	root[2*n-2].parent=-1;*/
//	hfmtree *ptr=&root[11];
/*	for(int i=0;i<2*n-1;i++)
	{
		cout<<i<<" "<<root[i].weight<<endl;
		cout<<root[i].parent<<" "<<root[i].lchild<<" "<<root[i].rchild<<endl;
		cout<<endl;
	}*/
//	test.preorder(ptr);
/*	for(int i=0;i<2*n-1;i++)cout<<i<<" weight:"<<root[i].weight<<" parent:"<<root[i].parent<<" lchild:"<<root[i].lchild<<" rchild:"<<root[i].rchild<<endl;*/
/*	text=test.read_the_text();
	cout<<text<<endl;*/
/*	coded=test.Encoding(text,root,2*n-1);
	cout<<coded<<endl;
	test.save_the_code(coded);*/
/*	coded=test.read_the_code();
	for_com=test.Decoding(coded,root,2*n-1);
	cout<<for_com<<endl;*/
	return 0;
}
