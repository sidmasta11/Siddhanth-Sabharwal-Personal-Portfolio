 /*
BookStoreSystem.cpp
Main entry point for the app
*/

#include "BookStoreSystem.h"
#define MAX_LOGIN_ATTEMPTS 3


BookStoreSystem::BookStoreSystem()
{
    inventory = new InventoryList("Inventory List", "/Users/Captain/GitHub/BookStoreApp/BookStoreApp/databases/book-inventory.txt");
    employeeListing = new EmployeeList("Employee List", "/Users/Captain/GitHub/BookStoreApp/BookStoreApp/databases/employee-list.txt");
    transactionsList = new OrderList("Order List", "/Users/Captain/GitHub/BookStoreApp/BookStoreApp/databases/orders.txt", employeeListing, inventory);
}

BookStoreSystem::BookStoreSystem(string storeName, string storeAddress, string invPATH, string empPATH, string tranPATH) : storeName(storeName), storeAddress(storeAddress), invPATH(invPATH), empPATH(empPATH), tranPATH(tranPATH)
{
   try{
      initLists(invPATH, empPATH, tranPATH);
   }catch(string e){
      throw;
   }
}

BookStoreSystem::~BookStoreSystem()
{

   delete transactionsList;
   delete inventory;
   delete employeeListing;
   cout << "\nBook Store Sytem Deleted\n" << endl;

}

void BookStoreSystem::initLists(string invPATH, string empPATH, string tranPATH)
{
    inventory = new InventoryList("Inventory List", invPATH);
    employeeListing = new EmployeeList("Employee List", empPATH);
    transactionsList = new OrderList("Transaction List", tranPATH, employeeListing, inventory);
	user = login();
}

Person * BookStoreSystem::login() 
{
	Person * loginPerson = NULL;
	int loginPIN;
	for (int i = 0; i < MAX_LOGIN_ATTEMPTS; i++)
	{
		cout << "\nEnter your PIN\n Try #" << i + 1 << endl;
		cin >> loginPIN;
		loginPerson = employeeListing->Search(loginPIN);
		if (loginPerson != NULL)
		{
			return(loginPerson);
		}
	}
	cout << "\nMaximum Attempts reached. Exitting...\n";
	cin.ignore();
	exit(1);
}

void BookStoreSystem::menu()
{
    char choice; 
    bool menuIsRunning = true;

    while (menuIsRunning)
    {
       cout << "\n1) Display Employees\n"
          << "2) Display Transactions\n"
          << "3) Display Inventory\n"
          << "4) Edit Employees\n"             //using Employee I.D.
          << "5) Edit Transactions\n"         //using Transaction I.D.
          << "6) Edit Inventory\n"             //using product I.D.
          << "7) Search Inventory\n"
          << "(q to quit)\n"
          << "Select an option: ";
        cin >> choice;
        switch (choice)
        {
            case '1':
                showEmployees();            //DONE
                break;
            case '2':
                showTransactions();         //Show Transactions
                break;
            case '3':
                showInventory();            //DONE
                break;
            case '4':
                modifyEmployees();		
                break;
            case '5':
                modifyTransactions();
                break;
            case '6':
                modifyInventory();
                break;
            case '7':
                searchInventory();
                break;
            case 'q':
            case 'Q':
                menuIsRunning = false;
                break;
            default:
                break;
        }
        cin.ignore(1000, '\n');
        cin.clear();
    }
	return;
}

// three below are done
void BookStoreSystem::showInventory() const
{
   inventory->DisplayList();
}
void BookStoreSystem::showTransactions() const
{
   transactionsList->DisplayList();
}
void BookStoreSystem::showEmployees() const
{
   employeeListing->DisplayList();
}


// Below methods modify the vectors

//Inventory Interaction
//Menu
void BookStoreSystem::modifyInventory()
{
   int targetProdID = 0;
   int choice = 0;
   Item * targetItem = NULL;
   int searchISBN = 0;
   Item* editableItem = NULL;

   cout << "1) Add New Item\n" << endl << "2) Remove Item\n" << endl << "3) View Item\n" << endl << "4) Reorder Existing Item\n" << endl;
   cin >> choice;
   if (choice == 1)
   {
      addItem();
      return;
   }

   if (choice == 1 || choice == 2 || choice == 3)
{
   cout << "\nEnter product ID:" << endl;
   cin >> targetProdID;
   targetItem = inventory->SearchID(targetProdID);
   if (targetItem == 0)
   {
      cout << "\nItem not found in database";
      return;
   }
}

    
    switch (choice)
    {
    case 1:
        addItem();
        break;
    case 2:
        removeItem(targetItem);
        break;
    case 3:
        viewItem(targetItem);
		break;
    case 4:
       editableItem = searchInventory();
       break;
    default:
        cout << "Invalid selection";
        break;
    }
}
//add a new item
Item * BookStoreSystem::addItem()
{

    int quantity;
    int ISBN;
    int itemType;
    int genreInt;
    int eFileInt;
    int numPages;
    double price;
    string author;
    string bookType="" ;
    string title;
    string publisher;
    string name;
    genreType genre;
    audioFileFormat audioFileFormat;
    eBookFileFormat eFileFormat;
    Item * newItem = NULL;

    cout << "\n1.)eBook\n2.)Audio Book\n3.)Paper Book" << endl;
    cin >> itemType;
    if (itemType == 1)
        bookType = "eBook";
    else if (itemType == 2)
        bookType = "Audio Book";
    else if (itemType == 3)
        bookType = "Paper Book";
    else
    {
        cout << "invalid selection";
        return NULL;
    }

    cout << "\nBook quantity?\n";
    cin >> quantity;

    cout << "\nBook price?\n";
    cin >> price;

    cout << "\nBook isbn?\n";
    cin >> ISBN;
    cin.ignore();

    cout << "\nBook author?\n";
    getline(cin, author);
    cout << "\nBook title?\n?";
    getline(cin, title);
    cout << "\nBook genre?\n?"
        << "0 Unknown\n 1 Science fiction\n 2 Mystery\n 3 Horror\n 4 Romance\n"   ;
    cin >> genreInt;
    genre = (genreType)genreInt;
    cin.ignore();
    cout << "\nBook publisher?\n?";
    getline(cin, publisher);

    if (itemType == 1)
    {
        cout << "Which eBook file format?\n"
            << "1 Unknown/Other \n2 PDF \n3 EPUB\n";
        cin >> eFileInt;
        eFileFormat = (eBookFileFormat)eFileInt;
        newItem = new eBook(bookType, quantity, price, ISBN, author, title, genre, publisher, eFileFormat);
    }
    else if (itemType == 2)
    {
        string YesOrNo;
        cout << "\nIs this Audio Book an mp3 Y/N ?\n";
        cin >> YesOrNo;
        if (toupper(YesOrNo[0]) == 'Y')
           audioFileFormat = MP3;
        else
            audioFileFormat = UNKNOWN_AUDIO;
        newItem = new AudioBook(bookType, quantity, price, ISBN, author, title, genre, publisher, audioFileFormat);
    }  
    else
    {
        cout << "\nHow many pages in your book??\n";
        cin >> numPages;
        newItem = new PaperBook(bookType, quantity, price, ISBN, author, title, genre, publisher, numPages);
    }
    inventory->AddToList(newItem);
	return newItem;
}
//remove an item
void BookStoreSystem::removeItem(Item * targetItem)
{
    inventory->RemoveFromList(targetItem);
}
//view an Item by its ID
void BookStoreSystem::viewItem(Item * targItem)
{
	AudioBook * ab = dynamic_cast<AudioBook  *>(targItem);
	eBook * eb = dynamic_cast<eBook *>(targItem);
	PaperBook * pb = dynamic_cast<PaperBook *>(targItem);

	if (ab)
	{
		cout << "\n" << *ab << "\n";
	}
	else if (eb)
	{
		cout << "\n" << *eb << "\n";
	}
	else if (pb)
	{
		cout << "\n" << *pb << "\n";
	}
}
//Search the inventory  by author, name, isbn
Item* BookStoreSystem::searchInventory()
{   
   int searchISBN;
   cout << "Enter ISBN: ";
   cin >> searchISBN;

   Item * search = inventory->Search(searchISBN);

   eBook * eb = dynamic_cast<eBook  *>(search);
   AudioBook * ap = dynamic_cast<AudioBook *>(search);
   PaperBook * pb = dynamic_cast<PaperBook *>(search);

      if (eb){
         cout << *eb << endl;
         return eb;
      }
      else if (ap){
         cout << *ap << endl;
         return ap;
      }
      else if (pb){
         cout << *pb << endl;
         return pb;
      }
      else{ 
         cout << "ISBN not found." << endl; 
         return NULL;
      }

   return NULL;
}


//Transaction Interaction
//Menu
void BookStoreSystem::modifyTransactions() {

	int targetOrderID = 0;
	int choice = 0;
	StoreOrder * targetOrder = NULL;

	cout
		<< "1) Reorder existing product\n"
		<< "2) Order a new product\n"
		<< "3) Remove Order\n"
		<< "4) View Order\n" << endl;
	cin >> choice;
    if (choice == 1) 
	{
		makeStoreOrder();
        cin.ignore();
        return;
    }
	if (choice == 2)
	{
		newStoreOrder();
		return;
	}

    cout << "\nEnter order ID:" << endl;
    cin >> targetOrderID;
    targetOrder = transactionsList->Search(targetOrderID);
    if (!targetOrder) 
	{        //If order does not exist
        cout << "\nOrder not found in database";
        cin.ignore();
        return;
    }
    switch (choice) {
        case 3:
            removeTransaction(targetOrder);
            break;
        case 4:
			cout << targetOrder;
            break;
        default:
            cout << "Invalid selection";
            break;
    }
}
//order a New item not in the data base
void BookStoreSystem::makeStoreOrder()
{
	int ProdID;
	int quantity;
	StoreOrder * sOrder = NULL;
	cout << "\nWhich item would you like to reorder (enter a product ID)" << endl;
	cin >> ProdID;
	Item * itemOrdered = inventory->SearchID(ProdID);
	if (!itemOrdered) //if not found
	{
		cout << "\nItem not found\n";
		return;
	}
	cout << "\nHow many more would you like to order?\n";
	cin >> quantity;

	sOrder = new StoreOrder(itemOrdered, quantity, "Amazon", user);
	transactionsList->AddToList(sOrder);

	cout << "\nOrder completed\n";
}

//Order an item already in the Database
void BookStoreSystem::newStoreOrder()
{
	Item * newItem = addItem();
	StoreOrder * newOrder = NULL;
	int quantity;
	cout << "\nHow many more would you like to order??" << endl;
	cin >> quantity;
	newOrder = new StoreOrder(newItem, quantity, "Amazon", user);
	transactionsList->AddToList(newOrder);
}
void BookStoreSystem::removeTransaction(StoreOrder *  targetOrder)
{
	transactionsList->RemoveFromList(targetOrder);
}
void BookStoreSystem::viewTransaction(StoreOrder * ORDA)
{
	if (ORDA == NULL)
	{
		cout << "order not found";
		return;
	}
	cout << ORDA;
}


void BookStoreSystem::modifyEmployees()
{
    int targetPersonID;
    int choice;
    Person * targetPerson = NULL;

    cout << "1) Add Person\n"
         << "2) Remove Person\n"
            "3) View Person\n" << endl;
    cin >> choice;

    if (choice == 1)
    {
        addEmployee();
        cin.ignore();
        return;
    }

    cout << "\nEnter Employee ID:" << endl;
    cin >> targetPersonID;

    targetPerson = employeeListing->Search(targetPersonID);
    if (!targetPerson)         //If person does not exist
    {
        cout << "\nPerson not found in database";
        cin.ignore();
        return;
    }
    
    switch (choice)
    {
    case 1: 
        addEmployee();
        break;
    case 3:
        viewEmployee(targetPerson);
        break;
    case 2:
        removeEmployee(targetPerson);
        break;
    default:
        cout << "Invalid selection";
        break;
    }

}
void BookStoreSystem::addEmployee()
{
    char yesNo;
    bool isManager = false;
    managerType managerlvl;
    int managerlvlInt;
    int age;
    string name;
    string address;
    Person * newGuy;

    cin.ignore();
    cout << "Person's Full name?\n";
    getline(cin, name);
    
    
    cout << "A manager? Y/N\n";
    cin >> yesNo;
    if (toupper(yesNo) == 'Y')
        isManager = true;
    
    cout << "\nPerson's age?\n";
    cin >> age;
    cin.ignore();

    cout << "\nPerson's address?\n";
    getline(cin, address);

    if (isManager)
    {
        cout << endl << "Manager Level:" << endl 
           << "0. Shift Manager" << endl << 
           "1. Store Manager" << endl 
           << "2. VP" << endl 
           << "3. CEO" << endl 
           << "Enter Here: ";
        cin >> managerlvlInt;
        if (managerlvlInt > 3 || managerlvlInt < 0)
        {
            cout << "Invalid #" << endl;
            return;
        }
        managerlvl = (managerType)managerlvlInt;
        newGuy = new Manager(age, address, name, NULL, managerlvl);
    }else{

        newGuy = new Employee(age, address, name, NULL);
    }

    employeeListing->AddToList(newGuy);

}
void BookStoreSystem::removeEmployee(Person * targetPerson)
{
    if (targetPerson != NULL) //person found
        employeeListing->RemoveFromList(targetPerson);
    else
        cout << "\nPerson not found\n";
}
void BookStoreSystem::viewEmployee(Person * targ)
{
    Manager * mg = dynamic_cast<Manager  *>(targ);
    Employee * ep = dynamic_cast<Employee *>(targ);
    Customer * cs = dynamic_cast<Customer *>(targ);

    if (mg)
    {
        cout << "\n" << *mg << "\n";
    }
    else if (ep)
    {
        cout << "\n" << *ep << "\n";
    }
    else if (cs)
    {
        cout << "\n" << *cs << "\n";
    }
}


////Time did not permit:
	//void BookStoreSystem::editItem(Item * targetItem){} 
	//void BookStoreSystem::editTransaction(Order<Item *> * targetTransaction){}
	//void BookStoreSystem::editEmployee(Person * Employee){}
