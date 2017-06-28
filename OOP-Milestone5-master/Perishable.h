#ifndef ICT_PERISHABLE_H__
#define ICT_PERISHABLE_H__
#include "NonPerishable.h"
#include "Date.h"

namespace ict {
   class Perishable : public NonPerishable {
      Date m_expiry;
   protected:
      virtual char signature()const;
   public:
      Perishable();
      virtual std::fstream& save(std::fstream& file)const;
      virtual std::fstream& load(std::fstream& file);
      virtual std::ostream& write(std::ostream& os, bool linear)const;
      virtual std::istream& read(std::istream& is);
   };


}






#endif
