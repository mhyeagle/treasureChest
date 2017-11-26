#include <iostream>
#include <string>

#include <event.h>

using namespace std;

int main() {
    cout << event_get_version() << endl;
    cout << "support method:" << endl;
    const char **methods = event_get_supported_methods();
    for (int i = 0; methods[i] != NULL; i++) {
        cout << methods[i] << endl;
    }

    cout << "******" << endl;
    event_base *base = event_base_new();
    cout << event_base_get_method(base) << endl;
    event_base_free(base);

    return 0;
}
