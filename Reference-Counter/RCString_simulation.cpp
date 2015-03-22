//实现带有引用计数string类
#include<iostream>
#include<cstring>
using namespace std;

//引用计数器类，用于被继承
class RCObject
{
private:
	//引用次数计算器
	int _refcount;
	//记录该实体能否被共享
	bool _shareable;
public:
	RCObject();
	RCObject(const RCObject&);
	RCObject& operator=(const RCObject&);
	virtual ~RCObject() = 0;

	//当有别的对象拥有共同拥有该实值时，引用计数+1
	void addReference();

	//当对象放弃拥有该实值时，引用计数-1
	void removeReferences();

	//当出现不能共享的情况时，将该实体设置不能被共享
	void markUnshareable();

	//查询能否被共享
	bool isShareable() const;

	//查询是否被多次引用
	bool isShared() const;
};

class String
{
private:
	//String类内包含一个StringValue类指针，用于指向有同一值的实体
	//StringValue继承引用计数器RCObejct，继承了自动计数的能力
	struct StringValue:public RCObject
	{
		char* data;
		StringValue(const char* initValue);
		StringValue(const StringValue& rhs);
		~StringValue();
	};
	StringValue* _string;
public:
	//这些接口是String基本的功能，出现重载主要是处理C风格和C++风格的字符串
	String();
	String(const char*);
	String(const String&);
	~String();
	const String& operator=(const char*);
	const String& operator=(const String&);
	String operator+(const char*) const;
	String operator+(const String&) const;
	const String& operator+=(const char*);
	const String& operator+=(const String&);

	//VC6.0对友元支持不佳，构建一个接口用于重载<<
	void print(ostream& os){os<<_string->data;}

	int length();
	char& operator[](int);
};

ostream& operator<<(ostream& os,String& rhs)
{
	rhs.print(os);
	return os;
}

int main(int argc,char* argv[])
{
	//mian中的测试都编译通过并正常运行
	String str1("asdfnakjsg");
	String str2(str1);
	cout<<str1<<endl;
	cout<<str2<<endl;
	String str3("I'm new string.");
	cout<<str3<<endl;
	str3=str2;
	cout<<str3<<endl;
	str3="dfefaeff";
	cout<<str3<<endl;
	str3=str1+str2;
	cout<<str3<<endl;
	str3=str3+"jabsdfasdf";
	cout<<str3<<endl;
	str1+=str2;
	cout<<str1<<endl;
	str3+="afsdfiiiiiiii";
	cout<<str3<<endl;
	cout<<str3.length()<<endl;
	return 0;
}

//引用计数器类的实现
RCObject::RCObject():_refcount(0),_shareable(true){}

RCObject::RCObject(const RCObject& rhs):_refcount(0),_shareable(true){}

RCObject& RCObject::operator=(const RCObject& rhs)
{
	return *this;
}

RCObject::~RCObject(){}

void RCObject::addReference()
{
	++_refcount;
}

void RCObject::removeReferences()
{
	if(--_refcount==0)delete this;         //当引用次数为零时，delete对象
}

void RCObject::markUnshareable()
{
	_shareable=false;
}

bool RCObject::isShareable() const
{
	return _shareable;
}

bool RCObject::isShared() const
{
	return _refcount>1;                    //检查是否还有别的对象使用该实体
}

//StringValue类的实现，由于计数器类的实现，自身的代码工作减少了很多
String::StringValue::StringValue(const char* initValue="")
{
	data=new char[strlen(initValue)+1];
	strcpy(data,initValue);
	addReference();                        //指向同一实体，引用次数+1
}

String::StringValue::StringValue(const StringValue& rhs)
{
	if(rhs.isShareable()){
		data=rhs.data;
		const_cast<StringValue*>(&rhs)->addReference();
	}
	else{
		data=new char[strlen(rhs.data)+1];
		strcpy(data,rhs.data);
		this->addReference();
	}
}

String::StringValue::~StringValue()
{
	delete[] data;
}

String::String():_string(0)
{
	_string=0;
}

String::String(const char* initvalue="")
{
	_string=new StringValue(initvalue);
}

String::String(const String& rhs)
{
	_string=new StringValue(*rhs._string);
}

String::~String()
{
	if(!_string)return;
	_string->removeReferences();           //当引用次数为0时，RCObject的析构函数为虚函数，能够自动析构子类
}

//以下的函数实现主要注意引用次数的正确变化即可
//不需要过多地管理StringValue的内存
const String& String::operator=(const char* newstr)
{
	if(!_string){
		_string=new StringValue(newstr);
		return (*this);
	}
	_string->removeReferences();                   
	_string=new StringValue(newstr);
	return (*this);
}

const String& String::operator=(const String& rhs)
{
	if(!_string){
		_string=new StringValue((*rhs._string));
		return (*this);
	}
	_string->removeReferences();
	_string=new StringValue((*rhs._string));
	return (*this);
}

String String::operator+(const char* secstr) const
{
	char* newstr=0;
	if(_string)
	{
		newstr=new char[strlen(_string->data)+strlen(secstr)+1];
		strcpy(newstr,_string->data);
		strcat(newstr,secstr);
	}
	else
	{
		newstr=new char[strlen(secstr)+1];
		strcpy(newstr,secstr);
	}
	return String(newstr);
}

String String::operator+(const String& rhs) const
{
	char* newstr;
	if(_string)
	{
		newstr=new char[strlen(_string->data)+strlen(rhs._string->data)+1];
		strcpy(newstr,_string->data);
		strcat(newstr,(rhs._string->data));
	}
	else
	{
		newstr=new char[strlen(rhs._string->data)+1];
		strcpy(newstr,rhs._string->data);
	}
	return String(newstr);
}

const String& String::operator+=(const char* secstr)
{
	if(_string)
	{
		char* old=new char[strlen(_string->data)+strlen(secstr)];
		strcpy(old,_string->data);
		strcat(old,secstr);
		StringValue* oldstr=_string;
		_string=new StringValue(old);
		oldstr->removeReferences();	
		old=0;
	}
	else
		_string=new StringValue(secstr);
	return (*this);
}

const String& String::operator+=(const String& rhs)
{
	if(_string)
	{
		char* old=new char[strlen(_string->data)+strlen(rhs._string->data)];
		strcpy(old,_string->data);
		strcat(old,rhs._string->data);
		StringValue* oldstr=_string;
		_string=new StringValue(old);
		oldstr->removeReferences();	
		old=0;
	}
	else _string=new StringValue(*rhs._string);
	return (*this);
}

int String::length()
{
	if(_string)return strlen(_string->data);
	else return 0;
}

//因为不符合引用次数增加的原则，该情况直接让StringValue类失去共享资格
char& String::operator [](int index)
{
	if(index<0||(index+1)>strlen(_string->data))
	{
		cout<<"Over the bound."<<endl;
		char tp=0;
		return tp;
	}
	else
	{
		_string->markUnshareable();
		return _string->data[index];
	}
}