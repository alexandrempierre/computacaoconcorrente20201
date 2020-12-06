# Atividade 1 - Laboratório 1

_Há mudanças na ordem de execução das threads?_

É difícil dizer já que todas as threads imprimem a mesma frase, seria mais fácil se fosse "Hello thread X" no lugar de "Hello world". Mas há diferenças sim, no arquivo `hello.log` gravei o resultado de 100 execuções do programa compilado e pode-se perceber que em alguns acontece a criação de threads seguidamente e "Hello world"s são impressos seguidamente na sequência, isso indica que a ordem de execução das threads pode ter mudado, já que a ordem de execução em relação a thread principal mudou.