#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

// Structure to represent a user
typedef struct {
    char name[50];
    int accountNumber;
    double balance;
    double totalDeposits;
    double totalWithdrawals;
} User;

// Array to store user information
User users[MAX_USERS];
int numUsers = 0;

// Function to register a new user
void registerUser() {
    if (numUsers >= MAX_USERS) {
        printf("Maximum number of users reached.\n\n");
        return;
    }

    User newUser;
    printf("Enter name: ");
    scanf("%s", newUser.name);
    printf("Enter account number: ");
    scanf("%d", &newUser.accountNumber);
    printf("Enter initial deposit: ");
    scanf("%lf", &newUser.balance);

    newUser.totalDeposits = 0.0;
    newUser.totalWithdrawals = 0.0;

    users[numUsers++] = newUser;
    printf("User registered successfully.\n\n");
}

// Function to save user information to a file
void saveUsersToFile() {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        printf("Sorry this information are already used.\n\n");
        return;
    }

    for (int i = 0; i < numUsers; i++) {
        fprintf(file, "%s %d %.2lf %.2lf %.2lf\n", users[i].name, users[i].accountNumber, users[i].balance, users[i].totalDeposits, users[i].totalWithdrawals);
    }

    fclose(file);
    printf("User information saved to file.\n\n");
}

// Function to delete a user account
void deleteUser() {
    int accountNumber;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    int userIndex = findUserByAccountNumber(accountNumber);
    if (userIndex == -1) {
        printf("Account not found.\n");
        return;
    }

    // Shift the remaining users in the array to fill the gap
    for (int i = userIndex; i < numUsers - 1; i++) {
        users[i] = users[i + 1];
    }

    numUsers--;

    printf("Account deleted successfully.\n\n");
}

// Function to load user information from a file
void loadUsersFromFile() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("There are no account from this bank.\n\n");
        return;
    }

    numUsers = 0;

    while (fscanf(file, "%s %d %lf %lf %lf", users[numUsers].name, &users[numUsers].accountNumber, &users[numUsers].balance, &users[numUsers].totalDeposits, &users[numUsers].totalWithdrawals) != EOF) {
        numUsers++;
    }

    fclose(file);
    printf("User information loaded from file.\n\n");
}

// Function to find a user by account number
int findUserByAccountNumber(int accountNumber) {
    for (int i = 0; i < numUsers; i++) {
        if (users[i].accountNumber == accountNumber) {
            return i;  // Return the index of the user in the array
        }
    }

    return -1;  // User not found
}

// Function to update user information
void updateUser() {
    int accountNumber;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    int userIndex = findUserByAccountNumber(accountNumber);
    if (userIndex == -1) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter new name: ");
    scanf("%s", users[userIndex].name);
    printf("Enter new balance: ");
    scanf("%lf", &users[userIndex].balance);

    printf("User information updated.\n\n");
}

// Function to deposit money into a user's account
void deposit() {
    int accountNumber;
    double amount;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    printf("Enter amount to deposit: ");
    scanf("%lf", &amount);

    int userIndex = findUserByAccountNumber(accountNumber);
    if (userIndex == -1) {
        printf("Account not found.\n\n");
        return;
    }

    users[userIndex].balance += amount;
    users[userIndex].totalDeposits += amount;

    printf("Deposit successful.\n\n");
}

// Function to withdraw money from a user's account
void withdraw() {
    int accountNumber;
    double amount;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    printf("Enter amount to withdraw: ");
    scanf("%lf", &amount);

    int userIndex = findUserByAccountNumber(accountNumber);
    if (userIndex == -1) {
        printf("Account not found.\n\n");
        return;
    }

    if (users[userIndex].balance >= amount) {
        users[userIndex].balance -= amount;
        users[userIndex].totalWithdrawals += amount;
        float service_charge;
        service_charge = 0.05 * users[userIndex].totalWithdrawals;
        users[userIndex].balance  = users[userIndex].balance - service_charge;
        printf("Withdrawal successful.\n");
        printf("The service charge: %.2f\n",service_charge);
        printf("Balance: %.2lf\n", users[userIndex].balance);
    } else {
        printf("Insufficient funds.\n\n");
    }
}

// Function todisplay the balance, total deposits, and total withdrawals for a user
void displaySummary() {
    int accountNumber;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    int userIndex = findUserByAccountNumber(accountNumber);
    if (userIndex == -1) {
        printf("Account not found.\n\n");
        return;
    }

    printf("Name: %s\n", users[userIndex].name);
    printf("Account Number: %d\n", users[userIndex].accountNumber);
    printf("Balance: %.2lf\n", users[userIndex].balance);
    printf("Total Deposits: %.2lf\n", users[userIndex].totalDeposits);
    printf("Total Withdrawals: %.2lf\n", users[userIndex].totalWithdrawals);
}

int main() {
    int choice;

    // Load user information from file at the start
    loadUsersFromFile();

do {
    printf("\t\t----Bank Management System----\n\n");
    printf("\t1. Register new user\n");
    printf("\t2. Update user information\n");
    printf("\t3. Deposit money\n");
    printf("\t4. Withdraw money\n");
    printf("\t5. Display summary\n");
    printf("\t6. Delete user account\n");  // Added option for deleting an account
    printf("\t7. Save user information to file\n");
    printf("\t0. Exit\n\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            updateUser();
            break;
        case 3:
            deposit();
            break;
        case 4:
            withdraw();
            break;
        case 5:
            displaySummary();
            break;
        case 6:
            deleteUser();  // Call the new function for deleting an account
            break;
        case 7:
            saveUsersToFile();
            break;
        case 0:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n\n");
    }
    printf("\n\n");
} while (choice != 0);

    return 0;
}