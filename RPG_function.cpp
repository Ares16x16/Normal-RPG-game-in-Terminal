#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include "RPG_struct.h"

using namespace std;

// Sets of data which will be used later in game
int difficulty = 0;
bool use_dragon_breathe = false;
int data_set[3][4] = {{200, 50, 50, 100}, {175, 45, 45, 75}, {160, 40, 40, 50}};  // initial value of player for different difficulty

// Area: Forest (health,atk,def,money drop)
// initialization of enemies, as well as variable to store if the boss is defeated
enemy Slime(15, 5, 1, 5, "", "Slime");  // enemy initialization
enemy Goblin(25, 15, 5, 7, "", "Goblin");
enemy Mio(40, 20, 10, 10, "Attack Potion", "Mio");
enemy Mutant(100, 25, 15, 25, "Health Potion", "Mutant");
bool Forest_boss_defeated = false;

// Area: Desert
enemy Lizard(40, 10, 15, 10, "Defense Potion", "Lizard");  // enemy initialization
enemy Cactus(35, 50, 5, 10, "Attack Potion", "Cactus");
enemy Pekora(50, 50, 15, 50, "Jailed Rabit Leg", "Pekora");
enemy Dragon(200, 50, 20, 30, "Dragon Breathe", "Dragon");
bool Desert_boss_defeated = false;

// Area: Maojo
enemy Executioner(75, 60, 60, 0, "", "Executioner");	// enemy initialization
enemy Solstice(80, 60, 60, 0, "", "Solstice");
enemy Strangler(90, 65, 60, 0, "", "Strangler");
enemy Calliope(350, 100, 80, 1000, "Ricky", "Calliope");
bool Final_boss_defeated = false;

//For saving the game into txt file
void save_game(player &p1) {  
    ofstream savefile;
    savefile.open("save.txt", ofstream::out | ofstream::trunc);    //if save.txt exists, clear the text file to prevent overwriting
    savefile.close();																							
    savefile.open("save.txt", ios::app);    //open the file 
    savefile << p1.name << endl;						// input player stats into the text file
    savefile << p1.weapon << endl;
    savefile << p1.armor << endl;
    savefile << p1.health << endl;
    savefile << p1.atk << endl;
    savefile << p1.def << endl;
    savefile << p1.location[0] << endl;
    savefile << p1.location[1] << endl;
    savefile << p1.money << endl;
    savefile << p1.backpack.size() << endl;    // input backpack size for later loading
    vector<item>::iterator itr;
    for (itr = p1.backpack.begin(); itr != p1.backpack.end(); itr++) {  //loop through the backpack and input each item's name and quantity into the text file
        savefile << itr->name << endl;
        savefile << itr->quantity << endl;
    }
    savefile << difficulty << endl;
    cout << "Save successful!" << endl;
}

// For loading the game if the player has save data
bool load_game(player &p1){
  
  ifstream loadfile("save.txt");      //open save.txt
  if (loadfile.is_open()){						//check if it can open
  		string str_stat, str_stat1;			
			int backpack_size;
    
    	getline(loadfile, str_stat);		//read each line of the text file
    	p1.name = str_stat;							//and assign it to the variable accordingly
    	getline(loadfile, str_stat);
    	p1.weapon = str_stat;
    	getline(loadfile, str_stat);
    	p1.armor = str_stat;
    
    	getline(loadfile, str_stat);
    	p1.health = stoi(str_stat);
    	getline(loadfile, str_stat);
    	p1.atk = stoi(str_stat);
    	getline(loadfile, str_stat);
    	p1.def = stoi(str_stat);
    	getline(loadfile, str_stat);
    	p1.location[0] = stoi(str_stat);
    	getline(loadfile, str_stat);
    	p1.location[1] = stoi(str_stat);
    	getline(loadfile, str_stat);
    	p1.money = stoi(str_stat);
    
    	getline(loadfile, str_stat);				//read the backpack size for the for loop
    	backpack_size = stoi(str_stat);			
    	for (int i = 0; i < backpack_size; i++) {			//each time read 2 lines, one for name and one for quantity of item
        	getline(loadfile, str_stat);							
        	getline(loadfile, str_stat1);
          item a(str_stat, stoi(str_stat1));				//create an item using struct for putting the item back to backpack
          p1.backpack.push_back(a);									//put the item into backpack vector
     	}
	getline(loadfile, str_stat);
    	difficulty = stoi(str_stat);
	return true;
  }
  else
    	cout << "There is no save file!" << endl;   //if no save file, output warning
    	return false;
  
}

// Clear the screen so that the screen will not be to messy 
void clearScreen()
{
    int n;
    for (n = 0; n < 10; n++)
      printf( "\n\n\n\n\n\n\n\n\n\n" );     //print empty lines to clear the screen
}

// For printing the status of player when needed
void print_player_stat(player &p1){
    cout << endl;
    cout << "--Your status-- " << endl;  
    cout << "Health: " << p1.health << endl;
    cout << "Attack: " << p1.atk << endl;
    cout << "Defense: " << p1.def << endl;
    cout << "Money: " << p1.money << endl;
    cout << "--Equipment--" << endl; 
    cout << "Weapon: " << p1.weapon << endl;
    cout << "Armor: " << p1.armor << endl;
    cout << "Backpack Items: " << endl;
    
    if (p1.backpack.size() == 0)
        cout << "You don't have any item!" << endl;   
    else{
  	    cout << "--Backpack Items-- " << endl;
  	    for (int i = 0; i < p1.backpack.size(); i++)    //loop whole backpack vector and print out all items
    	    cout << i << ". " << p1.backpack[i].name << "  " << p1.backpack[i].quantity << endl;
    }
    cout << "=======================================================" << endl;
    
    return;
}

// For calling random enemy encounter event
void random_enemy(player &p1){
    int probability;
    switch (p1.location[0])
    {
        case 1:
            probability = rand() % 100 + 1; // generate a number in the range 1 - 100
            if (probability <= 30) // if the number is lower or equal to 30 (1 - 30) will battle slime
                battle(Slime, p1);
            else if (probability > 30 and probability <= 60) // if the number is between 30 - 60, battle goblin
                battle (Goblin, p1);
            else if (probability > 60 and probability <= 70)// if the number is between 60 - 70, battle Mio (rare enemy)
                battle (Mio, p1);
            else if (probability > 70) // if the number is higher than 70, no encounters
                main_menu(p1);
            break; 
        
        case 2:
            probability = rand() % 100 + 1;
            if (probability <= 30)
            	battle(Lizard, p1);
            else if (probability > 30 and probability <= 60)
                battle (Cactus, p1);
            else if (probability > 60 and probability <= 70)
                battle (Pekora, p1);
            else if (probability > 70)
                main_menu(p1);
            break;
            
        case 3:
            probability = rand() % 100 + 1;
            if (probability <= 30)
            	battle(Executioner, p1);
            else if (probability > 30 and probability <= 60)
                battle (Solstice, p1);
            else if (probability > 60 and probability <= 70)
                battle (Strangler, p1);
            else if (probability > 70)
                main_menu(p1);
            break;
    }
}

// Battle system
void battle(enemy e, player &p1){
    bool player_dead = false;
    bool enemy_dead = false;
    int money_drop = e.money * (rand() % 100 + 1) / 100;  
    int choice = 0;
    int dmg = 0;
    int original_health = e.health;
  
  	cout << "=======================================================" << endl;
    cout << "Enemy Encounter!!!" << endl;
  	if (e.name == "Mutant" or e.name == "Dragon" or e.name == "Calliope")    //check if the player is battling with boss
        cout << "...Good Luck." << endl;																		// if yes, print statement
    while ((not enemy_dead) and (not player_dead)){    											//when both of them is alive
            
        //=======show enemy name===========                    
        cout << e.name << endl;
        
        // easter egg: only the slime has its own "image" using ascii 
        if (e.name == "Slime") {
            cout << "             ░░░░░░░░░░                " << endl;
            cout << "          ░░░░        ░░░░░░           " << endl;
            cout << "        ░░                  ░░         " << endl;
            cout << "      ░░                    ░░░░       " << endl;
            cout << "    ░░                      ░░░░░░     " << endl;
            cout << "    ░░                        ░░░░     " << endl;
            cout << "  ░░                ░░    ░░  ░░░░░░   " << endl;
            cout << "  ░░                ██░░  ██    ░░░░   " << endl;
            cout << "  ░░                ██░░  ██    ░░░░   " << endl;
            cout << "  ░░            ░░            ░░░░░░   " << endl;
            cout << "  ░░░░░░                      ░░░░░░   " << endl;
            cout << "    ░░░░░░                  ░░░░░░     " << endl;
            cout << "         ░░░░░░░░░░░░░░░░░░░░░░        " << endl;
        }
        
        //print status of enemy and player
        cout << "Health: " << e.health << endl;
        cout << "Attack: " << e.atk << endl;
        cout << "Defense: " << e.def << endl;
        cout << endl;
        print_player_stat(p1);
        
        // print actions for player to choose
        cout << "1. Attack" << endl;
        cout << "2. Block" << endl;
        cout << "3. Use item" << endl;
        cout << ">> ";
        cin >> choice;
        cout << "=======================================================" << endl;
        
        //==========action execute============
        int atk_fluc = rand() % 10 + 1;
        switch (choice){
            case 1:{
                if (atk_fluc >= 9) {
                    cout << "Critical!" << endl;
                    dmg = p1.atk + atk_fluc;
                }
                else{
                    int add_minus = rand() % 10 + 1;             //damage fluctuation so that it looks more similar to normal rpg game
          	        if (add_minus > 4)           								//some probabililty setting
            	        dmg = (p1.atk + atk_fluc - e.def);            
           	        else 
            	        dmg = (p1.atk - atk_fluc - e.def);
                }
                if (dmg < 0)																		//Prevent negative damage due to fluctuation formulas
                    dmg = 0;
              
                e.health -= dmg;
                cout << e.name << " -" << dmg << endl; 					//output damage by player to monster and damage by monster to player
                if (e.health > 0){
                    p1.health -= e.atk;
                    cout << "You -" << e.atk << endl;
                }
              
              	//===remove buff====
                if (p1.weapon == "Wooden Sword")								//remove the buff as most of the buffs only last 1 turn									
                    p1.atk = data_set[difficulty][1] + 5;				//Method:	check the weapon of player and add its atk to the initial stat of player								 
                else if (p1.weapon == "Dagger")
                    p1.atk = data_set[difficulty][1] + 10;
                else if (p1.weapon == "Hammer")
                    p1.atk = data_set[difficulty][1] + 25;
                else if (p1.weapon == "")
                    p1.atk = data_set[difficulty][1];
              
              	//=======restore dragon breathe===========
                if (use_dragon_breathe)													//since dragon breathe lasts forever
                    p1.atk *= 2;																//so after resetting the buff we need to multiply the atk again
              
                break;
            }
            case 2:{
                int add_minus = rand() % 10 + 1;								//block calculation
                if (add_minus < 4)
           	        dmg = (e.atk + atk_fluc - p1.def * 1.2);		//block formula
                else 
          	        dmg = (e.atk - atk_fluc - p1.def * 1.2);
                if (dmg < 0)
                    dmg = 0;
                     	
                cout << "You blocked." << endl;									//print the dmg after blocking
                p1.health -= dmg;
                cout << "You -" << dmg << endl;     
              
              	//===remove buff====													//same for defensive items
                if (p1.armor == "T-shirts")
                    p1.def = data_set[difficulty][2] + 5;
                else if (p1.armor == "Bronze armor")
                    p1.def = data_set[difficulty][2] + 10;
                else if (p1.armor == "Iron armor")
                    p1.def = data_set[difficulty][2] + 25;
                else if (p1.armor == "")
                    p1.def = data_set[difficulty][2];
        	    	break;
            } 
            case 3:{
                int choice = 0;
                for (int i = 0; i < p1.backpack.size(); i++)      //print all backpack item
                    cout << i << ". " << p1.backpack[i].name << "  " << p1.backpack[i].quantity << endl;			
                do {
                    cout << ">> ";
                    cin >> choice;																	    //read which item to use
                } while (choice > p1.backpack.size() and choice < 0);		//if choice invalid

                if (p1.backpack[choice].name == "Health Potion"){				//use item accordingly
                    use_item("Health Potion", p1);											
                    break;
                }
                else if (p1.backpack[choice].name == "Defense Potion"){
                    use_item("Defense Potion", p1);
                    break;
                }
                else if (p1.backpack[choice].name == "Attack Potion"){
                    use_item("Attack Potion", p1);
                    break;
                }
            }
        }
        
        //================Boss Speacial ability====================
        if (e.name == "Mutant") {        //check boss name for activating boss ability
            e.health += 1;							//Mutant skill: trade health with player
        	p1.health -= 1;									
            cout << "Mutant skills activated: EQUIVALENT EXCHANGE - Hemophagia" << endl;
            cout << "Your health -1 Mutant health +1" << endl;
        }		
        else if (e.name == "Dragon") {			//Dragon skill: when dragon health < 30 it will regenerate health by its damage
      	    if (dmg < 4 and e.health <= 30){
                cout << "ఠ Dragon Strikes Back ఠ" << endl;
                e.health += dmg;
                cout << "Dragon's Health Regenerated" << endl;
            }
        }
      
        //=====================Death Check=========================
        // player
        if (p1.health <= 0) {													//check wether player is dead
            p1.player_dead = true;
            cout << "You are dead．．．" << endl;
      	    cout << "這雖然是遊戲，但可不是鬧著玩 - これは、ゲームであっても遊びではない。" << endl;
        } 
                       
        // Normal enemy
        if (e.health <= 0){													//if enemy is dead
            enemy_dead = true;
            cout << "You Win!" << endl;							//print drop and add drop money to player struct
            cout << "Drop : $" <<  money_drop << endl;
            p1.money += money_drop;
        
            // random rate of normal enemy drop item
            if (e.name != "Mutant" and e.name != "Dragon" and e.name != "Calliope"){				//for enemy except boss
                bool item_exist = false;
                int i = (rand() % 100 + 1 );																								//chance of the drop rate of normal enemy 
                if (i > 30 and e.drop_item != "") {
            	    cout << "Drop : " << e.drop_item << endl;																	//if drop then print drop item
            	    // checks if the item is in the backpack already
                    vector<item>::iterator itr;
                    for (itr = p1.backpack.begin(); itr != p1.backpack.end(); itr++){  //check wether the item is in backpack originally
                        if (itr->name == e.drop_item){  
                            item_exist = true;
              	            break;
                        }
          		    }
          		    
          		    if (item_exist)  //if yes
              		    itr->quantity += 1;  //increase the quantity of the item by 1
          		    else {					//if no
              		    item i(e.drop_item, 1);
            		    p1.backpack.push_back(i);	//add a new item to backpack
          		    }
                }
                // restore enemy's health
                e.health = original_health;
          	    main_menu(p1);
            }
            else if (e.name == "Mutant"){
                cout << "Drop: " << e.drop_item << endl;
            	// checks if the item is in the backpack already
              	bool item_exist = false;
                vector<item>::iterator itr;
                for (itr = p1.backpack.begin(); itr != p1.backpack.end(); itr++){  //check wether the item is in backpack originally
                    if (itr->name == e.drop_item){
                        item_exist = true;
                        break;
                    }
          		}
          		    
          		if (item_exist)  //if yes
              		itr->quantity += 1;  //increase the quantity of the item by 1
          		else {					//if no
              		item i(e.drop_item, 1);
            		p1.backpack.push_back(i);	//add a new item to backpack
          		}
            }
            else if (e.name == "Dragon"){							//same as "Mutant"
                item i(e.drop_item, 1);
                p1.backpack.push_back(i);
                Desert_boss_defeated = true;
                cout << "Drop: Dragon Breathe" << endl;
            }
            else if (e.name == "Calliope"){					//same as "Mutant"
                item i(e.drop_item, 1);
                p1.backpack.push_back(i);
                Final_boss_defeated = true;
                cout << "Drop: Ricky" << endl;
            }
      	}
    }
}
  
// To start the game by choosing difficulty  
int opening(){
  	// to store the chooses of player
    char confirm_choose = 'N';
  	int game_init;
  	// printing info about our project
  	cout << "-------------ENGG1340 Course Project--------------" << endl;
  	cout << "Team members: " << endl;
  	cout << "UID: ----------, Name: Leung Ming Ting" << endl;
  	cout << "UID: ----------, Name: Lo Tsz Yin" << endl;
  	cout << "--------------------Normal RPG--------------------" << endl;
  	cout << endl;
  	
  	cout << "1. New Game" << endl;
  	cout << "2. Load Game" << endl;
  	cin >> game_init;
  	if (game_init == 1) {
        cout << "Please choose a difficulty" << endl;
        cout << "1. Easy" << endl;
        cout << "2. Normal" << endl;
        cout << "3. Hard" << endl;
        do{
            cout << "choose a difficulty" << endl;
            cout << ">> ";
            cin >> difficulty;
            cout << "Are you sure? (Y/N)" << endl;
            cin >> confirm_choose;
        } while (confirm_choose == 'N');
        return 1;  // retrun 1 if choosing start game
    }
  	else if (game_init == 2)
      	    return 2; // retrun 2 if choosing laod game
  	else{
      	    cout << "Please input properly!" << endl;
      	    opening();
  	}
}

// initialize player data based on difficulty chosed 
void create_character(player &p1){
  	// entering name
    cout << "King: Welcome, I am the king of this country." << endl;
    cout << "King: May I ask what is your name?" << endl;
    cout << ">> ";
    string name;
    cin >> name;
    p1.name = name;
    p1.weapon = "";
    p1.armor = "";
    
  	// story
  	cout << "King: Nice to meet you, " << p1.name << "." << endl;
  	cout << "King: Now, the world is controlled by the Evil Lord" << endl;
  	cout << "King: All of the creatures become her slaves." << endl;
  	cout << "King: We have already used up all of our resources to confront the Evil Lord." << endl;
  	cout << "King: But what we have been done is worthless." << endl;
  	cout << "King: You are our only hope!" << endl;
  	cout << "King: Please save the world." << endl;
  	cout << p1.name << ": K" << endl;
  	
  	// initialize player's stat
    switch (difficulty){
        case 1:{
            p1.health = data_set[0][0];
            p1.atk = data_set[0][1];
            p1.def = data_set[0][2];
            p1.money = data_set[0][3];
            break;
        }
        case 2:{
            p1.health = data_set[1][0];
            p1.atk = data_set[1][1];
            p1.def = data_set[1][2];
            p1.money = data_set[1][3];
            break;
        }
        case 3:{
            p1.health = data_set[2][0];
            p1.atk = data_set[2][1];
            p1.def = data_set[2][2];
            p1.money = data_set[2][3];
            break;
  	    }
    }
    // initialize player's location in the world map
    p1.location[0] = 0;
    p1.location[1] = 0;
    // for later use, as using 0 as start is better for later codes
    difficulty -= 1;
}

// for using items 
void use_item(string item, player &p1){
    if (item == "Health Potion"){                   // checks the name of item and do respective actions
        for (int i = 0; i < p1.backpack.size(); ++i){
            if (item == p1.backpack[i].name and p1.backpack[i].quantity != 0){
              	p1.health = data_set[difficulty][0];
        	    	p1.backpack[i].quantity -= 1;
            }
          	else 
              	cout << "You don't have this item!" << endl;
          	if (p1.backpack[i].quantity == 0)
              	p1.backpack.erase(p1.backpack.begin() + i);
        }
    }
    else if (item == "Attack Potion"){
        for (int i = 0; i < p1.backpack.size(); ++i){
            if (item == p1.backpack[i].name and p1.backpack[i].quantity != 0){
      					p1.atk += 20;
        	    	p1.backpack[i].quantity -= 1; 
            }
          	else 
              	cout  << "You don't have this item!" << endl;
          	if (p1.backpack[i].quantity == 0)
              	p1.backpack.erase(p1.backpack.begin() + i);
        }

	    
    }
    else if (item == "Defense Potion"){
        p1.def += 20;
        for (int i = 0; i < p1.backpack.size(); ++i){
            if (item == p1.backpack[i].name and p1.backpack[i].quantity != 0){
              	p1.def += 20;
        	    	p1.backpack[i].quantity -= 1;
            }
          	else 
              	cout  << "You don't have this item!" << endl;
          	if (p1.backpack[i].quantity == 0)
              	p1.backpack.erase(p1.backpack.begin() + i);
        }
    }
}

// menu for user to choose what item in the backpack to use
void item_menu(player &p1){
    int choice = 0;
    if (p1.backpack.size() == 0){           //check wether backpack is empty
        cout << "You don't have any item!" << endl;
        return;
    }
    
    int i = 0;
    for (i = 0; i < p1.backpack.size(); i++)		//print all items in backpack
        cout << i << ". " << p1.backpack[i].name << "  " << p1.backpack[i].quantity << endl;
    cout << i << ". " << "Return" << endl;			//last option is exit item menu
    
    do {
    	cout << ">> ";
  		cin >> choice;
    } while (choice > p1.backpack.size() and choice < 0);  //loop for cin choice
  
    if (choice == i)						//use item accordingly
        return;
    else if (p1.backpack[choice].name == "Health Potion"){
        use_item("Health Potion", p1);
  	    return;
    }
    else if (p1.backpack[choice].name == "Defense Potion"){
        use_item("Defense Potion", p1);
  	    return;
    }
    else if (p1.backpack[choice].name == "Attack Potion"){
        use_item("Attack Potion", p1);
        return;
    }
    else if (p1.backpack[choice].name == "Dragon Breathe"){
        p1.atk *= 2;
        p1.backpack.erase(p1.backpack.begin() + choice);     //clear the item after using since it is unique item
      	use_dragon_breathe = true;													//for resetting buff (aforementioned
        return;
    }
}

// The main menu of the game
void main_menu(player &p1){
    int choice = 0;
    switch (p1.location[0]){
        //==================Kingdom area==================== 
        case 0:
        		cout << "=======================================================" << endl;
            cout << "Currrent location: Kingdom" << endl;
            cout << "1. Shop" << endl;
            cout << "2. Adventure" << endl;
            cout << "3. Use Item" << endl;
        		cout << "4. Save" << endl;
            cout << ">> ";
            cin >> choice;
            if (choice == 1)           //read choice
                shop(p1);
            else if (choice == 2)
                p1.location[0] = 1;
            else if (choice == 3)
                item_menu(p1);
        		else if (choice == 4)
              	save_game(p1);
            break;
      
    		//==================Forest area====================  
        case 1:
        	cout << "=======================================================" << endl;
            cout << "Current location: Forest " << "Steps: " << p1.location[1] << " out of 15" << endl;
            cout << "1. Move Forward" << endl;
            cout << "2. Move Backward" << endl;
            cout << "3. Use Item" << endl;
        		cout << "4. Save" << endl;
            cout << ">> ";
            cin >> choice;
            if (choice == 1){
                if (p1.location[1] == 14 and Forest_boss_defeated == false){
                    char ready;
                  	cout << "=======================================================" << endl;
                    cout << "Danger Ahead!!" << endl;
                    cout << "Hints: Mutant can heal itself every turn" << endl;
                    cout << "!!!! There is no escape once entering !!!!" << endl;
                    cout << "Are you ready?  (Y/N)" << endl;

                    cin >> ready;
                    if (ready != 'N')
                        main_menu(p1);
                    else{
                        p1.location[0] += 1;    //because boss battle, so move player to next area 
                        p1.location[1] = 0;
                        battle (Mutant, p1);    
                    }
                }
                else if (p1.location[1] == 15){ 
                    p1.location[0] += 1;       //for second time stepping on the boss grid
                    p1.location[1] = 0;				// as you won't encounter boss again
                }
                else{
                    p1.location[1] += 1;			//for normal grid
                    random_enemy(p1);					//call for random enemy
                }
            }
            else if (choice == 2){
                if (p1.location[1] == 0)			//if at 0 step, move player to the previous area
                    p1.location[0] -= 1;
                else if (p1.location[1] != 0) //if player is not at 0 step
                    p1.location[1] -= 1;
                main_menu(p1);
            }
            else if (choice == 3)
                item_menu(p1);							// call item menu
        		else if (choice == 4)
              	save_game(p1);							//call save game

            break;
            
				//==================Desert area=====================  //same as above
        case 2:
        	cout << "=======================================================" << endl;
            cout << "Current location: Desert " << "Steps: " << p1.location[1] << " out of 10" << endl;
            cout << "1. Move Forward" << endl;
            cout << "2. Move Backward" << endl;
            cout << "3. Use Item" << endl;
        		cout << "4. Save" << endl;
            cout << ">> ";
            cin >> choice;
      
        if (choice == 1){
            if (p1.location[1] == 9 and Desert_boss_defeated == false){
                char ready;
              	cout << "=======================================================" << endl;
                cout << "Danger Ahead!!" << endl;
                cout << "Hints: weak attacks (<4) cannot affect the dragon when its HP is lower than 30" << endl;
                cout << "!!!! There is no escape once entering !!!!" << endl;
                cout << "Are you ready?  (Y/N)" << endl;
          
                cin >> ready;
                if (ready == 'N')
          	        main_menu(p1);
                else{ 
                    p1.location[0] += 1;
                    p1.location[1] = 0;
                    battle (Dragon, p1);
                }
            }
            else if (p1.location[1] == 10){
                p1.location[0] += 1; 
                p1.location[1] = 0;
            }
            else{
       		    p1.location[1] += 1;
      		    random_enemy(p1);
            }
        }
      
        else if (choice == 2){
            if (p1.location[1] == 0){
                p1.location[0] -= 1;
          			p1.location[1] = 15;
            }
            else if (p1.location[1] != 0)
                p1.location[1] -= 1;
            main_menu(p1);
        }
      
        else if (choice == 3)
            item_menu(p1);
        else if (choice == 4)
          	save_game(p1);
      
        break;
  
  	//==================Maojo=====================		//same as above
    case 3:
        cout << "=======================================================" << endl;
        cout << "Current location: Maojo " << "Steps: " << p1.location[1] << " out of 5" << endl;
        cout << "1. Move Forward" << endl;
        cout << "2. Move Backward" << endl;
        cout << "3. Use Item" << endl;
        cout << "4. Save" << endl;
        cout << ">> ";
        cin >> choice;
      
        if (choice == 1){
            if (p1.location[1] == 4 and Final_boss_defeated == false){
                char ready;
              	cout << "=======================================================" << endl;
                cout << "Danger Ahead!!" << endl;
                cout << "Finaly Boss Fight Warning!!!" << endl;
                cout << "Hints: You can only damage Calli if you perform CRITICAL Attack" << endl;
                cout << "Are you sure to proceed?  (Y/N)" << endl;
          
                cin >> ready;
                if (ready != 'Y')
          	        main_menu(p1);
                else{       
                    p1.location[1] += 1;
                    battle (Calliope, p1);
		}
            }
            else{
       		    p1.location[1] += 1;
      		    random_enemy(p1);
            }
        }
      
        else if (choice == 2){
            if (p1.location[1] == 0) {
                p1.location[0] -= 1;
         	 	p1.location[1] = 10;
            }
            else if (p1.location[1] != 0)
                p1.location[1] -= 1;
            main_menu(p1);
        }
      
        else if (choice == 3)
            item_menu(p1);
        else if (choice == 4)
          	save_game(p1);
      
        break;
            
    }	
}

// Shop menu in Kingdom for players to buy items
void shop(player &p1){
    int shop_choice;
    cout << "What do you want, traveller?" << endl;
    cout << "Potion:" << endl;
    cout << "1. Health Potion | Restore to full health | $25" << endl;
    cout << "2. Attack potion | ATK +20 (One turn) | $25" << endl;
    cout << "3. Defense potion | DEF + 20 (One turn) | $25" << endl;
    cout << "Weapon:" << endl;
    cout << "4. Wooden Sword | ATK +5 | $30" << endl;
    cout << "5. Dagger | ATK +10 | $60" << endl;
    cout << "6. Hammer | ATK +25 | $100" << endl;
    cout << "Armor:" << endl;
    cout << "7. T-shirt | DEF +5 | $30" << endl;
    cout << "8. Bronze Armor | DEF +10 | $60" << endl;
    cout << "9. Iron Armor | DEF +25 | $100" << endl;
    cout << "10. Leave Shop" << endl;
    cout << endl;
    print_player_stat(p1);
    cout << "Please enter the designated number of the item you want." << endl;
    cout << ">> ";
  
    cin >> shop_choice;
    vector<item>::iterator itr;
    bool item_exist = false;
    switch (shop_choice){
      
    //For potion
        case 1:
        		if (p1.money < 25) {
              	cout << "You don't have enough money." << endl;
              	cout << "=======================================================" << endl;
              	shop(p1);
              	break;
            }
            for (itr = p1.backpack.begin(); itr != p1.backpack.end(); itr++){ //check wether the item is in backpack originally
                if (itr->name == "Health Potion"){  
                    item_exist = true;
                    break;
      	        }
            }
            if (item_exist){  //if yes
                itr->quantity += 1;  //increase the quantity of the item by 1
                p1.money -= 25;     //deduct money
                shop(p1);
              	break;
            }
            else {					//if no
              item i("Health Potion", 1);
        	    p1.backpack.push_back(i);	//add a new item to backpack
        	    p1.money -= 25;	//deduct money
        	    cout << "You bought 1 Health Potion." << endl;
              cout << "=======================================================" << endl;
        	    shop(p1);
            	break;
            }
            break;
        case 2:
						if (p1.money < 25) {
              	cout << "You don't have enough money." << endl;
              	cout << "=======================================================" << endl;
              	shop(p1);
              	break;
            }
            for (itr = p1.backpack.begin(); itr != p1.backpack.end(); itr++){ //check wether the item is in backpack originally
                if (itr->name == "Attack Potion"){
                    item_exist = true;
                    break;
      	        }
            }
            if (item_exist){ 	//if yes
                itr->quantity += 1;	//increase the quantity of the item by 1
                p1.money -= 35;	//deduct money
                shop(p1);
              	break;
            }
            else {						//if no
                item i("Attack Potion", 1);
        	    p1.backpack.push_back(i);	//add a new item to backpack
        	    p1.money -= 35;	//deduct money
        	    cout << "You bought 1 Attack Potion." << endl;
              cout << "=======================================================" << endl;
        	    shop(p1);
              break;
            }
            break;
        case 3:
        		if (p1.money < 25) {
              	cout << "You don't have enough money." << endl;
              	cout << "=======================================================" << endl;
              	shop(p1);
              	break;
            }
            for (itr = p1.backpack.begin(); itr != p1.backpack.end(); itr++){
                if (itr->name == "Defense Potion"){
                    item_exist = true;
        	        break;
      	        }
            }
            if (item_exist){	//if yes
                itr->quantity += 1;	//increase the quantity of the item by 1
                p1.money -= 35;	//deduct money
                shop(p1);
              	break;
            }
            else {						//if no
                item i("Defense Potion", 1);
                p1.backpack.push_back(i);	//add a new item to backpack
                p1.money -= 35;	//deduct money
                cout << "You bought 1 Defense Potion." << endl;
              	cout << "=======================================================" << endl;
                shop(p1);
              	break;
            }
            break;
    		//For weapon  
        case 4:
        		if (p1.money < 30) {
              	cout << "You don't have enough money." << endl;
              	cout << "=======================================================" << endl;
              	shop(p1);
             		break;
            }
            if (p1.weapon == "Wooden Sword"){ //if the player has equipped the same weapon
                cout << "You have equipped this weapon." << endl;
      	        shop(p1);	//call the shop again
              	break;
            }
            else if (p1.weapon == "Dagger" or p1.weapon == "Dragon Breathe" or p1.weapon == "Hammer"){ 	//if the player equipped better weapon  
                cout << "You have equipped better weapon.";
                shop(p1);			
              	break;   
            }
            else{
                p1.weapon = "Wooden Sword";   //replace the weapon
      	        p1.atk = data_set[difficulty][1] + 5;  //refresh the data
                p1.money -= 30;				//deduct money
                cout << "You bought a Wooden Sword." << endl;
              	cout << "=======================================================" << endl;
                shop(p1);
              	break;
            }
            break;
        case 5:
        		if (p1.money < 60) {
              	cout << "You don't have enough money." << endl;
              	cout << "=======================================================" << endl;
              	shop(p1);
              	break;
            }
            if (p1.weapon == "Dagger"){
                cout << "You have equipped this weapon." << endl;
      	        shop(p1);
              	break;
            }
            else if (p1.weapon == "Dragon Breathe" or p1.weapon == "Hammer"){  
                cout << "You have equipped better weapon.";
                shop(p1);
              	break;
            }
            else{
                p1.weapon = "Dagger";
      	        p1.atk = data_set[difficulty][1] + 10;
                p1.money -= 60; 
                cout << "You bought a Dagger." << endl;
              	cout << "=======================================================" << endl;
                shop(p1);
              	break;
            }
            break;
        case 6:
        		if (p1.money < 100) {
              	cout << "You don't have enough money." << endl;
              	cout << "=======================================================" << endl;
              	shop(p1);
              	break;
            }
            if (p1.weapon == "Hammer"){
                cout << "You have equipped this weapon." << endl;
      	        shop(p1);
              	break;
            }
            else if (p1.weapon == "Dragon Breathe"){
                cout << "You have equipped better weapon.";
                shop(p1);
              	break;
            }
            else{
                p1.weapon = "Hammer";
              	p1.atk = data_set[difficulty][1] + 25;
                p1.money -= 100;
                cout << "You bought a Hammer." << endl;
              	cout << "=======================================================" << endl;
                shop(p1);
              	break;
            }
            break;
    		//For armour
        case 7:
        		if (p1.money < 30) {
              	cout << "You don't have enough money." << endl;
              	cout << "=======================================================" << endl;
              	shop(p1);
                break;
            }
            if (p1.weapon == "T-Shirt"){
                cout << "You have equipped this armour." << endl;
      	        shop(p1);
              	break;
            }
            else if (p1.def > data_set[difficulty][2] + 5){
                cout << "You have equipped better armour.";
                shop(p1);
              	break;
            }
            else{
                p1.weapon = "T-Shirt";
              	p1.def = data_set[difficulty][2] + 5;
              	p1.money -= 30;
                cout << "You bought a T-Shirt." << endl;
              	cout << "=======================================================" << endl;
              	shop(p1);
              	break;
            }
            break;
        case 8:
        		if (p1.money < 60) {
              	cout << "You don't have enough money." << endl;
              	cout << "=======================================================" << endl;
              	shop(p1);
              	break;
            }
            if (p1.weapon == "Bronze armor"){
                cout << "You have equipped this armor" << endl;
              	shop(p1);
              	break;
            }
            else if (p1.def > data_set[difficulty][2] + 10){
                cout << "You have equipped better weapon.";
                shop(p1);
              	break;
            }
            else{
                p1.weapon = "Bronze armor";
              	p1.def = data_set[difficulty][2] + 10;
              	p1.money -= 60;
                cout << "You bought a Bronze armor." << endl;
              	cout << "=======================================================" << endl;
              	shop(p1);
              	break;
            }
            break;
        case 9:
        		if (p1.money < 100) {
              	cout << "You don't have enough money." << endl;
              	cout << "=======================================================" << endl;
              	shop(p1);
              	break;
            }
            if (p1.weapon == "Iron Armor"){
                cout << "You have equipped this armor." << endl;
      	        shop(p1);
              	break;
            }
            else if (p1.def > data_set[difficulty][2] + 25){
                cout << "You have equipped better weapon.";
                shop(p1);
              	break;
            }
            else{
                p1.weapon = "Iron Armor";
              	p1.def = data_set[difficulty][2] + 25;
              	p1.money -= 100;
                cout << "You bought a Iron Armor." << endl;
              	cout << "=======================================================" << endl;
              	shop(p1);
              	break;
            }
            break;
        case 10:
        		clearScreen();
            main_menu(p1);
            break;
	}
}
