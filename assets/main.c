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
void incrementar_mes(int *mm, int *yy); //função para incrementar o valor de um mês 
void decrementar_mes(int *mm, int *yy); //função para decrementar o valor de um mês
void print_mes(int mm, int yy); //not done yet
void print_current_month(int mm, int yy); //not done yet
char *dia_semana(int dia); //função para retornar o dia da semana de determinado dia
int dis_semana(int dd, int mm, int aa); //função para saber qual dia da semana é de acordo com a data do usuário

int main(){
    setlocale(LC_ALL, "Portuguese"); //desse modo podemos imprimir caracteres especiais da língua sem problemas
    int entrada = 0;
    char us = 'a';
    int ref = 0;

    while(ref==0){
        printf("Bem vindo ser vivo altamente evoluido ou nao\nDigite uma tecla para continuarmos\n");
        printf("1. Localizar um dia\n");
        printf("2. Exibir todos os dias do mes\n");
        printf("3. Adicionar lembrete(s)\n");
        printf("4. Sair do Programa\n");
        scanf("%d", &entrada);
        //printf("dia da semana: %s\n", dia_semana(10));
        switch(entrada){
            case 1:
                printf("Digite uma data (DD / MM / AAAA)\n");
                scanf("%d%d%d%*c", &data.dd, &data.mm, &data.yy);
                printf("dia: %d mes: %d e ano: %d\n", data.dd, data.mm, data.yy);
                int temp = dis_semana(data.dd, data.mm, data.yy);
                printf("Dia da semana correspondente: %s\n", dia_semana(temp));
                printf("Precione qualquer tecla para continuar\n");
                getchar();
                printf("\n");
                break;
            case 2:
                printf("Digite o mes e o ano (MM/AAAA)");
                scanf("%d%d%*c", &data.mm, &data.yy);
                /*a lógica aqui é ter uma função que imprime o mês e verificar se o user quer imprimir
                    mais meses - próx e anterior*/
                while(us!='e'){
                    
                }

            case 3:
            case 4: 
                ref = 1;
            default:
                printf("Insira uma entrada valida camarada\n");
        }
    }
    printf("\nObrigado por usar o nosso programa - by: Gabriel & Tallya\n");
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
    printf("\n");
    switch(mm){
        case 1: printf("Janeiro");
        case 2: printf("Fevereiro");
        case 3: printf("Marco");
        case 4: printf("Abril");
        case 5: printf("Maio");
        case 6: printf("Junho");
        case 7: printf("Julho");
        case 8: printf("Agosto");
        case 9: printf("Setembro");
        case 10: printf("Outubro");
        case 11: printf("Novembro");
        case 12: printf("Dezembro");
    }
    printf(" de %d\n", yy);
}