/*******************************
/DND Combat Simulator
/The purpose of this program is to help DMs manage combat more smoothly. It also
/will force the coder to understand how a class works
/Developed by Drew Perenich, dperenich@outlook.com
/Please note that, in the comments I use npcs and enemies intetchangebly. I always mean NPCs
/Other Needed files:
/*******************************/
using namespace std;//fuck using the whole std::cin crap. If you think thats at all necessary you are a peice of shit
#include<iostream>//for cout cin, etc
#include<iomanip>//for setw, 
#include<cstring>//why is this not standard
#include<random>//for dice rolling
#include<fstream>//for printing to files
#include<limits>//if needed
#include<vector>//to hold array of classes
#include<time.h>//for srand value time variable
#include<algorithm>//for sort

class npc;//holds info about all group of npc (kobolds, acrolytes, guards, etc), such initiative bonus, max health, etc

//functions
void printWelcome();//print welcome characters
void lineOfAstrisks();//print line of astrisks
void basicInfo(char&);//gets basic info for battle, such as rolling for health
int initalizeEnemy(vector<npc>&, char);//initalizes enemy, reads in health, init, etc. Returns total number of enemies
int rollDice(int, int, int);//roll dice with modifier number of ti
void initiative(vector<npc>&);//roll and sort initiative
bool initCompare(npc& n1, npc& n2);//used to sort via intiative
void initializePCs(npc& n);//add PCs to vector
int getInt();//get integer does flushing and error checking
//global constant

class npc{//main npc class
	public:
		string title;//name of npc, eg cultist 1
		int health;//amount of health
		int initB;//initiative modifier
		int init;//initiative modifier
		bool pc;//is this a pc (yeah its a bad class name but thats what you get for not realizing you dont need two seperate classes 
		npc() {
			initB = 20000;//used to check to see if it has been changed yet. 
			pc = false;//will only touch this when initialising pcs
		}
		
};
int main(){
	char rollHealth;//weather or not to roll health
	bool done;//used for loop control
	char yn;//holds y or n that does not need to be stored
	vector<npc> npcs;//array of npcs
/* 	//get int test
	cout << "Testing getInt";
	int tester;
	while(1){
		cout << endl;
		tester = getInt();
		cout << "Value of tester is " << tester;
	} */
	//startup
	srand (time(NULL));//set random seed to time
	printWelcome();//print welcome menu
	basicInfo(rollHealth);//get basic information
	//initalize npcs,gives name, health, init bonus
	initalizeEnemy(npcs, rollHealth);//initalize npcs
	//initalizePCs(npcs);//initializeNPCs
	//roll initative and sort
	initiative(npcs);
	return 0;
	
	
}



void printWelcome(){
	char dummy;//used for cin stop
	lineOfAstrisks();
	cout << "This program is meant to help DMs run Combat Easier" << endl;
	cout << "It is reccomended you go through a test combat before using in a session," << endl;
	cout << "To see what the Program will and won't do." << endl;
	cout << "You will still need to roll dice for combat, and have stat blocks open, as this will not make turns for the NPCs" << endl;
	cout << "This is all text based, should make your life easier" << endl;
	cout << "As of right now, there is no way to change information once put in, so it is reccomended you double check" << endl;
	cout << "All info before continuing forward" << endl;
	cout << "Press enter to continue" << endl;
	cin.get(dummy);//stop until entered
	cin.ignore();//clear input buffer
	cout << endl;
	lineOfAstrisks();
	return;
}
void lineOfAstrisks(){

	cout << string(75, '*') << endl;//prints line of astrisks
	return;
}
void basicInfo(char& rHealth){
	//get basic information
	bool done = false;
	cout << "Lets get the basics" << endl;
	cout << "Do you want to roll enemy Health? y for yes, n for no" << endl;
	cin.get(rHealth);//get answer to rolling enemy health
	cin.ignore();//clear buffer streambu
	done = false;
	while(!done){
		if(rHealth == 'y'){
			cout << "You have chosen to roll health. That is something that this program can speed up!" << endl;
			done = true;
		}else if(rHealth == 'n'){
			cout << "You have chosen not to roll health. Boooooo!!!" << endl;
			done = true;
		}else{
			
			cout << "Huh? You didnt answer y or n? Try again!!!" << endl;
			
			cin.get(rHealth);//retry
			cin.ignore();
			}
	}
	return;
}
int rollDice(int dice, int times, int mod){
	int result = 0;
	for(int i = 0; i < times; i++){
		result += rand()%dice + 1 + mod;//roll random number, plus since if dice =10, rand%dice can be 0 to 9
	}
	return result;
}

int initalizeEnemy(vector<npc>& npcs, char rH){//initalizes enemy, returns total number of npcs
	bool done;
	char yn;
	string groupName;//current group name of enemies
	string groupNames[] = {};//stores all group names seperate of class, currently not used
	int groupNumber;//number of enemies in group
	int cHealth, groupInitB;//cHealth, initative of group members
	int hMax, hMod, hTimes;//for rolling cHealth, max, modifier, times
	string npcName;//name of current NPC
	int totNPC = 0;//total number of NPCs
	npc n;//current npc
	done = false;
	while(!done){
		cout << "Do you have anymore npc types? (eg kobolds, acrolytes, things with the same basic statblock)" << endl;
		cout << "y for yes, n for no" << endl;
		
		cin.get(yn);//get response
		cin.ignore(INT_MAX, '\n');//flush cin
		while(yn != 'y' && yn != 'n'){
				cout << "wrong answer!!! y or n!" << endl;
				
				cin.get(yn);//get response
				cin.ignore(INT_MAX, '\n');//flush cin
		}
		switch(yn){//check and see if anymore to add
			case 'n'://none to add
				cout << "Okay, out of enemies" << endl;
				done = true;
				break;
			case 'y':
				//prompt for name, number, etc
				cout << "What is the name of this group of enemies?" << endl;
				
				getline(cin, groupName);//so they can have multiple words
				cin.ignore();
				cout << "How many enemies are there" << endl;
				//cin.ignore(INT_MAX);
				groupNumber = getInt();
				totNPC += groupNumber;//add group number to total
				switch(rH){//check and see if rollting cHealth
					case 'n':
						cout << "How much health do they have? Enter integer" << endl;
						groupName = getInt();//
						break;
					case 'y':
						cout << "For health, what dice is being rolled, how many times, what is the modifier?";
						cin.ignore(INT_MAX, '\n');
						hMax = getInt();
						hTimes = getInt();
						hMod = getInt();
						cout << hMax << hTimes << hMod;
						cHealth = 0;//will be used to hold cHealth of individual 
						break;
				}
				/*Need to add roll dice function 2/21/2024*/
				cout << "Initaitive bonus?" << endl;
				cin >> groupInitB;
				for(int idx = 1; idx <= groupNumber; idx++){
					npcName = groupName + " " + to_string(idx);//make npc name unique eg kobold 1, kobold 2, etc
					//assign attributes to dummy object
					n.title = npcName;
					//check and see if rolling cHealth
					if(rH == 'y'){//roll dice for health
						cHealth = 0;
						for(int jdx = 0; jdx < hTimes; jdx++){
							cHealth += rollDice(hMax, hTimes, 0);//roll dice certain number of times and add together, mod will be added to total
						}
						cHealth += hMod;//cHealth += hMod
					}
					n.health = cHealth;
					n.initB = groupInitB;
					//add to vector
					npcs.push_back(n);
				}
				for (int idx = 0; idx < npcs.size(); idx++){
					cout << npcs[idx].title << " " << npcs[idx].health << " "<< npcs[idx].initB << endl;
				}
		}
	}
	return totNPC;
}
void initiative(vector<npc>& npcs){//roll and sort initiative
	npc n;//current class being worked on
	//roll initative for each npc
	for(int idx = 0; idx < npcs.size();idx++){
		npcs[idx].init = rollDice(20, 1, npcs[idx].initB);//roll initiative and add intiative bonus
		cout << npcs[idx].init;
	}
	sort(npcs.begin(),npcs.end(), initCompare);
	//print out initatives, for test
	for(int idx = 0; idx < npcs.size();idx++){
		cout << npcs[idx].title << " " << npcs[idx].init << endl;
	}
	return;
}
bool initCompare(npc& n1, npc& n2){
	int tempMod;//used if tie involving a PC
	if(n1.init != n2.init){//if not tied, return init order
		return n1.init > n2.init;
	} else{//if tied, return init bonus order
		if(n1.initB == 20000){//if initiative bonus hasnt been initialized (eg is player character) will equal default value of -1
			cout << "Tie detected for initiative! What is " << n1.title << " initiative bonus?" << endl;
			cin >> tempMod;
			n1.initB = tempMod;
		}
		if(n2.initB == 20000){
			cout << "Tie detected for initiative! What is " << n2.title << " initiative bonus?" << endl;
			cin >> tempMod;
			n2.initB = tempMod;
		}
		return n1.initB > n2.initB;
	}
}
int getInt(){
	int input;
	cin >> input;//get input
		while(!cin){//check to see if cin went bad
			cin.clear();//clear status
			cout << "You need to put in an integer!!!!";
			cin.ignore();//clear input buffer
			cin >> input;
			cout << endl;
		}
	cin.ignore();//just to make sure
	return input;
}