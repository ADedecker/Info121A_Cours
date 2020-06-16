# Cours 5 : Listes chaînées

## Théorie sur les "conteneurs"

Quelques caractéristiques des tableaux (rappel et introduction de concepts) :

- Un tableau est un bloc de mémoire **contigu**
- Sa taille est fixée : à la compilation pour un tableau statique, à l'allocation pour un tableau dynamique. Pour *simuler* des variations de taille, on doit faire des réallocations
- Accéder à la `i`-ème case d'un tableau requiert toujours les mêmes opérations : `tab[i]` <=> `*(tab+i)`

En termes techniques, un tableau est un **conteneur, ordonné, à accès aléatoire**

- Conteneur : n'importe quoi qui contient un ensemble d'éléments, en général de même type
- Ordonné/Séquentiel : les éléments sont dans un certain ordre : [1,2] != [2,1]
- À accès aléatoire : Quel que soit `i`, on peut accéder à la `i`-ème case, et cela requiert toujours la même complexité

Ce sont quelques critères qui permettent de classifier les conteneurs. On va donc remplir cette classification

Aujourd'hui, créons ensemble un conteneur ordonné qui n'est pas à accès aléatoire (!)

## Motivations

Retirer l'accès aléatoire peut sembler très restrictif. En effet, vous ne savez interagir avec les tableaux qu'en accédant à des cases par leur indice, ce qui ne sera plus possible, ou du moins très inefficace, sans accès aléatoire

Et pourtant, dans de nombreux cas on peut s'en passer ! De nombreuses actions ne nécessitent en effet que de parcourir le tableau dans l'ordre, ce qui peut se faire sans accès aux éléments par leur indice !

Exemple pour l'affichage

Avec accès par indice :

```cpp
void afficher(int* tab, size_t taille) {
  for (size_t i = 0; i<taille; ++i) {
    std::cout<<tab[i]<<std::endl;
  }
}
```

Sans accès par indice :

```cpp
void afficher(int* tab, size_t taille) {
  int* it = tab;  //On crée un itérateur, càd un pointeur qui va contenir successivement
                  //les adresses de tous les éléments du tableau, en commençant par le premier
  for (size_t i = 0; i<taille; ++i) {
    std::cout<<* it<<std::endl;
    it++; //On se décale vers l'élément suivant
  }
}
```

Ici, l'opération importante, ce n'est plus l'accès par indice, c'est le fait de pouvoir itérer sur le contenu, en passant d'un élément au suivant (ici par l'arithmétique des pointeurs)

Idée : pour passer d'un élément au suivant, on va "coller" à chaque élément un pointeur sur le suivant ==> liste chainée

## Implémentation basique d'une liste chainée d'entiers

Schéma d'une liste chainée : le pointeur de chaque noeud contient l'adresse du suivant

```md
               ---Noeud---
{val , ptr} -> {val , ptr} -> ... {val , nullptr}
```

Quand on rencontre le pointeur nul, on est arrivé à la fin ==> pas de parcours infini, pas besoin de stocker la taille

Commençons par créer la structure d'un Noeud (= maillon de la chaîne)

```cpp
struct Noeud {
  int valeur;
  Noeud* p_suivant;
};
```

Il faut maintenant la structure de la liste :

```cpp
struct Liste {
  Noeud* p_debut;
};
```

Rq : de manière similaire aux tableaux, le conteneur en entier peut être vu comme un pointeur sur le premier élément. C'est généralisable à la plupart des conteneurs à travers le concept d'itérateur

Rq : Attention, la copie n'est pas vraiment une copie ! L'opération `l1 = l2` fera qqch du genre :

```md
 l1
 v
{val , ptr} -> {val , ptr} -> ... {val , nullptr}
 ^
 l2
```

Traduisons notre fonction "afficher" pour cette structure. On reprend évidemment la version sans accès par indice

```cpp
void afficher(Liste* p_liste) {
  Noeud* it = p_liste->p_debut; //Création de l'itérateur

  //Comme on ne connait pas la taille, on vérifie si on est à la fin
  // en regardant si l'itérateur est nul
  while(it != nullptr) {
    std::cout<< it->valeur <<std::endl;
    it = it->p_suivant; //On se décale vers l'élément suivant
  }
}
```

Comme pour toute structure un minimum complexe, il faut maintenant écrire le(s) pseudo-constructeurs de la structure. Commençons par initialiser la liste comme une liste vide

```cpp
bool construireListeVide(Liste* p_liste) {
  p_liste->p_debut = nullptr; //Une liste vide n'a pas de premier élément
  return true; //Tout se passe bien
}
```

Comment construire des listes plus complexes ? On va utiliser un avantage des listes : il est très simple d'insérer un élément au début.
Donc pour contruire [3,4,5], on part de la liste [], et on ajoute 5, 4, puis 3. On a donc pas besoin d'autre constructeur, seulement de la fonction :

```cpp
bool insererDebut(Liste* p_liste, int val) {
  Noeud* nouveauDebut = (Noeud*)malloc(sizeof(Noeud));
  if(nouveauDebut == nullptr) return false; //Il y a eu un pb

  //Le suivant du nouveauDebut est le debut actuel :
  * nouveauDebut = {val, p_liste->p_debut};
  p_liste->p_debut = nouveauDebut;
  return true;
}
```

On fait un `malloc` ==> Il faut faire un `free` ==> Pseudo-destructeur

```cpp
void detruireListe(Liste* p_liste) {
  //On supprime le premier élément tant qu'il existe
  while(p_liste->p_debut != nullptr) {

    //Variable tampon pour ne pas perdre l'adresse du suivant :
    Noeud* tmp = p_liste->p_debut->p_suivant;

    free(p_liste->p_debut);

    p_liste->p_debut = tmp;
  }
}
```

Ces trois fonctions sont le cœur du fonctionnement des listes. On aime bien y rajouter une fonction pour insérer un élément après un autre élément donné par son adresse

```cpp
bool insererApres(Noeud* p_noeud, int val) {
  Noeud* nouveauNoeud = (Noeud*)malloc(sizeof(Noeud));
  if(nouveauNoeud == nullptr) return false; //Il y a eu un pb

  //Attention, ces deux lignes ne peuvent pas être échangées
  //sinon on perd de l'information :
  * nouveauNoeud = {val, p_noeud->p_suivant};
  p_noeud->p_suivant = nouveauNoeud;
  return true;
}
```

Schéma :

```md
                {val,ptr}
                /      \
 ... -> {val,ptr}    {val,ptr} -> ...
```

## Avantages et défauts des listes chainées

Imaginez à quoi ressemblerait cette  fonction sur un tableau dynamique. Il faudrait :

- augmenter la taille (donc éventuellement copier tout le contenu du tableau)
- décaler tous les éléments situés après le lieu d'insertion
- finalement, on peut insérer notre élément

==> O(taille) !

Sur une liste chaînée, on peut le faire en complexité constante ! On voit ici l'avantage principal des listes chainées : comme la structure de liste ne correspond à aucune structure particulière en mémoire (les noeuds sont alloués n'importe où sur le tas, la seule chose qui les relie sont leurs pointeurs), il est très peu coûteux de modifier l'ordre, d'insérer ou de supprimer des éléments : il suffit de modifier l'organisation des pointeurs

Autre conséquence de l'absence du fait que les noeuds sont indépendants les uns des autres : on peut faire des modifications à l'échelle locale sans modifier l'ensemble de la liste ==> meilleure complexité pour ces opérations

Petit tableau récapitulatif des points forts et points faibles des tableaux dynamiques et listes chaînées (certaines complexités des `vector` vont peut-être vous étonner, rappelez vous qu'on a vu une version simplifiée)

| Opération                     | Tableau dynamique (`vector`) | Liste chaînée        |
|-------------------------------|------------------------------|----------------------|
| Accès au premier élément      | Très optimisé : O(1)         | Très optimisé : O(1) |
| Accès au `i`-ème élément      | Très optimisé : O(1)         | À éviter : O(i)      |
| Insertion au début            | À éviter : O(n)              | Très optimisé : O(1) |
| Insertion à la fin            | Optimisé : O(1) en moyenne   | À éviter : O(n) [1]  |
| Insertion en `i`-ème position | À éviter : O(n)              | À éviter : O(i)      |
| Insertion après un pointeur   | À éviter : O(n)              | Très optimisé : O(1) |

Rq : les complexités de suppression sont essentiellement les mêmes que l'insertion

[1] sauf si on a un pointeur sur le dernier élément

Quelques autres points à prendre en compte :

- Efficacité de l'utilisation de mémoire : un tableau de `n` entiers prend *exactement* la taille nécessaire pour stocker `n` entiers (et quelques pointeurs dans le cas d'un tableau dynamique). Par contre, une liste chainée de `n` entier doit stocker `n` **noeuds**, de taille `sizeof(int)+sizeof(Noeud*)` ==> on perd `n*sizeof(Noued*)` octets.
- Efficacité de la réservation de mémoire : l'allocation sur le tas est optimisée pour des allocations rares de grands blocs de mémoire (ce que font les vector), pas pour des allocations fréquentes de petits blocs de mémoire (ce que font les listes)
- Validité des pointeurs : pour rappel, l'augmentation de la taille d'un `vector` n'en est pas vraiment une : on copie les éléments dans une zone plus grande. Problème majeur : si vous aviez ailleurs un pointeur vers un élément du tableau, il a de grandes chances de devenir invalide (puisque l'élément a été déplacé). Ce problème ne se pose pas avec des listes chainées, encore une fois car changer la structure ne nécessite pas de modifier la disposition en mémoire des noeuds.

En résumé, l'utilisation d'une liste chainée se fait dans le cas suivants :

- assez peu d'éléments
- vous êtes surtout intéressés par la notion de "suivant" (et éventuellement de "parent")
- vous voulez pouvoir réorganiser facilement les éléments, en ajouter, en enlever...

Bref, le point fort des listes est la FLEXIBILITÉ.

## Listes doublement chainées et structures dérivées

Contrairement aux vector, la structure de liste chainée est très souvent adaptée selon les besoins. On peut par exemple rajouter des champs à la structure `Liste`. Ou bien modifier le chainage

Notamment : le parcours de liste en sens inverse est pathétiquement complexe, puisqu'il faut à chaque fois reparcourir tout le début de la liste.

Pourtant ça peut être pratique ==> variation du concept

### Liste doublement chainée

On modifie la structure `Noeud` pour stocker aussi l'adresse du Noeud précédent

```md
{nullptr , val , ptr} <-> {ptr , val , ptr} <-> {ptr , val , ptr} <-> ... <-> {ptr , val , nullptr}
```

Rq : encore plus de mémoire perdue

On peut aussi utiliser la structure de liste chainée pour créer d'autres conteneurs !

### Pile et file

Les concepts de pile et de file ne sont pas à proprement parler des conteneurs, mais des classes de conteneurs pouvant être implémentées de différentes manières. Par exemple, on peut les implémenter en adaptant la structure de liste chainée, même si ce n'est pas toujours optimal.

Caractérsitique clé de ces concepts : on n'autorise l'insertion qu'à un endroit, la lecture et la suppression à un (autre ?) endroit
Rq : comme ce sont les seules opérations autorisées, on s'attend à ce qu'elles soient optimisées

Pile (stack) : LIFO Last In First Out : L'insertion et la lecture se font au même endroit (le haut de la pile). Ainsi l'élément situé au sommet est le plus récent.
Exemples : pile d'appel, parcours en profondeur...

File (queue) : FIFO First In First Out : L'insertion se fait à une extrémité et la lecture à l'autre.
Exemples : processus/requêtes en attente, parcours en largeur...

On va alors pouvoir modéliser ces deux concepts par une structure de liste chaînée.

Pile : Tout se passe à un endroit, donc on peut rester sur une liste classique, en définissant le sommet de la pile comme le début de la liste

File : Cette fois on a besoin des deux extrémités. On stocke donc dans la structure `Liste` un pointeur sur le dernier élément. On insère à la fin, et on lit/supprime au début de la liste

***Exercice de TP*** : Implémentez l'une de ces structures (au choix). Se référer à <https://hackmd.io/tiWRLgUQRICWbKwFjWJ9Tw> pour le sujet complet.

### Les conteneurs de la librairie standard

Évidemment, tous ces conteneurs (et d'autres encore) sont présents dans le librairie standard du C++. Comme ils sont *très* bien optimisés, c'est une bonne idée de les utiliser, cependant

- ce n'est pas l'objectif du cours
- pour les utiliser à leur plein potentiels, il faut étudier un peu plus le concept d'itérateur

Je ne les vous présenterai donc pas en détail ici, mais je vous encourage à vous y intéresser. Je vous donne quand même les noms :

- `forward_list` : liste simplement chainée
- `list` : liste doublement chainée
- `stack` : pile
- `queue` : file
- `priority_queue` : file avec priorité

Rq : les trois derniers ne sont pas (par défaut) implémentés comme des listes : ils utilisent le conteneur `deque` (double-ended queue) qui est un intermédiaire entre `list` et `vector`

## Les listes chainées en informatique théorique

Pour changer un peu après cette séance très technique, on va faire un petit aperçu du concept de liste chainée en info théorique (qui est évidemment très lié à ce qu'on a fait, mais en plus abstrait). C'est l'occasion de faire une petite intro à l'info théorique pour ceux qui ne connaissent pas (i.e qui ne sont pas en DLMI). Je vous donnerai quelques liens pour approfondir.

On se place dans le contexte de la théorie des types et de certains langages dits **fonctionnels** (qui sont plus propices à la formalisation, cf `lean`). On y construit **par clôture** (i.e par récurrence) l'ensemble des listes d'entiers. En termes techniques, on dit qu'on définit **par induction** le **type** `list` des listes d'entiers. La définition s'énonce alors :

- la liste vide `[]` est une liste d'entiers
- si `n` est un entier et `l` est une liste, on obtient une nouvelle liste d'entiers en ajoutant `n` "au début" de `l` (notation CAML : `n :: l`)

Lien avec notre structure ? Rappelez vous que, pour une liste de base, on a en quelque sorte une équivalence entre les types `Liste` et `Noeud*`. On pourrait donc réécrire nos structures de la manière suivante :

```cpp
struct Noeud {
  int valeur;
  Liste suivant;
};

//Une liste est l'adresse de son premier noeud
//On définit donc le type Liste comme étant exactement le type Noeud*
using Liste = Noeud*;
```

On a donc pour une variable `Liste l;` :

- soit `l == nullptr`, autrement dit `l` est la liste vide
- soit `l != nullptr`, et `l` est la liste obtenue en ajoutant `l->valeur` "au début" de `l`

On retombe bien sur la même chose !

La construction de l'ensemble des listes se traduit par les deux **constructeurs** suivants du type `list` :

- `nil : list` qui renvoie une liste vide.
- `cons : ℤ × list → list` telle que `cons(n,l)= n :: l`

Rq : la notation `truc : montype` peut être comprise de deux manières : comme une valeur de type `list` ou une fonction qui ne prend aucun paramètre et renvoie un objet de type `list`.

Remarquez la similitude entre ces fonctions et nos fonctions `construireListeVide` et `insererDebut`. La seule différence c'est que là où le C++ modifie une liste, l'informatique théorique en crée une nouvelle.

À partir de ces deux constructeurs, on peut construire toutes les listes possibles et imaginables ! La liste `[3,4,5]` s'obtient par exemple de cette manière :

```md
cons(3,cons(4,cons(5,nil())))
```

Exemple : définir fonction `repeat : ℤ × ℕ → list` qui construit une liste en répétant une valeur un certain nombre de fois. Par exemple, `repeat(2,3) = [2,2,2]`. Comme on a défini les listes par récurrences, on fait une fonction récursive :

```md
∀ val : ℤ, ∀ n : ℕ, repeat(val,n) := | nil                       si n=0
                                     | cons(val,repeat(val,n-1)) sinon
```

On a tout ce qu'il faut pour créer des listes, maintenant il faudrait pouvoir les lire. Si on n'est pas en maths ou dans un langage avec **pattern-matching**, on introduit en général deux nouvelles fontions :

- `head : list → ℤ` définie par `∀ n : ℤ, ∀ l : list, head(cons(n,l)) = n`
- `tail : list → list` définie par `∀ n : ℤ, ∀ l : list, head(cons(n,l)) = l`

Cela correspondrait, en `C++`, à pouvoir accéder aux champs de la structure `Noeud`. Remarquons que ces opérations ne sont pas définies sur la liste vide.

Enfin, si l'égalité sur le type `list` n'est pas définie, il faut au moins une fonction `isnil : list → bool` qui indique si une liste est vide (contrairement aux autres fonctions présentées ici, ce nom n'est **pas standard**).

Exemple : définir fonction `eqlist : list × list → bool` qui teste l'égalité de deux listes. Encore une fois, il faut faire une fonction récursive : si l'une des deux listes est vide alors on renvoie `true` ssi les deux listes le sont ; sinon, on vérifie que les deux listes ont la même tête et la même suite :

```md
∀ l1 : list, ∀ l2 : list, eqlist(l1,l2) := | isnil(l2) && isnil(l1)                               si (isnil(l1) || isnil(l2))
                                           | (head(l1) == head(l2)) && eqlist(tail(l1),tail(l2))  sinon
```

Si vous avez eu plus de mal avec cette dernière partie c'est normal, on level up ! Relisez là au calme, posez moi des questions, etc...

Pour finir, quelques exercices sur cette partie théorique, qui vous mettra dans le bain pour le prochain cours sur la récursivité : exprimez, en utilisant les fonctions `nil`, `cons`, `head`, `tail` et `isnil`, les fonctions suivantes :

- `size : list → ℕ` qui renvoie la taille d'une liste
- `range : ℤ × ℤ → list` telle que `range(a,b)=[a,a+1,...,b-2,b-1]`
- `push_back : list × ℤ → list` telle que `pushback([l1,...ln],val)=[l1,...,ln,val]`
- `reverse : list → list` telle que `reverse([l1,...,ln]) = [ln,...,l1]`

Cet exercice est plus dur qu'il n'y parait : inspirez vous des exemples de `repeat` et `eqlist`, prenez le temps d'y réfléchir, et envoyez moi ce que vous avez réussi à faire !
