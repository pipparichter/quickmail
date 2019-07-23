# include <iostream>
# include <map>
# include <string>
# include <any>

# include "curl/curl.h"


/////////////////////////////////// Defining a URL class ////////////////////////////////////////////////

class URL {
    
    private:

        std::string url;

        CURL* handle = curl_easy_init();
        curl_mime* mime = curl_mime_init(URL::handle);

        std::map<CURLoption, std::any> options;

        built = false;

    public:
        

        // Class constructor
        URL(std::str a_url);
        // Class destructor
        ~URL();
        
        // Member functions for handling options
        void custom_options(std::map<CURLoption, std::any new_options> new_options, bool and_default = true);
        void default_options();
    
        // Member functions for viewing, constructing, and sending the URL
        void view();
        void build();
        CURLcode send();
        
        // Member functions for managing post data
        void add_file(std::string filename);
        void add_data(std::string data);
};


// Defining the class constructor
void URL::URL(std::str a_url) {

    URL::url = a_url; 
}


// Defining the class destructor
void URL::~BuildURL() {

    curl_easy_cleanup(URL::handle);
}


// Include all of the set options in the request
void URL::build() {
    
    URL::built = true;

    for (auto const& pair : URL::options) {
        CURLoption option = pair.first;
        std::any param = pair.second;
        curl_easy_setopt(URL::handle, option, param);
    }    
}


// Pretty much just a wrapper for curl_easy_perform
CURLcode URL::send() {
    
    std::string proceed = "y";

    if built == false {
        std::cout << "WARNING: Latest updates have not yet been applied to the URL \n";
        std::cout << "Would you like to proceed? (y/n): ";
        std::cin >> proceed;
        std::cout << "\n";
    }

    if (proceed == "y") {
        // If all goes well, the return should be CURLE_OK (0)
        return curl_easy_perform(URL::handle);
    } 
    // Default to cancelling the send, even if "n" wasn't entered
    else {
        std::cout << "Send cancelled \n";
        // Make sure to include something about this in main.cpp... this could potentially be misleading,
        // as it wasn't so much 'send error' as 'send aborted by user'
        return CURLcode 55; // CURLE_SEND_ERROR
    }
}


// A wrapper which resets the URL to the defaults I want
void URL::default_options() {

    URL::built = false;

    URL::options = {
        {CURLOPT_URL, URL::url}
    };
    
    URL::view();
}

// Allows the user to input a map containing preferred options
void URL::custom_options(std::map<CURLoption, std::any> new_options, bool and_default = true) {
    
    if and_default {
        URL::default_options();
        for (auto const& key : new_options) {
            try URL::options.at(key) {
                // Do nothing if the option is already in the default
                ;
            }
            catch (std::out_of_range) {
                URL::options[key] = new_options[key];            
            }
        }
    }
    // If the user specifies that the default parameters should not be included, the URL options
    // are set equal to the function input
    else {
        URL::options = new_options;
    }
}


// View the URL, as well as the options and their associated parameters
void URL::view() {
    
    // If the URL is not built, print a warning
    if (built == false) {
        std::cout << "WARNING: Latest updates have not yet been applied to the URL \n"
    }
    
    std::cout << "URL: " << URL::url << "\n";
    std::cout << "Options: " << "\n";
        
    for (auto const& pair : URL::options) {
        std::cout << pair.first << " " << pair.second << "\n";
    }
}


