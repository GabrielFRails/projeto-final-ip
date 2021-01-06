#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#define N 11

//estrutura para armezenamento de data
typedef struct{
    int dd;
    int mm;
    int yy;
}Data;

Data data;

//estrutura para armazenamento de hora
typedef struct {
    int hh;
    int mm;
}Hora;

Hora hora;

//estrutura para armazenamento de usuário
typedef struct{
    char user[N];
    char password[N];
}User;

User U, *t;

//estrutura para armazenamento de lembrete
typedef struct{
    Data dataL;
    Hora horaL;
    char nota[51];
    User userL;
}Lembrete;

Lembrete L;

/*
* 1º bloco: funções que coletam/retornam valores necessários
* para a execução de outras funções e/ou verificam a validade
* de dados recebidos do usuário
*/

/**
 * @brief Função que verifica se um ano é bissexto ou não
 * 
 * @param ano (Ano a ser verificado)
 * @return 1 se for bissexto
 *         0 se não for bissexto
 */
int ano_bissexto(int ano);

/**
 * @brief Compara se a data e hora inseridas pelo usuário com as atuais
 * 
 * @param dd dia
 * @param mm mês
 * @param yy ano
 * @param hh hora
 * @param min minutos
 * @return int 0 se estiver no passado, 1 se não
 */
int compara_data_hora(int dd, int mm, int yy, int hh, int min);

/**
 * @brief decremente em 1 o ano passado como parâmetro
 * 
 * @param yy 
 */

void decrementar_ano(int *yy);

/**
 * @brief Função para decrementar o mês atual em uso/visualização em 1 unidade
 * 
 * @param mm (Mês a ser decrementado)
 * @param yy (Ano ao qual o mês a ser decrementado pertence)
 */
void decrementar_mes(int *mm, int *yy);

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
 * @return Um inteiro (0-7) de acordo com o dia da semana encontrado (0==Domingo e 7==Sábado)
 */
int dis_semana(int dd, int mm, int aa);

/**
 * @brief incrementa em 1 o ano passado como parâmetro
 * 
 * @param yy 
 */

void incrementar_ano(int *yy);

/**
 * @brief Função para incrementar o mês atual em uso/visualização em 1 unidade
 * 
 * @param mm (Mês a ser incrementado)
 * @param yy (Ano ao qual o mês a ser incrementado pertence)
 */
void incrementar_mes(int *mm, int *yy);

/**
 * @brief Função que verifica quantos dias tem um mês
 * 
 * @param mes (Mês a ser verificado)
 * @param ano (Ano ao qual o mês a ser verificado pertence)
 * @return Retorna a quantidade de dias do mês inserido pelo usuário ou -1 em caso de entrada inválida
 */
int numero_dias(int mes, int ano);

/**
 * @brief Verifica se uma data e hora são válidas
 * 
 * @param dd dia
 * @param mm mês
 * @param yy ano
 * @param hh hora
 * @param min minutos
 * @return int 0 se não for válida, 1 se sim
 */
int verifica_data_hora_valida(int dd, int mm, int yy, int hh, int min);

/*
* 2º bloco: funções responsáveis pela manipulação de lembretes:
* criação, exclusão, ordenação e verificação
*/

/**
 * @brief Adiciona um lembrete
 * 
 * @param win janela da qual será coletada a entrada do usuário e 
 * na qual serão impressas as mensagens necessárias
 */
void Add_note(WINDOW * win);

/**
 * @brief Verifica se um dia possui algum lembrete
 * 
 * @param dd dia
 * @param mm mês
 * @param yy ano
 * @return int 1 se possuir lembrete, 0 se não
 */
int check_note(int dd, int mm, int yy);

/**
 * @brief Verifica se um dia possui algum lembrete em uma hora determinada
 * 
 * @param dd dia
 * @param mm mês
 * @param yy ano
 * @param hh hora
 * @param min minutos
 * @return int 1 se possuir lembrete, 0 se não
 */
int check_noteH(int dd, int mm, int yy, int hh, int min);

/**
 * @brief Deleta o lembrete correspondente a uma data e hora inserida pelo usuário
 * 
 * @param dd dia
 * @param mm mês
 * @param yy ano
 * @param hh hora
 * @param min minutos
 */
void deleta_lembrete(WINDOW * win, int dd, int mm, int yy, int hh, int min);

/**
 * @brief inverte o valor de duas estruturas
 * 
 * @param a ponteiro para a estrutura lembrete
 * @param i posição i
 * @param j posição j
 */

void swap_lembretes(Lembrete * a, int i, int j);

/**
 * @brief Verifica se determinada parte da estrutura da posição i é maior que da posição j
 * 
 * @param a ponteiro para a estrutura
 * @param i posição "1"
 * @param j posição "2"
 * @return 1 caso for maior e 0 caso contrário
 */

int verica_maiorDia(Lembrete * a, int i, int j);

/*
* 3º bloco: funções responsáveis por imprimir conteúdo na tela
*/

/**
 * @brief Imprime todos os lembretes de um determinado dia
 * 
 * @param win janela na qual as notas serão impressas
 * @param dd dia
 * @param mm mês
 * @param yy ano
 */
void imprime_notes_dia(WINDOW * win, int dd, int mm, int yy);

/**
 * @brief Imprime todos os lembretes de um determinado mês
 * 
 * @param win janela na qual as notas serão impressas
 * @param mm mês
 * @param yy ano
 * @param flag indica se a função precisa esperar que o usuário digite um caracter antes de encerrar (1) ou não (0)
 */
void imprime_notes_mes(WINDOW * win, int mm, int yy, int flag);

/**
 * @brief Função que imprime o calendário do mês na tela
 * 
 * @param win (Janela na qual o calendário será impresso)
 * @param mm (Mês a ser impresso)
 * @param yy (Ano ao qual o mês a ser impresso pertence)
 */
void print_current_month(WINDOW * win, int mm, int yy); 

/*
* 4º bloco: funções responsáveis pelas tarefas
* relacionadas a usuários, senhas e login
*/

/**
 * @brief cadastra usuário e senha da struct User em um arquivo
 * 
 * @param t ponteiro para a estrura a ser salva
 */
void cadastra_User(WINDOW * win, User * t);

/**
 * @brief criptografa uma string
 * 
 * @param p ponteiro para o início de uma string
 */
void criptografar_password(char *p);

/**
 * @brief verifica se determinada posição de uma string é uma letra
 * 
 * @param r posição da string, exemplo str[i]
 * @return int 1 caso seja uma letra, 0 caso contrário
 */
int letras(char r);

/**
 * @brief realiza o login de um user e senha
 * 
 * @param t ponteiro para a estrura a ser verificada
 * @return int 1 login sucess e 0 caso contrário
 */
int login(User * t);


/**
 * @brief verifica se um usuário já está cadastrado
 * 
 * @param user string a ser verificada
 * @return int 1 para caso já tenha um usuário cadastrado e 0 caso não tenha
 */
int verify_User(char *user);

#endif
