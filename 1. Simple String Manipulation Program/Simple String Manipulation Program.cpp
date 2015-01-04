#include <iostream>

using namespace std;

class SmartString {

private:
   char *str;              //pointer to a char, named str

public:
   SmartString() :str(NULL){} //Default Constructor, initializes pointer str to NULL

   SmartString(char *p) //Nondefault Constructor
   {
      char msg[1024];
      char *cp = NULL;

      cp = msg;
      str = cp;
      int len = 0;
      while (*cp != '\0'){
         cp++;
         len++;
      }
      str = new char[len + 1];  //dynamic memory allocation

      cp = msg;
      char * s = str;
      while (*cp != '\0'){           //string is copied to str
         *s = *cp;
         ++cp;
         ++s;
      }
      *s = '\0';
   }

   ~SmartString() //Destructor, if str isn't NULL the array of characters is deleted
   {
      if (str != NULL)
         delete[] str;
   }

   void LoadString() {              //User enters string
      char msg[1024];               //max size of array is 1024 characters
      char *cp = NULL;

      if (str != NULL){
         delete[] str;
      }

      if (cin.peek() == '\n')
         cin.ignore();

      cout << "Enter string: ";
      cin.getline(msg, 1024);
      cp = msg;
      str = cp;
      int len = 0;
      while (*cp != '\0'){
         cp++;
         len++;
      }
      str = new char[len + 1];       //dynamic memory allocation for str based on input string length

      cp = msg;
      char * s = str;
      while (*cp != '\0'){           //input string is copied to str
         *s = *cp;
         ++cp;
         ++s;
      }
      *s = '\0';

      cout << "Your string is loaded, please choose one of the options again." << endl << endl;

      return;
   }


   void ShowString(){         //displays the string in appropriate format
      cout << "The string you loaded was [" << str << "]." << endl;
      cout << "Please choose one of the options again." << endl << endl;

      return;
   }

   int Size(){        //returns the number of characters in str

      int len = 0;
      char * dp = str;

      if (str == NULL || *str == '\0')      //if str is NULL, len = 0
         len = 0;
      else{
         while (*dp != '\0'){
            dp++;
            len++;
         }
      }
      cout << "Your string has " << len << " characters." << endl;
      cout << "Please choose one of the options again." << endl << endl;

      return len;
   }

   void Trim()          //removes all leading white-space characters in the original string str
   {
      char *tp = str;
      char *tp2 = str;

      while (isspace(*tp)){ ++tp; }

      while (*tp != 0)
      {
         *tp2 = *tp;
         ++tp;
         ++tp2;
      }

      *tp2 = '\0';

      cout << "Your originial string is now: [" << str << "]." << endl;
      cout << "Please choose one of the options again." << endl << endl;

      return;
   }

   void ToUpper()             //converts all letters in str string to upper case letters
   {
      char *up = str;

      while (*up != '\0')
      {
         *up = toupper(*up);
         *up++;
      }

      cout << "Your string is now: [" << str << "]." << endl;
      cout << "Please choose one of the options again." << endl << endl;

      return;
   }

   char * GetString(){ return str; }        //returns str

   void Reverse()                             //reverses string
   {
      int len = 0;
      char * dp = str;

      if (str == NULL || *str == '\0')      //if str is NULL, len = 0
         len = 0;
      else{
         while (*dp != '\0'){
            dp++;
            len++;                     //len is calculated again
         }
      }

      char *gp = str;
      char *gp2 = str + len - 1;

      while (gp < gp2)
      {
         char temp = *gp;
         *gp++ = *gp2;
         *gp2-- = temp;
      }


      cout << "Your string is now: [" << str << "]." << endl;
      cout << "Please choose one of the options again." << endl << endl;

      return;

   }

   bool Palindrome()               //checks if string is palindrome
   {
      bool pal = true;

      int len = 0;
      char * dp = str;
      if (str == NULL || *str == '\0')      //if str is NULL, len = 0
         len = 0;
      else{
         while (*dp != '\0'){
            dp++;
            len++;                     //len is calculated again
         }
      }

      char *gp = str;
      char *gp2 = str;

      for (int i = 0; i < len; i++)
      {
         if (toupper(*(gp + i)) == toupper(*(gp2 + (len - 1) - i)))

         {
            pal = true;
         }
         else{
            pal = false;
            break;
         }
      }

      if (pal == true)
         cout << "[" << str << "] is a palindrome." << endl;
      else
         cout << "[" << str << "] isn't a palindrome." << endl;

      cout << "Please choose another option." << endl << endl;
      return pal;
   }
};

//---------------------------

class SmartStringApp{

private:
   SmartString *ss;            //pointer to SmartString object named ss

public:
   SmartStringApp() :ss(NULL){} //default constructor, initiazlizes ss to NULL

   SmartStringApp(char *p2) : ss(NULL) //nondefault construtor
   {
      ss = new SmartString(p2);
   }

   ~SmartStringApp(){           //destructor, is ss isn't NULL then it is de-allocated
      if (ss != NULL)
         delete ss;
   }



   void Init(){               //invoked function LoadString from SmartString object ss, user can then input a string that gets loaded

      if (ss == NULL)
         ss = new SmartString();

      ss->LoadString();

      return;
   }

   void Start(){             //displays menu options and executes SmartString member functions based on user input

      int option;

      do{
         cout << "           Simple String Manipulation Program" << endl;
         cout << "1. Load String (Choose this option before choosing any others.)" << endl;
         cout << "2. Show String" << endl;
         cout << "3. Character Count" << endl;
         cout << "4. Trim String" << endl;
         cout << "5. Convert to Upper Case" << endl;
         cout << "6. Reverse String" << endl;
         cout << "7. Check for Palindrome." << endl;
         cout << "8. Quit" << endl;
         cout << "Enter Option: ";

         cin >> option;
         cout << endl;

         switch (option){

         case 1:
            Init();
            break;

         case 2: ss->ShowString();
            break;

         case 3: ss->Size();
            break;

         case 4: ss->Trim();
            break;

         case 5: ss->ToUpper();
            break;

         case 6: ss->Reverse();
            break;

         case 7: ss->Palindrome();
            break;

         case 8: cout << "Goodbye!" << endl;
            break;

         default: cout << "Please choose a number from 1 to 8." << endl << endl;
            break;
         }
      } while (option != 8);

      return;
   }

};

int main()
{

   SmartStringApp * fullp = NULL;         //pointer declaration to SmartStringApp

   if (fullp == NULL)
      fullp = new SmartStringApp();      //SmartStringApp's default object is dynamically created

   fullp->Start();                   //Start unction for the newly created SmartStringApp object is invoked

   delete fullp;                    //Frees memory for the SmartStringApp object

   return 0;
}