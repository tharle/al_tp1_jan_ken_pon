#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

/*
* TP1 - Faire un jan ken pon
*/


/**
* **********************************************
* CONSTANTS
* **********************************************
*/
const int TITLE_SCREEN_NOUVELLE_PARTIE = 1;
const int TITLE_SCREEN_QUITTER = 2;
const int SCORE_LIMIT_POUR_FINIR_GAME = 3;
const string NAME_PLAYER_NON_SET = "NON_PLAYER";


/**
* **********************************************
* VARIABLES DU PLAYER
* **********************************************
*/
string namePlayer = NAME_PLAYER_NON_SET;
int scorePlayer = 0; 
int scorePc = 0;

void afficherNouvellePartie();
void afficherPartie();
void afficherScore();
void afficherExplications();
void afficherResultatParciel();
void AfficherResultatFinal();

bool isFinitPartie();
bool isPlayerWin();
bool isPcWin();

void waitEnter() 
{
	system("pause");
}

void cleanScreen() 
{
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void afficherTitleScreen() 
{
	int option = -1;
	while (option != TITLE_SCREEN_QUITTER) 
	{
		cleanScreen();
		cout << "Bienvenue au JAN KEN PON!" << endl;
		cout << "[" << TITLE_SCREEN_NOUVELLE_PARTIE << "] - Nouvelle partie" << endl;
		cout << "[" << TITLE_SCREEN_QUITTER << "] - Quitter" << endl;
		cin >> option;

		if (option == TITLE_SCREEN_NOUVELLE_PARTIE)
		{
			afficherNouvellePartie();
		}
	}
	
}

bool isNamePlayerExist()
{
	return namePlayer.compare(NAME_PLAYER_NON_SET) != 0;
}

void afficherNewNamePlayer() 
{
	cleanScreen();
	cout << "Comment tu t'appelle?" << endl;
	cin >> namePlayer;
}

void afficherNouvellePartie() 
{
	if (!isNamePlayerExist()) 
	{
		afficherNewNamePlayer();
	}

	afficherPartie();
}

void afficherPartie() 
{
	cout << "Bienvenue " << namePlayer << endl;
	
	while(!isFinitPartie())
	{
		// continuer la partie
	}
}

bool isFinitPartie() {
	return isPlayerWin() || isPcWin();
}

bool isPlayerWin()
{
	return scorePlayer >= SCORE_LIMIT_POUR_FINIR_GAME;
}

bool isPcWin()
{
	return scorePc >= SCORE_LIMIT_POUR_FINIR_GAME;
}

void afficherExplications() 
{

}

void main() 
{
	afficherTitleScreen();
	
}