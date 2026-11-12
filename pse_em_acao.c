#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define MAX_ACOES 100
#define ARQUIVO_DADOS "acoes_pse.txt"

struct tp_acao {
    int codigo;
    char escola[100];
    char tema[100];
    char dataPrevista[11];
    char publicoAlvo[100];
    char responsavel[100];
    int quantidadePrevista;
    int situacao;            
    int quantidadeEfetiva;
};

struct tp_acao acoes[MAX_ACOES];
int prox = 0;
int sair = 0;

void lerLinha(char linha[], int tamanho) {
    int caractere;
    int comprimento;

    if (fgets(linha, tamanho, stdin) == NULL) {
        printf("\nEntrada encerrada. Finalizando o programa.\n");
        exit(0);
    }

    comprimento = (int)strlen(linha);
    if (comprimento > 0 && linha[comprimento - 1] == '\n') {
        linha[comprimento - 1] = '\0';
    } else {
        while ((caractere = getchar()) != '\n' && caractere != EOF) {
        }
    }
}

int lerInteiro(const char mensagem[], int minimo, int maximo) {
    char linha[100];
    char sobra;
    long numero;

    while (1) {
        printf("%s", mensagem);
        lerLinha(linha, sizeof(linha));

        if (sscanf(linha, "%ld %c", &numero, &sobra) == 1 &&
            numero >= minimo && numero <= maximo) {
            return (int)numero;
        }

        printf("Entrada invalida! Digite um numero entre %d e %d.\n", minimo, maximo);
    }
}

void lerTextoObrigatorio(const char mensagem[], char destino[], int tamanho) {
    char linha[300];
    int inicio, fim, i;

    while (1) {
        printf("%s", mensagem);
        lerLinha(linha, sizeof(linha));

        inicio = 0;
        while (linha[inicio] != '\0' && isspace((unsigned char)linha[inicio])) {
            inicio++;
        }

        fim = (int)strlen(linha) - 1;
        while (fim >= inicio && isspace((unsigned char)linha[fim])) {
            fim--;
        }

        if (fim < inicio) {
            printf("Campo obrigatorio! Digite uma informacao valida.\n");
            continue;
        }

        if (fim - inicio + 1 >= tamanho) {
            printf("Texto muito longo! Limite de %d caracteres.\n", tamanho - 1);
            continue;
        }

        for (i = 0; i <= fim - inicio; i++) {
            destino[i] = linha[inicio + i];
        }
        destino[fim - inicio + 1] = '\0';
        return;
    }
}

int dataValida(const char data[]) {
    int i, dia, mes, ano, maximoDia;
    int diasMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (strlen(data) != 10 || data[2] != '/' || data[5] != '/') {
        return 0;
    }

    for (i = 0; i < 10; i++) {
        if (i != 2 && i != 5 && !isdigit((unsigned char)data[i])) {
            return 0;
        }
    }

    sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano);
    if (ano < 1 || mes < 1 || mes > 12) {
        return 0;
    }

    maximoDia = diasMes[mes];
    if (mes == 2 && ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0)) {
        maximoDia = 29;
    }

    return dia >= 1 && dia <= maximoDia;
}

void lerData(char destino[]) {
    while (1) {
        lerTextoObrigatorio("Data prevista (DD/MM/AAAA): ", destino, 11);
        if (dataValida(destino)) {
            return;
        }
        printf("Data invalida! Informe uma data real no formato DD/MM/AAAA.\n");
    }
}

int buscarPorCodigo(int codigo) {
    int i;
    for (i = 0; i < prox; i++) {
        if (acoes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}
int contemTexto(const char texto[], const char busca[]) {
    int i, j;
    int tamanhoTexto = (int)strlen(texto);
    int tamanhoBusca = (int)strlen(busca);

    if (tamanhoBusca == 0) {
        return 1;
    }
    for (i = 0; i <= tamanhoTexto - tamanhoBusca; i++) {
        for (j = 0; j < tamanhoBusca; j++) {
            if (tolower((unsigned char)texto[i + j]) !=
                tolower((unsigned char)busca[j])) {
                break;
            }
        }
        if (j == tamanhoBusca) {
            return 1;
        }
    }
    return 0;
}

const char *nomeSituacao(int situacao) {
    if (situacao == 1) return "Planejada";
    if (situacao == 2) return "Realizada";
    return "Cancelada";
}

void mostrarAcao(int i) {
    printf("\n========== ACAO %d ==========\n", acoes[i].codigo);
    printf("Codigo: %d\n", acoes[i].codigo);
    printf("Escola: %s\n", acoes[i].escola);
    printf("Tema: %s\n", acoes[i].tema);
    printf("Data prevista: %s\n", acoes[i].dataPrevista);
    printf("Publico-alvo: %s\n", acoes[i].publicoAlvo);
    printf("Responsavel: %s\n", acoes[i].responsavel);
    printf("Participantes previstos: %d\n", acoes[i].quantidadePrevista);
    printf("Situacao: %s\n", nomeSituacao(acoes[i].situacao));
    printf("Participantes efetivos: %d\n", acoes[i].quantidadeEfetiva);
}

int salvarAcoes() {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "w");
    int i;
    int erro;

    if (arquivo == NULL) {
        printf("ERRO: nao foi possivel abrir %s para salvar.\n", ARQUIVO_DADOS);
        return 0;
    }

    fprintf(arquivo, "%d\n", prox);
    for (i = 0; i < prox; i++) {
        fprintf(arquivo, "%d\n", acoes[i].codigo);
        fprintf(arquivo, "%s\n", acoes[i].escola);
        fprintf(arquivo, "%s\n", acoes[i].tema);
        fprintf(arquivo, "%s\n", acoes[i].dataPrevista);
        fprintf(arquivo, "%s\n", acoes[i].publicoAlvo);
        fprintf(arquivo, "%s\n", acoes[i].responsavel);
        fprintf(arquivo, "%d\n", acoes[i].quantidadePrevista);
        fprintf(arquivo, "%d\n", acoes[i].situacao);
        fprintf(arquivo, "%d\n", acoes[i].quantidadeEfetiva);
    }

    erro = ferror(arquivo);
    if (fclose(arquivo) != 0) {
        erro = 1;
    }
    if (erro) {
        printf("ERRO: nao foi possivel concluir o salvamento dos dados.\n");
        return 0;
    }
    return 1;
}

int lerTextoArquivo(FILE *arquivo, char destino[], int tamanho) {
    char linha[512];
    int comprimento, c;

    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        return 0;
    }
    comprimento = (int)strlen(linha);
    if (comprimento > 0 && linha[comprimento - 1] == '\n') {
        linha[comprimento - 1] = '\0';
        comprimento--;
    } else if (!feof(arquivo)) {
        while ((c = fgetc(arquivo)) != '\n' && c != EOF) {
        }
        return 0;
    }
    if (comprimento >= tamanho) {
        return 0;
    }
    strcpy(destino, linha);
    return 1;
}


int lerNumeroArquivo(FILE *arquivo, int *numero) {
    char linha[60];
    char sobra;
    if (!lerTextoArquivo(arquivo, linha, sizeof(linha))) {
        return 0;
    }
    return sscanf(linha, "%d %c", numero, &sobra) == 1;
}


void carregarAcoes() {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "r");
    struct tp_acao carregadas[MAX_ACOES];
    int quantidade, i, j, valido = 1;

    if (arquivo == NULL) {
        printf("Nenhum arquivo anterior encontrado. Cadastro iniciado vazio.\n");
        return;
    }

    if (!lerNumeroArquivo(arquivo, &quantidade) ||
        quantidade < 0 || quantidade > MAX_ACOES) {
        valido = 0;
    }

    for (i = 0; valido && i < quantidade; i++) {
        struct tp_acao *atual = &carregadas[i];
        if (!lerNumeroArquivo(arquivo, &atual->codigo) ||
            !lerTextoArquivo(arquivo, atual->escola, sizeof(atual->escola)) ||
            !lerTextoArquivo(arquivo, atual->tema, sizeof(atual->tema)) ||
            !lerTextoArquivo(arquivo, atual->dataPrevista, sizeof(atual->dataPrevista)) ||
            !lerTextoArquivo(arquivo, atual->publicoAlvo, sizeof(atual->publicoAlvo)) ||
            !lerTextoArquivo(arquivo, atual->responsavel, sizeof(atual->responsavel)) ||
            !lerNumeroArquivo(arquivo, &atual->quantidadePrevista) ||
            !lerNumeroArquivo(arquivo, &atual->situacao) ||
            !lerNumeroArquivo(arquivo, &atual->quantidadeEfetiva)) {
            valido = 0;
            break;
        }
        if (atual->codigo < 1 || atual->codigo > 999999 ||
            atual->escola[0] == '\0' || atual->tema[0] == '\0' ||
            !dataValida(atual->dataPrevista) ||
            atual->publicoAlvo[0] == '\0' || atual->responsavel[0] == '\0' ||
            atual->quantidadePrevista < 0 || atual->quantidadePrevista > 1000000 ||
            atual->situacao < 1 || atual->situacao > 3 ||
            atual->quantidadeEfetiva < 0 || atual->quantidadeEfetiva > 1000000 ||
            (atual->situacao != 2 && atual->quantidadeEfetiva != 0)) {
            valido = 0;
        }
        for (j = 0; j < i; j++) {
            if (carregadas[j].codigo == atual->codigo) {
                valido = 0;
            }
        }
    }
    fclose(arquivo);

    if (!valido) {
        printf("AVISO: arquivo %s invalido; os dados nao foram carregados.\n", ARQUIVO_DADOS);
        printf("Preserve o arquivo para revisar antes de cadastrar novas acoes.\n");
        
        exit(1);
    }

    for (i = 0; i < quantidade; i++) {
        acoes[i] = carregadas[i];
    }
    prox = quantidade;
    printf("%d acao(oes) recuperada(s) do arquivo %s.\n", prox, ARQUIVO_DADOS);
}

void menu() {
	system("CLS");
    printf("\n========== PSE EM ACAO ==========\n");
    printf("01 - Cadastrar acao\n");
    printf("02 - Listar acoes\n");
    printf("03 - Pesquisar acao\n");
    printf("04 - Atualizar situacao\n");
    printf("05 - Registrar participantes\n");
    printf("06 - Exibir resumo geral\n");
    printf("00 - Sair do sistema\n");
}

void cadastrarAcao() {
    int codigo;
    struct tp_acao nova;

    printf("\n===== CADASTRAR ACAO =====\n");
    if (prox >= MAX_ACOES) {
        printf("Limite de armazenamento atingido! Maximo de %d acoes.\n", MAX_ACOES);
        return;
    }

    do {
        codigo = lerInteiro("Codigo da acao (1 a 999999): ", 1, 999999);
        if (buscarPorCodigo(codigo) != -1) {
            printf("Codigo ja cadastrado! Digite outro codigo.\n");
        }
    } while (buscarPorCodigo(codigo) != -1);

    nova.codigo = codigo;
    lerTextoObrigatorio("Escola: ", nova.escola, sizeof(nova.escola));
    lerTextoObrigatorio("Tema: ", nova.tema, sizeof(nova.tema));
    lerData(nova.dataPrevista);
    lerTextoObrigatorio("Publico-alvo: ", nova.publicoAlvo, sizeof(nova.publicoAlvo));
    lerTextoObrigatorio("Responsavel: ", nova.responsavel, sizeof(nova.responsavel));
    nova.quantidadePrevista = lerInteiro("Quantidade prevista de participantes: ", 0, 1000000);
    printf("Situacao inicial: 1 - Planejada | 2 - Realizada | 3 - Cancelada\n");
    nova.situacao = lerInteiro("Digite a situacao inicial: ", 1, 3);
    nova.quantidadeEfetiva = 0;

    acoes[prox] = nova;
    prox++;
    printf("Acao cadastrada com sucesso! Total de acoes: %d\n", prox);
    if (nova.situacao == 2) {
        printf("Utilize a opcao 5 para registrar os participantes efetivos.\n");
    }
    system("pause");
}

void listarAcoes() {
    int i;
    printf("\n===== LISTAR ACOES =====\n");
    if (prox == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    printf("Total de acoes cadastradas: %d\n", prox);
    for (i = 0; i < prox; i++) {
        mostrarAcao(i);
    }
    system("pause");
}

void pesquisarAcao() {
    int tipo, codigo, i, encontrado = 0;
    char busca[100];

    printf("\n===== PESQUISAR ACAO =====\n");
    if (prox == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    printf("01 - Pesquisar por codigo\n");
    printf("02 - Pesquisar por escola\n");
    printf("03 - Pesquisar por tema\n");
    tipo = lerInteiro("Digite uma opcao: ", 1, 3);

    if (tipo == 1) {
        codigo = lerInteiro("Digite o codigo: ", 1, 999999);
        i = buscarPorCodigo(codigo);
        if (i != -1) {
            mostrarAcao(i);
            encontrado = 1;
        }
    } else {
        if (tipo == 2) {
            lerTextoObrigatorio("Digite o nome da escola (ou parte): ", busca, sizeof(busca));
        } else {
            lerTextoObrigatorio("Digite o tema (ou parte): ", busca, sizeof(busca));
        }

        for (i = 0; i < prox; i++) {
            if ((tipo == 2 && contemTexto(acoes[i].escola, busca)) ||
                (tipo == 3 && contemTexto(acoes[i].tema, busca))) {
                mostrarAcao(i);
                encontrado++;
            }
        }
    }

    if (encontrado == 0) {
        printf("Nenhuma acao encontrada.\n");
    } else {
        printf("\nResultado(s) encontrado(s): %d\n", encontrado);
    }
    system("pause");
}

void atualizarSituacao() {
    int codigo, indice, novaSituacao;
    printf("\n===== ATUALIZAR SITUACAO =====\n");
    if (prox == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    codigo = lerInteiro("Codigo da acao: ", 1, 999999);
    indice = buscarPorCodigo(codigo);
    if (indice == -1) {
        printf("Acao nao encontrada.\n");
        return;
    }

    printf("Situacao atual: %s\n", nomeSituacao(acoes[indice].situacao));
    printf("1 - Planejada | 2 - Realizada | 3 - Cancelada\n");
    novaSituacao = lerInteiro("Nova situacao: ", 1, 3);
    acoes[indice].situacao = novaSituacao;

    if (novaSituacao != 2) {
        acoes[indice].quantidadeEfetiva = 0;
    }
    printf("Situacao atualizada com sucesso: %s\n", nomeSituacao(novaSituacao));
    if (novaSituacao == 2) {
        printf("Para informar os participantes efetivos, utilize a opcao 5.\n");
    }
    system("pause");
}

void registrarParticipantes() {
    int codigo, indice;
    printf("\n===== REGISTRAR PARTICIPANTES =====\n");
    if (prox == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    codigo = lerInteiro("Codigo da acao: ", 1, 999999);
    indice = buscarPorCodigo(codigo);
    if (indice == -1) {
        printf("Acao nao encontrada.\n");
        return;
    }
    if (acoes[indice].situacao != 2) {
        printf("Registro nao permitido! A acao precisa estar realizada.\n");
        return;
    }

    acoes[indice].quantidadeEfetiva =
        lerInteiro("Quantidade efetiva de participantes: ", 0, 1000000);
    printf("Participantes registrados com sucesso!\n");
    system("pause");
}

void exibirResumo() {
    int i, planejadas = 0, realizadas = 0, canceladas = 0;
    long long totalPrevisto = 0, totalParticipantes = 0;
    double percentual = 0.0;

    printf("\n===== RESUMO GERAL =====\n");
    for (i = 0; i < prox; i++) {
        if (acoes[i].situacao == 1) {
            planejadas++;
        } else if (acoes[i].situacao == 2) {
            realizadas++;
            totalPrevisto += acoes[i].quantidadePrevista;
            totalParticipantes += acoes[i].quantidadeEfetiva;
        } else {
            canceladas++;
        }
        
    }

    if (totalPrevisto > 0) {
        percentual = (double)totalParticipantes * 100.0 / totalPrevisto;
    }

    printf("Total de acoes cadastradas: %d\n", prox);
    printf("Acoes planejadas: %d\n", planejadas);
    printf("Acoes realizadas: %d\n", realizadas);
    printf("Acoes canceladas: %d\n", canceladas);
    printf("Participantes previstos (acoes realizadas): %lld\n", totalPrevisto);
    printf("Total de participantes efetivos: %lld\n", totalParticipantes);
    printf("Percentual de participacao: %.2f%%\n", percentual);
    system("pause");
}

void sairDoSistema() {
    printf("\nSaindo do sistema...\n");
    sair = 1;
}

int main() {
    int opcao;
    carregarAcoes();
    do {
        menu();
        opcao = lerInteiro("Digite uma opcao: ", 0, 6);
        switch (opcao) {
            case 1: cadastrarAcao(); break;
            case 2: listarAcoes(); break;
            case 3: pesquisarAcao(); break;
            case 4: atualizarSituacao(); break;
            case 5: registrarParticipantes(); break;
            case 6: exibirResumo(); break;
            case 0: sairDoSistema(); break;
        }
    } while (sair == 0);

    return 0;
}
