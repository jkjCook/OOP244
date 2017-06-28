#ifndef ICT_SAVINGSACCOUNT_H__
#define ICT_SAVINGSACCOUNT_H__

#include "Account.h"

using namespace std;

namespace ict{
	class SavingsAccount : public Account{
		private:
    		double interestRate; // interest rate (percentage)
		public:

			// TODO: put prototypes here
         SavingsAccount(double balance, double irate);
         double calculateInterest()const;
         virtual ostream& display(ostream& a);

   };
};
#endif
