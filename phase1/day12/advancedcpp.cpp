#include<cstring>
#include<cstdlib>
#include<iostream>

using std::cout;
using std::endl;
struct Account 
{
    private: //secured
        char name[255];
        char number[20];
        double balance;
        char phoneNumber[20];
        int numberOfTransaction;
        bool _isActive;
    
    private: //properties
        void setName(char _name[]) { strcpy(name, _name); }
        void setNumber(char _number[]) { strcpy(number, _number); }
        
        void setBalance(double _balance) { balance = _balance; }
        void setNumberOfTransaction(int _numberOfTransaction) { numberOfTransaction = _numberOfTransaction; }
        void setActive(bool __isActive) { _isActive = __isActive; }
    public: //properties -> getter/setter | encapsulated properties 
        char* getName() {  return name; }
        //
        char* getNumber() {  return number;  }
        //
        void setPhoneNumber(char _phoneNumber[])  { strcpy(phoneNumber, _phoneNumber); }
        char* getPhoneNumber()  { return phoneNumber; }
        //
        double getBalance() { return balance; }
        //
        int getNumberOfTransaction() { return numberOfTransaction; }
        //
        bool isActive() { return _isActive; }
    public://first time initilization of the account 
        void init(char _name[], char _number[], char _phoneNumber[]);
    public: //behavours
        void withdraw(double amount);
        void deposit(double amount);
        //deactivate()
    
};

int main()
{
    Account account {}; 
    account.init((char*)"Abel", (char*)"1002001001", (char*)"1112223333");//mistake-fix later
    
    account.deposit(50000);
    account.deposit(75000);
    account.deposit(30000);
    account.withdraw(4);
    account.withdraw(5);
    account.deposit(60000);
    account.withdraw(4);
    account.withdraw(5);
    account.withdraw(4);
    account.withdraw(5);
    account.withdraw(4);
    account.withdraw(5);

    cout << "Account Holder Name:" << account.getName() << "[" 
         << (account.isActive() ? "Active" : "Inactive")
         << "]" 
         << endl;
    cout << "Account Number:" << account.getNumber() << endl;
    cout << "Phone Number:" << account.getPhoneNumber() << endl;
    cout << "Balance:$" << account.getBalance()  
         << "[" << account.getNumberOfTransaction() << " trans]" << endl;
    
    return EXIT_SUCCESS;
}

void Account::withdraw( double amount)
{
    //validate amount as not negative
    //validate balance >= amount
    setBalance(getBalance()-amount);
    
    setNumberOfTransaction(getNumberOfTransaction() + 1);
}

void Account::deposit(double amount)
{
    //validate amount as not negative
    setBalance(amount+getBalance());
    setNumberOfTransaction(getNumberOfTransaction() + 1);
}

void Account::init(char _name[], char _number[], char _phoneNumber[])
{
    setName(_name);
    setNumber(_number);
    setPhoneNumber(_phoneNumber);
    setBalance(0);
    setNumberOfTransaction(0);
    setActive(true);
}
