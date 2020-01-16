//Exemples de fonctions pures:

//La fonction floor:

/*Cette fonction retourne la valeur entière d'un nombre, soit l'entier le plus proche inférieur ou égal au nombre.

Voici un exemple montrant une utilisation plus classique de cette fonction :*/

double floor( double value );


//subsubsection{La fonction max(resp.min)}

double MAX(double X, double Y)
{
if (X>Y) return X;
else return Y;
}


//Non localité des paramètres

//à cause de la variation de la valeur de retour avec une variable non locale

int f() {
    return x;
}


//Référence externe

//à cause de la variation de la valeur de retour avec un argument mutable de type référence

int f(int* x) {
    return *x; 
}


//Entrées-Sorties

//à cause de la variation de la valeur de retour avec un flux d'entrée

int f(int x) {
    x = 0;
    scanf("%d, &x);
    return x;
}


//Les fonctions C suivantes sont impures car elles ne vérifient pas la propriété 2 ci-dessus :

//L'effet de bord ici est de modifier la valeur de la variable non local:

void f() {
    ++x;
}


//à cause de la mutation d'une variable statique locale :

{
    static int i=0; 

    i++;
    
}



//à cause de la mutation d'un argument mutable de type référence:

void f(int* a) {
     ++*a;
}

//à cause de la mutation d'un flux de sortie

void f()
{
    printf("Hello.\n");
}

