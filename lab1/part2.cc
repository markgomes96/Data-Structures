/*
 *Mark Gomes
 *CSC 310 - 1/15/19
 *Program explores use of inheritance and polymorphism
 */

#include <iostream>
#include <string>

using namespace std;

class Base      //base class
{
    public :
        virtual void iam();
};

void Base::iam()
{
    cout << "Base" << endl;
}

class Base1 : public Base   //1st class derived from base
{
    public :
        void iam();
        void iam2();
};

void Base1::iam()
{
    cout << "Base1" << endl;
}

void Base1::iam2()
{
    Base::iam();
}

class Base2 : public Base   //2nd class derived from base
{
    public :
        void iam();
        void iam2();
};

void Base2::iam()
{
    cout << "Base2" << endl;
}

void Base2::iam2()
{
    Base::iam();
}

int main(int argc, char *argv[])
{
    Base1 b1;       //objects of two classes derived from base
    Base2 b2;

    b1.iam();
    b1.iam2();

    b2.iam();
    b2.iam2();

    Base *bp;
    bp = &b1;       //pointing to 1st derived class
    bp -> iam();

    bp = &b2;       //pointing to 2nd derived class
    bp -> iam();

    return 0;
}
