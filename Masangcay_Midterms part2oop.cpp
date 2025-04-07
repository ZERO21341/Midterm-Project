#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class Item{
    private:
    int id;
    int quantity;
    string name;
    string category;
    double price;

    public:
    Item(string n, string c, int q, double p, int i){
        this->id=i;
        this->quantity=q;
        this->name=n;
        this->category=c;
        this->price=p;
    }

    void setQuantity(int q){
        this -> quantity=q;
    }

    void setPrice(double p){
        this->price=p;
    }

    int getId(){
        return id;
    }

    int getQuantity(){
        return quantity;
    }

    string getName(){
        return name;
    }

    string getCategory(){
        return category;
    }

    double getPrice(){
        return price;
    }

    void display(){
        cout<<id<<"\t\t"<<name<<"\t\t   "<<quantity<<"\t\t\t"<<price<<"\t\t"<<category<<endl;
    }
};

vector<Item> items;
int autoID = 1;

void header(){
    cout<<"ID\t\tName\t\t\tQuantity\t\tPrice\t\tCategory"<<endl;
}

void AddItem() {
    string name, category;
    int quantity;
    float price;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter The Name Of The Product: ";
    getline(cin, name);

    cout << "Enter The Category Of The Product: ";
    getline(cin, category);

    cout << "Enter The Quantity Of The Product To Add: ";
    while (!(cin >> quantity) || quantity < 0) {
        cout << "Invalid Input. Please Enter a Whole Number Greater Than or Equal to 0: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter The Price Of The Product: ";
    while (!(cin >> price) || price < 0) {
        cout << "Invalid Input. Please Enter a Positive Price: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    inventory.push_back(Product(nextProductID++, name, quantity, price, category));

    cout << "Your Item Has Been Added Successfully!\n";
    banner();
}


void updateItem(){
    int id;
    bool ifFound = false;
    cout<<"Input item ID: ";
    cin>>id;

    for(int i = 0; i<items.size();i++){
        if(items[i].getId() == id){
            int updateItemChoice;
            cout<<"Price[1] or Quantity[2]: ";
            cin>>updateItemChoice;
            while (true){
                if (updateItemChoice == 1){
                    double oldPrice=items[i].getPrice();
                    double newPrice;

                    cout<<"New Price: ";
                    cin>>newPrice;
                    if (cin.fail() || newPrice < 0) {
                        cout << "Invalid price. Please enter a valid positive number.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        return;
                    }

                    items[i].setPrice(newPrice);
                    cout<<"Price of "<<items[i].getName()<<" is updated from "<<oldPrice<<" to "<<newPrice<<endl;
                    break;
                }
                else if (updateItemChoice == 2){
                    int oldQuantity=items[i].getQuantity();
                    int newQuantity;

                    cout<<"New Quantity: ";
                    cin>>newQuantity;
                    if (cin.fail() || newQuantity < 0) {
                        cout << "Invalid quantity. Please enter a valid positive number.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        return;
                    }

                    items[i].setQuantity(newQuantity);
                    cout<<"Quantity of "<<items[i].getName()<<" is updated from "<<oldQuantity<<" to "<<newQuantity<<endl;
                    break;
                }
                else{
                    cout<<"Invalid Input"<<endl;
                }
            }
        ifFound = true;
        break;
        }
    }
    if (!ifFound){
        cout<<"Item not found!"<<endl;
    }
}

void removeItem(){
    int id;
    bool ifFound = false;
    cout<<"Input item ID: ";
    cin>>id;

    for (int i = 0; i < items.size(); i++){
        if (items[i].getId() == id){
            cout<<"Item "<<items[i].getName()<<" has been removed from the inventory"<<endl;
            items.erase(items.begin()+i);
            ifFound = true;
            break;
        }
    }
    
    if (!ifFound){
        cout<<"Item not found!"<<endl;
    }
}

void displayAllItems(){
    header();
    for (int i = 0; i < items.size(); i++){
        items[i].display();
    }
}

void displayByID(){
    int id;
    bool ifFound = false;
    cout<<"\nInput item ID: ";
    cin>>id;

    header();
    for (int i = 0; i < items.size(); i++){
        if (items[i].getId() == id){
            items[i].display();
            ifFound = true;
            break;
        }
    }
    
    if (!ifFound){
        cout<<"\nItem not found!"<<endl;
    }
}

void displayByCategory(){
    string category;
    bool ifFound = false;
    cout<<"\nInput item Category: ";
    cin>>category;

    header();
    for (int i = 0; i < items.size(); i++){
        if (items[i].getCategory() == category){
            items[i].display();
            ifFound = true;
        }
    }
    
    if (!ifFound){
        cout<<"\nNo items found!"<<endl;
    }
}

void displaySearchItem(){
    int choice;
    
    cout<<"Search Item By:"<<endl;
    cout<<"ID[1] or Category[2]: ";
    cin>>choice;

    if (choice == 1)
    {
        displayByID();
    }
    else if(choice == 2){
        displayByCategory();
    }
    else{
        cout<<"Invalid Input"<<endl;
    }
}

void displayLowStock(){
    bool ifFound = false;
    header();
    for (int i = 0; i < items.size(); i++){
        if(items[i].getQuantity() <=5){
            items[i].display();
            ifFound=true;
        }
    }

    if (!ifFound){
        cout<<"\nItem Low Stock items found!"<<endl;
    }
}

int main() {

    int choice;

    do{
    cout<<"\n--------------------------"<<endl;
    cout<<"Menu"<<endl;
    cout<<"1 - Add Item"<<endl;
    cout<<"2 - Update Item"<<endl;
    cout<<"3 - Remove Item"<<endl;
    cout<<"4 - Display All Items"<<endl;
    cout<<"5 - Search Item"<<endl;    
    cout<<"6 - Sort Items"<<endl;
    cout<<"7 - Display Low Stock Items"<<endl;
    cout<<"8 - Exit"<<endl;
    cout<<"--------------------------"<<endl;

    cout<<"\nEnter your Choice: ";
    cin>>choice;

    if (choice == 1){
        addItem();
    }
    else if (choice == 2){
        updateItem();
    }
    else if (choice == 3){
        removeItem();
    }
    else if (choice == 4){
        displayAllItems();
    }
    else if (choice == 5){
        displaySearchItem();
    }
    else if (choice == 6){
    }
    else if (choice == 7){
        displayLowStock();
    }
    else if (choice == 8){
        cout<<"Thank you!"<<endl;
        break;
    }
    else{
        cout<<"Invalid input"<<endl;
        cout<<"Please Try Again"<<endl;
    }
    }
    while(choice !=8);
    return 0;
}