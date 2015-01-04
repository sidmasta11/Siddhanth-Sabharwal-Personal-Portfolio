/*
File name: Assignment4.cpp
Developer: Siddhanth Sabharwal
Program Purpose: This program reads a formatted text file containing product type, name, quantity, price, special data,
customer ID, order ID, and order Date.The product type can either be dairy product and eProduct. 
The special data for dairy products is the expiration date, and the special data for eProducts is the condition 
they are in.The inventory management system will show all inventory, show defective inventory, show expired items, 
and will allow the user to get information for specific product numbers, and customer IDs.
The inventory will be stored in an array of pointers meaning the records are to be stored in dynamic memory.
Text File Format: <Product Type>;Name;Quantity;Price;<Product Data>;CustomerID;OrderID;OrderDate
Example:
EP;Panasonic DVD Player;35;125.99;D;BestBuy;BB123;1414936800
DP;Dutch Cheese;234;4.95;141836800;Lucky;LK1234;1414831234
Program History:
Date                         Version                        ID                    Description
12/11/2014                   1.0                            1000                  Initial Creation
*/

#include "Assignment4.h"
using namespace std;

//Order Processing System constructors and destructor
OrderProcessingSystem::OrderProcessingSystem() :storeName(""), storeID(""), AddressPtr(NULL){}
OrderProcessingSystem::OrderProcessingSystem(string storename, string storeid, int streetnumber, string streetname, int zipcode, string state) : storeName(storename), storeID(storeid){
   AddressPtr = new Address(streetnumber, streetname, zipcode, state);
}

OrderProcessingSystem::~OrderProcessingSystem(){
   if (AddressPtr){
      delete AddressPtr;
   }

   map<string, deque<Order<Item*>>>::iterator mIter = customerOrderMap.begin();
   while (mIter != customerOrderMap.end()){
      deque<Order<Item*>>::iterator dIter = mIter->second.begin();

      while (dIter != mIter->second.end()){
         delete dIter->getItem();
         mIter->second.erase(dIter);
         dIter = mIter->second.begin();
      }
      ++mIter;
   }

   cout << "Order Processing System object [" << storeName << "," << storeID << "] is destroyed." << endl;
}

void OrderProcessingSystem::Init(){
   ifstream inv("Assignment4Inventory.txt");                                
   
   if (!inv){
      throw "File not open";
   }

   string tproducttype = "";
   string tname = "";
   int tquantity = 0;
   double tprice = 0.00;
   int tid = 0;   
   Condition tstate = NEW;
   time_t texpirationtime = 0;
   string tcustomerid = "";
   string torderid = "";
   long torderdate = 0;
   Item* tempitem = NULL;
   Order<Item*> temporder;

   string buffer;

   if (!inv){
      //cout << "There was an error opening the file.";
      //exit(-1);
   }

   

   while (getline(inv, buffer, ';')){

      tproducttype = buffer;

      getline(inv, buffer, ';');
      tname = buffer.c_str();

      getline(inv, buffer, ';');
      tquantity = atoi(buffer.c_str());

      getline(inv, buffer, ';');
      tprice = atof(buffer.c_str());

      if (tproducttype == "EP"){                     //test for product type
         getline(inv, buffer, ';');
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
         tempitem = new eProduct(tproducttype, tname, tquantity, tid, tprice, tstate);          //dynamic allocation to eProduct objects stored in ItemList array
      }

      else{
         getline(inv, buffer, ';');
         texpirationtime = atoi(buffer.c_str());

         tempitem = new DairyProduct(tproducttype, tname, tquantity, tid, tprice, texpirationtime);
      }
      
      getline(inv, buffer, ';');
      tcustomerid = buffer.c_str();

      getline(inv, buffer, ';');
      torderid = buffer.c_str();

      getline(inv, buffer, '\n');
      torderdate = atol(buffer.c_str());

      
      temporder.setItem(tempitem);
      temporder.setOrderID(torderid);
      temporder.setOrderDate(torderdate);

      customerOrderMap[tcustomerid].push_back(temporder);
   }
   
   inv.close();
}

void OrderProcessingSystem::Menu() const{
   cout << "MENU" << endl << "1. Show All Orders" << endl << "2. Find Order by Customer ID" << endl << "3. Process Order" << endl << "4. Quit" << endl;
}

void OrderProcessingSystem::Start(){
   
   int input;
   
   do{
      Menu();
      cin >> input;
      switch (input){
      case 1:
         ShowAllOrders();
         break;
      case 2:
         try{
            FindOrders();
         }
         catch (const char *error){
            cout << error << endl;
         }
         break;
      case 3:
         try{
            ProcessOrder();
         }
         catch (const char *error){
            cout << error << endl;
         }
         break;
      case 4:
         break;
      default:
         cout << "Please enter a number from 1 to 4." << endl << endl;
         break;
      }

   } while (input != 4);
}

void OrderProcessingSystem::ShowAllOrders() const{
   map<string, deque<Order<Item*>>>::const_iterator mIter = customerOrderMap.begin();
   
   while (mIter != customerOrderMap.end() ){
      
      deque<Order<Item*>>::const_iterator dIter = mIter->second.begin();
      cout << "Customer ID: " << mIter->first << endl;
      while (dIter != mIter->second.end()){
         eProduct *ep = dynamic_cast<eProduct*>(dIter->getItem());
         DairyProduct *dp = dynamic_cast<DairyProduct*>(dIter->getItem());

         cout << "Order ID: " << dIter->getOrderID() << endl;
         cout << "Order Date: " << dIter->getOrderDate() << endl;

         if (ep != NULL){
            cout << *ep;
         }
         else if (dp != NULL){
            cout << *dp;
         }
         cout << endl;
         ++dIter;
      }
      ++mIter;
   }
}

void OrderProcessingSystem::FindOrders() const{

   string input;
   bool found = false;
   map<string, deque<Order<Item*>>>::const_iterator mIter = customerOrderMap.begin();

   cout << "Enter Customer ID: ";
   cin >> input;

   mIter = customerOrderMap.find(input);

   if (mIter != customerOrderMap.end()){
      
         found = true;
         deque<Order<Item*>>::const_iterator dIter = mIter->second.begin();
         cout << "Customer ID: " << mIter->first << endl;
         while (dIter != mIter->second.end()){
            eProduct *ep = dynamic_cast<eProduct*>(dIter->getItem());
            DairyProduct *dp = dynamic_cast<DairyProduct*>(dIter->getItem());

            cout << "Order ID: " << dIter->getOrderID() << endl;
            cout << "Order Date: " << dIter->getOrderDate() << endl;

            if (ep != NULL){
               cout << *ep;
            }
            else if (dp != NULL){
               cout << *dp;
            }
            cout << endl;
            ++dIter;
         }
         
   }
   if (found = false){
      throw "No match.";
   }
}

void OrderProcessingSystem::ProcessOrder(){
   string customerID;
   string orderID;
   bool cfound = false;
   bool ofound = false;

   map<string, deque<Order<Item*>>>::iterator mIter = customerOrderMap.begin();
   cout << "Enter Customer ID: ";
   cin >> customerID;
   cout << "Enter Order ID: ";
   cin >> orderID;

   while (mIter != customerOrderMap.end()){
      if (mIter->first == customerID){
         cfound = true;
         deque<Order<Item*>>::iterator dIter = mIter->second.begin();

         while (dIter != mIter->second.end()){
            if (dIter->getOrderID() == orderID){
               ofound = true;
               cout << "Order ID has been deleted." << endl;
               delete dIter->getItem();
               mIter->second.erase(dIter);
               dIter = mIter->second.begin();               
            }
            else {
               ++dIter;
            }
         }
      }
      ++mIter;
   }
   
   if (!ofound && !cfound){
      throw "Order ID and customer ID are not found";
   }
   if (!cfound){
      throw "Customer ID not found";
   }
   if (!ofound){
      throw "Order ID not found";
   }
}

//Order Class constructors and destructor
template <class T>
Order<T>::Order():orderID(""),orderDate(0){}
template <class T>
Order<T>::Order(T t, string orderid, long orderdate) : item(t), orderID(orderid), orderDate(orderdate){}

template <class T>
Order<T>::~Order() { 
   cout << "Order object [" << this->getItem() << "," << orderID << "," << orderDate << "] is destroyed." << endl;
}

template<class T>
string Order<T>::getOrderID() const{
   return this->orderID;
}

template<class T>
void Order<T>::setOrderID(string tempOrderID) {
   this->orderID = tempOrderID;
}

template <class T>
T Order<T>::getItem() const {
   return this->item;
}

template <class T>
void Order<T>::setItem(const T &Tref) {
   this->item = Tref;
}

template <class T>
long Order<T>::getOrderDate() const{
   return this->orderDate;
}

template<class T>
void Order<T>::setOrderDate(long tempOrderDate){
   this->orderDate = tempOrderDate;
}

template<class T>
bool Order<T>::operator == (const Order&rhs)const{
   return(this->orderID == rhs.orderID && this->item == rhs.item);
}

Item::Item(){ cout << "Item constructor" << endl; }

Item::~Item(){ cout << "Item destructor" << endl; }

bool Item::IsNew() const{
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
   if ((this->Price) > ((dynamic_cast<const Product&>((ip))).Price)){
      return true;
   }
   else return false;
}

eProduct::eProduct() : Product(), condition(NEW){};                            //default constructor
eProduct::eProduct(string producttype, string name, int quantity, int id, double price, Condition state) : Product(producttype, name, quantity, id, price), condition(state){};            //nondefault constructor

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
   os << "Product Type: " << ep.ProductType << endl 
      << "Product Name: " << ep.Name << endl
      << "Product Quantity: " << ep.Quantity << endl
      << "Product ID: " << ep.ProductID << endl
      << "Price: " << ep.Price << endl
      << "Condition: " << ep.condition << endl;
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
   if (ExpirationTime >= now + 172800){
      return true;
   }
   else return false;
}

DairyProduct* DairyProduct::Clone() const{
   return new DairyProduct(*this);
}

ostream& operator<<(ostream& os, const DairyProduct& ep){
   os << "Product Type: " << ep.ProductType << endl
      << "Product Name: " << ep.Name << endl
      << "Product Quantity: " << ep.Quantity << endl
      << "Product ID: " << ep.ProductID << endl
      << "Price: " << ep.Price << endl
      << "Expiration Time: " << ep.ExpirationTime << endl;
   return os;
}

//Address constructors and destructors
Address::Address() : streetNumber(0), streetName(""), zipCode(0), State(""){};  
Address::Address(int streetnumber, string streetname, int zipcode, string state) : streetNumber(streetnumber), streetName(streetname), zipCode(zipcode), State(state){};

Address::~Address(){                                                                             
   cout << "Address object [" << streetNumber << "," << streetName << "," << zipCode << "," << State << "] is destroyed." << endl;    //destructor output
}

void Address::SetStreetNumber(){
   int tempStreetNumber = 0;
   cout << "Enter new Street Number: \n";
   cin >> tempStreetNumber;
   this->streetNumber = tempStreetNumber;
}

int Address::GetStreetNumber() const{
   return this->streetNumber;
}

void Address::SetStreetName(){
   string tempStreetName = "";
   cout << "Enter new Street Name: \n";
   cin >> tempStreetName;
   this->streetName = tempStreetName;
}

string Address::GetStreetName() const{
   return this->streetName;
}

void Address::SetZipCode(){
   int tempZipCode = 0;
   cout << "Enter new Zip Code: \n";
   cin >> tempZipCode;
   this->zipCode = tempZipCode;
}

int Address::GetZipCode() const{
   return this->zipCode;
}

void Address::GetState(){
   string tempState = "";
   cout << "Enter new State: \n";
   cin >> tempState;
   this->State = tempState;
}

string Address::GetState() const{
   return this->State;
}




int  main()
{
   OrderProcessingSystem *ops = new OrderProcessingSystem("Sid's Amazing Store","SAS",123, "Main Street", 94539, "CA");
   
   try{
      ops->Init();
      ops->Start();
   }
   catch (const char *error){
      cout << error << endl;
   }
   

   if (ops != NULL){
      delete ops;
   }                                      //de-allocation of InventorySystem object



   return 0;
}

