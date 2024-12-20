#include "task1.h"

class BankAccount {
    protected:
    int accountNumber;
    std::string holderName;
    double balance;
    public:
    BankAccount(const int accountNumber, const std::string &holderName)
    : accountNumber(accountNumber), holderName(holderName) {}
    void deposit(const double amount) {
        this->balance += amount;
        std::cout << "Внесено " << amount << std::endl;
    }
    void withdraw(const double amount) {
        this->balance -= amount;
        std::cout << "Снято " << amount << std::endl;
    }
    double getBalance() {
        return this->balance;
    }
};

class SavingsAccount: public BankAccount {
    protected:
    int percentage;
    public:
    SavingsAccount(const int accountNumber, const std::string &holderName, const int percentage)
    : BankAccount(accountNumber, holderName), percentage(percentage) {}
    void income() {
        this->balance += balance * (this->percentage * 0.01);
    }
};

int main() {
    task1();

    BankAccount account1(1, "bob");
    account1.deposit(1000);
    account1.withdraw(100);
    std::cout << account1.getBalance() << std::endl;

    SavingsAccount account2(2, "ivan", 13);
    account2.deposit(1000);
    account2.income();
    std::cout << account2.getBalance() << std::endl;


    return 0;
}
