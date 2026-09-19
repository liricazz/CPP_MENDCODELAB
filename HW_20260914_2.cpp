// Task 2
#include <iostream>
#include <string>
#include <vector>

enum class Status { ACTIVE, FROZEN, CLOSED };

struct Client {
    std::string name;
    int id;
};

class BankAccount {
public:
    BankAccount(const Client& c, double initial)
        : owner(c), balance(initial), status(Status::ACTIVE), transactions(0) {}

    void withdraw(double amount) const {
        if (status != Status::ACTIVE) {
            std::cout << owner.name << ": счёт не активен, снятие отклонено\n";
            return;
        }
        if (amount > balance) {
            std::cout << owner.name << ": недостаточно средств\n";
            return;
        }
        balance -= amount;
        ++transactions;
        std::cout << owner.name << ": снято " << amount
                  << ", остаток " << balance << '\n';
    }

    void deposit(double amount) {
        if (status != Status::ACTIVE) return;
        balance += amount;
        ++transactions;
        std::cout << owner.name << ": внесено " << amount
                  << ", баланс " << balance << '\n';
    }

    double getBalance() const { return balance; }
    Status getStatus() const { return status; }

    friend void audit_accounts(const std::vector<BankAccount>& accounts);

    friend class TaxInspector;

private:
    Client owner;
    double balance;
    Status status;
    mutable int transactions;
};

// Внешняя дружественная функция
void audit_accounts(const std::vector<BankAccount>& accounts) {
    double total = 0;
    for (const auto& acc : accounts) {
        total += acc.balance;
    }
    std::cout << "=== Аудит ===\nОбщая сумма в банке: " << total << "\n";
}

class TaxInspector {
public:
    static void freeze(BankAccount& acc) {
        acc.status = Status::FROZEN;
        std::cout << "TaxInspector: счёт " << acc.owner.name << " заморожен\n";
    }
};

int main() {
    std::vector<BankAccount> accounts = {
        BankAccount({"Alice", 1}, 1000),
        BankAccount({"Bob", 2}, 2500),
        BankAccount({"Carol", 3}, 500)
    };

    accounts[0].deposit(500);
    accounts[1].withdraw(1000);

    audit_accounts(accounts);

    TaxInspector::freeze(accounts[2]);
    accounts[2].withdraw(100);
    
    audit_accounts(accounts);
    return 0;
}