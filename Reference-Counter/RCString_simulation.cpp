//ʵ�ִ������ü���string��
#include<iostream>
#include<cstring>
using namespace std;

//���ü������࣬���ڱ��̳�
class RCObject
{
private:
	//���ô���������
	int _refcount;
	//��¼��ʵ���ܷ񱻹���
	bool _shareable;
public:
	RCObject();
	RCObject(const RCObject&);
	RCObject& operator=(const RCObject&);
	virtual ~RCObject() = 0;

	//���б�Ķ���ӵ�й�ͬӵ�и�ʵֵʱ�����ü���+1
	void addReference();

	//���������ӵ�и�ʵֵʱ�����ü���-1
	void removeReferences();

	//�����ֲ��ܹ�������ʱ������ʵ�����ò��ܱ�����
	void markUnshareable();

	//��ѯ�ܷ񱻹���
	bool isShareable() const;

	//��ѯ�Ƿ񱻶������
	bool isShared() const;
};

class String
{
private:
	//String���ڰ���һ��StringValue��ָ�룬����ָ����ͬһֵ��ʵ��
	//StringValue�̳����ü�����RCObejct���̳����Զ�����������
	struct StringValue:public RCObject
	{
		char* data;
		StringValue(const char* initValue);
		StringValue(const StringValue& rhs);
		~StringValue();
	};
	StringValue* _string;
public:
	//��Щ�ӿ���String�����Ĺ��ܣ�����������Ҫ�Ǵ���C����C++�����ַ���
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

	//VC6.0����Ԫ֧�ֲ��ѣ�����һ���ӿ���������<<
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
	//mian�еĲ��Զ�����ͨ������������
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

//���ü��������ʵ��
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
	if(--_refcount==0)delete this;         //�����ô���Ϊ��ʱ��delete����
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
	return _refcount>1;                    //����Ƿ��б�Ķ���ʹ�ø�ʵ��
}

//StringValue���ʵ�֣����ڼ��������ʵ�֣�����Ĵ��빤�������˺ܶ�
String::StringValue::StringValue(const char* initValue="")
{
	data=new char[strlen(initValue)+1];
	strcpy(data,initValue);
	addReference();                        //ָ��ͬһʵ�壬���ô���+1
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
	_string->removeReferences();           //�����ô���Ϊ0ʱ��RCObject����������Ϊ�麯�����ܹ��Զ���������
}

//���µĺ���ʵ����Ҫע�����ô�������ȷ�仯����
//����Ҫ����ع���StringValue���ڴ�
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

//��Ϊ���������ô������ӵ�ԭ�򣬸����ֱ����StringValue��ʧȥ�����ʸ�
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