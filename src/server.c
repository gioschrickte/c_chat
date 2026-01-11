#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"

void error(const char *msg) { // Função para erro que mostra uma mensagem msg
    perror(msg); // Interpreta o numero do erro e mostra um output padrão de erro
    exit(1);
}

int main(int argc, char *argv[]) { // Serão 2 parametros: nome do arquivo e numero da porta
    if (argc < 2) {
        fprintf(stderr,"ERRO: Número da porta nao definido\n");
        exit(1);
    }

    int sockfd, newsockfd, portno, n;

    char buffer[255]; // buffer para as mensagens
    struct sockaddr_in serv_addr, cli_addr; // Struct para o endereço de internet
    socklen_t clilen; // 32 bits

    // Aqui, criaremos um File Descripter para o arquivo de Rede que a função Socket() retornará
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("Erro ao abrir Socket");
    }

    // Vamos limpar os bytes alocados para o endereço do host
    memset(&serv_addr, 0, sizeof(serv_addr));
    portno = atoi(argv[1]); // Define o número da porta

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    /* Sobre htons: portno está definida como 8080 (argv[1]), em hexadecimal 8080 é 0x1F90. Esse número
     * precisa de 2 bytes para ser armazenado: o byte 1F e o byte 90. Como o PC (Intel/AMD) é Little Endian,
     * o processador irá salvar o byte menos significativo primeiro (90). Porém, a internet é big endian e interpreta
     * o mais significativo (1F) primeiro. A função htons então deixa os bytes na maneira interpretada pela internet (internet order).
     * HTONS = Host To Internet Short */

    /* Quando o socket foi criado, ele apenas existe um domínio de nome (address family), mas não há um endereço vinculado a ele.
     * Como temos um endereço de rede local configurado (serv_addr), podemos usar bind para vincula o endereço espeçificado por
     * serv_addr para o socket em sockfd. */

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("Falha no Binding.\n");

    int opt = 1;

    // Configura o socket para permitir o reuso imediato da porta, isso pode prejudicar o protocolo tcp
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        error("Erro no setsockopt");
    }

    listen(sockfd, 5); // 5 é o numero máximo de clientes que podem se conectar ao servidor
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen); // typecasting de (sockaddr_in*) para (sockaddr*)

    if (newsockfd < 0)
        error("Erro em Accept()");

    printf("Conexão com cliente recebida!\n");

    while (1) {
        bzero(buffer, 255); // limpa o buffer
        n = read(newsockfd, buffer, 255);
        if (n < 0)
            error("Erro na leitura.");
        printf("Client : %s", buffer);
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);

        n = write(newsockfd, buffer, strlen(buffer));
        if (n<0)
            error("Erro no envio.");

        int i = strncmp("Adeus", buffer, 5);
        if (!i)
            break;
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}