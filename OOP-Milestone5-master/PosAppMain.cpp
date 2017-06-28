#include <iostream>
#include "PosApp.h"
using namespace std;
int main(){
  ict::PosApp app("posapp.txt", "bill.txt");
  app.run();
  return 0;
}