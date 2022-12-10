#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h> 
#include "Appart.h"

housing * RangeFichierDansTableau(housing * accomodation, int TailleTab){
    //cette fonction range toutes les informations sur les caracteristiques des logements du fichier dans un tableau de type housing
    //ce tableau se nomme accomodation

    char tableau[1000]; //nombre de caractere sur 1 ligne du fchier
    int numLigne = 0; //le ligne a laquelle on est au fur et a mesure de la lecture du fichier
    char * delimiteur; //le ";" delimite les colonnes dans le fichier de donnees
    int k = 0; //represente la caracteristique, c'est le numero de colonne 
    int separateur; //le ";" mais en equivalent entier ?????????????????????????????????????????????????????????????????????????????????????????
    //printf("separateur 1 = %d\n", separateur);

    //on ouvre le fichier
    FILE * file = NULL;
    file = fopen("airbnb_donnees_propres.csv","r"); //ouvre en lecture

    //On lit chaque case du fichier puis on range les informations dans le tableau accomodation
    if (file != NULL){
        fgets(tableau, 200, file); //lire la lire qui fait max 200 carac
        for(int i=0; i<TailleTab; i++){ //on parcours fichier jusqu'a la ligne 7918
            
            fgets (tableau, 200, file); //relit la ligne
            delimiteur = strtok(tableau,","); // ;
            k = 0;    
            while(delimiteur){ //tant que pas a la fin ligne
                separateur = atoi(delimiteur); //transforme en entier
                //printf("separateur %d = %d\n", numLigne, separateur);
                switch(k){
                    case 0:
                        accomodation[i].numLigne = numLigne;
                        break;
                    case 1:
                        accomodation[i].accommodates = atoi(delimiteur);
                        break;
                    case 2:
                        accomodation[i].bedrooms = atoi(delimiteur);
                        break;
                    case 3:
                        accomodation[i].bathrooms = atoi(delimiteur);
                        break;
                    case 4:
                        accomodation[i].beds = atoi(delimiteur);
                        break;
                    case 5:
                        accomodation[i].price = atoi(delimiteur);
                        break;
                    case 6:
                        accomodation[i].min_night = atoi(delimiteur);
                        break;
                    case 7:
                        accomodation[i].max_night = atoi(delimiteur);
                        break;
                    case 8:
                        accomodation[i].number_review = atoi(delimiteur);
                        break;
                    default :
                        break;
                }
                delimiteur = strtok(NULL,","); //fin de ligne atteint
                k++;
            }
            k = 0;
            for (int j = 0; j < TailleTab; j++){
                accomodation[i].tabDistance[j].distance = 0;
                accomodation[i].tabDistance[j].numeroLigne = numLigne;
            }

            numLigne++;
        }
        fclose(file);
        return accomodation;

    }else{ //si le fichier n'a pas ete trouve
        printf("Fichier CSV non trouve\n");
    }

}

int RechercheDansTableau(housing * accomodation, int ligne, int colonne){
//cette fonction est appelee lorsqu'on recherche un element connaissant son numero de colonne et de ligne
//elle renvoie la valeur recherchee en traduisant le numero de colone par le une variable de housing.
    int y;
    switch(colonne){
        case 0:
            y =  accomodation[ligne].numLigne;
            break;
        case 1:
            y =  accomodation[ligne].accommodates;
            break;
        case 2:
            y =  accomodation[ligne].bedrooms;
            break;
        case 3:
            y =  accomodation[ligne].bathrooms;
            break;
        case 4:
            y =  accomodation[ligne].beds;
            break;
        case 5:
            y =  accomodation[ligne].price;
            break;
        case 6:
            y =  accomodation[ligne].min_night;
            break;
        case 7:
            y =  accomodation[ligne].max_night;
            break;
        case 8:
            y =  accomodation[ligne].number_review;
            break;
        default :
            printf("L'element n'est pas dans le tableau\n");
            y = -1;
            break;
    }
    return y;
}

void CalculeDistance(housing * accomodation, int TailleTab){
//Cette fonction calcule la distance euclidienne entre un element et tout les autres en fonction de une ou plusieurs caracteristiques
    float * Distance = malloc(TailleTab * sizeof(float)); //Distance est un tableau ou pour chaque indice (=ligne de l'element), met la valeur de la distance euclidienne avec l'element de comparaison
    float ecart; //ecart est une variable qui contient la difference de valeur d'une caracteristique entre un element et celui qui nous interesse 
    int nbcarac; //le nombre de caracteristiques etudie lors du calcule de la distance
    
    printf("Combien de caracteristiques voulez-vous prendre en compte dans le calcule de la distance ?\n");
    scanf("%d", &nbcarac);
    int * caracteristiquesAEtudier = malloc(nbcarac * sizeof(int)); //tableau contenant les numeros des colonnes des caracteristiques a etudier
    printf("Quelles sont-elles ? accomodate = 1, bedrooms = 2, bathrooms = 3, beds = 4, price = 5, min_night = 6, max_night = 7, number_review = 8\n");
    printf("\n Rentrez les chiffres un par un\n");
    printf("\nLe calcul pourra prendre plusieurs minutes\n");
    for(int i=0; i<nbcarac; i++){
        scanf("%d", &caracteristiquesAEtudier[i]);
    }

    //on calcule le tableau de distances euclidiennes pour chaque logement
    for(int numAppart=0; numAppart < TailleTab; numAppart++){ 
        //on initialise le tableau des valeurs des distances a 0 partout
        for(int i=0; i<TailleTab; i++){
            Distance[i] = 0;
        }
        for(int i=0; i<nbcarac; i++){   //pour chaque carcateristique 
            for(int n=0; n < TailleTab; n++){ //on parcours le tableau accomodattion
                ecart = abs(RechercheDansTableau(accomodation, numAppart, caracteristiquesAEtudier[i]) - RechercheDansTableau(accomodation, n, caracteristiquesAEtudier[i])); //valeur absolue de la difference dentre les 2 nombres
                Distance[n] = Distance[n] + ecart*ecart;  //calcule de la distance au carre
            }
        }
        
        for(int n=0; n < TailleTab; n++){ 
            Distance[n] = sqrt(Distance[n]);  //calcule de la distance qui est la RACINE de la somme des carres des ecarts absolus
            accomodation[numAppart].tabDistance[n].distance = Distance[n];
            accomodation[numAppart].tabDistance[n].numeroLigne = n;
        }
    }

    /*printf("on affiche le tableau 1 \n");
    for(int i=0; i < 5; i++){
        printf("%f\t", accomodation[0].tabDistance[i].distance );
    }*/
}

void Randomiser(housing * accomodation, int TailleTab){ //melange le tableau accomodation
    housing tmp;
    int y;
    for(int i=0; i < TailleTab; i++){ //on echange chaque case du tableau avec une autre case se trouvant apres, on le change pas la premiere ligne qui correspond au logement que l'on compare avec tous les autres
        y = rand()%(TailleTab-i);
        tmp = accomodation[i];
        accomodation[i] = accomodation[i+y];
        accomodation[i+y] = tmp;
    }
}

void Permuter(ElementTabDistance * tabDistance, int x, int y){
//cette fonction echange 2 elements du tableau accomodation en connaissant leur indice
    ElementTabDistance tmp;
    tmp = tabDistance[x];
    tabDistance[x] = tabDistance[y];
    tabDistance[y] = tmp;
}

//On trie le tableau de chaque logement en fonction de la distance de chaque element avec le logement qui nous interesse
//Pour cela, on utilise le trie rapide, il se fait en trois algorithmes : Partition, TriRapide qui appelle partition pour le tableau divise et TriTab qui appelle les autres.
int Partition(ElementTabDistance * tabDistance, int p, int r){
//cette fonction met tous les elements qui sont inferieurs au pivot a sa gauche et tous les elements qui sont superieurs a sa droite
    float x = tabDistance[r].distance; //pivot
    int i = p-1;
    //printf("\n");
    for (int j = p; j < r; j++){
        if (tabDistance[j].distance <= x){ //si la distance est plus petite que le piveau
            i++;
            Permuter(tabDistance, i, j); //on la met a gauche, a l'indice i
        }
    }
    if (p+1 == r){ //si il n'y a que deux element dans le tableau, si le premier element est plus petit que le pivot (le second element) alors on les echange
        //printf("if : taille = 2\n");
        if (tabDistance[p].distance > x){
            //printf("if : on permute\n");
            Permuter(tabDistance, p, r);
        }
    }else { // sinon, on met le mivot apres ses elements plus petits
        Permuter(tabDistance, i+1, r);
    }


    /*printf("on affiche le tableau Part p:%d, r:%d, q:%f\n", p, r, x);
    for(int i=0; i < 10; i++){
        printf("%f\t", tabDistance[i].distance);
    }*/
    //printf("\n");
    return i+1;
}

void TriRapide(ElementTabDistance * tabDistance, int p, int r){ //appel la fonction Partition sur une certaine partie du tableau et trie le tableau recursivement
    int q;
    if (p < r){ //si le tableau a plus d'une case
        q = Partition(tabDistance, p, r);  //Partition rend le tableau avec les elements plus petit que le pivot a sa gauche et les elements plus grand a sa droite
        TriRapide(tabDistance, p, q-1);    //on rappel la fonction TriRapide mais pour la partie ou les elements sont plus petits que le pivot donc a gauche
        TriRapide(tabDistance, q+1, r);    //de meme a droite
    }
    
}

void TriTab(housing * accomodation, int TailleTab){ //trie rapide
    for(int numAppart=0; numAppart < TailleTab; numAppart++){ 
        TriRapide(accomodation[numAppart].tabDistance, 0, TailleTab);
    }
    
    /*printf("\non affiche le tableau Trie\n");
    for(int i=0; i < 5; i++){
        printf("%f\t", accomodation[0].tabDistance[i].distance);
    }*/
}


void PredirPrix(housing * accomodation, int TailleTab){ //calcule le prix estime du logement qui correspond a la moyenne des prix k premiers logements
    int k; //pour les k premiers logements a comparer
    int prix = 0;
    int estimation[TailleTab];
    int ligne;
    printf("\nA partir de combien de logement k voulez-vous estimer le prix de votre bien ?");
    scanf("%d", &k);

    if (k != 0 && k < TailleTab){

        for (int logement = 0; logement < TailleTab; logement++){ //on estime le prix pour tous les appartements
            for(int i = 1; i<=k; i++){ //on ne compte pas le premier logement qui est le logement dont on souhaite predire le prix
                ligne = accomodation[logement].tabDistance[i].numeroLigne; //acceder a la ligne du prochain elemenet le plus proche
                prix = prix + accomodation[ligne].price;
                //printf("i = %d, ligne %d, colonne %d : prix ligne %d, prix tot = %d\n", i, logement, ligne, accomodation[ligne].price, prix);
            }
            estimation[logement] = floor(prix/k);
            //printf("\n estimation %d : %d\n", logement, estimation[logement]);
            prix = 0;
        }

    }
    printf("prix estime = %d (ligne %d dans le fichier)\n", estimation[0], accomodation[0].numLigne);
    printf("prix du logement = %d\n", accomodation[0].price);
}
