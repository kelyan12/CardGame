#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

int main()
{
    // Initialisation de Ncurses
    WINDOW *win = initscr(); // Crée une fenêtre Ncurses
    cbreak();               // Désactive la mise en mémoire tampon
    raw();                  // Lecture des caractères un par un
    keypad(stdscr, TRUE);   // Active les touches spéciales
    noecho();               // Désactive l'affichage des caractères saisis
    curs_set(FALSE);        // Cache le curseur

    // Définition des variables
    char *nom;              // Nom du joueur
    int choix = 0;          // Choix de l'utilisateur
    int rows, cols;         // Nombre de lignes et de colonnes de la fenêtre
    int jeuReturn;          // Résultat du jeu

    // Récupération de la taille de la fenêtre actuelle
    getmaxyx(stdscr, rows, cols);

    // Gestion des erreurs

    // 1) Vérification de la taille de la fenêtre
    if (rows < 50 || cols < 100)
    {
        printf("Taille de la fenetre insuffisante ! min (50x100)");
        return -1; // Code de sortie en cas d'erreur
    }

    // 2) Vérification de la création de la ressource Ncurses
    else if (win == NULL)
    {
        return -2; // Code de sortie en cas d'erreur
    }

    // Boucle de choix du mode de jeu + appels des fonctions du jeu

    do
    {
        choix = show_menu(); // Affiche le menu et obtient le choix de l'utilisateur
        if (choix == '1' || choix == '&') // Vérification du choix : mode de jeu Manuel
        {
            clear();           // Clear l'écran
            afficheJeu();      // Affiche le jeu
            jeuReturn = modeManuel(); // Démarre le mode de jeu manuel
            refresh();         // Refresh l'écran
            if (jeuReturn != 4)
            {
                victoire();     // Affiche un message de victoire
                refresh();
                nom = getNom2(); // Obtient le nom du joueur

                // Enregistre le score dans le classement
                ecrireHighScore(nom, secondes, tenths);
            }
            afficheScores(); // Affiche le classement

            break; // Sort de la boucle de jeu
        }
        else if (choix == '2' || choix == 'é') // Vérification du choix : mode automatique
        {
            clear();           // Clear l'écran
            afficheJeu();      // Affiche le jeu
            autoPlayer();      // Lance le mode de jeu automatique
            refresh();         // Refresh l'écran
            botVictory();      // Affiche un message de victoire du bot
            refresh();

            break; // Sort de la boucle de jeu
        }
        else
        {
            printw("VEUILLEZ CHOISIR UN CHIFFRE VALIDE"); // Affiche un message d'erreur
            refresh();
            sleep(1); // Pause d'une seconde
            clear();  // Clear l'écran
        }
    } while (choix != '1' && choix != '&' && choix != '2' && choix != 'é'); // Répète tant que le choix n'est pas valide

    return 0; // Code de sortie normal
}
