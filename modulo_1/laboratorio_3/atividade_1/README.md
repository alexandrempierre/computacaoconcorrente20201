# Atividade 1 - Laboratório 1

Abaixo a tabela com os erros correspondentes a cada uma das estratégias para somar os termos da série: k crescente implica somar os termos da série do maior para o menor valor absoluto, k decrescente soma do menor para o maior valor absoluto.

| N          | k crescente       | k decrescente     | diferença         | vencedor      |
|------------|-------------------|-------------------|-------------------|---------------|
| 1000       | 0.001001000750251 | 0.000999999750000 | 0.000001001000251 | k decrescente |
| 100000     | 0.000010000099927 | 0.000010000000000 | 0.000000000099927 | k decrescente |
| 10000000   | 0.000000100000008 | 0.000000100000000 | 0.000000000000008 | k decrescente |
| 1000000000 | 0.000000000998257 | 0.000000001000000 | 0.000000000001743 | k decrescente |

É bom pontuar que essas não são as únicas estratégias possíveis para somar os termos da série se estivermos tentando minimizar o erro numérico. Outra possibilidade seria somar os termos do menor para o maior valor absoluto em blocos, ou seja, somar 10 termos e guardar o resultado, e repetir a operação até ter uma lista de resultados com 1/10 do tamanho. A abordagem descrita demanda muito mais do disco e também demora mais, quanto ao ganho em termos de erro numérico eu nada posso dizer, pois não irei implementá-la nessa atividade.