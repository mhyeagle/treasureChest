#include <iostream>
#include <string>
#include "json/json.h"

using namespace std;

int main() {
    Json::Value root;
    Json::Value person;
    Json::FastWriter writer;

    person["name"] = "hello";
    person["age"] = "13";

    root.append(person);

    string json_str = writer.write(root);
    cout << "value:" << endl;
    cout << json_str << endl;

    root.clear();
    cout << "root is empty: " << root.empty() << endl;
    json_str = writer.write(root);
    cout << "value_null:" << endl;
    cout << json_str << endl;


    return 0;
}
