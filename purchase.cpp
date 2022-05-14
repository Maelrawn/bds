#ifndef PURCHASE_C
#define PURCHASE_C

#include "purchase.hpp"

AllPurchases::AllPurchases(string item, string date,
		 int amount, int account,
		 double price)
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

bool AllPurchases::operator<(AllPurchases& rhs){
	return this->account < rhs.account;
}
bool AllPurchases::operator==(AllPurchases& rhs){
	return this->account == rhs.account;
}
bool AllPurchases::operator<=(AllPurchases& rhs){
	return this->account <= rhs.account;
}

void AllPurchases::print(){
	return;
}

vector<AllPurchases*> populate_purchases_from_file(string filename){
	vector<AllPurchases*> output;
	ifstream inFile;
	string tmp;
	vector<string> inV;
	inFile.open(filename);
	while(getline(inFile, tmp)){
		if(tmp[0] == '$')
			tmp = tmp.substr(1, tmp.size()-1);
		inV.push_back(tmp);
		if(inV.size() == 5){
			output.push_back(new AllPurchases(  inV.at(0), 
						    					inV.at(1), 
										   stoi(inV.at(2)), 
			 		  					   stof(inV.at(3)),
			 		  					   stoi(inV.at(4))));
			inV.clear();
		}
	}
	inFile.close();
	return output;
}

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

void write_purchase_list(vector<AllPurchases*> purchases, string filename){
	ofstream outFile;
	for(int i = 0; i < purchases.size(); i++){
		purchases.at(i)->write_to_file(filename);
	}
}

void write_purchase_file(vector<AllPurchases*> purchases, string filename){
	ofstream outFile;
	outFile.open(filename, ios_base::trunc);
	outFile.close();
	for(int i = 0; i < purchases.size(); i++){
		purchases.at(i)->write_to_file(filename);
	}
}

#endif