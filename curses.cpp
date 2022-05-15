#ifndef CURSE_H
#define CURSE_H

const int HEIGHT = 25;
const int WIDTH = 80;
const float pi = 22/7;


//Clears the entire screen, so no artifacts are left over after
//switching contexts.
void clear_screen(){  
   for(int x = 0; x <= WIDTH; x++)
      for(int y = 0; y <= HEIGHT; y++)
         mvaddch(y, x, ' ');
}

void clear_screen_intro(){
	vector<string> logo ={
"                                                                                 ",
"                                                                                 ",
"                                                                                 ",
"                                                                                 ",
"                                                                                 ",
"                                                                                 ",
"                                                                                 ",
"                                                                                 ",
"                                                                                 ",
"                     aaaaaaaaa    aaaaaaaaaa      aaaaaaa                        ",
"                       aa    aa     aa    aaaa   aaa    aa                       ",
"                       aa    aa     aa     aaa    aaaa                           ",
"                       aaaaaaa      aa      aa     aaaaaa                        ",
"                       aa    aa     aa     aaa         aaa                       ",
"                       aa    aa     aa    aaaa   aa     aa                       ",
"                     aaaaaaaaa    aaaaaaaaaa      aaaaaaa                        ",
"                                                                                 ",
"                                                                                 ",
"                                                                                 ",
"                                                                                 ",
"                                                                                 ",
"                                                                                 ",
"                                                                                 ",
"                                                                                 ",
"                                                                                 ",
"                                                                                 ",
"                                                                                 ",};
    for(int x = 0; x <= WIDTH; x++)
        for(int y = 1; y < HEIGHT; y++)
        	if(logo.at(y).at(x) == ' ')
	           mvaddch(y, x, ' ');
}

//too lazy to figure out a more intelligent way to do this tbh

void intro_graphic(){
	int k = 45;
	for(int i = 0; i < 81; i++){
		for(int j = 0; j < 25; j++){
			init_color(COLOR_RED, 11*i,11*i,200+10*i);
			attron(COLOR_PAIR(1));
			if(i%2 == 0){					
				mvaddch(j, i, ACS_CKBOARD);
			}
			else
				mvaddch(HEIGHT - j, WIDTH-i, ACS_CKBOARD);
			attroff(COLOR_PAIR(1));
			refresh();
			usleep(5000);
		}
		clear_screen_intro();
	}
	sleep(2);
	clear_screen();
}

//clears an arbitrary rectangle, because I was about to have 10 functions
//that all cleared differently shaped rectangles
void clear_rectangle(int x1, int x2, int y1, int y2){
   for(int x = x1; x < x2 - 1; x++)
       for(int y = y1; y < y2; y++)
          mvaddch(x, y, ' ');
}

//Outlines our window with a character
void draw_fullscreen_border(){
   for(int x = 0; x < WIDTH; x++){   //Top and bottom borders
      mvaddch(0, x, ACS_CKBOARD);
      mvaddch(24, x, ACS_CKBOARD);
   }

   for(int y = 0; y < HEIGHT; y++){   //Left and right borders
      mvaddch(y, 0, ACS_CKBOARD);
      mvaddch(y, WIDTH, ACS_CKBOARD);
   }
}

//Used to paginate menus
int calculate_offset(int maxitem, int idx){
   if(maxitem < 9){
      return idx;
   }
   else if(maxitem >= 9 && idx >= 9){
      return idx%9;
   }
   else return idx;
}

//Makes the nice little arrow next to your current option
void highlight_option(int option, int column, int maxoption){
   string icon = "->";
   option = calculate_offset(maxoption, option);
   mvaddstr(6 + 2 * option, 2 + 15 * column, icon.c_str());
}

//Cleans up the arrow left behind when we switch options
void clear_option(int option, int column, int maxoption){
   string icon = "  ";
   option = calculate_offset(maxoption, option);
   mvaddstr(6 + 2 * option, 2 + 15 * column, icon.c_str());
}

//The thing at the top
void draw_header(){
   string header = " Business Documentation Software BDS  |  arrows move, esc backs";
   mvaddch(1, 40, '|');
   mvaddch(3, 40, '|');
   mvhline(4, 1, '-', 76);
   mvaddstr(2, 2, header.c_str());
}

//The following functions display the left half of the screen in some functions.
void display_main_menu_options(){
	draw_header();
    vector<string> menuitems;
    menuitems.push_back("Browse Customers");
    menuitems.push_back("Sort By:");
    menuitems.push_back("Add Customer");
    menuitems.push_back("Edit Customer");
    menuitems.push_back("Delete Records");
    menuitems.push_back("Save and Quit");
    menuitems.push_back("Quit Without Saving");
    for(int i = 0; i < menuitems.size(); i++){
    	mvaddstr(6 + 2*i, 5, menuitems.at(i).c_str());
    }
}

//Displays an individual customer and their info as a header
void display_customer_header(vector<AllCustomers*> customers, int idx){
    vector<string> menudata;
    AllCustomers* customer = customers.at(idx);
    menudata.push_back(customer->get_firstn());
    menudata.push_back(customer->get_lastn());
    menudata.push_back(to_string(customer->get_phone()));
    menudata.push_back(to_string(customer->get_acc()));
    menudata.push_back(customer->get_addr());
    menudata.push_back(customer->get_city());
    menudata.push_back(customer->get_state());
    menudata.push_back(to_string(customer->get_zip()));
	for(int j = 0; j < 2; j++){	   
   		for(int i = 0; i < menudata.size()/2; i++){
      		mvaddstr(6 + 2*j, 3+ 15 * i, menudata.at(i).c_str());
   		}
   	}
}

//Displays all purchases that will fit on the screen
//TODO: Adjust sizing for header
void display_purchases(vector<AllPurchases*> purchases, int idx){
   clear_rectangle(1, WIDTH, 11, HEIGHT);
   int page = idx/8;
   for(int i = 0; i < 8 && i + page * 8 < purchases.size(); i++){
      mvaddstr(12 + 2*i, 5, purchases.at(page * 8 + i)->get_item().c_str());
   }
   refresh();
}

//Handles vertical menus
int handleVertInput(int maxitem, int column){
   char input = ' ';
   int menuitem = 0;
   while(input != '`'){
      highlight_option(menuitem, column, maxitem);
      refresh();
      input = getch();
      clear_option(menuitem, column, maxitem);
      switch(input){
         case '\n':
            return menuitem;
         break;
         case 'w':
            if(menuitem > 0){
               menuitem--;
            }
         break;
         case 's':
            if(menuitem < maxitem - 1){
               menuitem++;
            }
         break;
      }
   }
   return -1;
}

//Handles vertical menus with pagination. Could the previous
//function have just been this function? Probably. Did I realize
//this before it was worth refactoring? Nope.
char handleVertInputScr(int maxitem, int column, int &menuitem){
   char input = ' ';
   while(input != '`'){
      highlight_option(menuitem, column, maxitem);
      refresh();
      input = getch();
      clear_option(menuitem, column, maxitem);
      switch(input){
         case '\n':
            return input;
         break;
//creating pagination was satanic trial and error, black magic code below 
         case 'w':
            if(menuitem > 0 && menuitem %9 != 0){
               menuitem--;
            }
            else if((menuitem%9) == 0 && menuitem != 0){
               menuitem--;
               return ' ';
            }
         break;
         case 's':
            if(menuitem < maxitem - 1 && menuitem %8 != 0){
               menuitem++;
            }
            else if((menuitem % 8) == 0){
               menuitem++;
               return ' ';
            }
         break;
      }
   }
   return '`';
}

//Handles horizontal menus
void handleHorInput(int maxitem, int &menuitem){
   char input = ' ';
   string left = "<-";
   string right = "->";
   string clear = "           ";
   while(input != '`'){
      if(menuitem > 0){
         mvaddstr(5, 35, left.c_str());
      }
      if(menuitem < maxitem - 1){
         mvaddstr(5, 40, right.c_str());
      }
      refresh();
      input = getch();
      mvaddstr(5, 34, clear.c_str());
      switch(input){
         case KEY_BACKSPACE: //stackexchange says backspace can output all
		 case 127:			 //3 of these things depending on platform
		 case '\b':
            menuitem = -1;
            return;
         case KEY_RIGHT:
            if(menuitem > 0){
               menuitem--;
               return;
            }
         break;
         case KEY_LEFT:
            if(menuitem < maxitem - 1){
               menuitem++;
               return;
            }
         break;
      }
   }
   return;
}

//Because we used cbreak() to disable text inputs being immediately
//displayed in the terminal, we need a function to simulate that
//functionality. Now featuring backspace!
string handleTextIn(int column, int row){
   char ch = ' ';
   int i = 0;
   string str;
   while(ch != '\n' && i >= 0){
      ch = getch();
      if(ch == KEY_BACKSPACE || ch == '127' || ch == '\b'){
      	mvaddch(6 + 2 * row, i + 15 * column, ' ');
      	str.pop_back();
       i--;
      }
      else if(ch != '\n'){
         mvaddch(6 + 2 * row, i + 15 * column, ch);
         str.push_back(ch);
      	 i++;
      }
      refresh();
   }
   return str;
}

//I was getting a crash on stoi(string-with-nonnumeric character input),
//so I wanted to take that out. This does it by only permitting numeric
//characters to be entered.
string handleNumericIn(int column, int row){
   string expr = "[0-9]";
   regex regex (expr);
   char ch = ' ';
   string chstr = " ";
   int i = 0;
   string str;
   while(ch != '\n' && i >= 0){
      ch = getch();
      chstr = ch;
      if(ch != '\n' && regex_match(chstr, regex)){
         i++;
         mvaddch(6 + 2 * row, i + 15 * column, ch);
         str.push_back(ch);
      }
      else if(ch == KEY_BACKSPACE || ch == '127' || ch == '\b'){
      	 mvaddch(6 + 2 * row, i + 15 * column, ' ');
      	 str.pop_back();
      	 i--;
      }
      refresh();
   }
   if(str.size() <= to_string(INT_MAX).size())
      return str;
   else
      return to_string(INT_MAX);
}
/*
//Routine for displaying lots of data about our collection of books
void browseLibrary(vector<Book*> library){
   int idx = 0;
   while(idx != -1){
      display_browse_book(library, idx);
      handleHorInput(library.size(), idx);
   }
}

//Creates a new book with user input and puts it into our library
void createBook(vector<Book*> &library){
   vector<string> bookData;
   string label = "Create Book";
   display_create_labels();
   mvaddstr(5, 33, label.c_str());
   for(int i = 0; i < 7; i++){
      highlight_option(i, 0, i);
      if(i != 4){
         bookData.push_back(handleTextIn(1, i));
      }
      else{
         bookData.push_back(handleNumericIn(1, i));
      }
      draw_fullscreen_border('X');
   }
   Book* book = new Book(  bookData[0],
                           bookData[1],
                           bookData[2],
                           bookData[6],
                           bookData[3],
                      stoi(bookData[4]),
                      stob(bookData[5]));
   library.push_back(book);
}

//Changes a field in a book, then returns to the book selection menu
void editBook(vector<Book*> &library){
   int idx = 0;
   int option = 0;
   char ch = ' ';
   while(ch != '`'){
      display_titles(library, idx);
      ch = handleVertInputScr(library.size(), 0, idx);
      if(ch == '\n'){
         display_browse_book(library, idx);
         option = handleVertInput(7, 0);
         if(option != -1)
            mvhline(6 + 2 * option, HEIGHT, ' ', 53);
         switch(option){
            case 0:
               library.at(idx)->setTitle(handleTextIn(1, option));
               break;
            case 1:
               library.at(idx)->setAuthor(handleTextIn(1, option));
               break;
            case 2:
               library.at(idx)->setPublisher(handleTextIn(1, option));
               break;
            case 3:
               library.at(idx)->setDate(handleTextIn(1, option));
               break;
            case 4:
               library.at(idx)->setPageCount(
                                 stoi(handleNumericIn(1, option)));
               break;
            case 5:
               library.at(idx)->setComplete(
                                 stob(handleTextIn(1, option)));
               break;
            case 6:
               library.at(idx)->setExcerpt(handleTextIn(1, option));
               break;
         }
         sortByAuthorAndTitle(library);
         idx = 0;
         ch = ' ';
      }
   }
}

//Groups books by publisher and allows you to view only grouped books
void browseByPublisher(vector<Book*> library){
   clear_workspace();
   vector<string> publishers;
   vector<Book*> books;
   string pub;
   char ch = ' ';
   bool exists;
   for(int i = 0; i < library.size(); i++){
      pub = library.at(i)->getPublisher();
      exists = false;
      for(int j = 0; j < publishers.size(); j++){
         if(pub == publishers.at(j)){
            exists = true;
         }
      }
      if(!exists){
         publishers.push_back(pub);
      }
   }
   int idx = 0;
   while(ch != '`'){
      for(int i = 0; i < publishers.size(); i++){
         mvaddstr(6 + 2*i, 5, publishers.at(i).c_str());   
      }
      ch = handleVertInputScr(publishers.size(), 0, idx);
      if(ch == '\n'){
         pub = publishers.at(idx);
         for(int i = 0; i < library.size(); i++){
            if(library.at(i)->getPublisher() == pub){
               books.push_back(library.at(i));
            }
         }
         browseLibrary(books);
         books.clear();
         clear_workspace();
         idx = 0;
         ch = ' ';
      }
   }
}


//Writes our library contents to a file of our choosing.
//Don't put a backspace in the name or you'll never be able to type it
void saveQuit(vector<Book*> library){
   string prompt = "-> Enter a filename: ";
   mvaddstr(16, 19, prompt.c_str());
   refresh();
   prompt = handleTextIn(2, 5);
   for(int i = 0; i < library.size(); i++){
      library.at(i)->writeToFile(prompt);
   }
}

//Routine to collect all of the functionality we have built
void mainMenu(vector<AllCustomers*> &customers){
   int option = 3;
   while(option != -1){
      clear_rectangle(1, WIDTH, 6, HEIGHT);
      draw_fullscreen_border();
      draw_header();
      display_main_menu_options();
      refresh();
      if(customers.size() > 0){
         option = handleVertInput(7, 0);
         (library);
      }
      switch(option){
            case -1:
               break;
            case 0:
               browseLibrary(library);
               break;
            case 1: 
               browseByPublisher(library);
               break;
            case 2:
               readBook(library);
               break;
            case 3:
               createBook(library);
               break;
            case 4:
               editBook(library);
               break;
            case 5:
               saveQuit(library);
               endwin();
               return;
            case 6:
               endwin();
               return;
      }
   }
   endwin();
   return;
}
*/
void init_curses(){
   initscr();           //This block of stuff starts Curses mode,
   cbreak();            //disables the input buffer (inputs sent immediately after keypress), 
   keypad(stdscr, true);//allows nonstandard keyboard inputs,
   noecho();            //disables drawing inputs to the screen, 
   start_color();       //gives us pretty colors, (not bothering with rn)
   curs_set(0);         //and disables the cursor graphic
   init_pair(1, COLOR_RED, COLOR_BLACK);
   return;
}

#endif