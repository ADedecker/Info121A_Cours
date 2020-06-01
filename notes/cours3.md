# Allocation dynamique le retour : détails techniques, syntaxe C++

Commençons par étudier plus en détail les différentes briques utiles pour faire de l'allocation dynamique manuelle. Parlons d'abord de la manière dont est découpée la mémoire d'un programme.

## Théorie : stockage "sur le tas"

La mémoire utilisée par un programme est découpée en "sections" (inutiles de connaitre les deux premières)
- `text` : code
- `data/bss` : variables statiques/globales
- `stack` : pile -> variables automatiques
- `heap` : tas -> variables manuelles

On veut maîtriser la durée de vie des variables allouées manuellement ==> on ne peut pas les stocker sur la pile.
==> stockage sur le tas

Ici le mot "tas" ne fait pas référence à une structure particulière (contrairement à "tri par tas")

La structure exacte (car il y en a une) dépend de l'implémentation ==> varie selon OS, version de librairie standard,...

La seule garantie, c'est qu'on est complètement maître de la durée de vie.

## The `C` way : `malloc`, `free`, `calloc`, `realloc` + `sizeof`

En C, l'allocation manuelle ne fait pas partie du langage "de base". Elle fait partie de la librairie standard, plus précisément du header `stdlib.h` (en C++ on y accède depuis `cstdlib`)

Prototype d'une fonction = en-tête de la fonction

Exemple : le prototype de swap : `void swap(int* p_a, int* p_b);`

### `malloc`

Prototype :
```cpp
void* malloc(size_t size);
```

`size_t` ? Entier non-signé adapté pour stocker une taille
`void*` ? "pointeur sur void" = pointeur sur n'importe quoi. En effet, on ne peut pas distinguer l'adresse d'un entier de l'adresse d'un flottant (mais on verra que `int*` a tout de même un comportement différent de `long*`)

Paramètres :
- `size_t size` : nombre d'octets à allouer (minimum)

Retour :
- `void*` : adresse de l'emplacement mémoire réservé (logique que ce soit `void*`, la fonction ne sait pas ce qu'on veut allouer)

Rq : En `C++`, pour convertir de `void*` à `int*` il faut faire une conversion

ATTENTION : `malloc` ne réussit pas toujours. Si erreur, elle renvoie `nullptr` ==> il faut toujours vérifier que l'allocation a fonctionné

Si `size = 0`, le comportement n'est pas spécifié

Rq : je vous laisse faire vos recherches sur `calloc` qui initialise à 0 (peu utile en général)

### `free`

Inséparable de `malloc`

**À chaque fois que vous faites un `malloc`, vous faites un `free`**

Prototype :
```cpp
void free(void* ptr);
```

Paramètres
- `void* ptr` : adresse l'emplacement à libérer (remarque : dans ce sens là, la conversion vers `void*` est automatique)

Il ne faut appeler `free` que sur un pointeur
- alloué par `malloc`
- pas encore libéré (--> double free)

Une fois un emplacement mémoire libéré :
- il ne faut plus essayer d'y accéder
- il ne faut plus le libérer à nouveau

Cas particulier : `free(nullptr);` ==> cette instruction est juste ignorée. Ainsi, pas de risque de double free si on respecte la règle suivante :

**Tout pointeur qui ne doit pas être déréférencé doit être donné la valeur `nullptr`**

### `realloc`

Très spécifique

En général, lors de l'allocation manuelle, la zone réservée est un peu plus grande que la taille demandée.
On ne peut pas utiliser ce surplus autrement qu'avec `realloc`

Permet d'agrandir (ou de réduire) la zone allouée **sans perte de données**

Si besoin, une nouvelle zone plus grande est allouée et les données y sont copiées.

Prototype :
```cpp
void* realloc(void* ptr, size_t nouvelle_taille);
```

- paramètre `void* ptr` : un pointeur vers une zone mémoire déjà allouée qu'on veut agrandir
ATTENTION : ça doit être une zone mémoire allouée par `malloc` (ou par un autre `realloc`)
- paramètre `size_t nouvelle_taille` : taille de la nouvelle zone (indéfini si 0)
- renvoie `void*` : adresse du nouvel espace mémoire

Attention, la validité des pointeurs varie selon les cas
- Si il n'y a pas d'erreur, le pointeur **renvoyé par la fonction** est valide, mais **l'ancien ne l'est plus** *a priori* (il a été libéré si nécessaire, il ne faut pas s'occuper de le libérer)
- Si il y a une erreur, la fonction renvoie `nullptr`, et l'ancien pointeur reste valide ==> il faudra le libérer

Il est très important de tester le résultat de `realloc`

Remarque POO : `realloc` n'appelle pas l'opérateur de copie, c'est une

### `sizeof`

Ce n'est pas une fonction (ni une macro), c'est un opérateur intégré au langage qui donne la taille **en octets** d'un type

On peut faire `sizeof(type)` ou bien `sizeof(variable)` (on peut aussi faire `sizeof(expression)` mais 1) le type n'est pas évident à voir 2) l'expression n'est pas caculée)

Petit bonus : en C on aime bien la syntaxe

```c
int* ptr;
ptr = malloc(sizeof(*ptr));
```

--> On peut changer le type du pointeur à un seul endroit

En C++ ce n'est pas aussi simple à cause du cast. Je vous ai concoté cette syntaxe (qui n'est ni à connaitre ni à comprendre) :

```cpp
int* ptr;
ptr = (decltype(ptr)) malloc(sizeof(*ptr));
```

## Le problème de l'initialisation

**`malloc` gère l'allocation de la mémoire, toute l'allocation de la mémoire, seulement l'allocation de la mémoire**

==> Pas d'initialisation

Par exemple, l'exemple `malloc_non_init` affiche `0` et non pas `42` (sur mon ordinateur).

Remarque POO : malloc n'appelle pas de constructeur !!!!

En général, on a des fonctions distinctes qui s'occupent d'initialiser

## Recommandations sur l'utilisation des pointeurs

- Tout pointeur "pendant" (pointant sur une case qui ne nous appartient pas, par exemple non-initialisé où libéré) doit valoir `nullptr` ==> erreurs beaucoup plus simples à corriger
- Écrire un `malloc` ==> écrire un `free`
- Toujours tester le fonctionnement de l'allocation
- Essayer d'avoir une notion de "propriétaire" : c'est le même "morceau de code" qui gère l'allocation et la libération d'une variable donnée ==> aucun dev ne doit se soucier de libérer de la mémoire qu'il n'a pas allouée
- Conséquence pour l'utilisation d'une structure avec encapsulation : l'utilisateur gère l'allocation et la libération de la structure, et il utilise des fonctions données par son développeur pour l'initialiser et la "désinitialiser". De cette manière, chacun est responsable de la partie qu'il contrôle.

Exemple pour une structure `Interface` :

```cpp
Interface* ptr = (Interface*)malloc(sizeof(Interface));
construitInterface(ptr,...); //Pseudo-Constructeur
//Utilisation
detruitInterface(ptr); //Pseudo-Destructeur
free(ptr);
```

- Toujours faire attention quand on copie une structure qui contient un pointeur ==> garder un unique propriétaire. Par exemple, l'exemple `double_free_structure.cpp` cause une fuite de mémoire et un potentiel `double-free`.

## Application

L'exemple `fac_ptr_mieux.cpp` reprend la version "pointeurs" de la factorielle en respectant ces règles.

## The C++ way : `new`, `delete`

L'utilisation de `malloc` est devenue très lourde, pour deux raisons principales :
- Les tests à chaque allocation
- L'allocation distincte de l'initialisation

Nouveaux opérateurs en C++ (cette fois intégrés au langage) résolvent ces problèmes : `new` et `delete`

```cpp
T* ptr = new T;
//On utilise le pointeur
delete ptr;
```

Avantage : `*ptr` est correctement initialisée, de la même manière que si elle avait été allouée automatiquement (pour ceux qui connaissent : `new` appelle le constructeur par défaut)

On peut aussi initialiser de manière plus poussée :

```cpp
int* ptr = new int(42);
UneStructure* ptr2 = new UneStructure{paramètres...}

//Pour ceux qui connaissent la POO
UneClasse* ptr3 = new UneClasse(paramètres...)
```

Remarque POO importante : `delete` appelle le destructeur, `free` ne le fait pas

**ATTENTION** : ne pas mélanger les syntaxes C et C++

Autre avantage : comportement en cas d'erreur différent : si l'allocation échoue, `new` lance une exception ==> si on sait la gérer, le programme continue ; sinon le programme s'arrête.

## Application

L'exemple `fac_ptr_new.cpp` reprend une ultime fois la version "pointeurs" de la factorielle en utilisant `new` et `delete`. On y rappelle au passage la syntaxe de gestion des exceptions.
