# Quiz em C — CP3

Projeto de quiz desenvolvido em linguagem C para o checkpoint integrador.

## Estrutura

- `src/main.c`: inicia o programa, carrega os arquivos e mostra o menu.
- `src/funcoes.c`: cadastro, jogo, ranking (bubble sort) e manipulacao dos arquivos.
- `src/modulo.c`: funcao `lerResposta`, que le a letra da alternativa (A a D).
- `include/modulo.h`: structs `Pergunta` e `Jogador`.
- `include/funcoes.h`: constantes e declaracoes das funcoes.
- `data/perguntas.txt`: perguntas cadastradas.
- `data/historico.txt`: resultados das partidas.

## Como compilar

Abra o terminal na pasta principal do projeto e execute:

```bash
gcc -Wall -Wextra -Iinclude src/main.c src/funcoes.c src/modulo.c -o programa
```

No Linux:

```bash
./programa
```

No Windows:

```bash
.\programa.exe
```

## Como funciona

1. Ao iniciar, o programa carrega as perguntas e o historico dos arquivos na pasta `data`.
2. No menu, e possivel jogar, cadastrar perguntas e consultar o ranking.
3. Ao cadastrar uma pergunta, ela e salva em `perguntas.txt`.
4. Ao terminar uma partida, o resultado e salvo em `historico.txt`.
5. O ranking usa bubble sort para ordenar os jogadores pelo percentual de acertos, do maior para o menor.

## Video de demonstracao

Link do video nao listado: (https://www.youtube.com/watch?v=lv7yk85QgWs)