#include <iostream>
#include <cmath>
#include <chrono>
#include <ctime>
#include <sstream>

using namespace std;

const int monthDays[12] = { 31, 59, 90, 120, 151, 181, 212, 243,
273, 304, 334, 365 };
int countLeapYearDays(int d[]){
   int years = d[2];
   if (d[1] <= 2)
      years--;
   return ( (years / 4) - (years / 100) + (years / 400) );
}
int countNoOfDays(int date1[], int date2[]){
   long int dayCount1 = (date1[2] * 365);
   dayCount1 += monthDays[date1[1]];
   dayCount1 += date1[0];
   dayCount1 += countLeapYearDays(date1);
   long int dayCount2 = (date2[2] * 365);
   dayCount2 += monthDays[date2[1]];
   dayCount2 += date2[0];
   dayCount2 += countLeapYearDays(date2);
   return ( abs(dayCount1 - dayCount2) );
}

string tmDate2String(struct tm nowLocal) {
    stringstream ss;
    ss << nowLocal.tm_mday << '/' << 1+nowLocal.tm_mon << '/' << 1900+ nowLocal.tm_year;
    return ss.str();
}

string tmTime2String(struct tm nowLocal) {
    stringstream ss;
    ss << nowLocal.tm_hour << ':' << nowLocal.tm_min << ':' << nowLocal.tm_sec;
    return ss.str();
}

tm getNow() {
    time_t now;
    struct tm nowLocal;
    // now = time(NULL);
    now = 3600*24;
    cout << "seconds: " << now << endl;
    nowLocal = *(localtime(&now));
    return nowLocal;
}

int do_date(){
   int date1[3] = {13, 3, 2021};
   int date2[3] = {24, 5, 2023};
   cout<<"The number of days between two dates is "<<countNoOfDays(date1, date2) << endl;
   tm nowLocal = getNow();
   cout << tmDate2String(nowLocal) << endl;
   cout << tmTime2String(nowLocal) << endl;

   return 0;
}