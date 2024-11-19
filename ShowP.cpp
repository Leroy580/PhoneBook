#include "ShowP.h"
void ShowP(Person* group, Hp hp) {
    cout << "#\t\tSurname\t\tName\t\tMiddle Name\t\tNumber\t\tMail\n";
    for (int i = 0; i < hp.spep; i++) {
        cout << i + 1 << "\t\t" << group[i].fio.surname << "\t\t"
            << group[i].fio.name << "\t\t" << group[i].fio.ochestvo << "\t\t"
            << group[i].number << "\t\t" << group[i].mail << "\n";
    }
}
