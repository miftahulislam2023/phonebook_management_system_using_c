#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAXNAME 80
#define MAXPHONE 13
#define MAXEMAIL 30
#define MAXADDRESS 50

typedef struct
{
    char name[MAXNAME];
    char phone[MAXPHONE];
    char email[MAXEMAIL];
    char address[MAXADDRESS];
    char createdAt[40];
    char updatedAt[40];
} Contact;

typedef struct
{
    Contact contact;
    struct Node *next;
} Node;

char *getCurrentTime()
{
    time_t t;
    struct tm *systime;
    t = time(NULL);
    systime = localtime(&t);

    static char timeString[40]; // 40 chars is enough for "dd-Month-yyyy hh:mm:ss Weekday" + null terminator

    // Get the month name
    char *month;
    switch (systime->tm_mon)
    {
    case 0:
        month = "January";
        break;
    case 1:
        month = "February";
        break;
    case 2:
        month = "March";
        break;
    case 3:
        month = "April";
        break;
    case 4:
        month = "May";
        break;
    case 5:
        month = "June";
        break;
    case 6:
        month = "July";
        break;
    case 7:
        month = "August";
        break;
    case 8:
        month = "September";
        break;
    case 9:
        month = "October";
        break;
    case 10:
        month = "November";
        break;
    case 11:
        month = "December";
        break;
    default:
        month = "Unknown";
        break;
    }

    // Get the day name
    char *day;
    switch (systime->tm_wday)
    {
    case 0:
        day = "Sunday";
        break;
    case 1:
        day = "Monday";
        break;
    case 2:
        day = "Tuesday";
        break;
    case 3:
        day = "Wednesday";
        break;
    case 4:
        day = "Thursday";
        break;
    case 5:
        day = "Friday";
        break;
    case 6:
        day = "Saturday";
        break;
    default:
        day = "Unknown";
        break;
    }

    // Format: date-month-year 00:00:00 day
    sprintf(timeString, "%02d-%s-%d %02d:%02d:%02d %s",
            systime->tm_mday,
            month,
            systime->tm_year + 1900,
            systime->tm_hour,
            systime->tm_min,
            systime->tm_sec,
            day);
    return timeString;
}

// Function to read and display contacts from file
void readContactsFromFile()
{
    FILE *fp = fopen("db.dat", "rb");
    if (fp == NULL)
    {
        printf("Error opening file for reading\n");
        return;
    }

    Contact c;
    printf("\n==== Contacts in Database ====\n");

    while (fread(&c, sizeof(Contact), 1, fp) == 1)
    {
        printf("\nName: %s\n", c.name);
        printf("Phone: %s\n", c.phone);
        printf("Email: %s\n", c.email);
        printf("Address: %s\n", c.address);
        printf("Created At: %s\n", c.createdAt);
        printf("Updated At: %s\n", c.updatedAt);
        printf("-----------------------------\n");
    }

    fclose(fp);
}

int main()
{
    // 1. Write a contact to file
    FILE *fp = fopen("db.dat", "rb+");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    Contact c; // Allocate memory on the stack

    strcpy(c.name, "Miftah");
    strcpy(c.phone, "01798306642");
    strcpy(c.email, "miftahulislam.ece@gmail.com");
    strcpy(c.address, "Mithur more, Rajpara, Rajshahi");
    strcpy(c.createdAt, getCurrentTime());
    strcpy(c.updatedAt, getCurrentTime());

    fwrite(&c, sizeof(Contact), 1, fp); // Pass the address of c
    fwrite(&c, sizeof(Contact), 1, fp); // Pass the address of c
    fclose(fp);

    printf("Contact saved successfully\n");
    readContactsFromFile();

    return 0;
}