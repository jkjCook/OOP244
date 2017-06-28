#include <iostream>



#include "SuperHero.h"


SuperHero::SuperHero() : Hero()
{
   this->m_superPowerAttack = 0;
   this->m_health = 0;
   this->m_superPowerDefend = 0;
}
        
        
SuperHero::SuperHero( const char* name, unsigned maximumHealth, unsigned attack,
                unsigned superPowerAttack, unsigned superPowerDefend
        )  : Hero(name, maximumHealth, attack)
{ 
   this->m_superPowerAttack = superPowerAttack;
   this->m_superPowerDefend = superPowerDefend;
}



  
        
unsigned SuperHero::getAttack() const 
{ 
   return this->m_superPowerAttack;
}
