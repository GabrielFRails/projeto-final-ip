/* 
* Este aplicativo se encaixa na área de organização pessoal,
* partindo da premissa de um calendário eletrônico no qual é possível
* adicionar lembretes, visualizá-los e deletá-los.
*
* O aplicativo conta também com um sistema de usuário e senha,
* foi completamente desenvolvido em C, possui uma biblioteca de funções
* própria, a "functions.h" e utiliza a biblioteca <ncurses.h> para
* construção da interface gráfica
*
* Este programa foi desenvolvido por Gabriel Freitas e Tallya Barbosa
* como trabalho final da disciplina de Introdução à Programação do curso
* de Ciência da Computação da Universidade Federal de Goiás
*
* Modificado pela última vez em 05/01/2021 por Tallya Barbosa
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ncurses.h>
#include <string.h>
#include "functions.h"

int main(){
    setlocale(LC_ALL, "Portuguese"); //desse modo podemos imprimir caracteres especiais da língua sem problemas
    initscr();
    keypad(stdscr, TRUE); 
    start_color();
    noecho();
    cbreak();
    curs_set(0);

    WINDOW * mainWin, * calendar, * menu, * notes; //janelas utilizadas durante a execução do programa
    int entradaMain = 0, entradaLogin; //variáveis que coletam as opções escolhidas pelo usuário nos menus
    int alteraMes;
    int refMain = 0, refLogin = 0; //flags que encerram o módulo de login e o módulo principal
    char senha[12];

    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);

    while(refLogin==0){ //módulo de login
        entradaLogin = 0;
        wclear(stdscr);
        refresh();
        mainWin = newwin(LINES, COLS, 0, 0);
        box(mainWin,0,0);
        wrefresh(mainWin);
        wattron(mainWin, COLOR_PAIR(2));
        mvwaddstr(mainWin,1,1,"Bem vindo, selecione uma opção");
        wattroff(mainWin, COLOR_PAIR(2));
        mvwaddstr(mainWin,3,1,"1.Fazer Login");
        wattron(mainWin, COLOR_PAIR(1));
        mvwaddstr(mainWin,4,1,"2.Cadastrar usuário");
        wattroff(mainWin, COLOR_PAIR(1));
        wrefresh(mainWin);
        entradaLogin = getch();
        switch(entradaLogin){
            case '1': //fazer login   
                t = calloc(1, sizeof(User));
                mvwaddstr(mainWin,6,1,"Digite usuário e senha (máx. 10 caracteres, sem espaços)");
                echo();
                mvwaddstr(mainWin,7,1, "Usuário: ");
                curs_set(1);
                mvwscanw(mainWin,7,11,"%s", t->user);
                mvwaddstr(mainWin,8,1,"Senha: ");
                mvwscanw(mainWin,8,8,"%s", t->password);
                noecho();
                strcpy(senha, t->password);
                criptografar_password(t->password);
                curs_set(0);
                if(login(t)==1){ //login bem-sucedido
                    wattron(mainWin, COLOR_PAIR(1));
                    mvwaddstr(mainWin,10,1,"Login bem-sucedido, pressione qualquer tecla para continuar.");
                    wattroff(mainWin, COLOR_PAIR(1));
                    wrefresh(mainWin);
                    getch();
                    refLogin = 1;
                }else{ //login mal-sucedido
                    wattron(mainWin, COLOR_PAIR(1));
                    /* 
                    * a mensagem de erro abaixo é apresentada tanto em caso de falha na abertura/leitura do arquivo
                    * quanto em caso de usuário/senha incorretos ou inexistentes
                    */
                    mvwaddstr(mainWin,10,1,"Falha no login, pressione qualquer tecla para voltar.");
                    wattroff(mainWin, COLOR_PAIR(1));
                    wrefresh(mainWin);
                    getch();
                }
                free(t);
                delwin(mainWin);
                break;
            case '2': //cadastrar novo usuário
                t = calloc(1, sizeof(User));
                mvwaddstr(mainWin,6,1,"Digite usuário e senha (máx. 10 caracteres, sem espaços)");
                echo();
                mvwaddstr(mainWin,7,1, "Usuário: ");
                curs_set(1);
                mvwscanw(mainWin,7,11,"%s", t->user);
                mvwaddstr(mainWin,8,1,"Senha: ");
                mvwscanw(mainWin,8,8,"%s", t->password);
                noecho();
                curs_set(0);
                cadastra_User(mainWin, t);
                free(t);
                delwin(mainWin);
                break;
        }
    }

    while(refMain==0){ //módulo principal
        //menu principal
        wclear(stdscr);
        refresh();
        mainWin = newwin(LINES, COLS, 0, 0);
        box(mainWin,0,0);
        wattron(mainWin, COLOR_PAIR(2));
        mvwaddstr(mainWin,1,1,"Bem vindo, ser vivo altamente evoluído (ou não) c:");
        wattroff(mainWin, COLOR_PAIR(2));
        mvwaddstr(mainWin,3,1,"Escolha uma opção e digite o número correspondente para continuar:");
        mvwaddstr(mainWin,4,1,"1. Localizar um dia (ver o dia da semana correspondente)");
        wattron(mainWin, COLOR_PAIR(1));
        mvwaddstr(mainWin,5,1,"2. Exibir calendário de um mês");
        wattroff(mainWin, COLOR_PAIR(1));
        mvwaddstr(mainWin,6,1,"3. Adicionar lembrete(s)");
        wattron(mainWin, COLOR_PAIR(1));
        mvwaddstr(mainWin,7,1,"4. Visualizar lembrete(s) de um dia");
        wattroff(mainWin, COLOR_PAIR(1));
        mvwaddstr(mainWin,8,1,"5. Visualizar lembrete(s) de um mês");
        wattron(mainWin, COLOR_PAIR(1));
        mvwaddstr(mainWin,9,1,"6. Deletar um lembrete");
        wattroff(mainWin, COLOR_PAIR(1));
        mvwaddstr(mainWin,10,1,"7. Sair do programa");
        mvwprintw(mainWin,14,1, "Usuário logado: %s", U.user);
        wrefresh(mainWin);

        entradaMain = getch();
    
        switch(entradaMain){
            case '1': //localizar um dia
                mvwaddstr(mainWin,11,1,"Digite uma data (DD/MM/AAAA)");
                echo();
                curs_set(1);
                mvwscanw(mainWin,12,1,"%d/%d/%d", &data.dd, &data.mm, &data.yy);
                noecho();
                curs_set(0);
                wclear(mainWin);
                wattron(mainWin, COLOR_PAIR(1));
                box(mainWin,0,0);
                wattroff(mainWin, COLOR_PAIR(1));
                mvwprintw(mainWin,1,1,"Dia: %d Mês: %d e Ano: %d", data.dd, data.mm, data.yy);
                int temp = dis_semana(data.dd, data.mm, data.yy);
                mvwprintw(mainWin,2,1,"Dia da semana correspondente: %s", dia_semana(temp));
                mvwaddstr(mainWin,4,1,"Pressione qualquer tecla para continuar");
                wrefresh(mainWin);
                getch();
                break;

            case '2': //exibir o calendário de um mês
                mvwaddstr(mainWin,11,1,"Digite o mês e o ano (MM/AAAA)");
                echo();
                curs_set(1);
                mvwscanw(mainWin,12,1,"%d/%d", &data.mm, &data.yy);
                noecho();
                curs_set(0);
                while(data.mm<1||data.mm>12){ //verifica se a entrada fornecida pelo usuário é válida
                    wclear(mainWin);
                    mvwaddstr(mainWin,1,1,"Entrada inválida! Digite o mês e o ano (MM/AAAA):");
                    echo();
                    curs_set(1);
                    mvwscanw(mainWin,2,1,"%d/%d", &data.mm, &data.yy);
                    noecho();
                    curs_set(0);
                }
                wclear(stdscr);
                refresh();
                delwin(mainWin);
                //divisão da tela em 3 janelas que comportarão o conteúdo da exibição do calendário, do menu e dos lembretes
                calendar = newwin(11,26,0,0);
                box(calendar,0,0);
                wrefresh(calendar);
                menu = newwin(11,COLS-27,0,27);
                box(menu,0,0);
                wrefresh(menu);
                notes = newwin(LINES-11,COLS,11,0);
                wattron(notes, COLOR_PAIR(1));
                box(notes,0,0);
                wattroff(notes, COLOR_PAIR(1));
                mvwaddstr(notes,1,1,"As notas aparecerão aqui.");
                wrefresh(notes);
                print_current_month(calendar,data.mm,data.yy);
                alteraMes = 0;
                while(alteraMes!='s'){ //mantém o programa na exibição do calendário até que o usuário escolha sair dela
                    //conteúdo da janela menu
                    mvwaddstr(menu,1,1,"Seta para a esquerda para ver o mês anterior");
                    wattron(menu, COLOR_PAIR(1));
                    mvwaddstr(menu,2,1,"Seta para a direita para ver o próximo mês");
                    wattroff(menu, COLOR_PAIR(1));
                    mvwaddstr(menu,3,1,"Seta para cima para ver o próximo ano");
                    wattron(menu, COLOR_PAIR(1));
                    mvwaddstr(menu,4,1,"Seta para baixo para ver o ano anterior");
                    wattroff(menu, COLOR_PAIR(1));
                    mvwaddstr(menu,5,1,"Digite \"v\" para ver as notas do mês");
                    wattron(menu, COLOR_PAIR(1));
                    mvwaddstr(menu,6,1,"Digite \"s\" para voltar ao menu principal");
                    wattroff(menu, COLOR_PAIR(1));
                    wattron(menu, A_DIM);
                    mvwaddstr(menu,8,1,"(Os dias em destaque possuem lembretes)");
                    wattroff(menu, A_DIM);
                    if(alteraMes == 0) wrefresh(menu); //atualiza o conteúdo da janela menu apenas na primeira exibição
                    alteraMes = getch();
                    switch(alteraMes){
                        //exibe o mês anterior (KEY_LEFT == seta esquerda)
                        case KEY_LEFT: decrementar_mes(&data.mm, &data.yy);
                             wclear(calendar);
                             box(calendar,0,0);
                             print_current_month(calendar, data.mm, data.yy);
                             wclear(notes);
                             wattron(notes, COLOR_PAIR(1));
                             box(notes,0,0);
                             wattroff(notes, COLOR_PAIR(1));
                             mvwaddstr(notes,1,1,"As notas aparecerão aqui.");
                             wrefresh(notes);
                             break;
                        //exibe o mês seguinte (KEY_RIGHT == seta direita)
                        case KEY_RIGHT: incrementar_mes(&data.mm, &data.yy);
                             wclear(calendar);
                             box(calendar,0,0);
                             print_current_month(calendar, data.mm, data.yy);
                             wclear(notes);
                             wattron(notes, COLOR_PAIR(1));
                             box(notes,0,0);
                             wattroff(notes, COLOR_PAIR(1));
                             mvwaddstr(notes,1,1,"As notas aparecerão aqui.");
                             wrefresh(notes);
                             break;
                        //exibe o mesmo mês do ano seguinte (KEY_UP == seta para cima)
                        case KEY_UP: incrementar_ano(&data.yy);
                             wclear(calendar);
                             box(calendar,0,0);
                             print_current_month(calendar, data.mm, data.yy);
                             wclear(notes);
                             wattron(notes, COLOR_PAIR(1));
                             box(notes,0,0);
                             wattroff(notes, COLOR_PAIR(1));
                             mvwaddstr(notes,1,1,"As notas aparecerão aqui.");
                             wrefresh(notes);
                             break;
                        //exibe o mesmo mês do ano anterior (KEY_DOWN == seta para baixo)
                        case KEY_DOWN: decrementar_ano(&data.yy);
                             wclear(calendar);
                             box(calendar,0,0);
                             print_current_month(calendar, data.mm, data.yy);
                             wclear(notes);
                             wattron(notes, COLOR_PAIR(1));
                             box(notes,0,0);
                             wattroff(notes, COLOR_PAIR(1));
                             mvwaddstr(notes,1,1,"As notas aparecerão aqui.");
                             wrefresh(notes);
                             break;
                        //exibe os lembretes do mês em exibição na janela "notes"
                        case 'V':
                        case 'v': wclear(notes);
                             wattron(notes, COLOR_PAIR(1));
                             box(notes,0,0);
                             wattroff(notes, COLOR_PAIR(1));
                             imprime_notes_mes(notes, data.mm, data.yy, 0);
                             break;
                        //retorna ao menu principal
                        case 's':          
                        case 'S': alteraMes='s';
                             delwin(calendar);
                             delwin(menu);
                             delwin(notes);
                             break;
                    }
                }
                break;
            //adicionar um lembrete
            case '3': Add_note(mainWin);
                      break;
            //visualizar lembretes de um único dia
            case '4':
                wclear(mainWin);
                wattron(mainWin, COLOR_PAIR(1));
                box(mainWin,0,0);
                wattroff(mainWin, COLOR_PAIR(1));
                wrefresh(mainWin);
                mvwaddstr(mainWin,1,1,"Digite uma data (DD/MM/AAAA)");
                echo();
                curs_set(1);
                mvwscanw(mainWin,2,1, "%d/%d/%d", &data.dd, &data.mm, &data.yy);
                noecho();
                curs_set(0);
                imprime_notes_dia(mainWin, data.dd, data.mm, data.yy);
                break;
            //visualizar lembretes de um mês
            case '5': 
                wclear(mainWin);
                wattron(mainWin, COLOR_PAIR(1));
                box(mainWin,0,0);
                wattroff(mainWin, COLOR_PAIR(1));
                wrefresh(mainWin);
                mvwaddstr(mainWin,1,1,"Digite um mês e ano (MM/AAAA)");
                echo();
                curs_set(1);
                mvwscanw(mainWin,2,1, "%d/%d", &data.mm, &data.yy);
                noecho();
                curs_set(0);
                wclear(mainWin);
                wattron(mainWin, COLOR_PAIR(1));
                box(mainWin,0,0);
                wattroff(mainWin, COLOR_PAIR(1));
                wrefresh(mainWin);
                imprime_notes_mes(mainWin, data.mm, data.yy, 1);
                break;
            //deletar um lembrete
            case '6':
                wclear(mainWin);
                wattron(mainWin, COLOR_PAIR(1));
                box(mainWin,0,0);
                wattroff(mainWin, COLOR_PAIR(1));
                wrefresh(mainWin);
                mvwaddstr(mainWin,1,1,"Digite a data e hora do lembrete que deseja deletar (DD/MM/AAAA HH:MM)");
                echo();
                curs_set(1);
                mvwscanw(mainWin,2,1, "%d/%d/%d %d:%d", &data.dd, &data.mm, &data.yy, &hora.hh, &hora.mm);
                noecho();
                curs_set(0);
                deleta_lembrete(mainWin, data.dd, data.mm, data.yy, hora.hh, hora.mm);
                break;
            //encerrar o programa
            case '7':
                refMain = 1;
                break;
        }
    }
    wclear(mainWin);
    wattron(mainWin, COLOR_PAIR(1));
    box(mainWin,0,0);
    wattroff(mainWin, COLOR_PAIR(1));
    wrefresh(mainWin);
    mvwaddstr(mainWin,1,1,"Obrigado por usar o nosso programa - by: Gabriel & Tallya");
    mvwaddstr(mainWin,3,1,"Pressione uma tecla para encerrar");
    wrefresh(mainWin);
    getch();
    delwin(mainWin);
    endwin();
    return 0;
}
