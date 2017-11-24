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
    person["name"] = "world";
    person["age"] = "15";
    person["sex"] = "female";
    root.append(person);

    string json_str = writer.write(root);
    cout << "value:" << endl;
    cout << json_str << endl;

    cout << "***************" << endl;

    cout << "root size: " << root.size() << endl;
    for (int i = 0; i < root.size(); ++i) {
        Json::Value::Members mem = root[i].getMemberNames();
        for (auto iter = mem.begin(); iter != mem.end(); iter++) {
            cout << "key and value: " << endl;
            cout << "*iter: " << *iter << " type: " << (*iter) << endl;
            cout << "root[i][*iter]: " << root[i][*iter] << " type: " << root[i][*iter].type() << endl;
        }
    }
    



    cout << "***************" << endl;

    root.clear();
    cout << "root is empty: " << root.empty() << endl;
    json_str = writer.write(root);
    cout << "value_null:" << endl;
    cout << json_str << endl;


    return 0;
}
