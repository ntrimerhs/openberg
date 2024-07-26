#include <stdlib.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <cstring>
#include <curl/curl.h>
using namespace std;

int main() {
   system("clear");
   
   cout <<R"(

 _____                          __                               
/\  __`\                       /\ \                              
\ \ \/\ \  _____      __    ___\ \ \____     __   _ __    __     
 \ \ \ \ \/\ '__`\  /'__`\/' _ `\ \ '__`\  /'__`\/\`'__\/'_ `\   
  \ \ \_\ \ \ \L\ \/\  __//\ \/\ \ \ \L\ \/\  __/\ \ \//\ \L\ \  
   \ \_____\ \ ,__/\ \____\ \_\ \_\ \_,__/\ \____\\ \_\\ \____ \ 
    \/_____/\ \ \/  \/____/\/_/\/_/\/___/  \/____/ \/_/ \/___L\ \
             \ \_\                                        /\____/
              \/_/                                        \_/__/ 
 ______                                                ___       
/\__  _\                          __                  /\_ \      
\/_/\ \/    __   _ __    ___ ___ /\_\    ___      __  \//\ \     
   \ \ \  /'__`\/\`'__\/' __` __`\/\ \ /' _ `\  /'__`\  \ \ \    
    \ \ \/\  __/\ \ \/ /\ \/\ \/\ \ \ \/\ \/\ \/\ \L\.\_ \_\ \_  
     \ \_\ \____\\ \_\ \ \_\ \_\ \_\ \_\ \_\ \_\ \__/.\_\/\____\ 
      \/_/\/____/ \/_/  \/_/\/_/\/_/\/_/\/_/\/_/\/__/\/_/\/____/ 
 
-Developed by M. Drimeris-)" << endl;

int i = 0;
system("touch .stock.txt");
string api = "generic709.herokuapp.com/stockc/";
//REPLACE THE FOLLOWING ARRAY WITH YOU FAVORITE STOCKS IN THIS EXACT ORDER 
string tickers[] = {
  "AAPL",
  "ABBV",
  "BA",
  "BABA",
  "BAC",
  "BAX",
  "BBY",
  "BDX",
  "BIDU",
  "BIIB",
  "BMY",
  "BP",
  "BRK.A",
  "BRK.B",
  "BSX",
  "C",
  "CL",
  "DIS",
  "EA",
  "F",
  "GM",
  "GS",
  "HD",
  "IBM",
  "JNJ",
  "KO",
  "LMT",
  "LOW",
  "META",
  "MSFT",
  "NFLX",
  "NKE",
  "NOK",
  "NVDA",
  "ORCL",
  "OXY",
  "PFE",
  "PG",
  "PYPL",
  "QCOM",
  "RBLX",
  "REGN",
  "SBUX",
  "SHOP",
  "SQ",
  "T",
  "TSLA",
  "U",
  "UNH",
  "V",
  "VZ",
  "WMT",
  "XOM",
  "ZM"
};

auto tinSize = sizeof(tickers);

CURL * curl;
CURLcode result;
curl_global_init(CURL_GLOBAL_DEFAULT);
curl = curl_easy_init();
do {
  cout << "Please Select an Option [0-9]" << endl;
  cout << "1. Enter a Symbol" << endl;
  cout << "2. Favorite Stocks" << endl;
  cout << "3. Exit" << endl;
  cout << "-More Options Coming Soon-" << endl;
  int input;
  cin >> input;
  if (input == 3) {
    cout << "Goodbye!" << endl;
    return 0;
    system("rm .stock.txt");
  }
  while(input == 1){  
    system("clear");
    cout << "Please Type the Stock's Symbol. Example AAPL" << endl;
    string symbol;
    cin >> symbol;
    ofstream chart_stock;
    chart_stock.open(".stock.txt", ios::out | ios::trunc);
    chart_stock << symbol;
    chart_stock.close();
    string url = api + symbol;
    const char * stock = url.data();

    if (curl) {
      curl_easy_setopt(curl, CURLOPT_URL, stock);
      string resultBody { };
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resultBody);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, static_cast<size_t (*) (char*, size_t, size_t, void*)>(
         [](char* ptr, size_t size, size_t nmemb, void* resultBody){
            *(static_cast<std::string*>(resultBody)) += std::string {ptr, size * nmemb};
            return size * nmemb;
          }
      ));
      result = curl_easy_perform(curl);
      string rebody = resultBody.substr(7,8);
      cout << "\033[36m" << symbol << " " << "\033[33m" <<  rebody << "\033[0m" << endl;
      cout << "Choose an option [1-3]" << endl;
      cout << "1. See Chart for this Symbol." << endl;
      cout << "2. Look at Another Symbol" << endl;
      cout << "3. Go Back" << endl;
      int ans;
      cin >> ans;
      if(ans==1){
        system("clear");
        cout << "Preparing Chart..." << endl;
        system("python3 chart.py");
        while (cin.get() != '\n');
        system("clear");
        break;
      }
      else if(ans == 3){
          break;
          system("rm .stock.txt");
      }
    }
  }
    if (input == 2) {
      system("clear");
      while (i < tinSize) {

        string url = api + tickers[i];
        const char * stock = url.data();
    if (curl) {
      curl_easy_setopt(curl, CURLOPT_URL, stock);
      string resultBody { };
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resultBody);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, static_cast<size_t (*) (char*, size_t, size_t, void*)>(
         [](char* ptr, size_t size, size_t nmemb, void* resultBody){
            *(static_cast<std::string*>(resultBody)) += std::string {ptr, size * nmemb};
            return size * nmemb;
          }
      ));
      result = curl_easy_perform(curl);
      string rebody = resultBody.substr(7,8);
      cout << "\033[36m" << tickers[i] << " " << "\033[33m" <<  rebody << "\033[0m" << endl;
        }
        i++;
      }
    } else {
      cout << "Option not recognised" << endl;
      system("rm .stock.txt");
    }
  }
while(true);
curl_global_cleanup();
return 0;
system("rm .stock.txt");
}