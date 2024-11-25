#include <stdio.h>
#include "password.h"

int main() {
    int choice;
    int userType;

    printf("Are you a new user or an existing user?\n");
    printf("1. New User\n2. Existing User\n");
    printf("Enter your choice: ");
    scanf("%d", &userType);

    loadMasterPasswords();  

    if (userType == 1) {
        setMasterPassword();
    } else if (userType == 2) {
        if (!verifyMasterPassword()) {
            printf("Incorrect master password. Exiting...\n");
            return 1;
        }
    } else {
        printf("Invalid choice. Exiting...\n");
        return 1;
    }

    while (1) {
        printf("\nPassword Manager Menu:\n");
        printf("1. Create an Entry \n");
        printf("2. Search an Entry\n");
        printf("3. Display All Entries\n");
        printf("4. Update an Entry\n");
        printf("5. Delete an Entry\n");
        printf("6. Delete All Entries\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createEntry();
                break;
            case 2:
                searchEntry();
                break;
            case 3:
                displayAllEntries();
                break;
            case 4:
                updateEntry();
                break;
            case 5:
                deleteEntry();
                break;
            case 6:
                deleteAllEntries();
                break;
            case 7:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}