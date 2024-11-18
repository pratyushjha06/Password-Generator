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
        printf("1. Generate Password\n");
        printf("2. Create an Entry\n");
        printf("3. Search an Entry\n");
        printf("4. Display All Entries\n");
        printf("5. Update an Entry\n");
        printf("6. Delete an Entry\n");
        printf("7. Delete All Entries\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char password[20];
                generatePassword(password, 12);
                printf("Generated Password: %s\n", password);
                break;
            }
            case 2:
                createEntry();
                break;
            case 3:
                searchEntry();
                break;
            case 4:
                displayAllEntries();
                break;
            case 5:
                updateEntry();
                break;
            case 6:
                deleteEntry();
                break;
            case 7:
                deleteAllEntries();
                break;
            case 8:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}