# Retour sur la mémoire : pointeurs et allocation dynamique manuelle

Temporairement, on s'interdit d'utiliser les références

Notion de variable (notion clé en impératif)
- type
- adresse
- (nom)
- valeur

On ne peut faire que 3 choses avec une variable :
- lire la valeur
- écrire la valeur
- récupérer l'adresse : `&a`

Notez que "créer une référence" ne fait pas partie de ce qu'on sait faire de base ==> Comment simuler passage par référence

`swap(a,b)` : inverse les valeurs de `a` et `b` ==> besoin d'un passage par référence

Pour simuler un passage par référence, on va stocker/passer en paramètre **les adresses** des variables

## Pointeurs

Si `T` est un type, on dit qu'un "pointeur sur `T`" est une variable de type `T*` qui contient l'adresse d'une variable de type `T`

```cpp
int a = 5;
int* p_a = &a;
```

Utilité ?
Nouvel opérateur : `*` (déréférencement) qui permet d'agir sur le contenu de l'adresse comme sur une variable normale

```cpp
int a = 5;
int* p_a = &a;
*p_a = 42;
//a vaut 42
```

--> Deux manières (ou plus) d'accéder au même emplacement mémoire

Les pointeurs sont des variables comme les autres : ils ont :
- type (`T*`)
- adresse (à distinguer de l'adresse de la case mémoire pointée)
- valeur (l'adresse d'une variable de type `T`)
On peut :
- lire la valeur (récupérer l'adresse de la variable pointée)
- écrire la valeur (changer la variable pointée)
- (récupérer l'adresse : `&a`) : on le fait rarement

Mais l'utilisation des pointeurs permet de simuler un fonctionnement par référence

```cpp
void incrementer(int* p_a) {
  (* p_a)++;
}
```

On peut créer des pointeurs sur **n'importe quel type**
Notamment sur des `struct`

```cpp
struct MonType {int a; char b};

MonType t{1,'2'};
MonType* p_t = &t;
(* p_t).a = 42;
// Attention : *p_t.a = *(p_t.a)
p_t->a = 42;
```

**Pointeur nul** :
- Adresse `0` n'existe pas
- On utilise l'adresse `0` pour pointer sur "rien"
- Notation sémantique : `NULL` ou `nullptr`
- NE JAMAIS DÉRÉFÉRENCER LE POINTEUR NUL
- Usage 1 : Valeur initiale pour les pointeurs : il faut toujours initialiser un pointeur à `nullptr`
- Usage 2 : "Pas de valeur" (~ None de python)

**Et les références ?**
- Historiquement : pas de références en C
- Référence = "sucre syntaxique" : si on regarde l'assembleur, utiliser des pointeurs ou des références est strictement équivalent
- Les références sont moins source d'erreur, mais elles sont plus limitées.
  - On ne peut pas changer la variable sur laquelle on fait une référence
  - **On ne peut créer une référence que sur une variable qui existe déjà**

## Allocation dynamique manuelle

Rappels : une allocation peut être
- statique/dynamique
  - statique : déterminée à la compilation (variables globales, variables `static`)
  - dynamique : déterminée à l'exécution (variables locales, paramètres)

Une allocation dynamique peut être
- automatique/manuelle
  - automatique : gérée par OS/programme/processeur en se basant sur les tableaux d'activation générés par le compilateur
  - manuelle : gérée par le programme qui va directement demander de la mémoire quand il en a besoin

Motivations :
- maîtriser la durée de vie
- gérer la quantité de mémoire (tableaux dynamiques)

### Petite mise en situation

===> On doit gérer une `struct` très grosse et dont l'initialisation est longue
Exemple : interface

On veut cacher l'initialisation dans une fonction
```cpp
Interface nouvelleInterface() {
  Interface inter;
  //On fait plein de choses
  return inter;
}
```
Problème : au moment du return, on fait une copie de `inter`
Au mieux c'est lent, au pire ça casse tout

Idée ==> copier l'adresse

```cpp
Interface* nouvelleInterface() {
  Interface inter;
  //Des trucs
  return &inter;
}
```
Programme faux : la variable inter est détruite à la fin de la fonction, donc on renvoie une adresse qui n'est plus valide

Problème des variables allouées automatiquement : elles sont désallouées automatiquement

Dernière idée : créer directement un pointeur
```cpp
Interface* nouvelleInterface() {
  Interface* p_inter; (0xabc123567890)
  //Des trucs
  return p_inter;
}
```

Problème : ici on a créé aucune interface, juste un emplacement pour stocker l'adresse d'une interface

Au final, on voudrait pouvoir réserver soi même la mémoire dont on a besoin, quand on en a besoin, sans devoir se reposer sur le compilateur et la gestion automatique de la mémoire

### `malloc` et le début des ennuis

On va snober le compilateur et aller parler directement à l'OS

- Salut, j'ai besoin de mémoire
- Je t'en mets combien ?
- De quoi stocker une `Interface`
- Ok, je t'ai réservé une place dans ma mémoire. Tu la trouveras à l'adresse 0x57777... Ne l'oublie pas !
- Ok je garde ça précieusement
- Et, ma mémoire, elle s'appelle "reviens" !

Traduction en `C++` (moins esthétique, plus synthétique)
```cpp
#include <cstdlib>

Interface* nouvelleInterface() {
  Interface* p_inter = (Interface*) malloc(sizeof(Interface));
  //Des trucs
  return p_inter;
}
```

Tout est bien qui finit bien ? Le programme ne supprimera JAMAIS l'interface

On vient de faire **une fuite de mémoire** : il faut libérer la mémoire, ou elle va continuer de s'accumuler

On a snobé le compilateur pour l'allocation, il ne s'occupera pas de la désallocation

Une fois qu'on a fini d'utiliser l'interface :
```cpp
free(ptr);
```

Règle d'or : **Dès que vous écrivez un `malloc`, écrivez le `free` correspondant**
