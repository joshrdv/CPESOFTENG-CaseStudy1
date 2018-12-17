#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

struct node {
	int id, pages, priority;
	char title[100];
	struct node * next;
} *head;

//INSERT FUNCTIONS HERE!!!
void input_project(){
	system("cls");
	cout << "ENTER A PROJECT" << endl;
	
	fstream myfile;
	int id(1),pages(50),priority;
	char c,title[100];
	
	myfile.open("inputs.txt");
   	while (myfile) {
    	while (myfile && c != '\n') {
       		myfile.get(c);
     	}
		id++;
		myfile.get(c);
   	}
   	myfile.close();
	myfile.open("inputs.txt",ios::app);
	cout<<"Enter title of the manuscript: "; //Title
	cin>>title;
	while((pages>=50)||(pages<=500)){
		cout<<"Enter number of pages: "; //Pages
		cin>>pages;
		if(pages<50||pages>500) cout<<"The pages of the manuscript exceeds the given range."<<endl;
		else break;
	}
	cout<<"Enter the priority of the manuscript: "; //Priority
	cin>>priority;
	myfile<<id<<"\t"<<title<<"\t"<<pages<<"\t"<<priority<<"\n";
	myfile.close();
	
	cout<<"ID"<<"\t"<<"TITLE"<<"\t"<<"PAGES"<<"\t"<<"PRIORITY"<<"\n";
	cout<<id<<"\t"<<title<<"\t"<<pages<<"\t"<<priority<<"\n";
	cout<<"\nPlacing inputs done successfully!\n";
}

void view_project_a(){
	system("cls");

	int id,pages,priority,searchId;
	char title[100];
	bool buff=true;

	cout<<"Search for one project"<<endl;
	cout<<"Enter the ID for the manuscript: ";
	cin>>searchId;
	
	ifstream infile("inputs.txt");
	
	while (infile>>id>>title>>pages>>priority){
		if(searchId==id){
			buff=false;
			break;
		}
	}
	if(!buff) cout<<"ID: "<<id<<"\tTITLE: "<<title<<"\tPAGES: "<<pages<<"\tPRIORITY: "<<priority<<endl;
	else cout<<"NOT FOUND!";
	infile.close();
}

int main(){
	char choice;
	bool buff=true;
	while(1){
		system("cls");
		cout<<"Main menu: "<<endl;
		cout<<"[1] Input Project Details"<<endl;
		cout<<"[2] View Projects"<<endl;
		cout<<"[3] Schedule Projects"<<endl;
		cout<<"[4] Get a Project"<<endl;
		cout<<"[5] Exit"<<endl;
		cout<<"Enter option: ";
		cin>>choice;
		switch(choice){
			case '1': input_project(); break;
			case '2': 
				while(buff){
					system("cls");
					cout<<"[a] One Project"<<endl;
					cout<<"[b] Completed Projects"<<endl;
					cout<<"[c] All Projects"<<endl;
					cout<<"[x] Back"<<endl;
					cout<<"Enter option: ";
					cin>>choice;
					switch(choice){
						case 'A':
						case 'a': view_project_a(); buff=false; break;
						case 'B':
						case 'b': /*insert function here*/break;
						case 'C':
						case 'c': /*insert function here*/break;
						case 'X':
						case 'x': buff=false; break;
						default: break;
					}
				} buff=true; break;
			case '3': 
				while(buff){
					system("cls");
					cout<<"[a] Create Schedule"<<endl;
					cout<<"[b] View Schedule"<<endl;
					cout<<"[x] Back"<<endl;
					cout<<"Enter option: ";
					cin>>choice;
					switch(choice){
						case 'A':
						case 'a': /*insert function here*/ break;
						case 'B':
						case 'b': /*insert function here*/ break;
						case 'X':
						case 'x': buff=false; break;
						default: break;
					} 
				} buff = true; break;
			case '4': /*insert function here*/ break;
			case '5': exit(0);
			default: cout<<"Wrong Input. Try again.\n"; break;
		}
		cout<<"----\nPress any key to continue.";
		system("pause>0");
	}
	return 0;	
}
