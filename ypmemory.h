#pragma once

#include <stack>
#include <list>
using namespace std;

#define YPClass(c) class c: public YPObject<c>
#define YPExtClass(father) class YP##father: public YPObject<YP##father>, public father

class _YPObject 
{
public:
	virtual void Release();
	virtual ~_YPObject() {}
protected:
	int _yp_count; 
};

class YPAutoreleasePool
{
public:
	YPAutoreleasePool();
	void Release();
	void AddObject(_YPObject *obj);
private:
	list<_YPObject*> objs;
};

class YPAutoreleasePoolCluster
{
public:
	YPAutoreleasePool* GetPool();
	void AddPool(YPAutoreleasePool* pool);
	void DeletePool();
private:
	stack<YPAutoreleasePool*> pools;
};

extern YPAutoreleasePoolCluster ypAutoreleasePoolCluster;

template<class T>
class YPObject: public _YPObject
{
public:
	static T* Alloc();
	T* Retain();
	T* Autorelease();
};

template<class T>
T* YPObject<T>::Alloc()
{
	T* ret = new T();
	ret->_yp_count = 1;
	return ret;
}

template<class T>
T* YPObject<T>::Retain()
{
	_yp_count++;
	cout << _yp_count << endl;
	return (T*)this;
}

template<class T>
T* YPObject<T>::Autorelease()
{
	YPAutoreleasePool* pool = ypAutoreleasePoolCluster.GetPool();
	pool->AddObject(this);
	return (T*)this;
}