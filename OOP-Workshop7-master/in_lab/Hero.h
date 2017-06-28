//Justin Cook
#ifndef HERO_H
#define HERO_H

#include <iostream>
namespace sict {
   class Hero
   {
      char m_name[41];
      unsigned m_attack;
      unsigned m_maximumHealth;
      int m_health;

      bool isEmpty() const;
   public:
      // constructors
      Hero();
      Hero(const char name[], unsigned maximumHealth, unsigned attack);

      // member functions
      void respawn();
      bool isAlive() const { return m_health > 0; }
      unsigned getAttack() const { return m_attack; }

      // display function
      void display(std::ostream &) const;

      // friend global helper function to assign damage to 2 heroes at the same time.
      friend void apply_damage(Hero& A, Hero& B);
   };
}



#endif
