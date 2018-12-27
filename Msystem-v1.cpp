/*This program is called the copy typing management system
This program functions as a allows them to organize and to manage the documents that should be typed in a certain time span; 
and allows them to store the projects or documents that was or is currently being typed.
*/
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
void input_project(){ //This function is where placing the inputs of the manuscript happens including the name, page, and the priority
	fstream myfile;
	int id(1),pages(50),priority;
	char c,title[100];
	
	system("cls");
	cout << "ENTER A PROJECT" << endl;

	//This part is where the auto-incrementation of the ID number happens based on the number of lines in the text file (inputs.txt)	
	myfile.open("inputs.txt");
   	while (myfile) {
    	while (myfile && c != '\n') {
       		myfile.get(c);
     	}
		id++;
		myfile.get(c);
   	}
   	myfile.close();
	myfile.open("inputs.txt",ios::app); //As new information is being added, it will be placed automatically below at the current end of file
	
	//Enter title for the manuscript
	cout<<"Enter title of the manuscript: ";
	cin.ignore(); //this command skips the characters in the input stream buffer
	cin.getline(title,100); //this command allows the user to enter sentences with white spaces
	
	//Enter pages of the manuscript
	while((pages>=50)||(pages<=500)){
		cout<<"Enter number of pages: ";
		cin>>pages; //Enter the number of pages
		if(pages<50||pages>500) cout<<"The pages of the manuscript exceeds the given range."<<endl; //should only be limited from 50-500 pages
		else break;
	}
	
	//Enter priority of the manuscript
	cout<<"Enter the priority of the manuscript: "; //Priority
	cin>>priority;
	
	//Place the information in the inputs.txt file	
	myfile<<id<<"\t"<<title<<"\t"<<pages<<"\t"<<priority<<"\n";
	myfile.close();
	
	//Display the information for confirmation
	cout<<"ID"<<"\t"<<"TITLE"<<"\t"<<"PAGES"<<"\t"<<"PRIORITY"<<"\n";
	cout<<id<<"\t"<<title<<"\t"<<pages<<"\t"<<priority<<"\n";
	cout<<"\nPlacing inputs done successfully!\n";
}

void view_project_a(){ //This function is where searching for the specific manuscript takes place
	system("cls");

	int id,pages,priority,searchId;
	char title[100];
	bool buff=true;
	
	//The user enters the ID number to find the specific manuscript
	cout<<"Search for one project"<<endl;
	cout<<"Enter the ID for the manuscript: ";
	cin>>searchId;
	
	//Opens the file "inputs.txt"
	ifstream infile("inputs.txt");
	
	//Reads all of the data present in the text file
	while (infile>>id>>title>>pages>>priority){
		if(searchId==id){ //Compares the ID number placed by the user to the ID numbers present in the text file
			buff=false; 
			break; //Reading stops
		}
	}
	if(!buff) cout<<"ID: "<<id<<"\tTITLE: "<<title<<"\tPAGES: "<<pages<<"\tPRIORITY: "<<priority<<endl; //If found, it displays the information from the text file that corresponds to its ID number
	else cout<<"NOT FOUND!"; //otherwise, not found
	infile.close();
}
void view_project_b(){
	system("cls");
	
	//Declarations subject to change
	int id,pages,priority;
	char title[100];
	
	//Opens the file "completed.txt"
	ifstream infile("completed.txt");
	
	//Reads all of the data present in the text file where the projects are completed
	cout<<"Completed projects"<<endl;
	cout<<"ID"<<"\t"<<"Title"<<"\t"<<"Pages"<<"\t"<<"Priority"<<endl;
	while(infile>>id>>title>>pages>>priority) //Reads the entire file
		cout<<id<<"\t"<<title<<"\t"<<pages<<"\t"<<priority<<endl; //Displays all the existing manuscripts being placed by the user
		
	infile.close();	
}
void view_project_c(){ //This function is where the viewing of all existing manuscripts takes place
	system("cls");
	
	int id,pages,priority;
	char title[100];
	
	//Opens the file
	ifstream infile("inputs.txt");
	
	//Display all existing manuscripts in text file
	cout<<"All projects"<<endl;
	cout<<"ID"<<"\t"<<"Title"<<"\t"<<"Pages"<<"\t"<<"Priority"<<endl;
	while(infile>>id>>title>>pages>>priority) //Reads the entire file
		cout<<id<<"\t"<<title<<"\t"<<pages<<"\t"<<priority<<endl; //Displays all the existing manuscripts being placed by the user
	
	infile.close();
}

//The main menu of the program
int main(){
	char choice; 
	bool buff=true; //used to exit the existing loops once the part of the menu is being accessed
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
			case '1': input_project(); break; //the function of placing inputs is being accessed
			case '2': 
				while(buff){ //also read as while(buff==true)
					system("cls");
					cout<<"[a] One Project"<<endl;
					cout<<"[b] Completed Projects"<<endl;
					cout<<"[c] All Projects"<<endl;
					cout<<"[x] Back"<<endl;
					cout<<"Enter option: ";
					cin>>choice;
					switch(choice){
						case 'A':
						case 'a': view_project_a(); buff=false; break; //viewing of specific project is being accessed
						case 'B':
						case 'b': view_project_b(); buff=false; break; //viewing of completed projects is being accessed
						case 'C':
						case 'c': view_project_c(); buff=false; break; //viewing of all projects is being accessed
						case 'X':
						case 'x': buff=false; break; //to return back to main menu
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
