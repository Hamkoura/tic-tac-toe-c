#include "morpion.h"          // Inclusion du header principal du projet
#include <stdlib.h>
#include <time.h>             // Nécessaire pour le chronométrage

void choisirSymboles(char *p1, char *p2)
{
    char choix; // Variable temporaire qui stocke le choix  du joueur 1
    while (1) {
        printf("Joueur 1, choisissez votre symbole (X ou O) : ");   // Demande au joueur 1 de choisir X ou O

        scanf(" %c", &choix); //  Vérifie que l'utilisateur a tapé un seul caractère valide
        if (choix == 'X' || choix == 'x') {
            *p1 = 'X';
            *p2 = 'O'; //  Assigne automatiquement le symbole du joueur 2
            break;
        }
        else if (choix == 'O' || choix == 'o') {
            *p1 = 'O';
            *p2 = 'X'; //   Assigne automatiquement le symbole du joueur 2
            break;
        }
        else {
            printf("Choix invalide. Veuillez taper X ou O.\n"); // Si le joueur à saisi autre chose que X ou O
        }
    }

    printf("\n>>> Joueur 1 = %c\n", *p1);
    printf(">>> Joueur 2 = %c\n\n", *p2);
}

// FONCTION : afficherJeu

// Affiche l'interface, les infos et la grille du jeu
void afficherJeu(char board[3][3], int turn, char joueurActuel, TempsJoueurs *tj)
{
    system(CLEAR); // Efface l’écran du terminal (compatibilité Windows/Linux)

    const char *pad = "                             "; // Décalage pour centrer l'affichage

    printf("%s=====================================\n",pad);
    printf("%s             MORPION \n",pad);
    printf("%s=====================================\n\n",pad);

    printf("%sTour : %d\n",pad, turn); // Affiche le numéro du tour
    printf("%sJoueur actuel : %c\n",pad, joueurActuel); // Affiche le joueur qui doit jouer

    printf("%sTemps X : %.2f s | Temps O : %.2f s\n",pad, tj->tempsX, tj->tempsO); // Affiche les temps
    printf("\n%s------------- GRILLE -------------\n\n",pad);

    printBoard(board); // Affiche la grille

    printf("\n%s----------------------------------\n",pad);
}
// Fonction : INITIALISATION DE LA GRILLE

// Initialise la grille en mettant toutes les cases à vide
void initBoard(char board[3][3]) {
    int i, j;

    for(i = 0; i < 3; i++)         // Parcourt les lignes de la matrice
        for(j = 0; j < 3; j++)     // Parcourt les colonnes de la matrice
            board[i][j] = ' ';     // Place un espace pour indiquer une case vide
}

// Affiche la grille du morpion avec un format visuel en tableau
void printBoard(char b[3][3]) {
    const char *pad = "                                  "; // Décalage visuel pour centrer

    printf("%s    0       1       2    \n",pad); // Affichage des colonnes
    printf("%s        |       |       \n",pad);

    printf("%s0 %3c   | %3c   | %3c    \n",pad, b[0][0], b[0][1], b[0][2]); // Ligne 0
    printf("%s        |       |       \n",pad);
    printf("%s -------|-------|-------\n",pad); // Séparateur

    printf("%s        |       |       \n",pad);
    printf("%s1 %3c   | %3c   | %3c    \n",pad, b[1][0], b[1][1], b[1][2]); // Ligne 1
    printf("%s        |       |       \n",pad);
    printf("%s -------|-------|-------\n",pad);

    printf("%s        |       |       \n",pad);
    printf("%s2 %3c   | %3c   | %3c    \n",pad, b[2][0], b[2][1], b[2][2]); // Ligne 2
    printf("%s        |       |       \n",pad);
}
// DETECTION DE VICTOIRE
// Vérifie si un joueur a gagné (ligne, colonne ou diagonale)
int checkWin(char board[3][3]){
    for(int i = 0; i < 3; i++){         // Vérifie les lignes

        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] &&
            board[i][0] != ' ')
            return 1;
    }

    for(int j = 0; j < 3; j++){        // Vérifie les colonnes
        if (board[0][j] == board[1][j] &&
            board[1][j] == board[2][j] &&
            board[0][j] != ' ')
            return 1;
    }

    if (board[0][0] == board[1][1] &&    // Vérifie  la diagonale principale
        board[1][1] == board[2][2] &&
        board[0][0] != ' ')
        return 1;

    if (board[0][2] == board[1][1] &&    // Vérifie la diagonale secondaire
        board[1][1] == board[2][0] &&
        board[0][2] != ' ')
        return 1;

    return 0; // Aucun gagnant trouvé
}

//   DETECTION DE GRILLE PLEINE
int isFull(char board[3][3]){
    for(int i = 0; i < 3; i++)         // Parcourt lignes
        for(int j = 0; j < 3; j++)     // Parcourt colonnes
            if (board[i][j] == ' ')    // Case vide trouvée
                return 0;              // Grille NON pleine

    return 1;                          // Grille pleine → match nul
}

//   SAISIE ROBUSTE DU COUP
int playTurn(char board[3][3], char player) {
    int row, col;

    while (1) { // Boucle jusqu'à saisie valide
        printf("\nJoueur %c, entrez ligne et colonne (0-2) : ", player);

        if (scanf("%d %d", &row, &col) != 2) { // Vérifie que 2 chiffres ont été lus
            printf("ERREUR : Vous devez entrer deux chiffres.\n");
            while (getchar() != '\n');        // Vide le buffer
            continue;                          // Redemande
        }

        if (row < 0 || row > 2 || col < 0 || col > 2) { // Vérifie limites
            printf("ERREUR : Coordonnees hors limites.\n");
            continue;
        }

        if (board[row][col] != ' ') { // Vérifie si la case est libre
            printf("ERREUR : La case (%d,%d) est deja occupee.\n", row, col);
            continue;
        }

        board[row][col] = player;     // Place le symbole du joueur
        return (row * 10 + col);      // Encode la position (ex : 12)
    }
}

//   LOG D'UN COUP DANS FICHIER
void logMove(FILE *f, int turn, char player, int row, int col)
{
    fprintf(f, "Tour %d : Joueur %c joue (%d,%d)\n", turn, player, row, col); // Écrit le coup
    fflush(f); // Force l'écriture immédiate
}

//   AFFICHAGE DE L'HISTORIQUE
void afficherHistorique(const char *fhistorique)
{
    FILE *f = fopen(fhistorique, "r"); // Ouvre le fichier en lecture
    if (f == NULL) {
        printf("Impossible d'ouvrir l'historique.\n");
        return;
    }

    char buffer[120];                  // Ligne temporaire
    while (fgets(buffer, sizeof(buffer), f)) // Lit ligne par ligne
        printf("%s", buffer);          // Affiche la ligne

    fclose(f);                         // Ferme le fichier
}

//   CHRONOMETRAGE PAR JOUEUR
static clock_t debutX = 0, debutO = 0; // Stocke l'heure de début
static int chronoDemarreX = 0, chronoDemarreO = 0; // Indique si le chrono est actif

void demarrerChronoJoueur(char player)
{
    if (player == 'X') { debutX = clock(); chronoDemarreX = 1; } // Démarre chrono X
    else if (player == 'O') { debutO = clock(); chronoDemarreO = 1; } // Démarre chrono O
}

double measuretime(char player)
{
    clock_t fin = clock(); // Heure actuelle

    if (player == 'X' && chronoDemarreX) {
        chronoDemarreX = 0; // Stop chrono X
        return (double)(fin - debutX) / CLOCKS_PER_SEC; // Durée en secondes
    }

    if (player == 'O' && chronoDemarreO) {
        chronoDemarreO = 0; // Stop chrono O
        return (double)(fin - debutO) / CLOCKS_PER_SEC;
    }

    return 0.0; // Aucun chrono actif
}

void ajouterTempsJoueur(TempsJoueurs *tj, char player, double secondes)
{
    if (!tj) return;               // Sécurité
    if (player == 'X') tj->tempsX += secondes; // Ajoute au total X
    else if (player == 'O') tj->tempsO += secondes; // Ajoute au total O
}



void ecrireTempsFinal(FILE *f, const TempsJoueurs *tj)
{
    if (!f || !tj) return;

    fprintf(f, "\n=== Temps par joueur ===\n"); // Titre
    fprintf(f, "Joueur X : %.2f secondes\n", tj->tempsX); // Temps X
    fprintf(f, "Joueur O : %.2f secondes\n", tj->tempsO); // Temps O
    fflush(f); // Écriture immédiate
}
