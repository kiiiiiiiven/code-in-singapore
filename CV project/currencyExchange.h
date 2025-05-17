#include "statistics.h"

#define NUMBER_OF_COUNTRY 150

struct exchangeRate {
    char currencyName[100]; 
    char currencyCode[3]; 
    double rate; 
}; 

void currencyExchange () {
    //read the .csv file 
    FILE * file = fopen("CurrencyExchangeRate.csv", "r"); 

    //use created data structure to store all the exchange rates read from the file
    struct exchangeRate rates[NUMBER_OF_COUNTRY]; 

    //a large enough string to store every line in the .csv file
    char line[1000]; 

    //read the first line (title line) in .csv file
    fgets(line, 1000, file); 

    //store all the data in format of created structure
    for (int i = 0; i < 150; i++) {
        //skip the first column (index)
        fgets(line, 1000, file); 
        char * token = strtok(line, ","); 

        //the second column (currency name with country name)
        token = strtok(NULL, ","); 
        strcpy(rates[i].currencyName, token); 

        //the third column (currencyCode)
        token = strtok(NULL, ","); 
        strcpy(rates[i].currencyCode, token); 

        //the fourth column (rate)
        token = strtok(NULL, ","); 
        rates[i].rate = atof(token); 
    }

    //close the file
    fclose(file); 

    char base[4], target[4];
    double base1 = 0.0, target1 = 0.0; 
    printf("Enter the currency you are holding (in Currency Code Name): "); 
    scanf("%s", base); 
    base[3] = '\0'; 
    printf("Enter the target currency you wish to exchange (in Currency Code Name): "); 
    scanf("%s", target); 
    target[3] = '\0'; 
    
    for (int i = 0; i < NUMBER_OF_COUNTRY; i++) {
        if (strcmp(rates[i].currencyCode, base) == 0)
            base1 = rates[i].rate; 
        if (strcmp(rates[i].currencyCode, target) == 0)
            target1 = rates[i].rate; 
        if (base1 != 0.0 && target1 != 0.0)
            break; 
    }

    if (base1 != 0.0 && target1 != 0.0){
        printf("the exchange rate from base currency (%s) to target currency (%s) is: %lf\n", base, target, rounding(target1 / base1, 5)); 
        printf("meaning 1 %s is equivalent to %lf %s\n", base, rounding(target1 / base1, 5), target); 
    }
    else {
        printf("Please double check the country code name. \n"); 
        currencyExchange(); 
    }
}
























































































/*
#include <curl/curl.h>
//installation required ---> cur.se
// Buffer to store API response
struct Memory {
    char *response;
    size_t size;
};

// Callback function to write response data
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t totalSize = size * nmemb;
    struct Memory *mem = (struct Memory *)userdata;

    char *temp = realloc(mem->response, mem->size + totalSize + 1);
    if (temp == NULL) {
        printf("Error reallocating memory\n");
        return 0;
    }

    mem->response = temp;
    memcpy(&(mem->response[mem->size]), ptr, totalSize);
    mem->size += totalSize;
    mem->response[mem->size] = '\0';

    return totalSize;
}

// Function to fetch exchange rate from API
double get_exchange_rate(const char *base_currency, const char *target_currency) {
    CURL *curl;
    CURLcode res;
    struct Memory chunk = {NULL, 0};
    
    char url[256];
    snprintf(url, sizeof(url), "https://api.exchangerate-api.com/v4/latest/%s", base_currency);

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);
        
        res = curl_easy_perform(curl);
        
        if (res != CURLE_OK) {
            fprintf(stderr, "Failed to fetch exchange rates: %s\n", curl_easy_strerror(res));
            return -1.0;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    // Parse JSON response to extract the exchange rate
    char *rate_pos = strstr(chunk.response, target_currency);
    if (rate_pos) {
        double exchange_rate;
        sscanf(rate_pos, "%*[^:]:%lf", &exchange_rate);
        free(chunk.response);
        return exchange_rate;
    }

    free(chunk.response);
    return -1.0; // Return error code if rate not found
}

void currencyExchange() {
    char base[4] = "USD";
    char target[4] = "EUR";
    
    double rate = get_exchange_rate(base, target);
    if (rate > 0) {
        printf("Exchange rate (%s to %s): %.2f\n", base, target, rate);
    } 
    else {
        printf("Failed to retrieve exchange rate.\n");
    }
}
*/