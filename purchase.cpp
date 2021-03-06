#ifndef PURCHASE_C
#define PURCHASE_C

#include "purchase.hpp"

//Account max is incremented automatically
AllPurchases::AllPurchases(string item, string date,
		 int amount, double price,
		 int account)
		:item(item), date(date),
		 amount(amount), account(account),
		 price(price)
	{
		if(accountmax <= this->account){
			accountmax = this->account+1;
		}
}

AllPurchases::AllPurchases()
	:item(""), date("00/00/0000"),
	 amount(0), account(accountmax++),
	 price(0)
{}
							
AllPurchases::~AllPurchases(){
	delete this;
}

string AllPurchases::get_item(){
	return this->item;
}
string AllPurchases::get_date(){
	return this->date;
}
int AllPurchases::get_amount(){
	return this->amount;
}
int AllPurchases::get_acc(){
	return this->account;
}
double AllPurchases::get_price(){
	return this->price;
}

void AllPurchases::set_item(string in){
	this->item = in;
}
void AllPurchases::set_date(string in){
	this->date = in;
}
void AllPurchases::set_amount(int in){
	this->amount = in;
}
void AllPurchases::set_price(double in){
	this->price = in;
}
void AllPurchases::set_acc(int in){
	this->account = in;
}

bool AllPurchases::operator<(AllPurchases& rhs){
	return this->account < rhs.account;
}
bool AllPurchases::operator==(AllPurchases& rhs){
	return this->account == rhs.account;
}
bool AllPurchases::operator<=(AllPurchases& rhs){
	return this->account <= rhs.account;
}

//Writes a purchase to the given file
void AllPurchases::write_to_file(string filename){
	ofstream outFile;
	outFile.open(filename, ios_base::app);
	if(outFile.is_open()){
		outFile << item 	<<"\n"
				<< date  	<<"\n"
				<< amount 	<<"\n"
				<< price 	<<"\n"
				<< account  <<"\n";
	}
	outFile.flush();
}

//Writes a vector of purchases, appending
void write_purchase_list(vector<AllPurchases*> purchases, string filename){
	ofstream outFile;
	for(int i = 0; i < purchases.size(); i++){
		purchases.at(i)->write_to_file(filename);
	}
}

//Writes a vector of purchases, truncating
void write_purchase_file(vector<AllPurchases*> purchases, string filename){
	ofstream outFile;
	outFile.open(filename, ios_base::trunc);
	outFile.close();
	for(int i = 0; i < purchases.size(); i++){
		purchases.at(i)->write_to_file(filename);
	}
}

#endif