#ifndef PURCHASE_H
#define PURCHASE_H

using namespace std;

int accountmax = 0;

class AllPurchases{

private:

	string item;
	string date;
	
	int amount;
	int account;
	
	double price;

public:
	
	AllPurchases(string item, string date,
			 int amount, double price,
			 int account);	
	AllPurchases();
	~AllPurchases();

	string get_item();
	string get_date();
	int get_amount();
	int get_acc();
	double get_price();

	void set_item(string in);
	void set_date(string in);
	void set_amount(int in);
	void set_price(double in);
	void set_acc(int in);

	bool operator<(AllPurchases& rhs);
	bool operator==(AllPurchases& rhs);
	bool operator<=(AllPurchases& rhs);

	void write_to_file(string filename);
};

#endif