// Adicionando as bibliotecas necessárias
#include<stdio.h>
#include <stdlib.h> //Função system() funciona apenas no Windows

// Cores de texto
#define VERMELHO "\033[31m"
#define VERDE "\033[32m"
#define AMARELO "\033[33m"
#define RESET "\033[0m"

//Definindo constantes
#define TEMP_MAX 80.0
#define ENERGIA_MIN 20.0
#define MAX_HISTORICO 5

//Criando struct
typedef struct {
    float temperatura;
    float energia;
    int comunicacao;
    int status_temp; //0 - > temperatura máx. | 1 - normal
    int status_ene; //0 - < energia mín. | 1 - normal
} Dados_nave;

Dados_nave historico[MAX_HISTORICO];

int total_registros = 0;
int proximo_indice = 0;

//Função para verificar estado das variáveis
void verificar_dados(Dados_nave *nave){
    if(nave->temperatura > TEMP_MAX){
        nave->status_temp = 0;
    } else{
        nave->status_temp = 1;
    }

    if(nave->energia < ENERGIA_MIN){
        nave->status_ene = 0;
    } else{
        nave->status_ene = 1;
    }
}

//Função para pegar os dados simulados
void inserir_dados(Dados_nave *nave){
    printf(AMARELO "---------------------\n" RESET);
    printf(AMARELO "   Inserindo Dados   \n" RESET);
    printf(AMARELO "---------------------\n" RESET);
    printf("\n");

    do{
        printf("Digite a temperatura interna da nave: ");
        scanf("%f", &nave->temperatura);
        printf("\n");
    } while(nave->temperatura < 0.0 || nave->temperatura > 100.0);

    do{
        printf("Digite a %% de energia da nave: ");
        scanf("%f", &nave->energia);
        printf("\n");
    } while(nave->energia < 0.0 || nave->energia > 100.00);

    do{
        printf("Digite o status de comunicacao da nave: \n");
        printf("0 - Falha\n");
        printf("1 - Ativa\n");
        scanf("%d", &nave->comunicacao);
        printf("\n");
    } while(nave->comunicacao < 0 || nave->comunicacao > 1);

    
    verificar_dados(nave);
}

//Função para visualizar as variáveis e o estado de cada uma
void visualizar_status(Dados_nave *nave){
    printf(AMARELO "----------------------\n" RESET);
    printf(AMARELO "   Visualizar Dados   \n" RESET);
    printf(AMARELO "----------------------\n" RESET);
    printf("\n");
    
    printf("Temperatura Interna: %.1f C | Status: ", nave->temperatura);
    if(nave->status_temp == 0){
        printf( VERMELHO "Superaquecimento\n" RESET);
    }else{
        printf( VERDE "Normal\n" RESET);
    }
    printf("\n");

    printf("Energia da Nave: %.1f%% | Status: ", nave->energia);
    if(nave->status_ene == 0){
        printf( VERMELHO "Economia de Energia\n" RESET);
    }else{
        printf( VERDE "Normal\n" RESET);
    }
    printf("\n");

    printf("Comunicacao com a central: ");
    if(nave->comunicacao == 0){
        printf( VERMELHO "Falhou\n" RESET);
    }else{
        printf( VERDE "Ativa\n" RESET);
    }
    printf("\n");
}

//Função para gerar um relatório com as ações necessárias para cada variável
void gerar_relatorio(Dados_nave *nave){
    printf(AMARELO "---------------------\n" RESET);
    printf(AMARELO "      Relatorio      \n" RESET);
    printf(AMARELO "---------------------\n" RESET);
    printf("\n");

    printf("Temperatura Interna: %.1f C\n", nave->temperatura);
    printf("Acoes: ");
    if(nave->status_temp == 0){
        printf( VERMELHO "Desligue o motor e procure a causa do aumento de temperatura.\n" RESET);
    }else{
        printf( VERDE "Sem acoes necessarias.\n" RESET);
    }
    printf("\n");

    printf("Energia da Nave: %.1f%%\n", nave->energia);
    printf("Acoes: ");
    if(nave->status_ene == 0){
        printf( VERMELHO "Pare a nave, desligue equipamentos menos prioritarios, espere o carregamento por energia solar.\n" RESET);
    }else{
        printf( VERDE "Sem acoes necessarias.\n" RESET);
    }
    printf("\n");

    printf("Comunicacao com a central: ");
    if(nave->comunicacao == 0){
        printf( VERMELHO "Falhou\n" RESET);
    }else{
        printf( VERDE "Ativa\n" RESET);
    }
    printf("Acoes: ");
    if(nave->comunicacao == 0){
        printf( VERMELHO "Reestabeleca comunicacao com a central urgentemente.\n" RESET);
        
    }else{
        printf( VERDE "Sem acoes necessarias.\n" RESET);
    }
    printf("\n");
}

//Função para preencher o histórico de dados da nave, mantendo os últimos 5 registros (Antigo -> Recente)
void preencher_historico(Dados_nave *nave){
    historico[proximo_indice] = *nave;
    
    proximo_indice = (proximo_indice + 1) % MAX_HISTORICO;

    if(total_registros < MAX_HISTORICO){
        total_registros++;
    }
}

//Função para mostrar o histórico de dados da nave (Antigo -> Recente)
void mostrar_historico(){
    printf(AMARELO "---------------------\n" RESET);
    printf(AMARELO "     Historico       \n" RESET);
    printf(AMARELO "---------------------\n" RESET);
    printf("\n");

    if(total_registros == 0){
        printf("Nenhum registro no historico.\n\n");
        return;
    }
    
    int indice_inicial;
    if(total_registros < MAX_HISTORICO){
        indice_inicial = 0;
    } else {
        indice_inicial = proximo_indice;
    }
    
    for(int i = 0; i < total_registros; i++){
        int indice = (indice_inicial + i) % MAX_HISTORICO;
        
        printf("Registro %d:\n", i + 1);
        printf("Temperatura Interna: %.1f C | Status: ", historico[indice].temperatura);
        if(historico[indice].status_temp == 0){
            printf( VERMELHO "Superaquecimento\n" RESET);
        }else{
            printf( VERDE "Normal\n" RESET);
        }
        printf("\n");

        printf("Energia da Nave: %.1f%% | Status: ", historico[indice].energia);
        if(historico[indice].status_ene == 0){
            printf( VERMELHO "Economia de Energia\n" RESET);
        }else{
            printf( VERDE "Normal\n" RESET);
        }
        printf("\n");

        printf("Comunicacao com a central: ");
        if(historico[indice].comunicacao == 0){
            printf( VERMELHO "Falhou\n" RESET);
        }else{
            printf( VERDE "Ativa\n" RESET);
        }
        printf("\n");
        printf("------------------------\n\n");
    }
    
    if(total_registros == MAX_HISTORICO){
        printf("Historico cheio - os registros mais antigos estao sendo substituidos\n\n");
    }
}

//Função menu
int menu(){
    int opcao;

    do{
        printf(AMARELO "=====================\n" RESET);
        printf(AMARELO "   Missao Espacial   \n" RESET);
        printf(AMARELO "=====================\n" RESET);
        printf("\n");

        printf("1 - Inserir Dados\n");
        printf("2 - Visualizar Status\n");
        printf("3 - Gerar Relatorio\n");
        printf("4 - Ver Historico\n");
        printf("5 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf("\n");
        
    } while(opcao < 1 || opcao > 5);

    return opcao;
}

int main(){
    int opcao;
    int dados_inseridos = 0;
    Dados_nave minha_nave;
    
    do{
        switch(opcao = menu()){
            case 1:
                inserir_dados(&minha_nave);

                preencher_historico(&minha_nave);

                dados_inseridos = 1;
            break;

            case 2:
                if(dados_inseridos == 1){
                    visualizar_status(&minha_nave);

                    system("pause");
                    system("cls");
                } else {
                    printf("Insira os dados primeiro (opcao 1).\n\n");
                }
            break;

            case 3:
                if(dados_inseridos == 1){
                    gerar_relatorio(&minha_nave);

                    system("pause");
                    system("cls");
                } else {
                    printf("Insira os dados primeiro (opcao 1).\n\n");
                }
            break;

            case 4:
                mostrar_historico();

                system("pause");
                system("cls");
            break;
        }
    } while(opcao != 5);
    
    printf("Encerrando o sistema...");
    printf("\n");

    system("pause");
    system("cls");

    return 0;
}