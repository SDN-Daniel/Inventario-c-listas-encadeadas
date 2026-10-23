# Sistema de Inventário em C com Listas Encadeadas

Este projeto é uma aplicação interativa de console desenvolvida na linguagem C que simula o gerenciamento de uma "Mochila de Sobrevivência". O objetivo principal da aplicação é demonstrar o domínio prático sobre estruturas de dados dinâmicas, operando inteiramente através de **Listas Encadeadas Simples** (Singly Linked Lists).

---

## 🚀 Funcionalidades

* **Adicionar Item:** Criação de novos nós contendo nome, tipo e quantidade. A inserção é feita percorrendo a lista até o final, respeitando o limite estrutural (10 itens).
* **Remover Item:** Remoção segura de itens com base em busca por nome. O algoritmo identifica se o alvo é o primeiro nó (cabeça) ou um nó intermediário/final, refazendo a "costura" dos ponteiros e liberando a memória isolada.
* **Busca Sequencial:** Varredura da lista encadeada comparando strings (`strcmp`) para localizar itens específicos.
* **Listagem Formatada:** Exibição de todos os itens alocados em formato de tabela iterando sobre os ponteiros.

---

## 🧠 Conceitos Técnicos Aplicados

* **Alocação Dinâmica de Memória:** Uso extensivo de `malloc` para criar itens sob demanda e `free` para destruí-los, garantindo eficiência no uso da memória.
* **Prevenção de Memory Leaks:** Implementação de uma função de varredura (`liberarMemoria`) executada ao encerrar o programa, que destrói todos os nós remanescentes de forma iterativa.
* **Manipulação Avançada de Ponteiros:** Passagem de ponteiros por referência e valor, atualização dinâmica da "cabeça" da lista e religação de nós (`atual->proximo = novoItem`).
* **Tipos de Dados Customizados:** Estruturação dos nós utilizando `typedef struct` contendo arrays de caracteres, inteiros e ponteiros de autorreferência.

---

## 💻 Como Executar

**Clone o repositório:**

git clone [https://github.com/SDN-Daniel/Inventario-c-listas-encadeadas.git](https://github.com/SDN-Daniel/Inventario-c-listas-encadeadas.git)

**Abra no Visual Studio:**

Abra o Visual Studio

Selecione "Continuar sem código" (Continue without code).

Vá em Arquivo (File) > Abrir (Open) > Ficheiro (File)... e selecione o arquivo .c clonado.

Alternativa: Crie um novo "Projeto Vazio" (Empty Project) em C++, adicione um novo arquivo .c na pasta Source Files e cole o código.

Compile e Execute:

Pressione Ctrl + F5 para compilar e iniciar a aplicação no terminal sem o modo de depuração anexado.

---

##👨‍💻 Autor

Desenvolvido por Daniel Santos do Nascimento.

GitHub: https://github.com/SDN-Daniel

Este projeto foi desenvolvido para fins de estudo e aprimoramento de habilidades em programação C, com foco em estruturas de dados dinâmicas com gerenciamento de memória e listas encadeadas.
