# Cours d'info 121 A

Objectifs :
- Étude théorique des algorithmes et structures de base
- Étendre la maîtrise du C/C++ (pointeurs, allocation dynamique)
- S'habituer à chercher une méthode optimale

Caractéristiques :
Langage : C++ orienté C
On présentera les deux syntaxes
Pas d'orienté objet

## Trier un tableau

- Très fréquent, dans des situations variées, avec des exigences différentes
- Cas d'école, problème très étudié et classique
- Bonne introduction à la recherche d'algorithme optimal

Suite contiguë d'éléments comparables qu'on veut ordonner (du plus petit au plus grand)
Dans un premier temps, on se concentre sur des **tableaux** (tableaux C, `vector`, `array`) :
l'accès à un élément se fait en tant constant

### Vocabulaire
On dit qu'un algorithme de tri est :
- *stable* quand il ne change pas l'ordre des éléments égaux (sinon instable)
- *en place* quand la quantité de mémoire nécessaire ne dépend pas de la taille du tableau
(en gros c'est quand on ne crée pas d'autre tableau)

Stabilité : dur à voir sur les entiers
Exemple : trier un tableau de `char` par ordre alphabétique sans prendre en compte majuscule/minuscule : 'A'='a'

On prends `tab = ['b','a','A','C','d']`

Un algorithme instable peut renvoyer `['A','a','b','C','d']`
Alors qu'un algorithme stable doit renvoyer `['a','A','b','C','d']`

### Opérations disponibles
Qu'est ce qu'on peut faire dans un tableau : lire et écrire dans les cases

- lecture : comparaison de deux éléments
- écriture : "déplacer" des éléments (! ne rien écraser), souvent sous forme de "swap" : échange de deux éléments

+ L'échange d'éléments en C++ : fonction `swap`

Pour des objets compliqués : `a = b` appelle une fonction qui crée une copie de `b` et la met dans `a`
"Échanger" des cases mémoires : il suffit d'échanger le contenu binaire

### Propositions

#### Tri par sélection

À l'étape `k`, les `k` premières cases du tableau contiennent les `k` plus petits éléments, triés. On cherche alors l'élément le plus petit dans le reste du tableau, et on l'échange avec le `(k+1)`-ième élément, *qui est en position `k`*

On répète le procédé ci-dessus pour `k` allant de 0 à la taille du tableau -1 (ou -2, puisque la dernière étape sera toujours inutile)

Caractéristiques : Non stable, en place, complexité O(n^2) où n est la taille du tableau

#### Tri par insertion

On répète (pour `k` allant de 1 à la taille du tableau)
À l'étape `k`, les `k` premiers éléments sont triés (mais ce ne sont plus forcément les `k` plus petits éléments du tableau). On va alors insérer le premier élément non trié, à savoir le `(k+1)`-ième, *d'indice `k`*, et on va l'insérer à la bonne position pour que les `k+1` premiers éléments soient triés.

On répète le procédé ci-dessus pour `k` allant de 1 à la taille du tableau -1

Deux visions possibles pour savoir où insérer le (k+1)e élément :
- On fait des échanges deux à deux en le faisant "remonter" jusqu'à ce qu'à trouver un élément plus petit **ou arriver au début du tableau**
- On cherche d'abord la position où on va l'insérer (comme une partie du tableau est triée, on a des algorithmes efficaces), on décale vers la fin du tableau tous les éléments qui sont entre cette position et la fin de la zone triée, et on insère l'élément à la place libérée

Caractéristiques : Stable, En place, Complexité O(n^2)

Au pire, le tableau est trié en ordre inverse, et alors le `k`-ième élément doit systématiquement remonter `k` cases
Le nombre d'échanges est donc n(n+1)/2, d'où la complexité au pire en O(n^2)

#### Tri à bulles

Jusqu'à ce que le tableau soit trié, on répète :
On parcourt le tableau en comparant les éléments adjacents, et on les échange si ils ne sont pas dans le bon sens

On observe que chaque parcours du tableau fait remonter vers la fin l'élément le plus grand, comme une bulle dans une boisson gazeuse

Caractéristiques : Stable, en place, O(n^2)
