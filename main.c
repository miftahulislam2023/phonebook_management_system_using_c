#include <stdio.h>
#include <stdbool.h>
#include <contact.h>

// functions related to contacts
bool addContact(Contact *contact);
bool deleteContact(Contact *contact);
bool deleteByName(char *name);
bool deleteByPhone(char *name);
bool searchByName(char *name);
bool searchByPhone(char *phone);
bool updateContact(Contact *contact);
// functions related to files
bool displayContacts(FILE *contactDB);
bool saveContactsToFile(FILE *contactDB);
bool loadContactsFromFile(FILE *contactDB);

int main(void)
{
    bool isReady = false;
    printf("%d\n", isReady);

    return 0;
}