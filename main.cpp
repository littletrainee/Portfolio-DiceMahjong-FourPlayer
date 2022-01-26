#include <iostream>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <tuple>
#include <vector>
#include <ctype.h>

using namespace std;

bool Wincheck(vector<int> playerhand,bool returnbool){
	vector<int> pair;							   // create vector<int> pair
	vector<int> temphand(playerhand);						   // create vector<int> temphand clone from playerhand
	for (int i = 1; i < 7; i++)					   // check has pair from 1 to 6 one by one
		if (count(temphand.begin(), temphand.end(), i) >= 2) // if the count i(1-6) is 2(pair)
			pair.push_back(i);					   // add i to vector<int> pair
	if (!pair.empty())							   // if pair is not empty
		for (auto const &poptile : pair){ // try to pop pair from playerhand
			for (int i = 0; i < 2; i++){
				vector<int>::iterator it = find(temphand.begin(), temphand.end(), poptile);
				temphand.erase(it);
			}
			if ((temphand[0] + 1 == temphand[1] && temphand[1] + 1 == temphand[2]) || (temphand[0] == temphand[1] && temphand[1] == temphand[2])){							  // check meld(turiple or sequence)
				returnbool = !returnbool;		  // player is winning gameswitch set to false
				break;
			}else{
				temphand.clear();
				temphand.assign(playerhand.begin(), playerhand.end());
			}
		}
	return returnbool;
}

void printallplayerhand(string player1name, string player2name, string player3name, string player4name, vector<int> player1hand, vector<int> player2hand, vector<int> player3hand, vector<int> player4hand,int temphand){
	cout << player1name << ": ";
	for (const auto &target : player1hand)
		cout << target << ' ';
	cout << endl;
	cout << player2name << ": ";
	for (const auto &target : player2hand)
		cout << target << ' ';
	cout << endl;
	cout << player3name << ": ";
	for (const auto &target : player3hand)
		cout << target << ' ';
	cout << endl;
	cout << player4name <<"; ";
	for (const auto &target : player4hand)
		cout << target << ' ';
	cout << endl;
	cout << temphand << endl;
}

vector<int> DrawCardAndSort(vector<int> &targetvector, int i){ // player drawcard
	int min = 1;
	int max = 6;
	targetvector.clear();
	for (i; i < 5; i++)
		targetvector.push_back((int)rand() % (max - min + 1) + min);
	sort(targetvector.begin(),targetvector.end());
	return targetvector;
}

pair<vector<int>, int> Discard(vector<int> &playerhand){
	char keyin;
	int target;
	vector<int> temphand(playerhand); // create a temphand vector
	cout << "Please select whitch one do you want to discard from 1-5:";
	cin >> keyin;
	while (isdigit(keyin) == false && (int)keyin != 1 && (int)keyin != 2 && (int)keyin != 3 && (int)keyin != 4 && (int)keyin != 5){
		cout << "please renter select:";
		cin >> keyin;
	}
	target = (int)keyin - 48;
	cout << "the secect is " << playerhand[target - 1] << endl;
	vector<int>::iterator it = temphand.begin() + target - 1;
	target = *it;
	temphand.erase(it);
	return make_pair(temphand, target); // make pair to return value
}

bool Check(vector<int> &playerhand, int temphand, bool returnbool){
	playerhand.push_back(temphand);												// add temphand to target playerhand
	sort(playerhand.begin(), playerhand.end());									// sor target playerhand
	returnbool = Wincheck(playerhand,returnbool);											// check target playerhand is winning hand(ron)
	if (returnbool)															// if target playerhand isn't winning hand(ron)
		playerhand.erase(find(playerhand.begin(), playerhand.end(), temphand)); // remove temphand value from target playerhand
	return returnbool;															// and return winning vector
}

int main(void){
	srand(time(NULL)); // set seed to random
	//declare vector
	vector<int> player1hand;
	vector<int> player2hand;
	vector<int> player3hand;
	vector<int> player4hand;
	// declare int
	int gameturn = 0;
	int temphand = 0;
	// declare string
	string player1name = "Player1";
	string player2name = "player2";
	string player3name = "player3";
	string player4name = "player4";
	// declare bool
	bool returnbool = true;
	// game start drawcard and sort, player1 is 5 other(player2, player3 and player4) is 4
	DrawCardAndSort(player1hand, 0);
	DrawCardAndSort(player2hand, 1);
	DrawCardAndSort(player3hand, 1);
	DrawCardAndSort(player4hand, 1);
	// print all playerhand 
	printallplayerhand(player1name, player2name, player3name, player4name, player1hand, player2hand, player3hand, player4hand, temphand);
	returnbool = Wincheck(player1hand,returnbool);// check player1 is winning
	while (returnbool){ // if player1 isn't winning then
		gameturn == 3 ? gameturn -=3 : gameturn += 1; // turn to next player
		if (gameturn == 0){ // player1 wincheck function
			tie(player4hand, temphand) = Discard(player4hand); // player4 discard from player4hand to temphand
			returnbool = Check(player1hand, temphand, returnbool); // check player1 is winning(ron)
			if (returnbool){ // if player1 isn't winning(ron)
				returnbool = Check(player2hand, temphand, returnbool); // check player2 is winning(ron)
				if (returnbool){// if player2 isn't winning(ron)
					returnbool = Check(player3hand, temphand,returnbool); // check player3 is winning(ron)
					if(returnbool){ // if player3 isn't winnint(ron)
						DrawCardAndSort(player1hand, 0); // redrawcard to player1hand and sort
						returnbool = Wincheck(player1hand,returnbool); // check player1 is winning(tsu-mo)
						printallplayerhand(player1name, player2name, player3name, player4name, player1hand, player2hand, player3hand, player4hand, temphand); // print all playerhand
					}else // if player3 is wiinning(ron)
						gameturn = 2; // set gameturnto 2(player3)
				}else  // if player2 is winning(ron)
					gameturn = 1; // set gameturn to 1(player2)
			}else // if player1 is winning(ron)
				gameturn = 0; // set gameturn to 0(player1)
		}else if (gameturn == 1){ // player2 wincheck function
			tie(player1hand, temphand) = Discard(player1hand); // player1 discard from player1hand to temphand
			returnbool = Check(player2hand, temphand, returnbool); // check player2 is winning(ron)
			if (returnbool){ // if player2 isn't winning(ron)
				returnbool = Check(player3hand, temphand, returnbool); // check player3 is winning(ron)
				if (returnbool){ // if player3 isn't winning(ron)
					returnbool = Check(player4hand,temphand,returnbool); // check player4 is winning(ron)
					if(returnbool){ // if player4 isn't winnint(ron)
						DrawCardAndSort(player2hand, 0); // redrawcard to player2hand and sort
						returnbool = Wincheck(player2hand,returnbool); // check player2 is winning(tsu-mo)
						printallplayerhand(player1name, player2name, player3name, player4name, player1hand, player2hand, player3hand, player4hand, temphand); // print all playerhand
					}else // if player4 is winning(ron)
						gameturn = 3; // set gameturn to 3(player4)
				}else // if player3 is winning(ron)
					gameturn = 2; // set gameturn to 2(player3)
			}else // if player2 is winning(ron)
				gameturn = 1; // set gameturn to 1(player2)
		}else if (gameturn == 2){ // player3 wincheck function
			tie(player2hand, temphand) = Discard(player2hand); // player2 discard from player2hand to temphand
			returnbool = Check(player3hand, temphand, returnbool); // check player3 is winning(ron)
			if (returnbool){ // if player3 isn't winning(ron)
				returnbool = Check(player4hand, temphand, returnbool);// check player4 is winning(ron)
				if (returnbool){ // if player4 isn't winning(ron)
					returnbool = Check(player1hand, temphand, returnbool); // check player1 is winning(ron)
					if (returnbool){ // if  player1 isn't winning(ron)
						DrawCardAndSort(player3hand, 0); // redrawcard to player3hand and sort
						returnbool = Wincheck(player3hand,returnbool); // check player3 is winning(tsu-mo)
						printallplayerhand(player1name, player2name, player3name, player4name, player1hand, player2hand, player3hand, player4hand, temphand); // print all playerhand
					}else // if player1 is winning(ron)
						gameturn = 0; // set  gameturn to 0(player1)
				}else // if player4 is winning(ron)
					gameturn = 3; // set gameturn to 3(player3)
			}else // if player3 is winning(ron)
				gameturn = 2; // set gameturn to 2(player3)
		}else if (gameturn == 3){ // player4 wincheck function
			tie(player3hand,temphand) = Discard(player3hand); // player3 discard from player3hand to temphand
			returnbool = Check(player4hand, temphand,returnbool); // check player4 is winning(ron)
			if (returnbool){ // if player4 isn't winnint(ron)
				returnbool = Check(player1hand, temphand, returnbool); //check player1 is winning(ron)
				if (returnbool){ // if player1 isn't winnint(ron)
					returnbool = Check(player2hand, temphand,returnbool); // check player2 is winning(ron)
					if(returnbool){ // if player2 isn't winning(ron)
						DrawCardAndSort(player4hand,0); // redrawcard to player4hand and sort
						returnbool = Wincheck(player4hand,returnbool); // check player4 is winning(tsu-mo)
						printallplayerhand(player1name, player2name, player3name, player4name, player1hand, player2hand, player3hand, player4hand, temphand); // print all playerhand
					}else // if player2 is winning(ron)
						gameturn = 1; // set gameturn to 1(player2)
				}else // if player1 is winning(ron)
					gameturn = 0; // set gameturn to 0(player1)
			}else // if player4 is winning(ron)
				gameturn = 3; // set gameturn to 3(player4)
		}
	}
	if (gameturn == 0)
		cout << "The Winner Is Player1" << endl;
	else if (gameturn == 1)
		cout << "The Winner Is Player2" << endl;
	else if (gameturn == 2)
		cout << "The Winner Is Player3" << endl;
	else if (gameturn ==3)
		cout << "The Winner Is Player4" << endl;
	return 0;
}
