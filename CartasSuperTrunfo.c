#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ESTADOS 8
#define CIDADES_POR_ESTADO 4

// Estrutura para armazenar os dados de uma cidade
typedef struct {
    char nome[50];
    int populacao; // população de habitantes
    float area; // area em km²
    float pib; // valor bruto em reais
    int pontos_turisticos; // quantidade de pontos turísticos
} Cidade;

int main() {
    Cidade cidades[ESTADOS][CIDADES_POR_ESTADO];
    char estados[ESTADOS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    // Coletar os dados
    for (int i = 0; i < ESTADOS; i++) {
        printf("\n== Estado %c ==\n", estados[i]);
        for (int j = 0; j < CIDADES_POR_ESTADO; j++) {
            printf("\n--- Cidade %c%d ---\n", estados[i], j + 1);

            printf("Nome da cidade: "); // Limitar a 50 caracteres
            fgets(cidades[i][j].nome, sizeof(cidades[i][j].nome), stdin);
            cidades[i][j].nome[strcspn(cidades[i][j].nome, "\n")] = '\0'; // remover '\n'

            printf("População: "); // Numeração sem digitos
            while (scanf("%d", &cidades[i][j].populacao) != 1) {
                printf("Entrada inválida. Digite um número inteiro: ");
                while (getchar() != '\n'); // limpar buffer
            }

            printf("Área (km²): "); // Incluir apenas 1 pontuação // Limitar a 1 casa decimal
            while (scanf("%f", &cidades[i][j].area) != 1) {
                printf("Entrada inválida. Digite um número decimal: ");
                while (getchar() != '\n'); // limpar buffer
            }

            printf("PIB (valor bruto em R$): "); // Incluir apenas 1 pontuação // Limitar a 1 casa decimal
            while (scanf("%f", &cidades[i][j].pib) != 1) {
                printf("Entrada inválida. Digite um número decimal: ");
                while (getchar() != '\n'); // limpar buffer
            }

            printf("Pontos Turísticos: "); // Numeração sem digitos
            while (scanf("%d", &cidades[i][j].pontos_turisticos) != 1) {
                printf("Entrada inválida. Digite um número inteiro: ");
                while (getchar() != '\n'); // limpar buffer
            }
            while (getchar() != '\n'); // limpar buffer após cada entrada
        }
    }

    // Exibir os dados com propriedades calculadas
    printf("\n===== DADOS DAS CIDADES =====\n");
    for (int i = 0; i < ESTADOS; i++) {
        for (int j = 0; j < CIDADES_POR_ESTADO; j++) {
            float densidade = 0.0f;
            float pib_per_capita = 0.0f;

            if (cidades[i][j].area > 0)
                densidade = cidades[i][j].populacao / cidades[i][j].area;

            if (cidades[i][j].populacao > 0)
                pib_per_capita = cidades[i][j].pib / cidades[i][j].populacao;

            printf("\n--- Carta %02d (%c%d) ---\n", i * CIDADES_POR_ESTADO + j + 1, estados[i], j + 1);
            printf("Estado: %c\n", estados[i]);
            printf("Código: %c%d\n", estados[i], j + 1);
            printf("Nome da cidade: %s\n", cidades[i][j].nome);
            printf("População: %d\n", cidades[i][j].populacao);
            printf("Área: %.2f km²\n", cidades[i][j].area);
            printf("PIB: R$ %.2f\n", cidades[i][j].pib);
            printf("Pontos Turísticos: %d\n", cidades[i][j].pontos_turisticos);
            printf("🔹 Densidade Populacional: %.2f hab/km²\n", densidade);
            printf("🔹 PIB per Capita: R$ %.2f\n", pib_per_capita);
        }
    }

    // Comparação de cartas
    char codigo1[3], codigo2[3];
    int i1, j1, i2, j2;

    printf("\n\n===== COMPARAÇÃO DE CARTAS =====\n");
    printf("Informe o código da primeira carta (ex: A1): ");
    scanf("%s", codigo1);
    printf("Informe o código da segunda carta (ex: H4): ");
    scanf("%s", codigo2);

    // Converter para índices
    i1 = toupper(codigo1[0]) - 'A';
    j1 = codigo1[1] - '1';
    i2 = toupper(codigo2[0]) - 'A';
    j2 = codigo2[1] - '1';

    // Validar
    if (i1 < 0 || i1 >= ESTADOS || j1 < 0 || j1 >= CIDADES_POR_ESTADO ||
        i2 < 0 || i2 >= ESTADOS || j2 < 0 || j2 >= CIDADES_POR_ESTADO) {
        printf("❌ Código(s) inválido(s).\n");
        return 1;
    }

    Cidade c1 = cidades[i1][j1];
    Cidade c2 = cidades[i2][j2];

    // Calcular propriedades derivadas
    float dens1 = c1.area > 0 ? c1.populacao / c1.area : 0;
    float dens2 = c2.area > 0 ? c2.populacao / c2.area : 0;

    float ppc1 = c1.populacao > 0 ? c1.pib / c1.populacao : 0;
    float ppc2 = c2.populacao > 0 ? c2.pib / c2.populacao : 0;

    float poder1 = c1.populacao + c1.area + c1.pib + c1.pontos_turisticos + ppc1 + (1000000 / (dens1 + 1));
    float poder2 = c2.populacao + c2.area + c2.pib + c2.pontos_turisticos + ppc2 + (1000000 / (dens2 + 1));

    // Comparações
    printf("\n🔍 Comparando %c%d vs %c%d:\n", estados[i1], j1 + 1, estados[i2], j2 + 1);

    printf("População: %s\n", c1.populacao > c2.populacao ? "1ª vence" : (c2.populacao > c1.populacao ? "2ª vence" : "Empate"));
    printf("Área: %s\n", c1.area > c2.area ? "1ª vence" : (c2.area > c1.area ? "2ª vence" : "Empate"));
    printf("PIB: %s\n", c1.pib > c2.pib ? "1ª vence" : (c2.pib > c1.pib ? "2ª vence" : "Empate"));
    printf("Pontos Turísticos: %s\n", c1.pontos_turisticos > c2.pontos_turisticos ? "1ª vence" : (c2.pontos_turisticos > c1.pontos_turisticos ? "2ª vence" : "Empate"));
    printf("PIB per Capita: %s\n", ppc1 > ppc2 ? "1ª vence" : (ppc2 > ppc1 ? "2ª vence" : "Empate"));
    printf("Densidade Populacional: %s\n", dens1 < dens2 ? "1ª vence" : (dens2 < dens1 ? "2ª vence" : "Empate"));

    // Super poder
    printf("\n⚡ Super Poder da 1ª Carta: %.2f\n", poder1);
    printf("⚡ Super Poder da 2ª Carta: %.2f\n", poder2);
    printf("🏆 Resultado Final: %s\n", 
        poder1 > poder2 ? "1ª Carta VENCEU!" : (poder2 > poder1 ? "2ª Carta VENCEU!" : "Empate"));

    return 0;
}
