//Justin Cook
#ifndef FIGHT_H
#define FIGHT_H
 

namespace sict {
   const Hero & operator* (const Hero & a, const Hero & b);
   void apply_damage(Hero& A, Hero& B);
}

#endif
