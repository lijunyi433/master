#include <iostream>

using namespace std;

typedef enum
{
	Shoes,
	Pants,
	Shirts
}cloth_type;

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
	clothing *produce_clothes(cloth_type type)
	{
		switch(type)
		{
			case Shoes : return new shoes(); break;
			case Pants : return new pants(); break;
			case Shirts : return new shirts(); break;
			default : return NULL; break;
		}
	}
};

int main(int argc,const char * argv[]){
	factory f;
	clothing *shoes = f.produce_clothes(Shoes);
	if(shoes)
	{
		shoes->show();
	}

	clothing *pants = f.produce_clothes(Pants);
	if(pants)
	{
		pants->show();
	}

	clothing *shirts = f.produce_clothes(Shirts);
	if(shirts)
	{
		shirts->show();
	}

	delete shoes;
	shoes = NULL;
	delete pants;
	pants = NULL;
	delete shirts;
	shirts = NULL;

   return 0;
}
