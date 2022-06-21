// https://www.bogotobogo.com/cplusplus/dynamic_cast.php


// We practice runtime type identification, which allow us to determine the type of object during runtime
// RTTI allow program that use pointer or reference to base classes to retrieve the actual derived types of the object 
// to wich these pointers or references refer


// We need dynamic_cast when we want to perform derived class operation 
// on a derived class object, but we have only a pointer order reference-to-base

// In this example, we create a base class Window, derived class ScrollWindow

#include <iostream>
#include <string>
using namespace std;

class Window
{
public:
	Window(){}
	Window(const string s):name(s) {};
	virtual ~Window() {};
	void getName() { cout << name << endl;};
private:
	string name;
};

class ScrollWindow : public Window
{
public:
	ScrollWindow(string s) : Window(s) {};
	~ScrollWindow() {};
	void scroll() { cout << "scroll()" << endl;};
};

void DoSomething(Window *w)
{
	w->getName();
	// w->scroll();  // class "Window" has no member scroll

	// check if the pointer is pointing to a scroll window
	ScrollWindow *sw = dynamic_cast<ScrollWindow*>(w);

	// if not null, it's a scroll window object
	if(sw)
    {
        sw->scroll();
        cout<<"Cast successfully"<<endl;
    }
    else
    {
        cout<<"Can't cast"<<endl;
    }
    
}

int main()
{
	Window *w = new Window("plain window");
	ScrollWindow *sw = new ScrollWindow("scroll window");

	DoSomething(w);
	DoSomething(sw);

    delete w;
    delete sw;

	return 0;
}