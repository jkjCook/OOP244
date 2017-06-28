#include "CheckingAccount.h"
#include <iomanip>
using namespace std;

namespace ict {

   // TODO: define CheckingAccount class member functions here  
   CheckingAccount::CheckingAccount(double balance, double transactionFee): Account(balance){
      if (transactionFee > 0)
         this->transactionFee = transactionFee;
   }
   void CheckingAccount::chargeFee() {
      this->setBalance(this->getBalance() - this->transactionFee);
   }
 
   bool CheckingAccount::debit(double balance) {
      this->chargeFee();
      return this->Account::debit(balance);
   }
   void CheckingAccount::credit(double balance) {
      this->chargeFee();
      this->Account::credit(balance);
   }
   ostream& CheckingAccount::display(ostream& a) {
      a << "Account type: Checking" << endl;
      a << "Balance: $ " << std::setprecision(2) << std::fixed << this->getBalance() << endl;
      a << "Transaction Fee: " << std::setprecision(2) << std::fixed << this->transactionFee << endl;
      return a;
   }
}