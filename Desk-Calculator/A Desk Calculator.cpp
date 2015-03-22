#include<iostream>
#include<sstream>
#include<string>
#include<map>
#include<cctype>
using namespace std;

//创建一个枚举类型，用于程序内部识别表达式符号
enum Token_value{
	NAME,NUMBER,END,PLUS='+',MINUS='-',MUL='*',DIV='/',PRINT=';',ASSIGN='=',LP='(',RP=')'
};

//创建一个全局的Token_value用于记录当前的表达式符号
Token_value curr_tok=PRINT;

//no_of_error记录错误信息
int no_of_errors;

//number_value记录当前表达式中的数字值
double number_value;

//string_value记录常量表达式，例如pi、e等常量，使用一个map用于匹配常量表达式的值
string string_value;
map<string,double> table;

//input用于应对表达式的输入方式，argc为2时，表达式从argv中获取
istream* input;

//expr函数用于运算加减表达式
double expr(bool get);

//term函数用于运算乘除表达式
double term(bool get);

//prim函数用于获得将要进行运算的数值
double prim(bool get);

//error函数用于输出非法输入情况
double error(const string& s);

//get_token函数用于识别表达式中的数字，常量以及符号并返回Token_value类型的值
Token_value get_token();

int main(int argc,char* argv[])
{
	switch(argc)                                    //检查命令行参数，若使用者从命令行参数中输入表达式，则input指向该表达式
	{
	case 1:input=&cin;break;
	case 2:input=new istringstream(argv[1]);break;
	default:error("too many arguments"); return 1;
	}
	table["pi"]=3.1415926535897932385;              //初始化常量表达式的值
	table["e"]=2.7182818284590452354;
	while(input)
	{
		get_token();                                //取得表达式中第一个字符，开始运算
		if(curr_tok==END)break;
		if(PRINT==curr_tok)continue;
		cout<<expr(false)<<endl;                    //向expr函数传入FALSE值，以停止运算并输出结果
	}
	if(input!=&cin)delete input;                    //当输入不是cin时，输出结果后清理输入源
	system("PAUSE");
	return no_of_errors;
}

double expr(bool get)
{
	double left=term(get);                          //调用term函数以处理运算级比加减高的运算
	for(;;)
		switch (curr_tok)
	{
		case PLUS:left += term(true);              
			break;
		case MINUS: left -= term(true);
			break;
		default:
			return left;                            //如果没有调用则返回结果
	}
}

double term(bool get)
{
	double left=prim(get);                          //调用prim函数获得将要操作的数值
	for(;;)
		switch (curr_tok)
	{
		case MUL:left *= prim(true);
			break;
		case DIV:if(double d=prim(true))            //检查是否除0
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
	if(get)get_token();                             //调用get_token函数获得表达式中的标志
	switch (curr_tok)
	{
	case NUMBER:                                    //数值标志则获得一个数值
		{
			double v=number_value;
			get_token();
			return v;
		}
	case NAME:                                      //常量标志，通过map<string,double>获得常量的数值
		{
			double &v=table[string_value];
			if(get_token()==ASSIGN)v=expr(true);    //检查表达式是否遇到“=”号，是则调用expr函数运算出结果
			return v;
		}
	case MINUS:return -prim(true);                  //检查负数并返回
	case LP:                                        //检测到左括号，调用expr函数优先运算括号的内容
		{
			double e = expr(true);
			if(curr_tok!=RP)return error(") expected"); //右括号匹配检测
			get_token();
			return e;
		}
	default:
		return error("primary expected");
	}
}

Token_value get_token()                             //标志检测函数
{
	char ch=0;
	(*input)>>ch;                                   //从istream流中获取一个字符
	switch(ch)
	{
		//判断是何种类型的字符，并将结果存入curr_tok中
		case 0:return curr_tok=END;
		case ';':case '*':case '/':case '+':case '-':case '(':case ')':case '=': return curr_tok=Token_value(ch);
		case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '.':
			input->putback(ch);                     //检测完字符后将字符放回输入流中
			(*input)>>number_value;                 //识别标志为number，从istream流中获取double型的值
			return curr_tok=NUMBER;
		default:
			if(isalpha(ch))                         //默认英文字母为常量表达式，将表达式值存入string_value中
			{
				(*input).putback(ch);
				(*input)>>string_value;
				return curr_tok=NAME;
			}
			error("bad token");
			return curr_tok=PRINT;                  //标志字符超出本程序的设定，输出错误信息
	}
}

double error(const string& s)
{
	no_of_errors++;
	cerr<<"error: "<<s<<'\n';
	return 1;
}