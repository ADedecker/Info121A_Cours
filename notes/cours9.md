# Tri par tas

Algorithme de tri de tableau en O(n log n)

## Prérequis : autre représentation de certains arbres binaires

On a vu le "parcours" d'arbre, i.e comment parcourir linéairement les noeuds d'un arbre (enraciné)

Évidemment, même pour une méthode de parcours donnée, des arbres différents peuvent donner la même suite de noeuds

```md
    A                   A
   / \                  |
  B   C       et        B
     / \               /|\
    D   E             C D E
```

donnent `ABCDE` par un parcours en largeur.

Cependant, il y a un cas particulier où on va pouvoir établir **une bijection** :

**Le fonction qui associe un arbre binaire "quasi-parfait" à sa représentation par un parcours en largeur est une bijection**

- Arbre binaire : arbre enraciné où chaque noeud a **au plus** 2 fils
- Arbre binaire parfait : arbre binaire où 1) tout noeud à 0 ou 2 fils 2) toutes les feuilles ont la même profondeur
- Arbre binaire quasi-parfait : arbre binaire parfait privé d'un certain nombre de ses feuilles; de telle sorte que les feuilles soient "tassées" à gauche

```md
    0                  0                  0
   / \                / \                / \
  1   2             1     2            1     2
     / \           / \   / \          / \   /
    3   4         3   4 5   6        3   4 5

```

Sur ce schéma, le numéro du noeud correspond à son indice dans l'ordre de parcours en largeur

Cherchons la bijection réciproque.

On remarque : si ils existent, les fils du noeud d'indice `n` sont, dans un arbre binaire quasi-parfait, les noeuds d'indice `2n+1` et `2n+2`

Autrement dit, n'importe quelle suite d'éléments définit un arbre binaire quasi-parfait : l'élément `0` est la racine, et ∀i, les fils de l'élément `i` sont, s'ils existent, les éléments `2i+1` et `2i+2`

Corollaire : tout tableau correspond à un unique arbre binaire quasi parfait ! (et réciproquement)

## Idée clé du tri par tas (heap sort)

On va partir du tri par sélection

Principe du tri par sélection : chercher l'élément maximal du tableau, le mettre à lé fin, et recommencer sur les éléments restant. Problème principal : trouver l'élément maximal implique de parcourir le tableau entier

Les arbres vont nous aider à améliorer cette opération

Instéressons nous à une sous catégorie des arbres binaires : les tas binaires

Définition : **Un tas binaire est un arbre binaire quasi-parfait où chaque noeud est associé à une valeur, de sorte que la valeur de chaque noeud soit plus grande que la valeur des ses deux fils**

Propriété intéressante : **la valeur la plus grande de l'arbre est celle de la racine**

```md

     6
    / \        
  5     4      
 / \   /     
3   1 2  
```

On a donc l'algo de tri suivant :

- réorganiser le tableau pour que l'arbre quasi-parfait associé soit un tas binaire
- répéter pour `i` allant de `n-1` à `1` :
  - échange l'élément 0 (la racine du tas) et l'élément `i`
  - "réparer" l'arbre de sorte que les éléments `0` à `i-1` forment de nouveau un tas binaire

Il reste deux points à expliquer. Commençons par la "réparation"

## Tamisage

Supposons que les `i` premiers éléments forment un tas binaire. On échange alors les éléments `0` et `i`

Du point de vue du tas, on interprète ça comme : on retire la racine, et on la remplace par une feuille du tas, plus précisément la feuille la plus à droite sur la rangée la plus profonde du tas (on garde donc un arbre quasi parfait)

```md
     6
    / \        
  5     4      
 / \   / \      
3   1 2   0   

     0
    / \        
  5     4      
 / \   /     
3   1 2   

```

On remarque que les sous arbres engendrés par les fils de la racine sont toujours des tas ! Il n'y a que la racine qui pose problème

Solution : **Échanger la racine et le plus grand de ses fils**

```md

     5
    / \        
  0     4      
 / \   /     
3   1 2   

```

Maintenant, il y a un problème dans le sous arbre où on a fait l'échange. Mais ce problème ne concerne que la racine de ce sous-arbre, donc on va le résoudre **en répétant la même opération** ==> On tamise récursivement jusqu'à ce qu'il n'y ait plus de problème

```md

     5
    / \        
  3     4      
 / \   /     
0   1 2   

```

Cette opération récursive s'appelle le "tamisage" et elle vérifie la propriété suivante : si les deux sous arbress engendrés par les fils de la racine sont des tas, le tamisage transforme l'arbre entier en tas

Rq : une autre manière de la voir, est : on "fait descendre" la racine dans l'arbre jusqu'à ce qu'elle soit plus grande que ses deux fils

## Formation du tas

On va se servir intelligemment de la procédure de tamisage

Propriété fondamentale du tamisage : si les deux sous-arbres engendrés par les fils de la racine sont des tas, il suffit d'appliquer la prcédure de tamisage pour transformer l'arbre entier en tas

Du coup, pour former un tas, il suffit de :
- transformer chacun des sous arbres en tas (appel récursif de la procédure de formation du tas)
- tamiser

Pour être sur du bon fonctionnement, condition d'arrêt ? Un arbre d'un seul noeud est un tas !







_
