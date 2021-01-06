#include <ncurses.h>
#include "functions.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

/*
* 1º bloco: funções que coletam/retornam valores necessários
* para a execução de outras funções e/ou verificam a validade
* de dados recebidos do usuário
*/

int ano_bissexto(int ano){
    if(ano % 400 == 0 || (ano % 100 != 0 && ano % 4 == 0))
    return 1; // ano bissexto
    return 0; // ano não bissexto
}

int compara_data_hora(int dd, int mm, int yy, int hh, int min){
    time_t rawtime;
    struct tm * data_hora;
    time(&rawtime);
    data_hora = localtime(&rawtime); //coleta a data e hora atuais

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

void decrementar_ano(int *yy){
    (*yy)--;
    if(*yy > 2100) (*yy) = 2100;
}

void decrementar_mes(int *mm, int *yy){
    (*mm)--;
    if(*mm<1){
        (*yy)--;
        *mm += 12;
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

void incrementar_ano(int *yy){
    (*yy)++;
    if(*yy < 1900) (*yy) = 1900;
}

void incrementar_mes(int *mm, int *yy){
    (*mm)++;
    if(*mm>12){
        (*yy)++;
        *mm -= 12;
    }
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

int verifica_data_hora_valida(int dd, int mm, int yy, int hh, int min){
    if(numero_dias(mm,yy)==-1) return 0;
    if(dd<1 || dd>numero_dias(mm,yy)) return 0;
    if(mm<1 || mm>12) return 0;
    if(hh<0 || hh>23) return 0;
    if(min<0 || min>59) return 0;

    return 1;
}

/*
* 2º bloco: funções responsáveis pela manipulação de lembretes:
* criação, exclusão, ordenação e verificação
*/

void Add_note(WINDOW * win){
    FILE *p;
    char nome_arq[30];
    int ano, ch=0;
    L.nota[0] = '\0';

    wclear(win);
    box(win,0,0);
    wrefresh(win);
    mvwaddstr(win,1,1,"Digite uma data e hora (DD/MM/AAAA HH:MM)");
    echo();
    curs_set(1);
    mvwscanw(win,2,1, "%d/%d/%d %d:%d", &L.dataL.dd, &L.dataL.mm, &L.dataL.yy, &L.horaL.hh, &L.horaL.mm);
    curs_set(0);
    noecho();
    while(1){
        //verifica se a data e a hora são válidas
        if(verifica_data_hora_valida(L.dataL.dd, L.dataL.mm, L.dataL.yy, L.horaL.hh, L.horaL.mm)==0){
            wclear(win);
            box(win,0,0);
            mvwaddstr(win,1,1,"Data/hora inválida!");
            mvwaddstr(win,2,1,"Pressione 't' para inserir data e hora novamente ou 'v' para voltar ao menu.");
            wrefresh(win);
            ch=0;
            while(ch!='t' && ch!='v') ch = getch();
            if(ch=='v') return;
            else{
                wclear(win);
                box(win,0,0);
                wrefresh(win);
                mvwprintw(win,1,1,"Insira uma data/hora válida (DD/MM/AAAA HH:MM): ");
                echo();
                curs_set(1);
                mvwscanw(win,2,1,"%d/%d/%d %d:%d", &L.dataL.dd, &L.dataL.mm, &L.dataL.yy, &L.horaL.hh, &L.horaL.mm);
                curs_set(0);
                noecho();
            }
        } 
        //verifica se a data e a hora estão ou não no passado
        else if(compara_data_hora(L.dataL.dd, L.dataL.mm, L.dataL.yy, L.horaL.hh, L.horaL.mm)==0){
            wclear(win);
            box(win,0,0);
            mvwaddstr(win,1,1, "Não é possível criar lembrete em uma data/hora passada!");
            mvwaddstr(win,2,1,"Pressione 't' para inserir data e hora novamente ou 'v' para voltar ao menu.");
            wrefresh(win);
            ch=0;
            while(ch!='t' && ch!='v') ch = getch();
            if(ch=='v') return;
            else{
                wclear(win);
                box(win,0,0);
                wrefresh(win);
                mvwprintw(win,1,1,"Insira uma data/hora válida (DD/MM/AAAA HH:MM): ");
                echo();
                curs_set(1);
                mvwscanw(win,2,1,"%d/%d/%d %d:%d", &L.dataL.dd, &L.dataL.mm, &L.dataL.yy, &L.horaL.hh, &L.horaL.mm);
                curs_set(0);
                noecho();
            }
        }
        else break;
    }
    //formato do nome do arquivo a ser acessado "Lembretes/ano_user.dat"
    sprintf(nome_arq, "Lembretes/%d_", L.dataL.yy);
    strcat(nome_arq, U.user);
    strcat(nome_arq, ".dat");
    p = fopen(nome_arq, "ab+");
    mvwaddstr(win,3,1,"Digite a nota (máx. 50 caracteres): ");
    echo();
    curs_set(1);
    mvwscanw(win,4,1, "%[^\n]", L.nota);
    curs_set(0);
    noecho();
    if(fwrite(&L, sizeof(L), 1, p)){
        mvwaddstr(win,6,1, "Nota salva com sucesso!");
        wrefresh(win);
        fclose(p);
    } else {
        mvwaddstr(win,6,1, "Erro ao salvar a nota!");
        wrefresh(win);
    } 
    mvwprintw(win,8,1,"Pressione qualquer tecla para voltar ao menu...");
    wrefresh(win);
    getch();
}

int check_note(int dd, int mm, int yy){
    FILE *p;
    char nome_arq[30];
    //formato do nome do arquivo a ser acessado "Lembretes/ano_user.dat"
    sprintf(nome_arq, "Lembretes/%d_", yy);
    strcat(nome_arq, U.user);
    strcat(nome_arq, ".dat");
    p = fopen(nome_arq, "rb");
    if(p==NULL) return 0;

    while(fread(&L,sizeof(L),1,p) == 1){
        if((L.dataL.dd == dd && L.dataL.mm == mm)){
            fclose(p);
            return 1;
        }
    }
    fclose(p);
    return 0;
}

int check_noteH(int dd, int mm, int yy, int hh, int min){
    FILE *p;
    char nome_arq[30];
    //formato do nome do arquivo a ser acessado "Lembretes/ano_user.dat"
    sprintf(nome_arq, "Lembretes/%d_", yy);
    strcat(nome_arq, U.user);
    strcat(nome_arq, ".dat");
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

void deleta_lembrete(WINDOW * win, int dd, int mm, int yy, int hh, int min){
    FILE * arq, * temp;
    char nome_arq[30];
    Lembrete lemb;
    //formato do nome do arquivo a ser acessado "Lembretes/ano_user.dat"
    sprintf(nome_arq, "Lembretes/%d_", yy);
    strcat(nome_arq, U.user);
    strcat(nome_arq, ".dat");
    arq = fopen(nome_arq, "rb");

    if(arq == NULL){
        mvwaddstr(win,4,1, "Erro ao acessar arquivo!");
        mvwaddstr(win,5,1, "Pressione qualquer tecla para voltar ao menu");
        wrefresh(win);
        getch();
        return;
    }

    if(check_noteH(dd, mm, yy, hh, min)==0){
        mvwaddstr(win,4,1,"Não existe nenhum lembrete na data e hora inseridas!");
        mvwaddstr(win,5,1, "Pressione qualquer tecla para voltar ao menu");
        wrefresh(win);
        getch();
        fclose(arq);
        return;
    }

    temp = fopen("temp.dat", "wb");

    /*
    * se o lembrete não for o que se deseja deletar
    * ele é copiado para um arquivo temporário
    * se sim, ele é ignorado e a mensagem é exibida na tels
    */
    while(fread(&lemb, sizeof(lemb), 1, arq) == 1){
        if(lemb.dataL.dd == dd && lemb.dataL.mm == mm && lemb.horaL.hh == hh && lemb.horaL.mm == min){
            mvaddstr(4,1, "Nota deletada com sucesso!");
            wrefresh(win);
        } 
        else fwrite(&lemb, sizeof(lemb), 1, temp);
    }

    fclose(arq);
    fclose(temp);
    //o arquivo temporário é transformado no principal, e o antigo é removido
    remove(nome_arq);
    rename("temp.dat", nome_arq);
    mvwaddstr(win,5,1, "Pressione qualquer tecla para voltar ao menu");
    wrefresh(win);
    getch();
}

void swap_lembretes(Lembrete* a, int i, int j){
    Lembrete *aux = (Lembrete *) malloc(sizeof(Lembrete));

    aux[0] = a[i];
    a[i] = a[j];
    a[j] = aux[0];
    free(aux);
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

/*
* 3º bloco: funções responsáveis por imprimir conteúdo na tela
*/

void imprime_notes_dia(WINDOW * win, int dd, int mm, int yy){
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    FILE *p;
    int i = 0, achou = 0, contador = 0;
    char nome_arq[30];
    //formato do nome do arquivo a ser acessado "Lembretes/ano_user.dat"
    sprintf(nome_arq, "Lembretes/%d_", yy);
    strcat(nome_arq, U.user);
    strcat(nome_arq, ".dat");
    p = fopen(nome_arq, "rb");

    wclear(win);
    wattron(win, COLOR_PAIR(1));
    box(win,0,0);
    wattroff(win, COLOR_PAIR(1));
    wrefresh(win);

    if(p==NULL){
        mvwprintw(win,1,1,"Erro ao abrir o arquivo");
        mvwaddstr(win,2,1, "Pressione qualquer tecla para voltar ao menu");
        getch();
        return;
    }

    fseek(p, 0, SEEK_SET);
    //imprime os lembretes
    while(fread(&L, sizeof(L),1,p)==1){
        if(L.dataL.dd==dd && L.dataL.mm==mm){
            if(L.horaL.mm<10) mvwprintw(win,1+i,1,"Nota %d, dia %d, hora %d:0%d: %s", i+1, L.dataL.dd, L.horaL.hh, L.horaL.mm, L.nota);
            else mvwprintw(win,1+i,1,"Nota %d, dia %d, hora %d:%d: %s", i+1, L.dataL.dd, L.horaL.hh, L.horaL.mm, L.nota);
            achou = 1;
            i++;
            wrefresh(win);
        }
    }
    if(achou==0) {
        mvprintw(1,1,"Esse dia não possui nenhum lembrete");
        wrefresh(win);
        i = 1;
    }

    fclose(p);
    mvprintw(1+i,1,"Pressione qualquer tecla para voltar ao menu...");
    wrefresh(win);
    getch();
}

void imprime_notes_mes(WINDOW * win, int mm, int yy, int flag){
    FILE *p;
    int i = 1, j, achou = 0, cont = 0;
    Lembrete * lembrete = (Lembrete*) malloc(sizeof(Lembrete)), *ltemp;
    char nome_arq[30];
    //formato do nome do arquivo a ser acessado "Lembretes/ano_user.dat"
    sprintf(nome_arq, "Lembretes/%d_", yy);
    strcat(nome_arq, U.user);
    strcat(nome_arq, ".dat");
    p = fopen(nome_arq, "rb");

    if(p==NULL){
        mvwprintw(win,1,1,"Erro ao abrir o arquivo");
        free(lembrete);
        wrefresh(win);
        return;
    }
    int k = 1;

    //coleta os lembretes do mês selecionado
    while(fread(&L, sizeof(L), 1, p) == 1){
        if(L.dataL.mm == mm){
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

    //ordena os lembretes por data e hora
    for(i=0; i<k-1; i++){
        for(j=i+1; j<k-1; j++){
            if(verica_maiorDia(lembrete, i, j) == 1) swap_lembretes(lembrete, i, j);
        }
    }
    
    //imprime os lembretes ordenados
    for(i=0; i<k-1; i++){
        if(lembrete[i].horaL.mm<10) mvwprintw(win, 1+i,1,"Nota %d, dia %d, hora %d:0%d: %s", i+1, 
        lembrete[i].dataL.dd, lembrete[i].horaL.hh, lembrete[i].horaL.mm, lembrete[i].nota);
        else mvwprintw(win, 1+i,1,"Nota %d, dia %d, hora %d:%d: %s", i+1, 
        lembrete[i].dataL.dd, lembrete[i].horaL.hh, lembrete[i].horaL.mm, lembrete[i].nota);
    }

    if(achou==0){
        mvwprintw(win, 1,1,"Esse mês não possui nenhum lembrete");
        i = 1;
    }

    fclose(p);
    free(lembrete);
    wrefresh(win);
    if(flag==1){
        mvwaddstr(win,3+i,1,"Pressione qualquer tecla para voltar ao menu.");
        wrefresh(win);
        getch();
    }
}

void print_current_month(WINDOW * win, int mm, int yy){
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    int mes[6][7]; //matriz que contém o calendário
    int dia1, nDias, i, j, k;
    dia1 = dis_semana(1,mm,yy); //dia da semana em que o mês começa
    nDias = numero_dias(mm,yy); //número de dias do mês
    for(i=0;i<6;i++){ 
        for(j=0;j<7;j++){
            mes[i][j]=0; //inicializa a matriz com 0 em todas as posições
        }
    }
    k=1;
    i=0;
    j=dia1;
    /*
    * preenche a matriz com os dias em sequência,
    * respeitando a quantidade de dias do mês e
    * o dia da semana em que o mês começa
    */
    while(k<=nDias){
        mes[i][j]=k;
        j++;         
        k++;
        if(j==7){
            j=0;
            i++;
        }
    }

    mvwprintw(win,1,1,"Mês: %d Ano: %d", mm, yy);
    switch(mm){
        case 1: mvwprintw(win,2,1,"Janeiro");
                break;
        case 2: mvwprintw(win,2,1,"Fevereiro");
                break;
        case 3: mvwprintw(win,2,1,"Março");
                break;
        case 4: mvwprintw(win,2,1,"Abril");
                break;
        case 5: mvwprintw(win,2,1,"Maio");
                break;
        case 6: mvwprintw(win,2,1,"Junho");
                break;
        case 7: mvwprintw(win,2,1,"Julho");
                break;
        case 8: mvwprintw(win,2,1,"Agosto");
                break;
        case 9: mvwprintw(win,2,1,"Setembro");
                break;
        case 10: mvwprintw(win,2,1,"Outubro");
                break;
        case 11: mvwprintw(win,2,1,"Novembro");
                break;
        case 12: mvwprintw(win,2,1,"Dezembro");
                break;
    }
    wattron(win, A_BOLD);
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win,3,3,"D  S  T  Q  Q  S  S");
    wattroff(win, A_BOLD);
    wattroff(win, COLOR_PAIR(1));
    for(i=0;i<6;i++){
        for(j=0;j<7;j++){
            if(check_note(mes[i][j], mm, yy)==1){ //destaca os dias que possuem lembretes
                wattron(win, A_BOLD);
                wattron(win, COLOR_PAIR(1));
            }
            if(mes[i][j]==0){ //imprime um "x" nas posições da matriz que não representam nenhum dia daquele mês
                wattron(win, A_DIM);
                wattron(win, COLOR_PAIR(1));
                mvwprintw(win,i+4,j*3+3,"x");
                wattroff(win, A_DIM);
                wattron(win, COLOR_PAIR(1));
            } 
            else mvwprintw(win,i+4,j*3+3,"%d", mes[i][j]); //imprime os dias do mês
            wattroff(win, A_BOLD);
            wattroff(win, COLOR_PAIR(1));
        }
    }
    wrefresh(win);
}

/*
* 4º bloco: funções responsáveis pelas tarefas
* relacionadas a usuários, senhas e login
*/

void cadastra_User(WINDOW * win, User * t){
    FILE *f = fopen("user.dat", "ab+");
    User *temp = malloc(sizeof(User));
    strcpy(temp->password, t->password);
    criptografar_password(t->password);

    wclear(win);
    box(win,0,0);
    wrefresh(win);
    if(verify_User(t->user) == 1) {
        mvwaddstr(win,1,1, "Usuário já cadastrado!");
        //mvwprintw(win,3,1,"Login: \"%s\" senha: \"%s\"", t->user, temp->password);
        fclose(f);
        mvwaddstr(win,5,1, "Pressione qualquer tecla para prosseguir");
        wrefresh(win);
        getch();
    } else{
        if(fwrite(t->user, sizeof(t->user), 1, f) && fwrite(t->password, sizeof(t->password), 1, f)){
            mvwaddstr(win,1,1, "Usuário cadastrado com sucesso!");
            mvwprintw(win,3,1,"Login: \"%s\" senha: \"%s\"", t->user, temp->password);
            fclose(f);
            mvwaddstr(win,5,1, "Pressione qualquer tecla para prosseguir");
            wrefresh(win);
            getch();
        }
    }
    free(temp);
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

int letras(char r){
    if((r >= 'a' && r <= 'z') || (r >= 'A' && r <= 'Z')) return 1;
    else return 0;
}

int login(User * t){
    FILE *f = fopen("user.dat", "rb");
    if(f == NULL) return -1;

    while(fread(&U, sizeof(U), 1, f) == 1){
        if(strcmp(U.user, t->user) == 0){
            if(strcmp(U.password, t->password)==0){
                fclose(f);
                return 1;
            }
        }
    }
    fclose(f);
    return 0; //não foi possível fazer login
}

int verify_User(char *user){
    FILE *p = fopen("user.dat", "rb");

    while(fread(&U, sizeof(U), 1, p) == 1){
        if(strcmp(U.user, user) == 0) {
            fclose(p);
            return 1; ////usuário já cadastrado;
        } 
    }

    fclose(p);
    return 0; //caso não tenha um usuário já cadastrado com esse nome;
}
