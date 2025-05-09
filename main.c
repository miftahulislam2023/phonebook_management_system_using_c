#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
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

typedef struct Node
{
    Contact contact;
    struct Node *next;
} Node;

// Global head pointer for linked list
Node *head = NULL;

// Function prototypes
char *getCurrentTime();
Node *createContact();
bool addContact(Contact newContact);
bool deleteByName(char *name);
bool deleteByPhone(char *phone);
bool searchByName(char *name);
bool searchByPhone(char *phone);
bool updateContact(char *name);
void displayContacts();
bool saveContactsToFile(char *filename);
bool loadContactsFromFile(char *filename);

int main(void)
{
    // Try to load contacts from file at startup
    loadContactsFromFile("contacts.dat");

    int choice;
    char searchName[MAXNAME];
    char searchPhone[MAXPHONE];

    while (1)
    {
        printf("\n=== PHONE BOOK MANAGEMENT ===\n");
        printf("1. Add Contact\n");
        printf("2. Delete Contact\n");
        printf("3. Search Contact\n");
        printf("4. Update Contact\n");
        printf("5. Display All Contacts\n");
        printf("6. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer

        switch (choice)
        {
        case 1: // Add Contact
        {
            Node *newNode = createContact();
            if (newNode != NULL)
            {
                if (addContact(newNode->contact))
                {
                    printf("Contact added successfully!\n");
                    free(newNode); 
                }
                else
                {
                    printf("Failed to add contact.\n");
                    free(newNode);
                }
            }
            break;
        }
        case 2: // Delete Contact
        {
            int deleteChoice;
            printf("Delete by:\n");
            printf("1. Name\n");
            printf("2. Phone\n");
            printf("Enter your choice: ");
            scanf("%d", &deleteChoice);
            getchar(); // Clear input buffer

            if (deleteChoice == 1)
            {
                printf("Enter name to delete: ");
                fgets(searchName, MAXNAME, stdin);
                searchName[strcspn(searchName, "\n")] = 0; // Remove newline

                if (deleteByName(searchName))
                {
                    printf("Contact deleted successfully!\n");
                }
                else
                {
                    printf("Contact not found or deletion failed.\n");
                }
            }
            else if (deleteChoice == 2)
            {
                printf("Enter phone to delete: ");
                fgets(searchPhone, MAXPHONE, stdin);
                searchPhone[strcspn(searchPhone, "\n")] = 0; // Remove newline

                if (deleteByPhone(searchPhone))
                {
                    printf("Contact deleted successfully!\n");
                }
                else
                {
                    printf("Contact not found or deletion failed.\n");
                }
            }
            else
            {
                printf("Invalid choice.\n");
            }
            break;
        }
        case 3: // Search Contact
        {
            int searchChoice;
            printf("Search by:\n");
            printf("1. Name\n");
            printf("2. Phone\n");
            printf("Enter your choice: ");
            scanf("%d", &searchChoice);
            getchar(); // Clear input buffer

            if (searchChoice == 1)
            {
                printf("Enter name to search: ");
                fgets(searchName, MAXNAME, stdin);
                searchName[strcspn(searchName, "\n")] = 0; // Remove newline

                if (!searchByName(searchName))
                {
                    printf("Contact not found.\n");
                }
            }
            else if (searchChoice == 2)
            {
                printf("Enter phone to search: ");
                fgets(searchPhone, MAXPHONE, stdin);
                searchPhone[strcspn(searchPhone, "\n")] = 0; // Remove newline

                if (!searchByPhone(searchPhone))
                {
                    printf("Contact not found.\n");
                }
            }
            else
            {
                printf("Invalid choice.\n");
            }
            break;
        }
        case 4: // Update Contact
        {
            printf("Enter name to update: ");
            fgets(searchName, MAXNAME, stdin);
            searchName[strcspn(searchName, "\n")] = 0; // Remove newline

            if (updateContact(searchName))
            {
                printf("Contact updated successfully!\n");
            }
            else
            {
                printf("Contact not found or update failed.\n");
            }
            break;
        }
        case 5: // Display Contacts
        {
            displayContacts();
            break;
        }
        case 6: // Save & Exit
        {
            if (saveContactsToFile("contacts.dat"))
            {
                printf("Contacts saved successfully!\n");
            }
            else
            {
                printf("Failed to save contacts.\n");
            }
            printf("Exiting...\n");

            // Free all memory before exit
            Node *current = head;
            Node *next;

            while (current != NULL)
            {
                next = current->next;
                free(current);
                current = next;
            }

            return 0;
        }
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

//Get current time
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

// Create a new contact node from user input
Node *createContact()
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    printf("Enter Name: ");
    fgets(newNode->contact.name, MAXNAME, stdin);
    newNode->contact.name[strcspn(newNode->contact.name, "\n")] = 0; // Remove newline

    printf("Enter Phone: ");
    fgets(newNode->contact.phone, MAXPHONE, stdin);
    newNode->contact.phone[strcspn(newNode->contact.phone, "\n")] = 0;

    printf("Enter Email: ");
    fgets(newNode->contact.email, MAXEMAIL, stdin);
    newNode->contact.email[strcspn(newNode->contact.email, "\n")] = 0;

    printf("Enter Address: ");
    fgets(newNode->contact.address, MAXADDRESS, stdin);
    newNode->contact.address[strcspn(newNode->contact.address, "\n")] = 0;

    // Set creation time
    strcpy(newNode->contact.createdAt, getCurrentTime());
    strcpy(newNode->contact.updatedAt, newNode->contact.createdAt); // Initially same as created time

    newNode->next = NULL;
    return newNode;
}

// Add a contact in alphabetical order by name
bool addContact(Contact newContact)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        return false;
    }

    // Copy the contact data
    newNode->contact = newContact;
    newNode->next = NULL;

    // If list is empty or new contact comes before first contact
    if (head == NULL || strcmp(newNode->contact.name, head->contact.name) < 0)
    {
        newNode->next = head;
        head = newNode;
        return true;
    }

    // Find the position to insert (alphabetically by name)
    Node *current = head;
    Node *prev = NULL;

    while (current != NULL && strcmp(newNode->contact.name, current->contact.name) > 0)
    {
        prev = current;
        current = current->next;
    }

    // Insert the new node
    newNode->next = current;
    prev->next = newNode;

    return true;
}

// Delete a contact by name
bool deleteByName(char *name)
{
    if (head == NULL)
    {
        return false;
    }

    // If head node contains the contact to be deleted
    if (strcmp(head->contact.name, name) == 0)
    {
        Node *temp = head;
        head = head->next;
        free(temp);
        return true;
    }

    // Search for the contact to delete
    Node *current = head;
    Node *prev = NULL;

    while (current != NULL && strcmp(current->contact.name, name) != 0)
    {
        prev = current;
        current = current->next;
    }

    // If contact was not found
    if (current == NULL)
    {
        return false;
    }

    // Remove the node
    prev->next = current->next;
    free(current);

    return true;
}

// Delete a contact by phone number
bool deleteByPhone(char *phone)
{
    if (head == NULL)
    {
        return false;
    }

    // If head node contains the contact to be deleted
    if (strcmp(head->contact.phone, phone) == 0)
    {
        Node *temp = head;
        head = head->next;
        free(temp);
        return true;
    }

    // Search for the contact to delete
    Node *current = head;
    Node *prev = NULL;

    while (current != NULL && strcmp(current->contact.phone, phone) != 0)
    {
        prev = current;
        current = current->next;
    }

    // If contact was not found
    if (current == NULL)
    {
        return false;
    }

    // Remove the node
    prev->next = current->next;
    free(current);

    return true;
}

// Search for a contact by name and display it
bool searchByName(char *name)
{
    Node *current = head;
    bool found = false;

    while (current != NULL)
    {
        if (strcmp(current->contact.name, name) == 0)
        {
            printf("Contact Found!\n");
            printf("Name: %s\n", current->contact.name);
            printf("Phone: %s\n", current->contact.phone);
            printf("Email: %s\n", current->contact.email);
            printf("Address: %s\n", current->contact.address);
            printf("Created At: %s\n", current->contact.createdAt);
            printf("Updated At: %s\n", current->contact.updatedAt);
            found = true;
        }
        current = current->next;
    }

    return found;
}

// Search for a contact by phone number and display it
bool searchByPhone(char *phone)
{
    Node *current = head;
    bool found = false;

    while (current != NULL)
    {
        if (strcmp(current->contact.phone, phone) == 0)
        {
            printf("Contact Found!\n");
            printf("Name: %s\n", current->contact.name);
            printf("Phone: %s\n", current->contact.phone);
            printf("Email: %s\n", current->contact.email);
            printf("Address: %s\n", current->contact.address);
            printf("Created At: %s\n", current->contact.createdAt);
            printf("Updated At: %s\n", current->contact.updatedAt);
            found = true;
        }
        current = current->next;
    }

    return found;
}

// Update a contact's details
bool updateContact(char *name)
{
    Node *current = head;

    // Find the contact
    while (current != NULL)
    {
        if (strcmp(current->contact.name, name) == 0)
        {
            printf("Enter new phone: ");
            fgets(current->contact.phone, MAXPHONE, stdin);
            current->contact.phone[strcspn(current->contact.phone, "\n")] = 0;

            printf("Enter new email: ");
            fgets(current->contact.email, MAXEMAIL, stdin);
            current->contact.email[strcspn(current->contact.email, "\n")] = 0;

            printf("Enter new address: ");
            fgets(current->contact.address, MAXADDRESS, stdin);
            current->contact.address[strcspn(current->contact.address, "\n")] = 0;

            // Update the updated_at time
            strcpy(current->contact.updatedAt, getCurrentTime());

            return true;
        }
        current = current->next;
    }

    return false;
}

// Display all contacts in alphabetical order
void displayContacts()
{
    if (head == NULL)
    {
        printf("No contacts available. Please add some.\n");
        return;
    }

    Node *current = head;
    int count = 1;

    printf("=== Contact List ===\n");

    while (current != NULL)
    {
        printf("%d. Name: %s\n", count, current->contact.name);
        printf("   Phone: %s\n", current->contact.phone);
        printf("   Email: %s\n", current->contact.email);
        printf("   Address: %s\n", current->contact.address);
        printf("   Created At: %s\n", current->contact.createdAt);
        printf("   Updated At: %s\n", current->contact.updatedAt);
        printf("\n");

        current = current->next;
        count++;
    }
}

// Save contacts to file
bool saveContactsToFile(char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        return false;
    }

    Node *current = head;

    while (current != NULL)
    {
        fwrite(&(current->contact), sizeof(Contact), 1, file);
        current = current->next;
    }

    fclose(file);
    return true;
}

// Load contacts from file
bool loadContactsFromFile(char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        return false;
    }

    // Clear existing list
    Node *current = head;
    Node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    head = NULL;

    // Read contacts from file
    Contact temp;

    while (fread(&temp, sizeof(Contact), 1, file) == 1)
    {
        addContact(temp);
    }

    fclose(file);
    return true;
}
