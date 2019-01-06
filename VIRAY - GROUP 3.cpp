// CPESOFTENG E41
// GROUP DALIRE ; DE VERA ; GADONG ; VIRAY
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <windows.h>
#include <iomanip>
using namespace std;

//Data structure for linked list, used for sorting
struct node {
	int id, pages, prio;
	string title;
	struct node *next;
}*head = NULL;

char * inputsFileName = "viray_inputs.txt";
char * completedFileName = "viray_completedlist.txt";
char * scheduleFileName = "viray_sched.txt";

//To make outputs readable
const char separator = ' ';
const int idSetw = 6;
const int titleSetw = 32;
const int pagesSetw = 7;
const int prioritySetw = 10;
const int statusSetw = 9;

void design(char dis,int iterate){
	for(int i=0; i<iterate; i++) cout<<dis;
}
int prompt(string displayS){
	design(' ',9);cout<<char(201); design(205,40); cout<<char(187)<<endl;
	design(' ',9);cout<<char(186); cout<<displayS<<char(186)<<endl;
	design(' ',9);cout<<char(200); design(205,40); cout<<char(188)<<endl;
}
//function used to validate if there are character other than numbers, meant for inputs that needs an integer
//characters are used for integer needed inputs for easy validation
bool checkInput(char in[15], bool buff){
	int i;
	for(i=0; i<strlen(in); i++){
		if(isalpha(in[i])||ispunct(in[i])){
			prompt("   INVALID INPUT:ENTER A WHOLE NUMBER   ");
			break;
			} 
		}
	if(i==strlen(in)) buff=!(buff);
	return buff;
}
//function that converts a specified character in a string into alternate an characters depending on parameter
//used mainly for converting whitespaces into a character for easy file reading
string convertSpaces(string str, char chreplace, char chment){
	for(int i=0; i<str.length(); i++)
		if(str[i]==chment) str[i] = chreplace;
	return str;
}
// function that checks if the file specified in the parameter is empty
bool isFileEmpty(char* checkFile){
	fstream sched(checkFile);
	string check;
	sched >> check;
	return (check=="");
}
//Checks if string input consists of only whitespaces
bool checkInput(string inChArr, char ch){
	int count=0;
	for(int i=0; i<inChArr.length(); i++){
		if(inChArr[i]==ch)count++;
	}
	if(ch==' '&&count==inChArr.length()){
		prompt(" ERROR: TITLE ONLY CONTAINS WHITESPACES ");
		return (true);	
	} 
	else if(ch=='\t'&&(count>0)){
		prompt("ERROR: TITLE SHOULD NOT CONTAIN TAB|'\\t'");
		return(true);	
	}else return(false);
}
//function used for Input Project
void input_project(char* inputfile){
	system("cls");		
	prompt("            INPUT MANUSCRIPT            ");
	
	fstream myfile;
	int id(1);
   	char pages[15], priority[15];
   	string title="";
	bool buff=false;
   	
   	myfile.open(inputfile); //used to get the current ID number
	while (myfile.getline(pages,50,'\n')) id++; 
   	myfile.close();
	
	myfile.open(inputfile,ios::app); // open inputs.txt
	cin.ignore();
	while(title==""||checkInput(title,'\t')||checkInput(title,' ')){	//Checks if inputed title is only whitespace or blank
		design(' ',6);cout<<"Enter Title "<<char(174)<<" ";
		getline(cin,title);	
	}
	do{
		while(!buff){
			design(' ',6);cout<<"Enter # of Page/s  "<<char(174)<<" "; // gets page size
			cin>>pages;
			buff = checkInput(pages, buff); //validates if there are alpha characters in the string
		}
		if((atoi(pages)<50)||(atoi(pages)>500)){ //validates if size is in range
			prompt("      PAGE LIMIT: 50 to 500 PAGES       ");
			buff = false;
		} else buff=true;
	} while(!buff);
	do{
		design(' ',6);cout<<"Enter # of Priority  "<<char(174)<<" "; //Priority
		cin>>priority;	
		buff = checkInput(priority,buff);
	} while(buff);
	
	//Verification of the data that is being input
	cout<<char(214);design(196,6);cout<<char(194);design(196,32);cout<<char(194);design(196,7);cout<<char(194);design(196,10);cout<<char(183)<<endl;
	cout<<char(186);design(' ',4);cout<<"ID"<<char(179);
	design(' ',13);cout<<"TITLE";design(' ',14);cout<<char(179);
	cout<<" PAGES "<<char(179)<<" PRIORITY "<<char(186)<<endl;
	cout<<char(199);design(196,6);cout<<char(197);design(196,32);cout<<char(197);design(196,7);cout<<char(197);design(196,10);cout<<char(182)<<endl;

	cout<<char(186)<<right<<setw(idSetw)<<setfill(separator)<<id<<char(179);
	cout<<left<<setw(titleSetw)<<setfill(separator)<<title<<char(179);
	cout<<left<<setw(pagesSetw)<<setfill(separator)<<pages<<char(179);
	cout<<left<<setw(prioritySetw)<<setfill(separator)<<priority<<char(186)<<endl;
	cout<<char(199);design(196,6);cout<<char(193);design(196,32);cout<<char(193);design(196,7);cout<<char(193);design(196,10);cout<<char(182)<<endl;
	cout<<char(186);design(' ',16);cout<<"INPUTS PLACED SUCCESSFULLY";design(' ',16);cout<<char(186)<<endl;
	cout<<char(211);design(196,58);cout<<char(189)<<endl<<endl;
	
	title = convertSpaces(title, '|', ' ');
	myfile<<id<<"\t"<<title<<"\t"<<pages<<"\t"<<priority<<"\n"; //enter into inputs.txt file
	myfile.close();	
}
//Function for View Project: One Project
void view_project_a(){
	system("cls");
	if(isFileEmpty(inputsFileName)){ //checks if file is empty
		prompt("         NO PROJECTS LISTED YET         ");
		system("pause>0");
		return;
	}
	ifstream myfile;
	int id,pages,priority;
	char searchId[15];
	string title;
	bool buff=true;

	prompt("          SEARCH FOR A PROJECT          ");
	do{
		design(' ',10);cout<<"Enter the ID# of the Manuscript  "<<char(174)<<" ";
		cin>>searchId;
		buff = checkInput(searchId,buff);
		if((atoi(searchId))<=0){ //validates if size is in range
			prompt("   ENTER A NUMBER GREATER THAN ZERO(0)  ");
			buff = true;
		} else buff=false;
	} while(buff);
	
	myfile.open(inputsFileName);	
	while (myfile>>id>>title>>pages>>priority){	//search inputs.txt for specified ID
		if(atoi(searchId)==id){ //Compares the ID number placed by the user to the ID numbers present in the text file
			buff=false; break; //Reading stops
		}else buff=true;
	}
	title = convertSpaces(title,' ','|');
	if(!buff){
		//DISPLAYS CONTENT OF SPECIFIED ID
		cout<<char(214);design(196,6);cout<<char(194);design(196,32);cout<<char(194);design(196,7);cout<<char(194);design(196,10);cout<<char(183)<<endl;
		cout<<char(186);design(' ',4);cout<<"ID"<<char(179);
		design(' ',13);cout<<"TITLE";design(' ',14);cout<<char(179);
		cout<<" PAGES "<<char(179)<<" PRIORITY "<<char(186)<<endl;
		cout<<char(199);design(196,6);cout<<char(197);design(196,32);cout<<char(197);design(196,7);cout<<char(197);design(196,10);cout<<char(182)<<endl;

		cout<<char(186)<<right<<setw(idSetw)<<setfill(separator)<<id<<char(179);
		cout<<left<<setw(titleSetw)<<setfill(separator)<<title<<char(179);
		cout<<left<<setw(pagesSetw)<<setfill(separator)<<pages<<char(179);
		cout<<left<<setw(prioritySetw)<<setfill(separator)<<priority<<char(186)<<endl;
		cout<<char(211);design(196,6);cout<<char(193);design(196,32);cout<<char(193);design(196,7);cout<<char(193);design(196,10);cout<<char(189)<<endl;
	} else prompt("               NOT FOUND                ");
	system("pause>0");
	myfile.close();
}
//displays the created schedule
void display_sched(char* schedfile) {
	struct node * r = head;
	if (r == NULL) {
  		prompt("          NO SCHEDULE CREATED           ");
  		system("cls");
   		return;
  	}
	fstream fout; 	
	fout.open(schedfile, ios::out);
	
	prompt("               NEW QUEUE                ");
	//DISPLAYS CONTENTS OF FILE
	cout<<char(214);design(196,6);cout<<char(194);design(196,32);cout<<char(194);design(196,7);cout<<char(194);design(196,10);cout<<char(183)<<endl;
	cout<<char(186);design(' ',4);cout<<"ID"<<char(179);
	design(' ',13);cout<<"TITLE";design(' ',14);cout<<char(179);
	cout<<" PAGES "<<char(179)<<" PRIORITY "<<char(186)<<endl;
	cout<<char(199);design(196,6);cout<<char(197);design(196,32);cout<<char(197);design(196,7);cout<<char(197);design(196,10);cout<<char(182)<<endl;
	
	while (r != NULL) {
		cout<<char(186)<<right<<setw(idSetw)<<setfill(separator)<<r->id<<char(179);
		cout<<left<<setw(titleSetw)<<setfill(separator)<<r->title<<char(179);
		cout<<left<<setw(pagesSetw)<<setfill(separator)<<r->pages<<char(179);
		cout<<left<<setw(prioritySetw)<<setfill(separator)<<r->prio<<char(186)<<endl;	
		r->title = convertSpaces(r->title,'|',' ');
		fout<<r->id<<"\t"<<r->title<<"\t"<<r->pages<<"\t"<<r->prio<<"\n";
    	r = r -> next;
	}
	cout<<char(211);design(196,6);cout<<char(193);design(196,32);cout<<char(193);design(196,7);cout<<char(193);design(196,10);cout<<char(189)<<endl;
	fout.close();
}
//Function to clear a queue
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
//Function to create a priority queue 
//reference:  https://www.geeksforgeeks.org/priority-queue-using-linked-list/
void addNode(int id, string title, int pages, int pr) {
    node *temp = new node(); 
    node *here = new node();
	
	temp->id = id;
    temp->title= title;
    temp->pages= pages;
	temp->prio= pr; 
    temp->next = NULL; 
 	
	if (head==NULL){ //if queue has no value, put inside head
 		head = temp;
 	} else if (head->prio > pr || (head->prio==pr)&&(head->pages>pages)){ //compares recent entry to first entry of the queue, if recent entry has greater priority, it becomes the new first entry
		temp->next = head;
		head = temp;
	} else {
		here = head;
		while(here->next!=NULL && (here->next)->prio < pr) here = here->next;	//traverse queue until it finds an entry with lesser priority
		while(here->next!=NULL && (here->next)->prio == pr && pages>(here->next)->pages) here=here->next; //if has equal priority, compares pages and proceeds to shortest job first
		while(here->next!=NULL && (here->next)->prio == pr && pages==(here->next)->pages&&id>(here->next)->id) here=here->next; //If equal priority & pages, proceeds to first come, first serve
		temp->next = here->next; //inserts entry into queue from designated place
		here->next = temp;
	}
}
//Function for Schedule Project: Create Schedule 
void create_sched(char* inputfile){
	system("cls");
	
	fstream myfile(inputfile);
	int id, pages, prio;
	string title;
	
	fstream cfile;
	int idc, pagesc, prioc;
	string titlec;
	deleteNodes(); //clear prevous queue
	
	while(myfile >> id >> title >> pages >> prio){	//compares contents of completedlist.txt and inputs.txt
		bool buff = true;
		cfile.open(completedFileName);
		if(!isFileEmpty(completedFileName)){
			while(cfile>> idc >> titlec >> pagesc >> prioc) {
				if (id==idc) buff=false;	
			}
		}
		if (buff){
			title = convertSpaces(title,' ','|');
			addNode(id,title,pages,prio);
		} //if entry is not mark completed, then insert into queue
		cfile.close();
	}
	if(head==NULL||isFileEmpty(inputsFileName)){ //if list is empty
		prompt(" NO MORE AVAILABLE PROJECTS TO SCHEDULE ");
		system("pause>0");
		return;
	}
	display_sched(scheduleFileName);	
	prompt("     NEW SCHEDULE HAS BEEN CREATED      ");
	myfile.close();
	system("pause>0");
}
//Function used to view a file based on parameter
void view_file(char* schedfile, string outString){
	system("cls");	
	prompt(outString);
	if(isFileEmpty(schedfile)){
		prompt("           THIS LIST IS EMPTY           ");
		system("pause>0");
		return;
	}
	
	fstream thisfile;
	int id,pages,priority;
	string title;
	
	thisfile.open(schedfile);
	
	//DISPLAYS CONTENTS
	cout<<char(214);design(196,6);cout<<char(194);design(196,32);cout<<char(194);design(196,7);cout<<char(194);design(196,10);cout<<char(183)<<endl;
	cout<<char(186);design(' ',4);cout<<"ID"<<char(179);
	design(' ',13);cout<<"TITLE";design(' ',14);cout<<char(179);
	cout<<" PAGES "<<char(179)<<" PRIORITY "<<char(186)<<endl;
	cout<<char(199);design(196,6);cout<<char(197);design(196,32);cout<<char(197);design(196,7);cout<<char(197);design(196,10);cout<<char(182)<<endl;

	while (thisfile>>id>>title>>pages>>priority){
		title = convertSpaces(title,' ','|');
		cout<<char(186)<<right<<setw(idSetw)<<setfill(separator)<<id<<char(179);
		cout<<left<<setw(titleSetw)<<setfill(separator)<<title<<char(179);
		cout<<left<<setw(pagesSetw)<<setfill(separator)<<pages<<char(179);
		cout<<left<<setw(prioritySetw)<<setfill(separator)<<priority<<char(186)<<endl;
	}		
	cout<<char(211);design(196,6);cout<<char(193);design(196,32);cout<<char(193);design(196,7);cout<<char(193);design(196,10);cout<<char(189)<<endl;
	system("pause>0");
	thisfile.close();
}

//Function subfuntion for Get a Project option: Displays and deletes the topmost project from current schedule queue in sched.txt and transfer it as completed to completedlist.txt
void chosenProj(struct node* temp){
	fstream cfile(completedFileName,ios::app);
	
	temp->title = convertSpaces(temp->title,'|',' ');
	cfile<<temp->id<<'\t'<<temp->title<<'\t'<<temp->pages<<'\t'<<temp->prio<<endl;
	prompt("      YOU HAVE TAKEN THIS PROJECT       ");
	//PRESENTS PROJECT TAKEN
	cout<<char(214);design(196,6);cout<<char(194);design(196,32);cout<<char(194);design(196,7);cout<<char(194);design(196,10);cout<<char(183)<<endl;
	cout<<char(186);design(' ',4);cout<<"ID"<<char(179);
	design(' ',13);cout<<"TITLE";design(' ',14);cout<<char(179);
	cout<<" PAGES "<<char(179)<<" PRIORITY "<<char(186)<<endl;
	cout<<char(199);design(196,6);cout<<char(197);design(196,32);cout<<char(197);design(196,7);cout<<char(197);design(196,10);cout<<char(182)<<endl;
	
	temp->title = convertSpaces(temp->title,' ','|');
	cout<<char(186)<<right<<setw(idSetw)<<setfill(separator)<<temp->id<<char(179);
	cout<<left<<setw(titleSetw)<<setfill(separator)<<temp->title<<char(179);
	cout<<left<<setw(pagesSetw)<<setfill(separator)<<temp->pages<<char(179);
	cout<<left<<setw(prioritySetw)<<setfill(separator)<<temp->prio<<char(186)<<endl;
	cout<<char(211);design(196,6);cout<<char(193);design(196,32);cout<<char(193);design(196,7);cout<<char(193);design(196,10);cout<<char(189)<<endl;
	
	prompt("     PRESS ANY KEY TO START PROJECT     ");
	system("pause>0");
	
	cout<<endl; design(' ',9);
	for(int i=0; i<42; i++){
		cout<<char(177);
		Sleep(10);
	} cout<<endl;
	prompt("            PROCESS COMPLETE            ");
	cout<<endl<<endl;
	system("pause>0");	
	cfile.close();
}
//Function for Get a Project option
void get_project(){
	system("cls");
	fstream schedfile(scheduleFileName);
	fstream cfile(completedFileName,ios::app);
	int id, pages, prio;
	string title;

	deleteNodes(); //clear current queue
	if(!isFileEmpty(scheduleFileName)){
		while(schedfile >> id >> title >> pages >> prio){
			title=convertSpaces(title,' ','|');
			addNode(id,title,pages,prio);
		}
	}else{
		prompt("          NO SCHEDULE CREATED           ");	
		schedfile.close();
		cfile.close();
		return;
	}
	schedfile.close();
	node *temp = new node();
	temp = head;
	bool buff = false;
	
	prompt("          INITIALIZING PROJECT          ");
	design(' ',25);
	for(int i=0; i<5; i++){
		cout<<char(254)<<" ";
		Sleep(200);
	} cout<<endl;
	
	if(head->next == NULL){ //if its the only one entry in the list
		buff=true;
		fstream schedfile(scheduleFileName,ios::out);
		schedfile <<"";
		schedfile.close();
		chosenProj(temp);
		prompt("            NO QUEUE FOLLOWS            ");
		return;
	} else head = head->next; //if there is greater that one entry 
	
	chosenProj(temp);
	free(temp);
	cfile.close();
	if(!buff) display_sched(scheduleFileName);
}
//MAIN PROGRAM
int main(){
	string choice;
	bool buff=true;
	while(1){
		system("cls");
		cout<<char(201); design(205,40); cout<<char(187)<<endl;
		cout<<char(186)<<"  F I N G E R S  O U T S O U R C I N G  "<<char(186)<<endl;
		cout<<char(204);design(205,11);cout<<char(203); design(205,28); cout<<char(185)<<endl;
		cout<<char(186)<<"       MAIN"<<char(186); design(176,10);cout<<" CHOOSE "; design(176,10);cout<<char(186)<<endl;
		cout<<char(186)<<"       MENU"<<char(186)<<char(176); design(' ',26);cout<<char(176)<<char(186)<<endl;
		cout<<char(204);design(205,11);cout<<char(185)<<char(176)<<"  1 "<<char(175)<<" Enter a Project     "<<char(176)<<char(186)<<endl;
		cout<<char(186)<<" Programmed"<<char(186)<<char(176)<<"  2 "<<char(175)<<" View Projects       "<<char(176)<<char(186)<<endl;
		cout<<char(186)<<"         By"<<char(186)<<char(176)<<"  3 "<<char(175)<<" Schedule Project    "<<char(176)<<char(186)<<endl;
		cout<<char(186)<<"M.J. DALIRE"<<char(186)<<char(176)<<"  4 "<<char(175)<<" Get a Project       "<<char(176)<<char(186)<<endl;
		cout<<char(186)<<"J.R. DEVERA"<<char(186)<<char(176)<<"  5 "<<char(175)<<" Exit                "<<char(176)<<char(186)<<endl;
		cout<<char(186)<<"  H. GADONG"<<char(186)<<char(176);design(' ',26);cout<<char(176)<<char(186)<<endl;
		cout<<char(186)<<"M.E.  VIRAY"<<char(186)<<char(176);design(176,26);cout<<char(176)<<char(186)<<endl;
		cout<<char(200); design(205,11); cout<<char(202); design(205,28); cout<<char(188)<<endl;	
		design(' ',14);cout<<"OPTION "<<char(174)<<" ";
		cin>>choice;
		if(choice.length()>1) choice = "z";
		switch(choice[0]){
			case '1': input_project(inputsFileName); break;
			case '2': 
				while(buff){
					system("cls");
					design(' ',9);cout<<char(201);design(205,40); cout<<char(187)<<endl;
					design(' ',9);cout<<char(186);design(' ',11); cout<<" VIEW PROJECT/S  "; design(' ',12); cout<<char(186)<<endl;
					design(' ',9);cout<<char(204);design(205,40); cout<<char(185)<<endl;
					design(' ',9);cout<<char(186)<<" ";design(178,38);cout<<" "<<char(186)<<endl;
					design(' ',9);cout<<char(186)<<" ";design(178,2);design(' ',34);design(178,2);cout<<' '<<char(186)<<endl;
					design(' ',9);cout<<char(186)<<" ";design(178,2);design(' ',7);cout<<"A "<<char(175)<<" One Project";design(' ',12);design(178,2);cout<<' '<<char(186)<<endl;
					design(' ',9);cout<<char(186)<<" ";design(178,2);design(' ',7);cout<<"B "<<char(175)<<" Completed Project/s";design(' ',4);design(178,2);cout<<' '<<char(186)<<endl;
					design(' ',9);cout<<char(186)<<" ";design(178,2);design(' ',7);cout<<"C "<<char(175)<<" All Projects";design(' ',11);design(178,2);cout<<' '<<char(186)<<endl;
					design(' ',9);cout<<char(186)<<" ";design(178,2);design(' ',7);cout<<"X "<<char(175)<<" Return to Menu";design(' ',9);design(178,2);cout<<' '<<char(186)<<endl;
					design(' ',9);cout<<char(186)<<" ";design(178,2);design(' ',34);design(178,2);cout<<' '<<char(186)<<endl;
					design(' ',9);cout<<char(186)<<" ";design(178,38);cout<<" "<<char(186)<<endl;
					design(' ',9);cout<<char(200);design(205,40);cout<<char(188)<<endl;	
					design(' ',14);cout<<"OPTION "<<char(174)<<" ";
					cin>>choice;
					if(choice.length()>1) choice = "z";
					switch(choice[0]){
						case 'A':
						case 'a': view_project_a(); break; //goes to view file with ID input option
						case 'B':
						case 'b': view_file(completedFileName,"           COMPLETED PROJECTS           "); break; //Displays all completed projects from completedlist.txt file
						case 'C':
						case 'c': view_file(inputsFileName,"              ALL PROJECTS              "); break; //Displays all created projects from inputs.txt file
						case 'X':
						case 'x': buff=false; break;
						default: break;
					}	
				} buff=true; break;
			case '3': 
				while(buff){
					system("cls");
					design(' ',9);cout<<char(201);design(205,40); cout<<char(187)<<endl;
					design(' ',9);cout<<char(186);design(' ',11); cout<<"SCHEDULE PROJECTS"; design(' ',12); cout<<char(186)<<endl;
					design(' ',9);cout<<char(204);design(205,40); cout<<char(185)<<endl;
					design(' ',9);cout<<char(186)<<" ";design(178,38);cout<<" "<<char(186)<<endl;
					design(' ',9);cout<<char(186)<<" ";design(178,2);design(' ',34);design(178,2);cout<<' '<<char(186)<<endl;
					design(' ',9);cout<<char(186)<<" ";design(178,2);design(' ',5);cout<<"A "<<char(175)<<" Create New Schedule";design(' ',6);design(178,2);cout<<' '<<char(186)<<endl;
					design(' ',9);cout<<char(186)<<" ";design(178,2);design(' ',5);cout<<"B "<<char(175)<<" View Schedule";design(' ',12);design(178,2);cout<<' '<<char(186)<<endl;
					design(' ',9);cout<<char(186)<<" ";design(178,2);design(' ',5);cout<<"X "<<char(175)<<" Return to Menu";design(' ',11);design(178,2);cout<<' '<<char(186)<<endl;
					design(' ',9);cout<<char(186)<<" ";design(178,2);design(' ',34);design(178,2);cout<<' '<<char(186)<<endl;
					design(' ',9);cout<<char(186)<<" ";design(178,38);cout<<" "<<char(186)<<endl;
					design(' ',9);cout<<char(200);design(205,40);cout<<char(188)<<endl;	
					design(' ',14);cout<<"OPTION "<<char(174)<<" ";
					cin>>choice;
					if(choice.length()>1) choice = "z";
					switch(choice[0]){
						case 'A':
						case 'a': create_sched(inputsFileName); break;
						case 'B':
						case 'b': view_file(scheduleFileName,"            CURRENT SCHEDULE            "); break;
						case 'X':
						case 'x': buff=false; break;
						default: break;
					}
				} buff = true; break;
			case '4': get_project(); break;
			case '5': 
				system("cls");
				prompt(" THANK U 4 CHOOSING FINGERS OUTSOURCING ");
				exit(0);
			default: 
				design(' ',13);cout<<char(218);design(196,26);cout<<char(191)<<endl;
				design(' ',13);cout<<char(179)<<"      INVALID INPUT!      "<<char(179)<<endl;
				design(' ',13);cout<<char(212);design(205,26);cout<<char(190)<<endl;
		}
		prompt("       PRESS ANY KEY TO CONTINUE.       ");
		system("pause>0");
	}
	return 0;	
}
