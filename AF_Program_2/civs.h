#include <iostream>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <iterator>
#include <chrono>
#include <thread>

/* Andy Fleischer - CS202 - Program 2 - 7/23/2021
 * ----------------------------------------------
 * This file manages six classes: the abstract base
 * Civilization, handling anything that every civ
 * needs, three civs derived from Civilization:
 * Farming, Mining, and Hunting, each with their
 * own unique versions of civ functions and
 * civ-specific methods. Also, a Node with a
 * next and previous pointer, and an upcasted
 * civilization pointer. Lastly, a DLL class to
 * store the nodes as a doubly-linked list.
*/


class Civilization
{
    public:
        Civilization(); //default constructor - chooses a random civilization name
        Civilization(char* civ_name);
        Civilization(const Civilization& source); //copy constructor
        virtual ~Civilization(); //destructor
        
        virtual void buy() = 0;
        virtual void sell() = 0;
        virtual void display() const;

        bool is_name(const char* the_name) const;

    protected:
        char* name;
        int money;
        std::vector<std::string> items; //holds purchased special items
};


class Farming : public Civilization
{
    public:
        Farming(); //default constructor - random name
        Farming(char* civ_name);

        void buy();
        void sell();
        void display() const;

        void farm(); //farming minigame

    protected:
        int farm_results(int wanted, std::string name, int music); //helps out farming minigame
        
        int wheat;
        int carrots;
        int potatoes;
};


class Mining : public Civilization
{
    public:
        Mining(); //random civ name
        Mining(char* civ_name);

        void buy();
        void sell();
        void display() const;

        void mine(); //mining minigame

    protected:
        int iron;
        int silver;
        int gold;
};


class Hunting : public Civilization
{
    public:
        Hunting(); //random civ name
        Hunting(char* civ_name);

        void buy();
        void sell();
        void display() const;

        void hunt(); //hunting minigame

    protected:
        void draw_ascii(int animal); //used in hunting minigame

        int boar;
        int turkey;
        int quail;
};


// ==== DATA STRUCTURE ==== //


class Node
{
    public:
        Node(); //default constructor
        Node(Civilization * source); //constructor

        Node *& go_next();
        Node *& go_previous();
        void set_next(Node *& the_next);
        void set_previous(Node *& the_previous);
        Civilization * get_civ();


    private:
        Civilization* civ;
        Node* next;
        Node* previous;
};


class DLL
{
    public:
        DLL(); //constructor
        DLL(const DLL& source); //copy constructor
        ~DLL(); //destructor

        void insert(Civilization * to_add); //insert civilization into DLL
        void remove(const char* name); //remove civilization with matching name
        void display() const; //display all data
        void remove_all(); //delete every node

    private:
        void remove(const char* name, Node *& head);
        void display(Node * head) const;
        void remove_all(Node *& head);
        void copy_all(Node *& head, Node * previous, Node * source_head);

        Node* head;
        Node* tail;
};
