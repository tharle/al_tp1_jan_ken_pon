#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib> // srand rand
#include <ctime>  // time

using std::cout;
using std::cin;
using std::endl;
using std::string;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds


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

const int CHOIX_REGLES = 0;
const int CHOIX_ROCHE	= 1;
const int CHOIX_PAPIER	= 2;
const int CHOIX_CISEAUX	= 3;


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
void afficherRegles();
void afficherResultatParciel();
void afficherResultatFinal();
int demanderChoixPlayer();
void waitEnter();
void wait();
void wait(int secs);

void cleanScreen();
void separateur();

bool isFinitPartie();
bool isPlayerWin();
bool isPcWin();


void playerChoisiRoche();
void playerChoisiPapier();
void playerChoisiCiseaux();
void genereteOptionPC();




void main()
{
	afficherTitleScreen();

}



// Attendez le une touche du clavier d'utilisateur
void waitEnter() 
{
	system("pause");
}


// Arreter le programme et attendre quelque seconds pour le repartir
void wait(int secs) 
{
	sleep_until(system_clock::now() + seconds(secs));
}

// Arreter le programme et attendre 1 second pour le repartir
void wait() 
{
	wait(1);
}

// netoyer l'ecran 
void cleanScreen() 
{
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

// ajoute une ligne de separation, jusque parce qu'il est beau.
void separateur() 
{
	cout << "----------------------------------------------------------- " << endl;
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
	cleanScreen();
	cout << "Attendez un peu, ta partie est en train d'etre configuree...";
	wait(3);
	cleanScreen();
	cout << "Bienvenue " << namePlayer << endl;
	
	while(!isFinitPartie())
	{
		// continuer la partie
		afficherJeuMenu();

	}
}

void afficherJeuMenu() 
{
	int opt = demanderChoixPlayer();
	switch (opt)
	{
		case CHOIX_REGLES:
		afficherRegles();
		break;
		case CHOIX_ROCHE:
			playerChoisiRoche();
			break;
		case CHOIX_PAPIER:
			playerChoisiPapier();
			break;
		case CHOIX_CISEAUX:
			playerChoisiCiseaux();
			break;
		default:
			mouvaisOption();
		break;
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

void afficherRegles() 
{
	cleanScreen();
	separateur();
	cout << "LES REGLES DE JAN-KEN-POW";
	separateur();
}

int demanderChoixPlayer() 
{
	int opt = -1;
	while (opt < 4 || opt > 0)
	{
		cout << "[1] Roche";
		cout << "[2] Papier";
		cout << "[3] Cisaux";
		cout << "[0] Regles";
		cout << "Tapez le ton choix: ";
		cin >> opt;
	}

	return opt;
}

/*
* Verifier qui ganhe la partie;
* 1 Player
* 0 Tie
* -1 PC
*/
int verifierQuiGanhe(int choixPlayer, int choixPC)
{
	cout << "Tu as choisi ROCHE!" << cout;
	//int optPC = genereteOptionPC();

	if(choixPlayer == choixPC) return 0;
	if (choixPlayer == CHOIX_ROCHE && choixPC == CHOIX_CISEAUX) return 1;
	if (choixPlayer == CHOIX_PAPIER && choixPC == CHOIX_ROCHE) return 1;
	if (choixPlayer == CHOIX_ROCHE && choixPC == CHOIX_PAPIER) return -1;
	if (choixPlayer == CHOIX_PAPIER && choixPC == CHOIX_CISEAUX) return -1;
	
}

void playerChoisiPapier() 
{
	cout << "Tu as choisi PAPIER!" << cout;
}

void playerChoisiCiseaux() 
{
	cout << "Tu as choisi CISEAUX!" << cout;
}

int genereteOptionPC() 
{
	cout << "Le PC est en train de choisir!" << cout;
	wait(3);
	srand(time(0));
	return rand() % 3 + 1;
}