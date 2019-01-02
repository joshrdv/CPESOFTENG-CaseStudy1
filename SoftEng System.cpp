#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>

using namespace std;

struct node {
	int id, pages, prio;
	string title;
	struct node *next;
}*head = NULL;

//For set width and set separator purposes
const char separator = ' ';
const int idSetw = 9;
const int titleSetw = 34;
const int pagesSetw = 14;
const int prioritySetw = 9;

bool checkInput(char in[15], bool buff){
	int i;
	for(i=0; i<strlen(in); i++){
		if(isalpha(in[i])||ispunct(in[i])){
			cout<<"Invalid input. Please enter a whole number."<<endl;
				break;
			} 
		}
	if(i==strlen(in)) 
		buff=!(buff);
	return buff;
}

string convertSpaces(string str, char chreplace, char chment){
	for(int i=0; i<str.length(); i++){
		if(str[i]==chment) str[i] = chreplace;
	}
	return str;
}

void input_project(char* inputfile){
	system("cls");
		
	cout<<"===================================================================="<<endl;
	cout<<"||                   1. Input project details                     ||"<<endl;
	cout<<"===================================================================="<<endl;
	
	fstream myfile;
	myfile.open(inputfile);
	int id(1);
   	char pages[15], priority[15];
   	string title;
	bool buff=false;
   	
	while (myfile.getline(pages,50,'\n')) id++;
   	myfile.close();
	
	myfile.open(inputfile,ios::app);
	cout<<"Enter title of the manuscript: "; //Title
	
	cin.ignore();
	getline(cin,title);
	
	do{
		while(!buff){
			cout<<"Enter number of pages: "; //Pages
			cin>>pages;
			buff = checkInput(pages, buff);
		}
		if((atoi(pages)<50)||(atoi(pages)>500)){
			cout<<"===================================================================="<<endl;
			cout<<"||          Please enter within the range of 50 to 500.           ||"<<endl;
			cout<<"===================================================================="<<endl;
			buff = false;
		} else buff=true;
	} while(!buff);
	
	do{
		cout<<"Enter the priority of the manuscript: "; //Priority
		cin>>priority;	
		buff = checkInput(priority,buff);
	}while(buff);
	
	//Verificatiob of the data that is being input
	cout<<"+---------+----------------------------------+--------------+---------+"<<endl;
	cout<<"|";
	cout<<left<<setw(idSetw)<<setfill(separator)<<"ID";
	cout<<"|";
	cout<<left<<setw(titleSetw)<<setfill(separator)<<"Title";
	cout<<"|";
	cout<<left<<setw(pagesSetw)<<setfill(separator)<<"Pages";
	cout<<"|";
	cout<<left<<setw(prioritySetw)<<setfill(separator)<<"Priority";
	cout<<"|"<<endl;
	cout<<"+---------+----------------------------------+--------------+---------+"<<endl;
	
	//The data itself
	cout<<"|";
	cout<<left<<setw(idSetw)<<setfill(separator)<<id;
	cout<<"|";
	cout<<left<<setw(titleSetw)<<setfill(separator)<<title;
	cout<<"|";
	cout<<left<<setw(pagesSetw)<<setfill(separator)<<pages;
	cout<<"|";
	cout<<left<<setw(prioritySetw)<<setfill(separator)<<priority;
	cout<<"|"<<endl;
	cout<<"+---------+----------------------------------+--------------+---------+"<<endl<<endl;
	
	cout<<"===================================================================="<<endl;
	cout<<"||               Placing inputs done successfully!                ||"<<endl;
	cout<<"===================================================================="<<endl;
	title = convertSpaces(title, '_', ' ');

	myfile<<id<<"\t"<<title<<"\t"<<pages<<"\t"<<priority<<"\n"; //enter into file
	myfile.close();
	
}

void view_project_a(char* inputfile){
	system("cls");
	
	ifstream myfile;
	
	int id,pages,priority;
	char searchId[15];
	string title;
	bool buff=true;

	cout<<"============================"<<endl;
	cout<<"|| Search for one project ||"<<endl;
	cout<<"============================"<<endl;
	do{
		cout<<"Enter the ID for the manuscript: ";
		cin>>searchId;
		buff = checkInput(searchId,buff);	
	}while(buff);
	
	myfile.open(inputfile);
	
	while (myfile>>id>>title>>pages>>priority){
		if(atoi(searchId)==id){ //Compares the ID number placed by the user to the ID numbers present in the text file
			buff=false; 
			break; //Reading stops
		}else{
			buff=true;
		}
	}
	title = convertSpaces(title,' ','_');
	
	if(!buff){
		//For the title bar
		cout<<"+---------+----------------------------------+--------------+---------+"<<endl;
		cout<<"|";
		cout<<left<<setw(idSetw)<<setfill(separator)<<"ID";
		cout<<"|";
		cout<<left<<setw(titleSetw)<<setfill(separator)<<"Title";
		cout<<"|";
		cout<<left<<setw(pagesSetw)<<setfill(separator)<<"Pages";
		cout<<"|";
		cout<<left<<setw(prioritySetw)<<setfill(separator)<<"Priority";
		cout<<"|"<<endl;
		cout<<"+---------+----------------------------------+--------------+---------+"<<endl;
		//The data itself
		cout<<"|";
		cout<<left<<setw(idSetw)<<setfill(separator)<<id;
		cout<<"|";
		cout<<left<<setw(titleSetw)<<setfill(separator)<<title;
		cout<<"|";
		cout<<left<<setw(pagesSetw)<<setfill(separator)<<pages;
		cout<<"|";
		cout<<left<<setw(prioritySetw)<<setfill(separator)<<priority;
		cout<<"|"<<endl;
		cout<<"+---------+----------------------------------+--------------+---------+"<<endl;		
	}
	else{
		cout<<"============================"<<endl;
		cout<<"||       NOT FOUND!       ||"<<endl;
		cout<<"============================"<<endl;
	}
	system("pause>0");
	system("cls");
	myfile.close();
}

void display_sched(char* schedfile) {
	struct node * r = head;
	if (r == NULL) {
  		cout << "No shit for youuu";
   		return;
  	}
	
	fstream fout; 	
	fout.open(schedfile, ios::out);
	
	cout<<"ID"<<"\t"<<"TITLE"<<"\t"<<"PAGES"<<"\t"<<"PRIORITY"<<"\n"; //output receipt
	while (r != NULL) {
		cout<<r->id<<"\t"<<r->title<<"\t"<<r->pages<<"\t"<<r->prio<<"\n";
		r->title = convertSpaces(r->title,'_',' ');
		fout<<r->id<<"\t"<<r->title<<"\t"<<r->pages<<"\t"<<r->prio<<"\n";
    	r = r -> next;
	}
	fout.close();
}

void deleteNodes(){
	node *deln = new node();
	deln = head;
	while(deln != NULL){
		head = deln->next;
		delete deln;
		deln = head;
	}
	delete head;
}

void addNode(int id, string title, int pages, int pr) {
    node *temp = new node(); 
    node *here = new node();
	
	temp->id = id;
    temp->title= title;
    temp->pages= pages;
	temp->prio= pr; 
    temp->next = NULL; 
 	
	if (head==NULL){
 		head = temp;
 	} else if (head->prio > pr || (head->prio==pr)&&(head->pages>pages)){
		temp->next = head;
		head = temp;
	} else {
		here = head;
		while(here->next!=NULL && (here->next)->prio < pr) 
			here = here->next;	
		while(here->next!=NULL && (here->next)->prio == pr && pages>(here->next)->pages)
			here=here->next;
		temp->next = here->next;
		here->next = temp;
	}
}

void create_sched(char* inputfile){
	fstream myfile(inputfile);
	int id, pages, prio;
	string title;
	
	fstream cfile;
	int idc, pagesc, prioc;
	string titlec;
	deleteNodes();
	if(cfile){
		while(myfile >> id >> title >> pages >> prio){
			bool buff = true;
			cfile.open("completedlist.txt");
			while(cfile>> idc >> titlec >> pagesc >> prioc){
				if (id==idc) buff=false;
			}
			if(buff){
				title = convertSpaces(title,' ','_');
				addNode(id,title,pages,prio);	
			}
			cfile.close();
		}
	}
	
	display_sched("sched.txt");	
	myfile.close();
	system("pause>0");
}

void view_file(char* schedfile){
	system("cls");
	
	fstream thisfile;
	
	int id,pages,priority;
	string title;
	
	thisfile.open(schedfile);

	cout<<"============================"<<endl;
	cout<<"||      All projects      ||"<<endl;
	cout<<"============================"<<endl;
	
	//For the title bar
	cout<<"+---------+----------------------------------+--------------+---------+"<<endl;
	cout<<"|";
	cout<<left<<setw(idSetw)<<setfill(separator)<<"ID";
	cout<<"|";
	cout<<left<<setw(titleSetw)<<setfill(separator)<<"Title";
	cout<<"|";
	cout<<left<<setw(pagesSetw)<<setfill(separator)<<"Pages";
	cout<<"|";
	cout<<left<<setw(prioritySetw)<<setfill(separator)<<"Priority";
	cout<<"|"<<endl;
	cout<<"+---------+----------------------------------+--------------+---------+"<<endl;
	while (thisfile>>id>>title>>pages>>priority){
		title = convertSpaces(title,' ','_');
		cout<<"|";
		cout<<left<<setw(idSetw)<<setfill(separator)<<id;
		cout<<"|";
		cout<<left<<setw(titleSetw)<<setfill(separator)<<title;
		cout<<"|";
		cout<<left<<setw(pagesSetw)<<setfill(separator)<<pages;
		cout<<"|";
		cout<<left<<setw(prioritySetw)<<setfill(separator)<<priority;
		cout<<"|"<<endl;
		cout<<"+---------+----------------------------------+--------------+---------+"<<endl;
	}		
	system("pause>0");
	system("cls");
	thisfile.close();
}

void get_project(){
	fstream myfile("sched.txt");
	int id, pages, prio;
	string title;
	
	fstream cfile("completedlist.txt",ios::app);

	if(myfile){
		while(myfile >> id >> title >> pages >> prio){
			title = convertSpaces(title,' ','_');
			addNode(id,title,pages,prio);
		}
	}

	node *temp = new node();
	temp = head;
	head = head->next;
	cfile<<temp->id<<'\t'<<temp->title<<'\t'<<temp->pages<<'\t'<<temp->prio<<endl;
	cout <<temp->id<<temp->title<<temp->pages<<temp->prio;
	
	display_sched("sched.txt");
	cfile.close();
	myfile.close();
	free(temp);
	system("pause>0");
}

int main(){
	string choice;
	bool buff=true;
	while(1){
		system("cls");
		cout<<"======================================="<<endl;
		cout<<"||         M A I N   M E N U         ||"<<endl;
		cout<<"======================================="<<endl;
		cout<<"|| 1 || Input project details        ||"<<endl;
		cout<<"======================================="<<endl;
		cout<<"|| 2 || View projects                ||"<<endl;
		cout<<"======================================="<<endl;
		cout<<"|| 3 || Schedule projects            ||"<<endl;
		cout<<"======================================="<<endl;
		cout<<"|| 4 || Get a project                ||"<<endl;
		cout<<"======================================="<<endl;
		cout<<"|| 5 || Exit                         ||"<<endl;
		cout<<"======================================="<<endl;
		cout<<"Enter option: ";
		cin>>choice;
		if(choice.length()>1) choice = "z";
		switch(choice[0]){
			case '1': input_project("inputs.txt"); break;
			case '2': 
				while(buff){
					system("cls");
					cout<<"======================================="<<endl;
					cout<<"||         2. View projects          ||"<<endl;
					cout<<"======================================="<<endl;
					cout<<"|| A || One project                  ||"<<endl;
					cout<<"======================================="<<endl;
					cout<<"|| B || Completed projects           ||"<<endl;
					cout<<"======================================="<<endl;
					cout<<"|| C || All projects                 ||"<<endl;
					cout<<"======================================="<<endl;
					cout<<"|| X || Return to menu               ||"<<endl;
					cout<<"======================================="<<endl;
					cout<<"Enter option: ";
					cin>>choice;
					if(choice.length()>1) choice = "z";
					switch(choice[0]){
						case 'A':
						case 'a': view_project_a("inputs.txt"); break;
						case 'B':
						case 'b': view_file("completedlist.txt"); break;
						case 'C':
						case 'c': view_file("inputs.txt"); break;
						case 'X':
						case 'x': buff=false; break;
						default: break;
					}	
				} buff=true; break;
			case '3': 
				while(buff){
					system("cls");
					cout<<"======================================="<<endl;
					cout<<"||       3. Schedule projects        ||"<<endl;
					cout<<"======================================="<<endl;
					cout<<"|| A || Create new schedule          ||"<<endl;
					cout<<"======================================="<<endl;
					cout<<"|| B || View schedule                ||"<<endl;
					cout<<"======================================="<<endl;
					cout<<"|| X || Return to menu               ||"<<endl;
					cout<<"======================================="<<endl;
					cout<<"Enter option: ";
					cin>>choice;
					if(choice.length()>1) choice = "z";
					switch(choice[0]){
						case 'A':
						case 'a': create_sched("inputs.txt"); break;
						case 'B':
						case 'b': view_file("sched.txt"); break;
						case 'X':
						case 'x': buff=false; break;
						default: break;
					}
				} buff = true; break;
			case '4': get_project(); break;
			case '5': exit(0);
			default: 
				cout<<"============================"<<endl;
				cout<<"||     Wrong input!       ||"<<endl;
				cout<<"============================"<<endl;
		}
		cout<<"----\nPress any key to continue.";
		system("pause>0");
	}
	return 0;	
}
