#include "knight.h"


void setcursor(bool visible, DWORD size){
	
    if(size == 0)
		size = 20;	
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(h,&lpCursor);
}
void gotoxy(short x, short y){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD a = {x, y}; SetConsoleCursorPosition(h, a);
}
int main(){
    int x = 4;
    string s = "a" + x;
    cout << s;
}



/*
int main(){
        setcursor(0,0);
          system("cls");
          int speed = 50;
    string frame10[] = { "', ",
                         "  ,",
                         "  ,",};

 string frame11[] = {   "', ",
                            " ;;",
                            " ;;",
                            "  ,"};
   
   string frame12[] = { " ', ",
                        "  ;;",
                        "  ;;",
                        "  ;,",
                        " ;; ",
                        ",'  "};
int i = 0;
    string frame13[] ={"   ', ",
                        "    ;,",
                        "    ;;",
                        "   ;,;",
                        "  ;;; ",
                        ",''   "};
    string frame14[] {
                        "      ', ",
                        "       ;,",
                        "       ;;",
                        "       ;,",
                        ",     ;; ",
                        "  , ,;   "};

string frame15[] = { " "," "," "," ",                 
                     ",     ;;",
                     "  , ,;  "};
    
        
 string frame2[] ={"   ~~o     . ",
                   "    _|_    | ", 
                   "   |'v'|   | ",
                   "  /|___|\\ _|_",
                   " //|_|_|\\\\>| ",
                   "   _/ \\_     "} ;
    string frame1[]  = {"   ~~o .    ",
                        "    _|_ \\   ", 
                        "   |'v'| \\  ",
                        "  /|___|\\_\\_",
                        " //|_|_|\\\\>\\",
                        "   _/ \\_    "} ;
    string frame3[] = {"   ~~o         .",
                   "    _|_       / ", 
                   "   |'v'|     /  ",
                   "  /|___|\\  _/_  ",
                   " //|_|_|\\\\>/    ",
                   "   _/ \\_        "} ;
    string frame4[] = {"   ~~o                  ",
                   "    _|_                 ", 
                   "   |'v'|                ",
                   "  /|___|\\               ",
                   " //|_|_|\\\\>-|---------",
                   "   _/ \\_     "} ;
 while(1){
  
  for(auto x : frame1){     
        cout << x << endl;
    }
    Sleep(speed); system("cls");
    for(auto x : frame2){    
        cout << x << endl;
    }
    Sleep(speed); system("cls");
    for(auto x : frame3){     
        cout << x << endl;
    }
    
    Sleep(speed); system("cls");
    for(auto x : frame4){     
        cout << x << endl;
    }
    
   
  Sleep(speed); system("cls");
  
  
  for(auto x : frame10){     
       gotoxy(40 , i); cout << x;
       i++;
    }
    i= 0;
    Sleep(speed); system("cls");
    for(auto x : frame11){    
       gotoxy(40 , i); cout << x;
       i++;
    }
    i= 0;
    Sleep(speed); system("cls"); 
    for(auto x : frame12){     
       gotoxy(40 , i); cout << x;
       i++;
    }
    i= 0;
    
    Sleep(speed); system("cls");
    for(auto x : frame13){     
       gotoxy(40 , i); cout << x;
       i++;
    }
    i= 0;
    
    Sleep(speed); system("cls");
    for(auto x : frame14){     
       gotoxy(40 , i); cout << x;
       i++;
    }
    i= 0;
    
    Sleep(speed); system("cls");
    for(auto x : frame15){     
       gotoxy(40, i); cout << x;
       i++;
    }
    i= 0;
    Sleep(speed); 
 system("cls"); Sleep(500);
    if(kbhit()) break;
    i=0;
  }
   

}

           (.)-=-(,)
         __(   "   )__
        / _/'-----'\_ \
     ___\\ \\     // //___
    >____)/_\---/_\(____<

    string frame10[] = { "', ",
                         "  ,",
                         "  ,",};
    
    string frame11[4] = {   "', ",
                            " ;;",
                            " ;;",
                            "  ,"};
   
   string frame12[] = { " ', ",
                        "  ;;",
                        "  ;;",
                        "  ;,",
                        " ;; ",
                        ",'  "};

                        " ,' ",
                        ";;  ",
                        ";;  ",
                        ",;  ",
                        " ;; ",
                        "  ',"

    string frame13[8] ={"   ', ",
                        "    ;,",
                        "    ;;",
                        "   ;,;",
                        "  ;;; ",
                        ",''   "};

                        " ,'",
                        ",;  ",
                        ";;  ",
                        ";,;  ",
                        " ;;; ",
                        "   '',"

    string frame14[] {
                        "      ', ",
                        "       ;,",
                        "       ;;",
                        "       ;,",
                        ",     ;; ",
                        "  , ,;   "};

                        " ,'      ",
                        ",;       ",
                        ";;       ",
                        ",;       ",
                        " ;;     ,",
                        "   ;, ,  "


string frame15[] = { " "," "," "," ",                 
                     ",     ;;",
                     "  , ,;  "};

                     " "," "," "," ",
                     
                     ";;     ,",
                     "  ;, ,   "
    
      

" ,"
"; "
", "
  
  
   
  " ,"
  ";;"
  ";;"
  ", "
  
  
"    ,"
"  ;, "
" ;;  "
" ;;  "
"  ;  "
"   ,  "



"    ,"
"  ;  "
" ;;  "
" ;;  "
" ;;  "
"  ;; "
"   ; "
"    ,"
  
"    ,     "
"  ,;      "
"  ;;      "
"  ;;      "
"   ;;    ,"
"     ;;,' "
      
"   ,      "
"   ;     ,"
"    ';,;' "


    
     
     
    
    
  

   ~~o .    
    _|_ \     
   |'v'| \  
  /|___|\_\_
 //|_|_|\\>\  
   // \\      
   ~~o     .  
    _|_    |  
   |'v'|   |  
  /|___|\ _|_   
 //|_|_|\\>|  
   // \\          
   ~~o         .  
    _|_       / 
   |'v'|     /  
  /|___|\  _/_  
 //|_|_|\\>/    
   // \\            
   ~~o                  
    _|_                   
   |'v'|                
  /|___|\               
 //|_|_| \\>-|---------- 
   // \\                            

                                          
                      
*/