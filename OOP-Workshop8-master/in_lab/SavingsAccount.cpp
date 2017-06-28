#include "SavingsAccount.h"
#include <iomanip>
using namespace std;

namespace ict{ 
	
	// TODO: Implement SavingsAccount member functions here
   SavingsAccount::SavingsAccount(double balance, double irate) : Account(balance) {
      if (irate >= 0)
         this->interestRate = irate;
      else
         this->interestRate = 0;
   }
   double SavingsAccount::calculateInterest()const {
      return (this->getBalance() * this->interestRate) * 1.00;
      
   }
   ostream& SavingsAccount::display(ostream& a) {
      a << "Account type: Saving" << endl;
      a << "Balance: $ " << std::setprecision(2) << std::fixed << this->getBalance() << endl;
      a << "Interest Rate (%): " << std::setprecision(2) << std::fixed << (this->interestRate * 100)  << endl;
      return a;
   }
}