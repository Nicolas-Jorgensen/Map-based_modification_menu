//    <creates a map of villagers with various attributes,
//    then allows users to modify the villagerMap through a menu>


#include <iostream>
#include <iomanip>
#include <map>
#include <tuple>
#include <chrono> //for loading time
#include <thread> //also loading time
#include <algorithm> //for_each()

using namespace std;

const int WIDTH = 5, WAITSEC = 3; //sets indent and "loadtime" in 0.5 of a sec

int mainMenu();
void outputVillagers(const map<string, tuple<int, string, string>>&);
void addVillager(map<string, tuple<int, string, string>>&);
void delVillager(map<string, tuple<int, string, string>>&);
void increaseFriendship(map<string, tuple<int, string, string>>&);
void decreaseFriendship(map<string, tuple<int, string, string>>&);
void lookupVillager(const map<string, tuple<int, string, string>>&);

int main() {
    // declarations
    map<string, tuple<int, string, string>> villagerMap;
    int choice = 0;
    // insert elements into the map
    villagerMap["Beatrice"] = {2, "Bee", "Buzz off!"};
    villagerMap["Raymond"] = {10, "Gray Wolf", "I really need to shave."};
    villagerMap.insert({"Richard", {4, "White Whale", "Do you listen to Moby?"}});

    outputVillagers(villagerMap);
    //main menu
    while(choice != 6) {
        choice = mainMenu();
        switch (choice) {
            case 1:
                addVillager(villagerMap);
                outputVillagers(villagerMap);
                break;
            case 2:
                delVillager(villagerMap);
                outputVillagers(villagerMap);
                break;
            case 3:
                increaseFriendship(villagerMap);
                outputVillagers(villagerMap);
                break;
            case 4:
                decreaseFriendship(villagerMap);
                outputVillagers(villagerMap);
                break;
            case 5:
                lookupVillager(villagerMap);
                outputVillagers(villagerMap);
                break;
            case 6:
                cout << "Ending program.";
        }
    
        
    }
    return 0;
}
//prints options and returns an int corresponding to user choice
int mainMenu() {
    int menuNum = 1, choice;
    
    cout <<setw(WIDTH) << "" << menuNum++ << ". Add Villager\n\n";
    cout <<setw(WIDTH) << "" << menuNum++ << ". Delete Villager\n\n";
    cout <<setw(WIDTH) << "" << menuNum++ << ". Increase Friendship\n\n";
    cout <<setw(WIDTH) << "" << menuNum++ << ". Decrease Friendship\n\n";
    cout <<setw(WIDTH) << "" << menuNum++ << ". Search for Villager\n\n";
    cout <<setw(WIDTH) << "" << menuNum << ". Exit\n\n";

    cout << "Your choice: ";
    cin >> choice;
    
    while(choice < 1 || choice > menuNum) { //error checking
        cout << setw(WIDTH) << "" << "Please choose from the menu.\n";
        cout << "Your choice: ";
        cin >> choice;
    }
    cout << endl; 
    return choice;
}
//prints villagerMap
void outputVillagers(const map<string, tuple<int, string, string>>& villagerMap) {
    cout << setw(WIDTH) << "" << "Loading villager details:";
    for(int i = 0; i < WAITSEC; i++) { // short loading bar
        cout << "-" <<flush;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << endl << endl;
    for (auto pair : villagerMap) { //for-each to print every villager in map
        cout << setw(WIDTH) << "" << pair.first << ": [";
        cout << get<0>(pair.second) << ", ";
        cout << get<1>(pair.second) << ", ";
        cout << get<2>(pair.second) << "]\n";
        cout << endl;
    }
    cout << setw(WIDTH) << "" << "---------\n\n";
}
//takes a map and adds a villager with user-specified attributes
void addVillager(map<string, tuple<int, string, string>>& villagerMap) {
    string vilName, vilSpecies, vilPhrase;
    int friendLvl = -1 ;

    cout << setw(WIDTH) << "" <<"Villager name: ";
    getline(cin>>ws,vilName); //flushing white space before getline
    cout << endl;
    auto it = villagerMap.find(vilName);
    if(it != villagerMap.end()) { //stops early if key is already in map
        cout << "That villager already lives here.\n\n";
        return;
    }
    while(friendLvl < 0 || friendLvl > 10) { //input error checking
        cout << setw(WIDTH) << "" <<"Friendship level(0-10): ";
        cin >> friendLvl;
        cout << endl;
    }
    cout << setw(WIDTH) << "" <<"Species: ";
    getline(cin>>ws,vilSpecies);
    cout << endl;
    cout << setw(WIDTH) << "" <<"Catchphrase: ";
    getline(cin>>ws,vilPhrase);
    cout << endl;
    //creating temp tuple for new villager
    tuple<int, string, string> attributes(friendLvl,vilSpecies,vilPhrase);
    //inserting new villager into map
    villagerMap.insert(make_pair(vilName, attributes));

    cout << setw(WIDTH) << "" << vilName << " added.\n\n";
}
//takes a map and deletes a user-chosen villager inside
void delVillager(map<string, tuple<int, string, string>>& villagerMap) {
    string vilName;
    
    cout << setw(WIDTH) << "";
    cout << "Which villager would you like to delete?:";
    getline(cin>>ws,vilName);
    cout << endl;
    auto it = villagerMap.find(vilName);
    if(it == villagerMap.end()) { //error checking for non-existent key
        cout << "Please pick a villager that already lives in town\n\n";
        return;
    }
    villagerMap.erase(it); //erasing chosen villager
    cout << setw(WIDTH) << "" << vilName << " has been \"removed\"\n\n"; 
}
//increases all villager friendship by 1 in a map
void increaseFriendship(map<string, tuple<int, string, string>>& villagerMap) {
    //using for_each algo to increase every villagers friendship
    for_each(villagerMap.begin(), villagerMap.end(),
            [](pair<const string, tuple<int, string, string>>& vil) {
                if(get<0>(vil.second) < 10) //won't go past 10
                    get<0>(vil.second) += 1;
            });
    cout << "You threw a party!\n\n"; //flavor text
    cout << setw(WIDTH) << "" << "all villagers friendship +1\n\n";
}
//decreases all villager friendship by 1 in a map
void decreaseFriendship(map<string, tuple<int, string, string>>& villagerMap) {
    //same for_each as increaseFriendship but -1 here
    for_each(villagerMap.begin(), villagerMap.end(),
            [](pair<const string, tuple<int, string, string>>& vil) {
                if(get<0>(vil.second) > 0) //wont go below 0
                    get<0>(vil.second) -= 1;
            });
     cout << "You were a huge grump today.\n\n";
    cout << setw(WIDTH) << "" << "all villagers friendship -1\n\n";
}
//find and print details of a user-specified villager in a map
void lookupVillager(const map<string, tuple<int, string, string>>& villagerMap) {
    string vilName;

    cout << setw(WIDTH) << "" <<"Villager you wish to find: ";
    getline(cin>>ws,vilName);
    cout << endl;
    auto it = villagerMap.find(vilName);
    if(it != villagerMap.end()) { //printing villager details
        cout << "You found " << it->first << "!\n\n";
        cout << "Here are their details:\n";
        cout << setw(WIDTH) << "Friendship level: " << get<0>(it->second) << endl;
        cout << setw(WIDTH) << "Species: " << get<1>(it->second) << endl;
        cout << setw(WIDTH) << "Catchphrase: " << get<2>(it->second) << "\n";
        cout << endl;
    }
    else //error state
        cout << vilName << " doesn't live here.\n\n";
}