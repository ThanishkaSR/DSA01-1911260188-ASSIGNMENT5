class Payer {
public:
    virtual double amountCovered(const Bill& bill) const = 0;
    virtual ~Payer() = default;
};

class SelfPay : public Payer {
public:
    double amountCovered(const Bill& bill) const override;
};

class Insurance : public Payer {
private:
    double coverLimit;
    double coPaymentPercentage;

public:
    double amountCovered(const Bill& bill) const override;
};

class GovernmentScheme : public Payer {
public:
    double amountCovered(const Bill& bill) const override;
};

class CorporateTieUp : public Payer {
public:
    double amountCovered(const Bill& bill) const override {
        return bill.total() * 0.80;
    }
};

double selfPay(const Bill& b) {
    return b.total();
}

double insurancePay(const Bill& b) {
    return b.total() * 0.80;
}

double governmentPay(const Bill& b) {
    return b.total() * 0.60;
}
