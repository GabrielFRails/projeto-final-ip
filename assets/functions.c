#include <ncurses.h>
#include "functions.h"
#include <time.h>

struct Data{
    int dd;
    int mm;
    int yy;
};

struct Data data;

struct Hora{
    int hh;
    int mm;
};

struct Hora hora;

struct Lembrete{
    struct Data dataL;
    struct Hora horaL;
    char nota[51];
};

struct Lembrete L;

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

void incrementar_ano(int *yy){
    (*yy)++;
    if(*yy < 1900) (*yy) = 1900;
}

void decrementar_ano(int *yy){
    (*yy)--;
    if(*yy > 2100) (*yy) = 2100;
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

void Add_note(){
    FILE *p;
    char nome_arq[8];
    int ano, ch=0;

    wclear(stdscr);
    mvaddstr(0,0,"Digite uma data e hora (DD/MM/AAAA HH:MM)");
    echo();
    curs_set(1);
    mvscanw(1,0, "%d/%d/%d %d:%d", &L.dataL.dd, &L.dataL.mm, &L.dataL.yy, &L.horaL.hh, &L.horaL.mm);
    curs_set(0);
    noecho();
    while(1){
        //verifica se a data e a hora são válidas
        if(verifica_data_hora_valida(L.dataL.dd, L.dataL.mm, L.dataL.yy, L.horaL.hh, L.horaL.mm)==0){
            wclear(stdscr);
            mvaddstr(0,0,"Data/hora inválida!");
            mvaddstr(1,0,"Pressione 't' para inserir data e hora novamente ou 'v' para voltar ao menu.");
            ch=0;
            while(ch!='t' && ch!='v') ch = getch();
            if(ch=='v') return;
            else{
                wclear(stdscr);
                mvprintw(0,0,"Insira uma data/hora válida (DD/MM/AAAA HH:MM): ");
                echo();
                curs_set(1);
                mvscanw(1,0,"%d/%d/%d %d:%d", &L.dataL.dd, &L.dataL.mm, &L.dataL.yy, &L.horaL.hh, &L.horaL.mm);
                curs_set(0);
                noecho();
            }
        } 
        //verifica se a data e a hora estão ou não no passado
        else if(compara_data_hora(L.dataL.dd, L.dataL.mm, L.dataL.yy, L.horaL.hh, L.horaL.mm)==0){
            wclear(stdscr);
            mvaddstr(0,0, "Não é possível criar lembrete em uma data/hora passada!");
            mvaddstr(1,0,"Pressione 't' para inserir data e hora novamente ou 'v' para voltar ao menu.");
            ch=0;
            while(ch!='t' && ch!='v') ch = getch();
            if(ch=='v') return;
            else{
                wclear(stdscr);
                mvprintw(0,0,"Insira uma data/hora válida (DD/MM/AAAA HH:MM): ");
                echo();
                curs_set(1);
                mvscanw(1,0,"%d/%d/%d %d:%d", &L.dataL.dd, &L.dataL.mm, &L.dataL.yy, &L.horaL.hh, &L.horaL.mm);
                curs_set(0);
                noecho();
            }
        }
        else break;
    }
    sprintf(nome_arq, "%d.dat", L.dataL.yy);
    p = fopen(nome_arq, "ab+");
    mvaddstr(2,0,"Digite a nota (máx. 50 caracteres): ");
    echo();
    curs_set(1);
    mvscanw(3,0, "%[^\n]", L.nota);
    curs_set(0);
    noecho();
    if(fwrite(&L, sizeof(L), 1, p)){
        mvaddstr(5,0, "Nota salva com sucesso!");
        fclose(p);
    } else mvaddstr(5,0, "Erro ao salvar a nota!");
    mvprintw(7,0,"Pressione qualquer tecla para voltar ao menu...");
    getch();
}

int check_note(int dd, int mm, int yy){
    FILE *p;
    char nome_arq[8];
    sprintf(nome_arq, "%d.dat", yy);
    p = fopen(nome_arq, "rb");
    if(p==NULL) mvaddstr(1,0, "Não foi possível abrir o arquivo");

    while(fread(&L,sizeof(L),1,p) == 1){
        if(L.dataL.dd == dd && L.dataL.mm == mm && L.dataL.yy == yy){
            fclose(p);
            return 1;
        }
    }
    fclose(p);
    return 0;
}

void imprime_note(int mm, int yy){
    FILE *p;
    int i = 0, achou = 0, contador = 0;
    char nome_arq[8];
    sprintf(nome_arq, "%d.dat", yy);
    p = fopen(nome_arq, "rb");

    wclear(stdscr);

    if(p==NULL){
        mvprintw(0,0,"Erro ao abrir o arquivo");
        return;
    }

    while(fread(&L, sizeof(L),1,p)==1){
        if(L.dataL.mm==mm) contador++;
    }

    int dias[contador];

    //mvprintw(1,0,"valor de contador: %d", contador);
    i = 0;
    fseek(p, 0, SEEK_SET);
    while(fread(&L, sizeof(L),1,p)==1){
        if(L.dataL.mm==mm){
            if(L.horaL.mm<10) mvprintw(0+i,0,"Nota %d, dia %d, hora %d:0%d: %s", i+1, L.dataL.dd, L.horaL.hh, L.horaL.mm, L.nota);
            else mvprintw(0+i,0,"Nota %d, dia %d, hora %d:%d: %s", i+1, L.dataL.dd, L.horaL.hh, L.horaL.mm, L.nota);
            achou = 1;
            i++;
        }
    }
    if(achou==0) mvprintw(0,0,"Esse mês não possui nenhum lembrete");

    fclose(p);
    mvprintw(i,0,"Pressione qualqual tecla para voltar ao menu...");
    getch();
}

int compara_data_hora(int dd, int mm, int yy, int hh, int min){
    time_t rawtime;
    struct tm * data_hora;
    time(&rawtime);
    data_hora = localtime(&rawtime);

    if(yy<data_hora->tm_year+1900) return 0;
    else if(yy>data_hora->tm_year+1900) return 1;
    else if(mm<data_hora->tm_mon+1) return 0;
    else if(mm>data_hora->tm_mon+1) return 1;
    else if(dd<data_hora->tm_mday) return 0;
    else if(dd>data_hora->tm_mday) return 1;

    if(yy==data_hora->tm_year+1900 && mm==data_hora->tm_mon+1 && dd==data_hora->tm_mday){
        if(hh<data_hora->tm_hour) return 0;
        else if(min<data_hora->tm_min) return 0;
        else return 1;
    }

    return 1;
}

int verifica_data_hora_valida(int dd, int mm, int yy, int hh, int min){
    if(numero_dias(mm,yy)==-1) return 0;
    if(dd<1 || dd>numero_dias(mm,yy)) return 0;
    if(mm<1 || mm>12) return 0;
    if(hh<0 || hh>23) return 0;
    if(min<0 || min>59) return 0;

    return 1;
}
