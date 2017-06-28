//Justin Cook
#ifndef ICT_ITEM_H__
#define ICT_ITEM_H__
// inlcude PosIO and POS header files
#include "POS.h"
#include "PosIO.h"

namespace ict{
  // class Item
   class Item :public PosIO {
      char m_sku[MAX_SKU_LEN + 1];
      char* m_name;
      double m_price;
      bool m_taxed;
      int m_quantity;
   public:
      Item();
      Item(const char* sku, const char* name, double price, bool tax = true);
      virtual ~Item();
      void sku(const char* sku);
      void name(const char* name);
      void price(double price);
      void taxed(bool tax);
      void quantity(int quantity);

      const char* sku()const { return this->m_sku; }
      char* name()const { return this->m_name; }
      double price()const { return this->m_price; }
      bool taxed()const { return this->m_taxed; }
      int quantity()const { return this->m_quantity; }
      double cost()const;
      bool isEmpty()const;

      bool operator==(const char* sku); // if the sku is eaqual to given sku
      int operator+=(int add); // add to quantity
      int operator-=(int sub); // subtract from quantity
      Item& operator=(Item& B);
   };
  // end class Item
  // operator += 
  double operator+=(double& d, const Item& I);
  // operator << and operator >>
  std::ostream& operator<<(std::ostream& A, const Item& B);
  std::istream& operator>>(std::istream& A, Item& B);
}


#endif