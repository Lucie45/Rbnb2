#include "AppartFonctions.c"

int main (int argc, char* argv[]){
    printf("\nDEBUT\n");
    srand(time(NULL));
    int TailleTab = 7918; //taille du tableau est aussi le nombre de lignes du fichier
    housing * accomodation = (housing*) malloc(TailleTab * sizeof(housing)); //tableau dynamique


    accomodation = RangeFichierDansTableau(accomodation, TailleTab);
    CalculeDistance(accomodation, TailleTab); //met a jour les tableaux de distance de chaque element
    

    Randomiser(accomodation, TailleTab);
    TriTab(accomodation, TailleTab);
    /*for (int logement = 0; logement < 5; logement++){
        printf("numLigne %d : distance %f\n", accomodation[0].tabDistance[logement].numeroLigne, accomodation[0].tabDistance[logement].distance);
    }*/

    PredirPrix(accomodation, TailleTab);

    printf("\nFIN\n\n");
    return 0;
}