//Autor: Marcos Vinícius Lima Bezerra 
//Matrícula: 211062698

#include <stdio.h>

// Cálculo MDC por divisões sucessivas
long long mdc(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// MDC de dois números
long long mmc_two(long long a, long long b) {
    return (a / mdc(a, b)) * b;
}

long long mmc_list(long long arr[], int n) {
    long long result = arr[0];
    for (int i = 1; i < n; i++) {
        result = mmc_two(result, arr[i]);
    }
    return result;
}

int main() {
    int n;
    printf("Insira a quantidade de chaves: ");
    scanf("%d", &n);
    
    if (n < 1 || n > 10) {
        printf("Quantidade inválida!\n");
        return 1;
    }
    
    long long chaves[10];
    printf("Insira os ciclos de ativação das chaves (2<= Ciclo <= 20): ");
    for (int i = 0; i < n; i++) {
        scanf("%lld", &chaves[i]);

        if(chaves[i] < 2 || chaves[i] > 20){
            printf("Valor invalido!");
            return 1;
        }
    }
    
    long long result = mmc_list(chaves, n);
    if (result > 50 )
    {
        printf("Limite de 50 anos estourado!");

    }else{

        printf("%lld\n", result);
    }
    
    printf("Autores:\nMarcos Vinicius Lima Bezerra - 211062698\nCaio Melo Borges");
    return 0;
}