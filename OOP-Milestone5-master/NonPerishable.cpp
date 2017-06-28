#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "NonPerishable.h"
using namespace std;

namespace ict {
   bool NonPerishable::ok()const {
      return this->m_err.isClear();
   }
   void NonPerishable::error(const char* message) {
      this->m_err.message(message);
   }
   char NonPerishable::signature()const {
      return 'N';
   }
   std::fstream& NonPerishable::save(std::fstream& file)const {
      file << this->signature() << "," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity();
      return file;
   }
   std::fstream& NonPerishable::load(std::fstream& file) {
      char skuC[MAX_SKU_LEN + 1];
      double priceC;
      int taxedC;
      int quantityC;
      char nameC[100];

         file.getline(skuC, 100, ',');
         sku(skuC);
         file.getline(nameC, 100, ',');
         name(nameC);
         file >> priceC;
         file.ignore();
         price(priceC);
         file >> taxedC;
         if (taxedC == 1)
            taxed(true);
         if (taxedC == 0)
            taxed(false);
         file.ignore();
         file >> quantityC;
         quantity(quantityC);
      return file;
   }
   std::ostream& NonPerishable::write(std::ostream& os, bool linear)const {
      if (!this->ok()) {
         os << (const char*)m_err;
      }
      else if (this->ok() && linear == true) {
         os << " "<< left << setw(MAX_SKU_LEN) << sku() << "|";
         os << left << setw(20) << name() << "|";
         os << right << setw(7) << fixed << setprecision(2) << price() << "|";
         os << right << setw(2)  << ((taxed() == true) ? "T" : " " )<< signature() << "|";
         os << right << setw(4) << quantity() << "|";
         os << right << setw(9) << (cost() * quantity()) << "|";
      }
      else if (this->ok() && linear == false) {
         os << "Name:" << endl << name() << endl;
         os << "Sku: " << sku() << endl;
         os << "Price: " << price() << endl;
         if (taxed() == true) {
            os << "Price after tax: " << cost() << endl;
         }
         else {
            os << "Price after tax: " << "N/A" << endl;
         }
            os << "Quantity: " << quantity() << endl;
            os << "Total Cost: " << (cost() * quantity()) << endl;
      }
         return os;
   }
   std::istream& NonPerishable::read(std::istream& is) {
      char skuC[MAX_SKU_LEN + 1];
      double priceC;
      char taxedC;
      int quantityC;
      char nameC[100];
      bool flag = false;

      this->m_err.clear();

      if (!is.fail()) {
         cout << "Item Entry:" << endl;
         cout << "Sku: ";
         is >> skuC;
         cout << "Name:" << endl;
         is >> nameC;
         cout << "Price: ";
         is >> priceC;
         if (is.fail()) {
            this->error("Invalid Price Entry");
            flag = true;
         }
         if (flag == false) {
            cout << "Taxed: ";
            is >> taxedC;
            if (taxedC != 'y' && taxedC != 'n') {
               is.setstate(ios::failbit);
               this->error("Invalid Taxed Entry, (y)es or (n)o"); 
               flag = true;
            }
         }
         if (flag == false) {
            cout << "Quantity: ";
            is >> quantityC;
            if (is.fail()) {
               this->error("Invalid Quantity Entry");
            }
            if (taxedC == 'y')
               taxed(true);
            else if (taxedC == 'n')
               taxed(false);
            sku(skuC);
            name(nameC);
            price(priceC);
            quantity(quantityC); 
         }
      }
      return is;
   }
}

