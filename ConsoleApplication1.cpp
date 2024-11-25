#include <iomanip>
#include <iostream>
#include <cstring>
#include <string>
#include "Person.h"
#include "Write.h"
#include "Read.h"
#include "New.h"
#include "ShowP.h"

#pragma warning (disable:4996) // Disable deprecation warning for `strcpy`, `strtok`
using namespace std;

// Main function
int main() {
    int speoples = 0, sgroup = 0;
    string buf;
    Person* person = nullptr;
    Grup* group = nullptr;
    Hp hp;
    int cs;

    cout << "Enter username: ";
    getline(cin, buf);
    string filename = buf + "P";
    string filename2 = buf + "G";
    Read(person, group, hp, filename.c_str(), filename2.c_str());

    do {
        cout << "\n\n/menu\n1. Show full list of persons\n2. Add new person\n3. Groups Manager\n";
        cin >> cs;
        cin.ignore();

        switch (cs) {
        case 1: ShowP(person, hp); break;
        case 2: New(person, hp); Write(person, group, hp, filename.c_str(), filename2.c_str()); break;
        case 3: /* Call Group Manager */ break;
        case 0: break;
        }
    } while (cs != 0);

    // Free dynamically allocated memory
    delete[] person;
    delete[] group;

    return 0;
}
