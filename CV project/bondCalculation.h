#include "debtCalculation.h"

//common stock: 
//1. "The Gorden Growth Model" ---> constant dividends growth 
//2. zero growth in dividend
//3. growth phsae model 

//perfered stock

double dividendGrowth (double dividend, double growthRate, int year) {
    return rounding(dividend * pow((1 + growthRate), year), 5); 
}

double commonStock (double dividend0, double rateOfReturn, double growthRate1) {
    double dividend1 = dividendGrowth(dividend0, growthRate1, 1); 
    if (growthRate1 == 0)
        return rounding(dividend1 / rateOfReturn, 2); 
    else 
        return rounding(dividend1 / (rateOfReturn - growthRate1), 2); 
}

double growthModel (double dividend0, double rateOfReturn, double growthRate1, int duration, double growthRate2) {
    double answer = 0.0; 
    for (int i = 1; i <= duration; i++) {
        answer += (dividendGrowth(dividend0, growthRate1, i) / (pow((1 + rateOfReturn), i))); 
    }

    printf("%lf\n", answer); 
    return rounding(answer + dividendGrowth(dividendGrowth(dividend0, growthRate1, duration), growthRate2, 1) / pow((1 + rateOfReturn), duration) / (rateOfReturn - growthRate2), 2); 
}

double preferredStock (double dividend0, double rateOfReturn) {
    return dividend0 / rateOfReturn; 
}