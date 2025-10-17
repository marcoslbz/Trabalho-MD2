/*
Autores: 
Marcos Vinícius Lima Bezerra - 211062698, 
Caio Melo Borges - 211030952
*/

#include <stdio.h>
#include <math.h>

int main() {
    int N;
    printf("Insira o valor N (1<= N <= 105): ");
    scanf("%d", &N);
    if(N < 1 || N > 105){
        printf("Valor invalido! N deve ser entre 1 e 105");
        printf("Autores:\nMarcos Vinicius Lima Bezerra - 211062698\nCaio Melo Borges - 211030952");
        return 1;
    }

    printf("Fatoracao de %d:\n", N);
    
    int temp = N;
    int factors[100][2]; 
    int count = 0;
    
    
    for (int p = 2; p * p <= temp; p++) {
        if (temp % p == 0) {
            factors[count][0] = p;
            factors[count][1] = 0;
            while (temp % p == 0) {
                factors[count][1]++;
                temp /= p;
            }
            count++;
        }
    }
    if (temp > 1) {
        factors[count][0] = temp;
        factors[count][1] = 1;
        count++;
    }

    // Imprimir fatores primos e expoentes
    for (int i = 0; i < count; i++) {
        printf("Primo: %d, Expoente: %d\n", factors[i][0], factors[i][1]);
    }

    // Cálculo de tau(N)
    int tau = 1;
    for (int i = 0; i < count; i++) {
        tau *= (factors[i][1] + 1);
    }
    printf("tau(%d) = %d\n", N, tau);

    // Cálculo de sigma(N)
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
    printf("sigma(%d) = %d\n", N, sigma);

    // Cálculo da Razão de Eficiência
    double razao = (double)sigma / tau;
    printf("Razao de Eficiencia = %.2f\n", razao);

    printf("Autores:\nMarcos Vinicius Lima Bezerra - 211062698\nCaio Melo Borges");

    return 0;
}