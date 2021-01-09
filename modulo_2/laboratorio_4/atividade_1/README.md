# Laboratório 4 - Atividade 1

_Altere o número de threads A para 1. O que vai ocorrer na execução? O programa vai terminar? Por quê?_

A thread B sempre vai se bloquear já que a condição `x < 2` sempre vai ser satisfeita e a segunda thread A nunca vai rodar para incrementar `x` e desbloquear a thread B, então o programa nunca termina de rodar independente de como as threads A - que agora é só uma - e B se entrelacem.

