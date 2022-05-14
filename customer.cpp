#ifndef CUSTOMER_C
#define CUSTOMER_C
#include "customer.hpp"


AllCustomers();
~AllCustomers();
AllCustomers(AllCustomers& rhs, vector<AllPurchases*> purchaseData,
			 vector<string> stringData, vector<int> intData);
	
vector<AllPurchases*> get_purchases(){
	return purchases;
}
string AllCustomers::get_firstn(){
	return firstName;
}
string AllCustomers::get_lastn(){
	return lastName;
}
string AllCustomers::get_addr(){
	return address;
}
string AllCustomers::get_city(){
	return city;
}
string AllCustomers::get_state(){
	return state;
}
int AllCustomers::get_zip(){
	return zip;
}
int AllCustomers::get_phone(){
	return phone;
}
int AllCustomers::get_acc(){
	return account;
}

void AllCustomers::add_purchase(AllPurchases* purchase){
	purchases.push_back(purchase);
}
void AllCustomers::set_firstn(string in){
	firstName = in;
}
void AllCustomers::set_lastn(string in){
	lastName = in;
}
void AllCustomers::set_addr(string in){
	address = in;
}
void AllCustomers::set_city(string in){
	city = in;
}
void AllCustomers::set_state(string in){
	state = in;
}
void AllCustomers::set_zip(int in){
	zip = in;
}
void AllCustomers::set_phone(int in){
	phone = in;
}

bool AllCustomers::operator<(AllCustomers& rhs){
	return this->account < rhs.account;
}
bool AllCustomers::operator==(AllCustomers& rhs){
	return this->account == rhs.account;
}
bool AllCustomers::operator<=(AllCustomers& rhs){
	return this->account <= rhs.account;
}

void AllCustomers::print(){}

void AllCustomers::get_purchases_from_vector(vector<AllPurchases*> allPurchases){
	for(int i = 0; i < allPurchases.size(); i++){
		if(this->account == allPurchases.at(i)->get_acc())
			this->add_purchase(allPurchases.at(i));
	}
}

double AllCustomers::get_purchase_sum(){}

//For absolutely no reason I decided to use a vector of lambda functions
//to determine how to sort the objects in the vector of purchases
//I feel like a genius after seeing this compile
//flags are 0, 1, 2, 3, 4, 5; item asc/desc, date asc/desc, price asc/desc
void AllCustomers::sort_purchases(int flag){
	auto itemasc = [&](AllPurchases* lpurchase, AllPurchases* rpurchase){
		string lstring = lpurchase->get_item();
		string rstring = rpurchase->get_item();
		int cmplen = min(lstring.size(), rstring.size());
		for(int i = 0; i < cmplen; i++){
			if(lstring[i] < rstring[i]){
				return true;
			}
		}
		if(lstring.size() < rstring.size())
			return true;
		return false;
	};
	auto itemdesc = [&](AllPurchases* lpurchase, AllPurchases* rpurchase){
		string lstring = lpurchase->get_item();
		string rstring = rpurchase->get_item();
		int cmplen = min(lstring.size(), rstring.size());
		for(int i = 0; i > cmplen; i++){
			if(lstring[i] > rstring[i]){
				return true;
			}
		}
		if(lstring.size() > rstring.size())
			return true;
		return false;
	};
	auto dateasc = [&](AllPurchases* lpurchase, AllPurchases* rpurchase){
		string lstring = lpurchase->get_date();
		string rstring = rpurchase->get_date();
		int lsize = lstring.size() - 1;
		int rsize = rstring.size() - 1;
		vector<int> datevals;
		datevals.push_back(stoi(lstring.substr(lsize - 3, lsize)));
		datevals.push_back(stoi(lstring.substr(3, 4)));
		datevals.push_back(stoi(lstring.substr(0, 1)));
		datevals.push_back(stoi(rstring.substr(0, 1)));
		datevals.push_back(stoi(rstring.substr(3, 4)));
		datevals.push_back(stoi(rstring.substr(rsize - 3, rsize)));
		for(int i = 0; i < 3; i++){
			if(datevals[i] < datevals[datevals.size() - (i + 1)]){
				return true;
			}
		}
		return false;
	};
	auto datedesc = [&](AllPurchases* lpurchase, AllPurchases* rpurchase){
		string lstring = lpurchase->get_date();
		string rstring = rpurchase->get_date();
		int lsize = lstring.size() - 1;
		int rsize = rstring.size() - 1;
		vector<int> datevals;
		datevals.push_back(stoi(lstring.substr(lsize - 3, lsize)));
		datevals.push_back(stoi(lstring.substr(3, 4)));
		datevals.push_back(stoi(lstring.substr(0, 1)));
		datevals.push_back(stoi(rstring.substr(0, 1)));
		datevals.push_back(stoi(rstring.substr(3, 4)));
		datevals.push_back(stoi(rstring.substr(rsize - 3, rsize)));
		for(int i = 0; i < 3; i++){
			if(datevals[i] > datevals[datevals.size() - (i + 1)]){
				return true;
			}
		}
		return false;
	};
	auto priceasc = [&](AllPurchases* lpurchase, AllPurchases* rpurchase){
		if(lpurchase->get_price() < rpurchase->get_price())
			return true;
		return false;
	};
	auto pricedesc = [&](AllPurchases* lpurchase, AllPurchases* rpurchase){
		if(lpurchase->get_price() > rpurchase->get_price())
			return true;
		return false;
	};

	vector<function<bool(AllPurchases*, AllPurchases*)>> funcvec 
		= {itemasc, itemdesc, dateasc, datedesc, priceasc, pricedesc};

	AllPurchases* tmp;
	for(int i = 0; i < purchases.size(); i++){
		for(int j = 0; j < purchases.size() - 1; j++){
			if(funcvec.at(i)(purchases.at(i), purchases.at(i + 1))){
				*tmp = *purchases.at(i);
				*purchases.at(i) = *purchases.at(i+1);
				*purchases.at(i+1) = *tmp;
			}
		}
	}
}

vector<AllCustomers*> populate_customers_from_file(string filename){
	vector<AllCustomers*> output;
	ifstream inFile;
	string tmp;
	vector<string> inV;
	inFile.open(filename);
	while(getline(inFile, tmp)){
		inV.push_back(tmp);
		if(inV.size() == 8){
			output.push_back(new AllCustomers(  inV.at(0), 
						    					inV.at(1),
						    					inV.at(2),
						    					inV.at(3),
						    					inV.at(4), 
										   stoi(inV.at(5)), 
			 		  					   stoi(inV.at(6))
			 		  					   stoi(inV.at(7))));
			inV.clear();
		}
	}
	inFile.close();
	return output;
}

void AllCustomers::write_to_file(string filename){
	ofstream outFile;
	outFile.open(filename, ios_base::app);
	if(outFile.is_open()){
		outFile << firstName<<"\n"
				<< lastName <<"\n"
				<< address 	<<"\n"
				<< city 	<<"\n"
				<< state 	<<"\n"
				<< zip 		<<"\n"
				<< phone 	<<"\n"
				<< account 	<<"\n";
	}
	outFile.flush();
}

void write_purchase_file(vector<AllCustomers*> customers, string filename){
	ofstream outFile;
	outFile.open(filename, ios_base::trunc);
	outFile.close();
	for(int i = 0; i < customers.size(); i++){
		customers.at(i)->write_purchase_list(filename);
	}
}

void write_customer_file(vector<AllCustomers*> customers, string filename){
	ofstream outFile;
	outFile.open(filename, ios_base::trunc);
	outFile.close();
	for(int i = 0; i < customers.size(); i++){
		customers.at(i)->write_to_file(filename);
	}
}

#endif