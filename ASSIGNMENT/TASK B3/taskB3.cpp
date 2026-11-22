#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

struct Bill {
    int type;
    double a, b;
};

double switchTotal(const Bill& bill) {
    switch (bill.type) {
        case 1: return bill.a + bill.b;
        case 2: return bill.a * bill.b;
        default: return 0;
    }
}

class BaseBill {
public:
    virtual double total() const = 0;
    virtual ~BaseBill() = default;
};

class OPBill : public BaseBill {
    double consultation, tests;
public:
    OPBill(double c, double t) : consultation(c), tests(t) {}
    double total() const override {
        return consultation + tests;
    }
};

class IPBill : public BaseBill {
    double days, rate;
public:
    IPBill(double d, double r) : days(d), rate(r) {}
    double total() const override {
        return days * rate;
    }
};

int main() {
    int sizes[] = {1000, 1000000, 10000000};

    for (int n : sizes) {
        vector<Bill> bills;
        vector<OPBill> op;
        vector<IPBill> ip;
        vector<BaseBill*> ptr;

        bills.reserve(n);
        op.reserve(n);
        ip.reserve(n);
        ptr.reserve(n);

        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                bills.push_back({1, 500, 1200});
                op.emplace_back(500, 1200);
            } else {
                bills.push_back({2, 3, 2500});
                ip.emplace_back(3, 2500);
            }
        }

        // Create polymorphic objects
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0)
                ptr.push_back(&op[i / 2]);
            else
                ptr.push_back(&ip[i / 2]);
        }

        double sum1 = 0, sum2 = 0;

        auto start1 = high_resolution_clock::now();

        for (const Bill& b : bills)
            sum1 += switchTotal(b);

        auto end1 = high_resolution_clock::now();

        auto start2 = high_resolution_clock::now();

        for (BaseBill* b : ptr)
            sum2 += b->total();

        auto end2 = high_resolution_clock::now();

        cout << "\nBills: " << n << '\n';
        cout << "Switch total: " << sum1 << '\n';
        cout << "Virtual total: " << sum2 << '\n';

        cout << "Switch time: "
             << duration_cast<milliseconds>(end1-start1).count()
             << " ms\n";

        cout << "Virtual time: "
             << duration_cast<milliseconds>(end2-start2).count()
             << " ms\n";
    }
}


#include <iostream>
#include <chrono>
#include <stdexcept>
using namespace std;
using namespace chrono;

bool validateReturn(bool invalid) {
    return !invalid;
}

bool validateException(bool invalid) {
    if (invalid)
        throw runtime_error("Invalid bill");

    return true;
}

int main() {
    const int N = 1000000;

    int percentages[] = {0, 1, 50};

    for (int p : percentages) {
        int invalidCount = N * p / 100;

        auto start1 = high_resolution_clock::now();

        int valid1 = 0;

        for (int i = 0; i < N; i++) {
            bool invalid = i < invalidCount;

            if (validateReturn(invalid))
                valid1++;
        }

        auto end1 = high_resolution_clock::now();

        auto start2 = high_resolution_clock::now();

        int valid2 = 0;

        for (int i = 0; i < N; i++) {
            bool invalid = i < invalidCount;

            try {
                if (validateException(invalid))
                    valid2++;
            }
            catch (const exception&) {
                // Invalid bill handled
            }
        }

        auto end2 = high_resolution_clock::now();

        cout << "\nInvalid bills: " << p << "%\n";

        cout << "Return code time: "
             << duration_cast<milliseconds>(end1-start1).count()
             << " ms\n";

        cout << "Exception time: "
             << duration_cast<milliseconds>(end2-start2).count()
             << " ms\n";

        cout << "Valid bills: " << valid1 << " and " << valid2 << '\n';
    }
}


