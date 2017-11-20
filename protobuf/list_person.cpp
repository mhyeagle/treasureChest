#include <iostream>
#include <fstream>
#include <string>

#include "Person.pb.h"

using namespace std;

void ListPerson(const tutorial::AddressBook& address_book);

int main(int argc, char** argv) {
    if (2 != argc) {
        cerr << "Usage: " << argv[0] << " address_book_file." << endl;
        return -1;
    }

    fstream in(argv[1], ios::binary | ios::in);
    if (!in) {
        cerr << "open " << argv[1] << " failed" << endl;
        return -1;
    }

    tutorial::AddressBook address_book;
    if (!address_book.ParseFromIstream(&in)) {
        cerr << "Parse Input file failed." << endl;
        return -1;
    }

    ListPerson(address_book);

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}

void ListPerson(const tutorial::AddressBook& address_book) {
    for (int i = 0; i < address_book.person_size(); i++) {
        const tutorial::Person& person = address_book.person(i);
        cout << "Person ID:" << person.id();
        cout << " Name: " << person.name();
        cout << " Email: " << person.email();

        for (int j = 0; j < person.phone_size(); j++) {
            const tutorial::Person::PhoneNumber& phone_number = person.phone(j);
            switch(phone_number.type()) {
                case tutorial::Person::MOBILE:
                    cout << " Mobile: ";
                    break;
                case tutorial::Person::HOME:
                    cout << " Home: ";
                    break;
                case tutorial::Person::WORK:
                    cout << " Work: ";
                    break;
            }
            cout << phone_number.number() << endl;
        }
    }
}
