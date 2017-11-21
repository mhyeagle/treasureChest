#include <iostream>
#include <fstream>
#include <string>

#include "Person.pb.h"

using namespace std;

void PromptForAddress(tutorial::Person* person);

int main(int argc, char** argv) {
    if (2 != argc) {
        cout << "Usage: " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
        return -1;
    }

    tutorial::AddressBook address_book;

    fstream in(argv[1], ios::binary | ios::in);
    if (!in) {
        cerr << "open file " << argv[1] << "failed" << endl;
        return -1;
    }

    if (!address_book.ParseFromIstream(&in)) {
        cerr << "Parse File " << argv[1] << " failed" << endl;
        return -1;
    }
    in.close();

    PromptForAddress(address_book.add_person());

    fstream out(argv[1], ios::binary | ios::out | ios::trunc);
    if (!address_book.SerializeToOstream(&out)) {
        cerr << "Failed to Write Address Book!" << endl;
        return -1;
    }

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}

void PromptForAddress(tutorial::Person* person) {
    cout << "Enter a Person ID number:";
    int id;
    cin >> id;
    person->set_id(id);

    cin.ignore(256, '\n');
    cout << "Enter name:";
    getline(cin, *person->mutable_name());

    cout << "Enter email address (blank for none):";
    string email;
    getline(cin, email);
    if (!email.empty()) {
        person->set_email(email);
    }

    while(true) {
        cout << "Enter a phone number (or leave blank to finish):";
        string number;
        getline(cin, number);
        if (number.empty())
            break;
        tutorial::Person_PhoneNumber* phone_number = person->add_phone();
        phone_number->set_number(number);

        cout << "Is this a mobile, home, or work phone?";
        string type;
        getline(cin, type);
        if ("mobile" == type) {
            phone_number->set_type(tutorial::Person_PhoneType_MOBILE);
        }
        else if ("home" == type) {
            phone_number->set_type(tutorial::Person_PhoneType_HOME);
        }
        else if ("work" == type) {
            phone_number->set_type(tutorial::Person_PhoneType_WORK);
        }
        else {
            phone_number->set_type(tutorial::Person_PhoneType_HOME);
        }
    }
}
