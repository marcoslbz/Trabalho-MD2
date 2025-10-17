/*
Autores: 
Marcos Vinícius Lima Bezerra - 211062698, 
Caio Melo Borges - 211030952
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Use long long for potentially large numbers in RSA calculations
typedef long long int lli;

// --- Function Prototypes ---

// Etapa 1 Helpers
lli euclidesMDC(lli a, lli b);
lli pollardsRho(lli n);
lli f_iter(lli x, lli n);

// Etapa 2 Helpers
lli extendedEuclidean(lli a, lli m, lli *x, lli *y);
lli modularInverse(lli a, lli m);

// Etapa 3 Helpers
lli modularPow(lli base, lli exp, lli mod, lli totient);
int isPrime(lli n);

// Main Program Logic
int main() {
    // --- ETAPA 1: FATORAÇÃO INTERATIVA ---
    printf("Autores:\nMarcos Vinicius Lima Bezerra - 211062698\nCaio Melo Borges - 211030952\n");
    printf("--- ETAPA 1: Fatoracao Interativa (Metodo p de Pollard) ---\n\n");

    lli N1, N2;
    // Solicita os dois números compostos distintos N1 e N2 [cite: 24]
    do {
        printf("Digite o primeiro numero composto N1 (3 ou 4 digitos): ");
        scanf("%lld", &N1);
    } while (N1 < 100 || N1 > 9999);

    do {
        printf("Digite o segundo numero composto N2 (3 ou 4 digitos, diferente de N1): ");
        scanf("%lld", &N2);
    } while (N2 < 100 || N2 > 9999 || N2 == N1);
    
    // Informa ao usuário sobre a condição para eficiência do método [cite: 26]
    printf("\nLembrete: Cada Ni deve ser produto de primos distintos para que o metodo p de Pollard seja eficiente.\n\n");

    printf("Fatorando N1 = %lld...\n", N1);
    lli p = pollardsRho(N1);
    
    printf("\nFatorando N2 = %lld...\n", N2);
    lli q = pollardsRho(N2);

    // Exibe claramente os valores de p e q [cite: 35]
    printf("\n--- Definicao dos primos RSA ---\n");
    printf("Fator p encontrado de N1: %lld\n", p);
    printf("Fator q encontrado de N2: %lld\n", q);
    printf("---------------------------------\n\n");

    // --- ETAPA 2: GERAÇÃO DAS CHAVES RSA ---
    printf("--- ETAPA 2: Geracao das Chaves RSA ---\n\n");
    
    // Cálculo do módulo n [cite: 39]
    lli n = p * q;
    printf("1. Calculo do modulo (n = p * q):\n");
    printf("   n = %lld * %lld = %lld\n\n", p, q, n);

    // Totiente de Euler z(n) [cite: 40]
    lli z_n = (p - 1) * (q - 1);
    printf("2. Calculo do Totiente de Euler (z(n) = (p-1)*(q-1)):\n");
    printf("   z(n) = (%lld - 1) * (%lld - 1) = %lld\n\n", p, q, z_n);

    // Escolha do expoente público E [cite: 41]
    lli E = 0;
    printf("3. Escolha do expoente publico (E):\n");
    printf("   Procurando o menor E > 1 e E < n tal que mdc(E, z(n)) = 1...\n");
    for (lli i = 2; i < z_n; i++) {
        if (euclidesMDC(i, z_n) == 1) {
            E = i;
            break;
        }
    }
    printf("   Expoente publico E encontrado: %lld\n\n", E);

    // Cálculo do expoente privado D [cite: 42]
    printf("4. Calculo do expoente privado (D):\n");
    printf("   Utilizando o Algoritmo Estendido de Euclides para encontrar o inverso modular de E em relacao a z(n).\n");
    lli D = modularInverse(E, z_n);
    printf("   Inverso modular de %lld (mod %lld) eh: %lld\n", E, z_n, D);
    printf("   Expoente privado D: %lld\n\n", D);

    // Impressão das chaves [cite: 44]
    printf("--- Chaves RSA Geradas ---\n");
    printf("Chave Publica: (n, E) = (%lld, %lld)\n", n, E); // [cite: 45]
    printf("Chave Privada: (n, D) = (%lld, %lld)\n", n, D); // [cite: 46]
    printf("--------------------------\n\n");

    // --- ETAPA 3: CODIFICAÇÃO E DECODIFICAÇÃO ---
    printf("--- ETAPA 3: Codificacao e Decodificacao ---\n\n");

    char mensagem[256];
    printf("Digite a mensagem para criptografar (letras maiusculas, sem acentos): ");
    getchar(); // Limpa o buffer do teclado
    fgets(mensagem, sizeof(mensagem), stdin);
    mensagem[strcspn(mensagem, "\n")] = 0; // Remove a nova linha

    // Pré-Codificação [cite: 50]
    char pre_codificada[512] = "";
    printf("\n1. Pre-codificacao da mensagem (A=11, B=12, ..., Z=36, Espaco=00):\n   ");
    for (int i = 0; i < strlen(mensagem); i++) {
        char buffer[4];
        if (mensagem[i] >= 'A' && mensagem[i] <= 'Z') {
            sprintf(buffer, "%d", mensagem[i] - 'A' + 11);
        } else if (mensagem[i] == ' ') {
            sprintf(buffer, "00");
        } else {
            // Ignora outros caracteres, conforme observação [cite: 66]
            continue; 
        }
        strcat(pre_codificada, buffer);
        printf("%s ", buffer);
    }
    printf("\nMensagem pre-codificada: %s\n\n", pre_codificada);

    // Codificação (Criptografia) [cite: 51]
    printf("2. Criptografia (C = M^E mod n):\n");
    int len = strlen(pre_codificada);
    lli encrypted_blocks[(len + 1) / 2];
    int block_count = 0;

    for (int i = 0; i < len; i += 2) {
        char bloco_str[3] = {pre_codificada[i], pre_codificada[i+1], '\0'};
        lli M = atoll(bloco_str);
        
        printf("   - Criptografando bloco M = %lld:\n", M);
        lli C = modularPow(M, E, n, z_n);
        encrypted_blocks[block_count] = C;
        printf("     C = %lld^%lld mod %lld = %lld\n\n", M, E, n, C);
        block_count++;
    }
    printf("   Mensagem Cifrada (blocos): ");
    for(int i = 0; i < block_count; i++) {
        printf("%lld ", encrypted_blocks[i]);
    }
    printf("\n\n");

    // Decodificação (Descriptografia) [cite: 54]
    printf("3. Descriptografia (M = C^D mod n):\n");
    char decrypted_message[512] = "";

    for (int i = 0; i < block_count; i++) {
        lli C = encrypted_blocks[i];
        printf("   - Descriptografando bloco C = %lld:\n", C);
        lli M_dec = modularPow(C, D, n, z_n);
        
        printf("     M = %lld^%lld mod %lld = %lld\n\n", C, D, n, M_dec);
        
        // Reconversão numérica em texto [cite: 56]
        if (M_dec == 0) {
            strcat(decrypted_message, " ");
        } else if (M_dec >= 11 && M_dec <= 36) {
            char letra[2] = {(char)(M_dec - 11 + 'A'), '\0'};
            strcat(decrypted_message, letra);
        }
    }

    printf("--- RESULTADO FINAL ---\n");
    printf("Mensagem Original: %s\n", mensagem);
    printf("Mensagem Decifrada: %s\n", decrypted_message);

    // Confirmação de que a mensagem decifrada é idêntica à original [cite: 76]
    if (strcmp(mensagem, decrypted_message) == 0) {
        printf("\nConfirmacao: A mensagem decifrada e identica a original.\n");
    } else {
        printf("\nErro: A mensagem decifrada NAO e identica a original.\n");
    }

    return 0;
}


// --- Function Implementations ---

/**
 * @brief Calcula o Máximo Divisor Comum (MDC) usando o Algoritmo de Euclides.
 * [cite: 36]
 */
lli euclidesMDC(lli a, lli b) {
    lli resto;
    // Exibe o passo a passo do cálculo do MDC [cite: 71]
    while (b != 0) {
        resto = a % b;
        printf("     MDC Step: %lld mod %lld = %lld\n", a, b, resto);
        a = b;
        b = resto;
    }
    return a;
}

/**
 * @brief Função de iteração g(x) = (x^2 + 1) mod n para o método de Pollard.
 * [cite: 28]
 */
lli f_iter(lli x, lli n) {
    return ((x * x) + 1) % n;
}

/**
 * @brief Encontra um fator primo de n usando o método p de Pollard.
 * [cite: 27]
 */
lli pollardsRho(lli n) {
    if (n % 2 == 0) return 2;
    
    lli x1 = 2; // Semente x0=2 [cite: 29]
    lli x2 = 2;
    lli d = 1;
    int iter = 1;

    printf("   Iteracoes do metodo p de Pollard:\n"); // [cite: 70]
    while (d == 1) {
        x1 = f_iter(x1, n);
        x2 = f_iter(f_iter(x2, n), n);
        lli diff = llabs(x1 - x2);
        
        printf("   Iter %d: x1=%lld, x2=%lld, |x1-x2|=%lld\n", iter++, x1, x2, diff);
        printf("   Calculando mdc(%lld, %lld)...\n", diff, n);
        d = euclidesMDC(diff, n); // [cite: 30]
        
        if (d == n) {
             printf("   Fator nao trivial nao encontrado. Tentando novamente com outra semente (nao implementado no escopo do trabalho).\n");
             return -1; // Falha
        }
    }
    printf("   Fator encontrado: %lld\n", d);
    return d;
}

/**
 * @brief Algoritmo Estendido de Euclides para encontrar o inverso modular.
 * [cite: 43, 72]
 */
lli extendedEuclidean(lli a, lli m, lli *x, lli *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return m;
    }
    lli x1, y1;
    lli gcd = extendedEuclidean(m % a, a, &x1, &y1);
    *x = y1 - (m / a) * x1;
    *y = x1;
    return gcd;
}

/**
 * @brief Calcula o inverso modular de 'a' modulo 'm'.
 */
lli modularInverse(lli a, lli m) {
    lli x, y;
    lli g = extendedEuclidean(a, m, &x, &y);
    if (g != 1) {
        printf("Inverso modular nao existe!");
        exit(1);
    }
    // Garante que o resultado seja positivo
    return (x % m + m) % m;
}

/**
 * @brief Verifica se um número é primo (helper para a escolha do teorema).
 */
int isPrime(lli n) {
    if (n <= 1) return 0;
    for (lli i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

/**
 * @brief Calcula (base^exp) % mod usando exponenciação modular e
 * seleciona o teorema apropriado para redução de expoente.
 * [cite: 58, 59, 60]
 */
lli modularPow(lli base, lli exp, lli mod, lli totient) {
    lli reduced_exp = exp;
    
    // Verificação das condições e seleção automática do método [cite: 60]
    if (isPrime(mod)) {
        // Pequeno Teorema de Fermat, se n for primo [cite: 61]
        if (base % mod != 0) {
             reduced_exp = exp % (mod - 1);
             printf("     Aplicando Pequeno Teorema de Fermat: expoente reduzido de %lld para %lld.\n", exp, reduced_exp);
        }
    } else if (euclidesMDC(base, mod) == 1) {
        // Teorema de Euler, se mdc(M,n)=1 [cite: 62]
        reduced_exp = exp % totient;
        printf("     Aplicando Teorema de Euler: expoente reduzido de %lld para %lld.\n", exp, reduced_exp);
    } else {
        // Caso geral, sem redução de expoente por teoremas, mas o algoritmo
        // de exponenciação por quadratura já é eficiente.
        // A "Divisão Euclidiana" para reduzir o expoente [cite: 63] é a base
        // para a aplicação dos teoremas acima.
        printf("     MDC(base, mod) != 1. Usando exponenciacao por quadratura sem reducao de expoente por teorema.\n");
    }

    lli res = 1;
    base %= mod;
    while (reduced_exp > 0) {
        if (reduced_exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        reduced_exp /= 2;
    }
    return res;
}