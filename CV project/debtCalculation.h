
#include "timeValueOfMoney.h"

//face value: the amount of money investor will get back at the end of maturity period 
//maturity: the date in the future on which the investor get their originla investment back 

//annual compound formula: PV = C * (1 - (1 + YTM) ^ (-n)) / YTM + (par value) / ((1 + YTM) ^ n)

//for special circumstances like: adjust corresponding terms and interest appropriately 
//semi-annual
//quarterly
//monthly


double costOfBond (int faceValue, double couponRate, int terms, double YTM) {
    double counponPayment = couponRate * faceValue; 
    int n = terms * -1; 

    return rounding(counponPayment * (1 - pow((1 + YTM), n)) / YTM + (faceValue) / pow((1 + YTM), terms), 2); 
}

double debtCalculation () {
    int faceValue, year; 
    double couponRate, YTM; 
    int mode; 

    printf("Enter the face value of your bond: "); 
    scanf("%d", &faceValue); 

    printf("Enter the number of year you will be holding the bond: "); 
    scanf("%d", &year); 

    printf("Enter the coupon rate of your bond: "); 
    scanf("%lf", &couponRate); 

    printf("Enter the YTM (yield-to-maturity) of your bond: "); 
    scanf("%lf", &YTM); 

    while (1) {
        printf("Enter the compound mode of your bond by number\n");
        printf("1. annually\n"); 
        printf("2. semi-annually\n"); 
        printf("3. quarterly\n"); 
        printf("4. monthly\n"); 
        printf("Compound mode: "); 
        scanf("%d", &mode);
        
        switch (mode) {
            case (1): 
                return costOfBond(faceValue, couponRate, year, YTM); 
            case (2): 
                return costOfBond(faceValue, couponRate / 2, year * 2, YTM / 2); 
            case (3): 
                return costOfBond(faceValue, couponRate / 4, year * 4, YTM / 4);
            case (4): 
                return costOfBond(faceValue, couponRate / 12, year * 12, YTM / 12); 
            default: 
                printf("\nInvalid input.\n"); 
                printf("Please try again.\n\n"); 
                break;  
        }
    }
}