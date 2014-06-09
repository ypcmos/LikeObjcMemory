#include <iostream>
#include "ypmemory.h"
#include <string>

class Test: public YPObject<Test> 
{
public:
	~Test() {
		cout << "~Test\r\n";
	}
};

YPClass(Test2) 
{
public:
	~Test2() {
		cout << "~Test2->" << i << "\r\n";
	}

	Test2* Init(int i) {
		this->i = i;
		return this;
	}

private:
	int i;
};

YPExtClass(string) 
{
public:
	~YPstring() {
		cout << *this << endl ;
	}
};

Test2* getT2(int i) 
{
	return Test2::Alloc()->Init(i)->Autorelease();
}

string* getString(int i)
{
	string* str = YPstring::Alloc()->Autorelease();
	char temp[10];
	*str = itoa(i, temp, 10);
	return str;
}

void main() {
	YPAutoreleasePool pool;
	Test *t = Test::Alloc();

	for (int i = 0; i < 5; i++)
	{
		YPAutoreleasePool pool;
		getT2(i);
		cout << "outer:" << *getString(i) << endl;
		pool.Release();
	}
	t->Autorelease();
	pool.Release();
	system("pause");
}