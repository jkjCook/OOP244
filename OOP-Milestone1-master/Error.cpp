#define _CRT_SECURE_NO_WARNINGS 

#include "Error.h"
#include <iostream>
#include <string.h>
using namespace std;

namespace ict{
   Error::Error() {
      this->m_message = nullptr;
   }
   Error::Error(const char* errorMessage) {
      this->m_message = nullptr;
      this->message(errorMessage);
   }
   Error::~Error() {
      delete[] m_message;
   }
   void Error::clear() {
      delete[] this->m_message;
      this->m_message = nullptr;
   }
   bool Error::isClear()const {
      return this->m_message == nullptr;
   }
   Error::operator const char*() const {
      return this->m_message;
   }
   Error::operator bool()const {
      return this->isClear();
   }
   void Error::operator=(const char* errorMessage) {
      this->message(errorMessage);
   }
   void Error::message(const char* value) {
      delete[] this->m_message;
      this->m_message = new char[strlen(value) + 1];
      this->m_message[strlen(value)] = '\0';
      strcpy(this->m_message, value);
   }
   std::ostream& operator<<(std::ostream& ostr, Error& A){
      if (!A.isClear()) {
         ostr << (const char*)A;
      }
      return ostr;
   }
}