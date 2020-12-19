# Atividade 2 - Laboratório 3

## Estratégia do passo

A estratégia do passo é um nome curto para a distribuição de carga entre as threads baseadas em somar os termos saltando um número de termos igual a quantidade de threads.

### Erro

| Termos / Threads | sequencial        | 4                 |
|------------------|-------------------|-------------------|
| 1000             | 0,000999999750000 | 0,000999999749999 |
| 100000           | 0,000010000000000 | 0,000009999999993 |
| 10000000         | 0,000000100000000 | 0,000000099999884 |
| 1000000000       | 0,000000000998257 | 0,000000001000462 |

### Tempo de execução (em segundos)

| Termos / Threads | sequencial | 4        | aceleração |
|------------------|------------|----------|------------|
| 1000             | 0,000006   | 0,000806 | 0,007444   |
| 100000           | 0,000489   | 0,000875 | 0,558857   |
| 10000000         | 0,046331   | 0,014028 | 3,302752   |
| 1000000000       | 4,732841   | 1,559942 | 3,033985   |

## Estratégia do bloco

### Erro

| Termos / Threads | sequencial        | 4                 |
|------------------|-------------------|-------------------|
| 1000             | 0,000999999750000 | 0,000999999750000 |
| 100000           | 0,000010000000000 | 0,000010000000000 |
| 10000000         | 0,000000100000000 | 0,000000100000000 |
| 1000000000       | 0,000000000998257 | 0,000000001000000 |

### Tempo de execução (em segundos)

| Termos / Threads | sequencial | 4        | aceleração |
|------------------|------------|----------|------------|
| 1000             | 0,000006   | 0,000928 | 0,006466   |
| 100000           | 0,000489   | 0,001033 | 0,473379   |
| 10000000         | 0,046331   | 0,015605 | 2,968984   |
| 1000000000       | 4,732841   | 1,579469 | 2,996476   |

## Respostas

_Pergunta: Os resultados coincidem? Por que? Qual solução se aproxima mais rapidamente do valor de PI?_

Resposta: Nenhum dos resultados coincide, todas as estratégias - sequenciais ou concorrentes - dão resultados com erros diferentes. Isso acontece porque todas as estratégias mudam um pouco a ordem em que os termos são somados, resultando em truncamentos que geram diferentes valores finais. A partir das minhas observações, incluindo aí dados que não vieram para esse texto, mas estão no arquivo `pi_series.log`, as estratégias tem diferentes erros para diferentes números de termos e, no caso das concorrentes, de threads. Aparentemente as estratégias sequenciais são um pouco mais estáveis a partir de certo ponto, mas foram muito poucos experimentos e num intervalo de valores muito limitado para tirar conclusões mais definitivas.

## Conclusão

Seria necessário fazer experimentos com valores maiores e outras quantidades de threads para tornar as conclusões mais sólidas, tudo indica que dentro do intervalo pedido as estratégias sequenciais são um pouco melhores em relação a erro numérico.