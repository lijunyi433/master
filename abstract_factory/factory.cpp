#include <iostream>

using namespace std;

class clothing
{
public:
	virtual ~clothing(){}
	virtual void show() = 0;
};

class shoes:public clothing
{
public:
	void show()
	{
		cout << "Shoes object" << endl;
	}
};

class pants:public clothing
{
public:
	void show()
	{
		cout << "Pants object" << endl;
	}
};

class shirts:public clothing
{
public:
	void show()
	{
		cout << "Shirts object" << endl;
	}
};

class factory
{
public:
	factory(){}
	~factory(){}
	virtual clothing *produce_shoes() = 0;
	virtual clothing *produce_pants() = 0;
	virtual clothing *produce_shirts() = 0;
};

class clothes_factory:public factory
{
public:
	clothing *produce_shoes()
	{
		return new shoes();
	}
	clothing *produce_pants()
	{
		return new pants();
	}
	clothing *produce_shirts()
	{
		return new shirts();
	}

};

int main(int argc,const char * argv[]){
	clothes_factory *clothes_f = new clothes_factory();
	clothing *shoes = clothes_f->produce_shoes();
	if(shoes)
	{
		shoes->show();
	}

	clothing *pants = clothes_f->produce_pants();
	if(pants)
	{
		pants->show();
	}

	clothing *shirts = clothes_f->produce_shirts();
	if(shirts)
	{
		shirts->show();
	}

	delete clothes_f;
	clothes_f = NULL;
	
	delete shoes;
	shoes = NULL;
	delete pants;
	pants = NULL;
	delete shirts;
	shirts = NULL;

   return 0;
}
