#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_MAX 10000


int main(){
    int npt=0;
    double lambda[NB_MAX];
    double intens[NB_MAX];

    //1)----------------------------------------------------------------
    FILE *p1_spectre= fopen("P1-spectre.txt","r");
    if(p1_spectre == NULL) exit(1);

    fscanf(p1_spectre,"%d\n",&npt);
    printf("nombre npt: %d\n",npt);

    double longueurOnde=0.0 , intensiteRelative=0.0;
    for(int i=0;i<npt;i++){
        fscanf(p1_spectre," %lf %lf\n",&longueurOnde,&intensiteRelative);
        lambda[i]=longueurOnde;
        intens[i]=intensiteRelative;
    }
    printf("Les donnees lues: \n");
    for(int i=0;i<npt;i++){
        printf(" %lf %lf\n",lambda[i],intens[i]);
    }
    fclose(p1_spectre);


    //2)---------------------------------------------------------------
    FILE *p1_spectre_lu= fopen("P1-spectre-lu.txt","w");
    if(p1_spectre_lu == NULL) exit(1);
    for(int i=0;i<npt;i++)
        fprintf(p1_spectre_lu," %lf %lf\n",lambda[i],intens[i]);
    fclose(p1_spectre_lu);  
    //3)----------------------------------------------------------------




    return 0;
}