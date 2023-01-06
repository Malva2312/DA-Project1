# DA_T1_G47 - Projeto1

## Membros do Grupo:
- André Soares  -   up202004161
- Bruna Marques -   up202007191
- João Malva    -   up202006605

## O Problema:

### Cenário 1 - Otimização do número de estafetas
O objetivo deste cenário é minimizar o número de estafetas a utilizar para realizar o máximo (ou a totalidade) das entregas normais. 

Dados de entrada a considerar:
- Conjunto de estafetas registados (capacidade de volume e de peso)
- Conjunto de pedidos a entregar (volume e peso)

Ordenamos os estafetas por densidade e, se possível, damos ao estafeta a encomenda com mais massa ou volume, dependendo se têm mais volume ou massa. Se o valor de "tempo" for verdadeiro, então terá em conta a variável de duração de cada encomenda. Quando uma embalagem é adicionada a um estafeta, então é definida como "feita" no mapa de embalagens da empresa.


### Cenário 2 - Otimização do lucro da empresa
O objetivo é selecionar os estafetas registados na plataforma, de modo a maximizar o lucro da empresa de um determinado dia, para os pedidos naquele dia.

Dados de entrada a considerar:
- Conjunto de estafetas registados (capacidade de volume e de peso e custo)
- Conjunto de pedidos a entregar (volume, peso e recomensa)

Ordena os estafetas pela relação entre a densidade e o seu custo e, se possível, dá ao estafeta a encomenda com mais massa ou volume, dependendo se têm mais volume ou massa. Se o valor de "tempo" for verdadeiro, então terá em conta a variável duração de cada encomenda. Quando uma encomenda é adicionado a um estafeta, então é definido como "feito" no mapa de encomendas da empresa. Se a recompensa de algumas encomendas estiver abaixo de um valor mínimo que signifique que a encomenda em si não vale a pena entregar, então será descartada o que permite não utilizar tantos estafetas e melhorar o lucro.

### Cenário 3 - Otimização das entregas expresso
O objetivo é eleger as encomendas que minimizem o tempo médio previsto para as entregas expresso.

Dados de entrada a considerar:
- Conjunto de pedidos expresso (tempo estimado de entrega)


Nota: para melhor mostrar a lógica por detrás deste cenário, consideramos cada embalegem no conjunto de dados como um expresso, o que significa que nem todas serão entregues num dia e, uma vez que voltam à empresa, continuarão a ser entregues nos dias seguintes Ordena as encomendas por ordem ascendente de duração, que é o que minimiza o tempo médio (mesma lógica do exercício 7 da primeira classe prática) Uma vez que as encomendas são ordenados por ordem ascendente todos os dias menos encomendas serão entregues e o tempo médio mínimo aumentará


## Experiência do Utilizador:
De modo a correr o programa é necessário aceder ao diretório "codigo" e utilizar o "CMakeLists.txt" e executar a função *main*.
Para alterar os dados de entrada é necessário alterar na função *main* as variáveis do tipo *string* que referenciam o caminho até aos ficheiros.
Foi criado um interface simples para testar as funções no código, que pode ser utilizado. É possível retroceder ao estado original dos dados por uma das opções do menu na interface (*Reset the data*) ou então voltar a executar o programa.
Visto que é simples, não está preparado para receber exceções no terminal, isto é, apenas aceita os valores corretos no terminal.

