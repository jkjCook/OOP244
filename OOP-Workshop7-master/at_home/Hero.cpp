//Justin Cook
#include <cstring>
#include <iostream>
#include "Hero.h"

using namespace std;


   //////////////////////////////////////////////
   // Default constructor
   //
   Hero::Hero()
   {
      m_health = 0;
      m_maximumHealth = 0;
      m_attack = 0;
   }


   ///////////////////////////////////////////////////
   // Constructor
   // 
   Hero::Hero(const char name[], unsigned maximumHealth, unsigned attack)
   {
      int counter = 0;
      for (int i = 0; i < 1; i++) {
         this->m_name[counter] = name[counter];
         if (name[counter] != '\0')
            i--;
         counter++;
      }
      this->m_health = maximumHealth;
      this->m_attack = attack;
   }



   /////////////////////////////////////////////////////////
   // 
   // Hero::display function
   void Hero::display(ostream & out) const
   {
      if (strcmp(this->m_name, "") != 0)
         out << this->m_name;
   }



   /////////////////////////////////////////////////
   // Hero::isEmpty ()
   // return true if the Hero object is uninitialized
   //
   bool Hero::isEmpty() const
   {
      return this->m_maximumHealth == 0 && this->m_attack == 0 && this->m_health == 0;
   }

   /////////////////////////////////////////////////
   // sets the Hero object's health back to full
   //
   void Hero::respawn()
   {
      this->m_health = this->m_maximumHealth;
   }

