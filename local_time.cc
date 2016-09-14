#include <iostream>
#include <sstream>
#include <time.h>

using namespace std;

int main() {
    stringstream ss;
    time_t now_seconds;
    now_seconds = time(NULL);
    struct tm * local_time;

    local_time = localtime(&now_seconds);

    int now_year = local_time->tm_year + 1900;
    int now_month = local_time->tm_mon + 1;
    int now_day = local_time->tm_mday;

    cout << "tm_year: " << local_time->tm_year + 1900 << endl;
    cout << "tm_mon: " << local_time->tm_mon + 1 << endl;
    cout << "tm_mday: " << local_time->tm_mday << endl;

    ss << now_year;
    if (now_month < 10) {
        ss << "0";
    }
    ss << now_month << now_day;
    cout << ss.str() << endl;

    return 0;
}
