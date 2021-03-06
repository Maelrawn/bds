#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "purchase.cpp"

class AllCustomers{
private:
	
	vector<AllPurchases*> purchases;
	
	string firstName;
	string lastName;
	string address;
	string city;
	string state;	
	string zip;
	string phone;

	int account;

public:
	
	AllCustomers();
	~AllCustomers();
	AllCustomers(string firstn, string lastn,
			     string addr, 	string city,
				 string state,	string zip,
				 string phone,	int acc);

	vector<AllPurchases*> get_purchases();
	string get_firstn();
	string get_lastn();
	string get_addr();
	string get_city();
	string get_state();
	string get_zip();
	string get_phone();
	int get_acc();
	
	void add_purchase(AllPurchases* purchase);
	void set_firstn(string in);
	void set_lastn(string in);
	void set_addr(string in);
	void set_city(string in);
	void set_state(string in);
	void set_zip(string in);
	void set_phone(string in);
	
	bool operator<(AllCustomers& rhs);
	bool operator==(AllCustomers& rhs);
	bool operator<=(AllCustomers& rhs);

	void populate_purchases(string filename);

	void sort_purchases(int flag);
	void get_purchases_from_vector(vector<AllPurchases*> allPurchases);

	double get_purchase_sum();

	void write_to_file(string filename);
	
};

/*Print out all list of all AllCustomerss
Option to sort and print AllCustomers list in descending or ascending order
Print out a specific AllCustomers’s account information
Print out the total spend for all a customer's purchases*/

void sort_customer_list(vector<AllCustomers> customers, int flag);

void print_customer_list(vector<AllCustomers> customers);

#endif

