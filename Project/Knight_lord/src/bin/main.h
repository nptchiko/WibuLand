#ifndef __MAIN_H__
#define __MAIN_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <direct.h>
#include <time.h>
#include <conio.h>
#include <vector> 


using namespace std;
#define SCREEN_W 72
#define SCREEN_H 24

#define NUM 20

#define Model_b_X_Length 1
#define Model_b_Y_Length 1
#define Model_c_X_Length 4
#define Model_c_Y_Length 2

//SmallBorder_X 4 68
//SmallBorder_Y 10 15

char modelBl[Model_b_Y_Length][Model_b_X_Length] = {{'v'}};

const char *Event_Name[] = {"", "MadBear", "Bandit", "LordLupin", "Elf", "Troll",
                             "Shaman", "Siren_Vajsh" ,"Asclepius", "Merlin", "Bowser" , "MushAttack", "Mushroom", "MushGhost", "Aspirin", "MaidenKiss", "PhoenixDown","Antidote"};
char modelMC[Model_c_Y_Length][Model_c_X_Length] = {{' ','_','_',' '},
                                                  {'|',':','3','|'}};

vector<string> frame2_0 = {
                   "   ~~o     . ",
                   "    _|_    | ", 
                   "   |'v'|   | ",
                   "  /|___|\\ _|_",
                   " //|_|_|\\\\>| ",
                   "   _/ \\_     "} ;
                   vector<string> frame2_1 ={
                   "   ~~o     .  ",
                   "    _|_    |   ", 
                   "   |'v'|   |   ",
                   "  /|___|\\ _|_ ",
                   " //|_|_|\\\\>| ",
                   "    / \\       ",
                   "   /   \\   "} ;
vector<string> frame1  = {
                        "   ~~o .    ",
                        "    _|_ \\   ", 
                        "   |'v'| \\  ",
                        "  /|___|\\_\\_",
                        " //|_|_|\\\\>\\",
                        "   _/ \\_    "} ;
vector<string> frame3 = {
                   "   ~~o         .",
                   "    _|_       / ", 
                   "   |'v'|     /  ",
                   "  /|___|\\  _/_  ",
                   " //|_|_|\\\\>/   ",
                   "   _/ \\_       "} ;
vector<string> frame4 = {
                   "   ~~o            ",
                   "    _|_                 ", 
                   "   |'v'|                ",
                   "  /|___|\\              ",
                   " //|_|_|\\\\>-|---------",
                   "   _/ \\_     "} ;
vector<string> frame10 = { "', ",
                         "  ,",
                         "  ,",};
       
vector<string> frame11 = {   "', ",
                            " ;;",
                            " ;;",
                            "  ,"};
   
vector<string> frame12 = { " ', ",
                        "  ;;",
                        "  ;;",
                        "  ;,",
                        " ;; ",
                        ",'  "};
vector<string> frame13 ={"   ', ",
                        "    ;,",
                        "    ;;",
                        "   ;,;",
                        "  ;;; ",
                        ",''   "};
vector<string> frame14 {
                        "      ', ",
                        "       ;,",
                        "       ;;",
                        "       ;,",
                        ",     ;; ",
                        "  , ,;   "};
vector<string> frame15 = { " "," "," "," ",                 
                     ",     ;;",
                     "  , ,;  "};
 vector<string> sprite_monster = {
      "    ╭─┬──┬─╮",
      "◦╮╭◦├ ╭─┴╮ ┤",
      "╭┴┴─┼ ╰┬ ├ │",
      "│^_^╰┬┼─┬╯ ┤",
      "╰┬┬┬┬┴─┴─┴─╯"};
      vector<string> sprite_NPC= { 
         "        ,\\        ",
         "      __/_\\__     ",
         "     , ((\")\\//  ",
         "      \\_/ \\_|     ",
         "       /___\\|     ",
         "       _/ |_|     "};
         vector<string> sprite_frog  = { 
         "   (o)--(o)    ",
         "  /.______.\\  ",
         "  \\________/  ",
         " ./        \\. ",
         "( .        , ) ",
         " \\ \\_\\//_/ /",
         "  ~~  ~~  ~~   "};
         vector<string> sprite_tiny = {
         "              " ,
         "              " ,
         "              " ,
         "    O" ,
         " --[|]--" ,
         "   / \\ " };
class Attribute;
class Knight;
class Monster;
class NPC;

class Item;
class Potion;
class ItemMangager;

class Object;
class MainCharacter;
class Bullet;
class Knight;

class Game;
#endif //KNIGHT.H