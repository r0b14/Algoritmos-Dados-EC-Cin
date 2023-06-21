# Começando com a Linguagem C++

## Criando o arquivo C++
Quando estamos criando o arquivo .C++, temos duas opções para poder adicionar a extensão do arquivo.
- C++
- Cplusplus
- Cpp
Todos os três modos podem ser reconhecidos.

### Função principal - `int main` 
Assim como na linguagem C, a função `int main` precisa ser declarada para que os códigos seja executados dentro do seu escopo.
```Cpp
    int main() {

    }
```
### Inclusão de Bibliotecas
Sempre que for usar funções que ajudem e facilitem o processo de codificação, é preciso se atentar se vai necessário incluir bibliotecas.

* para entrada e saida de dados -> `iostream`

    `#include <iostream>`
### Exibindo na Tela -> Função `cout <<`.
A função `cout` vai exibir na tela a mensagem que você deseja ou algum resultado de uma função atribuida como parâmetro. Vale levar em consideração a mesma abarangência do `printf`.
- A função `cout` é uma função padrão. Todas as funções que são padrão precisam ser acomapanhadas do prefixo `standart - std`

A função para fazer a demosntração na tela é a

```Cpp
    std::cout << "Descriptions"
```
* **Quebrando linhas para exibição**
    `<< std::endl` --> insere ao final da mensagem desejada.
    ```Cpp
        int main() {
            // Tela de apresentação
            std::cout << "***********************" << std::endl;
            std::cout << "* Welcome to the game *" << std::endl;
            std::cout << "***********************" << std::endl;
    }
    ```

* **Exibindo valor da variável no texto**
    A opção de concatenação de texto com valores de variáveis.
    ```Cpp
        int value1 = 110, value2 = 220;
        cout << "O valor da variável: "<< value1 << endl;
        cout << "O valor da variável2 "<< value2 << " é referente a voltagem." << endl;
    ```

#### Removendo o prefixo `std`.
Exista a possibilidade de remover o prefixo `std` para todas as funções padrões que usamos. Exemplo, a de quebra de linha e de output de informações/dados. Para isso temos que declarar de forma inicial `using`. Essa declaração demonstra que não precisamos ficar repetindo diversas vezes a nomeclatura padrão `std`.
    
    using namespace std
- Ex:

    -- Usando o `std`
    ```Cpp
        int main() {
            // Tela de apresentação
            std::cout << "***********************" << std::endl;
            std::cout << "* Welcome to the game *" << std::endl;
            std::cout << "***********************" << std::endl;
    }
    ```
    -- Sem o uso do `std`
    ```Cpp
        using namespace std;
            int main() {
                // Tela de apresentação
                cout << "***********************" << endl;
                cout << "* Welcome to the game *" << endl;
                cout << "***********************" << endl;
            }
    ```

## Tipos de dados e suas declarações

### 🔢 Valores numéricos

**Ambas as declações usam 4bytes de alocação**

* `int` -> Para valores inteiros. *1;10000;50;-20...*

        int value1 = 110, value2 = 220;

* `float` -> Para valores reais. *1.233;12.0...*

        float value2 = 2.44;

**Declação +4bytes**

* `double` -> Para valores expressamente grandes, que ultrapassem o limite de bytes.

        double numbersize = 9999999999999999999999999999999999.999;

### 🆙 Caracteres

* `char` -> Para caracteres simples. *c;a;b;9;.;*

        char caracter = 'a';

* `char[30]` -> Para caracteres "complexos" e que precisem de 30 'espaços'

        char caracter[15] = "Robson Cruzue";

* `string` -> Para um conjunto de caracteres. *nomes, textos etc*

Formas de uso:

Esse é um dos modos mais tradicionais de uso.

        string name= "Pedro Silva";

Nesse caso é preciso usar uma biblioteca chamada `#<string>`.

        auto name= "Manoel Silva";

