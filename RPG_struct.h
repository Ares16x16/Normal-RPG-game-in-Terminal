#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// structure of in-game items
struct item{
    string name;  //item stats
    int quantity;
    item(string name, int quantity) {  // constructor
        this->name = name;
        this->quantity = quantity;	
    };
};

// enemies
class enemy{   
    public:  	
  	    int health;    //enemy stats
  	    int atk;
  	    int def;
  	    int money;   //enemy money drop
  	    string drop_item;   //store what the enemy drops
  	    string name;   //enemy name
  
enemy(int a, int b, int c, int d, string e, string f) {  // constructor
            health = a;
            atk = b;
            def = c;
            money = d;
            drop_item = e;
            name = f; 
        }
};

// player
class player{
    public:
        string name;  //player's stat
  	    string weapon;
  	    string armor;
        int health;
        int atk;
        int def;
        int location[2];
  	    int money = 0;
  	    vector<item> backpack;    //for storing items
  	    bool player_dead = false;  //wether the player is dead, for deciding end game situation
};


// Declearation of functions
void battle(enemy e, player &p1);
void main_menu(player &p1);
void use_item(string item, player &p1);
int opening();
void shop(player &p1);
void create_character(player &p1);
bool load_game(player &p1);
void clearScreen();
