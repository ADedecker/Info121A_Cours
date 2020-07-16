# Le tri rapide

Algorithme de tri de tableau

Stratégie "diviser pour régner"

En place, non stable, complexité :
- au pire `O(n^2)`
- en moyenne `O(n log(n))`

MAIS en pratique c'est l'algorithme le plus utilisé car :
- la constante est très avantageuse (pour rappel la complexité est toujours exprimée à une constante près : un algorithme faisant `log(n)` opérations qu'un algorithme qui en fait `100*log(n)`)
- les cas "dégénérés" sont peu courant et facilement identifiables, donc on peut les éviter en rebasculant sur un algo "de secours"

Idée générale :
1) On choisit un "pivot" parmi les éléments du tableau
2) On "partitionne" le tableau : on le réorganise de manière à avoir : tous les éléments plus petits que le pivot à gauche du pivot ; tous les éléments plus grands à droite du pivot
3) On trie de la même manière chacun des deux sous-tableaux

La grande question : comment implémenter les étapes 1 et 2

## Choix du pivot

Pour que l’efficacité soir optimale, on veut que les deux sous tableaux créés aient des tailles les plus proches possibles. On minimise ainsi la profondeur de récursion

L'idéal : médiane du tableau. Il y un algorithme pour la trouver en temps O(n) ce qui permet d'avoir un tri en O(n log(n)) dans tous les cas. MAIS, bien que la complexité asymptotique soit optimale, la constante est très mauvaise et le tri ainsi obtenu est plutôt lent.

Pivot arbitraire. Par exemple : toujours le premier/dernier élément du tableau. Complexité moyenne : O(n log n). Pb : on atteint le cas O(n^2) sur les tableaux presque triés, ce qui est un cas d'usage très courant

Pivot aléatoire : toujours O(n log n) en moyenne, O(n^2) au pire, mais le cas "au pire" est moins fréquent

## Algorithme de partitionnement

On en présente un, qui n'est pas le plus optimal.

1) On met le pivot à la fin du tableau
2) Les "0" premiers éléments sont correctement partitionnés
3) On rajoute au fur et à mesure les éléments dans la partie partitionnée du tableau de manière à ce que les éléments ≤ au pivot soient situés avant les éléments > au pivot. Plus précisément, si ils sont plus grand on ne les déplace pas, sinon on le place à la fin de la portion des éléments qui sont plus petits que le pivot

Pb de cet algorithme : ***très*** mauvais pour les tableaux contenant une seule valeur répétée

## Optimisations possibles

- Autre algorithme de partitionnement : généralement plus efficace, et surtout plus efficace pour les tableaux constants
- On peut détecter les cas "dégénérés" qui vont engendrer O(n^2) et basculer sur un autre algorithme de tri
- Une fois que le tableau est assez petit, on utilise un autre algorithme de tri (par exemple tri par insertion), ce qui permet d'éviter pleins d'appels récursifs pour une opération quasi-instantanée
- Rq : l'un des deux appels récursifs est terminal ==> on peut l'optimiser pour éviter trop d'appels récursifs

TP : compléter le fichier `TP/Quicksort/quicksort.cpp`
