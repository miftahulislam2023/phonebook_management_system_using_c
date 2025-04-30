#include <stdio.h>
#include <stdbool.h>

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
    char createdAt;
    char updatedAt;
    bool isDeleted;
} Contact;

typedef struct
{
    Contact contact;
    Node *next;
} Node;

int main()
{
    FILE *fp = fopen("db.dat", "wb");
    Contact *c;
    strcpy(c->name, "Miftah");
    strcpy(c->phone, "01798306642");
    strcpy(c->email, "miftahulislam.ece@gmail.com");
    strcpy(c->address, "Mithur more, Rajpara, Rajshahi");
    
    return 0;
}