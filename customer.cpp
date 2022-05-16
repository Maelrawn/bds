#ifndef CUSTOMER_C
#define CUSTOMER_C

#include "customer.hpp"

//Account ID is incremented automatically on creation of new member.
AllCustomers::AllCustomers()
	:firstName(" "), lastName(" "), address(" "), city(" "),
	 state(" "), zip(" "), phone(" "){
	 	account = accountmax;
	 	accountmax++;
	 };

//Because we have a vector of pointers, we want to make sure
//we free that memory properly when we delete this object
AllCustomers::~AllCustomers(){
	for(int i = 0; i < purchases.size(); i++){
		delete purchases.at(i);
	}
	delete this;
};

AllCustomers::AllCustomers(string firstn, 	string lastn,
						   string addr, 	string city,
						   string state,	string zip,
						   string phone,	int acc):
						firstName(firstn), 	lastName(lastn),
						address(addr), 		city(city),
						state(state),		zip(zip),
						phone(phone),		account(acc)
{}								
	
vector<AllPurchases*> AllCustomers::get_purchases(){
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
string AllCustomers::get_zip(){
	return zip;
}
string AllCustomers::get_phone(){
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
void AllCustomers::set_zip(string in){
	zip = in;
}
void AllCustomers::set_phone(string in){
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

void AllCustomers::get_purchases_from_vector(vector<AllPurchases*> allPurchases){
	for(int i = 0; i < allPurchases.size(); i++){
		if(this->account == allPurchases.at(i)->get_acc())
			this->add_purchase(allPurchases.at(i));
	}
}

//Finds the sum total of all purchases tracked by the customer
double AllCustomers::get_purchase_sum(){
	double sum = 0;
	for(int i = 0; i < purchases.size(); i++){
		sum += purchases.at(i)->get_price();
	}
	return sum;
}

//For absolutely no reason I decided to use a vector of lambda functions
//to determine how to sort the objects in the vector of purchases
//I feel like a genius after seeing this compile
//flags are 0, 1, 2, 3, 4, 5; item asc/desc, date asc/desc, price asc/desc
void AllCustomers::sort_purchases(int flag){
	auto itemdesc = [&](AllPurchases* lpurchase, AllPurchases* rpurchase){
		string lstring = lpurchase->get_item();
		string rstring = rpurchase->get_item();
		int cmplen = min(lstring.size(), rstring.size());
		for(int i = 0; i < cmplen - 1; i++){
			if((int)lstring[i] < (int)rstring[i]){
				return true;
			}
		}
		if(lstring.size() < rstring.size())
			return true;
		return false;
	};
	auto itemasc = [&](AllPurchases* lpurchase, AllPurchases* rpurchase){
		string lstring = lpurchase->get_item();
		string rstring = rpurchase->get_item();
		int cmplen = min(lstring.size(), rstring.size());
		for(int i = 0; i > cmplen; i++){
			if((int)lstring[i] > (int)rstring[i]){
				return true;
			}
		}
		if(lstring.size() > rstring.size())
			return true;
		return false;
	};
	auto datedesc = [&](AllPurchases* lpurchase, AllPurchases* rpurchase){
		string lstring = lpurchase->get_date();
		string rstring = rpurchase->get_date();
		vector<int> datevals;
		datevals.push_back(stoi(lstring.substr(6, 9)));
		datevals.push_back(stoi(rstring.substr(6, 9)));
		datevals.push_back(stoi(lstring.substr(0, 1)));
		datevals.push_back(stoi(rstring.substr(0, 1)));
		datevals.push_back(stoi(lstring.substr(3, 4)));
		datevals.push_back(stoi(rstring.substr(3, 4)));
		for(int i = 0; i < 5; i++){
			if(datevals[i] < datevals[i+1]){
				return true;
			}
			i++;
		}
		return false;
	};
	auto dateasc = [&](AllPurchases* lpurchase, AllPurchases* rpurchase){
		string lstring = lpurchase->get_date();
		string rstring = rpurchase->get_date();
		vector<int> datevals;
		datevals.push_back(stoi(lstring.substr(6, 9)));
		datevals.push_back(stoi(rstring.substr(6, 9)));
		datevals.push_back(stoi(lstring.substr(0, 1)));
		datevals.push_back(stoi(rstring.substr(0, 1)));
		datevals.push_back(stoi(lstring.substr(3, 4)));
		datevals.push_back(stoi(rstring.substr(3, 4)));
		for(int i = 0; i < 5; i++){
			if(datevals[i] > datevals[i+1]){
				return true;
			}
			i++;
		}
		return false;
	};
	auto pricedesc = [&](AllPurchases* lpurchase, AllPurchases* rpurchase){
		if(lpurchase->get_price() < rpurchase->get_price())
			return true;
		return false;
	};
	auto priceasc = [&](AllPurchases* lpurchase, AllPurchases* rpurchase){
		if(lpurchase->get_price() > rpurchase->get_price())
			return true;
		return false;
	};

	vector<function<bool(AllPurchases*, AllPurchases*)>> funcvec 
		= {itemasc, itemdesc, dateasc, datedesc, priceasc, pricedesc};
	
	AllPurchases* tmp;
	
	for(int j = 0; j < purchases.size(); j++){
		for(int i = 0; i < purchases.size() - 1; i++){
			if(funcvec.at(flag)(purchases.at(i), purchases.at(i + 1))){
				tmp = purchases.at(i+1);
				purchases.at(i+1) = purchases.at(i);
				purchases.at(i) = tmp;
			}
		}
	}
}

//Sorts our customers by account ID
void sort_by_account(vector<AllCustomers*> &customers){
	AllCustomers* tmp;
	for(int i = 0; i < customers.size(); i++){
		for(int j = 0; j < customers.size() - 1; j++){
			if(customers.at(j)->get_acc() < customers.at(j)->get_acc()){
				tmp = customers.at(j+1);
				customers.at(j+1) = customers.at(j);
				customers.at(j) = tmp;
			}
		}
	}
}

//Reads through an input file and adds any purchases with matching
//account IDs to our AllCustomer's vector of purchases
void AllCustomers::populate_purchases(string filename){
	ifstream inFile;
	string tmp;
	vector<string> inV;
	inFile.open(filename);
	while(getline(inFile, tmp)){
		if(tmp[0] == '$'){
			tmp = tmp.substr(1, tmp.size()-1);
		}
		inV.push_back(tmp);
		if(inV.size() == 5 && stoi(inV.at(4)) == account){
			purchases.push_back(new AllPurchases(inV.at(0), 
						    					inV.at(1), 
										   stoi(inV.at(2)), 
			 		  					   stof(inV.at(3)),
			 		  					   stoi(inV.at(4))));
			inV.clear();
		}
		else if(inV.size() == 5){
			inV.clear();
		}
	}
	inFile.close();
}

//Reads all data from a file and stores it as AllCustomers
vector<AllCustomers*> populate_customers_from_file(string cfile, string pfile){
	vector<AllCustomers*> output;
	ifstream inFile;
	string tmp;
	vector<string> inV;
	inFile.open(cfile);
	while(getline(inFile, tmp)){
		inV.push_back(tmp);
		if(inV.size() == 8){
			output.push_back(new AllCustomers(  inV.at(0), 
						    					inV.at(1),
						    					inV.at(2),
						    					inV.at(3),
						    					inV.at(4), 
										   		inV.at(5), 
			 		  					   		inV.at(6),
			 		  					   stoi(inV.at(7))));
			inV.clear();
		}
	}
	inFile.close();
	for(int i = 0; i < output.size(); i++){
		output.at(i)->populate_purchases(pfile);
	}
	AllCustomers* tmp2;
	for(int i = 0; i < output.size(); i++){
		for(int j = 0; j < output.size()-1; j++){
			if(output.at(j)->get_acc() < output.at(j+1)->get_acc()){
				tmp2 = output.at(j);
				output.at(j) = output.at(j+1);
				output.at(j+1) = tmp2;
			}
		}
	}
	return output;
}

//Member function for a given customer to write its info to a file
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

//Writes all of our purchase data to its own file
void write_purchase_file(vector<AllCustomers*> customers, string filename){
	ofstream outFile;
	outFile.open(filename, ios_base::trunc);
	outFile.close();
	for(int i = 0; i < customers.size(); i++){
		write_purchase_list(customers.at(i)->get_purchases(), filename);
	}
}

//Writes all of our customer data to its own file
void write_customer_file(vector<AllCustomers*> customers, string filename){
	ofstream outFile;
	outFile.open(filename, ios_base::trunc);
	outFile.close();
	for(int i = 0; i < customers.size(); i++){
		customers.at(i)->write_to_file(filename);
	}
}

#endif