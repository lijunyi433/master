#include <iostream>

using namespace std;

class Singleton
{
private:
	static Singleton *singleton;
	Singleton(){}
	~Singleton()
	{
		delete singleton;
		singleton = NULL;
	}
public:
	static Singleton* getInstance();
};

Singleton *Singleton::singleton = new Singleton();
 
Singleton* Singleton::getInstance()
{
	return singleton;
}


int main(int argc,const char * argv[]){
	cout<<"Hello World"<<endl;
	Singleton *s = Singleton::getInstance();
   cout<<"Hello World"<<endl;

   return 0;
}