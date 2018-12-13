//management system v1.1
#include <iostream>
#include <fstream>

using namespace std;

int main(){
	int choice;
	char projectChoice;
	
	int id(0),pages(50),priority;
	char title[100];
	
	ofstream myfile("inputs.txt",ios::app);
	
	cout<<"Main menu: "<<endl;
	cout<<"[1] Input project details"<<endl;
	cout<<"[2] View projects"<<endl;
	cout<<"[3] Exit"<<endl;
	cout<<"Enter option: ";
	cin>>choice;
	
	if(choice==1){
		id++;
		myfile<<id<<"\t";
		cout<<"Enter title of the manuscript: "; //Title
		cin>>title; 
		myfile<<title<<"\t";
		//cin.getline(title,100);
		do{
			cout<<"Enter number of pages: "; //Pages
			cin>>pages;
			myfile<<pages<<"\t";
			if(pages<50||pages>500)
				cout<<"The pages of the manuscript exceeds the given range."<<endl;
		}while((pages<50)||(pages>500));
		cout<<"Enter the priority of the manuscript: "; //Priority
		cin>>priority;
		myfile<<priority<<"\n";
		myfile.close();
		cout<<"\nPlacing inputs done successfully!";
	}
	else if(choice==2){
		cout<<"\t[a] One project"<<endl;
		cout<<"\t[b] Completed projects "<<endl;
		cout<<"\t[c] All projects"<<endl;
		cout<<"\tEnter option: ";
		cin>>projectChoice;
		if(projectChoice=='a'){
			system("cls");
			cout<<"a";
		}
		else if(projectChoice=='b'){
			system("cls");
			cout<<"b";
		}
		else if(projectChoice=='c'){
			system("cls");
			cout<<"c";
		}
		else{
			cout<<"Invalid choice!";
		}
	}
	else if(choice==3){
		;
	}
	else{
		cout<<"Invalid choice!";
	}
	
}
