#include "tool.h"
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LIGNE 50
#define NB_CHRONOS 3


//structure pour gérer et comparer les chronos
typedef struct {
    char nom[5];
    double chrono;
} HighScore;

struct card cartes[12]; //creation de la "liste" de 12 cartes


//definition des variables pour le temps
int secondes = 0;
int tenths = 0;

int show_menu()
{
    //variable choix

    int choix = 0;

    // parametres ncurses
    initscr();
    cbreak();
    noecho();

    // agrandir la taille de la police
    attron(A_BOLD);
    attron(A_DIM);


    // afficher le texte en ASCII
    printw("       _ ______ _    _   _____  ______  _____   _____        _____ _____  ______  _____ \n");
    printw("      | |  ____| |  | | |  __ \\|  ____|/ ____| |  __ \\ /\\   |_   _|  __ \\|  ____|/ ____|\n");
    printw("      | | |__  | |  | | | |  | | |__  | (___   | |__) /  \\    | | | |__) | |__  | (___  \n");
    printw("  _   | |  __| | |  | | | |  | |  __|  \\___ \\  |  ___/ /\\ \\   | | |  _  /|  __|  \\___ \\ \n");
    printw(" | |__| | |____| |__| | | |__| | |____ ____) | | |  / ____ \\ _| |_| | \\ \\| |____ ____) |\n");
    printw("  \\____/|______|\\____/  |_____/|______|_____/  |_| /_/    \\_\\_____|_|  \\_\\______|_____/ \n");

     // desactiver les modifications de la police

    attroff(A_BOLD);
    attroff(A_DIM);



    // refresh l'écran
    refresh();

    //affichage des choix
    printw("\n\n\n\n\n\n");
    printw("  MENU\n\n  1. Joueur\n\n  2. Autoplayer");
    printw("\n\n\n  Choisissez un mode de jeu : ");

    // selection du choix

    choix = getch();


    // quitter ncurses
    endwin();

    return choix;
}


int PremierRectangle() {

    int row = 1;    // Ligne de départ
    int col = 1;   // Colonne de départ
    int width = 55; // Largeur du rectangle
    int height = 4; // Hauteur du rectangle

	// instructions pour dessiner le 1er rectangle

    mvhline(row, col+1, '-', width);

    mvhline(row+1 + height, col+1, '-', width);

    mvvline(row+1, col, '|', height);

    mvvline(row+1, col+1 + width, '|', height);

	// affichage du texte
    mvprintw(2,2,"Jeu des paires");
    mvprintw(3,2,"Trouver les paires en un minimum de temps");

    return 0;


}



int DeuxiemeRectangle() {

    int row=1;
    int col=60;
    int width=35;
    int height=4;

	// instructions pour dessiner le 1er rectangle

    mvhline(row, col+1, '-', width);

    mvhline(row+1 + height, col+1, '-', width);

    mvvline(row+1, col, '|', height);

    mvvline(row+1, col+1 + width, '|', height);

    return 0;


}

void generateSymboles() {
    srand(time(NULL)); // initialise le générateur de nombres aléatoires
    char symbols[6];
    int i, j;

    // génère 6 symboles (lettres) aléatoires différents
    for (i = 0; i < 6; i++) {
        char randomSymbol;
        int isUnique;
        do {
            isUnique = 1;
            randomSymbol = 'A' + (rand() % 26); // génère une lettre majuscule aléatoire
            for (j = 0; j < i; j++) {
                if (symbols[j] == randomSymbol) {
                    isUnique = 0;
                    break;
                }
            }
        } while (!isUnique);
        symbols[i] = randomSymbol;
    }

    // affecte chaque symbole à 2 cartes aléatoires
    for (i = 0; i < 6; i++) {
        int count = 0;
        while (count < 2) {
            int randomCardIndex = rand() % 12;
            if (cartes[randomCardIndex].symbole == '\0') { // vérifie si la carte n'a pas déjà un symbole
                cartes[randomCardIndex].symbole = symbols[i];
                count++;
            }
        }
    }
}

void drawCard(int x, int y, int width, int height, int color) {
    start_color();

    chtype pixel = mvwinch(stdscr, y, x);

    // Extraction des informations de couleur
    int color_pair = COLOR_PAIR(pixel & A_COLOR);
    int color_index = PAIR_NUMBER(color_pair);

	//changement de la couleur


    if (color == 1) {
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        attron(COLOR_PAIR(1));
    } else if (color == 2 && color_pair!= COLOR_YELLOW) {
        init_pair(2, COLOR_BLUE, COLOR_BLACK);
        attron(COLOR_PAIR(2));
    }
    else if (color == 3) {
        init_pair(2, COLOR_YELLOW, COLOR_BLACK);
        attron(COLOR_PAIR(2));
    }

	//changement de la carte en fonction de sa couleur et coordonées

    mvhline(y, x+1, '-', width);
    mvhline(y+1 + height, x+1, '-', width);
    mvvline(y+1, x, '|', height);
    mvvline(y+1, x+1 + width, '|', height);

    if (color != 0) {
        attroff(COLOR_PAIR(color));
    }
}


void victoire() {

	//variables pour dessiner le rectangle de victoire

    char nom[5];
    int row = 35;
    int col = 1;
    int width = 95;
    int height = 6;

    // dessiner le rectangle
    mvhline(row, col + 1, '-', width);
    mvhline(row + 1 + height, col + 1, '-', width);
    mvvline(row + 1, col, '|', height);
    mvvline(row + 1, col + 1 + width, '|', height);

	//affichage du texte pour la victoire
    mvprintw(36, 2, "VICTOIRE");
    mvprintw(37, 2, "Entrer votre nom en 4 lettres : ");



}


//Fonction pas utilsée car bugs
char* getNom() {

    echo();

    static char str[5];
    int ch, i = 0;



    flushinp();
    while (i < 4) {
        ch = getch();
        str[i] = ch;
        i++;
        printf("%c ",ch);
    }
    str[4] = '\0';

    mvprintw(38,2,"%s",str);

    endwin();



    return str;
}


char *getNom2(){
	//tableau pour stocker le nom
    static char nom[5];

	//récupérer un nom de 4 characteres
    scanf("%4s",nom);

    //mvprintw(38,2,"%s",nom);


    refresh();

    return nom;
}

int comparerChronos(const void *a, const void *b) {
    HighScore *chronoA = (HighScore *)a; //chrono 1
    HighScore *chronoB = (HighScore *)b; //chrono 2
	//comparaison entre les 2 chronos
    return (chronoA->chrono > chronoB->chrono) - (chronoA->chrono < chronoB->chrono);
}

void ecrireHighScore(char *nom, int sec, int ten) {

	//gestions des erreurs
    if (nom == NULL) {
        fprintf(stderr, "Le nom fourni est NULL\n");
        return;
    }

    FILE *fichier = fopen("jeuhighscore.txt", "r+");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier jeuhighscore.txt");
        return;
    }

	//definiton des variables

    HighScore scores[NB_CHRONOS + 1];
    char ligne[MAX_LIGNE];
    int index = 0;

    // lire les anciens scores
    while (fgets(ligne, MAX_LIGNE, fichier) && index < NB_CHRONOS) {
        if (sscanf(ligne, "%4s %lf", scores[index].nom, &scores[index].chrono) == 2) {
            index++;
        }
    }

    // ajouter le nouveau score
    strcpy(scores[NB_CHRONOS].nom, nom);
    scores[NB_CHRONOS].chrono = sec + ten / 10.0;

    // trier les scores
    qsort(scores, NB_CHRONOS + 1, sizeof(HighScore), comparerChronos);

    // réécrire les scores
    fseek(fichier, 0, SEEK_SET);
    fprintf(fichier, "Meilleurs chronos : \n");
    for (int i = 0; i < NB_CHRONOS; i++) {
        fprintf(fichier, "%s %.1f\n", scores[i].nom, scores[i].chrono);
    }
	//fermeture du fichier
    fclose(fichier);
}


void afficheScores() {
	//variables
    int cpt = 0;
    FILE *fichier = fopen("jeuhighscore.txt", "r"); // ouvrir le fichier en mode lecture
	//gestion d'erreur
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier jeuhighscore.txt");
        return;
    }

    char ligne[20]; // tableau de caractères pour stocker chaque ligne lue

    mvprintw(37,2,"\t\t\t\t\t\t");
    refresh();
    // lecture et affichage des 5 premieres ligne du fichier
    while (fgets(ligne, sizeof(ligne), fichier) != NULL && cpt < 5) {


        mvprintw(37+cpt,2,"%s", ligne); // Afficher la ligne
        cpt++;
        refresh();

    }

	//fermeture du fichier

    fclose(fichier);
}


int CarteCache(int x, int y) {
	//variables
    int row=8+y;
    int col=3+x;
    int width=10;
    int height=8;

	//appel de la fonction qui permet de dessiner les cartes
    drawCard(col, row, width, height, 0);

    return 0;
}

void changeCard(int x, int y,int color) //color: 0 = white, 1 = green, 2 = blue, 3 = yellow
{
    int width=10;
    int height=8;

	//appel de la fonction qui permet de redessiner les cartes

    drawCard(x, y, width, height, color);
}

void afficheJeu()
{

	//affichage des fenetres du jeu
    PremierRectangle();

    DeuxiemeRectangle();

	//choix aleatoire des symboles des cartes
    for (int i = 0; i<12;i++)
    {
        cartes[i].found=0;
    }
    generateSymboles();

	//dessiner les cartes retournées pour le début du jeu
    for (int j=0;j<6;j+=1)
    {
        cartes[j].nb = j;
        CarteCache(j*15,0);
        cartes[j].x=j*15+3;
        cartes[j].y=0+8;
    }
    for (int j=0;j<6;j+=1)
    {
        cartes[j+6].nb = j+6;
        CarteCache(j*15,15);
        cartes[j+6].x=j*15+3;
        cartes[j+6].y=15+8;
    }





	//refresh de l'ecran
    refresh();

}

void fixCards(){
	//boucle qui permet de vérifier que la couleur des cartes trouvées est la bonne
    for (int l;l<=11;l++){
        if (cartes[l].found==1){
            changeCard(cartes[l].x,cartes[l].y,3);
        }
    }

}

int modeManuel() {
	//parametres ncurses
    initscr();
    cbreak();
    noecho();
    timeout(1);

	//definition des variables
    int nb = 0;
    int pressed_key = 0;
    int lockedCards = 0;
    int nbFoundCards= 0 ;
    int gameState = 0;
    float elapsed_time = 0.0;

    int enter_last_press = 0;

    // création de la liste des cartes verrouillées
    struct Liste listLockedCards;
    listLockedCards.premier = NULL;

    changeCard(cartes[0].x,cartes[0].y,1);
    cartes[0].hovered=1;

	//boucle principale du jeu
    while (gameState==0){

		//chronometre
        mvprintw(2,62,"Chrono : %d.%d",secondes, tenths);
        refresh();

        usleep(10000);
        elapsed_time+=100000;
        if(elapsed_time > 1000000) {
            elapsed_time=0;
            tenths++;
            if(tenths == 10){
                tenths = 0;
                secondes+=1;
            }
        refresh();

		//recupere la touche utilsée par le joueur
        pressed_key = getch();

		//gestions des cas en fonction de la touche appuyée
        switch(pressed_key){
			//deplacement vers la droite
            case(KEY_RIGHT):
                if (!cartes[nb].locked) {
                    changeCard(cartes[nb].x,cartes[nb].y,0);
                    cartes[nb].hovered=0;
                }
                nb++;
                if (nb > 11) {
                    nb = 0;
                }
                while (nb<12 && cartes[nb].locked && cartes[nb].found) {
                    nb++;
                    if (nb > 11) {
                        nb = 0;
                    }
                }
                if (!cartes[nb].locked && !cartes[nb].hovered) {
                    changeCard(cartes[nb].x,cartes[nb].y,1);
                    cartes[nb].hovered=1;
                }

                break;
			//deplacement vers la gauche
            case(KEY_LEFT):
                if (!cartes[nb].locked) {
                    changeCard(cartes[nb].x,cartes[nb].y,0);
                    cartes[nb].hovered=0;
                }
                nb--;
                if (nb < 0) {
                    nb = 11;
                }
                while (nb>=0 && cartes[nb].locked && cartes[nb].found) {
                    nb--;
                    if (nb < 0) {
                        nb = 11;
                    }
                }
                if (!cartes[nb].locked && !cartes[nb].hovered) {
                    changeCard(cartes[nb].x,cartes[nb].y,1);
                    cartes[nb].hovered=1;
                }

                break;
            int temp=0;

			//appui de la touche entrée pour choisir une carte
            case('\n'):

				//si la carte n'est pas vérouillée hovered ou trouvée -> changer son état en vérouillée
                if (!cartes[nb].locked && cartes[nb].hovered && cartes[nb].found==0) {
                    if (cartes[nb].found==0){
                        changeCard(cartes[nb].x,cartes[nb].y,2);
                        cartes[nb].locked = 1;
                    }


                    // création d'une nouvelle carte verrouillée
                    struct card *newCard = malloc(sizeof(struct card));
                    *newCard = cartes[nb]; // copie des données de la carte
                    newCard->suivant = NULL; // initialisation du pointeur suivant

                    // ajout de la nouvelle carte à la liste des cartes verrouillées
                    if (listLockedCards.premier == NULL) {
                        // si la liste est vide donc newCard est le premier élément
                        listLockedCards.premier = newCard;
                    } else {
                        // si la liste n'est pas vide donc nous ajoutons newCard à la fin
                        struct card *currentCard = listLockedCards.premier;
                        while (currentCard->suivant != NULL) {
                            currentCard = currentCard->suivant;
                        }
                        currentCard->suivant = newCard;
                    }

                    cartes[nb].hovered = 0;

					//on compte une carte verouillée en +
                    lockedCards++;

                    // affiche le symbole des cartes après que 2 cartes sont verrouillées
                    if (lockedCards == 2) {
                        for (int i = 0; i < 12; i++) {
                            if (cartes[i].locked) {
                                mvprintw(cartes[i].y+4, cartes[i].x+5.5, "%c", cartes[i].symbole); // affiche le symbole à l'intérieur de la carte
                            }
                        }
                        lockedCards = 0; // réinitialise le compteur de cartes verrouillées

                        struct card *card1 = listLockedCards.premier;
                        struct card *card2 = card1->suivant;


                        refresh();

						//supprime les entrées en attente dans le buffer
                        flushinp();

						//mise à jour du chrono pendant les 2 secondes de pause
                        for (int i = 0; i<=20; i++)
                        {

                            mvprintw(2,62,"Chrono : %d.%d",secondes, tenths);
                                    refresh();

                                    usleep(100000);
                                    elapsed_time+=1000000;
                                    if(elapsed_time > 1000000) {
                                        elapsed_time=0;
                                        tenths++;
                                        if(tenths == 10){
                                            tenths = 0;
                                            secondes+=1;
                                        }
                                    refresh();
                                    }
                        }
                        flushinp();



                        refresh();


						//comparaison des symboles afin de changer l'état des cartes
                        if (card1->symbole == card2->symbole)
                        {
                            changeCard(cartes[card1->nb].x,cartes[card1->nb].y,3);
                            changeCard(cartes[card2->nb].x,cartes[card2->nb].y,3);
                            cartes[card1->nb].found = 1;
                            cartes[card2->nb].found = 1;
                            nbFoundCards+=2;
                        }
                        else
                        {
                            changeCard(cartes[card1->nb].x,cartes[card1->nb].y,0);
                            changeCard(cartes[card2->nb].x,cartes[card2->nb].y,0);
                            cartes[card1->nb].locked=0;
                            cartes[card2->nb].locked=0;
                            mvprintw(cartes[card1->nb].y+4, cartes[card1->nb].x+5.5, " ");
                            mvprintw(cartes[card2->nb].y+4, cartes[card2->nb].x+5.5, " ");
                            cartes[card2->nb].hovered = 1;
                            changeCard(cartes[card2->nb].x,cartes[nb].y,1);

                        }



                        // supprime les cartes de la liste temporaire
                        listLockedCards.premier = card2->suivant;

						//libérer la mémoire
                        free(card1);
                        free(card2);


                        fixCards();


                    }

                }

                break;
			//touche q pour arrêter le jeu
            case('q'):
                clear();
                printw("Vous avez mis fin au jeu !\n\n");
                refresh();
                endwin();

                // libération de la mémoire pour la liste des cartes verrouillées
                struct card *currentCard = listLockedCards.premier;
                while (currentCard != NULL) {
                    struct card *nextCard = currentCard->suivant;
                    free(currentCard);
                    currentCard = nextCard;
                }
				//mise à jour de l'état du jeu sur fini
                gameState=1;

				//code de retour pour jeu arrêté par l'utilisateur
                return 4;

            default:
                break;

        }

    }

    if(nbFoundCards>=12){

		//mise à jour de l'état du jeu sur fini

        gameState=1;
        break;

    }
}

}

int choseRandomMove(){

	//initialisation du srand
    srand(time(NULL));

	//var pour stocker l'action
    int action = 0;

	//choix aleatoire d'un mouvement
    action = rand() % 4;
    if (action==0){
        action=KEY_LEFT;
    }else if(action==1){
        action=KEY_RIGHT;
    }else{
        action='\n';
    }

	//retour du mouvement choisi
    return action;


}


/*
FONCTION AUTOPLAYER pareille que le modeManuel sauf que les touches sont bloquées et
que les mouvements sont choisis aléatoirement par la fonction choseRandomMove
*/
void autoPlayer() {
    initscr();
    cbreak();
    noecho();
    timeout(1);
    int nb = 0;
    int pressed_key = 0;
    int lockedCards = 0;
    int nbFoundCards= 0 ;
    int gameState = 0;
    float elapsed_time = 0.0;




    int enter_last_press = 0;

    struct Liste listLockedCards;
    listLockedCards.premier = NULL;

    changeCard(cartes[0].x,cartes[0].y,1);
    cartes[0].hovered=1;

    while (gameState==0){
        mvprintw(2,62,"Chrono : %d.%d",secondes, tenths);
        refresh();

        usleep(1000);
        elapsed_time+=10000;
        if(elapsed_time > 1000000) {
            elapsed_time=0;
            tenths++;
            if(tenths == 10){
                tenths = 0;
                secondes+=1;
            }
        refresh();


        if(nbFoundCards>9){
            if(tenths==5){
                pressed_key=choseRandomMove();

            }
        }else{
            pressed_key=choseRandomMove();
        }

        switch(pressed_key){
            case(KEY_RIGHT):
                if (!cartes[nb].locked) {
                    changeCard(cartes[nb].x,cartes[nb].y,0);
                    cartes[nb].hovered=0;
                }
                nb++;
                if (nb > 11) {
                    nb = 0;
                }
                while (nb<12 && cartes[nb].locked && cartes[nb].found) {
                    nb++;
                    if (nb > 11) {
                        nb = 0;
                    }
                }
                if (!cartes[nb].locked && !cartes[nb].hovered) {
                    changeCard(cartes[nb].x,cartes[nb].y,1);
                    cartes[nb].hovered=1;
                }

                break;

            case(KEY_LEFT):
                if (!cartes[nb].locked) {
                    changeCard(cartes[nb].x,cartes[nb].y,0);
                    cartes[nb].hovered=0;
                }
                nb--;
                if (nb < 0) {
                    nb = 11;
                }
                while (nb>=0 && cartes[nb].locked && cartes[nb].found) {
                    nb--;
                    if (nb < 0) {
                        nb = 11;
                    }
                }
                if (!cartes[nb].locked && !cartes[nb].hovered) {
                    changeCard(cartes[nb].x,cartes[nb].y,1);
                    cartes[nb].hovered=1;
                }

                break;
            int temp=0;
            case('\n'):

                if (!cartes[nb].locked && cartes[nb].hovered && cartes[nb].found==0) {
                    if (cartes[nb].found==0){
                        changeCard(cartes[nb].x,cartes[nb].y,2);
                        cartes[nb].locked = 1;
                    }


                    struct card *newCard = malloc(sizeof(struct card));
                    *newCard = cartes[nb];
                    newCard->suivant = NULL;

                    if (listLockedCards.premier == NULL) {
                        listLockedCards.premier = newCard;
                    } else {
                        struct card *currentCard = listLockedCards.premier;
                        while (currentCard->suivant != NULL) {
                            currentCard = currentCard->suivant;
                        }
                        currentCard->suivant = newCard;
                    }

                    cartes[nb].hovered = 0;
                    lockedCards++;

                    if (lockedCards == 2) {
                        for (int i = 0; i < 12; i++) {
                            if (cartes[i].locked) {
                                mvprintw(cartes[i].y+4, cartes[i].x+5.5, "%c", cartes[i].symbole);
                            }
                        }
                        lockedCards = 0;

                        struct card *card1 = listLockedCards.premier;
                        struct card *card2 = card1->suivant;


                        refresh();
                        flushinp();
                        for (int i = 0; i<=8; i++)
                        {

                            mvprintw(2,62,"Chrono : %d.%d",secondes, tenths);
                                    refresh();

                                    usleep(100000);
                                    elapsed_time+=1000000;
                                    if(elapsed_time > 1000000) {
                                        elapsed_time=0;
                                        tenths++;
                                        if(tenths == 10){
                                            tenths = 0;
                                            secondes+=1;
                                        }
                                    refresh();
                                    }
                        }
                        flushinp();



                        refresh();



                        if (card1->symbole == card2->symbole)
                        {
                            changeCard(cartes[card1->nb].x,cartes[card1->nb].y,3);
                            changeCard(cartes[card2->nb].x,cartes[card2->nb].y,3);
                            cartes[card1->nb].found = 1;
                            cartes[card2->nb].found = 1;
                            nbFoundCards+=2;
                        }
                        else
                        {
                            changeCard(cartes[card1->nb].x,cartes[card1->nb].y,0);
                            changeCard(cartes[card2->nb].x,cartes[card2->nb].y,0);
                            cartes[card1->nb].locked=0;
                            cartes[card2->nb].locked=0;
                            mvprintw(cartes[card1->nb].y+4, cartes[card1->nb].x+5.5, " ");
                            mvprintw(cartes[card2->nb].y+4, cartes[card2->nb].x+5.5, " ");
                            cartes[card2->nb].hovered = 1;
                            changeCard(cartes[card2->nb].x,cartes[nb].y,1);

                        }



                        listLockedCards.premier = card2->suivant;
                        free(card1);
                        free(card2);
                        fixCards();
                        usleep(100000);
                        elapsed_time+=1000000;


                    }

                }

                break;

            case('q'):
                clear();
                printw("Vous avez mis fin au jeu !\n\n");
                refresh();
                endwin();

                struct card *currentCard = listLockedCards.premier;
                while (currentCard != NULL) {
                    struct card *nextCard = currentCard->suivant;
                    free(currentCard);
                    currentCard = nextCard;
                }
                break;
                return;

            default:
                break;

        }

    }

    if(nbFoundCards>=12){
        gameState=1;
        break;
    }
}

}


void botVictory(){
    int row = 35;
    int col = 1;
    int width = 95;
    int height = 6;

    // dessiner le rectangle
    mvhline(row, col + 1, '-', width);
    mvhline(row + 1 + height, col + 1, '-', width);
    mvvline(row + 1, col, '|', height);
    mvvline(row + 1, col + 1 + width, '|', height);

	//affichage de la victoire du bot ainsi que de son chrono
    mvprintw(36, 2, "VICTOIRE DE L'AUTOPLAYER EN %s.%s secondes",secondes,tenths);
}
