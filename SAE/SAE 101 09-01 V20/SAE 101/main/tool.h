#ifndef TOOL_H_INCLUDED
#define TOOL_H_INCLUDED
#include <ncurses.h>

// Definition de la structure card
struct card{
    int nb;	//Numéro de la carte
    int x,y; //Coordonées
    int locked,hovered,found; //Etats de la carte
    char symbole; //Symbole de la carte

    struct card *suivant; //pointeur vers la carte suivante

};

struct Liste {
    // Pointeur vers le premier élément de la liste
    struct card *premier;
};

//Variables externes
extern int secondes;
extern int tenths;

/*
Fonction : show_menu
Param : Aucun
Traitement : Affiche le menu de lancement du jeu.
Retour : Touche saisie par l'utilisateur
*/
int show_menu();

/*
Fonction : PremierRectangle
Param : Aucun
Traitement : Dessine la première partie du menu.
Retour : 0
*/
int PremierRectangle();

/*
Fonction : DeuxiemeRectangle
Param : Aucun
Traitement : Dessine la deuxième partie du menu.
Retour : 0
*/
int DeuxiemeRectangle();

/*
Fonction : CarteCache
Param : x (position en x), y (position en y)
Traitement : Crée les cartes retournées à la position spécifiée.
Retour : 0
*/
int CarteCache(int x, int y);

/*
Fonction : afficheJeu
Param : Aucun
Traitement : Affiche le jeu de base.
Retour : Aucun
*/
void afficheJeu();

/*
Fonction : victoire
Param : Aucun
Traitement : Affiche un message de victoire.
Retour : Aucun
*/
void victoire();

/*
(pas utilisée car bugs)
Fonction : getNom 
Param : Aucun
Traitement : Récupère le nom de l'utilisateur (version 1).
Retour : Pointeur vers une chaîne de caractères (nom de l'utilisateur).
*/
char* getNom();

/*
Fonction : getNom2
Param : Aucun
Traitement : Récupère le nom de l'utilisateur (version 2).
Retour : Pointeur vers une chaîne de caractères (nom de l'utilisateur).
*/
char* getNom2();

/*
Fonction : ecrireHighScore
Param : nom (nom du joueur), sec (secondes), ten (dixiemes de seconde)
Traitement : Écrit les meilleurs scores dans un fichier texte.
Retour : Aucun
*/
void ecrireHighScore(char *nom, int sec, int ten);

/*
Fonction : afficheScores
Param : Aucun
Traitement : Affiche les trois meilleurs scores.
Retour : Aucun
*/
void afficheScores();

/*
Fonction : changeCard
Param : x (position en x), y (position en y), color (couleur)
Traitement : Change la couleur de la carte à la position spécifiée.
Retour : Aucun
*/
void changeCard(int x, int y, int color);

/*
Fonction : drawCard
Param : x (position en x), y (position en y), width (largeur), height (hauteur), color (couleur)
Traitement : Redessine les cartes à la position et avec les dimensions spécifiées.
Retour : Aucun
*/
void drawCard(int x, int y, int width, int height, int color);

/*
Fonction : modeManuel
Param : Aucun
Traitement : Active le mode manuel du jeu.
Retour : Retourne 4 si jeu interrompu par l'utilisateur.
*/
int modeManuel();

/*
Fonction : choseRandomMove
Param : Aucun
Traitement : Choisi un mouvement aléatoire pour le mode automatique.
Retour : Action aléatoire choisie
*/
int choseRandomMove();

/*
Fonction : autoPlayer
Param : Aucun
Traitement : Active le mode automatique du jeu.
Retour : Aucun
*/
void autoPlayer();

/*
Fonction : botVictory
Param : Aucun
Traitement : Affiche la victoire du bot.
Retour : Aucun
*/
void botVictory();




#endif // TOOL_H_INCLUDED
