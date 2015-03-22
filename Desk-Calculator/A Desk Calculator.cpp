#include<iostream>
#include<sstream>
#include<string>
#include<map>
#include<cctype>
using namespace std;

//����һ��ö�����ͣ����ڳ����ڲ�ʶ����ʽ����
enum Token_value{
	NAME,NUMBER,END,PLUS='+',MINUS='-',MUL='*',DIV='/',PRINT=';',ASSIGN='=',LP='(',RP=')'
};

//����һ��ȫ�ֵ�Token_value���ڼ�¼��ǰ�ı��ʽ����
Token_value curr_tok=PRINT;

//no_of_error��¼������Ϣ
int no_of_errors;

//number_value��¼��ǰ���ʽ�е�����ֵ
double number_value;

//string_value��¼�������ʽ������pi��e�ȳ�����ʹ��һ��map����ƥ�䳣�����ʽ��ֵ
string string_value;
map<string,double> table;

//input����Ӧ�Ա��ʽ�����뷽ʽ��argcΪ2ʱ�����ʽ��argv�л�ȡ
istream* input;

//expr������������Ӽ����ʽ
double expr(bool get);

//term������������˳����ʽ
double term(bool get);

//prim�������ڻ�ý�Ҫ�����������ֵ
double prim(bool get);

//error������������Ƿ��������
double error(const string& s);

//get_token��������ʶ����ʽ�е����֣������Լ����Ų�����Token_value���͵�ֵ
Token_value get_token();

int main(int argc,char* argv[])
{
	switch(argc)                                    //��������в�������ʹ���ߴ������в�����������ʽ����inputָ��ñ��ʽ
	{
	case 1:input=&cin;break;
	case 2:input=new istringstream(argv[1]);break;
	default:error("too many arguments"); return 1;
	}
	table["pi"]=3.1415926535897932385;              //��ʼ���������ʽ��ֵ
	table["e"]=2.7182818284590452354;
	while(input)
	{
		get_token();                                //ȡ�ñ��ʽ�е�һ���ַ�����ʼ����
		if(curr_tok==END)break;
		if(PRINT==curr_tok)continue;
		cout<<expr(false)<<endl;                    //��expr��������FALSEֵ����ֹͣ���㲢������
	}
	if(input!=&cin)delete input;                    //�����벻��cinʱ������������������Դ
	system("PAUSE");
	return no_of_errors;
}

double expr(bool get)
{
	double left=term(get);                          //����term�����Դ������㼶�ȼӼ��ߵ�����
	for(;;)
		switch (curr_tok)
	{
		case PLUS:left += term(true);              
			break;
		case MINUS: left -= term(true);
			break;
		default:
			return left;                            //���û�е����򷵻ؽ��
	}
}

double term(bool get)
{
	double left=prim(get);                          //����prim������ý�Ҫ��������ֵ
	for(;;)
		switch (curr_tok)
	{
		case MUL:left *= prim(true);
			break;
		case DIV:if(double d=prim(true))            //����Ƿ��0
				 {
					 left /= d;
					 break;
				 }
				 return error("divide by 0");
		default:
			return left;
	}
}

double prim(bool get)
{
	if(get)get_token();                             //����get_token������ñ��ʽ�еı�־
	switch (curr_tok)
	{
	case NUMBER:                                    //��ֵ��־����һ����ֵ
		{
			double v=number_value;
			get_token();
			return v;
		}
	case NAME:                                      //������־��ͨ��map<string,double>��ó�������ֵ
		{
			double &v=table[string_value];
			if(get_token()==ASSIGN)v=expr(true);    //�����ʽ�Ƿ�������=���ţ��������expr������������
			return v;
		}
	case MINUS:return -prim(true);                  //��鸺��������
	case LP:                                        //��⵽�����ţ�����expr���������������ŵ�����
		{
			double e = expr(true);
			if(curr_tok!=RP)return error(") expected"); //������ƥ����
			get_token();
			return e;
		}
	default:
		return error("primary expected");
	}
}

Token_value get_token()                             //��־��⺯��
{
	char ch=0;
	(*input)>>ch;                                   //��istream���л�ȡһ���ַ�
	switch(ch)
	{
		//�ж��Ǻ������͵��ַ��������������curr_tok��
		case 0:return curr_tok=END;
		case ';':case '*':case '/':case '+':case '-':case '(':case ')':case '=': return curr_tok=Token_value(ch);
		case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '.':
			input->putback(ch);                     //������ַ����ַ��Ż���������
			(*input)>>number_value;                 //ʶ���־Ϊnumber����istream���л�ȡdouble�͵�ֵ
			return curr_tok=NUMBER;
		default:
			if(isalpha(ch))                         //Ĭ��Ӣ����ĸΪ�������ʽ�������ʽֵ����string_value��
			{
				(*input).putback(ch);
				(*input)>>string_value;
				return curr_tok=NAME;
			}
			error("bad token");
			return curr_tok=PRINT;                  //��־�ַ�������������趨�����������Ϣ
	}
}

double error(const string& s)
{
	no_of_errors++;
	cerr<<"error: "<<s<<'\n';
	return 1;
}