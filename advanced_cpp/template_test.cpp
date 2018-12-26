#include <iostream>

using namespace std;

struct Job
{
	double salary;
	int floor;
};

typedef struct Job job;


template <typename T>
void myswap(T &a, T &b)
{
	cout << "template swap" << endl;
	T temp;
	temp = a;
	a = b;
	b = temp;
}

template<> 
void myswap<job>(job &a, job &b)
{
	double temp;
	temp = 	a.salary;
	a.salary = b.salary;
	b.salary = temp;
}

template<>
void myswap<int>(int &a, int &b)
{
	cout << "speical for int" << endl;
	int tmp;
	tmp = b + 1;
	a = b + 1;
	b = tmp;
}


int main()
{
	job a{100,5}, b{200,10};

	cout << "salary = " << a.salary << endl;
	myswap(a, b);
	cout << "salary = " << a.salary << endl;


	int ia = 10, ib = 20;
	cout << "ia = " << ia << " ib = " << ib << endl;
	myswap(ia, ib);
	cout << "ia = " << ia << " ib = " << ib << endl;
}
