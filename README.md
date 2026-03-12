# Jeu du KONANE

## Description

Implémentation complète du jeu Konane, un jeu de stratégie traditionnel hawaïen, développé en langage C. 
Le projet propose trois niveaux de complexité: **Joueur vs Joueur**, **Joueur vs Machine(simple)**, **Joueur vs Machine(complexe)**.

## Caractéristiques

### Partie 1 : Jeu de base
- Plateau 7×7 avec 49 pions (noir et blanc)
- Implémentation complète des règles du Konane
- Mode Joueur vs Joueur
- Interface interactive avec affichage en couleurs ANSI

### Partie 2 : Intelligence artificielle simple
- IA basée sur des stratégies aléatoires
- Mode Humain vs IA simple
- Temps de réponse rapide

### Partie 3 : Intelligence artificielle avancée
- Algorithme Minimax avec Alpha-Beta Pruning
- Profondeur de recherche : 4
- Fonction d'évaluation heuristique (ratio de mobilité)
- Fort taux de victoire
- Mode Humain vs IA avancée

## Règles du jeu

- **Mouvement** : Les pions se déplacent uniquement en sautant par-dessus un pion adverse
- **Sauts** : Distance de 2 cases dans les 4 directions orthogonales (haut, bas, gauche, droite)
- **Captures obligatoires** : Si un saut est possible, il doit être effectué
- **Chaînes de captures** : Les sauts peuvent changer de direction et continuent jusqu'à épuisement
- **Victoire** : L'adversaire n'a plus de mouvement légal possible

## 🛠️ Technologies utilisées

- **Langage** : C
- **Compilateur** : Code::Blocks
- **Environnement** : Windows

## Installation

### Prérequis
- GCC installé
- Terminal/Console

### Compilation
```bash
gcc -o konane main.c source.c jeu.c -lm
```

### Exécution
```bash
./konane
```

## Utilisation

### Menu principal
1. **Jouez au jeu** - Accès aux différents modes de jeu
2. **Voir les règles** - Affichage des règles du Konane
3. **Quitter** - Fermer l'application

### Modes de jeu
1. **Joueur vs Joueur** - Deux joueurs humains
2. **Joueur vs Machine (simple)** - Contre une IA aléatoire
3. **Joueur vs Machine (avancée)** - Contre une IA Minimax optimisée

### Codes spéciaux
- **99** - Abandonner la partie en cours
- **p** - Pause durant la partie

### Format d'entrée
- Positions : `ligne colonne` (ex: 33 pour ligne 3, colonne 3)
- Valeurs : de 1 à 7

## Architecture

### Structure modulaire
```
main.c          → Point d'entrée, gestion des menus
menu.c/h        → Fonctions UI et gestion d'affichage
jeu.c/h         → Logique du jeu, règles, mouvements
```

### Fonctions principales

#### Logique du jeu
- `est_coup_legal()` - Validation des coups
- `deplacer_piece()` - Exécution d'un mouvement
- `capture_multiple()` - Gestion des chaînes de captures
- `peut_jouer()` - Vérification des mouvements disponibles

#### Intelligence artificielle
- `generer_et_compter()` - Énumération des coups possibles
- `evaluer_position()` - Évaluation heuristique par ratio de mobilité
- `minimax_ab()` - Recherche Minimax avec Alpha-Beta Pruning
- `jouer_coup_ia()` - Sélection et exécution du meilleur coup

#### Gestion d'interface
- `affiche_grille()` - Affichage du plateau
- `gestion_de_saisie()` - Capture et validation des entrées
- `init_joueurs()` - Initialisation des joueurs

## Concepts utilisés

### Programmation C
- Tableaux multidimensionnels
- Structures de données
- Pointeurs et références
- Récursivité
- Boucles et conditions

### Algorithmes
- Minimax (recherche en profondeur)
- Alpha-Beta Pruning (optimisation)
- Negamax (formulation simplifiée)
- Heuristiques (ratio de mobilité)

### Théorie des jeux
- Arbre de jeu
- Évaluation de positions
- Stratégie optimale

## Performance

### Optimisations appliquées
- Alpha-Beta Pruning réduit l'exploration **efficacement**
- Encodage numérique des coups pour efficacité
- Copies de plateau optimisées

### Temps d'exécution
- **Profondeur 4** : exécution rapide

## Équipe

**Collaboration** : avec 2 camarades de classe

## Résultats du projet

✅ Implémentation complète des 3 parties
✅ IA avancée performante
✅ Code modulaire et maintenable
✅ Documentation complète
✅ Projet présenté avec succès

---

Ce projet a été développé à titre académique.

---
