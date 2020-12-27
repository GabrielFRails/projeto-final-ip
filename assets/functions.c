#include <ncurses.h>
#include "functions.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

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
            if(check_note(mes[i][j], mm, yy)==1) attron(A_BOLD);
            if(mes[i][j]==0) mvprintw(i+3,j*3,"x");
            else if(mes[i][j]<10) mvprintw(i+3,j*3,"%d", mes[i][j]);
            else mvprintw(i+3,j*3,"%d", mes[i][j]);
            attroff(A_BOLD);
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
    if(p==NULL) return 0;

    while(fread(&L,sizeof(L),1,p) == 1){
        if(L.dataL.dd == dd && L.dataL.mm == mm){
            fclose(p);
            return 1;
        }
    }
    fclose(p);
    return 0;
}

int check_noteH(int dd, int mm, int yy, int hh, int min){
    FILE *p;
    char nome_arq[8];
    sprintf(nome_arq, "%d.dat", yy);
    p = fopen(nome_arq, "rb");
    if(p==NULL) return 0;

    while(fread(&L,sizeof(L),1,p) == 1){
        if(L.dataL.dd == dd && L.dataL.mm == mm && L.horaL.hh == hh && L.horaL.mm == min){
            fclose(p);
            return 1;
        }
    }
    fclose(p);
    return 0;
}

int verica_maiorDia(Lembrete * a, int i, int j){
    if(a[i].dataL.dd > a[j].dataL.dd) return 1; //caso o dia da posição i for maior que o da posição j
    else if(a[i].dataL.dd == a[j].dataL.dd){ //verifica no caso a maior hora
        if(a[i].horaL.hh > a[j].horaL.hh) return 1;
        else if(a[i].horaL.hh == a[j].horaL.hh){
            if(a[i].horaL.mm > a[j].horaL.mm) return 1;
            else return 0;
        } else return 0;
    }else return 0; //caso contrário
    
}

void swap_lembretes(Lembrete* a, int i, int j){
    Lembrete *aux = (Lembrete *) malloc(sizeof(Lembrete));

    aux[0] = a[i];
    a[i] = a[j];
    a[j] = aux[0];
    free(aux);
}

void imprime_notes_mes(int mm, int yy){
    FILE *p;
    int i = 1, j, achou = 0, cont = 0;
    Lembrete * lembrete = (Lembrete*) malloc(sizeof(Lembrete)), *ltemp;
    char nome_arq[8];
    sprintf(nome_arq, "%d.dat", yy);
    p = fopen(nome_arq, "rb");

    wclear(stdscr);

    if(p==NULL){
        mvprintw(0,0,"Erro ao abrir o arquivo");
        return;
    }
    int k = 1;
    while(fread(&L, sizeof(L), 1, p) == 1){
        if(L.dataL.yy == yy && L.dataL.mm == mm){
            lembrete[k-1].dataL.dd = L.dataL.dd;
            lembrete[k-1].dataL.mm = L.dataL.mm;
            lembrete[k-1].dataL.yy = L.dataL.yy;
            lembrete[k-1].horaL.hh = L.horaL.hh;
            lembrete[k-1].horaL.mm = L.horaL.mm;
            memcpy(lembrete[k-1].nota, L.nota, sizeof(L.nota)+1);
            k++;
            ltemp = (Lembrete*) realloc(lembrete, sizeof(Lembrete)*k);
            lembrete = ltemp;
            achou = 1;
        }
    }

    for(i=0; i<k-1; i++){
        for(j=i+1; j<k-1; j++){
            if(verica_maiorDia(lembrete, i, j) == 1) swap_lembretes(lembrete, i, j);
        }
    }
    
    for(i=0; i<k-1; i++){
        if(lembrete[i].horaL.mm<10) mvprintw(0+i,0,"Nota %d, dia %d, hora %d:0%d: %s", i+1, 
        lembrete[i].dataL.dd, lembrete[i].horaL.hh, lembrete[i].horaL.mm, lembrete[i].nota);
        else mvprintw(0+i,0,"Nota %d, dia %d, hora %d:%d: %s", i+1, 
        lembrete[i].dataL.dd, lembrete[i].horaL.hh, lembrete[i].horaL.mm, lembrete[i].nota);
    }

    if(achou==0){
        mvprintw(0,0,"Esse mês não possui nenhum lembrete");
        i = 1;
    }

    fclose(p);
    free(lembrete);
    mvprintw(i,0,"Pressione qualqual tecla para voltar ao menu...");
    getch();
}

void imprime_notes_dia(int dd, int mm, int yy){
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

    fseek(p, 0, SEEK_SET);
    while(fread(&L, sizeof(L),1,p)==1){
        if(L.dataL.dd==dd && L.dataL.mm==mm){
            if(L.horaL.mm<10) mvprintw(0+i,0,"Nota %d, dia %d, hora %d:0%d: %s", i+1, L.dataL.dd, L.horaL.hh, L.horaL.mm, L.nota);
            else mvprintw(0+i,0,"Nota %d, dia %d, hora %d:%d: %s", i+1, L.dataL.dd, L.horaL.hh, L.horaL.mm, L.nota);
            achou = 1;
            i++;
        }
    }
    if(achou==0) {
        mvprintw(0,0,"Esse dia não possui nenhum lembrete");
        i = 1;
    }

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

void deleta_lembrete(int dd, int mm, int yy, int hh, int min){
    FILE * arq, * temp;
    char nome_arq[8];
    Lembrete lemb;
    sprintf(nome_arq, "%d.dat", yy);
    arq = fopen(nome_arq, "rb");

    if(arq == NULL){
        mvaddstr(3,0, "Erro ao acessar arquivo!");
        mvaddstr(4,0, "Pressione qualquer tecla para voltar ao menu");
        getch();
        return;
    }

    if(check_noteH(dd, mm, yy, hh, min)==0){
        mvaddstr(3,0,"Não existe nenhum lembrete na data e hora inseridas!");
        mvaddstr(4,0, "Pressione qualquer tecla para voltar ao menu");
        getch();
        fclose(arq);
        return;
    }

    temp = fopen("temp.dat", "wb");

    while(fread(&lemb, sizeof(lemb), 1, arq) == 1){
        if(lemb.dataL.dd == dd && lemb.dataL.mm == mm && lemb.horaL.hh == hh && lemb.horaL.mm == min) mvaddstr(3,0, "Nota deletada com sucesso!");
        else fwrite(&lemb, sizeof(lemb), 1, temp);
    }

    fclose(arq);
    fclose(temp);
    remove(nome_arq);
    rename("temp.dat", nome_arq);
    mvaddstr(4,0, "Pressione qualquer tecla para voltar ao menu");
    getch();
}

int veirfy_User(char *user){
    FILE *p = fopen("users.dat", "rb");

    while(fread(&U, sizeof(U), 1, p) == 1){
        if(strcmp(U.user, user) == 0) {
            fclose(p);
            return 1; ////usuário já cadastrado;
        } 
    }

    fclose(p);
    return 0; //caso não tenha um usuário já cadastrado com esse nome;
}

void cadastra_User(char *p, char *u){
    FILE *f = fopen("users.dat", "wb");
    wclear(stdscr);
    if(veirfy_User(p) == 1) {
        mvaddstr(0,1, "Usuário já cadastrado");
        fclose(f);
        return;
    } else{
        if(fwrite(&U, sizeof(U), 1, f)){
            mvaddstr(0,0, "Usuário cadastrado com sucesso!");
        }
    }
    fclose(f);
    mvaddstr(1,0, "Pressione qualquer tecla para prosseguir");
    getch();
}

int login(char *p, char *u){
    FILE *f = fopen("users.dat", "rb");
    if(f == NULL) return -1;

    while(fread(&U, sizeof(U), 1, f) == 1){
        if(strcmp(U.user, u) == 0 && strcmp(U.password, p) == 1){
            fclose(f);
            return 1; //login com sucesso
        }
    }
    fclose(f);
    return 0; //não foi possível fazer login
}

int letras(char r){
    if((r >= 'a' && r <= 'z') || (r >= 'A' && r <= 'Z')) return 1;
    else return 0;
}

void criptografar_password(char *p){
    int i, size = strlen(p);
    char tmp;

    for(i=0; p[i] != '\0'; i++)
        if(letras(p[i])==1) p[i] = (int) p[i]+3;
    
    for(i=0; i<size; i++){
        tmp = p[i];
        p[i] = p[size-i-1];
        p[size-i-1] = tmp;
    }

    for(i=size/2; p[i] != '\0'; i++)
        p[i] = (int) p[i]-1;

}