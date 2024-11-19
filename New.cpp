#include "New.h"
using namespace std;

void Sort(Person*& person, Hp hp) {
    for (int i = 0; i < hp.spep - 1; i++) {
        for (int j = 0; j < hp.spep - i - 1; j++) {
            if (person[j].fio.surname > person[j + 1].fio.surname) {
                swap(person[j], person[j + 1]);
            }
        }
    }
}
void New(Person*& group, Hp& hp) {
    string buff;
    cout << "Enter full name (surname, name, middle name): ";
    getline(cin, buff);

    Person* temp = new Person[hp.spep + 1];
    for (int i = 0; i < hp.spep; i++) {
        temp[i] = group[i]; // Copy existed data
    }
    delete[] group; // Delete old array
    group = temp;   // Update array

    // Parse and assign the name fields
    size_t pos1 = buff.find(" ");
    size_t pos2 = buff.find(" ", pos1 + 1);

    group[hp.spep].fio.surname = buff.substr(0, pos1);
    group[hp.spep].fio.name = buff.substr(pos1 + 1, pos2 - pos1 - 1);
    group[hp.spep].fio.ochestvo = buff.substr(pos2 + 1);

    cout << "Enter mail: ";
    getline(cin, group[hp.spep].mail);

    cout << "Enter number: ";
    cin >> group[hp.spep].number;
    cin.ignore();

    hp.spep++;
    if (hp.spep > 1) Sort(group, hp);
}
