# PSE em Ação — Sistema de Gerenciamento de Ações do Programa Saúde na Escola

**AEP — Engenharia de Software / Análise e Desenvolvimento de Sistemas — Unicesumar — 2º semestre de 2026**

**Integrantes**
- Felipe Oliveira Santos Febraio — RA 26005886-2
- João Vitor Guedes dos Santos — RA 26006557-2
- Kenzo Yasunaka Borges — RA 26014548-2

## Sobre o projeto

Aplicação acadêmica em **linguagem C**, executada em terminal, para cadastrar e acompanhar **ações coletivas** do Programa Saúde na Escola (PSE). Os exemplos destacam atividades físicas e saúde mental, mas é possível cadastrar qualquer tema do PSE.

Os registros são **fictícios e coletivos**. Não há cadastro de estudantes, diagnósticos, prontuários ou informações clínicas individuais.

## Funcionalidades do menu

| Opção | Funcionalidade |
|---|---|
| 1 | Cadastrar ação: código, escola, tema, data prevista, público-alvo, responsável, quantidade prevista e situação inicial |
| 2 | Listar ações cadastradas |
| 3 | Pesquisar por código, escola ou tema |
| 4 | Atualizar situação (planejada, realizada ou cancelada) |
| 5 | Registrar participantes efetivos, apenas em ação realizada |
| 6 | Exibir resumo de situação e percentual de participação |
| 0 | Sair |

**Regra de cálculo:** o percentual de participação considera `participantes efetivos ÷ participantes previstos nas ações realizadas × 100`. Planejadas e canceladas não entram nesse denominador. Se o total previsto for zero, exibe `0,00%`. Um percentual maior que 100% é possível quando há mais participantes que o previsto.

## Como executar no Dev-C++ (Windows)

1. Baixe ou clone este repositório.
2. Abra o **Dev-C++** e, em **Arquivo > Abrir**, selecione `pse_em_acao.c`.
3. Confirme que o arquivo está com a extensão **`.c`**, pois a atividade pede linguagem C, e não C++.
4. Utilize o comando **Executar > Compilar e Executar** (o nome do menu pode variar conforme a versão).
5. No terminal, escolha as opções numeradas do menu.

O programa não exige banco de dados nem bibliotecas externas; utiliza bibliotecas padrão da linguagem C. A compilação foi verificada com GCC em modo `-std=c99`. Para manter os cadastros entre execuções, cria automaticamente o arquivo `acoes_pse.txt` na pasta de trabalho em que o programa é executado.

**Alternativa por terminal com GCC:**

```bash
gcc -std=c99 -Wall -Wextra pse_em_acao.c -o pse_em_acao
./pse_em_acao
```

No Windows, o executável normalmente é `pse_em_acao.exe`.

## Exemplo de uso

1. Escolha `1` e cadastre uma ação com código `101`, escola fictícia "Escola Municipal do Parque", tema "Atividade fisica", data `20/11/2026`, público-alvo "Turmas do 6o ano", responsável "Equipe de Educacao Fisica", `30` participantes previstos e situação `1` (planejada).
2. Escolha `4`, informe o código `101` e a situação `2` (realizada).
3. Escolha `5`, informe o código `101` e `24` participantes efetivos.
4. Escolha `6`: o resumo apresentará **1 ação realizada e 80,00% de participação**.

## Salvamento e recuperação dos dados

- Ao cadastrar uma ação (opção 1), os dados são gravados automaticamente no arquivo de texto `acoes_pse.txt`.
- As alterações de situação (opção 4) e de participantes (opção 5) também são salvas automaticamente.
- Ao iniciar o programa novamente **pela mesma pasta de trabalho**, o arquivo é lido e os cadastros anteriores são recuperados; a listagem (opção 2) e a pesquisa (opção 3) passam a enxergá-los.
- **Importante no Dev-C++:** se o programa for executado a partir de outra pasta de trabalho, poderá criar um novo arquivo vazio nessa outra pasta. Use sempre a mesma pasta para o projeto/executável e confira a mensagem `Cadastro salvo no arquivo acoes_pse.txt` após cadastrar.
- Se a pasta não permitir gravação, uma mensagem de erro será exibida. Se o arquivo estiver danificado, o programa não o sobrescreve automaticamente.
- O arquivo de dados é gerado durante o uso, portanto não é necessário incluí-lo vazio no GitHub. Nunca use dados pessoais de estudantes nos cadastros.

## Regras e validações

- O código precisa ser inteiro positivo, sem duplicidade.
- Campos textuais obrigatórios não podem ficar vazios.
- A data segue `DD/MM/AAAA` e é conferida com o calendário, incluindo ano bissexto.
- Quantidades não podem ser negativas.
- O menu aceita somente opções de `0` a `6`.
- Há capacidade para **100 ações**; os dados ficam na memória durante a execução e são salvos em arquivo de texto.
- Não é permitido registrar participantes enquanto a situação não for `realizada`.
- Ao voltar uma ação para `planejada` ou `cancelada`, os participantes efetivos são zerados.

## Estrutura do projeto

```text
PSE_Entrega_Final/
├── pse_em_acao.c                 # Código-fonte em C
├── README.md                     # Este documento
├── documentacao/
│   ├── Relatorio_Final_PSE_2a_Etapa.docx
│   ├── Relatorio_Final_PSE_2a_Etapa.pdf
│   ├── diagrama_casos_uso.png
│   ├── fluxograma_geral.png
│   └── fluxograma_cadastro.png
├── evidencias/                  # Capturas de saída da aplicação em execução
├── testes/
│   ├── testar_pse.py             # Testes automatizados de entrada e saída
│   └── resultado_testes.txt      # Resultado verificado
└── roteiro_video.md              # Sugestão de divisão do vídeo (até 7 min)
```

## Testes

Foram executados **17 cenários automatizados**, todos aprovados, incluindo fluxo normal e entradas inválidas. Para reproduzir os testes em uma máquina com Python 3 e GCC:

```bash
python testes/testar_pse.py
```

Esse procedimento não é necessário para o uso normal do sistema. O desenvolvimento foi compilado e testado no ambiente GCC C99; recomenda-se compilar novamente no Dev-C++ utilizado em aula.

## Limitações e cuidados éticos

Os dados ficam em memória durante a execução e são salvos em arquivo de texto local para uso posterior. Não há banco de dados, login, interface gráfica nem dados clínicos individuais. O projeto não realiza diagnóstico ou recomendação médica.
