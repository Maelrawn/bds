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
			usleep(2500);
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
          mvaddch(y, x, ' ');
}

//Outlines our window with a character
void draw_fullscreen_border(){
   for(int x = 0; x < WIDTH; x++){   //Top and bottom borders
      mvaddch(0, x, ACS_CKBOARD);
      mvaddch(HEIGHT, x, ACS_CKBOARD);
   }

   for(int y = 0; y < HEIGHT; y++){   //Left and right borders
      mvaddch(y, 0, ACS_CKBOARD);
      mvaddch(y, WIDTH - 1, ACS_CKBOARD);
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
   mvaddstr(6 + 2 * option, 2 + 25 * column, icon.c_str());
}

//Cleans up the arrow left behind when we switch options
void clear_option(int option, int column, int maxoption){
   string icon = "  ";
   option = calculate_offset(maxoption, option);
   mvaddstr(6 + 2 * option, 2 + 25 * column, icon.c_str());
}

//The thing at the top
void draw_header(){
   string header = 
   		" Business Documentation Software BDS  |     W A S D move, backspace backs";
   mvaddch(1, 40, '|');
   mvaddch(3, 40, '|');
   mvhline(4, 1, '-', 78);
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
    menudata.push_back(		customer->get_firstn()+ " "
    				   	+ 	customer->get_lastn() + ", "
    				   	+	customer->get_phone() + ", account no. "
    				   	+ 	to_string(customer->get_acc()));
    menudata.push_back(		customer->get_addr() + ", "
    					+	customer->get_city() + ", "
    					+	customer->get_state()+ ", "
    					+	customer->get_zip());
    double sum = 0;
    for(int i = 0; i < customer->get_purchases().size(); i++){
    	sum += 		customer->get_purchases().at(i)->get_price()
    			*	customer->get_purchases().at(i)->get_amount();
    }
    menudata.push_back(		customer->get_firstn() + " "
    					+	customer->get_lastn() + "'s "
    					+	"total expenditures: $"
    					+	to_string(sum).substr(0, to_string(sum).size() - 4));
	for(int i = 0; i < menudata.size(); i++){
		mvaddstr(6 + 2*i, WIDTH/2 - menudata.at(i).size()/2 - 2, menudata.at(i).c_str());	
	}
}

//Displays all purchases that will fit on the screen
void display_purchases(vector<AllPurchases*> purchases, int idx){
   clear_rectangle(1, WIDTH, 11, HEIGHT);
   vector<string> itemdata;
   for(int i = idx; i < purchases.size(); i++){
   		itemdata.push_back(		purchases.at(i)->get_date() + ": x"
   							+	to_string(purchases.at(i)->get_amount()) + " "
   							+	purchases.at(i)->get_item() + " for $"
   							+	to_string(purchases.at(i)->get_price())
   								.substr(0, to_string(purchases.at(i)->get_price()).size() - 4) + " each");
   }
   for(int i = 0; i < purchases.size() - idx; i++){
   		if(12 + 2*i <= HEIGHT - 3){
		    mvaddstr(12 + 2*i, 5, itemdata.at(i).c_str());
   		}
   	}
   refresh();
}



char handle_2d_input(int maxitemx, int maxitemy, int& xidx, int& yidx){
	char input = ' ';
	string uparrow = "^";
	string downarrow = "v";
	string leftarrow = "<-";
	string rightarrow = "->";
	while(input != 127){
		clear_rectangle(3, 7, 6, 8);
		if(yidx > 0)
			mvaddstr(6, 5, uparrow.c_str());
		if(yidx < maxitemy)
			mvaddstr(8, 5, downarrow.c_str());
		if(xidx < maxitemx)
			mvaddstr(7, 6, rightarrow.c_str());
		if(xidx > 0)
			mvaddstr(7, 3, leftarrow.c_str());
		refresh();
		input = getch();
		switch(input){
			case 's':
				if(yidx < maxitemy){
					yidx++;
				}
			break;
			case 'w':
				if(yidx > 0){
					yidx--;
				}
			break;
			case 'a':
				if(xidx > 0){
					xidx--;
					yidx = 0;
				}
			break;
			case 'd':
				if(xidx < maxitemx){
					xidx++;
					yidx = 0;
				}
			break;
			case '\n':
				return '\n';
			break;
		}
		if(input == 127)
			xidx = -1;
			return input;
	}
}

//Handles vertical menus
int handle_vert_in(int maxitem, int column){
   char input = ' ';
   int menuitem = 0;
   while(input != 127){
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

//Because we used cbreak() to disable text inputs being immediately
//displayed in the terminal, we need a function to simulate that
//functionality. Now featuring backspace!
string handle_text_in(int column, int row){
   char ch = ' ';
   int i = 0;
   string str;
   while(ch != '\n' && i >= 0){
      ch = getch();
      // if(ch == 127 && str.size() > 0){
      //  i--;
      // 	mvaddch(6 + 2 * row, i + 15 * column, ' ');
      // 	str.pop_back();
      // }
      if(ch != '\n'){
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
string handle_numeric_in(int column, int row){
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
      // else if(ch == 127){
      // 	 i--;
      // 	 mvaddch(6 + 2 * row, i + 15 * column, ' ');
      // 	 str.pop_back();
      // }
      refresh();
   }
   if(str.size() <= to_string(INT_MAX).size())
      return str;
   else
      return to_string(INT_MAX);
}


void edit_purchase(AllPurchases* &purchase){
	clear_rectangle(1, WIDTH, 6, HEIGHT);
    int selection = 0;
    vector<string> fields = {"Item name: " + purchase->get_item(),
							"Date: " + purchase->get_date(),
							"Amount: " + to_string(purchase->get_amount()),
							"Price: $" + to_string(purchase->get_price()).substr(0, to_string(purchase->get_price()).size()-4),
							"Finish",
							"Account Number: " + to_string(purchase->get_acc())};
    string label = "Edit Purchase";
    for(int i = 0; i < fields.size(); i++){
		mvaddstr(6 + 2*i, 5, fields.at(i).c_str());
    }
	mvaddstr(5, 33, label.c_str());
    refresh();
    while(selection != -1){
	    selection = handle_vert_in(5, 0);
	    curs_set(1);
	    switch(selection){
	    	case 0:
	    		clear_rectangle(16, WIDTH, 6, 7);
	    		purchase->set_item(handle_text_in(2, selection));
	    		break;
	    	case 1:
	    		clear_rectangle(10, WIDTH, 8, 9);
	    		purchase->set_date(handle_text_in(2, selection));
	    		break;
	    	case 2:
	    		clear_rectangle(13, WIDTH, 10, 11);
	    		purchase->set_amount(stoi(handle_numeric_in(2, selection)));
	    		break;
	    	case 3:
	    		clear_rectangle(13, WIDTH, 12, 13);
	    		purchase->set_price(stof(handle_text_in(2, selection)));
	    		break;
	    	case 4:
	    		selection = -1;
	    		break;
	    }
	curs_set(0);
	}
}

void edit_customer(AllCustomers* &customer){
	clear_rectangle(1, WIDTH, 6, HEIGHT);
    int selection = 0;
    vector<string> fields = {"First name: " + customer->get_firstn(),
							"Last name: " + customer->get_lastn(),
							"Address: " + customer->get_addr(),
							"City: " + customer->get_city(),
							"State: "+ customer->get_state(),
							"Zip Code: " + customer->get_zip(),
							"Phone Number: " + customer->get_phone(),
							"Finish",
							"Account Number: " + to_string(customer->get_acc())};
    string label = "Edit Customer";
    for(int i = 0; i < fields.size(); i++){
		mvaddstr(6 + 2*i, 5, fields.at(i).c_str());
    }
	mvaddstr(5, 33, label.c_str());
    refresh();
    while(selection != -1){
	    selection = handle_vert_in(8, 0);
	    curs_set(1);
	    switch(selection){
	    	case 0:
	    		clear_rectangle(16, WIDTH, 6, 7);
	    		customer->set_firstn(handle_text_in(2, selection));
	    		break;
	    	case 1:
	    		clear_rectangle(15, WIDTH, 8, 9);
	    		customer->set_lastn(handle_text_in(2, selection));
	    		break;
	    	case 2:
	    		clear_rectangle(13, WIDTH, 10, 11);
	    		customer->set_addr(handle_text_in(2, selection));
	    		break;
	    	case 3:
	    		clear_rectangle(11, WIDTH, 12, 13);
	    		customer->set_city(handle_text_in(2, selection));
	    		break;
	    	case 4:
	    		clear_rectangle(12, WIDTH, 14, 15);
	    		customer->set_state(handle_text_in(2, selection));
	    		break;
	    	case 5:
	    		clear_rectangle(14, WIDTH, 16, 17);
	    		customer->set_zip(handle_text_in(2, selection));
	    		break;
	    	case 6:
	    		clear_rectangle(18, WIDTH, 18, 19);
	    		customer->set_phone(handle_text_in(2, selection));
	    		break;
	    	case 7:
	    		selection = -1;
	    		break;
	    }
	curs_set(0);
	}
}

//Routine for displaying lots of data about our collection of books
void browse_customers(vector<AllCustomers*> &customers){
   int xidx = 0;
   int yidx = 0;
   char input = ' ';
   while(xidx != -1){
      clear_rectangle(0, WIDTH, 0, HEIGHT);
   	  draw_fullscreen_border();
   	  draw_header();
      display_customer_header(customers, xidx);
      display_purchases(customers.at(xidx)->get_purchases(), yidx);
      highlight_option(3, 0, 5);
      input = handle_2d_input(	customers.size()-1, 
      							customers.at(xidx)->get_purchases().size()-1,
      							xidx,
      							yidx);
      clear_option(3, 0, 5);
      if(input == '\n'){
      	edit_purchase(customers.at(xidx)->get_purchases().at(yidx));
      }
   }
}

// void browse_customers(vector<AllCustomers*> &customers){
//    int xidx = 0;
//    int yidx = 0;
//    char input = ' ';
//    while(xidx != -1){
//       clear_rectangle(0, WIDTH, 0, HEIGHT);
//    	  draw_fullscreen_border();
//    	  draw_header();
//       display_customer_header(customers, xidx);
//       display_purchases(customers.at(xidx)->get_purchases(), yidx);
//       highlight_option(3, 0, 5);
//       input = handle_2d_input(	customers.size()-1, 
//       							customers.at(xidx)->get_purchases().size()-1,
//       							xidx,
//       							yidx);
//       clear_option(3, 0, 5);
//       if(input == '\n'){
//       	edit_purchase(customers.at(xidx)->get_purchases().at(yidx));
//       }
//    }
// }

//TODO: MENU FOR EDITING A CUSTOMER

//TODO: MENU FOR ADDING A PURCHASE TO A CUSTOMER

//TODO: FUNCTION FOR DELETING A CUSTOMER

//TODO: FUNCTION FOR DELETING A PURCHASE

void display_sort_options(){
	vector<string> menuitems = {"Items, ascending",
								"Items, descending",
								"Date, ascending",
								"Date, descending",
								"Price, ascending",
								"Price, descending"};
	for(int i = 0; i < menuitems.size(); i++){
		mvaddstr(6 + 2*i, 30, menuitems.at(i).c_str());
	}
}

void sort_customer_purchases(vector<AllCustomers*> &customers){
	int flag = 0;
	display_sort_options();
	flag = handle_vert_in(6, 1);
	if(flag != -1){
		for(int i = 0; i < customers.size(); i++){
			customers.at(i)->sort_purchases(flag);
		}
		flag = -1;
	}
}

//Creates a new customer with user input and puts it into our customers
void add_customer(vector<AllCustomers*> &customers){
    AllCustomers* customer = new AllCustomers();
	clear_rectangle(1, WIDTH, 6, HEIGHT);
    int selection = 0;
    vector<string> data = {" ", " ", " ", " ", " ", " ", " "};
    vector<string> fields = {"First name:",
							"Last name:",
							"Address:",
							"City:",
							"State:",
							"Zip Code:",
							"Phone Number:",
							"Finish",
							"Account Number: " + to_string(customer->get_acc())};
    string label = "Add Customer";
    for(int i = 0; i < fields.size(); i++){
		mvaddstr(6 + 2*i, 5, fields.at(i).c_str());
    }
	mvaddstr(5, 33, label.c_str());
    refresh();
    while(selection != -1){
	    selection = handle_vert_in(8, 0);
	    curs_set(1);
	    if(selection != -1 && selection < 5){
	        data.at(selection) = handle_text_in(2, selection);
	    }
	    else if(selection != -1 && selection != 7){
	   		data.at(selection) = handle_numeric_in(2, selection);
	    }
	    else if(selection == 7){
			customer->set_firstn(data.at(0));
			customer->set_lastn(data.at(1));
			customer->set_addr(data.at(2));
			customer->set_city(data.at(3));
			customer->set_state(data.at(4));
			customer->set_zip(data.at(5));
			customer->set_phone(data.at(6));
			customers.push_back(customer);
			for(int i = WIDTH/4; i < 3 * WIDTH/4; i++){
				for(int j = 3*HEIGHT/5; j < 4*HEIGHT/5; j++){
					mvaddch(j, i, ' ');
				}
			}
			string prompt = "Register another user? Y/N";
			mvaddstr(12, 30, prompt.c_str());
			refresh();
			curs_set(0);
			char yn = getch();
			if(yn == 'Y' || yn == 'y'){
				add_customer(customers);
			}
			else
				selection = -1;
		}
	}
	curs_set(0);
}

/*
//Changes a field in a book, then returns to the book selection menu
void editBook(vector<AllCustomers*> &customers){
   int idx = 0;
   int option = 0;
   char ch = ' ';
   while(ch != '`'){
      display_titles(customers, idx);
      ch = handle_vert_in_scr(customers.size(), 0, idx);
      if(ch == '\n'){
         display_browse_book(customers, idx);
         option = handle_vert_in(7, 0);
         if(option != -1)
            mvhline(6 + 2 * option, HEIGHT, ' ', 53);
         switch(option){
            case 0:
               customers.at(idx)->setTitle(handle_text_in(1, option));
               break;
            case 1:
               customers.at(idx)->setAuthor(handle_text_in(1, option));
               break;
            case 2:
               customers.at(idx)->setPublisher(handle_text_in(1, option));
               break;
            case 3:
               customers.at(idx)->setDate(handle_text_in(1, option));
               break;
            case 4:
               customers.at(idx)->setPageCount(
                                 stoi(handle_numeric_in(1, option)));
               break;
            case 5:
               customers.at(idx)->setComplete(
                                 stob(handle_text_in(1, option)));
               break;
            case 6:
               customers.at(idx)->setExcerpt(handle_text_in(1, option));
               break;
         }
         sortByAuthorAndTitle(customers);
         idx = 0;
         ch = ' ';
      }
   }
}

//Groups books by publisher and allows you to view only grouped books
void browseByPublisher(vector<AllCustomers*> customers){
   clear_workspace();
   vector<string> publishers;
   vector<Book*> books;
   string pub;
   char ch = ' ';
   bool exists;
   for(int i = 0; i < customers.size(); i++){
      pub = customers.at(i)->getPublisher();
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
      ch = handle_vert_in_scr(publishers.size(), 0, idx);
      if(ch == '\n'){
         pub = publishers.at(idx);
         for(int i = 0; i < customers.size(); i++){
            if(customers.at(i)->getPublisher() == pub){
               books.push_back(customers.at(i));
            }
         }
         browse_customers(books);
         books.clear();
         clear_workspace();
         idx = 0;
         ch = ' ';
      }
   }
}

*/
//Writes our customers contents to a file of our choosing.
//Don't put a backspace in the name or you'll never be able to type it
// void save_quit(vector<AllCustomers*> customers){
//    string prompt = "-> Enter a filename: ";
//    mvaddstr(16, 19, prompt.c_str());
//    refresh();
//    prompt = handle_text_in(2, 5);
//    for(int i = 0; i < customers.size(); i++){
//       customers.at(i)->writeToFile(prompt);
//    }
// }

//Routine to collect all of the functionality we have built
void main_menu(vector<AllCustomers*> &customers){
   int option = 3;
   while(option != -1){
      clear_rectangle(1, WIDTH, 6, HEIGHT);
      draw_fullscreen_border();
      draw_header();
      display_main_menu_options();
      refresh();
      option = handle_vert_in(7, 0);
      switch(option){
            case -1:
                break;
            case 0:
                browse_customers(customers);
                break;
            case 1: 
				sort_customer_purchases(customers);	
				break;
            case 2:
                add_customer(customers);
            	break;
            // case 3:
            //    createBook(customers);
            //    break;
            // case 4:
            //    editBook(customers);
            //    break;
            // case 5:
            //    save_quit(customers);
            //    endwin();
            //    return;
            case 6:
               endwin();
               return;
      }
   }
   endwin();
   return;
}

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