#ifndef ICT_CHECKINGACCOUNT_H__
#define ICT_CHECKINGACCOUNT_H__

#include "Account.h"

using namespace std;

namespace ict {
   class CheckingAccount : public Account {
   private:
      double transactionFee;

      // TODO: chargeFee subtract transaction fee form the balance
      void chargeFee();
   public:

      // TODO: constructor initializes balance and transaction fee
      CheckingAccount(double balance, double transactionFee);
      // TODO: Write a function prototype to override credit function
      virtual void credit(double balance);
      // TODO: Write a function prototype to override debit function
      virtual bool debit(double balance);
      // TODO: Write a function prototype to  override display function
      virtual ostream& display(ostream& a);
   };
};
#endif
