#include "ypmemory.h"

YPAutoreleasePoolCluster ypAutoreleasePoolCluster;

void _YPObject::Release() 
{
	if (--_yp_count == 0) {
		delete this;
	}
}

YPAutoreleasePool::YPAutoreleasePool() 
{
	ypAutoreleasePoolCluster.AddPool(this);
}

void YPAutoreleasePool::Release() 
{
	for (list<_YPObject*>::iterator it = objs.begin(); it != objs.end(); it++) 
	{
		(*it)->Release();
	}
	ypAutoreleasePoolCluster.DeletePool();
}

void YPAutoreleasePool::AddObject(_YPObject *obj) 
{
	objs.push_front(obj);
}

YPAutoreleasePool* YPAutoreleasePoolCluster::GetPool() 
{
	return pools.top();
}

void YPAutoreleasePoolCluster::AddPool(YPAutoreleasePool* pool)
{
	pools.push(pool);
}

void YPAutoreleasePoolCluster::DeletePool()
{
	pools.pop();
}