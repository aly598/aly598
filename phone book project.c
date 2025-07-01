#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[50];
    char sex[10];
    char email[50];
    char address[100];
    char phone[15];
} Record;

Record phonebook[MAX];
int recordCount = 0;

void add_record() {
    if (recordCount >= MAX) {
        printf("Phone book is full!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", phonebook[recordCount].name);

    printf("Enter Sex: ");
    scanf(" %[^\n]", phonebook[recordCount].sex);

    printf("Enter Email: ");
    scanf(" %[^\n]", phonebook[recordCount].email);

    printf("Enter Address: ");
    scanf(" %[^\n]", phonebook[recordCount].address);

    printf("Enter Phone Number: ");
    scanf(" %[^\n]", phonebook[recordCount].phone);

    recordCount++;
    printf("Record added successfully.\n");
}

void list_record() {
    if (recordCount == 0) {
        printf("No records found.\n");
        return;
    }

    printf("\nPhone Book Records:\n");
    for (int i = 0; i < recordCount; i++) {
        printf("Record %d:\n", i + 1);
        printf("Name: %s\n", phonebook[i].name);
        printf("Sex: %s\n", phonebook[i].sex);
        printf("Email: %s\n", phonebook[i].email);
        printf("Address: %s\n", phonebook[i].address);
        printf("Phone: %s\n\n", phonebook[i].phone);
    }
}

void modify_record() {
    int index;
    printf("Enter record number to modify (1-->%d): ", recordCount);
    scanf("%d", &index);

    if (index < 1 || index > recordCount) {
        printf("Invalid record number.\n");
        return;
    }

    printf("Enter new details for Record %d:\n", index);

    index--;
    printf("Enter Name: ");
    scanf(" %[^\n]", phonebook[index].name);

    printf("Enter Sex: ");
    scanf(" %[^\n]", phonebook[index].sex);

    printf("Enter Email: ");
    scanf(" %[^\n]", phonebook[index].email);

    printf("Enter Address: ");
    scanf(" %[^\n]", phonebook[index].address);

    printf("Enter Phone Number: ");
    scanf(" %[^\n]", phonebook[index].phone);

    printf("Record modified successfully.\n");
}

void delete_record() {
    int index;
    printf("Enter record number to delete (1-->%d): ", recordCount);
    scanf("%d", &index);

    if (index < 1 || index > recordCount) {
        printf("Invalid record number.\n");
        return;
    }
    index--; // Adjust to 0-based index

    for (int i = index; i < recordCount - 1; i++) {
        phonebook[i] = phonebook[i + 1];
    }
    recordCount--;
    printf("Record deleted successfully.\n");
}

void search_record() {
    int index;
    printf("Enter record number to search (1-->%d): ", recordCount);
    scanf("%d", &index);

    if (index < 1 || index > recordCount) {
        printf("Record not found.\n");
        return;
    }

    index--; // Adjust to 0-based index
    printf("\nRecord %d Details:\n", index + 1);
    printf("Name: %s\n", phonebook[index].name);
    printf("Sex: %s\n", phonebook[index].sex);
    printf("Email: %s\n", phonebook[index].email);
    printf("Address: %s\n", phonebook[index].address);
    printf("Phone: %s\n", phonebook[index].phone);
}

void menu() {
    int choice;
    while (1) {
        printf("\nPhone Book Menu:\n");
        printf("1. Add Record\n");
        printf("2. List Records\n");
        printf("3. Modify Record\n");
        printf("4. Delete Record\n");
        printf("5. Search Record\n");
        printf("6. Exit\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_record(); break;
            case 2: list_record(); break;
            case 3: modify_record(); break;
            case 4: delete_record(); break;
            case 5: search_record(); break;
            case 6: printf("Exiting...\n"); return;
            default: printf("Invalid choice. Please try again.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
