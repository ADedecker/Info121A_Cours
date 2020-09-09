# Cours 5 : récursion et tri fusion

## Rappels sur la récursion

Fonction "récursive" := s'appelle elle-même

```cpp
void rec() {
  rec();
}
```

Deux problèmes de cet exemple : 1) rien d'intéressant 2) on n'en sort jamais

==> **TOUJOURS METTRE UNE CONDITION D'ARRÊT**

```cpp
void loop(unsigned int n) {
  if(n == 0) return;
  loop(n-1);
}
```

C'est toujours inintéressant, mais au moins ça s'arrête !

Rq : en C++, le compilateur traite les fonctions récursives de la même façons que toutes les autres;

Pourquoi cette idée tordue de s'appeler soi-même ?

**Usage 1** : exprimer plus naturellement certaines définitions mathématiques

En maths, c'est très courant de définir des objets/des ensembles de manière récursive

Exemple : suites récurrentes

- D'ordre 1 : u(0) = a ; ∀ n, u(n+1) = f(u(n)). Exemple : suites arithmético-géométriques
- En info, on généralise en : u(0) = a ; ∀ n, u(n+1) = f(n,u(n)). Exemple : factorielle f(a,b) = a*b
- D'ordre p : u(0) = a(0) ; u(1) = a(1) ; ... ; u(p-1) = a(p-1) ; ∀ n, u(n+p) = f(n,u(n),u(n+1),...,u(n+p))

Ces suites se calculent naturellement de manière récursive.

Exemple : factorielle

```cpp
int fac(int n) {
  if (n == 0) return 1;
  return n*fac(n-1);
}
```

Rq :
- en maths on va "vers l'avant" : on définit fac(0), on en déduit fac(1), puis fac(2), ...
- en info on va "vers l'arrière" : on veut calculer fac(20), pour ça on doit calculer fac(19). Il faut donc aussi fac(18), ...

Rq sur les performances : en C++, l'appel de fonction est coûteux (empilement et dépilement). De plus c'est inefficace en mémoire (on le remarque en étudiant l'évolution de la pile). Du coup, on préfère toujours la version itérative à la version récursive, **quand elle existe**.

Ces problèmes sont en grande partie résolus par les langages dits "fonctionnels"

Exemple 2 : Fibonacci

```cpp
unsigned long long fib(int n) {
  if(n==0) return 0;
  if(n==1) return 1;
  return fib(n-1) + fib(n-2);
}
```

```
fib(4)
->fib(3)
  ->fib(2)
    -> fib(1)
    -> fib(0)
  ->fib(1)
->fib(2)
  -> fib(1)
  -> fib(0)
```

C'est très inefficace car on calcule plusieurs fois la même chose ==> Complexité exponentielle !!!!

Une solution possible : technique de mémorisation. C'est faisable en C++, mais seulement à la compilation (pas toujours satisfaisant)

Ici le problème n'est plus seulement le coût de l'appel de fonction, c'est la conception qui est mauvaise ! On va pouvoir résoudre ça avec un peu de théorie de la récursion

## Récursion, boucle, récursion terminale

Petit détour par la programmation **fonctionnelle**

En schématisant :
- en impératif (ce que vous connaissez), un programme est composé d'un état initial (état de la mémoire, données, constantes, ...) et d'une suite d'instructions qui modifient l'état courant, exécutées à la suite dans un ordre donné. L'avantage : c'est très proche du fonctionnement interne. Le défaut : c'est assez difficile de raisonner sur un programme, car il faut prendre en compte l'effet de chaque instruction sur l'état actuel dans son ensemble.
- en fonctionnel : il y a aussi un état initial, mais cette fois le programme est une fonction, au sens **mathématique**, qui prend en paramètre l'état initial et renvoie l'état final. Cette fonction est définie comme un emboitement de fonctions du même genre, ainsi que de fonctions "de bases". Il n'y a plus de notion de **modification**. L'avantage : ça colle très bien aux maths, et c'est facile de raisonner dessus. Le défaut : c'est assez éloigné du fonctionnement interne, donc c'est généralement plus lent

Fun fact : Avant que Alan Turing n'invente la "machine de Turing" qui modélise un programme impératif, Alonzo Church avait formalisé le **lambda-calcul**, une construction équivalent en mode fonctionnel.

Dans les langages fonctionnels, il n'y a pas de boucles.
Boucle = répéter des actions. Pas d'actions dans les langages fonctionnels !

Pour modéliser des répétitions, on fait des fonctions récursives ! Avec plein d'optimisations

L'une des ces optimisations va nous intéresser particulièrement : on peut transformer certaines récursions en boucles

**Définition** : Récursion terminale

On dit qu'un appel récursif est terminal si c'est la dernière instruction de la fonction à être évaluée? Par conséquent, si il y a une valeur de retour, ce sera exactement celle de cet appel récursif.

```cpp
int foo(int n) {
    if (n==0) return 1;
    return n * foo(n-1);
    //Non terminal car le `n *` est exécuté après l'appel récursif
}

int bar(int n, int acc) {
    if (n==0) return acc;
    return bar(n-1,n*acc);
    //Terminal
}
```

Propriété 1 : Une récursion terminale peut facilement être traduite comme une boucle !

La valeur de retour est exactement celle de l'appel terminal, donc les autres variables n'interviennent plus. On peut donc remplacer l'appel par un retour au début avec les nouvelles valeurs des paramètres

```cpp
int bar2(int n, int acc) {
  while(true) {
    if(n==0) return acc;
    acc = n*acc;
    n = n-1;
  }
}
```

On remarque donc que `bar(n,1)` calcule `fac(n)`.

Propriété 2 : Ça marche aussi dans l'autre sens !

L'idée est de transformer toutes les variables utilisées dans la boucle en paramètres de la fonction, et de les "modifier" dans l'appel terminal

Exemple en transformant le version itérative de la fonction `fib` :

```cpp
unsigned long long fibiter(int n) {
  unsigned long long a = 0;
  unsigned long long b = 1;
  if(n == 0) return 0;
  for (int i = 1; i < n; i++) {
    b=a+b;
    a=b-a;
  }
  return b;
}

//Donne :

unsigned long long fibutil(unsigned long long a, unsigned long long b, int n, int i) {
  if(i == n) return b;
  return fibutil(b,a+b,n,i+1);
}

unsigned long long fibcool(int n) {
  if(n == 0) return 0;
  return fibutil(0,1,n,1);
}
```

Rq : on a "montré" une forme d'équivalence entre les boucles et la récursion terminale.
MAIS toutes les fonctions récursives ne peuvent pas être rendues terminales. Dans ces cas là, il va falloir utiliser la récursion, même dans les langages impératifs.

## Application : Tri fusion

Le "tri fusion" est un algorithme de tri des listes chainées de complexité O(n log n)

Procédure `merge` : si deux listes sont triées, on peut facilement trier la concaténation de ces listes

Idée : "diviser pour régner" : on coupe la liste à trier en deux, on trie chacune des parties, et on fusionne

==> Algortihme récursif : `merge_sort` appelle `merge_sort` sur chacune des deux sous-listes

Ici il y a deux appels ==> on ne peut pas transformer en récursion terminale !

- **Usage 2** : stratégie "diviser pour régner". Dans de nombreux cas, on ne peut *pas* se passer de la récursion pour cette stratégie

Implémentation du tri fusion dans `exemples/tris/merge_sort.cpp`

**Remarque importante** concernant la mémoire : On peut montrer que cette implémentation ne cause pas de fuite de mémoire (à l'exception des cas d'échecs de l'allocation, qu'il faudrait traiter). Ce n'est pas évident et cela nécessite de changer un peu de point de vue : plutôt que de vérifier que chaque allocation est associée à une et une seule libération, la clé est de vérifier que, tout au long du tri, chaque Noeud a **un et un seul** propriétaire.

Plutôt que de m'étendre en définitions théoriques, je vous renvoie au fichier `exemples/tris/merge_sort.cpp` que j'ai commenté les différents changements de propriétaires. Je vous conseille de le lire dans l'ordre d'appel, c'est à dire en commençant par le fonction `merge_sort`. Fun fact, le concept de propriétaire est tellement pratique pour éviter les fuites de mémoire qu'il a été intégré dans la sémantique du langage `Rust` !







_
