# Cours 4 : Arithmétique des pointeurs et tableaux "C"

## Arithmétique des pointeurs

Les pointeurs contiennent des adresses. Une adresse n'étant rien d'autre qu'un entier, on peut faire différentes opérations dessus

- On peut ajouter 1 à un pointeur. Ajouter 1 à un pointeur de type `T*` ajoute à l'adresse correspondante `sizeof(T)`. De cette manière, on passe à la variable de type `T` située juste après

Découpage de la mémoire en "zones" :

Octets : | | | | | | | | | | | | | | | |
`int`  : |       |       |       |
`short`: |   |   |   |   |   |   |

- En fait, on peut ajouter n'importe quel entier relatif `n`, et cela correspond à ajouter à l'adresse `n*sizeof(T)` octets

Toutes les opérations sur des entiers ne marchent pas sur les pointeurs (exemple : ajouter deux pointeurs entre eux, multiplier par un entier...)

- On peut calculer la soustraction de deux pointeurs. Si `ptr1 - ptr2 = n`, leurs adresses sont distantes de `n * sizeof(T)`, autrement dit, on peut mettre `n` variables de type `T` entre les deux adresses

- On peut aussi comparer deux pointeurs : `==`,`!=`,`<`,`<=`,...

Rq : On a dit au dernier cours qu'on ne pouvait pas distinguer l'adresse d'un `int` de l'adresse d'un `double`. C'est vrai, mais les pointeurs sur `int` et sur `double` se comportent différemment pour l'arithmétique des pointeurs

Petite idée poétique (on y reviendra) :
On pourrait vouloir :
- allouer une "grande" zone de mémoire
- stocker l'adresse du début dans un pointeur `int* ptr`
- accéder au dixième entier après le début de la zone, on fait

```cpp
*(ptr+9) = 42;
```

Petite surprise : vous avez fait ça des milliers de fois. Vous l'avez juste écrit :

```cpp
ptr[9] = 42;
```

Ces deux écritures sont équivalentes **par définition**

## Retour sur les tableaux C statiques

Tableau statique := taille connue à la compilation

**Un tableau statique `T tab[c]` (où c est connu à la compilation) est une "grosse" variable (de taille `c * sizeof(T)`) qui se convertit spontanément en pointeur `T*` contenant l'adresse de la première case du tableau**

Rq : Un tableau n'est pas un pointeur. Il s'agit bien d'une conversion qui se fait automatiquement là où un pointeur est attendu. Un point où la différence est flagrante, c'est qu'on ne peut pas modifier l'adresse de ce pointeur (on ne peut pas faire `tab++`).

Rq 2 : Du coup, l'écriture `tab[i]` est juste un raccourci pour `*(tab+i)`.

**Précision importante** : Dès qu'un tableau est passé en paramètre, il est transformé en vrai pointeur. En paramètre, la notation `T tab[]` est strictement équivalente à `T* tab`.

| | | | | | | |
---- `tab` ----
^
`tab` après conversion

D'où comportement "par référence"

L'essentiel reste : **en général, tableaux statiques et pointeurs se comportent de manière similaire**

C'est d'autant plus vrai qu'on utilise en réalité assez rarement les tableaux statiques. On leur préfère les tableaux de taille variable, et eux ne se manipulent qu'avec des pointeurs

## Les tableaux dynamique

On avait imaginé
- allouer une "grande" zone de mémoire
- stocker l'adresse du début dans un pointeur `int* ptr`
- accéder au dixième entier après le début de la zone, on fait

```cpp
ptr[9] = 42;
```

On vient de voir de voir que c'est en gros ce qui se passe avec les tableaux statiques (alloués sur la pile), qui s'utilisent comme des pointeurs sur leur première case

MAIS on peut aussi vouloir faire l'allocation sur le tas (manuellement).
Question : pour un tableau de `n` variables de type `T`, quelle taille doit-on réserver ? `n * sizeof(T)`
On multiplie le nombre d'éléments par la taille d'un éléments

Qu'est-ce que ça change par rapport à un tableau statique ?
- Il est alloué sur le tas, donc pas supprimé à la fin de la fonction
- **Lors d'une allocation sur le tas, la taille n'a pas besoin d'être connue à la compilation**

On peut choisir la taille du tableau **à l'exécution**. On parle donc de tableau dynamique

```cpp
//Allocation : ici taille n'est pas focément connue à la compilation !!
T* ptr = (T*) malloc(taille * sizeof(T));

//Utilisation
ptr[18] = 42;

//Libération
free(ptr);
```

Cette fois-ci, il n'y a que des pointeurs, donc *normalement* vous savez gérer

Rq : comme pour les tableaux statiques, il faut au choix
- stocker à part la taille du tableau
- stocker à part un pointeur sur la fin du tableau

Rq2 : quand on dit "taille variable" c'est pas tout à fait vrai
La taille n'a plus besoin d'être connue à la compilation. Mais une fois la mémoire allouée, on ne peut plus changer la taille.

Pour changer la taille, il va falloir utiliser `realloc`. On verra comment en TP

## Syntaxe C++ pour les tableaux dynamiques

On a déjà vu que, là où `malloc` n'attends qu'une taille, l'opérateur `new` veut connaître le type. Il y a donc une syntaxe à part pour allouer un tableau avec `new` (et le supprimer avec `delete`) :

```cpp
//Allocation. taille est une variable
T* ptr = new T[taille];

//Libération
delete[] ptr;
```

ATTENTION : si vous faites `delete ptr` vous ne libérez que la première case du tableau.

Enfin, comme d'habitude, `new` permet d'initialiser immédiatement

```cpp
int* ptr = new int[3]{18,42,666};
```

Suite en TP : https://hackmd.io/yq59ElGVQW-m5tmfGDYPlg









_
