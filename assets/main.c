#include <stdio.h>
//#include <conio.h>
//#include <windows.h>
#include <locale.h>

struct Data{
    int dd;
    int mm;
    int yy;
};
struct Data data;

struct Lembrete{
    int dd;
    int mm;
    char nota[51];
};

struct Lembrete lembrete;

int ano_bissexto(int ano); //função para verificar se um ano é bissexto ou não
int numero_dias(int mes, int ano); //função para ver quantos dias tem um mês
void incrementar_mes(int *mm, int *yy); 
void decrementar_mes(int *mm, int *yy);
char *dia_semana(int dia);

int main(){
    setlocale(LC_ALL, " "); //desse modo podemos imprimir caracteres especiais da língua sem problemas
    int entrada = 0;
    char us = 'a';

    //while(1){
        printf("Bem vindo ser vivo altamente evoluído ou não\nDigite uma tecla para continuarmos\n");
        printf("1. Localizar um dia\n");
        printf("2. Exibir todos os dias do mês\n");
        printf("3. Adicionar lembrete\n");
        printf("4. Sair do Programa\n");
        //scanf("%d", &entrada);
        printf("dia da semana: %s\n", dia_semana(0));
/*        switch(entrada){
            case 1:
            case 2:
            case 3:
            case 4: 
                exit(0);
        }
    }*/
    return 0;
}

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