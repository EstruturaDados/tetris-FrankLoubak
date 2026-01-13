#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define maxFila 5
#define maxTipoPeca 4
#define id_inicio 10
#define maxPilha 3

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.
int inicialid=id_inicio;


typedef struct 
{
    char nome ;
    
    int id;
}peca;

typedef struct
{
    peca fila [maxFila];
    int inicio ;
    int fim ;
    int tamanho ;

}fila;
typedef struct {

    peca pilha[maxPilha];
    int topo;
    
}pilha;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define maxFila 5
#define maxTipoPeca 4

// PROTÓTIPOS AQUI
void limparBuffer(void);
peca iniciarPeca(void);
void iniciarFila(fila *f);
void preencherFila(fila *f);
int inserirPeca(fila *f, peca nova);
int removerPeca(fila *f, peca *removida);
void mostrarFila(fila *f);
void iniciarPilha(pilha *pil);
int inserirPilha(pilha *pil, peca removida);
int removerPilha(pilha *pil, peca *pecaDaPilha);
void mostrarPilha(pilha *pil);
void enviarFilaParaPilha(fila *f, pilha *pil);
void usarPilhaNaFila(fila *f, pilha *pil);
int trocarTresFilaPilha(fila *f, pilha *pil);




peca iniciarPeca(){
    inicialid++;
    peca p;
    p.id=inicialid;
    
    int n = rand()%maxTipoPeca;
    switch (n) {
        case 0: p.nome = 'I'; break;
        case 1: p.nome = 'T'; break;
        case 2: p.nome = 'O'; break;
        case 3: p.nome = 'L'; break;
    }

    return p;
}
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void iniciarPilha(pilha *pil){
    pil->topo =-1;
}
int inserirPilha(pilha *pil, peca removida){
    if(pil->topo == maxPilha-1){
        printf("pilha cheia\n");
        return 0;
    }
    pil->topo++;
    pil->pilha[pil->topo]=removida;
    return 1;
    
    

}
int removerPilha(pilha *pil, peca *pecaDaPilha){
    if(pil->topo<0){
        printf("pilha vazia\n");
        return 0;
    }else{
        *pecaDaPilha=pil->pilha[pil->topo];
        pil->topo--;
        return 1;
        
    }
}    
void mostrarPilha(pilha *pil){
    printf("\nEstado da pilha:\n");

    for (int i = maxPilha - 1; i >= 0; i--){
        printf("[%d] ", i);

        if (i == pil->topo)
            printf("TOPO ");

        if (i <= pil->topo)
            printf("(%c, %d)", pil->pilha[i].nome, pil->pilha[i].id);
        else
            printf("(vazio)");

        printf("\n");
    }
}


void enviarFilaParaPilha(fila *f, pilha *pil){
    peca retirada;

    if (!removerPeca(f, &retirada))
        return;

    if (!inserirPilha(pil, retirada)){
        // se pilha cheia, devolve a peça à fila
        inserirPeca(f, retirada);
        return;
    }
    printf("\npeça %c %d retirada da fila\n",retirada.nome,retirada.id);

    // mantém fila sempre cheia
    inserirPeca(f, iniciarPeca());
}
void usarPilhaNaFila(fila *f, pilha *pil){
    peca daPilha, daFila;

    if (!removerPilha(pil, &daPilha))
        return;

    if (!removerPeca(f, &daFila)){
        inserirPilha(pil, daPilha);
        return;
    }

    inserirPeca(f, daPilha);
    inserirPeca(f, daFila);
}

void iniciarFila(fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
}

void preencherFila(fila *f){
    for (int i = 0; i < maxFila; i++) {
        inserirPeca(f, iniciarPeca());
    }
}

    

int inserirPeca(fila *f, peca nova) {
   
    if (f->tamanho == maxFila) {
        printf("Fila cheia! Não é possível inserir.\n");
        return 0;
    }

    f->fila[f->fim] = nova;
    f->fim = (f->fim + 1) % maxFila;
    f->tamanho++;

    return 1;
}
int removerPeca(fila *f, peca *removida) {
    if (f->tamanho == 0) {
        printf("Fila vazia! Nada para remover.\n");
        return 0;
    }

    *removida = f->fila[f->inicio];
    f->inicio = (f->inicio + 1) % maxFila;
    f->tamanho--;

    return 1;
}
void mostrarFila(fila *f) {
    printf("\nEstado da fila:\n");
    printf("Inicio: %d | Fim: %d | Tamanho: %d\n", 
            f->inicio, f->fim, f->tamanho);

    for (int i = 0; i < maxFila; i++) {
        printf("[%d] ", i);

        if (i == f->inicio && f->tamanho > 0)
            printf("INICIO ");

        if (i == f->fim )
            printf("FIM ");

        if (f->fila[i].id != 0)
            printf("(%c, %d)", f->fila[i].nome, f->fila[i].id);
        else
            printf("(vazio)");

        printf("\n");
    }
}
int trocarTresFilaPilha(fila *f, pilha *pil) {
    if (f->tamanho < 3) {
        printf("\nErro: fila não possui 3 peças.\n");
        return 0;
    }

    if (pil->topo != 2) {
        printf("\nErro: pilha deve conter exatamente 3 peças.\n");
        return 0;
    }

    peca daFila[3];
    peca daPilha[3];

    // Remove 3 da fila
    for (int i = 0; i < 3; i++) {
        removerPeca(f, &daFila[i]);
    }

    // Remove 3 da pilha (do topo para baixo)
    for (int i = 2; i >= 0; i--) {
        removerPilha(pil, &daPilha[i]);
    }

    // Insere as 3 da pilha na fila
    for (int i = 0; i < 3; i++) {
        inserirPeca(f, daPilha[i]);
    }

    // Insere as 3 da fila na pilha
    for (int i = 0; i < 3; i++) {
        inserirPilha(pil, daFila[i]);
    }

    printf("\nTroca das 3 peças realizada com sucesso!\n");
    return 1;
}






int main() {
    srand (time(NULL));
    fila f , filainvertida;
    pilha pil;
    iniciarPilha(&pil);
    iniciarFila(&f);
    iniciarFila(&filainvertida);
    int opcao;
    

    printf("---teris---\n");

    do{
                printf("\n(01)-Iniciar fila\n");
                printf("(02)-Adicionar peça\n");
                printf("(03)-Jogar peça (remover da fila)\n");
                printf("(04)-Enviar peça para reserva\n");
                printf("(05)-Usar peça da reserva\n");
                printf("(06)-exibir estado atual da fila e pilha\n");
                printf("(07)-trocar as 3 primeiras peças da fila\n");
                printf("(09)-Sair\n");
                printf("escolha uma opção : ");

                scanf("%d",&opcao);
                limparBuffer();
                switch (opcao) {
                        case 1:
                            preencherFila(&f);
                            mostrarFila(&f);
                            
                            break;
                        case 2:
                            if(f.tamanho<maxFila){
                                peca p = iniciarPeca();
                                inserirPeca(&f,p);
                                mostrarFila(&f);

                            }else{
                                printf("\nfila cheia\n");
                            }
                            
                            break;
                        case 3:
                            peca removida;
                            peca subistituta = iniciarPeca();
                            removerPeca(&f,&removida);
                            mostrarFila(&f);
                            printf("\npeca removida %c %d",removida.nome,removida.id);
                            inserirPeca(&f,subistituta);
                            printf("\npeca adicionada %c %d",subistituta.nome,subistituta.id);
                            mostrarFila(&f);
                            break;
                        case 4:
                            if(pil.topo<maxPilha){
                                enviarFilaParaPilha(&f, &pil);
                                mostrarFila(&f);
                                mostrarPilha(&pil);

                            } else{
                                printf("\nPilha cheia!!\n");
                            }
                            
                            break;

                        case 5:
                            usarPilhaNaFila(&f, &pil);
                            mostrarFila(&f);
                            mostrarPilha(&pil);
                            break;

                        case 6:
                            mostrarFila(&f);
                            mostrarPilha(&pil);
                            break;
                        case 7:
                            if (trocarTresFilaPilha(&f, &pil)) {
                                mostrarFila(&f);
                                mostrarPilha(&pil);
                            }
                            break;
   
    

                            break;        
                        
                        //default:
                           // break;
                        }

      }while (opcao!=9);
   
    
    
    


    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.



    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


    return 0;
}

