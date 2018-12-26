#include <iostream>
#include <string>

using namespace std;

class Window
{
public:
	Window(string str):name(str) {cout << "Window()" << endl;}
	void setName(string str) { name = str; }
	~Window() {cout << "~Window()" << endl;}
	Window(Window& w)
	{
		cout << "Window(window& w)" << endl;
		name = w.name;
		name += "-w";
	}
	virtual void display() const {cout << "Window dispaly: " << name << endl;}

	string name;
};

class WindowWithScrollBars: public Window
{
public:
	WindowWithScrollBars(string str):Window(str) { setName(str); cout << "WindowWithScrollBars()" << endl; }

	~WindowWithScrollBars() {cout << "~WindowWithScrollBars()" << endl;}

	WindowWithScrollBars(WindowWithScrollBars& w): Window(w)
	{
		cout << "WindowWithScrollBars(WindowWithScrollBars& w)" << endl;
		name = w.name;
		name += "-ws";
	}
	virtual void display() const {cout << "WindowWithScrollBars display: " << name << endl;}
};

void printNameAndDisplay(Window& w)
{
	cout << w.name<< endl;
	w.display();
}

int main()
{
	WindowWithScrollBars ws("charlie");

	printNameAndDisplay(ws);

}

