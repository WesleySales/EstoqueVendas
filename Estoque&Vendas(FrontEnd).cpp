#include <pdcurses/curses.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USUARIOS 100

typedef struct Usuario {
    char nome_usuario[50];
    char senha[50];
} Usuario;

void inicializar();
void tela_login();
void acessar_ou_cadastrar();
void menu_admin();
void menu_usuario();
void tela_estoque();
void tela_vendas();
void cadastrar_usuario();

Usuario usuarios[MAX_USUARIOS];
int quantidade_usuarios = 0;

int main() {
    inicializar();
    tela_login();
    endwin();
    return 0;
}

void inicializar() {
    initscr();
    cbreak();
    echo(); // Habilita a visualizacao do que esta sendo digitado
    keypad(stdscr, TRUE);
    curs_set(0);
}

void tela_login() {
    int escolha;
    while (1) {
        clear();
        printw("Escolha uma opcao:\n");
        printw("1. Acessar\n");
        printw("2. Cadastrar\n");
        printw("Digite sua escolha: ");
        scanw("%d", &escolha);

        if (escolha == 1) {
            acessar_ou_cadastrar();
        } else if (escolha == 2) {
            cadastrar_usuario(); // Chama a funcao de cadastro
        } else {
            printw("Opcao invalida! Pressione qualquer tecla para tentar novamente.\n");
            getch();
        }
    }
}

void cadastrar_usuario() {
    if (quantidade_usuarios >= MAX_USUARIOS) {
        printw("Numero maximo de usuarios alcancado.\n");
        getch();
        return;
    }
    
    Usuario novo_usuario;
    clear();
    printw("Tela de Cadastro\n");
    printw("Digite o nome de usuario: ");
    echo();
    scanw("%s", novo_usuario.nome_usuario);
    printw("Digite a senha: ");
    noecho();
    scanw("%s", novo_usuario.senha);
    
    // Armazenar o novo usuario no array
    usuarios[quantidade_usuarios] = novo_usuario;
    quantidade_usuarios++;
    
    clear();
    printw("Usuario cadastrado com sucesso!\n");
    printw("Pressione qualquer tecla para voltar ao menu principal.");
    getch();
}

void acessar_ou_cadastrar() {
    int escolha;
    clear();
    printw("Escolha o tipo de acesso:\n");
    printw("1. Admin\n");
    printw("2. Usuario\n");
    printw("Digite sua escolha: ");
    scanw("%d", &escolha);
    
    if (escolha == 1) {
        menu_admin();
    } else if (escolha == 2) {
        menu_usuario();
    } else {
        printw("Opcao invalida! Pressione qualquer tecla para tentar novamente.\n");
        getch();
    }
}

void menu_admin() {
    int escolha;
    while (1) {
        clear();
        printw("Menu Admin:\n");
        printw("1. Estoque\n");
        printw("2. Voltar\n");
        printw("Digite sua escolha: ");
        scanw("%d", &escolha);
        
        if (escolha == 1) {
            tela_estoque();
        } else if (escolha == 2) {
            break; // Volta para a tela anterior
        } else {
            printw("Opcao invalida! Pressione qualquer tecla para voltar.\n");
            getch();
        }
    }
}

void menu_usuario() {
    int escolha;
    while (1) {
        clear();
        printw("Menu Usuario:\n");
        printw("1. Vendas\n");
        printw("2. Voltar\n");
        printw("Digite sua escolha: ");
        scanw("%d", &escolha);
        
        if (escolha == 1) {
            tela_vendas();
        } else if (escolha == 2) {
            break; // Volta para a tela anterior
        } else {

            printw("Opcao invalida! Pressione qualquer tecla para voltar.\n");
            getch();
        }
    }
}

void tela_estoque() {
    clear();
    printw("Tela de Estoque:\n");
    printw("Funcionalidade de Estoque ainda nao implementada.\n");
    printw("Pressione qualquer tecla para voltar.\n");
    getch();
}

void tela_vendas() {
    clear();
    printw("Tela de Vendas:\n");
    printw("Funcionalidade de Vendas ainda nao implementada.\n");
    printw("Pressione qualquer tecla para voltar.\n");
    getch();
}
