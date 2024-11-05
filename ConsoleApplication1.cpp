#include <iomanip>
#include <iostream>
#include <cstring>
#pragma warning (disable:4996) // Disable deprecation warning for `strcpy`, `strtok`
using namespace std;

// Struct representing extra properties
struct Hp {
    int spep = 0; // Number of people
    int sgrup = 0; // Number of groups
};

// Struct representing a full name
struct FIO {
    char* name = nullptr;
    char* surname = nullptr;
    char* ochestvo = nullptr; // Middle name
};

// Struct representing a person in the phonebook
struct Person {
    FIO fio;          // Full name
    int number = 0;   // Phone number
    int sp = 0;       // Space count (used for name parsing)
    char* mail = nullptr; // Email address
    int grp;          // Group ID
};

// Struct representing a group
struct Grup {
    int id;          // Group ID
    char* ngr = nullptr; // Group name
};

// Function to read data from files and populate Person and Grup arrays
void Read(Person*& person, Grup*& grup, Hp& hp, char* filename, char* filename2) {
    char buf[300];
    FILE* f = fopen(filename, "r"); // Open file for reading
    if (!f) {
        cout << "Wrong file\n";
    }
    else {
        // Count lines in the file
        while (fgets(buf, 300, f)) {
            hp.spep++;
        }

        person = new Person[hp.spep]; // Allocate memory for person array
        rewind(f); // Reset file cursor to the beginning

        // Parse each line to fill person data
        for (int i = 0; i < hp.spep; i++) {
            fgets(buf, 300, f);
            char* token = strtok(buf, ";");

            person[i].fio.surname = new char[strlen(token) + 1];
            strcpy(person[i].fio.surname, token);

            token = strtok(NULL, ";");
            person[i].fio.name = new char[strlen(token) + 1];
            strcpy(person[i].fio.name, token);

            token = strtok(NULL, ";");
            person[i].fio.ochestvo = new char[strlen(token) + 1];
            strcpy(person[i].fio.ochestvo, token);

            token = strtok(NULL, ";");
            person[i].number = atoi(token);

            token = strtok(NULL, ";");
            person[i].mail = new char[strlen(token) + 1];
            strcpy(person[i].mail, token);

            token = strtok(NULL, "\n");
            person[i].grp = atoi(token);
        }
        fclose(f); // Close file
    }

    // Repeat similar process for reading group data
    FILE* g = fopen(filename2, "r");
    if (!g) {
        cout << "Wrong file2\n";
    }
    else {
        while (fgets(buf, 300, g)) {
            hp.sgrup++;
        }

        grup = new Grup[hp.sgrup]; // Allocate memory for group array
        rewind(g);

        for (int i = 0; i < hp.sgrup; i++) {
            fgets(buf, 300, g);

            char* token = strtok(buf, ";");
            token = strtok(NULL, ";");
            grup[i].id = atoi(token);

            token = strtok(buf, ";");
            grup[i].ngr = new char[strlen(token) + 1];
            strcpy(grup[i].ngr, token);
        }
        fclose(g); // Close file
    }
}

// Function to write Person and Group data back to files
void Write(Person* group, Grup* grup, Hp hp, char* filename, char* filename2) {
    FILE* f = fopen(filename, "w");
    char buf[15];

    for (int i = 0; i < hp.spep; i++) {
        // Write person data
        fputs(group[i].fio.surname, f); fputc(';', f);
        fputs(group[i].fio.name, f); fputc(';', f);
        fputs(group[i].fio.ochestvo, f); fputc(';', f);
        itoa(group[i].number, buf, 10); fputs(buf, f); fputc(';', f);
        fputs(group[i].mail, f); fputc(';', f);
        itoa(group[i].grp, buf, 10); fputs(buf, f); fputc(';', f);
        fputc('\n', f);
    }
    fclose(f);

    // Write group data if it exists
    if (hp.sgrup > 0) {
        FILE* g = fopen(filename2, "w");
        for (int i = 0; i < hp.sgrup; i++) {
            itoa(grup[i].id, buf, 10); fputs(buf, g); fputc(';', g);
            fputs(grup[i].ngr, g); fputc(';', g);
            fputc('\n', g);
        }
        fclose(g);
    }
}

// Function to sort the Person array by surname
void Sort(Person*& person, Hp hp) {
    for (int i = 0; i < hp.spep - 1; i++) {
        for (int j = 0; j < hp.spep - i - 1; j++) {
            if (strcmp(person[j].fio.surname, person[j + 1].fio.surname) > 0) {
                swap(person[j], person[j + 1]);
            }
        }
    }
}

// Function to add a new Person to the list
void New(Person*& group, Hp& hp) {
    char buff[100];
    cout << "Enter full name (surname, name, middle name): ";
    cin.getline(buff, 100);

    Person* temp = new Person[hp.spep + 1];
    for (int i = 0; i < hp.spep; i++) {
        temp[i] = group[i]; // Copy existed data
    }
    delete[] group; // Delete old array
    group = temp;   // Update array

    // Parse and assign the name fields
    char* token = strtok(buff, " ");
    group[hp.spep].fio.surname = new char[strlen(token) + 1];
    strcpy(group[hp.spep].fio.surname, token);
    token = strtok(NULL, " ");
    group[hp.spep].fio.name = new char[strlen(token) + 1];
    strcpy(group[hp.spep].fio.name, token);
    token = strtok(NULL, " ");
    group[hp.spep].fio.ochestvo = new char[strlen(token) + 1];
    strcpy(group[hp.spep].fio.ochestvo, token);

    cout << "Enter mail: ";
    cin.getline(buff, 100);
    group[hp.spep].mail = new char[strlen(buff) + 1];
    strcpy(group[hp.spep].mail, buff);

    cout << "Enter number: ";
    cin >> group[hp.spep].number;

    hp.spep++;
    if (hp.spep > 1) Sort(group, hp);
}

// Display function for Person array
void ShowP(Person* group, Hp hp) {
    cout << "#\t\tSurname\t\tName\t\tMiddle Name\t\tNumber\t\tMail\n";
    for (int i = 0; i < hp.spep; i++) {
        cout << i + 1 << "\t\t" << group[i].fio.surname << "\t\t"
            << group[i].fio.name << "\t\t" << group[i].fio.ochestvo << "\t\t"
            << group[i].number << "\t\t" << group[i].mail << "\n";
    }
}

// Additional functions for managing groups and updating details can follow similar formatting
// ...

int main() {
    int speoples = 0, sgroup = 0;
    char buf[100];
    char* filename, * filename2;
    Person* person = nullptr;
    Grup* group = nullptr;
    Hp hp;
    int cs;

    cout << "Enter username: ";
    cin.ignore();
    cin.getline(buf, 100);
    filename = new char[strlen(buf) + 2];
    strcpy(filename, buf);
    filename[strlen(buf)] = 'P';
    filename2 = new char[strlen(buf) + 2];
    strcpy(filename2, buf);
    filename2[strlen(buf)] = 'G';

    do {
        cout << "\n\n/menu\n1. Show full list of persons\n2. Add new person\n3. Groups Manager\n";
        cin >> cs;
        cin.ignore();

        switch (cs) {
        case 1: ShowP(person, hp); break;
        case 2: New(person, hp); Write(person, group, hp, filename, filename2); break;
        case 3: /* Call Group Manager */ break;
        case 0: break;
        }
    } while (cs != 0);

    // Free dynamically allocated memory
    delete[] filename;
    delete[] filename2;
    delete[] person;
    delete[] group;

    return 0;
}
