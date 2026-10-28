
#include <iostream>
using namespace std;

class Acc {
protected:
    double b;

public:
    Acc(double x) {
        b = x;
    }

    virtual void sm(double a) {
        if (a > 0 && a <= b) {
            b -= a;
            cout << "Money sent\n";
        } else {
            cout << "Invalid amount or low balance\n";
        }
    }

    virtual void rm(double a) {
        if (a > 0) {
            b += a;
            cout << "Money received\n";
        } else {
            cout << "Invalid amount\n";
        }
    }

    void sb() {
        cout << "Balance: Rs. " << b << endl;
    }

    virtual ~Acc() {}
};

class CAcc : public Acc {
    bool h;

public:
    CAcc(double x, bool y) : Acc(x) {
        h = y;
    }

    void sm(double a) override {
        if (h)
            cout << "Account flagged, sending allowed for demo\n";

        Acc::sm(a);
    }

    void rm(double a) override {
        if (h)
            cout << "Account flagged, receiving blocked\n";
        else
            Acc::rm(a);
    }

    void cb() {
        h = false;
        cout << "Account cleared after enquiry\n";
    }
};

int main() {
    CAcc c1(5000, true);

    // Upcasting
    Acc *ptr = &c1;

    cout << "Account flagged:\n";
    ptr->sb();
    ptr->sm(1000);
    ptr->rm(500);

    // Downcasting
    cout << "\nAfter enquiry:\n";

    CAcc *p = dynamic_cast<CAcc*>(ptr);

    if (p != nullptr)
        p->cb();

    ptr->sm(500);
    ptr->rm(1000);
    ptr->sb();

    return 0;
}
