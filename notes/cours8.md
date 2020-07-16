# Arbres de recherche

## Introduction

Arbres

Définition (théorie des graphes) : Ensemble de sommets reliés par des arêtes (i.e un graphe) avec les deux propriétés suivantes :

- acyclicité : en suivant les arrêtes, on ne peut pas revenir à son point de départ (sauf en revenant sur ses pas)
- connexité : à partir d'un sommet, on peut se rendre à n'importe quel autre sommet en suivant les arêtes

On dit qu'un arbre est **enraciné** quand un sommet (un noeud) a été choisi comme racine. On donne en général un sens aux arêtes :

- depuis la racine : orientation naturelle
- vers la racine

Ex :

```md

    x--x
   /  / \
  x  x   x

```

Une version enracinée possible :

```md

    x
   /|\
  x x x
  |
  x

```

Dans un arbre enraciné, on parle de

- parent d'un noeud
- fils d'un noeud
- feuille : noeud qui n'a aucun fils

En pratique, cette définition théorique montre mal à quel point les arbres surviennent naturellement dans de nombreux contextes

Exemple d'arbres implicites qu'on a déjà eu l'occasion de voir :

```md

    fib(3)
    /    \
fib(1)   fib(2)
          /    \
      fib(0)   fib(1)

```

Autre exemple : les listes chainées sont un cas particulier d'arbre enraciné

```md

x -> x -> x .. x -> x

```

Il y a beaucoup d'autres exemples :

- labyrinthes
- expressions mathématiques

(1 + 2) * 3

```md

      *
    /    \
   3        +
          /   \
         1     2

```

Ajd, on va étudier un pb où les arbres surgissent alors qu'on ne les attends pas

**Comment modéliser informatiquement un ensemble fini (au sens mathématique du terme) d'entiers ?**

On veut donc une structure de données pour représenter une collection

- insensible à l'ordre : {1,2} = {2,1}
- sans doublon : {1,1} = {1}
- pour laquelle on peut tester facilement l'appartenance (∈) d'un élément

Exemple d'application : base de données

Les opérations clés

- `empty` : renvoie/initialise l'ensemble vide
- `insert` : insère un élément
- `search` : cherche un élément (dans le cas le plus basique, teste juste si x ∈ E)

Commençons par parler de la recherche. Petit détour : recherche dans un tableau

## Recherche dans un tableau

Dans un tableau quelconque, pour chercher un élément, on n'a pas d'autre choix que de parcourir tous les éléments jusqu'à le trouver/arriver à la fin du tableau : O(n)

==> Pas satisfaisant

Pourtant, il y a un cas particulier où on peut faire *beaucoup* mieux : tableau trié ==> recherche par dichotomie (cf `exemples/arbres/recherche.cpp`)

Complexité : O(log₂ n)

Arbre représentant la taille du tableau dans lequel on cherche. Ici chaque embranchement est un "OU" (recherche à gauche OU à droite du pivot)

```md

              n
             / \
          n/2   n/2
         /\       /\
      n/4  n/4 n/4  n/4

```

Ici, le nombre de tours de boucle/appels récursifs est la **profondeur** de cet arbre. On s'arrête quand le tableau est de taille 1, donc on veut répondre à :

Combien de fois doit-on diviser `n` par 2 pour arriver à 1 ? : ~log₂ n

==> **C'est le mieux que l'on sait faire sans information supplémentaire sur les éléments du tableau**

Idée : utiliser un tableau trié pour représenter notre ensemble

Pb : insertion ==> on va oublier les tableaux

Plutôt qu'un tableau entier où on va chercher le milieu, on peut voir la dichotomie sous un autre angle :

- un élément central ("pivot")
- deux sous tableaux
- le pivot est > à tous les éléments du premier sous-tableau et < à tous les éléments du deuxième

```md

1,2,3,4,5,6,7

      |
      v

      4
     / \
1,2,3   5,6,7

      |
      v

      4
    /   \
   2     6
  / \   / \
 1   3 5   7

```

On obtient un **arbre binaire de recherche**

## Arbres binaires de recherche (ABR)

Définition : Un arbre enraciné est dit k-aire lorsque chaque noeud a au maximum k enfants. Arbre binaire = arbre 2-aire

Définition' : Un ABR = un arbre binaire où chaque noeud est associé à une valeur ; la valeur d'un noeud est toujours > que toutes les valeurs situées dans le sous arbre gauche et < que celles situées dans le sous-arbre droit

Représentation dans le programme ? Comme une liste chainée, mais un noeud peut avoir *2* suivants = *2* fils

(cf structures et pseudo-constructeur dans `exemples/arbres/abr.cpp`)

### Recherche

On reprend le principe de la recherche par dichotomie en prenant comme pivot la racine de l'arbre (ou du sous-arbre) dans lequel on est en train de chercher

**RQ IMPORTANTE** : On n'est plus garanti d'avoir une complexité logarithmique, car on ne sait pas si la racine sépare l'ensemble des éléments en deux ensembles de taille ~égales. On dit que l'arbre n'est pas forcément équilibré. Au pire O(n)

Il existe des procédures d'insertion qui garantissent que l'ABR soit toujours plus ou moins équilibré (arbres rouge et noir) mais c'est pas le cas de celle qu'on va voir

(cf fonction `rechercherABR` dans `exemples/arbres/abr.cpp`)

### Insertion

Implémentés de cette manière, les arbres binaires ont un point commun avec listes chainées : facilité d'insertion *si on sait où on veut insérer*

En connaissant l'adresse d'un noeud dont l'un des fils est absent (on dit que ce fils est `leaf` ~ `nil`), on peut facilement lui rajouter un nouveau noeud comme fils

Ici, contrainte en plus : l'arbre obtenu doit être un ABR

- trouver le bon emplacement pour insérer un noeud
- ne pas insérer si l'élément existe

On adapte donc la procédure `search` :

- on garde la boucle
- si on a trouvé la valeur, on s'arrête (insérer 1 à {1} donne toujours {1})
- sinon, on est arrivé à `it == nullptr`. Il faut donc retrouver l'adresse à modifier pour remplacer ce `nullptr` par l'adresse d'un nouveau noeud alloué dynamiquement. Pour pouvoir facilement faire cette modification, on utilise toujours une variable `Noeud** ptr_a_modifier` qui contient l'adresse du pointeur de l'arbre stockant la même adresse que `it`.

(cf fonction `insererABR` dans `exemples/arbres/abr.cpp`)

## Parcours d'arbre

"Parcours" ==> faire une action (ex : affichage) sur tous les sommets d'un arbre (enraciné), dans un certain ordre

Deux grandes catégories de méthodes pour parcourir un arbre

### Parcours en profondeur

Rq : la structure d'arbre enraciné est "récursive"

Un arbre enraciné est soit :

- l'arbre vide (`leaf`)
- un noeud racine N₀ + plusieurs arbres enracinés dont les racines sont les fils de N₀

Pour traiter tous les sommets, une approche possible est donc :

- ne rien faire pour l'arbre vide
- pour un arbre non vide, on traite la racine puis on parcourt les sous-arbres

```md

    A                                 
   /|\
  B C D
  |
  E
                                        A B E C D
```

"En profondeur" : quand on commence à explorer une branche, on l'explore à fond avant de commencer à en explorer une autre

Variantes : ordre du traitement père/fils

- préfixe : on traite le parent avant de commencer à parcourir les sous arbres (A B E C D)
- postfixe : on parcourt les sous arbres puis on traite le parent (E B C D A)
- dans le cas particulier des arbres binaires : infixe : on parcourt le sous-arbre gauche, on traite le parent, puis on parcourt le sous arbre droit

Autre idée : Plutôt que faire des appels récursifs, on va stocker dans un conteneur les noeuds racines des sous arbres à parcourir. Il suffit alors d'une boucle pour les traiter un par un jusqu'à ce que le conteneur soit vide

Question : Dans quel ordre sortent les éléments : LIFO ou FIFO ?

Avec une pile : on retrouve le parcours en profondeur

```md

    A                                 
   /|\
  B C D
  |
  E
                                Pile des noeuds à explorer :
                                Noeud en cours de traitement :
                                Ordre de traitement : A B E C D
```

Que se passe-t-il avec une file ?

### Parcours en largeur

```md

    A                                 
   /|\
  B C D
  |
  E
                                File des noeuds à explorer :
                                Noeud en cours de traitement :
                                A B C D E
```

"En largeur" : commence par parcourir les noeuds les plus proches de la racine avant d'aller plus profondément

Rq : dans tous les cas, ce qui garantit que l'algorithme se termine, c'est l'absence de cycle ==> on ne traite jamais un noeud deux fois

### Retour à l'affichage

Quel parcours utiliser pour vérifier que notre arbre est bien un ABR ?

```md
        4
      /   \
     2     6
    / \   / \
   1   3 5   7
```

- parcours en profondeur préfixe : 4 2 1 3 6 5 7
- parcours en profondeur postfixe : 1 3 2 5 7 6 4
- parcours en profondeur infixe : 1 2 3 4 5 6 7
- parcours en largeur : 4 2 6 1 3 5 7

**Sur un ABR, le parcours en profondeur infixe donne une suite strictement croissante**

## Démo

(cf `exemples/arbres/abr.cpp`)

`main` : répète `n` fois : insertion d'un entier aléatoire entre 0 et n, puis recherche n/2 et affiche la profondeur maximale de l'arbre

La profondeur maximale étant en moyenne en O(log n), on prend conscience de **la lenteur de la croissancce logarithmique**
