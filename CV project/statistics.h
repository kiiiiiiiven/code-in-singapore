#include "riskAndReturn.h"



void statistics () {
    //assume total number of input is less than 100
    //or it could be directly fetching data from a .csv file
    double data[100]; 

    double total = 0; 
    int count = 0; 

    while (1) {
        char input[100]; 
        printf("enter data: "); 
        scanf("%s", input); 

        if (strcmp(input, "done") == 0)
            break; 
        else {
            double number = atof(input);
            data[count] = number; 
            total += number; 
            count++;  
        }
    } 

    double mean = total / count; 
    printf("The mean value of all input data is: %lf\n", rounding(mean, 2)); 

    total = 0; 
    for (int i = 0; i < count; i++) {
        total += pow((data[i] - mean), 2); 
    }

    double variance = total / (count - 1); 
    printf("The variance value of all input data is: %lf\n", rounding(variance, 2)); 

    double SD = pow(variance, 0.5); 
    printf("The standard deviation of all input data is: %lf\n", rounding(SD, 2)); 

    printf("\n"); 
    for (int i = 0; i < count; i++) {
        printf("The mediation score of the %dth data is: %lf\n", i + 1, rounding(data[i] - mean, 1)); 
    }

    int command; 
    printf("to what degree of population score would you like to range?\n "); 
    scanf("%d", &command); 

    if (command == 68) {
        printf("the range of %d percentage of population degree is: [%lf, %lf]\n", command, rounding(mean - SD, 2), rounding(mean + SD, 2)); 
    }
    else if (command == 95) {
        printf("the range of %d percentage of population degree is: [%lf, %lf]\n", command, rounding(mean - SD - SD, 2), rounding(mean + SD + SD, 2)); 
    }
    else if (command == 99) {
        printf("the range of %d percentage of population degree is: [%lf, %lf]\n", command, rounding(mean - SD - SD - SD, 2), rounding(mean + SD + SD + SD, 2)); 
    }
}
