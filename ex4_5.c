#include <__wctype.h>
//
// Created by João Valentim on 07/11/2020.
//

#include "ex1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include <conio.h>

int main_ex1(int argc, const char *argv[]){

    return 0;
}

void save_edificios_estudios_txt(EDIFICIO ed, char fn[]){

FILE * fp;
fp=fopen(fn,"w");
if(fp!=NULL){
        fprintf("fp,ID Edificio:%d\t",ed.id);
        fprintf("fp,Cordenadas:%d\t",ed.coordenadas);
        fprintf("fp,Morada:%c\t",ed.morada);

        ESTUDIO* es= ed.estudios;
    while(es!=NULL){
        fprintf(fp,"%d,%d,%d\n",es->id,es->num_clientes,es->num_agendas);
        ed=ed.next;//rever isto
    }
    }
    fclose(fp);
}



/*

 index = binarySearch(empresa->edificio->estudios, 0, empresa->edificio->

 void save_students_txt(CLASSSTUDENTS cs, char fn[]);{

    FILE * fp;
    fp=fopen(fn,"w");
    if(fp!=NULL){
        fprintf(fp,"class Name:%s\n",cs.name);
        fprintf(fp,"Number of students:%d\n",cs.nstudents);
        STUDENT * s=cs.pstudent;
        while(s!=NULL){
            fprintf(fp,"%s,%d,%.1f\n",s->pname,s->number,s->grade);
            s=s->pnert;
        }
        fclose(fp);
    }
}
*/
 void read_edificios_estudios_txt(EDIFICIO *pcs, char fn[]) {
    FILE *fp;
    fp = fopen(fn, "r");
    if (fp != NULL) {
        fscanf(fn,"%d\n",pcs->id);
        fscanf(fn,"%d",pcs->coordenadas);
        fscanf(fn,"%",pcs->)

    }
}