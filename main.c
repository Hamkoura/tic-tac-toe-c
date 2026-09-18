#include "morpion.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

int main(void)
{
    char board[3][3]; // Grille du jeu
    int turn = 1; // Compteur de tours
    char player1, player2; // Symboles des deux joueurs
    char joueurActuel; // Joueur dont c’est le tour
    int position; // Position du coup sous forme d'un seul nombre
    int row, col; // Ligne et colonne obtenues après décodage de la position
    TempsJoueurs totals = {0.0, 0.0}; // Temps total de jeu pour chaque joueur

    FILE *f = fopen("historique_morpion.txt", "w");   // Ouvre le fichier d'historique en écriture
    if (!f) {
        printf("Erreur : impossible d'ouvrir le fichier historique.\n");
        return 1; // Arrete le programme si le fichier ne s’ouvre pas
    }

    choisirSymboles(&player1, &player2); // Le joueur 1 choisit X ou O
    joueurActuel = player1; // Le joueur 1 commence

    initBoard(board); // Remplit la grille avec des cases vides


    while (1) {

        afficherJeu(board, turn, joueurActuel, &totals);
        demarrerChronoJoueur(joueurActuel);
        position = playTurn(board, joueurActuel);
        double sec = measuretime(joueurActuel);
        ajouterTempsJoueur(&totals, joueurActuel, sec);
        row = position / 10;
        col = position % 10;
        logMove(f, turn, joueurActuel, row, col);
        if (checkWin(board)) {
            afficherJeu(board, turn, joueurActuel, &totals); // Affiche état final
            printf("\n>>> Le joueur %c a gagne !\n", joueurActuel);
            break; // Fin de la partie
        }
        if (isFull(board)) {
            afficherJeu(board, turn, joueurActuel, &totals); // Affiche l'état final
            printf("\n>>> Match nul !\n");
            break; // Fin de la partie
        }
        joueurActuel = (joueurActuel == player1) ? player2 : player1;

        turn++; // Incrémente le nombre de tours
    }
    ecrireTempsFinal(f, &totals);

    fclose(f); // Ferme le fichier proprement
    printf("\n=== Historique complet ===\n");
    afficherHistorique("historique_morpion.txt");

    printf("\nMerci d'avoir joue !\n");

    return 0;
}
