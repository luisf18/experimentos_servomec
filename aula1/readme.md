# Roteiro Aula 1 - Controlador bang bang  

O controle bang bang é um controlador em malha fechada bem simples. Geralmente utiliza um sensor e um atuador que variam entre dois estados (Ligado e desligado, quente ou frio etc). É frequentemente utilizado em eletrodomésticos, como algumas cafeteiras. Nesse caso a cafereira utiliza uma resistencia ligada em seria com um reostato. Quando a temperatura esta abaixo de 100°C (por exemplo) o reostado abre o contado, desligando a resistência, que para de aquecer a água. Depois de algum tempo a temperatura cai e o contato no reostato é reestabelecido, ligando novamente a resistencia. Esse controlador simples garante que a temperatura não ultrapasse muito o valor desejada.

## Controle bang bang para seguidor de linha

Nesse experimento é utilizado esse tipo de contolador para controlar um seguidor de linha. O robô opera entre 3 estados: mover em frente, mover para esqueda e mover pra direita. Quando a linha está centralizada o robô segue em frente. Quando a linha está a direita move pra direita e quando está a esquerda move pra esquerda.

O sensor de linha foi ajustado para diferenciar digitalmente entre oque é linha e oque não é. Onde tem linha vale 1 e onde não tem vale 0.

### Item 1 - Controle usando 1 sensor

a) Configure o robô para usar 1 sensor  
b) Ajuste os valores de $V$ e $g$ para atingir a maior velocidade que conseguir sem perder a linha.  
c) Registre os valores de $V$ e $g$ e Grave o robô se movendo em uma linha reta de pelo menos 500cm  

| sensor | Me | Md | movimento |
|-|-|-|-|
| 0 | v | v | segue em frente |
| 1 | v+g | v-g | move pra direita |

### Item 2 - Controle usando 3 sensor

a) Configure o robô para usar 3 sensores.  
b) Repita os itens b) e c) do item 1 para este caso.  

| Se | Sc | Sd | Me | Md | movimento |
|-|-|-|-|-|-|
| 0 | 1 | 0 | v | v | segue em frente |
| 1 | 1 | 1 | v | v | segue em frente |
| 0 | 0 | 1 | v+g | v-g | move pra direita |
| 0 | 1 | 1 | v+g | v-g | move pra direita |
| 1 | 0 | 0 | v-g | v+g | move pra esquerda |
| 1 | 1 | 0 | v-g | v+g | move pra esquerda |

### Item 3 - Controle usando 5 sensor

a) Configure o robô para usar 3 sensores.  
b) Repita os itens b) e c) do item 1 para este caso.  

| Sensores | Me | Md | movimento |
|-|-|-|-|
| 00100 | v | v | segue em frente |
| 01110 | v | v | segue em frente |
| 11111 | v | v | segue em frente |
| 00001 | v+g | v-g | segue pra direita |
| 00010 | v+g | v-g | segue pra direita |
| 00011 | v+g | v-g | segue pra direita |
| 00110 | v+g | v-g | segue pra direita |
| 00111 | v+g | v-g | segue pra direita |
| 01111 | v+g | v-g | segue pra direita |
| 10000 | v-g | v+g | segue pra esquerda |
| 01000 | v-g | v+g | segue pra esquerda |
| 11000 | v-g | v+g | segue pra esquerda |
| 01100 | v-g | v+g | segue pra esquerda |
| 11100 | v-g | v+g | segue pra esquerda |
| 11110 | v-g | v+g | segue pra esquerda |


### Item 4

a) Compare os resultados.  
b) Com quantos sensores foi possivel atingir a maior velocidade?  
c) Com quantos sensores houve mais oscilação lateral?  
