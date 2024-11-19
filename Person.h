#pragma once
#include <string>
using namespace std;
// Struct representing extra properties
struct Hp {
    int spep = 0; // Number of people
    int sgrup = 0; // Number of groups
};

// Struct representing a full name
struct FIO {
    string name;
    string surname;
    string ochestvo; // Middle name
};
// Struct representing a person in the phonebook
struct Person {
    FIO fio;          // Full name
    int number = 0;   // Phone number
    string mail;      // Email address
    int grp;          // Group ID
};

// Struct representing a group
struct Grup {
    int id;          // Group ID
    string ngr;      // Group name
};
