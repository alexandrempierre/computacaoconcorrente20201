# Calculadora de gradiente

Este programa calcula o gradiente de uma função num ponto usando diferenciação automática direta. O modelo usado foi o de números duais e a implementação foi usando números complexos.

### <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/17/Warning.svg/1200px-Warning.svg.png" width=20px> Aviso: este programa não calcula derivadas de funções complexas, só usa a extensão complexa para calcular a derivada de funções reais!!!

## Como usar



### Definindo suas próprias funções

Os pré-requisitos para que o arquivo `.c` no qual a função que você quer derivar está descrita são: incluir os cabeçalhos `complex.h` e `function.h`, sua função deve se chamar `f` e ter retorno do tipo `double complex`, e deve receber os seguintes parâmetros na ordem: `int domain_dim` e `double complex input_values[]`.

No fim, seu arquivo de definição de função básico sempre vai parecer com o seguinte:

```
#include <complex.h>
#include "function.h"

double complex f (int domain_dim, double complex input_values[]) {
    ...
} 
```

0. `complex.h` : precisamos desse cabeçalho para usar a implementação padrão de números complexos que seu C99 oferece
1. `function.h` : é o cabeçalho com o protótipo da função `f`
2. `int domain_dim` : é a quantidade de entradas que sua função vai receber, o nome é referência à dimensão do domínio já que o programa lida com funções de R^n em R
3. `double complex input_values[]` : é o vetor com o valor das entradas

Os nomes das variáveis `domain_dim` e `input_values` não precisam ser esses, mas a ordem sim, então reforçando: primeiro o parâmetro inteiro, depois o vetor de números complexos em ponto flutuante com precisão dupla.

### Compilando seu programa

Já que não me foi possível escrever esse programa de modo a ler as funções a serem derivadas em tempo de execução, é necessário recompilar o programa para cada função que se quiser derivar.

Pausa pra lembrar que no [README do repositório](https://github.com/alexandrempierre/computacaoconcorrente20201/blob/main/README.md) eu coloco o GCC como uma das tecnologias usadas. Meu pífio conhecimento em C não me permite dizer se os próximos parágrafos dessa seção são fáceis ou difíceis de adaptar para outros compiladores.

É muito importante lembrar que estamos falando de funções matemáticas então para grande parte das possibilidades para `f` a compilação deverá incluir a flag `-lm` (math) para permitir uso de funções matemáticas como `csqrt`, `csin`, `ccos`, `cexp` e `clog`. Também é importante não esquecer que números complexos não estão incluídos no C89/90 que é o padrão de uma compilação com o GCC, então é necessário acrescentar `-std=c99`.

Seu arquivo de saída necessariamente deve se chamar `funcao.o` (atenção ao `.o` e ao `-c` no comando de compilação mais abaixo) se você quiser usar a makefile incluída no repositório, o que ela faz é bem simples então não deve ser um problema você compilar sua função de acordo com necessidades próprias.

Uma linha completa para a compilação de um arquivo com definição de uma função que calcula a norma euclidiana de um vetor cujo arquivo de definição está no mesmo diretório que o arquivo `main.c`:

`gcc -o function.o euclidean_norm.c -std=c99 -lm -c`

Depois disso é só digitar `make main` e seguir a direção apontada pelo seu gradiente (talvez no sentido oposto se você quiser minimizar a distância).

### Rodando seu programa

#### <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/17/Warning.svg/1200px-Warning.svg.png" width=20px> Correndo o risco de ficar repetitivo: muita atenção aqui!

Esse programa tem duas etapas de entrada de dados: argumentos de linha de comando, que são o número de threads e a quantidade de entradas a serem lidas para a função; e `scanf` para cada variável de entrada da função. Isso significa um milhão de `scanf`s se seu segundo argumento de linha de comando for `1000000`. Eu tenho usado arquivos texto para alimentar os `scanf`s, então um exemplo completo de uma das minhas chamadas do programa com 3 threads e recebendo 100 entradas para a função seria:

`./main.out 3 100 < input/100.txt`

Ao final da execução você terá a avaliação do gradiente da sua função no ponto descrito pelos 100 primeiros valores nesse arquivo.

### Possibilidades para esse programa

É bastante simples adapta-lo para também dar a avaliação da função, isso é uma característica da derivação automática usando números duais: o resultado da avaliação da função num ponto é a avaliação da função e a avaliação de uma derivada direcional.

Esse programa estava sendo construído para calcular matrizes jacobianas, mas percebi muito perto do prazo que ele fazia muitas alocações e desalocações de memória nesse processo, então decidi reduzi-lo para gradiente e com isso tirei o 1/3 mais trabalhoso do código. É possível refazer essa parte adequadamente.

Alguém que manje de verdade de diferenciação automática pode tentar acrescentar o modo reverso e usar o direto só em funções com codomínio muito maior que o domínio (é onde o modo direto brilha, em oposição ao reverso que brilha quando o domínio é muito maior que o codomínio).

## <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/7/7b/Canada_Stop_sign.svg/800px-Canada_Stop_sign.svg.png" width=20px> Limitações

Uma já comentada é que esse código não foi feito para calcular derivadas de funções complexas. 

Uma outra um pouco melhor explicada abaixo é que a implementação de números complexos do C99 é bastante lenta.

O código pode ou não estar calculando as derivadas corretamente (ele está), mas o que os [testes](https://github.com/alexandrempierre/computacaoconcorrente20201/tree/main/modulo_1/trabalho/output/values) mostram é que ele dá o mesmo resultado para qualquer número de threads entre 1 (que na prática é como rodar o programa sequencial) e 8.

## Quatro palavrinhas sobre eficiência

<cite>"Complexos não tem nenhuma." - Sócrates</cite>

Sei que os números complexos do C99 sofrem um pouco em termos de velocidade na operação de divisão, pois os complexos são um par de números em ponto flutuante e qualquer um deles que se torne um `NaN` cria um problema em toda a operação a partir de qualquer ponto. Nesse trabalho parece que essa questão de eficiência também afeta bastante funções trigonométricas, mas não é tão forte com multiplicação nem soma.


## Créditos e referências

[O lugar de onde eu tirei essa ideia maluca.](https://github.com/MikeInnes/diff-zoo/blob/notebooks/forward.ipynb)

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/17/Warning.svg/1200px-Warning.svg.png" width=20px> <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/7/7b/Canada_Stop_sign.svg/800px-Canada_Stop_sign.svg.png" width=20px> Agradeço à [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Warning.svg) pelas ótimas imagens.

O [contador de tempo](https://github.com/alexandrempierre/computacaoconcorrente20201/blob/main/modulo_1/trabalho/timer.h) usado no código não foi feito por mim, recebi pronto da professora Silvana Rossetto.

Se alguém ainda estiver na dúvida, Sócrates - o filósofo grego mesmo - nunca falou nada sobre a implementação de números complexos em C99. O lance dele era mais dialético - alguns acrescentariam maiêutico também - e a formalização dos números complexos ter levado mais uns séculos para acontecer também não ajudou muito. Não vou nem comentar sobre computação eletrônica ou a linguagem de programação C.