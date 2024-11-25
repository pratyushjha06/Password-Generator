#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "password.h"

char masterPassword[50];
char userFileName[100];
char storedPasswords[100][50];  
int storedPasswordCount = 0; 

void setUserFile(char *password) {
    unsigned long hash = 5381;
    int c;
    while ((c = *password++)) {
        hash = ((hash << 5) + hash) + c;
    }
    snprintf(userFileName, sizeof(userFileName), "%lu_passwords.txt", hash);
}

void encrypt(char *data) {
    for (int i = 0; data[i] != '\0'; i++) {
        data[i] ^= ENCRYPTION_KEY;
    }
}

int loadMasterPasswords() {
    FILE *file = fopen(MASTER_PASSWORD_FILE, "r");
    if (file == NULL) {
        return 0;
    }

    while (fscanf(file, "%s", storedPasswords[storedPasswordCount]) != EOF) {
        encrypt(storedPasswords[storedPasswordCount]); 
        storedPasswordCount++;
    }
    fclose(file);
    return storedPasswordCount;
}

void setMasterPassword() {
    FILE *file = fopen(MASTER_PASSWORD_FILE, "a");
    if (!file) {
        printf("Failed to set master password.\n");
        return;
    }

    printf("Set your master password: ");
    scanf("%s", masterPassword);

    encrypt(masterPassword);
    fprintf(file, "%s\n", masterPassword);
    fclose(file);

    encrypt(masterPassword);
    strcpy(storedPasswords[storedPasswordCount++], masterPassword);
    setUserFile(masterPassword);

    printf("Master password set successfully!\n");
}

int verifyMasterPassword() {
    char input[50];
    printf("Enter master password: ");
    scanf("%s", input);

    for (int i = 0; i < storedPasswordCount; i++) {
        if (strcmp(input, storedPasswords[i]) == 0) {
            strcpy(masterPassword, input); 
            setUserFile(masterPassword); 
            return 1;
        }
    }
    return 0;
}

void generatePassword(char *password, int length) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789@#$%";
    srand(time(0));
    for (int i = 0; i < length; i++) {
        password[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    password[length] = '\0';
}

void createEntry() {
    Entry entry;
    char choice;
    FILE *file = fopen(userFileName, "a");
    if (!file) {
        printf("Could not open file.\n");
        return;
    }

    printf("Enter service name: ");
    scanf("%s", entry.service);
    printf("Enter username: ");
    scanf("%s", entry.username);

    printf("Do you want to generate a password? (y/n): ");
    scanf(" %c", &choice);  
    if (choice == 'y' || choice == 'Y') {
        generatePassword(entry.password, 12);  
        printf("Generated Password: %s\n", entry.password);
    } else {
        printf("Enter password: ");
        scanf("%s", entry.password);
    }

    encrypt(entry.password);
    fprintf(file, "%s %s %s\n", entry.service, entry.username, entry.password);
    fclose(file);

    printf("Entry added successfully!\n");
}

void searchEntry() {
    char service[50];
    Entry entry;
    int found = 0;
    FILE *file = fopen(userFileName, "r");
    if (!file) {
        printf("No entries found.\n");
        return;
    }

    printf("Enter service name to search: ");
    scanf("%s", service);

    while (fscanf(file, "%s %s %s", entry.service, entry.username, entry.password) != EOF) {
        if (strcmp(entry.service, service) == 0) {
            encrypt(entry.password); 
            printf("Service: %s\nUsername: %s\nPassword: %s\n", entry.service, entry.username, entry.password);
            found = 1;
            break;
        }
    }

    if (!found) printf("No entry found for %s.\n", service);
    fclose(file);
}

void displayAllEntries() {
    Entry entry;
    FILE *file = fopen(userFileName, "r");
    if (!file) {
        printf("No entries to display.\n");
        return;
    }

    printf("All Entries:\n");
    while (fscanf(file, "%s %s %s", entry.service, entry.username, entry.password) != EOF) {
        encrypt(entry.password);
        printf("Service: %s\nUsername: %s\nPassword: %s\n", entry.service, entry.username, entry.password);
    }
    fclose(file);
}

void updateEntry() {
    char service[50];
    Entry entry;
    int found = 0;
    FILE *file = fopen(userFileName, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (!file || !tempFile) {
        printf("Could not open file.\n");
        return;
    }

    printf("Enter service name to update: ");
    scanf("%s", service);

    while (fscanf(file, "%s %s %s", entry.service, entry.username, entry.password) != EOF) {
        if (strcmp(entry.service, service) == 0) {
            encrypt(entry.password); 
            printf("Enter new username: ");
            scanf("%s", entry.username);
            printf("Enter new password: ");
            scanf("%s", entry.password);
            encrypt(entry.password); 
            found = 1;
        }
        fprintf(tempFile, "%s %s %s\n", entry.service, entry.username, entry.password);
    }

    fclose(file);
    fclose(tempFile);
    remove(userFileName);
    rename("temp.txt", userFileName);

    if (found) printf("Entry updated successfully!\n");
    else printf("No entry found for %s.\n", service);
}

void deleteEntry() {
    char service[50];
    Entry entry;
    int found = 0;
    FILE *file = fopen(userFileName, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (!file || !tempFile) {
        printf("Could not open file.\n");
        return;
    }

    printf("Enter service name to delete: ");
    scanf("%s", service);

    while (fscanf(file, "%s %s %s", entry.service, entry.username, entry.password) != EOF) {
        if (strcmp(entry.service, service) != 0) {
            fprintf(tempFile, "%s %s %s\n", entry.service, entry.username, entry.password);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(userFileName);
    rename("temp.txt", userFileName);

    if (found) printf("Entry deleted successfully!\n");
    else printf("No entry found for %s.\n", service);
}

void deleteAllEntries() {
    remove(userFileName);
    printf("All entries deleted successfully!\n");
}