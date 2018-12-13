//menu default
#include <iostream>
#include <stdlib.h>
using namespace std;

//INSERT FUNCTIONS HERE!!!
void input_project(){
	
}

void view_project(){
	
}


int main(){
	char choice;
	
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
			case '1': /*insert function here*/ break;
			case '2': 
				while(1){
					system("cls");
					cout<<"[a] One Project"<<endl;
					cout<<"[b] Completed Projects"<<endl;
					cout<<"[c] All Projects"<<endl;
					cout<<"Enter option (press other key to go back to menu): ";
					cin>>choice;
					switch(choice){
						case 'a': /*insert function here*/ break;
						case 'b': /*insert function here*/break;
						case 'c': /*insert function here*/break;
						default: break;
					}
					break;
				}break;
				
			case '3': 
				while(1){
					system("cls");
					cout<<"[a] Create Schedule"<<endl;
					cout<<"[b] View Schedule"<<endl;
					cout<<"Enter option (press other key to go back to menu): ";
					cin>>choice;
					switch(choice){
						case 'a': /*insert function here*/ break;
						case 'b': /*insert function here*/ break;
						default: break;
					}
					break;
				} 
				break;
			case '4': /*insert function here*/ cout<<"Hi 4"; break;
			case '5': exit(0);
			default: cout<<"Hi def"; break;
		}
		system("pause>0");
	}
	return 0;	
}
