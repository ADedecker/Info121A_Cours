# Quiz 1 : Les pointeurs, première approche

Au dernier cours, nous avons fait une petite introduction aux pointeurs. Le sujet étant assez délicat mais très important, j'ai souhaité préparer un petit questionnaire que nous corrigerons en cours. Le but est principalement l'auto-évaluation, donc vous aurez les réponses à la fin. Si ça ne vous dérange pas, je veux bien que vous me transmettiez les questions où vous vous êtes trompés, afin que j'aie une petite idée des difficultés.

Les questions portent sur des extraits de code (pas toujours corrects), lisez les attentivement !

## Partie 1

### Question 1

```cpp
int a = 25;
int b = a;
b = 42;
cout<<a<<std::endl;
```

- Ce code ne compile pas
- Ce code a un comportement indéfini (SEGFAULT, fonctionnement bizarre...)
- Ce code affiche `25`
- Ce code affiche `42`
- Ce code affiche une adresse mémoire

### Question 2

```cpp
int a = 25;
int* b = &a;
*b = 42;
cout<<a<<std::endl;
```

- Ce code ne compile pas
- Ce code a un comportement indéfini (SEGFAULT, fonctionnement bizarre...)
- Ce code affiche `25`
- Ce code affiche `42`
- Ce code affiche une adresse mémoire

### Question 3

```cpp
int a = 25;
int* b = &a;
b = 42;
cout<<*b<<std::endl;
```

- Ce code ne compile pas
- Ce code a un comportement indéfini (SEGFAULT, fonctionnement bizarre...)
- Ce code affiche `25`
- Ce code affiche `42`
- Ce code affiche une adresse mémoire

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
- Ce code affiche une adresse mémoire

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
- Ce code affiche `2 3`
- Ce code affiche `2 2`

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

- Ce code ne compile pas
- Ce code a un comportement indéfini (SEGFAULT, fonctionnement bizarre...)
- Ce code affiche `3 2`
- Ce code affiche `2 3`
- Ce code affiche `2 2`

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
- Ce code affiche `2 2`

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
- Ce code affiche `3 2`
- Ce code affiche `2 3`
- Ce code affiche `2 2`

## Partie 3

### Question 9

Contexte : vous en avez marre de devoir vous rappeler la syntaxe de `malloc`. Vous demandez à votre équipe de développeur de coder des fonctions qui `int* nouvelEntier(int valeur)` qui alloue manuellement un entier, lui assigne la valeur `valeur`, et renvoie son adresse. Ils vous proposent les codes suivants :

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
  int a = (int)malloc(sizeof(int));
  a = valeur;
  return &a;
}
```

**Code C :**
```cpp
int* nouvelEntier(int valeur) {
  int* a = (int*)malloc(sizeof(int));
  * a = valeur;
  return a;
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
- Le code B
- Le code C
- La réponse D
- Le code D

### Question 10

Le développeur du code correct est tellement fier de son code qu'il le publie sur Stack Overflow avec un petit exemple :

```cpp
int main() {
  //Ce programme calcule les 10 premiers termes de la suite factorielle
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
- Ce programme cause une fuite de mémoire
- Faites du python c'est plus intuitif

# Réponses

Voici les bonnes réponses, je donnerai plus d'explication au prochain cours :
- q1 : 3
- q2 : 4
- q3 : 1
- q4 : 5
- q5 : 4
- q6 : 1
- q7 : 5
- q8 : 3
- q9 : 3
- q10 : 3
