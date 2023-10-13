
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
    int count;
    char login[30]; 
    char password[30];
};

struct Course
{
    char name[25];
    char facultyname[50];
    int total;
    int enrol;
    bool active;
};
struct enroll
{
   char facultyname[50];
   char name[50];
   char studentname[50];
   bool active;
};
