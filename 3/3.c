/*
Autores: 
Marcos Vinicius Lima Bezerra - 211062698, 
Caio Melo Borges - 211030952
*/

#include <stdio.h>
#include <math.h>

int main() {
    printf("Autores:\nMarcos Vinicius Lima Bezerra - 211062698\nCaio Melo Borges - 211030952\n");
    
    int N;
    printf("Insira o valor N (1<= N <= 105): ");
    scanf("%d", &N);
    
    // Validacao da entrada
    if(N < 1 || N > 105){
        printf("Valor invalido! N deve ser entre 1 e 105\n");
        printf("Autores:\nMarcos Vinicius Lima Bezerra - 211062698\nCaio Melo Borges - 211030952\n");
        return 1;
    }

    printf("Fatoracao de %d:\n", N);
    
    int temp = N;
    int factors[100][2]; // Array para armazenar fatores primos e expoentes
    int count = 0; // Contador de fatores primos
    
    // METODO: Trial Division (Divisao por Tentativa)
    // Justificativa: Para N <= 105, este metodo e suficiente e eficiente
    // Percorremos todos os numeros de 2 ate sqrt(N)
    for (int p = 2; p * p <= temp; p++) {
        if (temp % p == 0) {
            // Encontramos um fator primo
            factors[count][0] = p;
            factors[count][1] = 0;
            
            // Calculamos o expoente do fator primo
            while (temp % p == 0) {
                factors[count][1]++;
                temp /= p;
            }
            count++;
        }
    }
    
    // Se sobrou algum valor maior que 1, ele e primo
    if (temp > 1) {
        factors[count][0] = temp;
        factors[count][1] = 1;
        count++;
    }
    
    // Exibir resumo da fatoracao
    for (int i = 0; i < count; i++) {
        printf("Primo: %d, Expoente: %d\n", factors[i][0], factors[i][1]);
    }

    // === PASSO 2: CALCULO DE TAU(N) ===
    // Formula: tau(N) = produto de (expoente_i + 1)
    // Justificativa: Cada fator primo p_i^a_i contribui com (a_i + 1) divisores
    int tau = 1;
    for (int i = 0; i < count; i++) {
        tau *= (factors[i][1] + 1);
    }

    // === PASSO 3: CALCULO DE SIGMA(N) ===
    // Formula: sigma(N) = produto de soma das potencias de cada fator primo
    // Para cada fator primo p^a: soma = 1 + p + p^2 + ... + p^a
    int sigma = 1;
    for (int i = 0; i < count; i++) {
        int p = factors[i][0];
        int a = factors[i][1];
        int soma = 1;
        int power = 1;
        
        for (int j = 0; j < a; j++) {
            power *= p;
            soma += power;
        }
        sigma *= soma;
    }

    // === PASSO 4: CALCULO DA RAZAO DE EFICIENCIA ===
    // Formula: Razao = sigma(N) / tau(N)
    double razao = (double)sigma / tau;

    printf("\n=== RESULTADO FINAL ===\n");
    printf("Para N = %d:\n", N);
    printf("- tau(N) = %d\n", tau);
    printf("- sigma(N) = %d\n", sigma);
    printf("- Razao de Eficiencia = %.2f\n", razao);

    return 0;
}
