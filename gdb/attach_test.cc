#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    cout << "start" << endl;

    for(int i = 0; i < 100; ++i) {
        cout << i << endl;
    }


    cout << "now sleep 1000s" << endl;
    sleep(1000);
    cout << "finish" << endl;

    return 0;
}
