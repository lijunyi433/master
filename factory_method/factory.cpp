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
	virtual clothing *produce_clothes() = 0;
};

class shoes_factory:public factory
{
public:
	clothing * produce_clothes()
	{
		return new shoes();
	}
};

class pants_factory:public factory
{
public:
	clothing * produce_clothes()
	{
		return new pants();
	}
};

class shirts_factory:public factory
{
public:
	clothing * produce_clothes()
	{
		return new shirts();
	}
};

int main(int argc,const char * argv[]){
	shoes_factory *shoes_f = new shoes_factory();
	clothing *shoes = shoes_f->produce_clothes();
	if(shoes)
	{
		shoes->show();
	}

	pants_factory *pants_f = new pants_factory();
	clothing *pants = pants_f->produce_clothes();
	if(pants)
	{
		pants->show();
	}

	shirts_factory *shirts_f = new shirts_factory();
	clothing *shirts = shirts_f->produce_clothes();
	if(shirts)
	{
		shirts->show();
	}

	delete shoes_f;
	shoes_f = NULL;
	delete pants_f;
	pants_f = NULL;
	delete shirts_f;
	shirts_f = NULL;
	delete shoes;
	shoes = NULL;
	delete pants;
	pants = NULL;
	delete shirts;
	shirts = NULL;

   return 0;
}
