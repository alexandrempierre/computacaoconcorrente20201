# Atividade 1 - Laboratório 5

## Sobre o `sem_inanicao.c`

A política de escalonamento escolhida foi: somar a quantidade de tentativas de escritas que ocorrem durante a escrita (e decrementar caso essas escritas ocorram), somar numa variável diferente as tentativas de escrita que ocorrem durante a leitura (tentativas essas que geram bloqueio das novas tentativas de leitura), e quando acabarem as leituras concorrentes e a primeira escrita for ocorrer, somar os dois valores e usar como quantidade mínima de escritas a serem feitas antes da próxima leitura.
