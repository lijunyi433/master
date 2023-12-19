#include <iostream>
#include <mutex>
using namespace std;

class Singleton
{
private:
	static volatile Singleton *singleton;
	static mutex mtx;
	Singleton(){}
	~Singleton()
	{
		delete singleton;
		singleton = NULL;
	}
public:
	static volatile Singleton* getInstance();
};

Singleton volatile *Singleton::singleton = new Singleton();
mutex Singleton:: mtx;
 
volatile Singleton* Singleton::getInstance()
{
	if(NULL == singleton)
	{
		std::lock_guard<std::mutex> my_guard(mtx);
		if(NULL == singleton)
		{	
			singleton = new Singleton();
		}
	}
	return singleton;
}


int main(int argc,const char * argv[]){
	cout<<"Hello World"<<endl;
	Singleton volatile *s = Singleton::getInstance();
    cout<<"Hello World"<<endl;

    return 0;
}