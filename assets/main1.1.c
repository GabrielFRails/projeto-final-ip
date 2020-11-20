#include <stdio.h>
#include <stdlib.h>
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
//void print_mes(int mm, int yy); not done yet
void print_current_month(int mm, int yy); //função que imprime o calendário do mês na tela
char *dia_semana(int dia); //função para retornar o dia da semana de determinado dia
int dis_semana(int dd, int mm, int aa); //função para saber qual dia da semana é de acordo com a data do usuário

int main(){
    setlocale(LC_ALL, "Portuguese"); //desse modo podemos imprimir caracteres especiais da língua sem problemas
    int entrada = 0;
    char us = 'a';
    char alteraMes = 'z';
    int ref = 0;

    while(ref==0){
        system("clear");
        printf("Bem vindo, ser vivo altamente evoluído (ou não) c:\nEscolha uma opção para continuarmos:\n");
        printf("1. Localizar um dia\n");
        printf("2. Exibir todos os dias do mês\n");
        printf("3. Adicionar lembrete(s)\n");
        printf("4. Visualizar lembrete(s)\n");
        printf("5. Sair do Programa\n");
        scanf("%d", &entrada);
    
        switch(entrada){
            case 1:
                printf("Digite uma data (DD MM AAAA)\n");
                scanf("%d%d%d%*c", &data.dd, &data.mm, &data.yy);
                system("clear");
                printf("Dia: %d Mês: %d e Ano: %d\n", data.dd, data.mm, data.yy);
                int temp = dis_semana(data.dd, data.mm, data.yy);
                printf("Dia da semana correspondente: %s\n", dia_semana(temp));
                printf("Pressione qualquer tecla para continuar\n");
                getchar();
                break;

            case 2:
                system("clear");
                printf("Digite o mês e o ano (MM AAAA)\n");
                scanf("%d%d", &data.mm, &data.yy);
                while(data.mm<1||data.mm>12){
                    system("clear");
                    printf("Entrada inválida!\nDigite o mês e o ano:\n");
                    scanf("%d%d", &data.mm, &data.yy);
                }
                system("clear");
                print_current_month(data.mm,data.yy);
                while(alteraMes!='s'){
                    printf("\n");
                    printf("Digite \"a\" para ver o mês anterior\n");
                    printf("Digite \"p\" para ver o próximo mês\n");
                    printf("Digite \"s\" para voltar ao menu principal\n");
                    scanf("%*c%c", &alteraMes);
                    switch(alteraMes){
                        case 'a':
                        case 'A': decrementar_mes(&data.mm, &data.yy);
                                  system("clear");
                                  print_current_month(data.mm, data.yy);
                                  break;
                        case 'p': 
                        case 'P': incrementar_mes(&data.mm, &data.yy);
                                  system("clear");
                                  print_current_month(data.mm, data.yy);
                                  break;
                        case 's':
                        case 'S': break;
                    }
                }
                break;

            case 3:
            case 4:
            case 5: 
                ref = 1;
        }
    }
    system("clear");
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
    printf("Mês: %d  Ano: %d\n", mm, yy);
    switch(mm){
        case 1: printf("Janeiro\n");
                break;
        case 2: printf("Fevereiro\n");
                break;
        case 3: printf("Março\n");
                break;
        case 4: printf("Abril\n");
                break;
        case 5: printf("Maio\n");
                break;
        case 6: printf("Junho\n");
                break;
        case 7: printf("Julho\n");
                break;
        case 8: printf("Agosto\n");
                break;
        case 9: printf("Setembro\n");
                break;
        case 10: printf("Outubro\n");
                break;
        case 11: printf("Novembro\n");
                break;
        case 12: printf("Dezembro\n");
                break;
    }
    printf("D  S  T  Q  Q  S  S\n");
    for(i=0;i<6;i++){
        for(j=0;j<7;j++){
            if(mes[i][j]==0) printf("x  ");
            else if(mes[i][j]<10) printf("%d  ", mes[i][j]);
            else printf("%d ", mes[i][j]);
        }
        printf("\n");
    }
}