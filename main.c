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
    for(int i=0;i<npt;i++)
        fscanf(p1_spectre," %lf %lf\n", lambda[i],intens[i]);
    fclose(p1_spectre);


    //2)---------------------------------------------------------------
    FILE *p1_spectre_lu= fopen("P1-spectre-lu.txt","w");
    if(p1_spectre_lu == NULL) exit(1);
    for(int i=0;i<npt;i++)
        fprintf(p1_spectre_lu,"%lf %lf\n",lambda[i],intens[i]);
    fclose(p1_spectre_lu);  


    //3)----------------------------------------------------------------

    int N=0;
    float intensf[NB_MAX];
    printf("Donnez la valeur de N : ");
    scanf("%d",&N);
    for(int i=0;i<npt;i++)  intensf[i]=0.0;
    float poids=1.0/(2.0*N + 1.0);
   
    int i=N,j=0;
    while( i < (npt-N)){
        intensf[i]=0;

        j=i-N;
        while( j <= (i+N)){
            intensf[i]=intensf[i] + poids*intens[j];
            j++;
        }
        i++;
    }
    //Complete reste (10 premiers et derniers)
    for(int i=0;i<N;i++){
        intensf[i]=intens[i];
        intensf[npt-N+i]=intens[npt-N+i];
    }

    //4)----------------------------------------------------------------
    FILE *p1_spectre_filtre= fopen("P1-spectre-filtre.txt","w");
    if(p1_spectre_filtre == NULL) exit(1);
    for(int i=0;i<npt;i++)
        fprintf(p1_spectre_filtre,"%lf %lf %f\n",lambda[i],intens[i],intensf[i]);
    fclose(p1_spectre_filtre); 



    //Detection des raies
    double seuil = 0.0, maxIntensity = intens[0];
    printf("Donnez un un seuil d'intensite : ");
    scanf("%lf",&seuil);
     for(int i=0;i<npt;i++){
         if(intens[i]>seuil){
             printf("%lf %lf\n",lambda[i],intens[i]);
             if(intens[i]>maxIntensity) maxIntensity = intens[i];
         }
     }
    //Bonus 
    for (int i = 1; i < npt; ++i) {
        double valeurIntensity = intens[i] , valeurLambda =  lambda[i];
        for (int j = i; j > 0 && intens[j-1] < valeurIntensity; j--)
        intens[j] = intens[j-1];
        intens[j] = valeurIntensity;
        lambda[j] = lambda[j-1];
        lambda[j] = valeurLambda;
    }

    FILE *p1_spectre_tri= fopen("P1-spectre-tri.txt","w");
    if(p1_spectre_tri == NULL) exit(1);
    for(int i=0;i<npt;i++)
        fprintf(p1_spectre_tri,"%lf %lf\n",lambda[i],intens[i]);
    fclose(p1_spectre_tri); 

    return 0;
}