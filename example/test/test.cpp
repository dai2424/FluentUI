#include <iostream>

using namespace std;

class Base {
protected:
    virtual void dowork() {
        cout << "Base" << endl;
    }
public:
    void start() {
        dowork();
    }
};

class Derive : public Base {
protected:
    void dowork() {
        cout << "Derive" << endl;
    }
};

int main() {

    Base *b1 = new Derive();
    b1->start();

    Derive *d1 = new Derive();
    d1->start();
    return 0;
}