#include <iomanip>
#include <iostream>
#pragma warning (disable:4996)
using namespace std;
//-ФИО
//- Номер телефона
//- адрес электронной почты
//- группа(допустим "Семья" или "Работа")

//
struct Hp {
    int spep = 0;
    int sgrup = 0;
};

struct FIO {
    char* name = nullptr;
    char* surname = nullptr;
    char* ochstvo = nullptr;
};

struct Person {
    FIO fio;
    int number = 0;
    int sp = 0;
    char* mail = nullptr;
    int grp;
};

struct Grup {
    int id;
    char* ngr = nullptr;
};

void Read(Person*& person, Grup* grup, Hp& hp, char* filename, char* filename2)
{
    char buf[300];
    FILE* f = fopen(filename, "r");//создали поток, привязали его
    if (!f)
        cout << "Wrong file\n";
    else
    {
        while (fgets(buf, 300, f))
        {
            hp.spep++;
        }
        //создаем новый массив на кол-во полезных строк
        person = new Person[hp.spep];
        rewind(f);//вернкли курсор в начало файла
        for (int i = 0; i < hp.spep; i++)
        {
            fgets(buf, 300, f);
            char* token = strtok(buf, ";");
            person[i].fio.surname = new char[strlen(token) + 1];
            strcpy(person[i].fio.surname, token);

            token = strtok(NULL, ";");//вычитываем
            person[i].fio.name = new char[strlen(token) + 1];
            strcpy(person[i].fio.name, token);

            token = strtok(NULL, ";");
            person[i].fio.ochstvo = new char[strlen(token) + 1];
            strcpy(person[i].fio.ochstvo, token);

            token = strtok(NULL, ";");
            person[i].number = atoi(token);

            token = strtok(NULL, ";");
            person[i].mail = new char[strlen(token) + 1];
            strcpy(person[i].mail, token);

            token = strtok(NULL, "\n");
            person[i].grp = atoi(token);

        }fclose(f);//закрываем поток
    }

    FILE* g = fopen(filename2, "r");//создали поток, привязали его
    if (!g)
        cout << "Wrong file2\n";
    else
    {
        while (fgets(buf, 300, g))
        {
            hp.sgrup++;
        }
        //создаем новый массив на кол-во полезных строк
        grup = new Grup[hp.sgrup];
        rewind(g);//вернкли курсор в начало файла
        for (int i = 0; i < hp.sgrup; i++)
        {
            fgets(buf, 300, g);

            char* token = strtok(buf, ";");
            token = strtok(NULL, ";");
            grup[i].id = atoi(token);

            token = strtok(buf, ";");
            grup[i].ngr = new char[strlen(token) + 1];
            strcpy(grup[i].ngr, token);
        }fclose(g);//закрываем поток
    }

}

void Write(Person* group, Grup* grup, Hp hp, char* filename, char* filename2)
{
    FILE* f = fopen(filename, "w");
    char buf[15];
    for (int i = 0; i < hp.spep; i++)
    {
        fputs(group[i].fio.surname, f);//записали в файл имя
        fputc(';', f);//поставили ;

        fputs(group[i].fio.name, f);//записали ее в файл
        fputc(';', f);//поставили ;

        fputs(group[i].fio.ochstvo, f);//записали ее в файл
        fputc(';', f);//поставили ;

        itoa(group[i].number, buf, 10);//преобрразовали N
        fputs(buf, f);//записали ее в файл
        fputc(';', f);//поставили ;

        fputs(group[i].mail, f);//записали ее в файл
        fputc(';', f);//поставили ;

        itoa(group[i].grp, buf, 10);
        fputs(buf, f);//записали ее в файл
        fputc(';', f);//поставили ;
        fputc('\n', f);//поставили перенос строки
    }
    fclose(f);//закрыли поток

    if (hp.sgrup > 0)
    {
        FILE* g = fopen(filename2, "w");
        for (int i = 0; i < hp.sgrup; i++)
        {
            itoa(grup[i].id, buf, 10);
            fputs(buf, g);//записали ее в файл
            fputc(';', g);//поставили ;

            fputs(grup[i].ngr, g);//записали ее в файл
            fputc(';', g);//поставили ;
            fputc('\n', g);
        }
        fclose(g);//закрыли поток
    }
}

void Sort(Person*& person, Hp hp) {
    Person temp;
    int tik = 0;//проверка на первую букву

    for (int k = 0; k < hp.spep/*количество людей*/ - 1; k++)
        for (int i = 0; i < hp.spep/*количество людей*/ - 1; i++)
        {
            tik = 0;
            for (int j = 0; j < strlen(person[i].fio.surname) - i - 1; j++)
                if ((int)person[i].fio.surname[j] > (int)person[i + 1].fio.surname[j])
                    if (tik == 0)
                        if ((int)person[i].fio.surname[j - 1] == (int)person[i + 1].fio.surname[j - 1])
                        {
                            temp = person[i];
                            person[i] = person[i + 1];
                            person[i + 1] = temp;
                            tik++;
                        }
                        else
                        {
                            i++;
                            j = strlen(person[i].fio.surname);
                        }
        }
}

void New(Person*& group, Hp& hp)
{
    char buff[100];
    int sp = 0;

    Person* temp;
    temp = new Person[hp.spep + 1];
    for (int i = 0; i < hp.spep; i++)
        temp[i] = group[i];
    delete[] group;
    group = temp;
    do {
        cout << "Enter full name(fio)\n"; cin.getline(buff, 100);
        for (int i = 0; buff[i] != '\0'; i++)/////////////////
        {
            if (buff[i] == ' ')
            {
                group[hp.spep].sp++;
            }
        }
    } while (group[hp.spep].sp < 2);
    char* token = strtok(buff, " ");
    group[hp.spep].fio.surname = new char[strlen(token) + 1];
    strcpy(group[hp.spep].fio.surname, token);
    // if (group[hp.spep].sp > 0) {
    token = strtok(NULL, " ");
    group[hp.spep].fio.name = new char[strlen(token) + 1];
    strcpy(group[hp.spep].fio.name, token);
    // }
     //if (group[hp.spep].sp > 1) {
    token = strtok(NULL, " ");
    group[hp.spep].fio.ochstvo = new char[strlen(token) + 1];
    strcpy(group[hp.spep].fio.ochstvo, token);
    //}
    //cout << "Enter age\n"; cin >> group[size].age;
    cout << "Enter mail\n"; cin.getline(buff, 100);
    group[hp.spep].mail = new char[strlen(buff) + 1];
    strcpy(group[hp.spep].mail, buff);
    cout << "Enter number\n"; cin >> group[hp.spep].number;

    hp.spep++;
    if (hp.spep > 1) Sort(group, hp);
}

void ShowP(Person* group, Hp hp)
{
    cout << "#\tSName\tName\tPName\tNumber\tMail\n\n";
    for (int i = 0; i < hp.spep; i++)
    {
        cout << i + 1 << "\t" << group[i].fio.surname << "\t";

        //if (group[hp.spep].sp > 0)
        cout << group[i].fio.name << "\t";
        //else
        //    cout << "-\t";
        //if (group[hp.spep].sp > 1)
        cout << group[i].fio.ochstvo << "\t";
        //else
        //    cout << "-\t";

        cout << group[i].number << "\t";
        cout << group[i].mail << "\n";
    }
}


void CrGroup(Grup*& group, Hp& hp)
{
    char buff[100];
    Grup* temp = new Grup[hp.sgrup + 1];
    for (int i = 0; i < hp.sgrup; i++)
        temp[i] = group[i];
    delete[] group;
    group = temp;
    cout << "Enter name of new group\n"; cin.getline(buff, 100);
    group[hp.sgrup].ngr = new char[strlen(buff)];
    strcpy(group[hp.sgrup].ngr, buff);
    group[hp.sgrup].id = hp.sgrup;
    hp.sgrup++;
}

void pPiG(Person*& person, Grup*& group, Hp& hp)
{
    int per, grp;
    do {
        cout << "\n/menu/goups manager/put person in group\n";
        ShowP(person, hp);
        do {
            cout << "Choose(#) person whom you want to add in some group or enter zero to back  ";  cin >> per;
        } while (per<0 || per>hp.spep);

        if (per > 0) {
            cout << "#" << "\t" << "Name\n";
            for (int i = 0; i < hp.sgrup; i++)
                cout << i << "\t" << group[i].ngr << "\n";
            do {
                cout << "Choose(#) group in whitch you want to add chosen person  ";  cin >> grp;
            } while (grp<0 || grp>hp.sgrup);

            person[per].grp = grp;
            cout << "Done\n";
        }
    } while (per != 0);
}

void dPfG(Person*& person, Grup*& group, Hp& hp)
{
    int per, grp, temp = 0;
    do {
        cout << "\n/menu/goups manager/delete person from group\n";
        cout << "#" << "\t" << "Name\n";
        for (int i = 0; i < hp.sgrup; i++)
            cout << i << "\t" << group[i].ngr << "\n";
        do {
            cout << "Choose(#) group form whitch you want to delete person(not undo) or enter zero to back  ";  cin >> grp;
        } while (grp<0 || grp>hp.spep);

        if (grp > 0) {
            cout << "#\tSName\tName\tPname\tNumber\t\tMail\n";
            for (int i = 0; i < hp.spep; i++)
            {
                if (person[i].grp = group[grp].id) {
                    cout << i + 1 << "\t" << person[i].fio.surname << "\t";
                    cout << person[i].fio.name << "\t";
                    cout << person[i].fio.ochstvo << "\t";
                    cout << person[i].number << "\t\t";
                    cout << person[i].mail << "\n";
                    temp++;
                }
            }
            if (temp < 1)cout << "Group is empty ";
            else {
                cout << "Choose(#) person whom you want to delete from group  "; cin >> per;
                person[per].grp = -1;
                cout << "Done";
            }
        }
    } while (grp != 0);


}

void ShowG(Person* person, Grup* group, Hp hp)
{
    int ch, temp = 0;
    if (hp.sgrup < 1) cout << "Group is not created jet";
    else {
        cout << "\n/menu/goups manager/Show\n";
        cout << "#" << "\t" << "Name\n";
        for (int i = 0; i < hp.sgrup; i++)
            cout << i << "\t" << group[i].ngr << "\n";
        do {
            cout << "Choose(#) group you want to read   "; cin >> ch;
        } while (ch<0 || ch>hp.sgrup);

        if (temp < 1)cout << "Group is empty ";
        else {
            cout << "#\tSName\t\tName\t\tPname\t\tNumber\t\tMail\n\t\t\t\t\t\t\t\t\t\n";
            for (int i = 0; i < hp.spep; i++)
            {
                if (person[i].grp = group[ch].id) {
                    cout << i + 1 << "\t" << person[i].fio.surname << "\t\t";
                    cout << person[i].fio.name << "\t\t";
                    cout << person[i].fio.ochstvo << "\t\t";
                    cout << person[i].number << "\t\t";
                    cout << person[i].mail << "\n";
                    temp++;
                }
            }
        }
    }
}

void GruMngr(Person*& person, Grup*& group, Hp& hp)
{
    int chose;
    do {
        cout << "\n\n/menu/goups manager\n";
        cout << "1.Show list of group\n2. Put persons in group\n3. Delete person from group(not undo)\n4. Create group\n0. Back  ";
        cin >> chose;
        cin.ignore();
        switch (chose)
        {
        case 1:if (hp.sgrup < 1) cout << "Group is not created jet"; else ShowG(person, group, hp); break;
        case 2:if (hp.sgrup < 1) cout << "Group is not created jet"; else pPiG(person, group, hp); break;
        case 3:if (hp.sgrup < 1) cout << "Group is not created jet"; else dPfG(person, group, hp); break;
        case 4:CrGroup(group, hp); break;
        }
    } while (chose != 0);
}

void main()
{
    int speoples = 0, sgroup = 0;
    char buf[100];
    char* filename, * filename2;
    Person* person = nullptr;
    Grup* group = nullptr;
    Hp hp;
    int cs;

    cout << "Enter username:  "; cin.ignore(); cin.getline(buf, 100);
    filename = new char[strlen(buf) + 1];
    strcpy(filename, buf);
    filename[strlen(buf)] = 'P';
    filename2 = new char[strlen(buf) + 1]; strcpy(filename2, buf); filename2[strlen(buf)] = 'G';
    do {
        cout << "\n\n/menu\n1.Show full list of person\n2.Add new person\n3.Groups Manager\n"; cin >> cs;
        cin.ignore();
        switch (cs)
        {
        case 1:ShowP(person, hp); break;
        case 2:New(person, hp); Write(person, group, hp, filename, filename2); break;
        case 3:GruMngr(person, group, hp); break;
        case 4:CrGroup(group, hp); break;
        case 0:break;
        }
    } while (cs != 0);
}
