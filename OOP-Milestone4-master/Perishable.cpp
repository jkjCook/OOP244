#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include "Perishable.h"

namespace ict {
   char Perishable::signature()const {
      return 'P';
   }
   Perishable::Perishable() {
      m_expiry.dateOnly(true);
   }
   std::fstream& Perishable::save(std::fstream& file)const {
      NonPerishable::save(file) << "," << m_expiry;
      return file;
   }
   std::fstream& Perishable::load(std::fstream& file) {
      NonPerishable::load(file);
      file >> m_expiry;
      return file;
   }
   std::ostream& Perishable::write(std::ostream& os, bool linear)const {
      NonPerishable::write(os, linear);
      if (this->ok() && linear == false)
         os << "Expiry date: " << m_expiry << std::endl;
      return os;
   }
   std::istream& Perishable::read(std::istream& is) {
      std::cout << "Perishable ";
      NonPerishable::read(is);
      if (this->ok()) {
         std::cout << "Expiry date (YYYY/MM/DD): ";
         is >> m_expiry;
         if (is.fail()) {
            if (m_expiry.errCode() == YEAR_ERROR) {
               this->error("Invalid Year in Date Entry");
               is.setstate(std::ios::failbit);
            }
            else if (m_expiry.errCode() == MON_ERROR) {
               this->error("Invalid Month in Date Entry");
               is.setstate(std::ios::failbit);
            }
            else if (m_expiry.errCode() == DAY_ERROR) {
               this->error("Invalid Day in Date Entry");
               is.setstate(std::ios::failbit);
            }
            else {
               this->error("Invalid Date Entry");
            }
         }
         //is.ignore();
      }
      return is;
  }

}
