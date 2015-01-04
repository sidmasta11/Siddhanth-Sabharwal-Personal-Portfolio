#include "Assignment3.h"
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
         delete ItemList[i];
         ItemList[i] = NULL;
      }
   }
}


void InventorySystem::BuildInventory(){

   ifstream inv("Assignment3Inventory.txt");                                //reads text file containing eProduct records, contains 16 inventory items

   string tproducttype = "";
   string tname = "";
   int tquantity = 0;
   int tid = 0;
   double tprice = 0.00;
   Condition tstate = NEW;
   time_t texpirationtime = 0;


   string buffer;

   if (!inv){
      cout << "There was an error opening the file.";
      exit(-1);
   }

   ItemCount = 0;

   while (getline(inv, buffer, ';')){

      tproducttype = buffer;

      getline(inv, buffer, ';');
      tname = buffer.c_str();

      getline(inv, buffer, ';');
      tquantity = atoi(buffer.c_str());

      getline(inv, buffer, ';');
      tprice = atof(buffer.c_str());

      if (tproducttype == "EP"){                     //test for product type
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
         ItemList[ItemCount] = new eProduct(tproducttype,tname, tquantity, tid, tprice, tstate);          //dynamic allocation to eProduct objects stored in ItemList array
         ++ItemCount;
      }

      else{
         getline(inv, buffer, '\n');
         texpirationtime = atoi(buffer.c_str());

         ItemList[ItemCount] = new DairyProduct(tproducttype, tname, tquantity, tid, tprice, texpirationtime);
         ++ItemCount;         
      }

   }
   inv.close();


}

void InventorySystem::ShowInventory() const{

   cout << endl << "Inventory System Report: " << endl;

   for (int i = 0; i < ItemCount; i++){
      ItemList[i]->DisplayItem();
      }
   }

void InventorySystem::ReportExpiredItems() const{
   int i = 0;

   cout << endl << "Expired Items: " << endl;
   while (ItemList[i] != NULL){
      DairyProduct* dp = dynamic_cast<DairyProduct*>(ItemList[i]);

      if (dp != NULL){
         if (!(dp->IsNew())){
            dp->DisplayItem();
         }
      }
      i++;
   }
   cout << endl;
}
void InventorySystem::ReportDefectiveItems() const {
   int i = 0;

   cout << endl << "Defective Inventory: " << endl;
   while (ItemList[i] != NULL){
      eProduct* ep = dynamic_cast<eProduct*>(ItemList[i]);                      //downcasting
      
      if (ep != NULL){
         if (ep->DefectiveTest()){
            ep->DisplayItem();
         }
      }
      i++;
   }
}



Item* InventorySystem::SearchItem() const {                  //
   int IDS;
   cout << "Enter Product ID: ";                //user inputs product ID
   cin >> IDS;
   int i = 0;
   bool d = false;
   
   while (i < ItemCount){
   
      if (dynamic_cast<eProduct *>(ItemList[i]) != NULL){
         eProduct* p = dynamic_cast<eProduct *>(ItemList[i]);
         if ((p->GetID()) == IDS){                                      //ItemList is searched
            p->DisplayItem();                    //Product information is displayed if product id is found
            d = true;
            Item *op = static_cast<Item *>(p);
            return op;
         }
      }
      
      else if (dynamic_cast<DairyProduct*>(ItemList[i]) != NULL){
         DairyProduct* q = dynamic_cast<DairyProduct*>(ItemList[i]);
         if((q->GetID()) == IDS){
            q->DisplayItem();
            d = true;
            Item *op = static_cast<Item *>(q);
            return op;
         }
      }
      i++;
   }
   if (d == false)
      cout << "There is no item with such a Product ID." << endl;                  //Error message
}

Item::Item(){ cout << "Item constructor" << endl; }

Item::~Item(){ cout << "Item destructor" << endl; }

bool Item:: IsNew() const{
   return false;
}

Item* Item::Clone() const{
   return NULL;
}

bool Item::MoreValuable(const Item &ip) const{
   return false;
}

void Item::DisplayItem() const{
   cout << "";
}

InventoryItem::InventoryItem() : ProductType(""), Name(""), Quantity(0){}                            //default constructor

InventoryItem::InventoryItem(string producttype, string name, int quantity) : ProductType(producttype), Name(name), Quantity(quantity){}                 //nondefault constructor

InventoryItem::~InventoryItem(){
   cout << "InventoryItem object [" << ProductType << "," << Name << "," << Quantity << "] is destroyed." << endl;          //destructor
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
   Item::DisplayItem();
   cout << ProductType << ";" << Name << ";" << Quantity;
}

Product::Product() :InventoryItem(), ProductID(0), Price(0.0){}                                //default constructor

Product::Product(string producttype, string name, int quantity, int id, double price) : InventoryItem(producttype, name, quantity), ProductID(generateProductID()), Price(price){}          //nondefault constructor that randomly generates product ID

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

bool Product::MoreValuable(const Item& ip) const{
   if ((this->Price) > ((dynamic_cast<Product&>((const_cast<Item&>(ip)))).Price)){
     return true;
   }
   else return false;
}

eProduct::eProduct() : Product(), condition(NEW){};                            //default constructor
eProduct::eProduct(string producttype,string name, int quantity, int id, double price, Condition state) : Product(producttype, name, quantity, id, price), condition(state){};            //nondefault constructor

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

void eProduct::DisplayItem() const{                         //invokes DisplayItem from base class then displays its own data
   Product::DisplayItem();

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

bool eProduct::IsNew() const{
   if ((this->condition) == NEW)
      return true;
   else return false;
}

eProduct* eProduct::Clone() const{
   return new eProduct(*this);
}

ostream& operator<<(ostream& os, const eProduct& ep){
   os << ep.ProductType << ";" << ep.Name << ";" << ep.Quantity << ";" << ep.ProductID << ";" << ep.Price << ";" << ep.condition << endl;
   return os;
}

bool eProduct::operator==(const eProduct& other2) const{
   return(this->ProductType == other2.ProductType &&
      this->Name == other2.Name &&
      this->Quantity == other2.Quantity &&
      this->Price == other2.Price &&
      this->condition == other2.condition);
}

DairyProduct::DairyProduct() : Product(), ExpirationTime(0){};                            //default constructor
DairyProduct::DairyProduct(string producttype, string name, int quantity, int id, double price, time_t expirationtime) : Product(producttype, name, quantity, id, price), ExpirationTime(expirationtime){};            //nondefault constructor

DairyProduct::~DairyProduct(){                                                           //destructor
   cout << "DiaryProduct object [" << ExpirationTime << "] is destroyed." << endl;              //destructor output
}

time_t DairyProduct::GetExpirationTime() const{
   return this->ExpirationTime;
}

void DairyProduct::SetExpirationTime(){
   time_t tempExpirationTime;
   cout << "Enter new expiration time of product: \n";
   cin >> tempExpirationTime;
   this->ExpirationTime = tempExpirationTime;
}

void DairyProduct::DisplayItem() const{
   Product::DisplayItem();
   cout << ";" << ExpirationTime << endl;
}

bool DairyProduct::IsNew() const{
   time_t now = time(NULL);
   if (ExpirationTime + 172800 >= now){
      return true;
   }
   else return false;
}

DairyProduct* DairyProduct::Clone() const{
   return new DairyProduct(*this);
}




int  main()
{
   InventorySystem * fullp = NULL;
   fullp = new InventorySystem();
   fullp->BuildInventory();                                       //This will output Item Constructor 24 times
   fullp->ShowInventory();
   fullp->ReportDefectiveItems();
   fullp->ReportExpiredItems();
  
   cout << "Overloading operator Implementation: " << endl;                       //This will be deleted during actual implementation
   eProduct ep("EP", "Test", 5, 365, 20.56, NEW);
   cout << ep << endl;

   
   eProduct p1("EP", "Samsung", 200, 1001, 2000.12, REFURBISHED);
   eProduct p2("EP", "Samsung", 200, 1001, 2000.12, REFURBISHED);
   
   if (p1 == p2){
      cout << "eProducts are the same" << endl << endl;
   }
   else {cout << "eProducts are not the same" << endl << endl;}
   cout << "End of operator overloading test." << endl << endl;
   
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