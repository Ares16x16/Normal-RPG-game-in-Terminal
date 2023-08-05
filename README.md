# **The project for ENGG 1340 2020-2021 Sem2, by Benny Leung and Edward Lo**:+1:

Team members:

>UID: ---------- , Name: Leung Ming Ting<br/>
>UID: ---------- , Name: Lo Tsz Yin

Topic: Role-playing Adventure games <br/>
Name of the game: Normal RPG game

We can successfully compile our codes on academy11 server.

## **Game description:**

You are living in a peaceful world. One day, darkness emerges. A guy comes out and says “I’m Calliope, from now on, I’m the lord of the world!”. After that, all of the people become the slaves of Calliope, and they have to fulfill all of his requirements. You do not want to live in this abysmal condition anymore, so you are determined to rescue the world.

In this game, you are role-playing the savior of the world. And what you have to do is kill the final boss, Calliope. First, you will begin in the Kingdom area, you can choose to purchase items in shop or adventure. In your adventure, you can move forward to reach the next area. But be careful, enemies may pop up when you move every single step! 
There are a total of 4 areas: Kingdom, Forest, Desert, Maojo. In each area (except Kingdom), you will meet various kinds of monsters. Each of them have different drops and stats. Before moving on to the next area, you have to beat the guardian in order to gain access to the next area. Each of the guardians or bosses possess their own ability, which means that you may need a little bit of technique to defeat them. If you do not visit the place for a long time, the bosses may respawn.

For the battle system, you can opt to attack, block or use items during the battle stage. Attack and block count as one turn movement while using items does not, which means that you can use items infinitely in one turn to help you prevail (i.e. you can drink 20 attack potions in one turn to heavily strike on the boss and give it a lethal hit!). Blocking will reduce the damage you take. Please be aware that some monsters may drop special items, which may become your left-right hand in the future.

You can only save your game outside battle and load your game when launching the game.

Every monster and player have their own stats(value of health etc.). Player’s stats includes your name, weapon equipped, armor equipped, health, attack, defense, money, your location and the items in your backpack, whereas monster’s stats includes their name, health, attack, defense, money drop and item drop. One of the tips to win the game is that you can observe the stats of the monster and compare it to your stats and indicate what to do next. Doing some calculation is the key to winning.

## **Compiling the codes**
In the terminal, enter "make RPG" with all 4 files (header file, 2 cpp files and the makefile) at the same directory. The terminal will have to be accessing the same directory too. 
After executing the "make RPG" line, there will be 2 .o files and a "RPG" file. Enter "./RPG" in the terminal to start the game. 
## **Game guides:**
1. After entering the games, choose “New game” or “Load game”.
2. If you choose “Load game”, you can continue your journey to save the world.
3. If you choose “New game”, select your favourable difficulty and input the data according to the game instructions printed on the screen.
4. Once you have entered the main menu (i.e. Location = Kingdom), you will have 4 options to choose from: “Shop”, “Adventure”, “Use item” and “save”.
5. You can only purchase items and equipment at shops in the Kingdom..
6. You will move to next area (i.e. Forest) by choosing “Adventure” .
7. You will be able to use items by choosing “Use item”.
8. After choosing adventure, you will move to wild area.
9. You can “Move forward”,  “Move backward” or “Use item” in wild area.
10. If you “Move forward”, you may encounter enemies.
11. “Move backward” will not encounter enemies.
12. If you encounter an enemy, battle begins immediately.
13. During battles, you can “Attack”, “Block” or “Use item”.
14. “Attack” will deal damage to the enemy, and the enemy will also damage you.
15. “Block” will reduce the damage you take.
16. You can use items infinitely many times during battle.
17. After winning the battle, item drop and money drop will be displayed.
18. Item drop is randomized(i.e. Can be no item drop and money drop can be fluctuated.).
19. Repeat this process until you reach the last grid of the area.
20. When you reach the last grid of the area, you will encounter boss fight.
21. Each boss has their own ability.
22. After reaching the last area and beating the last boss, you will become the savior of the world.
23. End game.
  
## **Extra data:** 
1. Area size
   1. Kingdom : 1 grid
   1. Forest: 15 grids
   1. Desert: 10 grids
   1. Maojo: 5 grids
   
2. Monsters information [HP, ATK, DEF, MONEY][Possible DROP]

```
    2.1. Forest
        2.1.1. Slime [15, 5, 1, 5][None] 

        2.1.2. Goblin [25, 15, 5, 7][None] 

        2.1.3. Mio [40, 20, 10, 10][Attack Potion] 

        2.1.4. Mutant (Area Boss) [100, 25, 15, 25][Health Potion] 
            
    2.2. Desert
        2.2.1. Lizard [40, 10, 15, 10][Defense Potion]

        2.2.2. Cactus [35, 50, 5, 10][Attack Potion]

        2.2.3. Pekora [50, 50, 15, 50][Jailed Rabit Leg]

        2.2.4. Dragon (Area Boss) [200, 50, 20, 30][Dragon Breathe]

    3. Maojo
        2.3.1. Executioner [75, 60, 60, 0][None]

        2.3.2. Solstice [80, 60, 60, 0][None]

        2.3.3. Strangler [90, 65, 60, 0][None]

        2.3.4. Calliope (Final Boss) [350, 100, 80, 1000][Ricky]
```
    
## **Game rules:**
1. Do not edit the data stored in the text file “save.txt”.
2. Do not input too fast during the game.
3. Do not input invalid characters(e.g. ^A, ^C etc.).
4. Do not enter a name with space character for the player's name (e.g "David" is ok, but "D avid" is not ok)
5. Follow the instructions printed in the game.
6. Re-open the game if you want to load the game.
7. Read the game guide.
8. Enjoy the game!

## **Game Features:**
1. Varying status for monsters The monsters will have randomly generated stats (health point, atk point and def point). Each area will have monsters of different strengths. This feature corresponds to the 1st requirement, as the varying data of the monster is random.

2. Random encounter of monsters in certain areas The player may encounter monsters in certain areas with random chance. This feature corresponds to the 1st requirement, as the chance of encountering monsters is random.

3. Extendable backpack Player’s backpack will be extended upon beating the first boss, so that players can store more items. This feature corresponds to the 3rd requirement, as the backpack will be an dynamically allocated array, in which the size will be changed later in the game.

4. Save and Load When the player enters a different area (new or old), the game will auto saves. The player is not allowed to save themselves. This corresponds to the 2nd requirement as the player status will be grouped using “struct” in game and in the save file. This also corresponds to the 4th requirement as the saved game data will be outputted as a separate file in the game directory. This corresponds to the 5th requirement as the save data will be outputted as a separate file in the game directory for loading.

## **Code Description**

The game consists of 3 files, *RPG_struct.h*, *RPG_function.cpp*, *RPG_main.cpp*. This corresponds to the 5th code requirement, as the codes of the program is stored in 3 separate files

### 1. *RPG_struct.h*
This header file contains the structure of self-defined objects, namely item, player and enemy. There are also declarations of function names and the input, to be used in RPG_function.cpp. In “player”, the items in the backpack are stored as a vector, which is 0 at the beginning, and expand upon getting new items. This corresponds to the 3rd code requirement, as the use vectors are present in the code. This also corresponds to the 2nd code requirement too, as there are self-defined data structures.

### 2. *RPG_function.cpp*
This cpp file contains all the functions and the preset-data sets that will be used in the game. The data-sets are different initial values for different enemies, as well as stats for players under different difficulty. The functions included in this cpp file are listed below:

  - [x] `void save_game(player &p1)`
  - [x] `void load_game(player &p1)`
  - [x] `void print_player_stat(player &p1)`
  - [x] `void random_enemy(player &p1)`
  - [x] `void battle(enemy e, player &p1)`
  - [x] `int opening()`
  - [x] `void create_character(player &p1)`
  - [x] `void use_item(string item, player &p1)`
  - [x] `void item_menu(player &p1)`
  - [x] `void main_menu(player &p1)`
  - [x] `void shop(player &p1)`
  	<br/>
    
    2.1. 	`void save_game(player &p1)`

      `save_game(player &p1)` will output the values of all items in the player object p1, which are player’s name, atk, def, player’s current location, money, weapon, armor and backpack items as 1 “save.txt” file. The save data does not save if the bosses are defeated or not, as according to the game’s setting, bosses will respawn. This corresponds to the 4th code requirement, as there is file output by the program.

    2.2. 	`void load_game(player &p1)`

    `load_game(player &p1)` will read in “save.txt” line by line, as set the corresponding data to the value in save.txt, for example, the first line of save.txt is the name of the player, then this function will read this line, and change the name of the player to it. This way, the player’s stats (not including if the bosses are defeated or not) can be loaded in again. This corresponds to the 4th code requirement, as there is file input by the program. 

    2.3. 	`void print_player_stat(player &p1)`

    `print_player_stat(player &p1)` will print the stats of the player when needed, for example, at the shop. This way player can see his/her equipments, money as well as backpack items

    2.4. 	`void random_enemy(player &p1)`

    `random_enemy(player &p1)` will generate a random number from 1 to 100, and the game will do different actions based on that number. For example, if the number is 23, the game will call the battle event, with slime as the enemy if the player is in the forest area. This corresponds to the 1st code requirement, as whether there will be battle, or which enemy to fight is decided based on a randomly generated number.

    2.5.	`void battle(enemy e, player &p1)`

    `battle(enemy e, player &p1)` is the battle system, which consists of different parts, like removing potion buff, dealing damage by both enemy and player to each other, as well as checking if either the enemy and player is dead or not. The damage dealt by the player to the monster, although not completely random, has randomness. There is a variable called “atk_fluc” which is used to determine if the attack is a critical hit or not, as well as deciding how much more damage dealt or how much less damage dealt. In the battle, the player can also use items (does not count as a move) when it is their turn.

    2.6. 	`int opening()`

    `<opening()>` is called at the beginning, for the player to decide to start a new game or load an existing save data. If the player decides to start a new game, this function will return 1 and start from the beginning, while choosing load game will return 2, which calls the load_game function introduced above.

    2.7.	`void create_character(player &p1)`

    `<create_character(player p1)>` will initialize the stats of the player based on the difficulty chosen by the player previously, as well as introducing the story of the game

    2.8.	`void use_item(string item, player &p1)`

    `use_item(string item, player &p1)` will check if the item is in the player’s backpack, and will only apply the effects, for example, restore to full health, if the item is present and the quantity of the item is not 0.

    2.9.	`void item_menu(player &p1)`

    `item_menu(player &p1)` will print all items in the player’s backpack, and let the player choose what items he/she want to use, or not using any item. If they choose to use items, function use_item will be called. 

    2.10.	`void main_menu(player &p1)`

    `main_menu(player &p1)` is where the player chooses to shop, adventure, use items or save, as well as move forward or move backward when outside of the kingdom. This function is called in a loop in the main() function until the player reaches the last tile in the last area, or the player dies in game. 

    2.11.	`void shop(player &p1)`

    `shop(player &p1)` will open a shop menu for the player to shop, there are potions, as well as weapons and armors for the player to buy using money. Weapons and armors can add atk and def of the player, while potions gives the player 1 time effect. 

### 3. *RPG_main.cpp*
This cpp file contains the main() function of the program, as well as part of the story after defeating the final boss. There is a do-while loop to loop the main_menu function, and will end once the player is dead, or the player reaches the last step of the last area, so that the game can continue and will not exit accidently in the game.
