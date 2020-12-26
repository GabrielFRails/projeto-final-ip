#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ncurses.h>
#include "functions.h"

int main(){
    setlocale(LC_ALL, "Portuguese"); //desse modo podemos imprimir caracteres especiais da língua sem problemas
    initscr();
    keypad(stdscr, TRUE);
    start_color();
    noecho();
    cbreak();
    curs_set(0);

    int entrada = 0;
    int alteraMes;
    int ref = 0;

    while(ref==0){
        wclear(stdscr);
        mvaddstr(0,0,"Bem vindo, ser vivo altamente evoluído (ou não) c:");
        mvaddstr(1,0,"Escolha uma opção e digite o número correspondente para continuar:");
        mvaddstr(2,0,"1. Localizar um dia (ver o dia da semana correspondente)");
        mvaddstr(3,0,"2. Exibir calendário de um mês");
        mvaddstr(4,0,"3. Adicionar lembrete(s)");
        mvaddstr(5,0,"4. Visualizar lembrete(s) de um dia");
        mvaddstr(6,0,"5. Visualizar lembrete(s) de um mês");
        mvaddstr(7,0,"6. Deletar um lembrete");
        mvaddstr(8,0,"7. Sair do programa");

        entrada = getch();
    
        switch(entrada){
            case '1':
                mvaddstr(9,0,"Digite uma data (DD/MM/AAAA)");
                echo();
                curs_set(1);
                mvscanw(10,0,"%d/%d/%d", &data.dd, &data.mm, &data.yy);
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
                mvaddstr(9,0,"Digite o mês e o ano (MM/AAAA)");
                echo();
                curs_set(1);
                mvscanw(10,0,"%d/%d", &data.mm, &data.yy);
                noecho();
                curs_set(0);
                while(data.mm<1||data.mm>12){
                    wclear(stdscr);
                    mvaddstr(0,0,"Entrada inválida! Digite o mês e o ano (MM/AAAA):");
                    echo();
                    curs_set(1);
                    mvscanw(1,0,"%d/%d", &data.mm, &data.yy);
                    noecho();
                    curs_set(0);
                }
                wclear(stdscr);
                print_current_month(data.mm,data.yy);
                alteraMes = 0;
                while(alteraMes!='s'){
                    mvaddstr(10,0,"Seta para a esquerda para ver o mês anterior");
                    mvaddstr(11,0,"Seta para a direita para ver o próximo mês");
                    mvaddstr(12,0,"Seta para cima para ver o próximo ano");
                    mvaddstr(13,0,"Seta para baixo para ver o ano anterior");
                    mvaddstr(14,0,"Digite \"v\" para ver as notas do mês");
                    mvaddstr(15,0,"Digite \"s\" para voltar ao menu principal");
                    attron(A_DIM);
                    mvaddstr(16,0,"(Os dias em negrito possuem lembretes)");
                    attroff(A_DIM);
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
                        case KEY_UP: incrementar_ano(&data.yy);
                            wclear(stdscr);
                            print_current_month(data.mm, data.yy);
                             break;
                        case KEY_DOWN: decrementar_ano(&data.yy);
                            wclear(stdscr);
                            print_current_month(data.mm, data.yy);
                             break;
                        case 'v': wclear(stdscr);
                                imprime_notes_mes(data.mm, data.yy);
                                alteraMes = 's';
                                break;
                        case 's':          
                        case 'S': alteraMes='s';
                                  break;
                    }
                }
                break;

            case '3': Add_note();
                      break;
            case '4':
                wclear(stdscr);
                mvaddstr(0,0,"Digite uma data (DD/MM/AAAA)");
                echo();
                curs_set(1);
                mvscanw(1,0, "%d/%d/%d", &data.dd, &data.mm, &data.yy);
                noecho();
                curs_set(0);
                imprime_notes_dia(data.dd, data.mm, data.yy);
                break;
            case '5': 
                wclear(stdscr);
                mvaddstr(0,0,"Digite um mês e ano (MM/AAAA)");
                echo();
                curs_set(1);
                mvscanw(1,0, "%d/%d", &data.mm, &data.yy);
                noecho();
                curs_set(0);
                imprime_notes_mes(data.mm, data.yy);
                break;
            case '6':
                wclear(stdscr);
                mvaddstr(0,0,"Digite a data e hora do lembrete que deseja deletar (DD/MM/AAAA HH:MM)");
                echo();
                curs_set(1);
                mvscanw(1,0, "%d/%d/%d %d:%d", &data.dd, &data.mm, &data.yy, &hora.hh, &hora.mm);
                noecho();
                curs_set(0);
                deleta_lembrete(data.dd, data.mm, data.yy, hora.hh, hora.mm);
                break;
            case '7':
                ref = 1;
                break;
        }
    }
    wclear(stdscr);
    mvaddstr(0,0,"Obrigado por usar o nosso programa - by: Gabriel & Tallya");
    mvaddstr(2,0,"Pressione uma tecla para encerrar");
    getch();
    endwin();
    return 0;
}
