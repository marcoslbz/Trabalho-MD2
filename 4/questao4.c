#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#endif

// Função para calcular o máximo divisor comum (MDC) com exibição dos passos
int mdcComPassos(int a, int b) {
    int resto;
    // [1] O laço continua enquanto b for diferente de 0.
    while (b != 0) {
        resto = a % b;
        printf("Algoritmo de Euclides: %d mod %d = %d\n", a, b, resto);
        a = b;
        // [2] b recebe o valor do resto para a próxima iteração.
        b = resto;
    }
    printf("MDC = %d\n", a);
    return a;
}

// Função para calcular o inverso modular usando o Algoritmo de Euclides Estendido
int inversoModular(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m;

    // [3] Chamada para verificar e mostrar o cálculo do MDC.
    // O inverso só existe se mdc(a, m) == 1.
    if (mdcComPassos(a, m) != 1) {
        printf("O inverso modular nao existe.\n");
        return -1; // Retorna -1 para indicar erro
    }

    // Reinicia 'a' e 'm' para o algoritmo estendido, pois foram alterados em mdcComPassos
    a = A;
    m = B;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // [4] Se o inverso x1 for negativo, ajusta para o equivalente positivo.
    if (x1 < 0) {
        x1 += m0;
    }
    
    printf("\nSubstituindo, temos que o inverso de %d em mod %d eh %d.\n\n", A, B, x1);
    return x1;
}

// Função para calcular a potência modular (base^exp % mod) de forma eficiente
long long powMod(int base, int exp, int mod) {
    long long res = 1;
    long long b = base % mod;
    while (exp > 0) {
        // [5] Se o expoente for ímpar, multiplica o resultado pela base.
        if (exp % 2 == 1) {
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        exp >>= 1; // Equivale a exp = exp / 2
    }
    return res;
}

int main() {
#ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int H, G, Zn, x, n1;

    printf("Insira H: ");
    scanf("%d", &H);
    printf("Insira G: ");
    scanf("%d", &G);
    printf("Insira Zn: ");
    scanf("%d", &Zn);
    printf("Insira x: ");
    scanf("%d", &x);
    printf("Insira n1: ");
    scanf("%d", &n1);

    printf("\nCalculando H / G (mod Zn)\n");
    // [6] Chama a função para encontrar o inverso modular de G em Zn.
    int inverso = inversoModular(G, Zn);

    if (inverso != -1) {
        long long a = (long long)H * inverso % Zn;
        if (a < 0) { // Garante que 'a' seja positivo
            a += Zn;
        }

        printf("Fazendo a multiplicacao modular: (%d * %d) mod %d = %lld\n", H, inverso, Zn, a);
        
        printf("\nCalculando a^x (mod n1)\n");
        // [7] Chama a função de exponenciação modular.
        long long resultado = powMod(a, x, n1);

        printf("\nResultados Finais\n");
        printf("Sendo %d o inverso de %d (mod %d)\n", inverso, G, Zn);
        printf("O valor de 'a' eh: %lld\n", a);
        printf("Valor final da congruencia (a^x mod n1): %lld\n", resultado);
    }

    return 0;
}

/*

 SAÍDA E RESPOSTAS DO V OU F                     

 PARTE 1: Saída do programa com os valores H=7, G=3, Zn=11, x=10, n1=13

 Insira H: 7
 Insira G: 3
 Insira Zn: 11
 Insira x (expoente): 10
 Insira n1 (modulo final): 13

 - Calculando H / G (mod Zn)
 Algoritmo de Euclides: 11 mod 3 = 2
 Algoritmo de Euclides: 3 mod 2 = 1
 Algoritmo de Euclides: 2 mod 1 = 0
 MDC = 1

 Substituindo, temos que o inverso de 3 em mod 11 eh 4.

 Fazendo a multiplicacao modular: (7 * 4) mod 11 = 6

- Calculando a^x (mod n1)

 - Resultados Finais
 Sendo 4 o inverso de 3 (mod 11)
 O valor de 'a' eh: 6
 Valor final da congruencia (a^x mod n1): 4


 PARTE 2: Respostas das afirmativas de Verdadeiro (V) ou Falso (F)


 (V) O algoritmo de Euclides estendido é utilizado para calcular o inverso modular de um número.

 (F) Se mdc(G,Zn) != 1, o programa ainda consegue encontrar o inverso de G em Zn.

 (V) A operação `(H * inverso) % Zn` representa a divisão modular de H por G.

 (F) Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar o cálculo de a^x mod n1.

 (F) A função powMod implementa o cálculo de potência modular utilizando multiplicações diretas sem otimização.

 (V) Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0.

 (F) O cálculo de fi(n1) (função totiente de Euler) é utilizado apenas quando n1 não é primo.

*/