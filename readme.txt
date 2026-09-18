
# Projet morpion (C)
1. STRATÉGIE D'IMPLÉMENTATION

- Séparation des responsabilités :
 Le programme distingue clairement l’affichage du jeu, la logique des règles et la gestion des interactions utilisateur. Chaque fonction a un rôle précis pour garder un code lisible et structuré.
- Gestion des données :
 La grille de jeu 'board[3][3]' est créée dans le 'main.c' et transmise aux fonctions par pointeurs. Cela permet d’éviter les variables globales et de garder un contrôle direct sur les données.
- Fichier d’en-tête unique :
 Le fichier 'Morpion.h' centralise les prototypes des fonctions ainsi que les constantes du projet. Il simplifie l’organisation et permet de mieux structurer le code.
- Déroulement du programme :
 Le jeu fonctionne de manière séquentielle dans le 'main.c' : affichage puis entrée du joueur puis vérification des règles enfin mise à jour de la grille.


2. FONCTIONS PRINCIPALES

• int playTurn(char board[3][3], char player)                 [OMAR]
  permet de gèrer un tour. Blinde la saisie (anti-caractère via getchar()), vérifie les limites (0-2) et la disponibilité de la case.

• void initBoard(char board[3][3])                            [MEHDI]
  permet d'initialiser la matrice à l'état vide (' ') avec 2 boucles imbriquées.

• void printBoard(char board[3][3])                           [MEHDI]
 permet de dessiner la grille de jeu et les séparateurs (| et ---) dans la console.

• int checkWin(char board[3][3])                              [WILLIAM]
  permet d'analyser la géométrie des lignes, colonnes et diagonales pour la victoire

• int isFull(char board[3][3])                                [WILLIAM]
  permet de parcourir le tableau pour détecter le match nul

• void logMove(FILE *f, int turn, char player, int row, int col) [MICHEL]
  permet d'écrire les coups sur disque en mode synchrone grâce à 'fflush'.

• Gestion Chrono (3 fonctions dédiées)                  [MICHEL]
  permettent d'isoler et cumuler le temps de réflexion avec la fonction 'clock()'

3. TESTS REALISES 
 Pour initBoard et printBoard, nous avons isolé la grille dans un programme séparé afin de tester uniquement l'initialisation et l’affichage. Nous avons vérifié que chaque case était correctement initialisée avec un espace vide, puis nous avons ajusté plusieurs fois l’espacement horizontal et vertical ainsi que le nombre d'espaces d'affichage des symboles dans les cases pour que tout soit aligné et lisible.

Pour checkWin, nous avons construit plusieurs configurations de grille afin de couvrir tous les cas possibles : une ligne complète, une colonne complète, les deux diagonales, ainsi qu’une grille sans combinaison gagnante. Ces tests ont permis de valider que la fonction détectait correctement chaque situation.

Pour measuretime, plusieurs simulations ont été faites afin de vérifier que le temps compté par la fonction correspondait au temps réel. Ces tests ont permis de confirmer que le chrono était fiable et cohérent.

Pour playTurn, nous avons testé différents types d’entrées afin de valider la robustesse de la fonction. Nous avons essayé des positions valides, des positions hors grille (ex : ligne 4, colonne 8), des cases déjà occupées, ainsi que des entrées non numériques. Cela a permis de vérifier que la fonction répondait aux exigences fixées par les règles du jeu, et affichait les messages d’erreur appropriés et redemandait une saisie tant qu’une position correcte n’était pas fournie.

4. Difficultés rencontrées :
Lors de l’implémentation de la main : nous avons eu du mal à trouver la méthode pour rafraichir la grille afin d’éviter qu’une nouvelle grille apparaisse à chaque tour.
La Gestion du temps des deux joueurs : la principale difficulté que nous avons rencontrée concernait la gestion du chronométrage des joueurs X et O de manière indépendante, sans mélanger leurs temps de jeu, alors qu’ils évoluent dans la même boucle d’exécution.
Il a également fallu déterminer avec précision le moment où démarrer et arrêter le chronomètre, c’est-à-dire juste avant l’appel à la fonction playTurn et immédiatement après son exécution, afin d’obtenir des mesures de temps fiables.
Enfin, j’ai mis en place une structure TempsJoueurs permettant de cumuler et de stocker séparément le temps de chaque joueur, puis d’enregistrer ces informations dans le fichier d’historique à la fin de la partie.
En revanche, la gestion de l’écriture et de l’affichage du contenu du fichier historique_morpion.txt n’a pas présenté de difficulté particulière.
