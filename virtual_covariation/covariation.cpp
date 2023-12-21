#include <iostream>

using namespace std;

// 以自身父子类的指针/引用做返回值
// class Person
// {
// public:
// 	virtual Person* BuyTicket()
// 	{
// 		cout << "virtual Person* BuyTicket()" << endl;
// 		return nullptr;
// 	}
// };
// class Student : public Person
// {
// public:
// 	virtual Person* BuyTicket()
// 	{
// 		cout << "virtual Student* BuyTicket()" << endl;
// 		return nullptr;
// 	}
// };


// 以其他父子类指针/引用做返回值
class A
{};
class B : public A
{};

class Person
{
public:
	virtual A* BuyTicket()
	{
		cout << "virtual A* BuyTicket()" << endl;
		return nullptr;
	}
};
class Student : public Person
{
public:
	virtual B* BuyTicket()
	{
		cout << "virtual B* BuyTicket()" << endl;
		return nullptr;
	}
};

//error
// class Person
// {
// public:
// 	virtual B* BuyTicket()
// 	{
// 		cout << "virtual B* BuyTicket()" << endl;
// 		return nullptr;
// 	}
// };
// class Student : public Person
// {
// public:
// 	virtual A* BuyTicket()
// 	{
// 		cout << "virtual A* BuyTicket()" << endl;
// 		return nullptr;
// 	}
// };

void func(Person* p)
{
	p->BuyTicket();
	cout << endl;
}
int main()
{
	Person p;
	func(&p);

	Student s;
	func(&s);

	return 0;
}
