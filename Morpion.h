#ifndef MORPION_H          // Empêche d'inclure ce fichier plusieurs fois
#define MORPION_H

#include <stdio.h>

#ifdef _WIN32               // Permet d'adapter la commande pour effacer l'écran selon le système d'exploitation
    #define CLEAR "cls"     // Pour Windows
#else
    #define CLEAR "clear"   // Pour macOS/Linux
#endif

// MODULE MEHDI : Grille
void initBoard(char board[3][3]);   // Initialise les 9 cases à ' '
void printBoard(char board[3][3]);  // Affiche la grille formatée

//  MODULE WILLIAM : Victoire / Match nul
int checkWin(char board[3][3]);     // Vérifie les lignes, les colonnes et les diagonales
int isFull(char board[3][3]);       // Retourne 1 si aucune case n'est vide
void choisirSymboles(char *p1, char *p2); // Attribution des symboles pour chaque utilisateur

//  MODULE MICHEL : Historique + Chronométrage
void logMove(FILE *f, int turn, char player, int row, int col); // Enregistre un coup
void afficherHistorique(const char *fhistorique);               // Affiche le fichier log

// Structure contenant les temps cumulés des joueurs
typedef struct {
    double tempsX;         // Temps total du joueur X
    double tempsO;         // Temps total du joueur O
} TempsJoueurs;

// Chronométrage individuel
void demarrerChronoJoueur(char player);            // Lance le chrono du joueur actif
double measuretime(char player);                   // Mesure le temps écoulé depuis le début
void ajouterTempsJoueur(TempsJoueurs *tj, char player, double secondes); // Ajoute au total

void ecrireTempsFinal(FILE *f, const TempsJoueurs *tj); // Écrit les temps dans l'historique

//  MODULE OMAR : Saisie robuste
int playTurn(char board[3][3], char player); // Gère la saisie + les erreurs + la pose du pion
void afficherJeu(char board[3][3], int turn, char joueurActuel, TempsJoueurs *tj); // Affiche l'interface principale du jeu

#endif     // Fin de la protection d'inclusion
