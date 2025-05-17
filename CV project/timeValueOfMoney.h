
#include "roundingMachine.h"


//Time value of money in finance: 
//1. compound interest: FV = PV * (1 + i) ^ n 
//2. simple interest: FV = PV * (1 + i * n)  
//and it is checked by "bool" variable compound



//future value
//round to 2 digits after decimal
double futureValue (double presentValue, double interestRate, int terms, bool compound) {
    if (compound == true) {
        return rounding(presentValue * (pow((1 + interestRate), terms)), 2); 
    }
    else {
        return rounding(presentValue * (1 + interestRate * terms), 2); 
    }
}

//present value
//round to 2 digits after decimal
double presentValue (double futureValue, double interestRate, int terms, bool compound) {
    if (compound == true) {
        return rounding(futureValue / (pow((1 + interestRate), terms)), 2); 
    }
    else {
        return rounding(futureValue / (1 + interestRate * terms), 2); 
    }
}

//interest rate
//round to 4 digits after decimal
double interestRate (double presentValue, double futureValue, int terms, bool compound) {
    if (compound == true) {
        return rounding(((futureValue / presentValue), (1 / terms)) - 1, 4); 
    }
    else {
        return rounding(((futureValue / presentValue) - 1) / terms, 4); 
    }
}

//number of terms of saving 
//round to integer
int terms (double futureValue, double presentValue, double interestRate, bool compound) {
    if (compound == true) {
        return rounding((futureValue / presentValue) / log(1 + interestRate), 0); 
    }
    else {
        return rounding(((futureValue / presentValue) - 1) / interestRate, 0); 
    }
}

//"effective annual rate"
double EAR (double APR, int terms) {
    return pow((1 + (APR / terms)), terms) + 1; 
}

//loan amortisation: regular payment
double instalmentPayment (double PV, double r, int n) {
    return (PV * r) / (1 - (1.0 / pow((1 + r), n))); 
}

//monthly loan amortisation plan
void amortisation (double PV, double r, int t) {
    double balance = PV; 
    double instalment = rounding(instalmentPayment(PV, r, t), 5); 
    printf("%d\n", instalment); 
    double totalInterest = 0; 
    double totalPayment = 0;  
    printf(" Year | month | Beginning Balance | Instalment Payment | Interest Payment | Principle Repayment | Ending Balance \n"); 
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf(" %4d |   -   |%18d |                    |                  |                     | %14d \n", 0, PV, PV);
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < t; i++) {
        printf(" %4d | %5d |%18f | %18f | %15f  | %18f  | %14f \n", 
                i / 12 + 1, i % 12 + 1, rounding(balance, 2), rounding(instalment, 2), rounding(balance * r, 2), rounding(instalment - balance * r, 2), rounding(balance - instalment + balance * r, 2)); 
        totalInterest += rounding(balance * r, 5);  
        totalPayment += instalment;  
        balance = rounding(balance - instalment + balance * r, 5); 
        printf("-----------------------------------------------------------------------------------------------------------------\n");
    } 
    
    printf("Total instalment payment is: %f\n", rounding(totalPayment, 0)); 
    printf("Total interest Payment: %f\n", rounding(totalInterest, 0)); 
}

void amortisationExtraPayment (double PV, double r, int t, int schedule, double number) {
    double balance = PV; 
    double instalment = rounding(instalmentPayment(PV, r, t), 5); 
    double totalInterest = 0; 
    double totalPayment = 0;  

    switch (schedule) {
        case -1: //yearly extra payment
            printf(" Year | month | Beginning Balance | Instalment Payment | Interest Payment | Principle Repayment | Ending Balance \n"); 
            printf("-----------------------------------------------------------------------------------------------------------------\n");
            printf(" %4d |   -   |%18d |                    |                  |                     | %14d \n", 0, PV, PV);
            printf("-----------------------------------------------------------------------------------------------------------------\n");
            for (int i = 0; i < t; i++) {
                if (i % 12 == 0 && balance <= instalment + number) {
                    printf(" %4d | %5d |%18f | %18f | %15f  | %18f  | %14f \n", 
                        i / 12 + 1, i % 12 + 1, rounding(balance, 2), rounding(balance * (1 + r), 2), rounding(balance * r, 2), rounding(balance, 2), rounding(0, 2)); 
                    totalInterest += rounding(balance * r, 5);  
                    totalPayment += balance * (1 + r); 
                    balance = rounding(balance - instalment + balance * r, 5); 
                    printf("-----------------------------------------------------------------------------------------------------------------\n");
                    printf("The loan will be paid in %d year and %d month\n", i / 12, (i + 1) % 12); 
                    printf("which is in advance of %d year and %d month compared to original plan\n\n", (t - i) / 12, (t - i - 1) % 12); 
                    break; 
                }
                if (balance <= instalment) {
                    printf(" %4d | %5d |%18f | %18f | %15f  | %18f  | %14f \n", 
                        i / 12 + 1, i % 12 + 1, rounding(balance, 2), rounding(balance * (1 + r), 2), rounding(balance * r, 2), rounding(balance, 2), rounding(0, 2)); 
                    totalInterest += rounding(balance * r, 5);  
                    totalPayment += balance * (1 + r); 
                    balance = rounding(balance - instalment + balance * r, 5); 
                    printf("-----------------------------------------------------------------------------------------------------------------\n");
                    printf("The loan will be paid in %d year and %d month\n", i / 12, (i + 1) % 12); 
                    printf("which is in advance of %d year and %d month compared to original plan\n\n", (t - i) / 12, (t - i - 1) % 12); 
                    break; 
                }
                else if (i % 12 == 0) {
                    printf(" %4d | %5d |%18f | %18f | %15f  | %18f  | %14f \n", 
                            i / 12 + 1, i % 12 + 1, rounding(balance, 2), rounding(instalment, 2), rounding(balance * r, 2), rounding(instalment - balance * r + number, 2), rounding(balance - instalment + balance * r - number, 2)); 
                    totalInterest += rounding(balance * r, 5);  
                    totalPayment += instalment + number;  
                    balance = rounding(balance - instalment + balance * r - number, 5); 
                    printf("-----------------------------------------------------------------------------------------------------------------\n");
                }
                else {
                    printf(" %4d | %5d |%18f | %18f | %15f  | %18f  | %14f \n", 
                            i / 12 + 1, i % 12 + 1, rounding(balance, 2), rounding(instalment, 2), rounding(balance * r, 2), rounding(instalment - balance * r, 2), rounding(balance - instalment + balance * r, 2)); 
                    totalInterest += rounding(balance * r, 5);  
                    totalPayment += instalment;  
                    balance = rounding(balance - instalment + balance * r, 5); 
                    printf("-----------------------------------------------------------------------------------------------------------------\n");
                }
            } 
            
            printf("Total instalment payment is: %f\n", rounding(totalPayment, 0)); 
            printf("Total interest Payment: %f\n", rounding(totalInterest, 0)); 

            return; 
        case -2: //monthly extra payment  
            printf(" Year | month | Beginning Balance | Instalment Payment | Interest Payment | Principle Repayment | Ending Balance \n"); 
            printf("-----------------------------------------------------------------------------------------------------------------\n");
            printf(" %4d |   -   |%18d |                    |                  |                     | %14d \n", 0, PV, PV);
            printf("-----------------------------------------------------------------------------------------------------------------\n");
            for (int i = 0; i < t; i++) {
                if (balance <= instalment) {
                    printf(" %4d | %5d |%18f | %18f | %15f  | %18f  | %14f \n", 
                        i / 12 + 1, i % 12 + 1, rounding(balance, 2), rounding(balance * (1 + r), 2), rounding(balance * r, 2), rounding(balance, 2), rounding(0, 2)); 
                    totalInterest += rounding(balance * r, 5);  
                    totalPayment += balance * (1 + r); 
                    balance = rounding(balance - instalment + balance * r, 5); 
                    printf("-----------------------------------------------------------------------------------------------------------------\n");
                    printf("The loan will be paid in %d year and %d month\n", i / 12, (i + 1) % 12); 
                    printf("which is in advance of %d year and %d month compared to original plan\n\n", (t - i) / 12, (t - i - 1) % 12); 
                    break; 
                }
                else {
                    printf(" %4d | %5d |%18f | %18f | %15f  | %18f  | %14f \n", 
                            i / 12 + 1, i % 12 + 1, rounding(balance, 2), rounding(instalment, 2), rounding(balance * r, 2), rounding(instalment - balance * r + number, 2), rounding(balance - instalment + balance * r - number, 2)); 
                    totalInterest += rounding(balance * r, 5);  
                    totalPayment += instalment + number;  
                    balance = rounding(balance - instalment + balance * r - number, 5); 
                    printf("-----------------------------------------------------------------------------------------------------------------\n");
                }
            } 
            
            printf("Total instalment payment is: %f\n", rounding(totalPayment, 0)); 
            printf("Total interest Payment: %f\n", rounding(totalInterest, 0)); 

            return; 
        default: 
            break; 
    }

    printf(" Year | month | Beginning Balance | Instalment Payment | Interest Payment | Principle Repayment | Ending Balance \n"); 
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf(" %4d |   -   |%18d |                    |                  |                     | %14d \n", 0, PV, PV);
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < t; i++) {
        if (balance <= instalment) {
            printf(" %4d | %5d |%18f | %18f | %15f  | %18f  | %14f \n", 
                i / 12 + 1, i % 12 + 1, rounding(balance, 2), rounding(balance * (1 + r), 2), rounding(balance * r, 2), rounding(balance, 2), rounding(0, 2)); 
            totalInterest += rounding(balance * r, 5);  
            totalPayment += balance * (1 + r); 
            balance = rounding(balance - instalment + balance * r, 5); 
            printf("-----------------------------------------------------------------------------------------------------------------\n");
            printf("The loan will be paid in %d year and %d month\n", i / 12, (i + 1) % 12); 
            printf("which is in advance of %d year and %d month compared to original plan\n\n", (t - i) / 12, (t - i - 1) % 12); 
            break; 
        }
        else if (i == schedule) {
            printf(" %4d | %5d |%18f | %18f | %15f  | %18f  | %14f \n", 
                    i / 12 + 1, i % 12 + 1, rounding(balance, 2), rounding(instalment, 2), rounding(balance * r, 2), rounding(instalment - balance * r + number, 2), rounding(balance - instalment + balance * r - number, 2)); 
            totalInterest += rounding(balance * r, 5);  
            totalPayment += instalment + number;  
            balance = rounding(balance - instalment + balance * r - number, 5); 
            printf("-----------------------------------------------------------------------------------------------------------------\n");
        }
        else {
            printf(" %4d | %5d |%18f | %18f | %15f  | %18f  | %14f \n", 
                    i / 12 + 1, i % 12 + 1, rounding(balance, 2), rounding(instalment, 2), rounding(balance * r, 2), rounding(instalment - balance * r, 2), rounding(balance - instalment + balance * r, 2)); 
            totalInterest += rounding(balance * r, 5);  
            totalPayment += instalment;  
            balance = rounding(balance - instalment + balance * r, 5); 
            printf("-----------------------------------------------------------------------------------------------------------------\n");
        }
    } 
    printf("Total instalment payment is: %f\n", rounding(totalPayment, 0)); 
    printf("Total interest Payment: %f\n", rounding(totalInterest, 0)); 
}

//future value of mutiple uneven cashflow 
double compoundingCashFlow (double *cashFlow, int size, int targetYear, double interestRate) {
    double answer = 0;  
    for (int i = 0; i < size; i++) {
        answer += futureValue(cashFlow[i], interestRate, targetYear - i, true);
        printf("%f\n", answer); 
    }

    return answer; 
}

//present value of multiple uneven cashflow
double discountingCashFlow (double *cashFlow, int size, double interestRate) {
    double answer = 0; 
    for (int i = 0; i < size; i++) {
        answer += presentValue(cashFlow[i], interestRate, i, true); 
    }

    return answer; 
}

//future value of annuity
double compoundingAnnuity (double PMT, int targetYear, double interestRate) {
    double answer = 0; 
    for (int i = 0; i < targetYear; i++) {
        answer += futureValue(PMT, interestRate, targetYear - i, true); 
    }

    return answer; 
}

//present value of annuity 
double discountingAnnuity (double PMT, int endingYear, double interestRate) {
    double answer = 0; 
    for (int i = 0; i < endingYear; i++) {
        answer += presentValue(PMT, interestRate, i, true); 
    }

    return answer; 
}

//future value of perpetuity ---> positive infinity

//present value of perpetuity
double discountingPerpetuity (double PMT, double interestRate) {
    return PMT / interestRate; 
}

// instruction of user input!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1


//changing interest model