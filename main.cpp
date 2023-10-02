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
const string NAME_PC = "PC";

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
void afficherChoix(int choixPlayer, string name);
void afficherTitleScreen();
void afficherTexteStyleTypeWriter(string message, int tempsParLettreEnwaitAvecMiliSeconds);


void runJanKenPon();
void runCombat(int choixPlayer);
void runScore(int winnerOption);


void waitEnter();
void wait(int secs);
void waitAvecMiliSeconds(int milisecs);

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
int cheatPC(int choixPlayer);

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
	string messageRegles1 = "JAN-KEN-POW (du japonais) est un jeu, appelé également papier-caillou-ciseaux\n";
	messageRegles1 +=		" ou chifoumi en France, roche-papier-ciseaux au Québec, pierre-papier-ciseaux\n";
	messageRegles1 +=		" en France et Belgique, feuille-caillou-ciseaux en Suisse, Rochambeau aux États-Unis,\n";
	messageRegles1 +=		" morra en Italie. Il existe de nombreuses variantes régionales.";
	string messageRegles2 =	"De façon générale, la pierre bat les ciseaux (en les émoussant), les ciseaux battent\n" ;
	messageRegles2 +=		" la feuille (en la coupant), la feuille bat la pierre (en l'enveloppant). Ainsi chaque\n";
	messageRegles2 +=		" coup bat un autre coup, fait match nul contre le deuxième (son homologue) et est battu\n";
	messageRegles2 +=		" par le troisième.";
	separateur();
	cout << "\t\tLES REGLES DE JAN-KEN-POW" << endl;
	separateur();
	afficherTexteStyleTypeWriter(messageRegles1, 30);
	cout<< endl<< endl;
	waitEnter();
	afficherTexteStyleTypeWriter(messageRegles2, 30);
	cout << endl << endl;
	waitEnter();
	cleanScreen();
}

void afficherTexteStyleTypeWriter(string message, int tempsParLettreEnwaitAvecMiliSeconds)
{
	for (int i = 0; i < message.length(); i++) {
		cout << message[i] ;
		waitAvecMiliSeconds(tempsParLettreEnwaitAvecMiliSeconds);
	}
}

void afficherChoix(int choixPlayer, string name)
{
	cout<< "Le "<<name<<" as choisi " << choixToString(choixPlayer) << "!" << endl;
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
	afficherChoix(playerChoix, namePlayer);
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
			mensageWinner = "Le " + NAME_PC + " a gagne ce tour!";
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

	afficherChoix(choixPC, NAME_PC);

	if(choixPlayer == choixPC) return WIN_TIE;
	if (choixPlayer == CHOIX_ROCHE		&& choixPC == CHOIX_CISEAUX) return WIN_PLAYER;
	if (choixPlayer == CHOIX_PAPIER		&& choixPC == CHOIX_ROCHE) return  WIN_PLAYER;
	if (choixPlayer == CHOIX_CISEAUX	&& choixPC == CHOIX_PAPIER) return  WIN_PLAYER;
	if (choixPlayer == CHOIX_ROCHE		&& choixPC == CHOIX_PAPIER) return  WIN_PC;
	if (choixPlayer == CHOIX_PAPIER		&& choixPC == CHOIX_CISEAUX) return  WIN_PC;
	if (choixPlayer == CHOIX_CISEAUX	&& choixPC == CHOIX_ROCHE) return  WIN_PC;
	
	return WIN_TIE;
	
}


int genereteOptionPC(int choixPlayer)
{
	srand(time(0));
	int isPcTriche = rand() % 2;
	int choixPC;

	if (isPcTriche == 0) {
		cout << "Le "<< NAME_PC <<" est en train de CHOISIR!" << endl;
		srand(time(0)); 
		choixPC = rand() % 3 + 1;
	} else 
	{
		cout << "Le " << NAME_PC << " est en train de TRICHER!" << endl;
		choixPC = cheatPC(choixPlayer);
	}
	wait(1);

	return choixPC;
}

int cheatPC(int choixPlayer) 
{
	switch (choixPlayer) {
		case CHOIX_ROCHE:
			return CHOIX_PAPIER;
		case CHOIX_PAPIER:
			return CHOIX_CISEAUX;
		case CHOIX_CISEAUX:
			return CHOIX_ROCHE;
		default:
			return CHOIX_ROCHE; // si la choix player est pas bonne, affiche le ROCHE par default
			break;
	}
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
	waitAvecMiliSeconds(secs * 1000);
}

void waitAvecMiliSeconds(int milisecs)
{
	sleep_until(system_clock::now() + milliseconds(milisecs));
}

// netoyer l'ecran 
void cleanScreen()
{
	system("cls");
}

// ajoute une ligne de separation, jusque parce qu'il est beau.
void separateur()
{
	cout << "----------------------------------------------------------- " << endl;
}
