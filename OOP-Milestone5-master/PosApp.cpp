#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include "PosApp.h"

using namespace std;
namespace ict {
   PosApp::PosApp(const char* filename, const char* billfname) {
      strncpy(m_filename, filename, 128);
      strncpy(m_billfname, billfname, 128);
      m_noOfItems = 0;
   }
   int PosApp::menu() {
      int input = -1;
      cout << "The Sene-Store\n"  
         <<"1- List items\n"
         << "2- Add Perishable item\n"
         << "3- Add Non-Perishable item\n"
         << "4- Update item quantity\n"
         << "5- Show Item\n"
         << "6- POS\n"
         << "0- exit program\n"
         << "> ";
      cin >> input;
      cout << endl;
      if (cin.fail()) {
         cin.clear();
         cin.ignore(2000, '\n');
         input = -1;
      }
      if (!(input < 7 && input > -1))
         input = -1;
      return input;
   }
   //Loops through and deletes the elements, then sets the number of items to 0
   void PosApp::deallocateItems() {
      if (m_noOfItems > 0) {
         for (int i = 0; i < m_noOfItems; i++)
            delete this->m_items[i];
      }
      m_noOfItems = 0;
   }
   //Gets the first single character and if it's P or N calls the load files for Perishable or NonPerishable
   void PosApp::loadRecs() {
      char c;

      deallocateItems();
      fstream file;
      file.open(m_filename, ios::in);
      if (file.fail()) {
         file.clear();
         file.close();
         file.open(m_filename, ios::out);
         file.close();
      }
      else {
         while (!file.eof()) {
            file.get(c);
            if (c == 'P') {
               file.ignore();
               m_items[m_noOfItems] = new Perishable;
               m_items[m_noOfItems]->load(file);
               m_noOfItems++;
            }
            if (c == 'N') {
               file.ignore();
               m_items[m_noOfItems] = new NonPerishable;
               m_items[m_noOfItems]->load(file);
               m_noOfItems++;
            }
         }
      }
      file.close();
     
   }
   //Loops through and stores the data from the array into the text file then loads the records again after it's successful
   void PosApp::saveRecs() {
      fstream file;
      file.open(m_filename, ios::out);
      for (int i = 0; i < m_noOfItems; i++) {
         if (m_items[i]->quantity() > 0)
            m_items[i]->save(file);
      }
      file.close();
      loadRecs();
   }
   //Takes a sku and loops through the array to find a match and returns the loop counter for the index
   int PosApp::searchItems(const char* sku)const {
      int a = -1;
      for (int i = 0; i < m_noOfItems; i++) {
         if (*(m_items[i]) == sku) {
            a = i;
            i = m_noOfItems;
         }
      }
      return a;
   }
   //Uses the sku to call searchItems and locate the correct Item, then adds onto the quantity with your input
   void PosApp::updateQty() {
      char input[MAX_SKU_LEN + 1];
      cout << "Please enter the SKU: ";
      cin >> input;
      int add;
      int index = searchItems(input);
      if (index != -1) {
         m_items[index]->write(cout, false);
         cout << endl;
         cout << "Please enter the number of purchased items: ";
         cin >> add;
         *(m_items[index]) += add;
         saveRecs();
         cout << "Updated!" << endl;
      }
      else {
         cout << "Not found!" << endl;
      }
      cout << endl;
   }
   //Allows you to enter in an item to the array with user input, based on the argument it decides if its P or N, then saves to the file
   void PosApp::addItem(bool isPerishable) {
      if (isPerishable == true) {
         m_items[m_noOfItems] = new Perishable;
         m_items[m_noOfItems]->read(cin);
         m_noOfItems++;
         if (cin.fail()) {
            cin.clear();
            cin.ignore(2000, '\n');
            cout << m_items[m_noOfItems] << endl;
            m_noOfItems--;
         }
         else {
            cout << "Item added." << endl;
         }
      }
      else if (isPerishable == false) {
         m_items[m_noOfItems] = new NonPerishable;
         m_items[m_noOfItems]->read(cin);
         m_noOfItems++;
         if (cin.fail()) {
            cin.clear();
            cin.ignore(2000, '\n');
            cout << m_items[m_noOfItems] << endl;
            m_noOfItems--;
         }
         else {
            cout << "Item added." << endl;
         }
      }
      cout << endl;
      saveRecs();
   }
   //Prints all the items in linear form to the screen
   void PosApp::listItems()const {
      double total = 0;
      cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total |" << endl;
      cout << "-----|--------|--------------------|-------|---|----|---------|" << endl;
      for (int i = 0; i < m_noOfItems; i++) {
         cout << std::setw(4) << std::right << i + 1 << " |";
         m_items[i]->write(cout, true);
         cout << endl;
 
         total += *(m_items[i]);
      }
      cout << "-----^--------^--------------------^-------^---^----^---------^" << endl;
      cout << "                               Total Asset: $  |"  << std::setw(14) << std::right << std::setprecision(2)<< total <<"|" << endl;
      cout << "-----------------------------------------------^--------------^" << endl << endl;
   }
   //Opens the file in write truncate mode to clear the file
   void PosApp::truncateBillFile() {
      fstream file;
      file.open(m_billfname, ios::out | ios::trunc);
      file.close();
   }
   //Prints the bill to the screen using the write function and then truncates the bill file so no data is saved 
   void PosApp::showBill() {
      double total = 0;
      fstream file;
      file.open(m_billfname, ios::in);
      char c;
      if (file.fail()) {
         file.clear();
         file.close();
         file.open(m_billfname, ios::out);
         file.close();
      }
      else {
         cout << "v--------------------------------------------------------v" << endl;
         cout << "| 2017/04/02, 12:42                                      |" << endl;
         cout << "| SKU    | Item Name          | Price |TX |Qty |   Total |" << endl;
         cout << "|--------|--------------------|-------|---|----|---------|" << endl;
         
         while (!file.eof()) {
            file.get(c);
            if (c == 'P') {
               file.ignore();
               Perishable P;
               P.load(file);
               cout << "|";
               P.write(cout, true);
               cout << endl;
               total += P;
            }
            if (c == 'N') {
               file.ignore();
               NonPerishable NP;
               cout << "|";
               NP.load(file);
               NP.write(cout, true);
               cout << endl;
               total += NP;
            }
         }
         cout << "^--------^--------------------^-------^---^----^---------^" << endl;
         cout << "|                               Total: $  |" << std::setw(14) << std::right << std::setprecision(2) << total << "|" << endl;;
         cout << "^-----------------------------------------^--------------^" << endl << endl;
      }

      file.close();
      truncateBillFile();
   }
   //Takes an item and subtracts one from it's quantity and then makes that one appear in the bill file
   void PosApp::addToBill(Item& I) {
      fstream file;
      file.open(m_billfname, ios::out | ios::app);
      int qty = I.quantity();
      I.quantity(1);
      I.save(file);
      I.quantity(qty - 1);
      saveRecs();
      file.close();
   }
   //Allows you to continuously call addToBill, and then automatically displays and truncates the bill at the end
   void PosApp::POS() {
      char input[MAX_SKU_LEN + 1];
      int index = 0;
       do{
         cout << "Sku: ";
         cin.get();
         cin.get(input, MAX_SKU_LEN + 1);
         index = searchItems(input);
         if (index < 0 && input[0] != '\0')
            cout << "Not found!" << endl;
         else if(index >= 0) {
            cout << "v------------------->" << endl;
            cout << "| " << m_items[index]->name() << endl;
            cout << "^------------------->" << endl;
            addToBill(*(m_items[index]));
         }
       } while (input[0] != '\0');
       cin.clear();
       showBill();
   }
   //Puts everything together using the menu function
   void PosApp::run() {
      loadRecs();
      char input[MAX_SKU_LEN + 1];
      int index = 0;
      bool flag = true;
      while (flag == true) {
         switch (menu()) {
         case 0: cout << "Goodbye!" << endl;
            flag = false;
            break;
         case 1: 
            listItems();
            break;
         case 2: 
            addItem(true);
            break;
         case 3: 
            addItem(false);
            break;
         case 4: updateQty();
            break;
         case 5:
            cout << "Please enter the SKU: ";
            cin >> input;
            cout << "v-----------------------------------v" << endl;
            index = searchItems(input);
            if (index == -1)
               cout << "Not Found!" << endl;
            else
               m_items[index]->write(cout, false);
            cout << "^-----------------------------------^" << endl << endl;
            break;
         case 6: POS();
            break;
         default: cout << " === Invalid Selection, try again === " << endl;
            break;
         }
      }
   }
}

/*
ouputs:
-------------------------------------
update:
Please enter the SKU: 1313
Name:
Paper Tissue
Sku: 1313
Price: 1.22
Price after tax: 1.38
Quantity: 194
Total Cost: 267.45

Please enter the number of purchased items: 12
Updated!

------------------------------
Please enter the SKU: 3434
Not found!

-------------------------------------
add item:
Perishable Item Entry:
Sku: 5656
Name:
Honey
Price: 12.99
Taxed: y
Quantity: 12
Expiry date (YYYY/MM/DD): 1200/10/12
Invalid Year in Date Entry

Perishable Item Entry:
Sku: 5656
Name:
Honey
Price: 12.99
Taxed: y
Quantity: 12
Expiry date (YYYY/MM/DD): 2017/5/15
Item added.

--------------------------------------------
list item:
 Row | SKU    | Item Name          | Price |TX |Qty |   Total |
-----|--------|--------------------|-------|---|----|---------|
   1 | 1234   |Milk                |   3.99|  P|   2|     7.98|
   2 | 3456   |Paper Cups          |   5.99| TN|  38|   257.21|
   3 | 4567   |Butter              |   4.56| TP|   9|    46.38|
   4 | 1212   |Salted Butter       |   5.99|  P| 111|   664.89|
   5 | 1313   |Paper Tissue        |   1.22| TN| 206|   283.99|
   6 | 5656   |Honey               |  12.99| TP|  12|   176.14|
-----^--------^--------------------^-------^---^----^---------^
                               Total Asset: $  |       1436.59|
-----------------------------------------------^--------------^


--------------------------------------
printbill:
v--------------------------------------------------------v
| 2017/04/02, 12:42                                      |
| SKU    | Item Name          | Price |TX |Qty |   Total |
|--------|--------------------|-------|---|----|---------|
| 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
| 1313   |Paper Tissue        |   1.22| TN|   1|     1.38|
| 5656   |Honey               |  12.99| TP|   1|    14.68|
^--------^--------------------^-------^---^----^---------^
|                               Total: $  |         22.05|
^-----------------------------------------^--------------^

-------------------------------------------------------
POS:
Sku: 1212
v------------------->
| Salted Butter
^------------------->
Sku: 1212
v------------------->
| Salted Butter
^------------------->
Sku: 1313
v------------------->
| Paper Tissue
^------------------->
Sku: 1234
v------------------->
| Milk
^------------------->
Sku: 7654
Not found!
Sku: 5656
v------------------->
| Honey
^------------------->
Sku:
v--------------------------------------------------------v
| 2017/04/02, 12:58                                      |
| SKU    | Item Name          | Price |TX |Qty |   Total |
|--------|--------------------|-------|---|----|---------|
| 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
| 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
| 1313   |Paper Tissue        |   1.22| TN|   1|     1.38|
| 1234   |Milk                |   3.99|  P|   1|     3.99|
| 5656   |Honey               |  12.99| TP|   1|    14.68|
^--------^--------------------^-------^---^----^---------^
|                               Total: $  |         32.03|
^-----------------------------------------^--------------^

------------------------------------------------------
run:
The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> 5

Please enter the SKU: 5656
v-----------------------------------v
Name:
Honey
Sku: 5656
Price: 12.99
Price after tax: 14.68
Quantity: 10
Total Cost: 146.79
Expiry date: 2017/05/15
^-----------------------------------^

The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> 5

Please enter the SKU: 12345
Not found!

The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> five

===Invalid Selection, try again===

The Sene-Store
1- List items
2- Add Perishable item
3- Add Non-Perishable item
4- Update item quantity
5- Show Item
6- POS
0- exit program
> 0

Goodbye!

*/