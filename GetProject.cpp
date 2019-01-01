// GET A PROJECT
// Josh Part

#include <fstream>
#include <iostream>
using namespace std;

// Initial declaration ng functions para di mag-error
void displayTextFile(char* file1);
void CopyFile(char* file1, char* file2);
void CopyFileWithoutLine1(char* file1, char* file2);
 
// Data structures na hindi nagamit
struct node {
	int data;
	struct node *next;
} *head; 

int main () {
	string Line1;
	char hey[100];
	char name[100];
	int count;
	int choice;

	do{
		cout << "MAIN MENU\n";
		cout << "1. Input project details.\n";
		cout << "2. View projects.\n";
		cout << "3. Schedule projects.\n";
		cout << "4. Get a project.\n";
		cout << "5. Exit\n";
		cout << "Choose: ";
		cin >> choice;	
	}while(choice<1||choice>5);
	
	switch(choice){
		case 1: cout << "Option 1 was chosen and exited."; break;
		case 2: cout << "Option 2 was chosen and exited."; break;
		case 3: cout << "Option 3 was chosen and exited."; break;
		case 5: exit(1);	
	}
	
	// Get a Project MAIN
	if(choice==4){
		//-------------------------------------------------------------------------------
		// Display the scheduled queue and open the file to get topmost project from schedule queue
		cout << "\nContent of sched.txt\n";
		displayTextFile("sched.txt");
		cout << "\n\nTopmost schedule from sched.txt\n";
		ifstream readfile("sched.txt"); //Eto daw filename ni Em
		string Line1;
		
		if (readfile.good())
		{
		    getline(readfile, Line1);
		    cout << Line1 << endl;
	  	}
	
	  	readfile.close();
	  	
		cout << "\n\nTopmost project from the queue has been removed.\n\n";
		cout << "Copy progress:\n";
		CopyFileWithoutLine1("sched.txt", "temp.txt");
		CopyFile("temp.txt", "sched.txt");
		cout<<'\n';
		system("pause");
		
		//-------------------------------------------------------------------------------
		// Place the removed project's details to the completed projects list
		ofstream complist;
		complist.open("completedlist.txt", ios::app);
		
		// Write details to completedlist file func
		complist << '\n' << Line1;
		complist.close();
		cout << "\nCopy progress:\n";
		CopyFile("completedlist.txt", "temp.txt");
		
		cout<<"\n";
		system("pause");
		
		//-------------------------------------------------------------------------------
		// Display the schedule queue but this time without the topmost project
		cout << "\nThe sched.txt queue without the topmost project\n";
		displayTextFile("sched.txt");
		
		cout<<"\n";
		system("pause");
	}
}

void displayTextFile(char* file1) {
	char line[255];
    ifstream dataFile;
	dataFile.open(file1,ios::in);
	
	while(!dataFile.eof()){
        dataFile.getline(line,255,'\n');
        cout<<line<<endl;
    }
    
    /*while (!dataFile.fail() && !dataFile.eof() )
    {
          dataFile >> name ;
          cout << name;
          count++;
          if (count==5){
          	cout<<"\n";
          	count=0;
		  }
    }*/
    dataFile.close();
    return;
}

void CopyFile(char* file1, char* file2) {
	ifstream fin;
    fin.open(file1,ios::in);

    ofstream fout;
    fout.open(file2,ios::out);
    char line[255];

    while(!fin.eof()){
        fin.getline(line,255,'\n');
        fout<<line<<endl;
    }
    fin.close();
    fout.close();
    cout<<"done"<<endl;

    return;
}

void CopyFileWithoutLine1(char* file1, char* file2) {
	ifstream fin;
    fin.open(file1,ios::in);
	string line;
	
    ofstream fout;
    fout.open(file2,ios::out);
    int count = 1;

    while(getline(fin,line)){
    	if (count > 1){
        fout<<line<<endl;
    	}
    	count++;
	}
    fin.close();
    fout.close();
    cout<<"done"<<endl;

    return;	
}
