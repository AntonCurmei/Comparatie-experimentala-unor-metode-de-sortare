#define _CRT_SECURE_NO_WARNINGS
#define NUM_LISTE 10000
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int random_positive_int()
{
    unsigned int x = 0;
    while (x == 0 || x > INT_MAX)
    {
        x = ((unsigned int)rand() << 16) ^ (unsigned int)rand();
    }
    return (int)x;
}

void creareArray(const char* numeFisier, int n)
{
    FILE* f = fopen(numeFisier, "w");
    if (f == NULL)
    {
        printf("Nu s-a putut deschide fisierul pentru creare: %s\n", numeFisier);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        int x = random_positive_int();
        fprintf(f, "%d ", x);
    }

    fclose(f);
}

int citireArray(const char* numeFisier, int v[], int n)
{
    FILE* f = fopen(numeFisier, "r");
    if (f == NULL)
    {
        printf("Nu s-a putut deschide fisierul pentru citire: %s\n", numeFisier);
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        if (fscanf(f, "%d", &v[i]) != 1)
        {
            fclose(f);
            printf("Eroare la citirea din fisierul: %s\n", numeFisier);
            return 0;
        }
    }

    fclose(f);
    return 1;
}

void scriereArray(const char* numeFisier, int v[], int n)
{
    FILE* f = fopen(numeFisier, "w");
    if (f == NULL)
    {
        printf("Nu s-a putut deschide fisierul pentru scriere: %s\n", numeFisier);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(f, "%d ", v[i]);
    }

    fclose(f);
}

void insertionSort(int v[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int x = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > x)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = x;
    }
}

void insertionSortInterval(int v[], int st, int dr)
{
    for (int i = st + 1; i <= dr; i++)
    {
        int x = v[i];
        int j = i - 1;
        while (j >= st && v[j] > x)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = x;
    }
}

int maxim(int v[], int n)
{
    int max = v[0];
    for (int i = 1; i < n; i++)
        if (v[i] > max)
            max = v[i];
    return max;
}

int minim(int v[], int n)
{
    int min = v[0];
    for (int i = 1; i < n; i++)
        if (v[i] < min)
            min = v[i];
    return min;
}

int partition(int v[], int st, int dr)
{
    int pivot = v[dr];
    int i = st - 1;

    for (int j = st; j < dr; j++)
    {
        if (v[j] < pivot)
        {
            i++;
            int aux = v[i];
            v[i] = v[j];
            v[j] = aux;
        }
    }

    int aux = v[i + 1];
    v[i + 1] = v[dr];
    v[dr] = aux;
    return i + 1;
}

void quickSort(int v[], int st, int dr)
{
    if (st < dr)
    {
        int p = partition(v, st, dr);
        quickSort(v, st, p - 1);
        quickSort(v, p + 1, dr);
    }
}

void countingSortCifra(int v[], int n, int exp)
{
    int* output = (int*)malloc(n * sizeof(int));
    int count[10] = { 0 };

    if (output == NULL)
    {
        printf("Eroare la alocarea memoriei\n");
        return;
    }

    for (int i = 0; i < n; i++)
        count[(v[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        int cifra = (v[i] / exp) % 10;
        output[count[cifra] - 1] = v[i];
        count[cifra]--;
    }

    for (int i = 0; i < n; i++)
        v[i] = output[i];

    free(output);
}

void heapify(int v[], int n, int i)
{
    int max = i;
    int st = 2 * i + 1;
    int dr = 2 * i + 2;

    if (st < n && v[st] > v[max]) max = st;
    if (dr < n && v[dr] > v[max]) max = dr;

    if (max != i)
    {
        int aux = v[i];
        v[i] = v[max];
        v[max] = aux;
        heapify(v, n, max);
    }
}

void interclasare(int v[], int stanga, int mijloc, int dreapta)
{
    int n1 = mijloc - stanga + 1;
    int n2 = dreapta - mijloc;

    int* st = (int*)malloc(n1 * sizeof(int));
    int* dr = (int*)malloc(n2 * sizeof(int));

    if (st == NULL || dr == NULL)
    {
        free(st);
        free(dr);
        printf("Eroare la alocarea memoriei\n");
        return;
    }

    for (int i = 0; i < n1; i++)
        st[i] = v[stanga + i];

    for (int i = 0; i < n2; i++)
        dr[i] = v[mijloc + 1 + i];

    int i = 0, j = 0, k = stanga;

    while (i < n1 && j < n2)
    {
        if (st[i] <= dr[j]) v[k++] = st[i++];
        else v[k++] = dr[j++];
    }

    while (i < n1) v[k++] = st[i++];
    while (j < n2) v[k++] = dr[j++];

    free(st);
    free(dr);
}

void selection_sort(const char* fisierIntrare, const char* fisierIesire, int n)
{
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL) return;
    if (!citireArray(fisierIntrare, v, n)) { free(v); return; }

    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (v[j] < v[min])
                min = j;

        if (min != i)
        {
            int aux = v[i];
            v[i] = v[min];
            v[min] = aux;
        }
    }

    scriereArray(fisierIesire, v, n);
    free(v);
}

void double_selection_sort(const char* fisierIntrare, const char* fisierIesire, int n)
{
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL) return;
    if (!citireArray(fisierIntrare, v, n)) { free(v); return; }

    for (int st = 0, dr = n - 1; st < dr; st++, dr--)
    {
        int min = st, max = st;

        for (int i = st + 1; i <= dr; i++)
        {
            if (v[i] < v[min]) min = i;
            if (v[i] > v[max]) max = i;
        }

        if (min != st)
        {
            int aux = v[st];
            v[st] = v[min];
            v[min] = aux;
        }

        if (max == st) max = min;

        if (max != dr)
        {
            int aux = v[dr];
            v[dr] = v[max];
            v[max] = aux;
        }
    }

    scriereArray(fisierIesire, v, n);
    free(v);
}

void insertionSortFisier(const char* fisierIntrare, const char* fisierIesire, int n)
{
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL) return;
    if (!citireArray(fisierIntrare, v, n)) { free(v); return; }

    insertionSort(v, n);
    scriereArray(fisierIesire, v, n);
    free(v);
}

void quickSortFisier(const char* fisierIntrare, const char* fisierIesire, int n)
{
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL) return;
    if (!citireArray(fisierIntrare, v, n)) { free(v); return; }

    quickSort(v, 0, n - 1);
    scriereArray(fisierIesire, v, n);
    free(v);
}

void radixSort(const char* fisierIntrare, const char* fisierIesire, int n)
{
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL) return;
    if (!citireArray(fisierIntrare, v, n)) { free(v); return; }

    int max = maxim(v, n);
    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSortCifra(v, n, exp);

    scriereArray(fisierIesire, v, n);
    free(v);
}

void bucketSort(const char* fisierIntrare, const char* fisierIesire, int n)
{
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL) return;
    if (!citireArray(fisierIntrare, v, n)) { free(v); return; }

    if (n <= 1)
    {
        scriereArray(fisierIesire, v, n);
        free(v);
        return;
    }

    int min = minim(v, n);
    int max = maxim(v, n);
    int nrBucketuri = n;
    int interval = (max - min) / nrBucketuri + 1;

    int* dim = (int*)calloc(nrBucketuri, sizeof(int));
    int* poz = (int*)calloc(nrBucketuri, sizeof(int));
    int** bucketuri = (int**)malloc(nrBucketuri * sizeof(int*));

    if (dim == NULL || poz == NULL || bucketuri == NULL)
    {
        free(v); free(dim); free(poz); free(bucketuri);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        int index = (v[i] - min) / interval;
        dim[index]++;
    }

    for (int i = 0; i < nrBucketuri; i++)
    {
        if (dim[i] > 0)
            bucketuri[i] = (int*)malloc(dim[i] * sizeof(int));
        else
            bucketuri[i] = NULL;
    }

    for (int i = 0; i < n; i++)
    {
        int index = (v[i] - min) / interval;
        bucketuri[index][poz[index]++] = v[i];
    }

    for (int i = 0; i < nrBucketuri; i++)
        if (dim[i] > 1)
            insertionSort(bucketuri[i], dim[i]);

    int k = 0;
    for (int i = 0; i < nrBucketuri; i++)
        for (int j = 0; j < dim[i]; j++)
            v[k++] = bucketuri[i][j];

    for (int i = 0; i < nrBucketuri; i++)
        free(bucketuri[i]);

    free(bucketuri);
    free(dim);
    free(poz);

    scriereArray(fisierIesire, v, n);
    free(v);
}

void heapSort(const char* fisierIntrare, const char* fisierIesire, int n)
{
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL) return;
    if (!citireArray(fisierIntrare, v, n)) { free(v); return; }

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        int aux = v[0];
        v[0] = v[i];
        v[i] = aux;
        heapify(v, i, 0);
    }

    scriereArray(fisierIesire, v, n);
    free(v);
}

void timSort(const char* fisierIntrare, const char* fisierIesire, int n)
{
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL) return;
    if (!citireArray(fisierIntrare, v, n)) { free(v); return; }

    for (int i = 0; i < n; i += 32)
    {
        int dr = i + 31;
        if (dr >= n) dr = n - 1;
        insertionSortInterval(v, i, dr);
    }

    for (int m = 32; m < n; m = 2 * m)
    {
        for (int st = 0; st < n; st += 2 * m)
        {
            int mj = st + m - 1;
            int dr = st + 2 * m - 1;

            if (mj >= n - 1) continue;
            if (dr >= n) dr = n - 1;

            interclasare(v, st, mj, dr);
        }
    }

    scriereArray(fisierIesire, v, n);
    free(v);
}

void construiesteNumeFisierIntrare(char* buffer, int index)
{
    sprintf(buffer, "D:\\Anton\\uni\\sort\\liste\\lista_%05d.txt", index);
}

void construiesteNumeFisierIesire(char* buffer, const char* algoritm, int index)
{
    sprintf(buffer, "D:\\Anton\\uni\\sort\\rezultate\\%s\\%s_%05d.txt", algoritm, algoritm, index);
}

void genereazaToateListele(int n)
{
    char fisier[256];

    for (int i = 1; i <= NUM_LISTE; i++)
    {
        construiesteNumeFisierIntrare(fisier, i);
        creareArray(fisier, n);
    }
}

void sorteazaToateListeleInsertion(int n)
{
    char fin[256], fout[256];
    for (int i = 1; i <= NUM_LISTE; i++)
    {
        construiesteNumeFisierIntrare(fin, i);
        construiesteNumeFisierIesire(fout, "insertion", i);
        insertionSortFisier(fin, fout, n);
    }
}

void sorteazaToateListeleSelection(int n)
{
    char fin[256], fout[256];
    for (int i = 1; i <= NUM_LISTE; i++)
    {
        construiesteNumeFisierIntrare(fin, i);
        construiesteNumeFisierIesire(fout, "selection", i);
        selection_sort(fin, fout, n);
    }
}

void sorteazaToateListeleDoubleSelection(int n)
{
    char fin[256], fout[256];
    for (int i = 1; i <= NUM_LISTE; i++)
    {
        construiesteNumeFisierIntrare(fin, i);
        construiesteNumeFisierIesire(fout, "double_selection", i);
        double_selection_sort(fin, fout, n);
    }
}

void sorteazaToateListeleQuick(int n)
{
    char fin[256], fout[256];
    for (int i = 1; i <= NUM_LISTE; i++)
    {
        construiesteNumeFisierIntrare(fin, i);
        construiesteNumeFisierIesire(fout, "quick", i);
        quickSortFisier(fin, fout, n);
    }
}

void sorteazaToateListeleBucket(int n)
{
    char fin[256], fout[256];
    for (int i = 1; i <= NUM_LISTE; i++)
    {
        construiesteNumeFisierIntrare(fin, i);
        construiesteNumeFisierIesire(fout, "bucket", i);
        bucketSort(fin, fout, n);
    }
}

void sorteazaToateListeleRadix(int n)
{
    char fin[256], fout[256];
    for (int i = 1; i <= NUM_LISTE; i++)
    {
        construiesteNumeFisierIntrare(fin, i);
        construiesteNumeFisierIesire(fout, "radix", i);
        radixSort(fin, fout, n);
    }
}

void sorteazaToateListeleHeap(int n)
{
    char fin[256], fout[256];
    for (int i = 1; i <= NUM_LISTE; i++)
    {
        construiesteNumeFisierIntrare(fin, i);
        construiesteNumeFisierIesire(fout, "heap", i);
        heapSort(fin, fout, n);
    }
}

void sorteazaToateListeleTim(int n)
{
    char fin[256], fout[256];
    for (int i = 1; i <= NUM_LISTE; i++)
    {
        construiesteNumeFisierIntrare(fin, i);
        construiesteNumeFisierIesire(fout, "tim", i);
        timSort(fin, fout, n);
    }
}

int main()
{
    int n=1000;
    //printf("n = ");
    //scanf("%d", &n);

    srand((unsigned int)time(NULL));

    genereazaToateListele(n);
    clock_t start, finish;
    double durata;

    start = clock();
    sorteazaToateListeleInsertion(n);
    finish = clock();
    durata = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("Sortarea InsertionSort a durat %.6f secunde\n", durata);

    start = clock();
    sorteazaToateListeleSelection(n);
    finish = clock();
    durata = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("Sortarea SelectionSort a durat %.6f secunde\n", durata);

    start = clock();
    sorteazaToateListeleDoubleSelection(n);
    finish = clock();
    durata = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("Sortarea DoubleSelectionSort a durat %.6f secunde\n", durata);

    start = clock();
    sorteazaToateListeleQuick(n);
    finish = clock();
    durata = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("Sortarea QuickSort a durat %.6f secunde\n", durata);

    start = clock();
    sorteazaToateListeleBucket(n);
    finish = clock();
    durata = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("Sortarea BucketSort a durat %.6f secunde\n", durata);

    start = clock();
    sorteazaToateListeleRadix(n);
    finish = clock();
    durata = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("Sortarea RadixSort a durat %.6f secunde\n", durata);

    start = clock();
    sorteazaToateListeleHeap(n);
    finish = clock();
    durata = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("Sortarea HeapSort a durat %.6f secunde\n", durata);

    start = clock();
    sorteazaToateListeleTim(n);
    finish = clock();
    durata = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("Sortarea TimSort a durat %.6f secunde\n", durata);

    printf("Gata.\n");
    return 0;
}