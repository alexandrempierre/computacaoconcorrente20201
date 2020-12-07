# Atividade 5 - Laboratório 1

#### Roteiro e observações:

1. _Comece pensando em como dividir a tarefa de incrementar todos os elementos de um vetor entre duas threads._

Pensei em duas possibilidades: cada thread incrementa elementos alternados; cada thread incrementa uma metade. Achei a solução alternada (um pouco) mais fácil do que passar um offset pra função que vai executar a tarefa.

2. _Qual/quais argumento(s) deverá/deverão ser passado(s) para a funcção executada pelas threads?_

Usando a solução de incremento alternado eu só preciso passar a primeira posição do vetor que a thread precisa incrementar. Para a próxima posição eu só preciso somar o número de threads (2) à posição inicial.

3. _Na função `main` faça a inicialização do vetor e imprima os valores iniciais_

Aqui cabe dizer que optei por inicializar o vetor com zeros.

4. _Implemente a tarefa de cada thread_

5. _Na função thread/main imprima os valores finais do vetor_

6. _Teste seu programa_

No diretório deste arquivo haverá outro de nome `incrementa_vetor.log` com registros de execuções.

Mais uma observação, fiz o programa de forma que o tamanho do vetor a ser usado seja passado como argumento de linha de comando.

A linha de comando para gerar o `incrementa_vetor.log` foi 

```
for i in {11..99}; do printf "======= Vetor de tamanho %d ======= \n\n" $i >> incrementa_vetor.log; ./incrementa_vetor $i >> incrementa_vetor.log; printf "\n\n" >> incrementa_vetor.log; done
```