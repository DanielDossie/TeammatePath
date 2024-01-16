#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <cctype>
#include <ctype.h>
#include <unistd.h>
#include <algorithm>
#include "LLNode.h"
#include "Vertex.h"
#include <math.h>

using namespace std;
//vector<Vertex *> nodes;
const int tableSize = 16150;
//vector<vector<Vertex *>>hashtable;
vector<Vertex *> hashtable[tableSize];
//hashtable.reserve(tablesize);

int hashFunction(string name) {
    int result = 0;
    for(size_t i = 0; i < name.length(); ++i) {
        result += name[i] * pow(2, i);
    }
    //cout << result << endl;
    //cout << result % tableSize << endl;
    return result % tableSize;

}

void echo(string filename) {
    string line;
    ifstream file;
    file.open(filename);
    while(getline(file, line)) {
        cout << line << endl;
    }
    //file.close();
}

bool playerYearSort(Vertex *i, Vertex *j) {
    if (i->count == j->count) {
        return i->getName() < j->getName();
    }
    return i->count > j->count;
}

void teamSort(string teamname) {
    vector<Vertex *> sorting;
    bool teamExists = false;
    int hashIndex = hashFunction(teamname);
    for (long unsigned int i = 0; i < hashtable[hashIndex].size(); i++) {
        if (hashtable[hashIndex].at(i)->getName() == teamname) {
            teamExists = true;
            for (LLNode *np = hashtable[hashIndex].at(i)->list.getHead(); np != nullptr; np = np->next) {
		        np->data->count++;
                sorting.push_back(np->data);
            }
        }
    }
    if (teamExists == false) {
        cout << "Team does not Exist" << endl;
        exit(1);
    }
    sort(sorting.begin(), sorting.end(), playerYearSort);
    string mostRecentPlayer = "";
    for(long unsigned int i = 0; i < sorting.size(); i++) {
        if (sorting.at(i)->getName() == mostRecentPlayer) {
            continue;
        }
        mostRecentPlayer = sorting.at(i)->getName();
        cout << sorting.at(i)->getName() << " played " << 
        sorting.at(i)->count << " years for the " << teamname << endl;
    }
}

bool sortByYear(Vertex *i, Vertex *j) {
    return (i->getYear() < j->getYear());
}

void teamsByYear(string playername) {
    vector<Vertex *> sorting;
    int index = -1;
    /*for(long unsigned int i = 0; i < nodes.size(); i++) {
        if(nodes.at(i)->getName() == playername) {
            index = i;
            break;
        }
    } */
    int hashIndex = hashFunction(playername);
    for (long unsigned int i = 0; i < hashtable[hashIndex].size(); i++) {
        if(hashtable[hashIndex].at(i)->getName() == playername) {
            index = i;
            break;
        }
    }
    if(index == -1) {
        cout << "Player " << playername << " not found." << endl;
        return;
    }
    else {
        for (LLNode *np = hashtable[hashIndex].at(index)->list.getHead(); np != nullptr; np = np->next) {
		    sorting.push_back(np->data);
        }
    }

    sort(sorting.begin(), sorting.end(), sortByYear);

    for(long unsigned int i = 0; i < sorting.size(); i++) {
        cout << hashtable[hashIndex].at(index)->getName() << " played for the " << 
        sorting.at(i)->getYear() << " " << sorting.at(i)->getName() << endl;
    }
}

void specTeam(string playername, string tname) {
    vector<Vertex *> sorting;
    int hashIndex = hashFunction(playername);
    int index = -1;
    for(long unsigned int i = 0; i < hashtable[hashIndex].size(); i++) {
        if(hashtable[hashIndex].at(i)->getName() == playername) {
            index = i;
            break;
        }
    } 
    if(index == -1) {
        cout << playername << " does not appear in the input file." << endl;
        return;
    }
    else {
        bool hasPlayed = false;
        for (LLNode *np = hashtable[hashIndex].at(index)->list.getHead(); np != nullptr; np = np->next) {
            if(np->data->getName() == tname) {
                hasPlayed = true;
                sorting.push_back(np->data);
            }
        }
        if (hasPlayed == false) {
            cout << playername << " has never played for the " << tname << endl;
            return;
        }
    }

    sort(sorting.begin(), sorting.end(), sortByYear);

    for(long unsigned int i = 0; i < sorting.size(); i++) {
        cout << hashtable[hashIndex].at(index)->getName() << " played for the " << 
        sorting.at(i)->getYear() << " " << sorting.at(i)->getName() << endl;
    }
}

Vertex *BFS(LL *queue, string player2name, string teamname, bool teamSearch){
    while(queue->getHead() != nullptr){
        LLNode* node;
        node = queue->remove();
        node->data->setColor("black");
        if((!teamSearch) || (!node->data->team) || ((teamSearch && node->data->team) && (teamname == node->data->getName()))) {
            //cout << node->data->getName() << " " << teamname << endl;
            for (LLNode *np = node->data->list.getHead(); np != nullptr; np = np->next) {
                if (np->data->getColor() == "white"){
                    np->data->setColor("gray");
                    if(np->data->team){
                        np->data->setDistance(node->data->getDistance());
                    }else{
                        np->data->setDistance(node->data->getDistance()+1);
                    }

                    if(np->data->team){
                        np->data->setPred(node->data);
                    }else{
                        np->data->setPred(node->data->getPred());
                    }
                    if(node->data->team) {
                        np->data->predTeam = node->data;
                    }

                    queue->insert(np);
                    if(np->data->getName() == player2name) {
                        return np->data;
                    }
                    
                }
            }
        }
    }
    return nullptr;
}

int main(int argc, char *argv[]) {
    LL *queue = new LL();
    //Vertex *Tvertex = new Vertex();
    //Vertex *Pvertex = new Vertex();
    vector<Vertex *> toDelete;
    int op;
    string line;
    string inputfilename;
    string playerName1;
    string playerName2;
    //Vertex Pvertex;
    //Vertex Tvertex;
    if(argc < 2) {
        cout << "missing args" << endl;
        exit(1);
    }
    if(strcmp(argv[1], "-i") != 0) {
        cout << "invalid input" << endl;
        exit(1);
    }
    inputfilename = argv[2];
    ifstream file;
    file.open(inputfilename);

    if(!(file.is_open())){
        cout << "File did not open properly" << endl;
        return 0;
    }

        //while (!(file.eof())){
    int sCount = 0;
    int dCount = 0;
    int tCount = 0;
    string player1name;
    string player2name;
    string teamname;
    while((op = getopt(argc, argv, ":i:s:d:t:")) != -1) {
        switch(op) {
            case 'i':
                break;
            case 's':
                player1name = optarg;
                sCount++;
                break;
            case 'd':
                player2name = optarg;
                dCount++;
                break;
            case 't':
                teamname = optarg;
                tCount++;
                break;
            case '?':
                cout << "Bad input" << endl;
                exit(1);
                break;
        }
    }

    if(dCount > 0 && sCount == 0) {
        cout << "must provide player1 name" << endl;
        exit(1);
    }
    if(sCount == 0 && dCount == 0 && tCount == 0) {
        echo(inputfilename);
        exit(1);
    }

    string name;
    string team;
    int year;
    bool teamExists = false;
    bool playerExists = false;

    /*
    LLNode *teamNode;// = new LLNode(hashtable[teamHash].at(teamIndex));
    LLNode *playerNode;// = new LLNode(hashtable[playerHash].at(playerIndex));
    */

    while (getline(file, line)){
        stringstream s_stream(line);
        for (int i = 0; i < 3; i++) {
            string substr;
            getline(s_stream, substr, ',');
            if (i == 0) {
                name = substr;
            }
            else if (i == 1) {
                team = substr;
            }
            else {
                year = stoi(substr);

            }
        }

        int teamIndex;
        int playerHash = hashFunction(name);
        int teamHash = hashFunction(team);

        for (long unsigned int i = 0; i < hashtable[teamHash].size(); i++) {
            //cout << i << endl;
            if (hashtable[teamHash].at(i)->getName() == team && hashtable[teamHash].at(i)->getYear() == year) {
                teamExists = true;
                teamIndex = i;
            }
        }
        if (teamExists == false) {
            Vertex *Tvertex = new Vertex();
            Tvertex->teamRead(team, year);
            hashtable[teamHash].push_back(Tvertex);
            teamIndex = hashtable[teamHash].size()-1;
            //toDelete.push_back(Tvertex);
            //delete Tvertex;
        }
        teamExists = false;

        int playerIndex;

        for (long unsigned int i = 0; i < hashtable[playerHash].size(); i++) {
            if (hashtable[playerHash].at(i)->getName() == name) {
                playerExists = true;
                playerIndex = i;
            }
        }
        if (playerExists == false) {
            Vertex *Pvertex = new Vertex();
            Pvertex->playerRead(name);
            hashtable[playerHash].push_back(Pvertex);
            playerIndex = hashtable[playerHash].size()-1;
            //toDelete.push_back(Pvertex);
            //delete Pvertex;
        }

        playerExists = false;
        /*
        cout << "Name " << name << endl;
        cout << "Team " << team << endl;
        cout << "Year " << year << endl;
        */
        //}

        
        LLNode *teamNode = new LLNode(hashtable[teamHash].at(teamIndex));
        LLNode *playerNode = new LLNode(hashtable[playerHash].at(playerIndex));
        
        /*
        teamNode = new LLNode(hashtable[teamHash].at(teamIndex));
        playerNode = new LLNode(hashtable[playerHash].at(playerIndex));
        */

        hashtable[teamHash].at(teamIndex)->list.insert(playerNode);
        hashtable[playerHash].at(playerIndex)->list.insert(teamNode);

        /*
        LL *deleteList = new LL();
        deleteList->insert(teamNode);
        deleteList->insert(playerNode);
        */
        
        //cout << nodes.at(nodes.size() - 1)->list.getNumElements() << endl;
        //delete teamNode;
        //delete playerNode;
        //teamNode->~LLNode();
        //delete deleteList;
    }

    /*
    //cout << nodes.size() << endl;
    for (long unsigned int i = 0; i < nodes.size(); i++) {
        //cout << nodes.at(i)->getName() << nodes.at(i)->getYear() << endl;
        //cout << nodes.at(i)->list.getNumElements() << endl;
        //cout << nodes.at(i) << endl;
        nodes.at(i)->list.show();
    }
    */

    if(sCount > 0 && dCount == 0 && tCount == 0) {
        teamsByYear(player1name);
    }
    else if(sCount > 0 && dCount == 0 && tCount > 0) {
        specTeam(player1name, teamname);
    }else if (sCount == 0 && dCount == 0 && tCount > 0) {
        teamSort(teamname);
    }else if(sCount > 0 && dCount > 0){
        
        int playerHash = hashFunction(player1name);
        int playerInd = -1;
        for (long unsigned int i = 0;i < hashtable[playerHash].size(); i++){
            if (player1name == hashtable[playerHash].at(i)->getName()){
                playerInd = i;
                break;
            }
        }
        if(playerInd == -1){
            cout << "Player not found." << endl;
            delete queue;
            exit(1);
        }
        hashtable[playerHash].at(playerInd)->setColor("gray");
        hashtable[playerHash].at(playerInd)->setDistance(0);

        LLNode *newnode = new LLNode(hashtable[playerHash].at(playerInd));

        queue->insert(newnode);
        Vertex *player2;
        if(tCount == 0) {
            player2 = BFS(queue, player2name, "", false);
        }
        else {
            player2 = BFS(queue, player2name, teamname, true);
        }
        
        if(player2 == nullptr) {
            cout << "No teammate path exists between " << player1name << " and " << player2name << endl;
            exit(1);
        }
        cout << player2name << "'s " << player1name << " number is " << player2->getDistance() << endl;
        vector<Vertex *> path;
        Vertex *dummy = new Vertex();
        path.push_back(dummy);
        for (Vertex *np = player2; np != nullptr; np = np->getPred()) {
            path.push_back(np);
        }
        for(long unsigned int i = path.size() - 2; i > 0; i--) {
            cout << path.at(i)->getPred()->getName() << " played with " << path.at(i)->getName() << " on the " << 
            path.at(i)->predTeam->getYear() << " " << path.at(i)->predTeam->getName() << endl;
        }
        delete dummy;
        delete newnode;
        //delete queue;
    }else {
        //bad commands
    }
    delete queue;
    //delete Pvertex;
    //delete Tvertex;
    
    for(int i = 0; i < tableSize; i++) {
        for(long unsigned int j = 0; j < hashtable[i].size(); j++) {
            /*
            if(!hashtable[i].at(j)->team) {
                for (LLNode *np = hashtable[i].at(j)->list.getHead(); np != nullptr; np = np->next) {
                    int removeHash = hashFunction(np->data->getName());
                    for(long unsigned int k = 0; k < hashtable[removeHash].size(); k++) {
                        if(hashtable[removeHash].at(k)->getName() == np->data->getName()) {
                            hashtable[removeHash].erase(hashtable[removeHash].begin() + k);
                        }
                    }
                    
                }
            }
            */
            /*
            if(!hashtable[i].at(j)->team) {
                delete hashtable[i].at(j);
            }
            */
            delete hashtable[i].at(j);
            
        }
    }
    
    /*
    for(long unsigned int i = 0; i < toDelete.size(); i++) {
        delete toDelete.at(i);
    }
    */
}