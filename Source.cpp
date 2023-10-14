//Name: (Chad Huntebrinker)
//Student ID Number: (12567690)
//Student Email: (crh92d@umsystem.edu)

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>

using namespace std;

void FindCurrentScore(int& userScore, char userInput, int cardNumber, string cardStatus, int totalCardsPlayed);
void DeadCards(int& deadCardsTotal, int deadCards [], char userInput, int cardNumber, string cardStatus);
void LiveCards(int& liveCardsTotal, int liveCards[], char userInput, int cardNumber, string cardStatus);
string NextCard(int cardsToPlay[], int& cardsToPlayTotal, int cards[], int cardsTotal, int& cardNumber);

int main() {

	char goAgain;

	do {
	//For Score
	int userScore = 0;
	//For live and dead cards
	int deadCardsTotal = 0;
	int liveCardsTotal = 16;
	int deadCards[16];
	int liveCards[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	//For the card
	int cardNumber = 0;
	int cardsToPlay[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	int cardsToPlayTotal = 16;
	string cardStatus;
	//Keeping track of how many cards have been played
	int totalCardsPlayed = 0;
	//Keeping track of take it or leave it
	char userInput = 'N';
	

	srand(time(NULL));
	

		
		
		do {
				FindCurrentScore(userScore, userInput, cardNumber, cardStatus, totalCardsPlayed);

				if (totalCardsPlayed < 16) {
					DeadCards(deadCardsTotal, deadCards, userInput, cardNumber, cardStatus);


					LiveCards(liveCardsTotal, liveCards, userInput, cardNumber, cardStatus);


					cardStatus = NextCard(cardsToPlay, cardsToPlayTotal, deadCards, deadCardsTotal, cardNumber);
				}
			cout << endl;
			if (cardStatus != "Dead" && totalCardsPlayed < 16) {
				cout << "Take it [T] or Leave it [L]? " << endl;
				cin >> userInput;
				userInput = toupper(userInput);
				cout << endl;
			}
			++totalCardsPlayed;
		} while (totalCardsPlayed < 17);
		cout << "Final Score: " << userScore << endl;
		cout << endl;
		cout << "Enter q to quit and any other key to go again." << endl;
		cin >> goAgain;
		goAgain = toupper(goAgain);
	} while (goAgain != 'Q');

	return 0;
}

void FindCurrentScore(int& userScore, char userInput, int cardNumber, string cardStatus, int totalCardsPlayed) {
	if (cardStatus != "Dead") {
		if (userInput == 'T') {
			userScore = userScore + cardNumber;
			
		}
	}
	else {
		userScore = userScore;
	}
	
	if (totalCardsPlayed < 16) {
		cout << "Current score: " << userScore << endl;
	}
}

void DeadCards(int& deadCardsTotal, int deadCards[], char userInput, int cardNumber, string cardStatus) {
	int i;
	int smallestNumber;
	int temp;
	cout << "Dead cards: ";
	if (cardStatus != "Dead") {
		if (userInput == 'L') {
			deadCards[deadCardsTotal] = cardNumber;
			++deadCardsTotal;
		}
		else if (userInput == 'T') {
			int numOccur;
			int x;
			for (x = cardNumber; x > 0; --x) {
				numOccur = 0;
				for (i = 0; i < deadCardsTotal; ++i) {
					if (deadCards[i] == x) {
						++numOccur;
					}
				}
				if (numOccur == 0) {
					deadCards[deadCardsTotal] = x;
					++deadCardsTotal;
				}
			}
		}
		for (i = 0; i < deadCardsTotal - 1; ++i) {
			smallestNumber = i;
			for (int j = i + 1; j < deadCardsTotal; ++j) {

				if (deadCards[j] < deadCards[smallestNumber]) {
					smallestNumber = j;
				}
			}
			temp = deadCards[i];
			deadCards[i] = deadCards[smallestNumber];
			deadCards[smallestNumber] = temp;
		}
	}
	for (int i = 0; i < deadCardsTotal; ++i) {
		cout << setw(3) << right << deadCards[i];
	}
	
	cout << endl;
}

void LiveCards(int& liveCardsTotal, int liveCards[], char userInput, int cardNumber, string cardStatus) {
	int i;
	int temp;
	cout << "Live cards: ";
	if (cardStatus != "Dead") {
		if (userInput == 'L') {
			for (i = 0; i < liveCardsTotal; ++i) {
				if (liveCards[i] == cardNumber) {
					for (int j = i; j < liveCardsTotal; ++j) {
						temp = liveCards[j + 1];
						liveCards[j] = temp;
					}
					--liveCardsTotal;
				}
			}
		}
		else if (userInput == 'T') {
			int c = -1;
			for (i = 0; i < liveCardsTotal; ++i) {
				if (liveCards[i] == cardNumber) {
					c = i;
					break;
				}
			}
			for (int x = c; x > -1; --x) {
					for (int y = x; y < liveCardsTotal; ++y) {
						temp = liveCards[y + 1];
						liveCards[y] = temp;
					}
					--liveCardsTotal;
				--cardNumber;
			}
		}
	}

	for (i = 0; i < liveCardsTotal; ++i) {
		cout << setw(3) << right << liveCards[i];
	}
	cout << endl;
}

string NextCard(int cardsToPlay[], int& cardsToPlayTotal, int cards[], int cardsTotal, int& cardNumber) {
	int i, temp;
	string cardStatus;
	do {
		cardNumber = (rand() % 16);
		cardNumber = cardsToPlay[cardNumber];
	} while (cardNumber < 0);
		
		for (int i = 0; i < cardsTotal; ++i) {
			if (cardNumber == cards[i]) {
				cardStatus = "Dead";
				break;
			}
			else {
				cardStatus = "  ";
			}
		}
		cout << "Next card: " << cardNumber << "  " << cardStatus << endl;
		for (i = 0; i < cardsToPlayTotal; ++i) {
			if (cardsToPlay[i] == cardNumber) {
				for (int j = i; j < cardsToPlayTotal; ++j) {
					temp = cardsToPlay[j + 1];
					cardsToPlay[j] = temp;
				}
				--cardsToPlayTotal;
			}
		}
		return cardStatus;
}