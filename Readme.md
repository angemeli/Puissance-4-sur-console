# Puissance 4 sur console

Il s'agit de la création du jeu **Puissance4** sur console, avec le language C++. Le jeu inclut une intelligence artificielle capable de jouer contre l'utilisateur.

## Description
L'utilisateur choisit un mode de jeu (Joueur vs Joueur, Joueur vs IA). La grille de jeu s'affiche ensuite sur la console et le joueur peut jouer soit contre un autre joueur, soit contre l'IA, en fonction du mode choisi. 
Si les conditions de victoire ou de match nul sont respectées, le jeu s'arrête et le programme demande à l'utilisateur s'il souhaite rejouer. Si oui, le programme relance l'exécution et redemande le mode de jeu. Si non, le programme s'arrête.

## Structure
Le projet est divisé en plusieurs parties. Le programme principal *main.cpp* inclut les différentes fonctions qui gèrent le jeu. Dans le dossier *header* se trouvent les fichiers .h permettant d'importer les différentes fonctions créées dans les programmes C++. Dans le dossier *source*, se trouvent les différents codes sources C++ de ces fonctions. Cette programmation modulaire permet ainsi une meilleure visibilité et une bonne gestion du projet.

## L'Intelligence Artificielle
Le jeu inclut une IA capable de jouer contre l'utilisateur. Ainsi, l'IA s'adapte au jeu du joueur et choisit à son tour comment placer ses pions. En cas de danger par exemple, elle cherchera automatiquement à bloquer ce danger. Au cas contraire, elle jouera en mode attaque. 

## Illustration
Les captures d'écran dans le dossier *screenshots* illustrent l'exécution du programme.
