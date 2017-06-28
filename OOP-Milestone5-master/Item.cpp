#define _CRT_SECURE_NO_WARNINGS  
//Justin Cook
// Lib includes
#include <iostream>
#include <cstring>
// inlcude Item and POS header files
#include "Item.h"
#include "POS.h"

using namespace std;
namespace ict{
  // class Item implementaion
   Item::Item() {
      m_sku[0] = '\0';
      m_name = nullptr;
      m_price = 0.0;
      m_quantity = 0;
   }
   Item::Item(const char* sku, const char* name, double price, bool tax) {
      this->sku(sku);
      this->name(name);
      this->price(price);
      this->taxed(tax);
      this->quantity(0);
   }
   Item::~Item() {
      if (this->isEmpty() == true) {
         delete[] this->m_name;
         this->m_name = nullptr;
      }
   }
   void Item::sku(const char* sku) {
      std::strncpy(this->m_sku, sku, MAX_SKU_LEN);
   }
   void Item::name(const char* name) {
      this->m_name = new char[std::strlen(name) + 1];
      std::strncpy(this->m_name, name, (std::strlen(name) + 1));
   }
   void Item::price(double price) {
      this->m_price = price;
   }
   void Item::taxed(bool tax) {
      this->m_taxed = tax;
   }
   void Item::quantity(int quantity) {
      this->m_quantity = quantity;
   }
   bool Item::isEmpty()const {
      return this->m_name == nullptr;
   }
   double Item::cost()const {
      return (this->m_taxed == true) ? ((this->m_price * TAX) + this->m_price) : (this->m_price);
   }
   bool Item::operator==(const char* sku) {
      return (std::strcmp(sku, this->sku()) == 0) ? true : false;
   }
   int Item::operator+=(int add) {
      this->m_quantity += add;
      return this->m_quantity;
   }
   int Item::operator-=(int sub) {
      this->m_quantity -= sub;
      return this->m_quantity;
   }
   Item& Item::operator=(Item& B) {
      this->m_name = new char[std::strlen(B.m_name) + 1];
      if (this->isEmpty() == false) {
         std::strncpy(this->m_sku, B.m_sku, MAX_SKU_LEN);
         std::strncpy(this->m_name, B.m_name, (strlen(B.m_name)));
         this->price(B.m_price);
         this->taxed(B.m_taxed);
         this->quantity(B.m_quantity);
      }
      return B;
   }
   double operator+=(double& d, const Item& I) {
      if (I.taxed() == true) {
         d += (I.quantity() * I.price()) * 1.13;
      }
      else {
         d += I.quantity() * I.price();
      }
      return d;
   }
   ostream& operator<<(ostream& A, const Item& B) {
      B.write(A, true);
      return A;
   }
   istream& operator>>(istream& A, Item& B) {
      B.read(A);
      return A;
   }




}