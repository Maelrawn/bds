#ifndef CURSE_H
#define CURSE_H

const int HEIGHT = 25;
const int WIDTH = 80;
const float pi = 22/7;


//Clears the entire screen, so no artifacts are left over after
//switching contexts.
void clear_screen(){  
   for(int x = 0; x < WIDTH; x++)
      for(int y = 0; y < HEIGHT; y++)
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
"                                                                                 ",

						};
    for(int x = 0; x < WIDTH; x++)
        for(int y = 1; y < HEIGHT; y++)
        	if(logo.at(y).at(x) == ' ')
	           mvaddch(y, x, ' ');
}

//too lazy to figure out a more intelligent way to do this tbh

void intro_graphic(){
	for(int k = 0; k < 46; k++){
		for(int i = 0; i < 80; i++){
			for(int j = 0; j < 25; j++){

				init_color(COLOR_RED, 1000*sin(atan2(2*pi/(.01*i) - k, 2*pi/(.04*j) - k)),
									  1000*cos(1 - atan2(2*pi/(.04*j) - k, 2*pi/(0.01*i) - k)),
									  1000*sin(atan(k)));
				attron(COLOR_PAIR(1));
				if(i%2 == 0){					
					mvaddch(j, i, ACS_CKBOARD);
				}
				else
					mvaddch(HEIGHT - j, i, ACS_CKBOARD);
				attroff(COLOR_PAIR(1));
				refresh();
				usleep(3000);
			}
			clear_screen_intro();
		}
		k += 44;
	}
}

/*
//Same as above but leaves the header and border intact
void clear_workspace(){
   for(int x = 5; x < MAXY - 1; x++)
       for(int y = 1; y < MAXX - 1; y++)
          mvaddch(x, y, ' ');
}

//Outlines our window with a character
void draw_fullscreen_border(char graphic){
   for(int x = 0; x < MAXX; x++){   //Top and bottom borders
      mvaddch(0, x, graphic);
      mvaddch(24, x, graphic);
   }

   for(int y = 0; y < MAXY; y++){   //Left and right borders
      mvaddch(y, 0, graphic);
      mvaddch(y, MAXX, graphic);
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
   mvaddch(1, 38, '|');
   mvaddch(3, 38, '|');
   mvhline(4, 1, '-', 76);
   mvaddstr(2, 2, header.c_str());
}

//The following functions display the left half of the screen in some functions.
void display_main_menu_options(){
   vector<string> menuitems;
   menuitems.push_back("Browse Customers");
   menuitems.push_back("Add Customer");
   menuitems.push_back("Edit Customer");
   menuitems.push_back("Delete Records");
   menuitems.push_back("Save and Quit");
   menuitems.push_back("Quit Without Saving");
   for(int i = 0; i < menuitems.size(); i++){
      mvaddstr(6 + 2*i, 5, menuitems.at(i).c_str());
   }
}

//Displays an individual book and all fields, i.e. from browse mode
void display_browse_book(vector<Book*> library, int idx){
   display_browse_labels();
   vector<string> menudata;
   Book* book = library.at(idx);
   menudata.push_back(book->getTitle());
   menudata.push_back(book->getAuthor());
   menudata.push_back(book->getPublisher());
   menudata.push_back(book->getDate());
   menudata.push_back(to_string(book->getPageCount()));
   menudata.push_back(as_dhm(book->getReadingTime()));
   menudata.push_back(book->isComplete());
   for(int i = 0; i < menudata.size(); i++){
      mvaddstr(6 + 2*i, MAXY, menudata.at(i).c_str());
   }
}

//Displays all titles in the library that will fit on the screen
void display_purchases(vector<Book*> library, int idx){
   clear_workspace();
   int page = idx/9;
   for(int i = 0; i < 9 && i + page * 9 < library.size(); i++){
      mvaddstr(6 + 2*i, 5, library.at(page * 9 + i)->getTitle().c_str());
   }
   refresh();
}

//Breaks up the excerpt into lines without cutting any words,
//then displays those lines sequentially. We have a capacity
//of about 600 characters without adding pagination. The tools to
//do so are here, but I am stopping now.
void displayExcerpt(Book* book){
   string excerpt = book->getExcerpt();
   vector<string> excerptLines;
   int startpos = 0;
   int lastVal = 0;
   int i = 0;
   while(excerpt.size() > 70){
      if(excerpt[i] == ' '){
         lastVal = i;
      }
      if(i == 70){
         excerptLines.push_back(excerpt.substr(0, lastVal));
         excerpt = excerpt.erase(0, lastVal);
         i = 0;
      }      
      i++;
   }
   excerptLines.push_back(excerpt);
   clear_workspace();
   string titlestr = book->getTitle() + " excerpt:";
   mvaddstr(6, 5, titlestr.c_str());
   for(int k = 0; k < excerptLines.size(); k++){
      mvaddstr(8 + 2*k, 5, excerptLines.at(k).c_str());
   }
   refresh();
   getch();
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
         case '`':
            menuitem = -1;
            return;
         case 'a':
            if(menuitem > 0){
               menuitem--;
               return;
            }
         break;
         case 'd':
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
//functionality. Just don't ask me to backspace.
string handleTextIn(int column, int row){
   char ch = ' ';
   int i = -1;
   string str;
   while(ch != '\n'){
      ch = getch();
      i++;
      if(ch != '\n'){
         mvaddch(6 + 2 * row, i+  MAXY * column, ch);
         str.push_back(ch);
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
   int i = -1;
   string str;
   while(ch != '\n'){
      ch = getch();
      chstr = ch;
      if(ch != '\n' && regex_match(chstr, regex)){
         i++;
         mvaddch(6 + 2 * row, i+  MAXY * column, ch);
         str.push_back(ch);
      }
      refresh();
   }
   if(str.size() <= to_string(INT_MAX).size())
      return str;
   else
      return to_string(INT_MAX);
}

//Routine for selecting and displaying chunks of text
void readBook(vector<Book*> library){
   int idx = 0;
   char ch = ' ';
   while(ch != '`'){
      display_titles(library, idx);
      ch = handleVertInputScr(library.size(), 0, idx);
      if(ch == '\n'){
         displayExcerpt(library.at(idx));
         idx = 0;
         ch = ' ';
      }
   }
}

//Routine for displaying lots of data about our collection of books
void browseLibrary(vector<Book*> library){
   int idx = 0;
   while(idx != -1){
      display_browse_book(library, idx);
      handleHorInput(library.size(), idx);
   }
}

//Takes common ways of saying "true" and standardizes them so we can parse it
bool stob(string in){
   for(int i = 0; i < in.size(); i++){
      in.at(i) = toupper(in.at(i));
   }
   if(in == "1" ||in == "TRUE" || in == "YES" || in == "Y"){
      return 1;
   }
   else
      return 0;
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
            mvhline(6 + 2 * option, MAXY, ' ', 53);
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
void mainMenu(vector<Book*> &library){
   int option = 3;
   while(option != -1){
      clear_workspace();
      draw_fullscreen_border('X');
      draw_header();
      display_main_menu_options();
      refresh();
      if(library.size() > 0){
         option = handleVertInput(7, 0);
         sortByAuthorAndTitle(library);
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