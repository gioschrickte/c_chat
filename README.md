# Chat TCP (C Sockets)

Projeto de estudo de Engenharia da Computação focado na implementação de um sistema cliente-servidor utilizando Sockets BSD em linguagem C.

O objetivo é compreender a comunicação de baixo nível, manipulação de descritores de ficheiro (file descriptors) e o protocolo TCP/IP sem o uso de bibliotecas de alto nível.

## 🛠 Tecnologias

* **Linguagem:** C (C11 Standard)
* **Bibliotecas:** `<sys/socket.h>`, `<netinet/in.h>` (Nativas do Linux/Unix)
* **Build System:** CMake
* **Ferramentas:** GCC, CLion, Git

## 📂 Estrutura do Projeto

* `src/server.c`: Código do servidor (Bind, Listen, Accept).
* `src/client.c`: Código do cliente (Connect).
* `CMakeLists.txt`: Configuração de compilação.

## 🚀 Como Compilar e Executar

Este projeto utiliza CMake, mas pode ser compilado manualmente com GCC.

### Pré-requisitos
Necessitas de um ambiente Linux (ou WSL no Windows) com compilador C instalado.

### 1. Compilar (Via Terminal/GCC)

Se estiveres a testar no portátil (Ubuntu) sem CMake:

```bash
# Compilar o Servidor
gcc src/server.c -o server

# Compilar o Cliente
gcc src/client.c -o client