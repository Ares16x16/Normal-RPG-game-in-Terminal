#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include "RPG_struct.h"

using namespace std;

int main(){

    player p1;   // declare an User object for the pleyer
	
    int game_start = 0;
    while (game_start != 1 and game_start != 2){
        game_start = opening();
      	if (game_start == 1)         //new game
      	    create_character(p1);
      	else if (game_start == 2){		//load game
      	    if (load_game(p1))
                cout << "Load successful!" << endl;
            else
                cout << "Load unsuccessful, please try again." << endl;
	}
    }

    
    do{     // looping the core part of the game
  	    main_menu(p1);
  	    if (p1.location[0] == 3 and p1.location[1] == 5)  //after final boss battle, check wether the player have killed the boss
  	        break;																				//if yes, break the loop and head to end game
  	} while (p1.player_dead != true);

  	if (p1.player_dead)																	// if player dead, close the game
  	    return 0 ;

  	clearScreen();    //clear the screen
		
  	//conversation when win game
  	cout << "Calliope: You are strong....." << endl;
  	cout << "Calliope: I lose..." << endl;
  	cout << "=======================================================" << endl;
  	cout << "King: Thank you " << p1.name << ", you are our saviour!" << endl;
    	cout << p1.name << ": If Calliope returns I will be more than happy to save this world." << endl;
    	cout << "Thank you for playing!!" << endl;
  	cout << "ENGG1340 Course Project" << endl;
}
