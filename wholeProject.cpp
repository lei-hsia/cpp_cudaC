#define _CRT_SECURE_NO_WARNINGS
/* #include "curl.h"
#include "Stock.h"
#include "StockDic.h"
#include "Calculation.h"
#include "gnuplot.h"
#include "Matrix.h" */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <iterator>
#include <vector>
#include <list>
#include <iomanip>
#include <locale>
#include <algorithm>
#include <random>


using namespace std;


// Stock.h
class Stock{
    string ticker;
    string name;
    string announcement_date;
    double surprise;
    map<string,double> price_lst;
    vector<double> AR;
public:
    Stock(string n, string t, string d, double s){
        name = n;
        ticker = t;
        announcement_date = d;
        surprise = s;
    }
    double get_surprise(){
        return surprise;
    }
    string get_ticker(){
        return ticker;
    }
    string get_date(){
        return announcement_date;
    }
    string get_name(){
        return name;
    }
    map<string,double> get_price_lst(){
        return price_lst;
    }
    void set_price_lst(map<string,double> lst){
        price_lst = lst;
    }
    vector<double> get_AR(){
        return AR;
    }
    void set_AR(vector<double> AR_){
        AR = AR_;
    }
};




// Matrix.cpp
typedef vector<double> Vector;
typedef vector<Vector> Matrix;

Vector operator*(const Matrix& C,const Vector& V)
{
   unsigned long d = C.size();
   Vector W(d);
   for (int j=0; j<d; j++)
   {
      W[j]=0.0;
      for (int l=0; l<d; l++) W[j]=W[j]+C[j][l]*V[l];
   }
   return W;
}

Vector operator+(const Vector& V,const Vector& W)
{
   unsigned long d = V.size();
   Vector U(d);
   for (int j=0; j<d; j++) U[j] = V[j] + W[j];
   return U;
}

Vector operator+(const double& a,const Vector& V)
{
   unsigned long d = V.size();
   Vector U(d);
   for (int j=0; j<d; j++) U[j] = a + V[j];
   return U;
}

Vector operator*(const double& a,const Vector& V)
{
   unsigned long d = V.size();
   Vector U(d);
   for (int j=0; j<d; j++) U[j] = a*V[j];
   return U;
}

Vector operator*(const Vector& V,const Vector& W)
{
   unsigned long d = V.size();
   Vector U(d);
   for (int j=0; j<d; j++) U[j] = V[j] * W[j];
   return U;
}

Vector exp(const Vector& V)
{
   unsigned long d = V.size();
   Vector U(d);
   for (int j=0; j<d; j++) U[j] = exp(V[j]);
   return U;
}

double operator^(const Vector& V,const Vector& W)
{
   double sum = 0.0;
   unsigned long d = V.size();
   for (int j=0; j<d; j++) sum = sum + V[j]*W[j];
   return sum;
}

ostream & operator<<(ostream & out, Vector & V)
{
    for (Vector::iterator itr= V.begin(); itr != V.end(); itr++)
        out << *itr << "   ";
    out << endl;
    return out;
}

ostream & operator<<(ostream & out, vector<int> & V)
{
    for (vector<int>::iterator itr = V.begin(); itr != V.end(); itr++)
        out << *itr << "   ";
    out << endl;
    return out;
}

ostream & operator<<(ostream & out, Matrix & W)
{
    for (Matrix::iterator itr= W.begin(); itr != W.end(); itr++)
        out << *itr;
    out << endl;
    return out;
}





// Calculation.cpp
//Generate a set of 30 different random stocks  of each group
vector<Stock* > random_generator(vector<Stock *> group) {
    vector<int> a;
    int size = group.size();
    for (int i = 0; i < size; i++)
        a.push_back(i);
    srand(time(NULL));
    //random_shuffle(a.begin(), a.end());
    //vector<int> top_30(a.begin(), a.begin() + 30);
    vector<int> top_30(30);
    int temp;
    for (int i = 0; i < 30; i++) {
        temp = rand() % (a.size()-i);
        top_30[i] = a[temp];
        a[temp] = a[a.size() - 1 - i];
    }
    
    cout << top_30 << endl << endl;
    vector<Stock *> selected;
    for (int i = 0; i < top_30.size(); i++) {
        selected.push_back(group[top_30[i]]);
    }
    return selected;
}

//Calculate AAR using AR of selected stocks
vector<double> AAR(vector<Stock *> selected) {
    vector<double> aar(120);
    for (int t = 0; t < 120; t++) {
        aar[t] = 0.0;
    }
    for (int i = 0; i < selected.size(); i++){
        aar = aar + selected[i]->get_AR();
    }
    aar =  (1/(double)selected.size()) * aar;
    return aar;
}

//Calculate CAAR using AAR
vector<double> CAAR(vector<double> aar) {
    vector<double> caar(120);
    caar[0] = aar[0];
    for (int t = 1; t < 120; t++) {
        caar[t] = caar[t - 1] + aar[t];
    }
    return caar;
}

//Calculate average CAAR of 30 samples
vector<double> averageCAAR(vector<Stock *> group) {
    vector<double> AverCAAR(120);
    for (int t = 0; t < 120; t++) {
        AverCAAR[t] = 0.0;
    }
    for (int i = 0; i < 30; i++) {
        srand(time(NULL));
        vector<Stock *> selected = random_generator(group);
        vector<double> aar = AAR(selected);
        vector<double> caar = CAAR(aar);
        AverCAAR = AverCAAR + caar;
    }
    AverCAAR = (1.0/30.0) * AverCAAR;
    return AverCAAR;
}



// gnuplot.cpp
//Please input data in the sequence of miss, meet, beat
int plotResults(vector<double> yData1, vector<double> yData2, vector<double> yData3) {
    int dataSize = 120;
    FILE *gnuplotPipe, *tempDataFile;
    //String of legends
    const char *tempDataFileName1 = "Average CAAR for Miss Group";
    const char *tempDataFileName2 = "Average CAAR for Meet Group";
    const char *tempDataFileName3 = "Average CAAR for Beat Group";
    double x, y, x2, y2, x3, y3;
    int i;
    //Check if the 3 data are of the same length
    if (sizeof(yData1) != sizeof(yData2) || sizeof(yData2) != sizeof(yData3)) {
        cout << "Error Input" << endl;
        return 1;
    }
    //gnuplot
    gnuplotPipe = popen("gnuplot -persist", "w");
    if (gnuplotPipe) {
        fprintf(gnuplotPipe, "plot \"%s\" with lines,\"%s\" with lines, \"%s\" with lines\n", tempDataFileName1, tempDataFileName2, tempDataFileName3);
        fflush(gnuplotPipe);
        tempDataFile = fopen(tempDataFileName1, "w");
        for (i = 0; i < dataSize; i++) {
            x = i - 60;
            y = yData1[i];
            fprintf(tempDataFile, "%lf %lf\n", x, y);
        }
        fclose(tempDataFile);
        tempDataFile = fopen(tempDataFileName2, "w");
        for (i = 0; i < dataSize; i++) {
            x2 = i - 60;
            y2 = yData2[i];
            fprintf(tempDataFile, "%lf %lf\n", x2, y2);
        }
        fclose(tempDataFile);
        tempDataFile = fopen(tempDataFileName3, "w");
        for (i = 0; i < dataSize; i++) {
            x3 = i - 60;
            y3 = yData3[i];
            fprintf(tempDataFile, "%lf %lf\n", x3, y3);
        }
        fclose(tempDataFile);
        printf("press enter to continue...");
        getchar();
        remove(tempDataFileName1);
        remove(tempDataFileName2);
        remove(tempDataFileName3);
        fprintf(gnuplotPipe, "exit \n");
    }
    else {
        printf("gnuplot not found...");
    }
    return 0;
}





// StockDic.cpp

struct MemoryStruct {
    char *memory;
    size_t size;
};

void *myrealloc(void *ptr, size_t size) {
    if (ptr)
        return realloc(ptr, size);
    else
        return malloc(size);
}

int write_data(void *ptr, size_t size, size_t nmemb, void *data) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) data;

    mem->memory = (char *) myrealloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory) {
        memcpy(&(mem->memory[mem->size]), ptr, realsize);
        mem->size += realsize;
        mem->memory[mem->size] = 0;
    }
    return realsize;
}

string getTimeinSeconds(string Time) {
    std::tm t = {0};
    std::istringstream ssTime(Time);
    char time[100];
    memset(time, 0, 100);
    if (ssTime >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S")) {
//        cout << std::put_time(&t, "%c %Z") << "\n"
//             << std::mktime(&t) << "\n";
        sprintf(time, "%lld", mktime(&t));
        return string(time);
    } else {
        cout << "Parse failed\n";
        return "";
    }
}

pair<string, string> getStart_End(string a_date) {
    string start_time, end_time, str;
    stringstream ss(a_date);
    vector<string> results;
    while (getline(ss, str, '-')) {
        results.push_back(str);
    }
    int year = stoi(results[0]);
    int month = stoi(results[1]);
    string day = results[2];
    if (month + 4 > 12)
        end_time = getTimeinSeconds(to_string(year + 1) + "-0" + to_string(month - 8) + "-" + day + "T16:00:00");
    else {
        if (month + 4 < 10)
            end_time = getTimeinSeconds(to_string(year) + "-0" + to_string(month + 4) + "-" + day + "T16:00:00");
        else
            end_time = getTimeinSeconds(to_string(year) + "-" + to_string(month + 4) + "-" + day + "T16:00:00");
    }
    if (month - 4 <= 0)
        start_time = getTimeinSeconds(to_string(year - 1) + "-" + to_string(month + 8) + "-" + day + "T16:00:00");
    else
        start_time = getTimeinSeconds(to_string(year) + "-0" + to_string(month - 4) + "-" + day + "T16:00:00");
    return pair<string, string>(start_time, end_time);
}




// StockDic.h
class StockDic{
    map<string, Stock> Stock_dic;
public:
    bool read_surprise();
    bool fillin_price();
    void fillin_AR();
    map<string, Stock> getDic(){
        return Stock_dic;
    }

};



// StockDic.cpp
bool StockDic::read_surprise() {
    // -----------------Read Bloomberg Surprise Data--------------------
    ifstream surpirse_csv("announcements.csv");
    string line;
    if (surpirse_csv.is_open()) {
        getline(surpirse_csv, line);
        while (getline(surpirse_csv, line)) {
            string str;
            stringstream ss(line);
            vector<string> results;
            while (getline(ss, str, ',')) {
                results.push_back(str);
            }
            if (results[1] == "BF/B" || results[1] == "BRK/A")
                continue;
            Stock s(results[0], results[1], results[2], stod(results[3]));
            Stock_dic.insert(pair<string, Stock>(results[1], s));
        }
    } else {
        cerr << "Read csv error" << endl;
        return false;
    }
    Stock sp("S&P 500", "SPY", "2018-05-01", 0.0);
    Stock_dic.insert(pair<string, Stock>("SPY", sp));
    // -----------------Read Bloomberg Surprise Data--------------------
    return true;
}

bool StockDic::fillin_price() {
    map<string, Stock>::iterator itr = Stock_dic.begin();

    struct MemoryStruct data;
    data.memory = NULL;
    data.size = 0;

    // file pointer to create file that store the data
    FILE *fp;

    // declaration of an object CURL
    CURL *handle;

    CURLcode result;

    // set up the program environment that libcurl needs
    curl_global_init(CURL_GLOBAL_ALL);

    // curl_easy_init() returns a CURL easy handle
    handle = curl_easy_init();

    // if everything's all right with the easy handle...
    if (handle) {
        int counter = 0;
        string sCookies, sCrumb;
        //----------------------------Get Crumb-----------------------
        if (sCookies.length() == 0 || sCrumb.length() == 0) {
            curl_easy_setopt(handle, CURLOPT_URL, "https://finance.yahoo.com/quote/AMZN/history");
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
            curl_easy_setopt(handle, CURLOPT_COOKIEJAR, "cookies.txt");
            curl_easy_setopt(handle, CURLOPT_COOKIEFILE, "cookies.txt");
            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *) &data);
            // perform, then store the expected code in result
            result = curl_easy_perform(handle);
            if (result != CURLE_OK) {
                // if errors have occured, tell us what is wrong with result
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
                return false;
            }

            char cKey[] = "CrumbStore\":{\"crumb\":\"";
            char *ptr1 = strstr(data.memory, cKey);
            char *ptr2 = ptr1 + strlen(cKey);
            char *ptr3 = strstr(ptr2, "\"}");
            if (ptr3 != NULL)
                *ptr3 = NULL;
            sCrumb = ptr2;

            fp = fopen("cookies.txt", "r");
            char cCookies[100];
            if (fp) {
                while (fscanf(fp, "%s", cCookies) != EOF);
                fclose(fp);
            } else
                cerr << "cookies.txt does not exists" << endl;

            sCookies = cCookies;
            //free heap
            free(data.memory);
            data.memory = NULL;
            data.size = 0;
        }
        //----------------------------Get Crumb-----------------------
        cout << "Retrieving Price" << endl;
        cout << "*************************************************" << endl;
        while (true) {
            //break condition
            if (itr == Stock_dic.end())
                break;
            //----------------------------Get Price_lst----------------------
            string urlA = "https://query1.finance.yahoo.com/v7/finance/download/";
            string symbol = itr->first;
            string urlB = "?period1=";
            string urlC = "&period2=";
            string urlD = "&interval=1d&events=history&crumb=";
            pair<string, string> time = getStart_End(itr->second.get_date());
            string startTime, endTime;
            if (itr->first == "SPY") {
                startTime = getTimeinSeconds("2017-03-01T16:00:00");
                endTime = getTimeinSeconds("2019-04-01T16:00:00");
            } else {
                startTime = time.first;
                endTime = time.second;
            }
            string url = urlA + symbol + urlB + startTime + urlC + endTime + urlD + sCrumb;
            const char *cURL = url.c_str();
            const char *cookies = sCookies.c_str();
            curl_easy_setopt(handle, CURLOPT_COOKIE, cookies);   // Only needed for 1st stock
            curl_easy_setopt(handle, CURLOPT_URL, cURL);
            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *) &data);
            result = curl_easy_perform(handle);

            if (result != CURLE_OK) {
                // if errors have occurred, tell us what is wrong with result
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
                return false;
            }
            //----------------------------Get Price_lst----------------------


            stringstream sData;
            sData.str(data.memory);
            string sValue, sDate;
            double dValue = 0;
            string line;
            getline(sData, line);
            if (line.length() == 0) {
                itr++;
                free(data.memory);
                data.memory = NULL;
                data.size = 0;
                continue;
            }
            map<string, double> price_lst;
            string error_code = "";
            while (getline(sData, line)) {
                sDate = line.substr(0, line.find_first_of(','));
                line.erase(line.find_last_of(','));
                sValue = line.substr(line.find_last_of(',') + 1);
                dValue = strtod(sValue.c_str(), NULL);
                price_lst.insert(pair<string, double>(sDate, dValue));
                if (dValue == 0) {
                    error_code = itr->first;
                }
            }
            if (itr->first == "SPY") {
                itr->second.set_price_lst(price_lst);
                itr++;
                free(data.memory);
                data.memory = NULL;
                data.size = 0;
                continue;
            }
            //choose first 60 and later 60
            auto front = price_lst.find(itr->second.get_date());
            auto after = price_lst.find(itr->second.get_date());
            for (int i = 0; i < 60; i++) {
                front--;
                after++;
            }
            after++;
            price_lst.erase(price_lst.begin(), front);
            price_lst.erase(after, price_lst.end());
            itr->second.set_price_lst(price_lst);
            counter++;
            if (counter % 10 == 0)
                cout << "*";
            itr++;
            free(data.memory);
            data.memory = NULL;
            data.size = 0;
            if (error_code != "")
                Stock_dic.erase(error_code);
        }
        cout << endl;
    } else {
        fprintf(stderr, "Curl init failed!\n");
        return false;
    }

    // cleanup since you've used curl_easy_init
    curl_easy_cleanup(handle);

    // release resources acquired by curl_global_init()
    curl_global_cleanup();
    return true;
}

void StockDic::fillin_AR() {
    map<string, double> sp_price = Stock_dic.find("SPY")->second.get_price_lst();
    for (auto stocki = Stock_dic.begin(); stocki != Stock_dic.end(); stocki++) {
        map<string, double> this_price_lst = stocki->second.get_price_lst();
        if (stocki->first == "SPY")
            continue;
        vector<double> AR;
        string start_date = this_price_lst.begin()->first;
        auto sp_itr = sp_price.find(start_date);
        double ThistodayPrice, ThistomorrowPrice, SPtodayPrice, SPtomorrowPrice, ThisReturn, SPReturn;
        for (auto i = this_price_lst.begin(); i != this_price_lst.end();) {
            ThistodayPrice = i->second;
            i++;
            if (i == this_price_lst.end())
                break;
            ThistomorrowPrice = i->second;
            ThisReturn = (ThistomorrowPrice - ThistodayPrice) / ThistodayPrice;
            SPtodayPrice = sp_itr->second;
            sp_itr++;
            SPtomorrowPrice = sp_itr->second;
            SPReturn = (SPtomorrowPrice - SPtodayPrice) / SPtodayPrice;
            AR.push_back(ThisReturn - SPReturn);
        }
        stocki->second.set_AR(AR);
    }
    cout << "AR Calculated" << endl;
}



int main() {
    StockDic sp500;

    if (sp500.read_surprise())
        cout << "Read Surprise Finished" << endl;


    if (sp500.fillin_price())
        cout << "Read Price Finished" << endl;

    sp500.fillin_AR();

    map<string, Stock> Stock_dic = sp500.getDic();
    vector<Stock *> Beat_group;
    vector<Stock *> Meet_group;
    vector<Stock *> Miss_group;
    for (auto it = Stock_dic.begin(); it != Stock_dic.end(); it++) {
        if (it->first == "SPY")
            continue;
        if (it->second.get_surprise() >= 5)
            Beat_group.push_back(&it->second);
        else if (it->second.get_surprise() <= -1)
            Miss_group.push_back(&it->second);
        else
            Meet_group.push_back(&it->second);
    }
	vector<double> beatCAAR = averageCAAR(Beat_group);
	vector<double> meetCAAR = averageCAAR(Meet_group);
	vector<double> missCAAR = averageCAAR(Miss_group);
	cout << "CAAR for Beat " << beatCAAR << endl;
    cout << "CAAR for Meet " << meetCAAR << endl;
    cout << "CAAR for Miss " << missCAAR << endl;
	plotResults(missCAAR, meetCAAR, beatCAAR);

    return 0;
}