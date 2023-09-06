#include <iostream>

using namespace std;

class Base {
protected:
    virtual void dowork() {
        cout << "Base" << endl;
    }

public:
    Base() {
        cout << "Base construct" << endl;
    }

    virtual ~Base() {
         cout << "Base deConstruct" << endl;
    }
    void start() {
        dowork();
    }
};

class Derive : public Base {
protected:
    void dowork() {
        cout << "Derive" << endl;
    }

public:
    Derive() {
        cout << "Derive construct" << endl;
    }

    ~Derive() {
         cout << "Derive deConstruct" << endl;
    }
};

int main() {
    Base *b1 = new Derive();
    delete b1;

    Derive *d1 = new Derive();
    delete d1;
    return 0;
}