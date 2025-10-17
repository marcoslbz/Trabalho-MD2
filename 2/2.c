/*
Autores: 
Marcos Vinícius Lima Bezerra - 211062698, 
Caio Melo Borges - 211030952
*/

#include <stdio.h>

// Cálculo MDC por divisões sucessivas (Algoritmo de Euclides)
long long mdc(long long a, long long b) {
    printf("\n=== CALCULANDO MDC(%lld, %lld) ===\n", a, b);
    int passo = 1;
    while (b != 0) {
        printf("Passo %d: %lld = %lld × %lld + %lld\n", 
               passo, a, b, a/b, a%b);
        long long temp = b;
        b = a % b;
        a = temp;
        passo++;
    }
    printf("MDC = %lld\n", a);
    return a;
}

// MMC de dois números usando a relação MDC × MMC = a × b
long long mmc_two(long long a, long long b) {
    printf("\n=== CALCULANDO MMC(%lld, %lld) ===\n", a, b);
    long long mdc_val = mdc(a, b);
    long long mmc_val = (a / mdc_val) * b;
    printf("Formula: MMC = (a × b) / MDC = (%lld × %lld) / %lld = %lld\n", 
           a, b, mdc_val, mmc_val);
    return mmc_val;
}

// MMC de lista com passo a passo
long long mmc_list(long long arr[], int n) {
    printf("\n=== INICIANDO CALCULO DO MMC DA LISTA ===\n");
    long long result = arr[0];
    printf("MMC parcial inicial: %lld\n", result);
    
    for (int i = 1; i < n; i++) {
        printf("\n--- Processando chave %d (ciclo %lld) ---\n", i+1, arr[i]);
        printf("Calculando MMC entre %lld e %lld\n", result, arr[i]);
        result = mmc_two(result, arr[i]);
        printf("Novo MMC parcial: %lld\n", result);
        
        // Verifica se ultrapassou o limite
        if (result > 50) {
            printf("MMC PARCIAL ULTRAPASSOU O LIMITE DE 50 ANOS!\n");
            break;
        }
    }
    
    printf("\n=== MMC FINAL: %lld ===\n", result);
    return result;
}

int main() {
    printf("=========================================\n");
    printf("      SISTEMA DE CHAVES PERIODICAS\n");
    printf("=========================================\n");
    printf("Autores:\n- Marcos Vinicius Lima Bezerra - 211062698\n- Caio Melo Borges - 211030952\n\n");
    
    // Entrada do número de chaves
    int n;
    printf("Insira a quantidade de chaves (1-10): ");
    scanf("%d", &n);
    
    if (n < 1 || n > 10) {
        printf("ERRO: Quantidade invalida! Deve ser entre 1 e 10.\n");
        return 1;
    }
    
    // Entrada dos ciclos das chaves
    long long chaves[10];
    printf("Insira os ciclos de ativacao das chaves (2-20):\n");
    for (int i = 0; i < n; i++) {
        printf("Chave %d: ", i+1);
        scanf("%lld", &chaves[i]);

        if(chaves[i] < 2 || chaves[i] > 20){
            printf("ERRO: Ciclo invalido! Deve ser entre 2 e 20.\n");
            return 1;
        }
    }
    
    // Exibe os dados de entrada
    printf("\n=== DADOS DE ENTRADA ===\n");
    printf("Numero de chaves: %d\n", n);
    printf("Ciclos das chaves: ");
    for (int i = 0; i < n; i++) {
        printf("%lld", chaves[i]);
        if (i < n-1) printf(", ");
    }
    printf("\n");
    
    // Calcula o MMC
    long long result = mmc_list(chaves, n);
    
    // Resultado final
    printf("\n=== RESULTADO FINAL ===\n");
    if (result > 50) {
        printf("NAO HA ANO DE SINCRONIZACAO DENTRO DO LIMITE DE 50 ANOS.\n");
        printf("Motivo: MMC = %lld > 50\n", result);
    } else {
        printf("As chaves poderao ser utilizadas simultaneamente no ano: %lld\n", result);
    }
    
    printf("\n=========================================\n");
    return 0;
}