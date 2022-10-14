#include "civs.h"

/* Andy Fleischer - CS202 - Program 2 - 7/23/2021
 * ----------------------------------------------
 * This file manages six classes: the abstract base
 * Civilization, handling anything that every civ
 * needs, three civs derived from Civilization:
 * Agricultural, Mining, and Hunting, each with
 * their own unique versions of civ functions and
 * civ-specific methods. Also, a Node with a
 * next and previous pointer, and an upcasted
 * civilization pointer. Lastly, a DLL class to
 * store the nodes as a doubly-linked list.
*/


// ==== Civilization ==== //


Civilization::Civilization() : money(10)
{
    srand(time(NULL));

    //choose random name
    switch (rand() % 5)
    {
        case 0: name = new char[7];
                strcpy(name, (char*)("Aztecs"));
                break;
        case 1: name = new char[7];
                strcpy(name, (char*)("Romans"));
                break;
        case 2: name = new char[7];
                strcpy(name, (char*)("Franks"));
                break;
        case 3: name = new char[7];
                strcpy(name, (char*)("Mayans"));
                break;
        case 4: name = new char[6];
                strcpy(name, (char*)("Incas"));
                break;
    }
}

Civilization::Civilization(char* civ_name) : money(10)
{
    srand(time(NULL));

    name = new char[strlen(civ_name) + 1];
    strcpy(name, civ_name);
}

Civilization::Civilization(const Civilization& source)
{
    name = new char[strlen(source.name) + 1];
    strcpy(name, source.name);
    
    money = source.money;
    items = source.items;
}

Civilization::~Civilization()
{
    delete [] name;
    name = NULL;
}

void Civilization::display() const
{
    std::cout << name << std::endl;
    std::cout << "$" << money << std::endl;
}

bool Civilization::is_name(const char* the_name) const
{
    return strcmp(the_name, name) == 0;
}


// ==== Farming ==== //


Farming::Farming() : wheat(0), carrots(0), potatoes(0)
{}

Farming::Farming(char* civ_name) : Civilization(civ_name), wheat(0), carrots(0), potatoes(0)
{}

void Farming::buy()
{
    if (money < 10)
    {
        std::cout << "Not enough money!" << std::endl;
        return;
    }
    std::cout << "Bought 1 wheat!" << std::endl;
    money -= 10;
    wheat += 1;
}

void Farming::sell()
{
    int profit = 10 * (wheat + carrots + potatoes);
    std::cout << "Sold all crops for $" << profit << "!" << std::endl;
    money += profit;
    wheat = 0;
    carrots = 0;
    potatoes = 0;
}

//display all data
void Farming::display() const
{
    Civilization::display();

    std::cout << std::endl;
    std::cout << "Wheat: " << wheat << std::endl;
    std::cout << "Carrots: " << carrots << std::endl;
    std::cout << "Potatoes: " << potatoes << std::endl;
}

//farming minigame
void Farming::farm()
{
    //game explanation
    std::cout << "~~~ FARM ~~~" << std::endl;
    std::cout << "In this game, you need to grow your crops by playing" << std::endl;
    std::cout << "them some music! However, each crop will have a certain" << std::endl;
    std::cout << "music type they want to listen to, which you will get a" << std::endl;
    std::cout << "hint to. Choose what music to play, but be careful! Some" << std::endl;
    std::cout << "crops may not enjoy the music you choose to play." << std::endl;
    std::cout << "Press enter to start." << std::endl;

    std::cin.clear(); std::cin.ignore(1000, '\n');
    std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' ); //wait for enter

    //set up clues and what each crop wants
    std::string clues[3] = {"are wearing their Run-DMC chains today.",
                            "are wearing their Taylor Swift merch today",
                            "are wearing their Beethoven wigs today."};
    int wheat_want = rand() % 3;
    int carrots_want = rand() % 3;
    int potatoes_want = rand() % 3;
    std::cout << "The wheat " << clues[wheat_want] << std::endl;
    std::cout << "The carrots " << clues[carrots_want] << std::endl;
    std::cout << "The potatoes " << clues[potatoes_want] << "\n" << std::endl;

    //ask for music and get input
    std::cout << "What music do you want to play for your crops today?" << std::endl;
    std::cout << "1 - Hip Hop" << std::endl;
    std::cout << "2 - Pop" << std::endl;
    std::cout << "3 - Classical" << std::endl;
    std::cout << ">> ";

    int music;
    std::cin >> music;
    std::cout << std::endl;
    music -= 1; //minus one since we want 0 to 2

    //update each plant, but don't let it go below zero
    wheat += farm_results(wheat_want, "wheat", music);
    carrots += farm_results(carrots_want, "carrots", music);
    potatoes += farm_results(potatoes_want, "potatoes", music);
    wheat = std::max(wheat, 0);
    carrots = std::max(carrots, 0);
    potatoes = std::max(potatoes, 0);
}

//this function prints out how the crop felt about the music and returns the amount of crop gained
int Farming::farm_results(int wanted, std::string name, int music)
{
    int gain = rand() % 3; //0 to 2
    std::cout << "The " << name << " ";
    
    if (music == wanted)
    {
        std::cout << "liked your music choice! +";
        gain += 3; //3 to 6
    }
    else if (music == (wanted + 1) % 3)
    {
        std::cout << "hated your music choice! ";
        gain -= 3; //-3 to -1
    }
    else
        std::cout << "are ambivalent about your music choice. +";

    std::cout << gain << " " << name << "." << std::endl;
    return gain;
}


// ==== Mining ==== //


Mining::Mining() : iron(0), silver(0), gold(0)
{}

Mining::Mining(char* civ_name) : Civilization(civ_name), iron(0), silver(0), gold(0)
{}

void Mining::buy()
{
    if (money < 5)
    {
        std::cout << "Not enough money!" << std::endl;
        return;
    }
    std::cout << "Bought 1 iron!" << std::endl;
    money -= 5;
    ++iron;
}

void Mining::sell()
{
    int profit = 5 * iron + 10 * silver + 15 * gold;
    std::cout << "Sold all ores for $" << profit << "!" << std::endl;
    money += profit;
    iron = 0;
    silver = 0;
    gold = 0;
}

void Mining::display() const
{
    Civilization::display();

    std::cout << std::endl; 
    std::cout << "Iron: " << iron << std::endl;
    std::cout << "Silver: " << silver << std::endl;
    std::cout << "Gold: " << gold << std::endl;
}

void Mining::mine()
{
    //game explanation
    std::cout << "~~~ MINE ~~~" << std::endl;
    std::cout << "The caves are a dangerous place, but can be full of great" << std::endl;
    std::cout << "resources, too! At every stop, you will earn some ores," << std::endl;
    std::cout << "but be careful! The further you head into the caves, the" << std::endl;
    std::cout << "more likely it is that you will get injured and lose many" << std::endl;
    std::cout << "of your resources." << std::endl;
    std::cout << "To head into the caves, press enter." << std::endl;

    //waits for user enter
    std::cin.clear(); std::cin.ignore(1000, '\n');
    std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' ); //wait for enter

    int death_chance = 0;
    char again;
    int iron_gained = 0;
    int silver_gained = 0;
    int gold_gained = 0;
    int gain = 0;

    do
    {
        int roll = rand() % 100; //random 0-99
        if (roll > death_chance) //survive
        {
            std::cout << "You carefully make your way into the next cavern. Ores are" << std::endl;
            std::cout << "everywhere! You mine away at them and come away with:" << std::endl;

            //ore gains
            gain = rand() % 3 + 3 * (death_chance / 10) + 1;
            iron_gained += gain;
            std::cout << gain << " iron" << std::endl;

            gain = std::max(0, rand() % 3 + 3 * (death_chance / 10) - 2);
            silver_gained += gain;
            std::cout << gain << " silver" << std::endl;

            gain = std::max(0, rand() % 3 + 3 * (death_chance / 10) - 5);
            gold_gained += gain;
            std::cout << gain << " gold" << std::endl;

            std::cout << "Would you like to venture further? It looks" << std::endl;
            std::cout << "more dangerous up ahead... (y/n) ";
            std::cin >> again;
            death_chance += 10;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "The ceiling starts crumbling down, rocks flying everywhere!" << std::endl;
            std::cout << "You scramble to get out, dropping some of your minerals on" << std::endl;
            std::cout << "the way. Luckily, you barely make it out alive." << std::endl;
            iron_gained /= 4;
            silver_gained /= 4;
            gold_gained /= 4;
            again = 'n';
        }

    }
    while (tolower(again) == 'y');

    std::cout << "You walk out with:" << std::endl;
    std::cout << iron_gained << " iron" << std::endl;
    std::cout << silver_gained << " silver" << std::endl;
    std::cout << gold_gained << " gold" << std::endl;
    iron += iron_gained;
    silver += silver_gained;
    gold += gold_gained;
}


// ==== Hunting ==== //


Hunting::Hunting() : boar(0), turkey(0), quail(0)
{}

Hunting::Hunting(char* civ_name) : Civilization(civ_name), boar(0), turkey(0), quail(0)
{}

void Hunting::buy()
{
    if (money < 3)
    {
        std::cout << "Not enough money!" << std::endl;
        return;
    }
    std::cout << "Bought 1 quail!" << std::endl;
    money -= 3;
    ++quail;
}

void Hunting::sell()
{
    int profit = 3 * quail + 5 * turkey + 7 * boar;
    std::cout << "Sold all meat for $" << profit << "!" << std::endl;
    money += profit;
    quail = 0;
    turkey = 0;
    boar = 0;
}

void Hunting::display() const
{
    Civilization::display();

    std::cout << std::endl;
    std::cout << "Boar: " << boar << std::endl;
    std::cout << "Turkey: " << turkey << std::endl;
    std::cout << "Quail: " << quail << std::endl;
}

//hunting minigame
void Hunting::hunt()
{
    std::cout << "~~~ HUNT ~~~" << std::endl;
    std::cout << "Once you start the game, wait for the animal to appear." << std::endl;
    std::cout << "Once the animal appears, press the enter key to fire an" << std::endl;
    std::cout << "arrow. You can fire as many arrows as you want, but some" << std::endl;
    std::cout << "may miss. If you hit enough arrows before the animal runs" << std::endl;
    std::cout << "away, you win!" << std::endl;
    std::cout << "When you are ready, press enter." << std::endl;
    
    //waits for user enter
    std::cin.clear(); std::cin.ignore(1000, '\n');
    std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' ); //wait for enter

    int wait = rand() % 3000 + 2000; // 2000-5000 milliseconds sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(wait)); 

    int animal = rand() % 3; //choose animal and show it
    draw_ascii(animal);
    
    char input;
    int hits = 0;
    //user gets five seconds
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point curr;
    while (hits < 15 && ((std::chrono::duration_cast<std::chrono::microseconds>(curr - begin).count()) / 1000000.0 < 5))
    {
        std::cin.get(input);
        int shot = rand() % 100;
        int odds = 50;

        if (input == '\n' && shot < odds)
        {
            std::cout << "HIT";
            hits++;
        }
        else
            std::cout << "MISS";
        curr = std::chrono::steady_clock::now();
    }

    //TODO - change odds and hits required depending on animal, and make helper function for this:
    if (hits >= 15)
    {
        std::cout << "\nYou took down the " << std::endl;
        int gain = rand() % 3 + 3;
        switch (animal)
        {
            case 0: std::cout << "boar!" << std::endl;
                    std::cout << "+" << gain << " boar." << std::endl;
                    boar += gain; 
                    break;
            case 1: std::cout << "turkey!" << std::endl;
                    std::cout << "+" << gain << " turkey." << std::endl;
                    turkey += gain;
                    break;
            case 2: std::cout << "quail!" << std::endl;
                    std::cout << "+" << gain << " quail." << std::endl;
                    quail += gain;
                    break;
            default: break;
        }
                
    }
    else
        std::cout << "\nThe animal ran away! Better luck next time." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(2)); //sleep so user stops pressing space lol
}

// 0 = boar, 1 = turkey, 2 = quail
void Hunting::draw_ascii(int animal)
{
    switch (animal)
    {
        case 0: std::cout << std::endl;
                std::cout << "   ,__         __," << std::endl;
                std::cout << "    \\)`\\_..._/`(/" << std::endl;
                std::cout << "    .'  _   _  '." << std::endl;
                std::cout << "   /    o\\ /o   \\" << std::endl;
                std::cout << "   |    .-.-.    |  _" << std::endl;
                std::cout << "   |   /() ()\\   | (,`)" << std::endl;
                std::cout << "  / \\  '-----'  / \\ .'" << std::endl;
                std::cout << " |   '-..___..-'   |" << std::endl;
                std::cout << " |                 |" << std::endl;
                std::cout << " |                 |" << std::endl;
                std::cout << " ;                 ;" << std::endl;
                std::cout << "  \\      / \\      /" << std::endl;
                std::cout << "   \\-..-/'-'\\-..-/" << std::endl;
                std::cout << "    \\/\\/     \\/\\/" << std::endl;
                std::cout << std::endl;
                break;
        case 1: std::cout << std::endl;
                std::cout << "   .--." << std::endl;
                std::cout << "  /} p \\             /}" << std::endl;
                std::cout << " `~)-) /           /` }" << std::endl;
                std::cout << "  ( / /          /`}.' }" << std::endl;
                std::cout << "   / / .-'""-.  / ' }-'}" << std::endl;
                std::cout << "  / (.'       \\/ '.'}_.}" << std::endl;
                std::cout << " |            `}   .}._}" << std::endl;
                std::cout << " |     .-=-';   } ' }_.}" << std::endl;
                std::cout << " \\    `.-=-;'  } '.}.-}" << std::endl;
                std::cout << "  '.   -=-'    ;,}._.}" << std::endl;
                std::cout << "    `-,_  __.'` '-._}" << std::endl;
                std::cout << "        `|||" << std::endl;
                std::cout << "       .=='=," << std::endl;
                std::cout << std::endl;
                break;
        case 2: std::cout << std::endl;
                std::cout << "         _" << std::endl;
                std::cout << "     __// \\" << std::endl;
                std::cout << "    /.__.\\" << std::endl;
                std::cout << "    \\ \\/ /" << std::endl;
                std::cout << " '__/    \\" << std::endl;
                std::cout << "  \\-      )" << std::endl;
                std::cout << "   \\_____/" << std::endl;
                std::cout << "     | |" << std::endl;
                std::cout << "     \" \"" << std::endl;
                std::cout << std::endl;
                break;
        default: break;
    }
}


// ==== Node ==== //


Node::Node() : civ(nullptr), next(nullptr), previous(nullptr)
{}

Node::Node(Civilization * source) : next(nullptr), previous(nullptr)
{
    civ = source;
}

Node *& Node::go_next()
{
    return next;
}

Node *& Node::go_previous()
{
    return previous;
}

void Node::set_next(Node *& the_next)
{
    next = the_next;
}

void Node::set_previous(Node *& the_previous)
{
    previous = the_previous;
}

Civilization * Node::get_civ()
{
    return civ;
}


// ==== DLL ==== //


DLL::DLL() : head(nullptr), tail(nullptr)
{}

DLL::DLL(const DLL& source)
{
    copy_all(head, NULL, source.head); 
}

void DLL::copy_all(Node *& head, Node * previous, Node * source_head)
{
    if (!source_head)
    {
        head = NULL;
        return;
    }

    head = new Node(source_head->get_civ());
    head->set_previous(previous);

    copy_all(head->go_next(), head, source_head->go_next());
}

DLL::~DLL()
{
    remove_all();
}

void DLL::insert(Civilization * to_add)
{
    Node* new_node = new Node(to_add);
    tail->set_next(new_node);
    new_node->set_previous(tail);
    tail = new_node;
}

void DLL::remove(const char* name)
{
    remove(name, head);
}

void DLL::remove(const char* name, Node *& head)
{
    if (!head)
        return;

    if (head->get_civ()->is_name(name))
    {
        Node* temp = head->go_previous();
        if (temp)
            temp->set_next(head->go_next());
        if (head->go_next())
            head->go_next()->set_previous(temp);

        delete head->get_civ();
        delete head; 
        return;
    }
    remove(name, head->go_next());
}

void DLL::display() const
{
    display(head);  
}

void DLL::display(Node * head) const
{
    head->get_civ()->display();
    display(head->go_next());
}

void DLL::remove_all()
{
    remove_all(head);
}

void DLL::remove_all(Node *& head)
{
    if (!head)
    {
        head = NULL;
        return;
    }

    Node* temp = head;
    delete head->get_civ();
    delete head;
    head = temp;
    remove_all(head->go_next());
}
