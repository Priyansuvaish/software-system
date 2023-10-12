#ifndef RECORD
#define RECORD

struct professor
{
    int id;
    char name[25];
    int age;

    char login[30]; 
    char password[30];

};

struct student
{
    int id;
    char name[25];
    int age;
    bool active;

    char login[30]; 
    char password[30];
};

struct Course
{
    int id;
    char name[25];
    char facultyname[50];
};
#endif
