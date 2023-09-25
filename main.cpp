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

const int WIN_TIE = 90;
const int WIN_PLAYER = 91;
const int WIN_PC = 92;


/**
* **********************************************
* VARIABLES DU PLAYER
* **********************************************
*/
string namePlayer = NAME_PLAYER_NON_SET;
int scorePlayer = 0; 
int scorePc = 0;

void afficherMessageMauvaisOption();
void afficherMessageGameOver(string mensage);
void afficherNouvellePartie();
void afficherPartie();
void afficherRegles();
void afficherResultat();
void afficherPlayerChoix(int choixPlayer);
void afficherTitleScreen();


void runJanKenPon();
void runCombat(int choixPlayer);
void runScore(int winnerOption);


void waitEnter();
void wait();
void wait(int secs);

void cleanScreen();
void separateur();

bool isFinitPartie();
bool isNamePlayerExist();
bool isPlayerWin();
bool isPcWin();

int calculerWinner(int choixPlayer);
void choisirNewNamePlayer();
string choixToString(int choixPlayer);
int demanderChoixPlayer();
void verifyJeuEstFini();
int genereteOptionPC(int choixPlayer);

int main()
{
	afficherTitleScreen();

}


/*******************************************************************
*
* AFFICHAGE
*
*******************************************************************/

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
		else if(option != TITLE_SCREEN_QUITTER) {
			afficherMessageMauvaisOption();
			waitEnter();
		}
	}
	
}

void afficherNouvellePartie() 
{
	if (!isNamePlayerExist()) 
	{
		choisirNewNamePlayer();
	}

	afficherPartie();
}

void afficherPartie() 
{
	cleanScreen();
	cout << "Attendez un peu, ta partie est en train d'etre configuree...";
	scorePlayer = 0;
	scorePc = 0;
	wait(3);
	cleanScreen();
	cout << "Bienvenue " << namePlayer << endl;
	
	while(!isFinitPartie())
	{
		// continuer la partie
		afficherResultat();
		runJanKenPon();
	}
}

void afficherRegles()
{
	cleanScreen();
	separateur();
	cout << "LES REGLES DE JAN-KEN-POW";
	separateur();
}

void afficherPlayerChoix(int choixPlayer)
{
	cout<< "Tu as choisi " << choixToString(choixPlayer) << "!" << endl;
}

void afficherResultat() 
{
	separateur();
	cout << "\t\tSCORE DE LA PARTIE" << endl;
	cout << "\t\t[" << scorePlayer << "] " << namePlayer << " X [" << scorePc << "] PC" << endl;
	separateur();
}

void afficherMessageMauvaisOption() 
{
	cout << "Option invalide. STP, Choisir un autre option" << endl;
}

/*******************************************************************
*
* RUN EXTRAS
*
*******************************************************************/

void runJanKenPon()
{
	int choixPlayer = demanderChoixPlayer();
	switch (choixPlayer)
	{
		case CHOIX_REGLES:
			afficherRegles();
			break;
		case CHOIX_ROCHE:
			runCombat(choixPlayer);
			break;
		case CHOIX_PAPIER:			
			runCombat(choixPlayer);
			break;
		case CHOIX_CISEAUX:
			runCombat(choixPlayer);
			break;
		default:
			afficherMessageMauvaisOption();
		break;
	}
}

void runCombat(int playerChoix)
{
	afficherPlayerChoix(playerChoix);
	int winnerOption = calculerWinner(playerChoix);

	// add score
	runScore(winnerOption);

	//valider si game over
	verifyJeuEstFini();

	cleanScreen();
}

void runScore(int winnerOption)
{
	string mensageWinner = "";
	switch (winnerOption)
	{
		case WIN_PLAYER:
			scorePlayer++;
			mensageWinner = "Le "+namePlayer+" a gagne ce tour!";
		break;
		case WIN_PC:
			scorePc++;
			mensageWinner = "Le PC a gagne ce tour!";
			break;
		default:
			mensageWinner = "Le jeu est nul. Personne ni machine a ganhe!";
		break;
	}

	cout << mensageWinner << endl;
}

int demanderChoixPlayer()
{
	int playerChoix = -1;
	while (playerChoix >= 4 || playerChoix <= -1)
	{
		cout << "\t\t[1] Roche" << endl;
		cout << "\t\t[2] Papier" << endl;
		cout << "\t\t[3] Cisaux" << endl;
		cout << "\t\t[0] Regles" << endl;
		cout << "Tapez le ton choix: ";
		cin >> playerChoix;
	}

	return playerChoix;
}

bool isNamePlayerExist()
{
	return namePlayer.compare(NAME_PLAYER_NON_SET) != 0;
}

void choisirNewNamePlayer()
{
	cleanScreen();
	cout << "Comment tu t'appelle?" << endl;
	cin >> namePlayer;
}

void verifyJeuEstFini() 
{
	afficherResultat();
	if (isPlayerWin()) {
		afficherResultat();
		afficherMessageGameOver("TU AS GANHE");
	}
	else if (isPcWin()) {
		afficherResultat();
		afficherMessageGameOver("TU AS PERDU");
	}
	waitEnter();
	
}

void afficherMessageGameOver(string message) 
{
	cleanScreen();
	separateur();
	cout<<message<<endl;
	separateur();
}

/*
* Verifier qui ganhe la partie;
* 91 Player voir WIN_PLAYER
* 90 Tie WIN_TIE
* 92 PC WIN_PC
*/
int calculerWinner(int choixPlayer)
{
	int choixPC = genereteOptionPC(choixPlayer);

	if(choixPlayer == choixPC) return WIN_TIE;
	if (choixPlayer == CHOIX_ROCHE && choixPC == CHOIX_CISEAUX) return WIN_PLAYER;
	if (choixPlayer == CHOIX_PAPIER && choixPC == CHOIX_ROCHE) return  WIN_PLAYER;
	if (choixPlayer == CHOIX_ROCHE && choixPC == CHOIX_PAPIER) return  WIN_PC;
	if (choixPlayer == CHOIX_PAPIER && choixPC == CHOIX_CISEAUX) return  WIN_PC;
	
	return -1;
	
}


int genereteOptionPC(int choixPlayer)
{
	// TODO ajouter possibiliter du pc tricher
	cout<< "Le PC est en train de choisir!" << endl;
	wait(3);
	srand(time(0));
	return rand() % 3 + 1;
}

string choixToString(int choixPlayer) 
{
	switch (choixPlayer)
	{
		case CHOIX_ROCHE:
			return "roche";
		case CHOIX_PAPIER:
			return "papier";
		case CHOIX_CISEAUX:
			return "ciseaux";
		default:
			return "null";
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

/*******************************************************************
* 
* FUNCTIONS EXTRAS
* 
*******************************************************************/

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
