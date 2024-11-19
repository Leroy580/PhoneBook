#include "Write.h"

void Write(Person* group, Grup* grup, Hp hp, const char* filename, const char* filename2) {
    FILE* f = fopen(filename, "w");
    char buf[15];

    for (int i = 0; i < hp.spep; i++) {
        // Write person data
        fputs(group[i].fio.surname.c_str(), f); fputc(';', f);
        fputs(group[i].fio.name.c_str(), f); fputc(';', f);
        fputs(group[i].fio.ochestvo.c_str(), f); fputc(';', f);
        itoa(group[i].number, buf, 10); fputs(buf, f); fputc(';', f);
        fputs(group[i].mail.c_str(), f); fputc(';', f);
        itoa(group[i].grp, buf, 10); fputs(buf, f); fputc(';', f);
        fputc('\n', f);
    }
    fclose(f);

    // Write group data if it exists
    if (hp.sgrup > 0) {
        FILE* g = fopen(filename2, "w");
        for (int i = 0; i < hp.sgrup; i++) {
            itoa(grup[i].id, buf, 10); fputs(buf, g); fputc(';', g);
            fputs(grup[i].ngr.c_str(), g); fputc(';', g);
            fputc('\n', g);
        }
        fclose(g);
    }
}
