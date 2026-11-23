#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class BankException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class InvalidAmountException : public BankException {
public:
    InvalidAmountException() : BankException("Amount must be greater than zero.") {}
};

class InsufficientFundsException : public BankException {
public:
    InsufficientFundsException() : BankException("Insufficient balance for withdrawal.") {}
};

class BankAccount {
public:
    BankAccount(std::string holder, double initialBalance)
        : holder_(std::move(holder)), balance_(initialBalance) {
        if (initialBalance < 0) throw InvalidAmountException();
    }

    void deposit(double amount) {
        if (amount <= 0) throw InvalidAmountException();
        balance_ += amount;
    }

    void withdraw(double amount) {
        if (amount <= 0) throw InvalidAmountException();
        if (amount > balance_) throw InsufficientFundsException();
        balance_ -= amount;
    }

    void display() const {
        std::cout << "Account Holder: " << holder_ << "\nBalance: Rs. " << balance_ << '\n';
    }

private:
    std::string holder_;
    double balance_;
};

int main() {
    BankAccount account("Arun", 5000.0);
    std::cout << "Initial Account Details:\n";
    account.display();

    try {
        std::cout << "\nDepositing Rs. 1000...\n";
        account.deposit(1000.0);
        std::cout << "Withdrawing Rs. 2000...\n";
        account.withdraw(2000.0);
        std::cout << "Withdrawing Rs. 10000...\n";
        account.withdraw(10000.0);
    } catch (const InsufficientFundsException& error) {
        std::cout << "Error: " << error.what() << '\n';
    } catch (const InvalidAmountException& error) {
        std::cout << "Error: " << error.what() << '\n';
    } catch (const BankException& error) {
        std::cout << "Bank error: " << error.what() << '\n';
    } catch (const std::exception& error) {
        std::cout << "Unexpected error: " << error.what() << '\n';
    }

    std::cout << "\nFinal Account Details:\n";
    account.display();
}
