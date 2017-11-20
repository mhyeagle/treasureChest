#include <iostream>
#include <fstream>
#include <string>

#include "Person.pb.h"

using namespace std;

void add_person(tutorial::Person* person);

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " file." << endl;
        return -1;
    }

    fstream in(argv[1], ios::in | ios::binary);
    if (!in) {
        cout << "open " << argv[1] << " failed." << endl;
        return -1;
    }
    in.close();

    tutorial::AddressBook address_book;

    add_person(address_book.add_person());

    fstream out(argv[1], ios::out | ios::trunc | ios::binary);
    if (!address_book.SerializeToOstream(&out)) {
        cout << "Serialize to file failed." << endl;
        return -1;
    }

    return 0;
}

void add_person(tutorial::Person* person) {
    cout << "input id: " << endl;
    int id = 0;
    cin >> id;
    person->set_id(id);

    cin.ignore(256, '\n');
    cout << "input name:" << endl;
    string line;
    getline(cin, line);
    person->set_name(line);
    line.clear();

    cout << "input email:" << endl;
    getline(cin, line);
    person->set_email(line);
    line.clear();

    while(true) {
        cout << "input number(blank to break): " << endl;
        getline(cin, line);

        if (line.empty())
            break;
        tutorial::Person::PhoneNumber* phone_num = person->add_phone();

        phone_num->set_number(line);
        line.clear();
        
        cout << "number type:" << endl;
        getline(cin, line);
        if (line == "mobile")
            phone_num->set_type(tutorial::Person_PhoneType_MOBILE);
        else 
            phone_num->set_type(tutorial::Person_PhoneType_HOME);

        line.clear();
    }
}
