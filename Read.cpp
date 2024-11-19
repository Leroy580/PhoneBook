#include "Read.h"
using namespace std;

void Read(Person*& person, Grup*& grup, Hp& hp, const char* filename, const char* filename2) {
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

            person[i].fio.surname = token;

            token = strtok(NULL, ";");
            person[i].fio.name = token;

            token = strtok(NULL, ";");
            person[i].fio.ochestvo = token;

            token = strtok(NULL, ";");
            person[i].number = atoi(token);

            token = strtok(NULL, ";");
            person[i].mail = token;

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
            grup[i].ngr = token;

            token = strtok(NULL, ";");
            grup[i].id = atoi(token);
        }
        fclose(g); // Close file
    }
}
