/**
 * Department of Computer Engineering has student's club named 'Pinnacle Club'. 
 * Students of Second, third and final year of department can be granted membership 
 * on request. Similarly one may cancel the membership of club. First node is 
 * reserved for president of club and last node is reserved for secretary of club. 
 * Write C++ program to maintain club member‘s information using singly linked 
 * list. Store student PRN and Name. Write functions to
 * a) Add and delete the members as well as president or even secretary.
 * b) Compute total number of members of club
 * c) Display members
 * d) Display list in reverse order using recursion
 * e) Two linked lists exists for two divisions. Concatenate two lists.
 * 
 * Roshan Maind    
 * (S2 - 34)
 */


#include<iostream>
#include<stdlib.h>

using namespace std;

//Globals
struct student{
    int PRN;
    string name;
    int year;
    student *next;
}*first[2], *new_mem;
student **cursor;

string temp;
int t;

//Functions
inline string getYearString(int);
int menu();
void add_beg(int);
void add_end(int);
void add(int);
int remove(string, int);
int get();
int total(int);
void display(int);
void conc();
void display_rev(student*);
inline void empty(int);

int main(){
    char buffer;
    int d;
    empty(0);
    empty(1);
    while(1){
        switch(menu()){
            case 1:
                add_beg(get());
                cout << "Addition successful\n";
                break;
            case 2:
                add_end(get());
                cout << "Addition successful\n";
                break;
            case 3:
                add(get());
                cout << "Addition successful\n";
                break;
            case 4:
                cout << "Deletion Warning: Removing the president will automatically make the oldest\nmember of the club, the new president and removing the secretary\nwill make the newest member of the club, the new secretary\n";
                cout << "Enter the name of the student whom you want to remove from the club: ";
                cin >> temp;
                cout << "Which division?\n1. A\n2. B\nSelect one: ";
                cin >> d;
                if(remove(temp, (d-1)))
                    cout << temp << " was removed.\n";
                else
                    cout << "Couldn't remove " << temp << ".\n";
                break;
            case 5:
                cout << "Which division?\n1. A\n2. B\nSelect one: ";
                cin >> d;
                cout << "The total number of students in the club is " << total(d-1) << "\n";
                break;
            case 6:
                cout << "Which division?\n1. A\n2. B\nSelect one: ";
                cin >> d;
                cout << "Club members:-\n";
                display(d-1);
                break;
            case 7:
                cout << "Which division?\n1. A\n2. B\nSelect one: ";
                cin >> d;
                if(first[d-1]==NULL){
                    cout << "Club empty!\n";
                }
                else{
                    cout << "\nPRN\tName\t\tYear\tRemarks";
                    display_rev(first[d-1]);
                    cout << "President\n";
                }
                break;
            case 8:
                cout << "Keep in mind that concatenating the two divisions will make the second division record void\n";
                conc();
                break;
            case 9:
                cout << "Thanks for using! Goodbye...\n";
                cin.ignore();
                cin.get(buffer);
                return 0;
            default:
                cout << "Wrong choice, try again\n";
                break;
        }
        cout << "Press enter to continue...";
        cin.ignore();
        cin.get(buffer);
    }
}

//Function definitions
inline string getYearString(int year) {
    switch(year){
        case 2:
            return "SE";
        case 3:
            return "TE";
        default:
            return "BE";
    }
}

int menu(){
    int ch;
    system("clear");
    cout << "Pinnacle Club Database\n";
    cout << "===================================================\n\n";
    cout << "1. Add president\n";
    cout << "2. Add secretary\n";
    cout << "3. Add other members\n";
    cout << "4. Delete member\n";
    cout << "5. Calculate total number of members in the club\n";
    cout << "6. Display club members' information\n";
    cout << "7. Display the records in reversed order\n";
    cout << "8. Concatenate two divisions\n";
    cout << "9. Exit\n";
    cout << "Your choice: ";
    cin >> ch;
    system("clear");
    return ch;
}

int get(){
    int n;
    new_mem = new student;
    cout << "Enter the name of the member: ";
    cin >> new_mem->name;
    cout << "Enter the PRN of the member: ";
    cin >> new_mem->PRN;
    do {
        cout << "Which year does the member study in (Enter 2, 3 or 4. FE students are not allowed): ";
        cin >> new_mem->year;
    } while (new_mem->year < 2 || new_mem->year > 4);
    new_mem->next = NULL;
    cout << "Which division does the member belong to?\n1. A\n2. B\nSelect one: ";
    cin >> n;
    n--;
    return n;
}

void add_beg(int x){
    if(first[x]==NULL)
        first[x] = new_mem;
    else{
        new_mem->next = first[x];
        first[x] = new_mem;
    }
}

void add_end(int x){
    if(first[x]==NULL){
        cout << "Warning: Since the club is currently empty, this member will by default be made the president\n";
        first[x] = new_mem;
    }
    else{
        cursor = &first[x];
        while(*cursor!=NULL)
            cursor = &(*cursor)->next;
        *cursor = new_mem;
    }
}

void add(int x){
    if(first[x]==NULL){
        cout << "Warning: Since the club is currently empty, this member will by default be made the president\n";
        first[x] = new_mem;
    }
    else if(first[x]->next==NULL){
        cout << "Warning: Since this is the second member of the club, he/she will by default be made the secretary\n";
        first[x]->next = new_mem;
    }
    else{
        cursor = &first[x];
        while((*cursor)->next!=NULL){
            cursor = &(*cursor)->next;
        }
        new_mem->next = *cursor;
        *cursor = new_mem;
    }
}

int remove(string s, int x){
    if(first[x]==NULL){
        cout << "Club empty!\n";
        return 0;
    }
    else{
        bool found = false;
        cursor = &first[x];
        while(*cursor!=NULL){
            if((*cursor)->name == s){
                found = true;
                break;
            }
            cursor = &(*cursor)->next;
        }
        if(found){
            *cursor = (*cursor)->next;
            return 1;
        }
    }
    cout << "There is no " << s << " in the club. Did you spell the name right?\n";
    return 0;   
}

int total(int x){
    int count = 0;
    cursor = &first[x];
    while(*cursor!=NULL){
        count++;
        cursor = &(*cursor)->next;
    }
    return count;
}

void display(int x){
    cout << "PRN\tName\t\tYear\tRemarks\n";
    cursor = &first[x];
    while((*cursor)!=NULL){
        cout << ((*cursor)->PRN) << "\t" << ((*cursor)->name) << "\t\t" << getYearString((*cursor)->year)<< "\t";
        if(*cursor==first[x])               
            cout << "President\n";
        else if((*cursor)->next==NULL)      
            cout << "Secretary\n";
        else                                
            cout << "\n";
        cursor = &(*cursor)->next;
    }
}

void conc(){
    cursor = &first[0];
    while(*cursor!=NULL){
        cursor = &(*cursor)->next;
    }
    *cursor = first[1];
    empty(1);
}

void display_rev(student *p){
    if(p->next!=NULL){
        display_rev(p->next);               //Recursion
    }
    cout << "\n" << p->PRN << "\t" << p->name << "\t\t" << getYearString(p->year)<< "\t";
    if(p->next==NULL&&(p!=first[0]&&p!=first[1]))       
        cout << "Secretary";
}

inline void empty(int x){
    first[x] = NULL;
}
