#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define MAX_TRANSACTIONS 100

typedef struct {
    char name[100];
    int balance;
} Account;

typedef struct {
    char type; // 'W' for Withdrawal, 'D' for Deposit, 'T' for Transfer
    int amount;
} Transaction;

Account accounts[MAX_ACCOUNTS];
Transaction transactions[MAX_TRANSACTIONS];
int numAccounts = 0;
int numTransactions = 0;

void displayMenu() {
    printf("\nATM Interface\n");
    printf("1. Check Balance\n");
    printf("2. Withdraw\n");
    printf("3. Deposit\n");
    printf("4. Transfer\n");
    printf("5. View Transaction History\n");
    printf("6. Quit\n");
    printf("Enter your choice: ");
}

void checkBalance(int accountIndex) {
    printf("Your balance is: %d\n", accounts[accountIndex].balance);
}

void withdraw(int accountIndex, int amount) {
    if (amount > accounts[accountIndex].balance) {
        printf("Insufficient funds.\n");
    } else {
        accounts[accountIndex].balance -= amount;
        printf("Withdrawn %d. Current balance: %d\n", amount, accounts[accountIndex].balance);

        // Update transaction history
        transactions[numTransactions].type = 'W';
        transactions[numTransactions].amount = amount;
        numTransactions++;
    }
}

void deposit(int accountIndex, int amount) {
    accounts[accountIndex].balance += amount;
    printf("Deposited %d. Current balance: %d\n", amount, accounts[accountIndex].balance);

    // Update transaction history
    transactions[numTransactions].type = 'D';
    transactions[numTransactions].amount = amount;
    numTransactions++;
}

void transfer(int accountIndex, int targetAccountIndex, int amount) {
    if (amount > accounts[accountIndex].balance) {
        printf("Insufficient funds for transfer.\n");
    } else {
        accounts[accountIndex].balance -= amount;
        accounts[targetAccountIndex].balance += amount;
        printf("Transferred %d to account %s. Current balance: %d\n", amount, accounts[targetAccountIndex].name, accounts[accountIndex].balance);

        // Update transaction history for both accounts
        transactions[numTransactions].type = 'T';
        transactions[numTransactions].amount = amount;
        numTransactions++;
        transactions[numTransactions].type = 'T';
        transactions[numTransactions].amount = -amount;
        numTransactions++;
    }
}

void viewTransactionHistory() {
    printf("\nTransaction History:\n");
    for (int i = 0; i < numTransactions; i++) {
        if (transactions[i].type == 'W') {
            printf("Withdrawal of %d\n", transactions[i].amount);
        } else if (transactions[i].type == 'D') {
            printf("Deposit of %d\n", transactions[i].amount);
        } else if (transactions[i].type == 'T') {
            if (transactions[i].amount > 0) {
                printf("Transfer to another account: %d\n", transactions[i].amount);
            } else {
                printf("Transfer from another account: %d\n", -transactions[i].amount);
            }
        }
    }
}

int main() {
    // Initialize accounts (for demonstration purposes)
    strcpy(accounts[0].name, "Ayan");
    accounts[0].balance = 1000;
    strcpy(accounts[1].name, "Octanet");
    accounts[1].balance = 1500;
    numAccounts = 2;

    int choice;
    int accountIndex = 0;  // Default account for demonstration purposes

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance(accountIndex);
                break;

            case 2:
                {
                    int amount;
                    printf("Enter the amount to withdraw: ");
                    scanf("%d", &amount);
                    withdraw(accountIndex, amount);
                }
                break;

            case 3:
                {
                    int amount;
                    printf("Enter the amount to deposit: ");
                    scanf("%d", &amount);
                    deposit(accountIndex, amount);
                }
                break;

            case 4:
                {
                    int targetAccountIndex;
                    printf("Enter the target account index: ");
                    scanf("%d", &targetAccountIndex);
                    if (targetAccountIndex >= 0 && targetAccountIndex < numAccounts && targetAccountIndex != accountIndex) {
                        int amount;
                        printf("Enter the amount to transfer: ");
                        scanf("%d", &amount);
                        transfer(accountIndex, targetAccountIndex, amount);
                    } else {
                        printf("Invalid target account index.\n");
                    }
                }
                break;

            case 5:
                viewTransactionHistory();
                break;

            case 6:
                printf("Exiting. Thank you!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (1);

    return 0;
}
