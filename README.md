# Sistema de Mercado para Panificadora

## 📌 Descrição do Projeto

Este projeto é um sistema de mercado desenvolvido em **linguagem C**, projetado para atender às necessidades de uma panificadora. O sistema gerencia o estoque, realiza cálculos de desconto e juros, e gera recibos de compras em formato **.txt**. O objetivo é oferecer um controle eficiente das vendas e dos produtos disponíveis.

## 🔧 Funcionalidades Principais

### 🛒 Controle de Estoque
- Cadastro e listagem de produtos disponíveis.
- Atualização automática do estoque após cada venda.
- Registro dos produtos no arquivo `stock.txt`.

### 💰 Calculadora de Desconto e Juros
- Aplicação de descontos para clientes fiéis.
- Cálculo de juros em caso de compras parceladas.

### 🧾 Geração de Recibo
- Após cada compra, o sistema gera um **recibo detalhado** e salva em um arquivo `.txt`.
- O recibo contém a lista de produtos, valores individuais, descontos aplicados e valor total.

## 🛠 Estrutura do Projeto

```
/
|-- bin/Debug/                # Arquivos compilados
|-- obj/Debug/                # Objetos de depuração
|-- Lista encadeada.depend     # Dependências do projeto
|-- Lista encadeada.layout     # Arquivo de layout (possivelmente UI)
|-- README.md                 # Documentação do projeto
|-- berenice.cbp               # Arquivo de projeto Code::Blocks
|-- berenice.depend            # Arquivo de dependências
|-- berenice.layout            # Configuração do layout do projeto
|-- calculos.c                 # Módulo responsável pelos cálculos financeiros
|-- header.h                   # Arquivo de cabeçalho com funções globais
|-- main.c                     # Código principal do sistema
|-- stock.txt                  # Arquivo de controle de estoque
```

## 🚀 Como Compilar e Executar

1. **Clone o repositório:**
   ```sh
   git clone https://github.com/seu-usuario/nome-do-repositorio.git
   ```
2. **Abra o projeto no Code::Blocks** ou em outro compilador C de sua preferência.
3. **Compile o código-fonte:**
   - Se estiver utilizando `gcc`:
     ```sh
     gcc main.c calculos.c -o mercado
     ```
4. **Execute o programa:**
   ```sh
   ./mercado
   ```

## 📌 Melhorias Futuras
- Implementação de uma interface gráfica simples.
- Adição de um sistema de login para segurança dos dados.
- Relatórios estatísticos de vendas.

## 📌 Autor

Projeto desenvolvido por [Seu Nome](https://github.com/leoocalegario). Caso tenha dúvidas ou sugestões, entre em contato!
