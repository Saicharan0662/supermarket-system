#include<iostream>
#include<cstring>
#include<fstream>

using namespace std;

class Shop{
	int prod_code;
	float prod_price, discount;
	string prod_name;
	
	public:
		void menu();
		void administrator();
		void buyer();
		void addProduct();
		void receipt();
		void editProduct();
		void displayProduct();
		void removeProduct();
};

void Shop :: menu(){
	top:
	int choice;
	string email, password;
	
	cout<<"\t\t\t\t______________________________________"<<endl;
	cout<<"\t\t\t\t                                      "<<endl;
	cout<<"\t\t\t\t         Super Market Main Menu       "<<endl;
	cout<<"\t\t\t\t                                      "<<endl;
	cout<<"\t\t\t\t______________________________________"<<endl;
	cout<<"\t\t\t\t                                      "<<endl;
	
	cout<<"\t\t\t\t|      1. Administrator  |"<<endl;
	cout<<"\t\t\t\t|      2. Buyer          |"<<endl;
	cout<<"\t\t\t\t|      3. Exit           |"<<endl;
	
	cout<<"Please Select your identity..."<<endl;
	cin>>choice;
	
	switch(choice){
		case 1:{
			cout<<"\t\t\t\t Signing as administrator!"<<endl;
			cout<<"\t\t\t\t Please enter your email..."<<endl;
			cin>>email;
			cout<<"\t\t\t\t Please enter your password..."<<endl;
			cin>>password;
			if(email == "admin@gmail.com" && password == "admin@pass") administrator();
			else cout<<"\t\t\t\t Invalid Credentials"<<endl;
			break;
		}
		case 2:{
			buyer();
			break;
		}
		case 3: {
			exit(0);
			break;
		}
		default :{
			cout<<"Please select valid options!";
			break;
		}
	}
	
	goto top;
}

void Shop :: administrator(){
	top:
	int choice;
	
	cout<<"\t\t\t\tAdministrator Pannel"<<endl;
	cout<<"\t\t\t\t|      1. Add a product     |"<<endl;
	cout<<"\t\t\t\t|      2. Edit a product    |"<<endl;
	cout<<"\t\t\t\t|      3. Remove a product  |"<<endl;
	cout<<"\t\t\t\t|      4. Back to main menu |"<<endl;
	
	cout<<"Please enter your choice"<<endl;
	cin>>choice;
	
	switch(choice){
		case 1:{
			addProduct();
			break;
		}
		case 2:{
			editProduct();
			break;
		}
		case 3:{
			removeProduct();
			break;
		}
		case 4:{
			menu();
			break;
		}
		default :{
			cout<<"Please select valid options!";
			break;
		}
	}
	
	goto top;
}

void Shop :: buyer(){
	top:
	int choice;
	
	cout<<"\t\t\t\tBuyer Pannel"<<endl;
	cout<<"\t\t\t\t|      1. Buy Product |"<<endl;
	cout<<"\t\t\t\t|      2. Go back     |"<<endl;
	cout<<"Please enter your choice"<<endl;
	cin>>choice;
	
	switch(choice){
		case 1: {
			receipt();
			break;
		}
		case 2:{
			menu();
			break;
		}
		default:{
			cout<<"Please select valid options!";
			break;
		}
	}
	goto top;
}

void Shop :: addProduct(){
	top:
	fstream data;
	int code;
	bool isPresetnt = false;
	float price, dis;
	string name;
	
	cout<<"\t\t\t\tAdd a new product"<<endl;
	cout<<"Code of the product"<<endl;
	cin>>prod_code;
	cout<<"Name of the product"<<endl;
	cin>>prod_name;
	cout<<"Price of the product"<<endl;
	cin>>prod_price;
	cout<<"Discount on product"<<endl;
	cin>>discount;
	
	data.open("database.txt", ios::in);
	if(!data){
		data.open("database.txt", ios::app | ios::out);
		data<<" "<<prod_code<<" "<<prod_name<<" "<<prod_price<<" "<<discount<<"\n";
		data.close();
	}
	else{
		data>>code>>name>>price>>dis;
		while(!data.eof()){
			if(code == prod_code) isPresetnt = true;
			data>>code>>name>>price>>dis;
		}
		
		data.close();
		if(isPresetnt){
			cout<<"Product with code: "<<prod_code<<" allready exist. Please enter another code."<<endl;
			goto top;
		}
		else{
			data.open("database.txt", ios::app | ios::out);
			data<<" "<<prod_code<<" "<<prod_name<<" "<<prod_price<<" "<<discount<<"\n";
			data.close();
		}
	}
}

void Shop :: editProduct(){
	fstream data1, data2;
	int key;
	int code;
	bool isPresent = false;
	float price, dis;
	string name;
	
	cout<<"\t\t\t\tModify a product"<<endl;
	cout<<"Code of the product"<<endl;
	cin>>key;
	
	data1.open("database.txt", ios::in);
	if(!data1) cout<<"File dosent exist."<<endl;
	else{
		data2.open("database1.txt", ios::app | ios::out);
		data1>>prod_code>>prod_name>>prod_price>>discount;
		while(!data1.eof()){
			if(key == prod_code){
				cout<<"New code for the product: "<<endl;
				cin>>code;
				cout<<"New name for the product: "<<endl;
				cin>>name;
				cout<<"New price of the product: "<<endl;
				cin>>price;
				cout<<"New disount on the product: "<<endl;
				cin>>dis;
				data2<<" "<<code<<" "<<name<<" "<<price<<" "<<dis<<"\n";
				cout<<"\t\t\t\tRecord edited!"<<endl;
				isPresent = true;
			}
			else{
				data2<<" "<<prod_code<<" "<<prod_name<<" "<<prod_price<<" "<<discount<<"\n";
			}
			data1>>prod_code>>prod_name>>prod_price>>discount;
		}
		data1.close();
		data2.close();
		
		remove("database.txt");
		rename("database1.txt", "database.txt");
		
		if(!isPresent) cout<<"Record not fount."<<endl;
	}
}

void Shop :: removeProduct(){
	fstream data1, data2;
	int key;
	bool isPresent = false;
	
	cout<<"\t\t\t\tDelete a product."<<endl;
	cout<<"Enter a product code."<<endl;
	cin>>key;
	
	data1.open("database.txt", ios::in);
	if(!data1) cout<<"File dosent exist."<<endl;
	else{
		data2.open("database1.txt", ios::app | ios::out);
		data1>>prod_code>>prod_name>>prod_price>>discount;
		while(!data1.eof()){
			if(key == prod_code){
				cout<<"Product deleted succesfuly!"<<endl;
				isPresent = true;
			}
			else{
				data2<<" "<<prod_code<<" "<<prod_name<<" "<<prod_price<<" "<<discount<<"\n";
			}
			data1>>prod_code>>prod_name>>prod_price>>discount;
		}
		data1.close();
		data2.close();
		remove("database.txt");
		rename("database1.txt", "database.txt");
		
		if(!isPresent) cout<<"Record not fount."<<endl;
	}
}

void Shop :: displayProduct(){
	fstream data;
	
	data.open("database.txt", ios::in);
	cout<<"\n__________________________________\n";
	cout<<"Code\t\tName\t\tPrice"<<endl;
	cout<<"\n__________________________________\n";
	data>>prod_code>>prod_name>>prod_price>>discount;
	while(!data.eof()){
		cout<<prod_code<<"\t\t"<<prod_name<<"\t\t"<<prod_price<<endl;
		data>>prod_code>>prod_name>>prod_price>>discount;
	}
	
	data.close();
}

void Shop :: receipt(){
	top:
	fstream data;
	int goods[100];
	int quantity[100];
	int count;
	char choice;
	float amount = 0, dis = 0, total = 0;
	
	cout<<"\t\t\t\tRECEIPT"<<endl;
	data.open("database.txt", ios::in);
	if(!data){
		cout<<"\n\n No products found."<<endl;
	}
	else{
		data.close();
		displayProduct();
		cout<<"\n___________________________________\n";
		cout<<"\n       Please place the order      \n";
		cout<<"\n___________________________________\n";
		
		do{
			cout<<"Enter product code: "<<endl;
			cin>>goods[count];
			cout<<"Enter the product quantity: "<<endl;
			cin>>quantity[count];
			
			for(int i=0; i<count; i++){
				if(goods[count] == goods[i]){
					cout<<"Duplicate entry, please select different product."<<endl;
					goto top;
				}
			}
			count++;
			cout<<"Press y to purchase another product and x to finish shoping."<<endl;
			cin>>choice;
		}while(choice == 'y');
		
		cout<<"\n___________________________________\n";
		cout<<"\n              RECEIPT              \n";
		cout<<"\n___________________________________\n";
		cout<<"\nProduct no.\t Name\t\t Price\t Amount\t Amount with discount"<<endl;
		
		for(int i=0; i<count; i++){
			data.open("database.txt", ios::in);
			data>>prod_code>>prod_name>>prod_price>>discount;
			while(!data.eof()){
				if(prod_code == goods[i]){
					amount = prod_price*goods[i];
					dis = amount - amount * (discount/100);
					total += dis;
					cout<<prod_code<<"\t\t "<<prod_name<<"\t "<<prod_price<<"\t "<<amount<<"\t "<<dis<<endl;
				}
				data>>prod_code>>prod_name>>prod_price>>discount;
			}
			data.close();
		}
	}
	
	cout<<"Total Amount: "<<total<<endl;
	cout<<"__________________________________"<<endl;
}


int main(){
	
	Shop sh;
	sh.menu();
	
	return 0;
}
