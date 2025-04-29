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