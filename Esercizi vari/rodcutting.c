#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b)) ? (a) : (b)


/* Versione ricorsiva PURA (calcola solo il valore ottimo)
 *
 * Tempo = O(2^n)
 * Spazio (implicito dovuto alla ricorsione) = O(2^n)
 */
int rod_cut(int* p, int n) {
    if(n == 0) // Caso base: barretta di lunghezza zero => guadagno 0
        return 0;
    
    int q = -1;
    int i;
    for(i=1;i<=n;i++) { // Per ogni possibile taglio iniziale
        // Valuta il massimo tra non tagliare oppure tagliare a lunghezza i
        // e poi tagliare ricorsivamente il resto della barretta
        q = max(q, p[i] + rod_cut(p, n-i));
    }
    
    return q;
}

/* Versione ricorsiva memoizzata (calcola solo il valore ottimo)
 *
 * Utilizza un array ausiliario in cui salvare via via il risultato
 * delle chiamate ricorsive in modo da non doverle ripetere più di una volta.
 * Assumiamo che r[i] = -1 inizialmente
 *
 * Tempo = O(n^2)
 * Spazio = O(n) per l'array revenue
 */
int memoized_rod_cut(int* p, int n, int* r) {
    if(r[n] >= 0) // Se conosciamo già la soluzione di questa chiamata la restituiamo
        return r[n];
    
    int q;
    int i;
    
    if(n == 0) // Lunghezza zero => zero guadagno
        q = 0;
    else {
        q = -1;
        for(i=1;i<=n;i++) { // Per ogni possibile taglio iniziale
            // Valuta il massimo tra non tagliare oppure tagliare a lunghezza i
            // e poi tagliare ricorsivamente il resto della barretta
            q = max(q, p[i] + memoized_rod_cut(p, n-i, r));
        }
    }
    
    r[n] = q; // Salviamo il risultato di questa chiamata
    
    return q;
}

/* Versione Programmazione Dinamica
 *
 *
 * Tempo: O(n^2)
 * Spazio: O(n) per gli array revenue e cutting
 *
 * Regola ricorsiva:
 * Base: barretta di lunghezza zero, 0 guadagno. r[0] = 0
 * Ricorsione: r[j] = max (p[i] + r[j-i]) per 0 < i <= j
 * ovvero il massimo che ottengo tagliando il primo pezzo a lunghezza i
 * e poi aggiungendo il guadagno ottimo ricavato dal taglio del resto della
 * barretta, lungo j-i.
 */

int* dynamic_rod_cut(int* p, int n, int* optimal_value) {
    // Revenue (r sul Cormen)
    // revenue[i] = guadagno corrispondente alla
    // soluzione ottima per una barretta lunga i
    int* revenue = (int*) malloc((n+1) * sizeof(int));
    // Cutting (s sul Cormen):
    // s[i] = lunghezza ottima del primo taglio di una barretta lunga i
    int* cutting = (int*) malloc((n+1) * sizeof(int));
    
    int i, j;
    
    // Caso base: una barretta di lunghezza 0 non produce guadagno
    revenue[0] = 0;
    
    // Casi ricorsivi
    for(j=1;j<=n;j++) {
        int q = -1; // Valore ottimo
        for(i=1;i<=j;i++) { // Sottoproblemi da 1 a j
            if(q < p[i] + revenue[j - i]) { // Regola ricorsiva
                q = p[i] + revenue[j - i];
                cutting[j] = i; // Se conviene fare il taglio, questo avviene a lunghezza i
            }
        }
        revenue[j] = q; // Salviamo la soluzione ottima per questo sottoproblema
    }
    
    *optimal_value = revenue[n]; // Per restituire il valore ottimo
    free(revenue); // L'array di revenue non ci serve più
    return cutting;
}

int main(void) {
    int n;
    int* price;
    int i;
    
    scanf("%d", &n);
    
    // Servono n+1 celle perché i prezzi (e le lunghezze) vanno da 1 a n compreso
    price = (int*) malloc((1+n) * sizeof(int));
    
    price[0] = 0;
    for(i=1;i<=n;i++) { // Da 1 a n compreso
        scanf("%d", &(price[i]));
    }
    
    // --------------------------------
    
    // VERSIONE RICORSIVA INEFFICIENTE
    // printf("%d\n", rod_cut(price, n));
    
    // --------------------------------
    
    // VERSIONE RICORSIVA EFFICIENTE (che però non ricostruisce la soluzione)
    /*
    int* revenue = malloc((n+1) * sizeof(int));
    for(i=0;i<=n;i++)
        revenue[i] = -1;
    printf("%d\n", memoized_rod_cut(price, n, revenue));
    free(revenue);
     */
    
    // ---------------------------------
    
    // VERSIONE PROGRAMMAZIONE DINAMICA (EFFICIENTE)
    
    int optimal_revenue;
    int* cutting = dynamic_rod_cut(price, n, &optimal_revenue);
    
    printf("%d\n", optimal_revenue); // Valore ottimo
    // La soluzione può essere ricostruita andando a ritroso nell'array cutting:
    // cutting[n] contiene infatti la lunghezza del primo taglio da fare
    // per una barretta lunga n.
    // Una volta tagliato il primo pezzo, tagliamo il "primo pezzo"
    // della restante barretta e così via, fino ad arrivare ad una barretta
    // lunga zero.
    while(n > 0) {
        printf("%d ", cutting[n]);
        n = n - cutting[n];
    }
    
    printf("\n");

    free(price);
    free(cutting);
    return 0;
}
