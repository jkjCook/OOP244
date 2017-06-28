#include "Account.h"

using namespace std;

namespace ict{ 
	
	// constructor   
   Account::Account(double balance) {
      if (balance >= 0)
         this->balance = balance;
      else
         this->balance = 1.0;
   }

	// credit (add) an amount to the account balance
   void Account::credit(double balance) {
      this->balance += balance;
   }
	
	// debit (subtract) an amount from the account balance return bool 
   bool Account::debit(double balance) {
      double flag = this->balance;
      if(this->balance >= balance)
         this->balance -= balance;
      return flag != this->balance;
   }

	double Account::getBalance() const
	{
		return double(balance);
	} 

	void Account::setBalance( double newBalance )
	{
		balance = newBalance;
	} 
}