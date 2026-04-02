#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random_positive_int()
{
    unsigned int x = 0;
    while (x <= 0 || x > INT_MAX)
    {
        x = ((unsigned int)rand() << 16) ^ (unsigned int)rand();
    }
    return (int)x;
}

int random_signed_int_interval(int a, int b)
{
    return a + rand() % (b - a + 1);
}

double random_double_interval(double a, double b)
{
    return a + (double)rand() / RAND_MAX * (b - a);
}

void creareArray(const char* numeFisier, int n)
{
    FILE* f = fopen(numeFisier, "w");
    if (f == NULL)
    {
        printf("Nu s-a putut deschide fisierul pentru creare\n");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        int x = random_positive_int(); //numere mai mari
        //int x = rand(); //numere mai mici
        //double x = random_double_interval(-100000, 100000); //numere reale
        fprintf(f, "%d ", x);
    }
    fclose(f);
}

void citireArray(const char* numeFisier, int v[], int n)
{
    FILE* f = fopen(numeFisier, "r");
    if (f == NULL)
    {
        printf("Nu s-a putut deschide fisierul pentru citire\n");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        fscanf(f, "%d", &v[i]);
    }
    fclose(f);
}

void scriereArray(const char* numeFisier, int v[], int n)
{
    FILE* f = fopen(numeFisier, "w");
    if (f == NULL)
    {
        printf("Nu s-a putut deschide fisierul pentru scriere\n");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(f, "%d ", v[i]);
    }
    fclose(f);
}

void genereazaAproapeSortat(const char* numeFisier, int n, double procent)
{
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL)
    {
        printf("Eroare la alocarea memoriei.\n");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        v[i] = i + 1;
    }
    int nrSchimbari = (int)(n * procent / 100.0);
    for (int i = 0; i < nrSchimbari; i++)
    {
        int poz1 = rand() % n;
        int poz2 = rand() % n;
        int aux = v[poz1];
        v[poz1] = v[poz2];
        v[poz2] = aux;
    }
    scriereArray(numeFisier, v, n);
    free(v);
}

void inverseazaVector(int v[], int n)
{
    int i, temp;
    for (i = 0; i < n / 2; i++)
    {
        temp = v[i];
        v[i] = v[n - 1 - i];
        v[n - 1 - i] = temp;
    }
}

void inverseazaListaDinFisier(const char* numeFisier, int n)
{
    int* v = (int*)malloc(n * sizeof(int));
    citireArray(numeFisier, v, n);
    inverseazaVector(v, n);
    scriereArray(numeFisier, v, n);
    free(v);
}

void selection_sort(const char* fisierIntrare, const char* fisierIesire, int n)
{
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL)
    {
        printf("Eroare la alocarea memoriei\n");
        return;
    }
    citireArray(fisierIntrare, v, n);
    clock_t start, finish;
    double durata;
    start = clock();
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (v[j] < v[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            int aux = v[i];
            v[i] = v[min];
            v[min] = aux;
        }
    }
    finish = clock();
    durata = (double)(finish - start) / CLOCKS_PER_SEC;
    scriereArray(fisierIesire, v, n);
    printf("Sortarea SelectionSort a durat %.6f secunde\n", durata);
    free(v);
}

void double_selection_sort(const char* fisierIntrare, const char* fisierIesire, int n)
{
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL)
    {
        printf("Eroare la alocarea memoriei\n");
        return;
    }
    citireArray(fisierIntrare, v, n);
    clock_t start, finish;
    double durata;
    start = clock();
    for (int st=0, dr=n-1; st<dr; st++, dr--)
    {
        int min = st;
        int max = st;
        for (int i=st+1; i<=dr; i++)
        {
            if (v[i] < v[min])
            {
                min = i;
            }
            if (v[i] > v[max])
            {
                max = i;
            }
        }
        if (min != st)
        {
            int aux = v[st];
            v[st] = v[min];
            v[min] = aux;
        }
        if (max == st)
        {
            max = min;
        }
        if (max != dr)
        {
            int aux = v[dr];
            v[dr] = v[max];
            v[max] = aux;
        }
    }
    finish = clock();
    durata = (double)(finish - start) / CLOCKS_PER_SEC;
    scriereArray(fisierIesire, v, n);
    printf("Sortarea DoubleSelectionSort a durat %.6f secunde\n", durata);
    free(v);
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

void quickSortFisier(const char* fisierIntrare, const char* fisierIesire, int n)
{
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL)
    {
        printf("Eroare la alocarea memoriei\n");
        return;
    }
    citireArray(fisierIntrare, v, n);
    clock_t start, finish;
    double durata;
    start = clock();
    quickSort(v, 0, n - 1);
    finish = clock();
    durata = (double)(finish - start) / CLOCKS_PER_SEC;
    scriereArray(fisierIesire, v, n);
    printf("Sortarea QuickSort a durat %.6f secunde\n", durata);
    free(v);
}

int maxim(int v[], int n)
{
    int max = v[0];
    for (int i=1; i<n; i++)
    {
        if (v[i] > max)
        {
            max = v[i];
        }
    }
    return max;
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
    {
        int cifra = (v[i] / exp) % 10;
        count[cifra]++;
    }
    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        int cifra = (v[i] / exp) % 10;
        output[count[cifra] - 1] = v[i];
        count[cifra]--;
    }
    for (int i = 0; i < n; i++)
    {
        v[i] = output[i];
    }
    free(output);
}

void radixSort(const char* fisierIntrare, const char* fisierIesire, int n)
{
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL)
    {
        printf("Eroare la alocarea memoriei\n");
        return;
    }
    citireArray(fisierIntrare, v, n);
    clock_t start, finish;
    double durata;
    start = clock();
    int max = maxim(v, n);
    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        countingSortCifra(v, n, exp);
    }
    finish = clock();
    durata = (double)(finish - start) / CLOCKS_PER_SEC;
    scriereArray(fisierIesire, v, n);
    printf("Sortarea RadixSort a durat %.6f secunde\n", durata);
    free(v);
}

void insertionSort(int v[], int n)
{
    for (int i=1; i<n; i++)
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

int minim(int v[], int n)
{
    int min = v[0];
    for (int i=1; i<n; i++)
    {
        if (v[i] < min)
        {
            min = v[i];
        }
    }
    return min;
}

void bucketSort(const char* fisierIntrare, const char* fisierIesire, int n)
{
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL)
    {
        printf("Eroare la alocarea memoriei\n");
        return;
    }
    citireArray(fisierIntrare, v, n);
    clock_t start, finish;
    double durata;
    start = clock();
    if (n <= 1)
    {
        return;
    }
    int min = minim(v, n);
    int max = maxim(v, n);
    int nrBucketuri = n;
    int interval = (max - min) / nrBucketuri + 1;
    int* dim = (int*)calloc(nrBucketuri, sizeof(int));
    int** bucketuri = (int**)malloc(nrBucketuri * sizeof(int*));
    int* poz = (int*)calloc(nrBucketuri, sizeof(int));
    for (int i=0; i<n; i++)
    {
        int index = (v[i] - min) / interval;
        dim[index]++;
    }
    for (int i=0; i<nrBucketuri; i++)
    {
        if (dim[i] > 0)
        {
            bucketuri[i] = (int*)malloc(dim[i] * sizeof(int));
        }
        else
        {
            bucketuri[i] = NULL;
        }
    }
    for (int i=0; i<n; i++)
    {
        int index = (v[i] - min) / interval;
        bucketuri[index][poz[index]] = v[i];
        poz[index]++;
    }
    for (int i=0; i<nrBucketuri; i++)
    {
        if (dim[i] > 1)
        {
            insertionSort(bucketuri[i], dim[i]);
        }
    }
    int k = 0;
    for (int i=0; i<nrBucketuri; i++)
    {
        for (int j=0; j<dim[i]; j++)
        {
            v[k++] = bucketuri[i][j];
        }
    }
    for (int i=0; i<nrBucketuri; i++)
    {
        free(bucketuri[i]);
    }
    free(bucketuri);
    free(dim);
    free(poz);
    finish = clock();
    durata = (double)(finish - start) / CLOCKS_PER_SEC;
    scriereArray(fisierIesire, v, n);
    printf("Sortarea BucketSort a durat %.6f secunde\n", durata);
    free(v);
}

void heapify(int v[], int n, int i)
{
    int maxim = i;
    int stanga = 2 * i + 1;
    int dreapta = 2 * i + 2;
    if (stanga < n && v[stanga] > v[maxim])
    {
        maxim = stanga;
    }
    if (dreapta < n && v[dreapta] > v[maxim])
    {
        maxim = dreapta;
    }
    if (maxim != i)
    {
        int aux = v[i];
        v[i] = v[maxim];
        v[maxim] = aux;
        heapify(v, n, maxim);
    }
}

void heapSort(const char* fisierIntrare, const char* fisierIesire, int n)
{
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL)
    {
        printf("Eroare la alocarea memoriei\n");
        return;
    }
    citireArray(fisierIntrare, v, n);
    clock_t start, finish;
    double durata;
    start = clock();
    for (int i=n/2-1; i>=0; i--)
    {
        heapify(v, n, i);
    }
    for (int i = n - 1; i > 0; i--)
    {
        int aux = v[0];
        v[0] = v[i];
        v[i] = aux;
        heapify(v, i, 0);
    }
    finish = clock();
    durata = (double)(finish - start) / CLOCKS_PER_SEC;
    scriereArray(fisierIesire, v, n);
    printf("Sortarea HeapSort a durat %.6f secunde\n", durata);
    free(v);
}

void insertionSortFisier(const char* fisierIntrare, const char* fisierIesire, int n)
{
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL)
    {
        printf("Eroare la alocarea memoriei\n");
        return;
    }
    citireArray(fisierIntrare, v, n);
    clock_t start, finish;
    double durata;
    start = clock();
    insertionSort(v, n);
    finish = clock();
    durata = (double)(finish - start) / CLOCKS_PER_SEC;
    scriereArray(fisierIesire, v, n);
    printf("Sortarea InsertionSort a durat %.6f secunde\n", durata);
    free(v);
}

void insertionSortInterval(int v[], int st, int dr)
{
    for (int i=st+1; i<=dr; i++)
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

void interclasare(int v[], int stanga, int mijloc, int dreapta)
{
    int n1 = mijloc - stanga + 1;
    int n2 = dreapta - mijloc;
    int* st = (int*)malloc(n1 * sizeof(int));
    int* dr = (int*)malloc(n2 * sizeof(int));
    if (st == NULL || dr == NULL)
    {
        printf("Eroare la alocarea memoriei\n");
        free(st);
        free(dr);
        return;
    }
    for (int i=0; i<n1; i++)
    {
        st[i] = v[stanga + i];
    }

    for (int i=0; i<n2; i++)
    {
        dr[i] = v[mijloc + 1 + i];
    }
    int i = 0, j = 0, k = stanga;
    while (i < n1 && j < n2)
    {
        if (st[i] <= dr[j])
        {
            v[k] = st[i];
            i++;
        }
        else
        {
            v[k] = dr[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        v[k] = st[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        v[k] = dr[j];
        j++;
        k++;
    }
    free(st);
    free(dr);
}

void timSort(const char* fisierIntrare, const char* fisierIesire, int n)
{
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL)
    {
        printf("Eroare la alocarea memoriei\n");
        return;
    }
    citireArray(fisierIntrare, v, n);
    clock_t start, finish;
    double durata;
    start = clock();
    for (int i=0; i<n; i+=32)
    {
        int dr = i + 32 - 1;
        if (dr >= n)
        {
            dr = n - 1;
        }
        insertionSortInterval(v, i, dr);
    }
    for (int m=32; m<n; m=2*m)
    {
        for (int st=0; st<n; st+=2*m)
        {
            int mj = st + m - 1;
            int dr = st + 2 * m - 1;
            if (mj >= n - 1)
            {
                continue;
            }
            if (dr >= n)
            {
                dr = n - 1;
            }
            interclasare(v, st, mj, dr);
        }
    }
    finish = clock();
    durata = (double)(finish - start) / CLOCKS_PER_SEC;
    scriereArray(fisierIesire, v, n);
    printf("Sortarea TimSort a durat %.6f secunde\n", durata);
    free(v);
}

void bubble_sort(const char* fisierIntrare, const char* fisierIesire, int n)
{
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL)
    {
        printf("Eroare la alocarea memoriei\n");
        return;
    }
    citireArray(fisierIntrare, v, n);
    clock_t start, finish;
    double durata;
    start = clock();
    for (int i = 0; i < n - 1; i++)
    {
        
        for (int j = 0; j < n - i - 1; j++)
        {
            if (v[j] > v[j + 1])
            {
                int temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
    finish = clock();
    durata = (double)(finish - start) / CLOCKS_PER_SEC;
    scriereArray(fisierIesire, v, n);
    printf("Sortarea BubbleSort a durat %.6f secunde\n", durata);
    free(v);
}


int main()
{

    int n = 1000000;
    //scanf("%d", &n);
    srand(time(NULL));

    //creareArray("D:\\Anton\\uni\\sort\\lista.txt", n); //lista random
    genereazaAproapeSortat("D:\\Anton\\uni\\sort\\lista.txt", n, 0.1); //lista aproape sorata

    //insertionSortFisier("D:\\Anton\\uni\\sort\\lista.txt", "D:\\Anton\\uni\\sort\\lista.txt", n); //lista sortata
    //inverseazaListaDinFisier("D:\\Anton\\uni\\sort\\lista.txt", n); //lista inversata

    //insertionSortFisier("D:\\Anton\\uni\\sort\\lista.txt", "D:\\Anton\\uni\\sort\\insertion_sortat.txt", n);
    //selection_sort("D:\\Anton\\uni\\sort\\lista.txt", "D:\\Anton\\uni\\sort\\selection_sortat.txt", n);
    //double_selection_sort("D:\\Anton\\uni\\sort\\lista.txt", "D:\\Anton\\uni\\sort\\double_selection_sortat.txt", n);
    //quickSortFisier("D:\\Anton\\uni\\sort\\lista.txt", "D:\\Anton\\uni\\sort\\quick_sortat.txt", n);
    //bucketSort("D:\\Anton\\uni\\sort\\lista.txt", "D:\\Anton\\uni\\sort\\bucket_sortat.txt", n);
    //radixSort("D:\\Anton\\uni\\sort\\lista.txt", "D:\\Anton\\uni\\sort\\radix_sortat.txt", n);
    //heapSort("D:\\Anton\\uni\\sort\\lista.txt", "D:\\Anton\\uni\\sort\\heap_sortat.txt", n);
    //timSort("D:\\Anton\\uni\\sort\\lista.txt", "D:\\Anton\\uni\\sort\\tim_sortat.txt", n);
    
    bubble_sort("D:\\Anton\\uni\\sort\\lista.txt", "D:\\Anton\\uni\\sort\\bubble_sortat.txt", n);
    return 0;
}