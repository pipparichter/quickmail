# include <curl/curl.h>
# include <iostream>

curl_global_init(CURL_GLOBAL_ALL);


int main() {
    CURL* handle = curl_easy_init();
    CURLcode result;
    // Make sure the handle pointer was correctly assigned
    if (handle) {
        // Setting options for request
        std::str options = {CURLOPT}
    
        curl_easy_setopt(handle, );
        curl_easy_setopt();

        curl_easy_cleanup();
    
}

