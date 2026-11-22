class EmergencyBill : public Bill {
    double emergencyCharge;
    double treatmentCharge;

public:
    EmergencyBill(const string& p, double e, double t)
        : Bill(p), emergencyCharge(e), treatmentCharge(t) {}

    double total() const override {
        return emergencyCharge + treatmentCharge;
    }

    string type() const override {
        return "Emergency";
    }
};


EmergencyBill emergency("Arun", 5000, 15000);
CorporateTieUp corporate;

cout << emergency.type() << " Bill: "
     << emergency.total() << endl;

cout << "Corporate Coverage: "
     << corporate.amountCovered(emergency) << endl;
