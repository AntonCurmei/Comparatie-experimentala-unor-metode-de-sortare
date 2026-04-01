# Comparație experimentală a unor metode de sortare

Acest proiect prezintă o comparație experimentală între mai mulți algoritmi de sortare implementați în limbajul C, pe baze de date de dimensiuni și structuri diferite.

## Algoritmi implementați
- Insertion Sort
- Selection Sort
- Double Selection Sort
- Quick Sort
- Bucket Sort
- Radix Sort
- Heap Sort
- Tim Sort

## Scopul proiectului
Scopul proiectului este analiza comparativă a performanței algoritmilor de sortare și evidențierea diferențelor dintre comportamentul teoretic și cel experimental.

## Tipuri de date testate
- liste aleatoare
- liste sortate
- liste aproape sortate
- liste invers sortate

În experimentele pe liste aleatoare au fost folosite:
- numere mici: intervalul [0, 32767]
- numere mari: intervalul [0, 2147483647]

## Observații importante
- Double Selection Sort a fost frecvent mai rapid decât Selection Sort, dar nu în toate cazurile.
- Quick Sort a produs stack overflow pe liste sortate, aproape sortate și invers sortate, din cauza alegerii ultimului element drept pivot.
- Testarea pe volume foarte mari de date a fost limitată de memoria RAM disponibilă.

## Structura proiectului
- `src/` - cod sursă
- `data/` - informații despre datele de test
- `results/` - rezultate brute și prelucrate
- `report/` - raportul final și graficele
- `docs/` - documentație suplimentară

## Compilare
Exemplu:
```bash
gcc src/sortari.c -o sortari
gcc src/sortari_multeliste.c -o sortari_multeliste
