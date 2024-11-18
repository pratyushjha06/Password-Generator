#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#define MASTER_PASSWORD_FILE "all_master_passwords.txt"
#define ENCRYPTION_KEY 0xAA  

typedef struct {
    char service[50];
    char username[50];
    char password[50];
} Entry;

int loadMasterPasswords();
void setMasterPassword();
int verifyMasterPassword();
void generatePassword(char *password, int length);
void createEntry();
void searchEntry();
void displayAllEntries();
void updateEntry();
void deleteEntry();
void deleteAllEntries();
void encrypt(char *data);
void setUserFile(char *masterPassword);

#endif