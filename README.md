LikeObjcMemory
====

LikeObjcMemory is a very simple memory management tool. We can use it just as in Objective-C.
For example:
	YPAutoreleasePool pool;
	Test *t = Test::Alloc();

	for (int i = 0; i < 5; i++)
	{
		YPAutoreleasePool pool;
		...
		pool.Release();
	}
	t->Autorelease();
	pool.Release();

also, we can release any object immediately with using 't->Release()'.
Sometimes we need to save object when release the pool with using 't->Retain()' .

To use these convenient tools, your class must inherit 'YPObject<T>', such as 
	class Test: public YPObject<Test>
	{
		...
	};

    We offer a quick way to replace the above:
	YPClass(Test)
	{
		...
	};

Some code which has been written can easily be expanded in order to use this tool, as 'string':

	YPExtClass(string) 
	{
	public:
		~YPstring() {
			cout << *this << endl ;
		}
	};

    Macro 'YPExtClass(T)' expands class name with prefix 'YP'
