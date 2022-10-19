#include <iostream>
#define UNDEFINED -1
#define FALSE     0
#define TRUE      1

using namespace std;
struct _cell {
    int element;
    struct _cell *next;
};

typedef struct _cell *List;

int getTransition(char *x, int p, List L[], char c) {
    List cell;

    if (p > 0 && x[p - 1] == c)
        return (p - 1);
    else {
        cell = L[p];
        while (cell != NULL)
            if (x[cell->element] == c)
                return (cell->element);
            else
                cell = cell->next;
        return (UNDEFINED);
    }
}

void setTransition(int p, int q, List L[]) {
    List cell;

    cell = (List)malloc(sizeof(struct _cell));
    if (cell == NULL)
        cout << "BOM/setTransition";
    cell->element = q;
    cell->next = L[p];
    L[p] = cell;
}

void oracle(char *x, int m, char T[], List L[]) {
    int i, p, q;
    // XSIZE is size of that x string
    int S[XSIZE + 1];
    char c;

    S[m] = m + 1;
    for (i = m; i > 0; --i) {
        c = x[i - 1];
        p = S[i];
        while (p <= m && (q = getTransition(x, p, L, c)) == UNDEFINED) {
            setTransition(p, i - 1, L);
            p = S[p];
        }
        S[i - 1] = (p == m + 1 ? m : q);
    }
    p = 0;
    while (p <= m) {
        T[p] = TRUE;
        p = S[p];
    }
}

void BOM(char *x, int m, char *y, int n) {
    char T[XSIZE + 1];
    List L[XSIZE + 1];
    int i, j, p, period, q, shift;

    memset(L, NULL, (m + 1) * sizeof(List));
    memset(T, FALSE, (m + 1) * sizeof(char));
    oracle(x, m, T, L);

    j = 0;
    while (j <= n - m) {
        i = m - 1;
        p = m;
        shift = m;
        while (i + j >= 0 &&
               (q = getTransition(x, p, L, y[i + j])) != UNDEFINED) {
            p = q;
            if (T[p] == TRUE) {
                period = shift;
                shift = i;
            }
            --i;
        }
        if (i < 0) {
            cout << j;
            shift = period;
        }
        j += shift;
    }
}
