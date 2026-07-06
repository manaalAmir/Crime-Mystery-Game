#include <iostream>
#include <string>
using namespace std;

class Person{ //Base class
	protected:
    	string name; // data members
    	int age;
    	string alibi; 
	public:
    	void setDetails(const string& n,int a,const string& ali){ // Set data members of Person class
        	name=n;
        	age=a;
        	alibi=ali;
    	}

    	virtual void displayInfo(){  //Virtual function for displaying information 
        	cout<<"Name: "<<name<<endl<<"Age: "<<age<<endl<<"Alibi: "<<alibi<<endl;
    	}

    	string getName(){ 
			return name; 
		}
		
    	string getAlibi(){ 
			return alibi; 
		}
};

class Suspect:public Person{ //Derived class
	private:
    	string motive;
    	bool isGuilty; //Data members
	public:
    	void setSuspectDetails(const string& m,bool guilty){
        	motive=m;  //Sets Suspect(Derived class ) data members
        	isGuilty=guilty;
    	}
    	
    	void displayInfo() override{ //Override to include motive in the display
        	Person::displayInfo(); //Calls Person (Base class) displayInfo first
        	cout<<"Motive: "<<motive<<endl;
    	}

    	void interrogate(){
        	displayInfo();
    	}

    	bool checkGuilt(){ //Checks if the suspect is guilty
        	return isGuilty;
    	}

    	string getMotive(){
        	return motive;
    	}
};

class Evidence{
	private:
    	string description;
    	string foundAt; // data members
    	string relatedTo;
	public:
    	void setEvidence(const string& desc,const string& location,const string& suspectName){
        	description=desc;  //Sets data members of Evidence class
        	foundAt=location;
        	relatedTo=suspectName;
    	} 

    void displayEvidence(){ //Displays evidence
        cout<<"Evidence: "<<description<<endl<<"Found at: "<<foundAt<<endl<<"Related to: "<<relatedTo<<endl;
    }

    string getRelated(){
        return relatedTo;
    }

    string getDescription(){
        return description;
    }
};

class Game{
private:
//ARRAYS TO STORE SUSPECT AND EVIDENCE 
    Suspect suspects[3];
    Evidence evidences[3];
    string playerName;
    int score;
    int maxAttempts;
    int caseNumber;
    int totalScore;

public:
//CONSTRUCTOR : INITIALIZE SCORE AND TOTAL SCORE
    Game(){
        score=100;
        totalScore=0;
    }

    void startGame(){
        //WELCOME SCREEN
        cout<<"=============================="<<endl;
        cout<<" TEXT DETECTIVE: FAST Edition"<<endl;
        cout<<"=============================="<<endl;
        cout<<"Enter your name, Detective: ";
        getline(cin,playerName); //GET PLAYER NAME 

        int choice;
        do{
            //MENU TO CHOOSE THE CASE 
            cout<<endl<<"Choose a case to investigate:"<<endl;
            cout<<"1. DLD Lab Fire"<<endl;
            cout<<"2. CS Lab Data Leak"<<endl;
            cout<<"3. Kidnap Case"<<endl;
            cout<<"4. Plagiarism Scandal"<<endl;
            cout<<"5. Research Theft"<<endl;
            cout<<"6. Murder at Campus"<<endl;
            cout<<"7. Exit Game"<<endl;
            cout<<"Enter case number (1-7): ";
            cin>>choice;
            cin.ignore();

            if(choice>=1&&choice<=6){ //IF CASE IS VALID 
                loadCase(choice);
                score=100;
                maxAttempts=2;
                playCase();
                totalScore=totalScore+score;
            }else if(choice==7){
                //EXIT MESSAGE
                cout<<"Thank you for playing,Detective "<<playerName<<"."<<endl;
                cout<<"Your Total Score: "<<totalScore<<endl;
                cout<<"Goodbye!\n";
                break;
            }else{
                cout<<"Invalid choice. Try again.\n";
            }
        } while(true); //REPEAT THE LOOP UNTIL PLAYER EXIT
    }

    void playCase(){ //MAIN MENU FOR EACH CASE
        int menuChoice;
        while(maxAttempts>0){
            cout<<endl<<"------- CASE MENU --------"<<endl;
            cout<<"1. Interrogate Suspects"<<endl;
            cout<<"2. View Evidence"<<endl;
            cout<<"3. Use Hint (-10 points)"<<endl;
            cout<<"4. Make an Accusation"<<endl;
            cout<<"Score: "<<score<<" | Attempts left: "<<maxAttempts<<endl;
            cout<<"Choose an option: ";
            cin>>menuChoice;
            cin.ignore();

            switch(menuChoice){ //HANDLES USER CHOICE
                case 1:
                interrogateAll(); 
                break;
                case 2: 
                viewEvidence(); 
                break;
                case 3: 
                useHint(); 
                break;
                case 4:
                    if(makeAccusation()) 
					return;
                    if(maxAttempts==0){
                        cout<<endl<<"You've used both your chances. Final attempt!"<<endl;
                        makeAccusation();
                        return;
                    }
                    break;
                default: 
                cout<<"Invalid choice."<<endl;
            }
        }
    }
//DISPLAY SUSPECTS 
    void interrogateAll(){
        cout<<endl<<"----- Interrogating Suspects -----"<<endl;
        for(int i=0;i<3;i++){
            cout<<endl<<"Suspect "<<(i+1)<<":"<<endl;
            suspects[i].interrogate();
        }
    }
//DISPLAY ALL THREE EVIDENCE
    void viewEvidence(){
        cout<<endl<<"--- Viewing Evidence ---"<<endl;
        for(int i=0;i<3;i++){
            cout<<endl<<"Evidence "<<(i+1)<<":"<<endl;
            evidences[i].displayEvidence();
        }
    }
//DEDUCT THE SCORE AND GIVE A CLUE 
    void useHint(){
        if(score<10){
            cout<<"Not enough score to use a hint."<<endl;
            return;
        }

        score=score-10;
        if(score<0)
        	score=0;
		
        for (int i=0;i<3;i++){
            if(suspects[i].checkGuilt()){
                cout<<endl<<"Hint: A suspect with a motive like '"<<suspects[i].getMotive()<<"' seems to be hiding something related to a key piece of evidence."<<endl;
                return;
            }
        }
    }
//ACCUSE THE PERSON
    bool makeAccusation(){
        cout<<endl<<"--- Make Your Accusation ---"<<endl;
        for(int i=0;i<3;i++){
            cout<<i+1<<". "<<suspects[i].getName()<<endl;
        }

        cout<<endl<<"Enter the number of the person you accuse: ";
        int acc;
        cin>>acc;
        cin.ignore();

        if(acc>=1&&acc<=3){
            if(suspects[acc-1].checkGuilt()){
                score=score+50;
                cout<<endl<<"Congratulations, Detective "<<playerName<<endl;
                cout<<suspects[acc-1].getName()<<" was guilty. You solved the case!"<<endl;
                cout<<"Case Score: "<<score<<endl;
                maxAttempts=0;
                return true;
            } 
            else{
                maxAttempts--;
                if(maxAttempts<0)
				 maxAttempts=0;
				 
                score=score-20;
                if(score<0)
        		score=0;
                cout<<endl<<"Incorrect accusation."<<endl;
                cout<<endl<<"Remaining Attempts: "<<maxAttempts<<" | Score: "<<score<<endl;
                return false;
            }
        }
        else{
            cout<<"Invalid choice."<<endl;
            return false;
        }
    }
//lOAD CASE
    	void loadCase(int caseID){
        	caseNumber=caseID;
//case 1 
        	if(caseID==1){
            	suspects[0].setDetails("Ahmed Khan",22,"I was in the cafeteria during the fire.");
            	suspects[0].setSuspectDetails("Failed the DLD course and was furious",false);
            	suspects[1].setDetails("Zainab Tariq",21,"I was in the girls common room.");
            	suspects[1].setSuspectDetails("Blamed lab instructor for poor grade",true);
            	suspects[2].setDetails("Bilal Qureshi",23,"I was attending my Data Structures class.");
            	suspects[2].setSuspectDetails("Had a fight with lab assistant",false);
            	evidences[0].setEvidence("Burnt lab report","DLD Lab trash can","Zainab Tariq");
            	evidences[1].setEvidence("CCTV footage","Hallway camera","Ahmed Khan");
            	evidences[2].setEvidence("Angry email to instructor","Instructor's inbox","Bilal Qureshi");
        	}
//case 2			
			else if(caseID==2){
        		suspects[0].setDetails("Sana Yousaf",20,"I was in the library all afternoon.");
            	suspects[0].setSuspectDetails("Wanted access to senior project code",false);
            	suspects[1].setDetails("Ali Raza",22,"I was fixing a bug in my code in lab.");
            	suspects[1].setSuspectDetails("Was recently suspended for hacking",true);
            	suspects[2].setDetails("Hassan Shah",24,"I was in an interview call at seminar hall.");
            	suspects[2].setSuspectDetails("Has a history of copying assignments",false);
            	evidences[0].setEvidence("USB with leaked code","Under lab PC #4","Ali Raza");
            	evidences[1].setEvidence("WiFi access logs","CS Lab Server Room","Sana Yousaf");
            	evidences[2].setEvidence("Screenshot of shared folder","WhatsApp group chat","Hassan Shah");
        	}
//case 3
			else if(caseID==3){
        		suspects[0].setDetails("umer",26,"I was at my cousin's wedding.");
            	suspects[0].setSuspectDetails("Had a grudge with the victim",true);
            	suspects[1].setDetails("Muneeb Shah",29,"I was on a business trip.");
            	suspects[1].setSuspectDetails("Victim owed him money",false);
            	suspects[2].setDetails("Sara Malik",22,"I was in the library.");
            	suspects[2].setSuspectDetails("Was in a romantic relationship with the victim",false);
            	evidences[0].setEvidence("Abduction note","Near victim's house","umer");
            	evidences[1].setEvidence("Flight ticket","Airport counter","Muneeb Shah");
            	evidences[2].setEvidence("Victim's phone","Library bench","Sara Malik");
        	}
//case 4			
			else if(caseID==4){
        		suspects[0].setDetails("Fahad Karim",25,"In final year project meeting.");
            	suspects[0].setSuspectDetails("Got caught plagiarizing before",true);
            	suspects[1].setDetails("Aiman Saeed",23,"Doing internship remotely.");
            	suspects[1].setSuspectDetails("Suspicious but no prior record",false);
            	suspects[2].setDetails("abdullah",24,"At home with family.");
            	suspects[2].setSuspectDetails("Was topping class unfairly",false);
            	evidences[0].setEvidence("Turnitin Report","Dean's inbox","Fahad Karim");
            	evidences[1].setEvidence("Similar thesis files","Laptop","Aiman Saeed");
            	evidences[2].setEvidence("Faculty chat screenshot","Whatsapp","abdullah");
        	}
//case 5		
			else if(caseID==5){
        		suspects[0].setDetails("Usama Iqbal",24,"At FAST cafe.");
            	suspects[0].setSuspectDetails("Competing on same research topic",false);
            	suspects[1].setDetails("Noor Fatima",23,"Working in computer lab.");
            	suspects[1].setSuspectDetails("Wanted early access to paper",true);
            	suspects[2].setDetails("Tariq Mehmood",26,"Sleeping in hostel.");
            	suspects[2].setSuspectDetails("Was denied co-authorship",false);
            	evidences[0].setEvidence("Printout of stolen draft","Printer room","Noor Fatima");
            	evidences[1].setEvidence("USB logs","Lab PC","Usama Iqbal");
            	evidences[2].setEvidence("Handwritten notes","Dorm room","Tariq Mehmood");
        	}
//case 6
			else if(caseID==6){
        		suspects[0].setDetails("Salman Haider",30,"In gym during murder.");
            	suspects[0].setSuspectDetails("Victim exposed his affair",false);
            	suspects[1].setDetails("Rabia Jameel",28,"Watching movie at Centaurus.");
            	suspects[1].setSuspectDetails("Victim blackmailed her",true);
            	suspects[2].setDetails("Adil Noor",27,"On a phone call.");
            	suspects[2].setSuspectDetails("Old college rivalry",false);
            	evidences[0].setEvidence("Bloody knife","Campus garden","Rabia Jameel");
            	evidences[1].setEvidence("Call logs","Victim's mobile","Adil Noor");
            	evidences[2].setEvidence("Security footage","Parking area","Salman Haider");
        	}
    	}
};

int main(){
    Game game;
    game.startGame();
    return 0;
}
