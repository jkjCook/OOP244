#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
using namespace std;
#include "Date.h"
#include "POS.h"


namespace ict{
  void Date::set(){
    time_t t = time(NULL);
    tm lt = *localtime(&t);
    m_day = lt.tm_mday;
    m_mon = lt.tm_mon + 1;
    m_year = lt.tm_year + 1900;
    if (dateOnly()){
      m_hour = m_min = 0;
    }
    else{
      m_hour = lt.tm_hour;
      m_min = lt.tm_min;
    }
  }

  int Date::value()const{
    return m_year * 535680 + m_mon * 44640 + m_day * 1440 + m_hour * 60 + m_min;
  }

  int Date::mdays()const{
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
    mon--;
    return days[mon] + int((mon == 1)*((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
  }
  void Date::errCode(int errorCode) {
     if (errorCode == NO_ERROR && errorCode == CIN_FAILED && errorCode == YEAR_ERROR && errorCode == MON_ERROR &&
        errorCode == DAY_ERROR && errorCode == HOUR_ERROR && errorCode == MIN_ERROR) {
        this->m_readErrorCode = errorCode;
     }
  }
  void Date::set(int year, int mon, int day, int hour, int min) {
     this->m_year = year;
     this->m_mon = mon;
     this->m_day = day;
     this->m_hour = hour;
     this->m_min = min;
     this->m_readErrorCode = NO_ERROR;
  }
  Date::Date() {
     this->m_dateOnly = false;
     this->set();
  }
  Date::Date(int year, int mon, int day) {
     set(year, mon, day, 0, 0);
     this->m_readErrorCode = NO_ERROR;
     this->m_dateOnly = true;
  }
  Date::Date(int year, int mon, int day, int hour, int min) {
     this->set(year, mon, day, hour, min);
     this->m_dateOnly = false;
     this->m_readErrorCode = NO_ERROR;
  }
  int Date::errCode()const {
     return this->m_readErrorCode;
  }
  bool Date::bad()const {
     return this->m_readErrorCode != NO_ERROR;
  }
  bool Date::dateOnly()const {
     return this->m_dateOnly;
  }
  void Date::dateOnly(bool value) {
     (value == true) ? this->m_hour = 0, this->m_min = 0, this->m_dateOnly = value : this->m_dateOnly = value;
  }
  bool Date::operator==(const Date& D)const {
     return this->value() == D.value();
  }
  bool Date::operator!=(const Date& D)const {
     return this->value() != D.value();
  }
  bool Date::operator<(const Date& D)const {
     return this->value() < D.value();
  }
  bool Date::operator>(const Date& D)const {
     return this->value() > D.value();
  }
  bool Date::operator<=(const Date& D)const {
     return this->value() <= D.value();
  }
  bool Date::operator>=(const Date& D)const {
     return this->value() >= D.value();
  }
  std::istream& Date::read(std::istream& is){
     is >> this->m_year;
     if (is.fail() || is.get() != '/') {
           this->m_readErrorCode = CIN_FAILED;
     }
     if (this->m_year < MIN_YEAR || this->m_year > MAX_YEAR)
        this->m_readErrorCode = YEAR_ERROR;
     
        is >> this->m_mon;
        if (is.fail() || is.get() != '/') {
           if (this->m_readErrorCode == 0)
              this->m_readErrorCode = CIN_FAILED;
        }
        else if (this->m_mon < 1 || this->m_mon > 12)
           this->m_readErrorCode = MON_ERROR;

        is >> this->m_day;
        if (this->m_day < 1 || this->m_day > this->mdays()) {
           if (this->m_readErrorCode <= 0)
              this->m_readErrorCode = DAY_ERROR;
        }
        if (is.fail()) {
           if (this->m_readErrorCode <= 0)
              this->m_readErrorCode = CIN_FAILED;
        }

     if (this->m_dateOnly == false) {
        if (is.get() != ',')
           this->m_readErrorCode = CIN_FAILED;
           is >> this->m_hour;
           if (this->m_hour < 1 || this->m_hour > 24) {
                 this->m_readErrorCode = HOUR_ERROR;
           }
           if (is.fail() || is.get() != ':') {
              if (this->m_readErrorCode == 0)
                 this->m_readErrorCode = CIN_FAILED;
           }
           
           is >> this->m_min;
           if (this->m_min < 1 || this->m_min > 59) {
                 this->m_readErrorCode = MIN_ERROR;
           }
           if (is.fail()) {
              if (this->m_readErrorCode == 0)
                 this->m_readErrorCode = CIN_FAILED;
           }
     }
     if (is.fail())
        this->m_readErrorCode = CIN_FAILED;
     return is;

  }
  std::ostream& Date::write(std::ostream& ostr)const {
     if(this->m_dateOnly)
        ostr << this->m_year << "/" << ((this->m_mon < 10) ? "0" : "") << this->m_mon << "/" << ((this->m_day < 10) ? "0" : "") << this->m_day;
     else
        ostr << this->m_year << "/" << ((this->m_mon < 10) ? "0" :"") << this->m_mon << "/" << ((this->m_day < 10) ? "0" : "") <<this->m_day 
        << ", " << ((this->m_hour < 10) ? "0" : "") << this->m_hour << ":" << ((this->m_min < 10) ? "0" : "") << this->m_min;
     return ostr;
  }
  std::ostream& operator<<(std::ostream& ostr, const Date& A) {
     A.write(ostr);
     return ostr;
  }
  std::istream& operator>>(std::istream& istr, Date& A) {
     A.read(istr);
     return istr;
  }


  

}
