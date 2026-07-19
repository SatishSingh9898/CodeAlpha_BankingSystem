#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Transaction Class
class Transaction
{
public:
    string type;
    double amount;

    Transaction(string t, double a)
    {
        type = t;
        amount = a;
    }
};

// Customer Class
class Customer
{
public:
    int customerID;
    string name;

    Customer(int id, string n)
    {
        customerID = id;
        name = n;
    }
};

// Account Class
class Account
{
private:
    Customer customer;
    int accountNumber;
    double balance;
    vector<Transaction> history;

public:
    Account(Customer c, int accNo, double initialBalance)
        : customer(c)
    {
        accountNumber = accNo;
        balance = initialBalance;
    }

    void deposit(double amount)
    {
        balance += amount;
        history.push_back(Transaction("Deposit", amount));
        cout << "\nDeposit Successful!\n";
    }

    void withdraw(double amount)
    {
        if (amount > balance)
        {
            cout << "\nInsufficient Balance!\n";
            return;
        }

        balance -= amount;
        history.push_back(Transaction("Withdraw", amount));
        cout << "\nWithdrawal Successful!\n";
    }

    void transfer(Account &receiver, double amount)
    {
        if (amount > balance)
        {
            cout << "\nInsufficient Balance!\n";
            return;
        }

        balance -= amount;
        receiver.balance += amount;

        history.push_back(Transaction("Transfer Sent", amount));
        receiver.history.push_back(Transaction("Transfer Received", amount));

        cout << "\nTransfer Successful!\n";
    }

    void displayAccount()
    {
        cout << "\n========== ACCOUNT DETAILS ==========\n";
        cout << "Customer ID   : " << customer.customerID << endl;
        cout << "Customer Name : " << customer.name << endl;
        cout << "Account No.   : " << accountNumber << endl;
        cout << "Balance       : Rs. " << fixed << setprecision(2)
             << balance << endl;
    }

    void showTransactions()
    {
        cout << "\n------ Transaction History ------\n";

        if (history.empty())
        {
            cout << "No Transactions Found.\n";
            return;
        }

        for (int i = 0; i < history.size(); i++)
        {
            cout << i + 1 << ". "
                 << history[i].type
                 << " : Rs. "
                 << history[i].amount << endl;
        }
    }
};

int main()
{
    Customer c1(101, "Satish Singh");
    Customer c2(102, "Rahul Kumar");

    Account acc1(c1, 5001, 10000);
    Account acc2(c2, 5002, 5000);

    int choice;
    double amount;

    do
    {
        cout << "\n==============================";
        cout << "\n      BANKING SYSTEM";
        cout << "\n==============================";
        cout << "\n1. Deposit";
        cout << "\n2. Withdraw";
        cout << "\n3. Transfer";
        cout << "\n4. Account Details";
        cout << "\n5. Transaction History";
        cout << "\n6. Exit";
        cout << "\n\nEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Deposit Amount: ";
            cin >> amount;
            acc1.deposit(amount);
            break;

        case 2:
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;
            acc1.withdraw(amount);
            break;

        case 3:
            cout << "Enter Transfer Amount: ";
            cin >> amount;
            acc1.transfer(acc2, amount);
            break;

        case 4:
            acc1.displayAccount();
            break;

        case 5:
            acc1.showTransactions();
            break;

        case 6:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}