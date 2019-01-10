
#include <iostream>
using namespace std;

class Base
{
	public :
		virtual void iam();
};

void Base::iam()
{
          cout << "base" << endl;
}

class One : public Base
{
	public :
		void iam() { cout << "one" << endl; }
		void iam2() {	Base::iam();  }
};

int main()
{
	Base b;  cout << "Calling b.iam() "; b.iam();

	One derived1;

        cout << "Calling derived1.iam() "; derived1.iam();

	Base *d1Ptr  = &derived1;
	d1Ptr -> iam();
}
