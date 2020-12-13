# Atividade 1 - Laboratório 2

#### Comparação dos tempos com 1 e 2 threads

| Dimensão/Threads | 1        | 2        | Aceleração |
|------------------|----------|----------|------------|
| 500              | 0,595 s  | 0,311 s  | 1,913      |
| 1000             | 4,887 s  | 2,602 s  | 1,878      |
| 2000             | 39,374 s | 21,403 s | 1,840      |

#### Comparação dos tempos com 1 e 4 threads

| Dimensão/Threads | 1        | 4        | Aceleração |
|------------------|----------|----------|------------|
| 500              | 0,595 s  | 0,215 s  | 2,767      |
| 1000             | 4,887 s  | 1,670 s  | 2,926      |
| 2000             | 39,374 s | 13,753 s | 2,863      |

#### Observações

A versão final do código é que guarda as matrizes A e B em vetores unidimensionais e guarda a matriz B transposta, acabei esquecendo de fazer um commit para registrar o código que usa vetores unidimensionais sem guardar a matriz transposta, mas registrei os tempos e estará disponível no repositório.

O arquivo com os tempos acima é o `matmatt.log`, atenção aos dois `t` no final do nome, o segundo `t` é de transposta.

Sobre a verificação de corretude, mantive as funções de impressão de matrizes no código e comentei as chamadas delas onde estavam sendo feitas.

Considerei que as etapas cujo tempo deveria ser medido seriam:

a. alocação e inicialização das matrizes e outras estruturas de dados
b. criação, execução e fim das threads
c. desalocação das estruturas de dados

Com isso não medi chamadas de `printf` que levam um tempo notoriamente longo.
