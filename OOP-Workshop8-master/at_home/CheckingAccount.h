#ifndef ICT_CHECKINGACCOUNT_H__
#define ICT_CHECKINGACCOUNT_H__

#include "Account.h"

using namespace std;

namespace ict{
	class CheckingAccount : public Account {
		private:
			double transactionFee;

			// TODO: chargeFee subtract transaction fee form the balance

		public:

			// TODO: constructor initializes balance and transaction fee

			// TODO: Write a function prototype to override credit function

			// TODO: Write a function prototype to override debit function

			// TODO: Write a function prototype to  override display function

	};
};
#endif
