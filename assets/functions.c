#include <ncurses.h>
#include "functions.h"

int ano_bissexto(int ano){
    if(ano % 400 == 0 || (ano % 100 != 0 && ano % 4 == 0))
    return 1; // ano bissexto
    return 0; // ano não bissexto
}

int numero_dias(int mes, int ano){
    switch(mes){
        case 1: return 31;
        case 2: if(ano_bissexto(ano)==1) return 29;
            else return 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31; //é natal é natal ...
        default: return -1; //usuário inseriu um mês inválido 
    }
}

char *dia_semana(int dia){
    switch(dia){
        case 0: return "Domingo";
        case 1: return "Segunda";
        case 2: return "Terça";
        case 3: return "Quarta";
        case 4: return "Quinta";
        case 5: return "Sexta";
        case 6: return "Sábado";
        default: return "Dia da semana inválido parça";
        
    }
}

int dis_semana(int dd, int mm, int aa){
    int a, y, m, q, d;
    a = (14-mm) / 12;
    y = aa - a;
    m = mm + 12*a -2;
    q = dd + (31*m/12) + y + (y/4) - (y/100) + (y/400);
    d = q%7;

    return d;
}

void incrementar_mes(int *mm, int *yy){
    (*mm)++;
    if(*mm>12){
        (*yy)++;
        *mm -= 12;
    }
}

void decrementar_mes(int *mm, int *yy){
    (*mm)--;
    if(*mm<1){
        (*yy)--;
        *mm += 12;
    }
}

void print_current_month(int mm, int yy){
    int mes[6][7];
    int dia1, nDias, i, j, k;
    dia1 = dis_semana(1,mm,yy);
    nDias = numero_dias(mm,yy);
    for(i=0;i<6;i++){
        for(j=0;j<7;j++){
            mes[i][j]=0;
        }
    }
    k=1;
    i=0;
    j=dia1;
    while(k<=nDias){
        mes[i][j]=k;
        j++;
        k++;
        if(j==7){
            j=0;
            i++;
        }
    }
    printf("\n");
    mvprintw(0,0,"Mês: %d  Ano: %d", mm, yy);
    switch(mm){
        case 1: mvprintw(1,0,"Janeiro");
                break;
        case 2: mvprintw(1,0,"Fevereiro");
                break;
        case 3: mvprintw(1,0,"Março");
                break;
        case 4: mvprintw(1,0,"Abril");
                break;
        case 5: mvprintw(1,0,"Maio");
                break;
        case 6: mvprintw(1,0,"Junho");
                break;
        case 7: mvprintw(1,0,"Julho");
                break;
        case 8: mvprintw(1,0,"Agosto");
                break;
        case 9: mvprintw(1,0,"Setembro");
                break;
        case 10: mvprintw(1,0,"Outubro");
                break;
        case 11: mvprintw(1,0,"Novembro");
                break;
        case 12: mvprintw(1,0,"Dezembro");
                break;
    }
    mvprintw(2,0,"D  S  T  Q  Q  S  S");
    for(i=0;i<6;i++){
        for(j=0;j<7;j++){
            if(mes[i][j]==0) mvprintw(i+3,j*3,"x");
            else if(mes[i][j]<10) mvprintw(i+3,j*3,"%d", mes[i][j]);
            else mvprintw(i+3,j*3,"%d", mes[i][j]);
        }
    }
}