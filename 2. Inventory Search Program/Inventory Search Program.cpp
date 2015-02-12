#include "Assignment2.h"
using namespace std;

InventorySystem::InventorySystem() : StoreName(""), StoreID(0){                            //default constructor
   for (ItemCount = 0; ItemCount < 512; ItemCount++){
      ItemList[ItemCount] = NULL;
   }
}

InventorySystem::InventorySystem(string storename, int id) : StoreName(storename), StoreID(id){                 //Nondefault Constructor
   for (ItemCount = 0; ItemCount < 512; ItemCount++){
      ItemList[ItemCount] = NULL;
   }
}

InventorySystem::~InventorySystem(){                                         //Destructor
   for (int i = 0; i < ItemCount; i++){
      if (ItemList[i] != NULL){
         eProduct *ep = static_cast<eProduct*>(ItemList[i]);                    //downcasting
         delete ep;
         ep = NULL;
      }
   }
}



void InventorySystem::BuildInventory(){                                    

   ifstream inv("inventory.txt");                                //reads text file containing eProduct records, contains 16 inventory items

   string tname = "";
   int tquantity = 0;
   int tid = 0;
   double tprice = 0.00;
   Condition tstate = NEW;

   string buffer;

   if (!inv){
      cout << "There was an error opening the file.";
      exit(-1);
   }

   ItemCount = 0;

   while (getline(inv, buffer, ';')){

      tname = buffer;

      getline(inv, buffer, ';');
      tquantity = atoi(buffer.c_str());

      getline(inv, buffer, ';');
      tprice = atof(buffer.c_str());

      getline(inv, buffer, '\n');
      char cond = buffer[0];
      
      switch (cond){
      case 'N':
         tstate = NEW;
         break;
      case 'R':
         tstate = REFURBISHED;
         break;
      case 'U':
         tstate = USED;
         break;
      case 'D':
         tstate = DEFECTIVE;
         break;
      default:
         cout << "Check conditions in text file and make sure they are either N, R, U, or D" << endl;
         exit(-2);
         break;

      }
      ItemList[ItemCount] = new eProduct(tname, tquantity, tid,tprice, tstate);          //dynamic allocation to eProduct objects stored in ItemList array
      ++ItemCount;
   }

   inv.close();


}

void InventorySystem::ShowInventory() const{

   cout << "Inventory System Report: " << endl;

   for (int i = 0; i < ItemCount; i++){
      if (ItemList[i] != NULL){
         eProduct* ep = static_cast<eProduct*>(ItemList[i]);                    //downcasting
         ep->DisplayItem();
      }
   }
   cout << endl;
}

void InventorySystem:: ShowDefectiveInventory() const {
int i = 0;

cout << "Defective Inventory: " << endl;
while (ItemList[i] != NULL){
eProduct *ep = static_cast<eProduct*>(ItemList[i]);                      //downcasting

if (ep->DefectiveTest()){                                       //displays items that are defective
   ep->DisplayItem();
   
}

i++;
}
cout << endl;
}

void InventorySystem::SearchItem() const {                  //
   int IDS;
   cout << "Enter Product ID: ";                //user inputs product ID
   cin >> IDS;
   int i = 0;
   bool d = false;
   while(i < ItemCount){
      Product *p = static_cast<Product *>(ItemList[i]);                    //downcasting
      if ((p->GetID()) == IDS){                                      //ItemList is searched
         eProduct *ep = static_cast<eProduct*>(ItemList[i]);               //downcasting
         ep->DisplayItem();                                      //Product information is displayed if product id is found
         d = true;
      }
      i++;
      }
   if (d == false)
      cout << "There is no item with such a Product ID." << endl;                  //Error message
}

InventoryItem::InventoryItem() : Name(""), Quantity(0){}                            //default constructor

InventoryItem::InventoryItem(string name, int quantity) : Name(name), Quantity(quantity){}                 //nondefault constructor
 
InventoryItem::~InventoryItem(){
   cout << "InventoryItem object [" << Name << "," << Quantity << "] is destroyed." << endl;             //destructor output
}

void InventoryItem::SetName(){

   char tempname[50];
   cout << "Enter new name of product: \n";
   cin.getline(tempname, 50);
   this->Name = tempname;

}

string InventoryItem::GetName() const{
   return this->Name;
}

int InventoryItem::GetQuantity() const{
   return this->Quantity;
}

void InventoryItem::AddQuantity(){

   int q;
   cout << "How much quantity would you like to add: " << endl;
   cin >> q;
   this->Quantity = this->Quantity + q;
}

void InventoryItem::DisplayItem() const{
   cout << this->Name << ";" << this->Quantity;
}


Product::Product() :InventoryItem(), ProductID(0), Price(0.0){}                                //default constructor
Product::Product(string name, int quantity, int id, double price) : InventoryItem(name, quantity), ProductID(generateProductID()), Price(price){}          //nondefault constructor that randomly generates product ID

Product::~Product(){                                                                             //destructor
   cout << "Product object [" << ProductID << "," << Price << "] is destroyed." << endl;               //destructor output
}

void Product::SetID(){

   int tempID;
   cout << "Enter new product ID: \n";
   cin >> tempID;
   this->ProductID = tempID;
}

int Product::GetID() const {
   return this->ProductID;
}

void Product::SetPrice(){

   int tempPrice;
   cout << "Enter new price of product: \n";
   cin >> tempPrice;
   this->Price = tempPrice;
}

double Product::GetPrice() const{
   return this->Price;
}

void Product::DisplayItem() const {
   InventoryItem::DisplayItem();                                                   //Invokes DisplayItem from InventoryItem class then displays its own data
   cout << ";" << ProductID << ";" << fixed << setprecision(2) << Price;                         //Price is set to two digits after decimal point
}

int Product::generateProductID(){                                        //member function specific to this class

   srand(time(NULL) + rand());
   ProductID = rand() % 100000;

   return ProductID;
}


eProduct::eProduct() : Product(), condition(NEW){};                            //default constructor
eProduct::eProduct(string name, int quantity, int id, double price, Condition state) : Product(name, quantity, id, price), condition(state){};            //nondefault constructor

eProduct::~eProduct(){                                                           //destructor
   cout << "eProduct object [" << condition << "] is destroyed." << endl;              //destructor output
}

Condition eProduct::GetCondition() const{
   switch (this->condition){
   
   case '0':
      return NEW;
      break;
   case '1':
      return REFURBISHED;
      break;
   case '2':
      return USED;
      break;
   case '3':
      return DEFECTIVE;
      break;
   default:
      cout << "No condition exists for this item." << endl;
      exit(-1);
      break;
   }
}

void eProduct::SetCondition(){

   char state[5];

   cout << "Enter condition (N = NEW, R = REFURBISHED, U = USED, D = DEFECTIVE) for this product: ";
   cin.getline(state, 5);

   if (state == "N"){
      this->condition = NEW;
   }

   else if (state == "R"){
      this->condition = REFURBISHED;
   }

   else if (state == "U"){
      this->condition = USED;
   }

   else if (state == "D"){
      this->condition = DEFECTIVE;
   }
   else{
      cout << "Please enter a valid input, make sure it is uppercase, the options are N, R, U, and D.";
   }
}

void eProduct::DisplayItem() const{
   Product::DisplayItem();                           //invokes DisplayItem from base class then displays itws own data

   if (condition == 0)
      cout << ";N" << endl;
   if (condition == 1)
      cout << ";R" << endl;
   if (condition == 2)
      cout << ";U" << endl;
   if (condition == 3)
      cout << ";D" << endl;

}

bool eProduct::DefectiveTest() const{                        //member function specific to this class
   if ((this->condition) == DEFECTIVE)
      return true;
   else return false;
}



int main()
{
   InventorySystem * fullp = NULL;                          //pointer to InventorySystem object

   fullp = new InventorySystem();                         //Dynamic allocation to InventorySystem object
   fullp->BuildInventory();                             //BuildInventory is invoked
   fullp->ShowInventory();                                 //ShowInventory is invoked
   fullp->ShowDefectiveInventory();                        //ShowDefectiveInventory is invoked

   char searchorquit;

   do{                                                           //do-while loop that user can use to search an inventory item or quit the program
      cout << "Would you like to search for an item (S or s) or would you like to quit (Q or q) the program? ";
      cin >> searchorquit;
      cout << endl;

      switch (searchorquit){
      case 's':
      case 'S':
         fullp->SearchItem();
         cout << endl << endl;
         break;
      case 'q':
      case 'Q':
        break;
      default:
         cout << "Please enter a q/Q or s/S." << endl << endl;
         break;
      }
   } while (searchorquit != 'q' && searchorquit != 'Q');

   cout << "Thank You!" << endl << endl;

   delete fullp;                                      //de-allocation of InventorySystem object

   cout << endl << "Goodbye!" << endl;
   
   int n;                                           //variable is for testing
   cin >> n;                                         //this is just so I can copy my test code, would actually be deleted during implementation
   return 0;

}
