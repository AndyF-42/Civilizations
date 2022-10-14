#include "civs.h"
#define MAIN_MENU 0
#define FARMING 1
#define MINING 2
#define HUNTING 3


/* Andy Fleischer - CS202 - Program 2 - 7/23/2021
 * ----------------------------------------------
 * Main manages the civilizations in a turn-based
 * minigame-playing game. The user will be able to
 * travel across the "world" to different civilizations
 * and play their minigames. After a certain number
 * of rounds, play stops and points are calculated.
*/


using namespace std;

void help(int menu);
void civ(Civilization *& my_civ, int type);
void RTTI(Civilization *& my_civ);


int main()
{
    cout << "--------------------" << endl;
    cout << "   Civilizations!   " << endl;
    cout << "--------------------" << endl;
    
    Civilization* my_civ = new Mining();

    //main menu loop
    char input;
    do
    {
        help(MAIN_MENU);
        cout << ">> ";
        cin >> input;

        //check which input
        switch (input)
        {
            case '0': break;
            case '1': civ(my_civ, FARMING); break;
            case '2': civ(my_civ, MINING); break;
            case '3': civ(my_civ, HUNTING); break;
            default: cout << "Invalid command." << endl;
        }
    }
    while (input != '0');

    delete my_civ;

    return 0;
}


//print out a certain menu
void help(int menu)
{
    cout << endl;
    if (menu == MAIN_MENU)
    {
        cout << "------MENU------" << endl;
        cout << "0 - Quit" << endl;
        cout << "1 - Farming" << endl;
        cout << "2 - Mining" << endl;
        cout << "3 - Hunting" << endl;
    }
    else
    {
        switch (menu)
        {
            case FARMING: cout << "-----FARMING------" << endl;
                          cout << "0 - Back" << endl;
                          cout << "1 - Farm" << endl;
                          break;
            case MINING: cout << "-----MINING-----" << endl;
                         cout << "0 - Back" << endl;
                         cout << "1 - Mine" << endl;
                         break; 
            case HUNTING: cout << "-----HUNTING------" << endl;
                          cout << "0 - Back" << endl;
                          cout << "1 - Hunt" << endl; 
                          break;
            default: break;
        }
        cout << "2 - Buy" << endl;
        cout << "3 - Sell" << endl;
        cout << "4 - Display" << endl;
    }
    cout << "----------------" << endl;
    cout << endl;
}


//loops to get user input on a certain civ type
void civ(Civilization *& my_civ, int type)
{
    if (my_civ)
        delete my_civ;

    //get the name
    char name_input[30];
    cout << "Civilization name: ";
    cin.clear(); cin.ignore(1000, '\n');
    cin.get(name_input, 30);
    cin.clear(); cin.ignore(1000, '\n');
    char* name = new char[strlen(name_input) + 1];
    strcpy(name, name_input);

    switch (type) //make the right civilization
    {
        case FARMING: my_civ = new Farming(name); break;
        case MINING:  my_civ = new Mining(name);  break;
        case HUNTING: my_civ = new Hunting(name); break;
        default: break;
    }
    delete [] name;

    char input;
    do
    {
        //display menu and get input
        help(type);
        cout << ">> ";
        cin >> input;

        //check input
        switch (input)
        {
            case '0': break;
            case '1': RTTI(my_civ); break;
            case '2': my_civ->buy(); break;
            case '3': my_civ->sell(); break;
            case '4': my_civ->display(); break;
            default: cout << "Invalid command." << endl; break;
        }
    }
    while (input != '0');
}


void RTTI(Civilization *& my_civ)
{
    Farming* ptr = dynamic_cast<Farming*>(my_civ);
    if (ptr)
        ptr->farm();
    else
    {
        Mining* ptr = dynamic_cast<Mining*>(my_civ);
        if (ptr)
            ptr->mine();
        else
        {
            Hunting* ptr = dynamic_cast<Hunting*>(my_civ);
            if (ptr)
                ptr->hunt();
        }
    }
}
