/**
* \file TP1_AlgoProc
* \author Melisande Clisson, Lucie Charrier et Ritchy Agnesa
* \brief TP1 Algo proc
* \version 0.1
* \date 03/10/2022
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h> 

typedef struct{

    int numeroLigne; //numero de la ligne du bien dans la fichier
    float distance; //distance avec un logement en fonction d'une ou plusieurs caracteristiques
    
}ElementTabDistance;

typedef struct{

    int numLigne; //numero de la ligne du bien dans la fichier
    int accommodates; // ???????????????????????????????????????????????????????????????????????????
    int bedrooms; //nb de chambres
    int bathrooms; //nb de salles de bain
    int beds; //nb de lits
    int price; //prix de la nuit
    int min_night; //minimum de nuits pour un sejour
    int max_night; //maximum de nuits pour un sejour
    int number_review; //float tabDistance[7918]nb de vue du logement
    ElementTabDistance tabDistance[7918]; //distance avec un logement en fonction d'une ou plusieurs caracteristiques
    
}housing;

housing * RangeFichierDansTableau(housing * accomodation, int TailleTab);
int RechercheDansTableau(housing * accomodation, int ligne, int colonne);
void CalculeDistance(housing * accomodation, int TailleTab);
void Randomiser(housing * accomodation, int TailleTab);
void Permuter(ElementTabDistance * tabDistance, int x, int y);
int Partition(ElementTabDistance * tabDistance, int p, int r);
void TriRapide(ElementTabDistance * tabDistance, int p, int r);
void TriTab(housing * accomodation, int TailleTab);
void PredirPrix(housing * accomodation, int TailleTab);
