#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ncurses.h>

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
    initscr();
    keypad(stdscr, TRUE);
    start_color();
    noecho();
    cbreak();
    curs_set(0);

    int entrada = 0;
    char us = 'a';
    int alteraMes = 0;
    int ref = 0, i = 0;

    while(ref==0){
        wclear(stdscr);
        mvaddstr(0,0,"Bem vindo, ser vivo altamente evoluído (ou não) c:");
        mvaddstr(1,0,"Escolha uma opção para continuarmos:");
        mvaddstr(2,0,"1. Localizar um dia");
        mvaddstr(3,0,"2. Exibir todos os dias do mês");
        mvaddstr(4,0,"3. Adicionar lembrete(s)");
        mvaddstr(5,0,"4. Visualizar lembrete(s)");
        mvaddstr(6,0,"5. Sair do Programa");
        entrada = getch();
    
        switch(entrada){
            case '1':
                mvaddstr(8,0,"Digite uma data (DD MM AAAA)");
                echo();
                curs_set(1);
                mvscanw(9,0,"%d %d %d", &data.dd, &data.mm, &data.yy);
                noecho();
                curs_set(0);
                wclear(stdscr);
                mvprintw(0,0,"Dia: %d Mês: %d e Ano: %d", data.dd, data.mm, data.yy);
                int temp = dis_semana(data.dd, data.mm, data.yy);
                mvprintw(1,0,"Dia da semana correspondente: %s", dia_semana(temp));
                mvaddstr(3,0,"Pressione qualquer tecla para continuar");
                getch();
                break;

            case '2':
                mvaddstr(8,0,"Digite o mês e o ano (MM AAAA)");
                echo();
                curs_set(1);
                mvscanw(9,0,"%d%d", &data.mm, &data.yy);
                noecho();
                curs_set(0);
                while(data.mm<1||data.mm>12){
                    wclear(stdscr);
                    mvaddstr(0,0,"Entrada inválida! Digite o mês e o ano:");
                    echo();
                    curs_set(1);
                    mvscanw(1,0,"%d%d", &data.mm, &data.yy);
                    noecho();
                    curs_set(0);
                }
                wclear(stdscr);
                print_current_month(data.mm,data.yy);
                while(alteraMes!='s'){
                    printf("\n");
                    mvaddstr(10,0,"Seta para a esquerda para ver o mês anterior");
                    mvaddstr(11,0,"Seta para a direita para ver o próximo mês");
                    mvaddstr(12,0,"Digite \"s\" para voltar ao menu principal");
                    alteraMes = getch();
                    switch(alteraMes){
                        case KEY_LEFT: decrementar_mes(&data.mm, &data.yy);
                                  wclear(stdscr);
                                  print_current_month(data.mm, data.yy);
                                  break;
                        case KEY_RIGHT: incrementar_mes(&data.mm, &data.yy);
                                  wclear(stdscr);
                                  print_current_month(data.mm, data.yy);
                                  break;
                        case 's':          
                        case 'S': alteraMes='s';
                                  break;
                    }
                }
                break;

            case '3':
            case '4':
            case '5': 
                ref = 1;
        }
    }
    system("clear");
    mvaddstr(0,0,"Obrigado por usar o nosso programa - by: Gabriel & Tallya");
    mvaddstr(2,0,"Pressione uma tecla para encerrar");
    getch();
    endwin();
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
