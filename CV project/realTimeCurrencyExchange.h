#include <curl/curl.h?>
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

    char *temp = (char *)realloc(mem->response, mem->size + totalSize + 1);
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

void realCurrencyExchange() {
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