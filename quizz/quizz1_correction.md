# Correction du quiz 1

## Partie 1

### Question 1

```cpp
int a = 25;
int b = a;
b = 42;
cout<<a<<endl;
```

- Ce code ne compile pas
- Ce code a un comportement indéfini (SEGFAULT, fonctionnement bizarre...)
- **Ce code affiche `25`**
- Ce code affiche `42`
- Ce code affiche une adresse mémoire

Explication : La ligne `int b=a` **copie** le contenu de `a` dans `b`, mais il n'y a aucune raison que changer `b` change le contenu de `a`.

### Question 2

```cpp
int a = 25;
int* b = &a;
*b = 42;
cout<<a<<endl;
```

- Ce code ne compile pas
- Ce code a un comportement indéfini (SEGFAULT, fonctionnement bizarre...)
- Ce code affiche `25`
- **Ce code affiche `42`**
- Ce code affiche une adresse mémoire

Explication : Le pointeur `b` contient l'adresse de `a`, donc modifier `*b` revient à modifier `a`.

### Question 3

```cpp
int a = 25;
int* b = &a;
b = 42;
cout<<*b<<endl;
```

- **Ce code ne compile pas**
- Ce code a un comportement indéfini (SEGFAULT, fonctionnement bizarre...)
- Ce code affiche `25`
- Ce code affiche `42`
- Ce code affiche une adresse mémoire

Explication : On ne peut pas assigner une valeur entière à une variable contenant l'adresse d'un entier.

### Question 4

```cpp
int a = 25;
int* b = &a;
a = 42;
cout<<b<<endl;
```

- Ce code ne compile pas
- Ce code a un comportement indéfini (SEGFAULT, fonctionnement bizarre...)
- Ce code affiche `25`
- Ce code affiche `42`
- **Ce code affiche une adresse mémoire**

Explication : On affiche `b`, autrement dit l'adresse de `a`. Pour afficher la valeur de `a`, il aurait fallu afficher `*b`.

## Partie 2

### Question 5

```cpp
void swap(int* p_a, int* p_b) {
  int* tmp;
  tmp = p_a;
  p_a = p_b;
  p_b = tmp;
}

int main() {
  int a = 2, b = 3;
  swap(&a,&b);
  cout<<a<<" "<<b<<endl;
}
```

- Ce code ne compile pas
- Ce code a un comportement indéfini (SEGFAULT, fonctionnement bizarre...)
- Ce code affiche `3 2`
- **Ce code affiche `2 3`**
- Ce code affiche `2 2`

Explication : Ici, la fonction swap échange les contenus de `p_a` et `p_b`, c'est à dire que `p_b` contient l'adresse de `a` et `p_a` celle de `b`. Mais les valeurs contenues à ces adresses ne sont pas modifiées, donc les contenus de `a` et `b` ne changent pas.

### Question 6

```cpp
void swap(int* p_a, int* p_b) {
  int tmp;
  tmp = * p_a;
  * p_a = * p_b;
  * p_b = tmp;
}

int main() {
  int a = 2, b = 3;
  swap(a,b);
  cout<<a<<" "<<b<<endl;
}
```

- **Ce code ne compile pas**
- Ce code a un comportement indéfini (SEGFAULT, fonctionnement bizarre...)
- Ce code affiche `3 2`
- Ce code affiche `2 3`
- Ce code affiche `2 2`

Explication : La ligne `swap(a,b);` est invalide. En effet, on donne des valeurs de type `int` alors que la fonction attend `int*`.

### Question 7

```cpp
void swap(int* p_a, int* p_b) {
  int tmp;
  tmp = * p_a;
  p_a = p_b;
  * p_b = tmp;
}

int main() {
  int a = 2, b = 3;
  swap(&a,&b);
  cout<<a<<" "<<b<<endl;
}
```

- Ce code ne compile pas
- Ce code a un comportement indéfini (SEGFAULT, fonctionnement bizarre...)
- Ce code affiche `3 2`
- Ce code affiche `2 3`
- **Ce code affiche `2 2`**

Explication : La fonction `swap` ne modifie pas `*p_a`, donc la valeur de `a` ne change pas. Par contre elle copie bien la valeur initiale de `*p_a` dans `*p_b`, ce qui équivaut à effectuer `b = a`.

### Question 8

```cpp
void swap(int* p_a, int* p_b) {
  int tmp;
  tmp = * p_a;
  * p_a = * p_b;
  * p_b = tmp;
}

int main() {
  int a = 2, b = 3;
  swap(&a,&b);
  cout<<a<<" "<<b<<endl;
}
```

- Ce code ne compile pas
- Ce code a un comportement indéfini (SEGFAULT, fonctionnement bizarre...)
- **Ce code affiche `3 2`**
- Ce code affiche `2 3`
- Ce code affiche `2 2`

Explication : Ici le code est correct : `*p_a` désignant `a` et `*p_b` désignant `b`, le corps de la fonction revient à :
```cpp
int tmp;
tmp = a;
a = b;
b = tmp;
```

## Partie 3

### Question 9

Contexte : vous en avez marre de devoir vous rappeler la syntaxe de `malloc`. Vous demandez à votre équipe de développeur de coder une fonction `int* nouvelEntier(int valeur)` qui alloue manuellement un entier, lui assigne la valeur `valeur`, et renvoie son adresse. Ils vous proposent les codes suivants :

**Code A :**
```cpp
int* nouvelEntier(int valeur) {
  int a = valeur;
  return &a;
}
```

**Code B :**
```cpp
int* nouvelEntier(int valeur) {
  int* a = (int*)malloc(sizeof(int));
  * a = valeur;
  return a;
}
```

**Code C :**
```cpp
int* nouvelEntier(int valeur) {
  int a = (int)malloc(sizeof(int));
  a = valeur;
  return &a;
}
```

**Code D :**
```cpp
int* nouvelEntier(int valeur) {
  int* a = (int*)malloc(sizeof(int));
  * a = valeur;
  return &a;
}
```

Lequel choisissez-vous :
- Le code A
- **Le code B**
- Le code C
- La réponse D
- Le code D

Explication :
- Le code A renvoie l'adresse d'une variable locale, qui n'existe plus après le `return`
- Le code C fait de même. De plus, il essaye de stocker l'adresse renvoyée par `malloc` dans un entier (attention, dans certains cas ce genre de code compile et a un comportement très imprévisible).
- Le code D renvoie l'adresse d'une variable de type `int*` au lieu de l'adresse d'une variable de type `int`

### Question 10

Le développeur du code correct est tellement fier de son code qu'il le publie sur Stack Overflow avec un petit exemple :

```cpp
int main() {
  //Ce programme calcule les 10 premiers termes de la suite de Fibonacci
  int* tab[10];
  tab[0] = nouvelEntier(0);
  tab[1] = nouvelEntier(1);
  for (int i = 2; i < 10; i++) {
    tab[i] = nouvelEntier(*(tab[i-1]) + *(tab[i-2]));
  }
  //Affichage
  for (int i = 0; i < 10; i++) {
    cout<<tab[i]<<endl;
  }
}
```

Étant un bon développeur, il a vérifié que son programme marche. Pourtant, parmi les réponses négatives qu'il reçoit l'une est justifiée, laquelle ?

- On ne doit pas utiliser `malloc` en C++
- Il faut utiliser des pointeurs intelligents et la RAII
- **Ce programme cause une fuite de mémoire**
- Faites du python c'est plus intuitif

Explication : La fonction `nouvelEntier` fait une allocation manuelle mais la mémoire n'est jamais libérée. Il y a donc fuite de mémoire. 
