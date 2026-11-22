ALGORITHM ProcessAllBills

BEGIN

    totalAmount ← 0

    FOR each bill in bills DO

        bill.print()

        totalAmount ← totalAmount + bill.total()

    END FOR

    DISPLAY "Total Hospital Billing Amount:", totalAmount

END

  struct Bill {
    int type;
    double amount1, amount2, amount3;

    double total() {
        switch(type) {
            case 1:
                return amount1 + amount2;

            case 2:
                return amount1 + amount2 + amount3;

            case 3:
                return amount1;

            case 4:
                return amount1 + amount2;

            default:
                return 0;
        }
    }
};



