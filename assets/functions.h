#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

typedef struct{
    int dd;
    int mm;
    int yy;
}Data;

Data data;

typedef struct {
    int hh;
    int mm;
}Hora;

Hora hora;

typedef struct{
    Data dataL;
    Hora horaL;
    char nota[51];
}Lembrete;

Lembrete L;

/**
 * @brief Função que verifica se um ano é bissexto ou não
 * 
 * @param ano (Ano a ser verificado)
 * @return 1 se for bissexto
 *         0 se não for bissexto
 */
int ano_bissexto(int ano);

/**
 * @brief Função que verifica quantos dias tem um mês
 * 
 * @param mes (Mês a ser verificado)
 * @param ano (Ano ao qual o mês a ser verificado pertence)
 * @return Retorna a quantidade de dias do mês inserido pelo usuário ou -1 em caso de entrada inválida
 */
int numero_dias(int mes, int ano);

/**
 * @brief Função para incrementar o mês atual em uso/visualização em 1 unidade
 * 
 * @param mm (Mês a ser incrementado)
 * @param yy (Ano ao qual o mês a ser incrementado pertence)
 */
void incrementar_mes(int *mm, int *yy);

/**
 * @brief Função para decrementar o mês atual em uso/visualização em 1 unidade
 * 
 * @param mm (Mês a ser decrementado)
 * @param yy (Ano ao qual o mês a ser decrementado pertence)
 */
void decrementar_mes(int *mm, int *yy);

/**
 * @brief incrementa em 1 o ano passado como parâmetro
 * 
 * @param yy 
 */

void incrementar_ano(int *yy);

/**
 * @brief decremente em 1 o ano passado como parâmetro
 * 
 * @param yy 
 */

void decrementar_ano(int *yy);

/**
 * @brief Função que imprime o calendário do mês na tela
 * 
 * @param mm (Mês a ser impresso)
 * @param yy (Ano ao qual o mês a ser impresso pertence)
 */
void print_current_month(int mm, int yy);

/**
 * @brief Função que verifica qual dia da semana corresponde a uma determinada data,
 *        de acordo com o retorno da função <dis_semana>
 * 
 * @param dia (retorno da função <dis_semana>)
 * @return Uma string com o dia da semana correspondente 
 */
char *dia_semana(int dia);

/**
 * @brief 
 * 
 * @param dd (Dia a ser verificado)
 * @param mm (Mês ao qual o dia a ser verificado pertence)
 * @param aa (Ano ao qual o dia e o mês a serem verificados pertencem)
 * @return Um inteiro de acordo com o dia da semana encontrado
 */
int dis_semana(int dd, int mm, int aa); 

/**
 * @brief Adiciona um lembrete
 * 
 */
void Add_note();

/**
 * @brief Verifica se um dia possui algum lembrete
 * 
 * @param dd 
 * @param mm 
 * @param yy 
 * @return int 1 se possuir lembrete, 0 se não
 */
int check_note(int dd, int mm, int yy);

/**
 * @brief Verifica se um dia possui algum lembrete em uma hora determinada
 * 
 * @param dd 
 * @param mm 
 * @param yy 
 * @param hh
 * @param min
 * @return int 1 se possuir lembrete, 0 se não
 */
int check_noteH(int dd, int mm, int yy, int hh, int min);

/**
 * @brief Imprime todos os lembretes de um determinado mês
 * 
 * @param mm 
 * @param yy 
 */
void imprime_notes_mes(int mm, int yy);

/**
 * @brief Imprime todos os lembretes de um determinado dia
 * 
 * @param dd 
 * @param mm 
 * @param yy 
 */
void imprime_notes_dia(int dd, int mm, int yy);

/**
 * @brief Compara se a data e hora inseridas pelo usuário estão no passado ou futuro
 * 
 * @param dd 
 * @param mm 
 * @param yy 
 * @param hh 
 * @param min 
 * @return int 0 se estiver no passado, 2 se não
 */
int compara_data_hora(int dd, int mm, int yy, int hh, int min);

/**
 * @brief Verifica se uma data e hora são válidas
 * 
 * @param dd 
 * @param mm 
 * @param yy 
 * @param hh 
 * @param min 
 * @return int 0 se não for válida, 1 se sim
 */
int verifica_data_hora_valida(int dd, int mm, int yy, int hh, int min);

/**
 * @brief Verifica se determinada parte da estrutura da posição i é maior que da posição j
 * 
 * @param a ponteiro para a estrutura
 * @param i posição "1"
 * @param j posição "2"
 * @return 1 caso for maior e 0 caso contrário
 */

int verica_maiorDia(Lembrete * a, int i, int j);

/**
 * @brief inverte o valor de duas estruturas
 * 
 * @param a ponteiro para a estrutura lembrete
 * @param i posição i
 * @param j posição j
 */

void swap_lembretes(Lembrete * a, int i, int j);

/**
 * @brief Deleta o lembrete correspondente a uma data e hora inserida pelo usuário
 * 
 * @param dd 
 * @param mm 
 * @param yy 
 * @param hh 
 * @param min 
 */
void deleta_lembrete(int dd, int mm, int yy, int hh, int min);

#endif
