#include <iostream>

using namespace std;

class accessory_factory
{
public:
	virtual ~accessory_factory(){}
	virtual void produce_screen() = 0;
	virtual void produce_motor() = 0;
	virtual void produce_shell() = 0;
	virtual void produce_sound() = 0;
};

class accessory_factory_A:public accessory_factory
{
public:
	void produce_screen()
	{
		cout << "a screen object from accessory factory A" << endl;
	}
	void produce_motor()
	{
		cout << "a motor object accessory factory A" << endl;
	}
	void produce_shell()
	{
		cout << "can not produce shell accessory factory A" << endl;
	}
	void produce_sound()
	{
		cout << "can not produce sound accessory factory A" << endl;
	}
};

class accessory_factory_B:public accessory_factory
{
public:
	void produce_motor()
	{
		cout << "a motor object accessory factory B" << endl;
	}
	void produce_screen()
	{
		cout << "a screen object accessory factory B" << endl;
	}
	void produce_shell()
	{
		cout << "can not produce shell accessory factory B" << endl;
	}
	void produce_sound()
	{
		cout << "can not produce sound accessory factory B" << endl;
	}
};

class accessory_factory_C:public accessory_factory
{
public:
	void produce_screen()
	{
		cout << "can not produce screen accessory factory C" << endl;
	}
	void produce_motor()
	{
		cout << "can not produce motor accessory factory C" << endl;
	}
	void produce_shell()
	{
		cout << "a shell object accessory factory C" << endl;
	}
	void produce_sound()
	{
		cout << "a sound object accessory factory C" << endl;
	}
};

class phone_factory
{
private:
	accessory_factory *a_f;
	accessory_factory *b_f;
public:
	phone_factory(accessory_factory *f1, accessory_factory *f2)
	{
		a_f = f1;
		b_f = f2;
	}
	~phone_factory(){}
	void assemble_phone()
	{
		a_f->produce_screen();
		a_f->produce_motor();
		b_f->produce_shell();
		b_f->produce_sound();
	}
};

int main(int argc,const char * argv[]){
	accessory_factory_A *f1 = new accessory_factory_A();
	accessory_factory_B *f2 = new accessory_factory_B();
	accessory_factory_C *f3 = new accessory_factory_C();

	phone_factory *huawei = NULL;
	phone_factory *xiaomi = NULL;

	if(f1 && f3)
	{
		huawei = new phone_factory(f1, f3);
	}
	
	if(f2 && f3)
	{
		xiaomi = new phone_factory(f2, f3);
	}

	if(huawei)
	{
		huawei->assemble_phone();
	}

	if(xiaomi)
	{
		xiaomi->assemble_phone();
	}
	
	delete f1;
	f1 = NULL;
	delete f2;
	f2 = NULL;
	delete f3;
	f3 = NULL;
	delete huawei;
	huawei = NULL;
	delete xiaomi;
	xiaomi = NULL;

   return 0;
}
