#### Copyright Damian Mihai-Robert & Pirlea Andrei 312CAb 2022-2023
<br>

## Programul reprezinta un editor de imagini, care poate realiza:
    -deschiderea unei imagini
    -rotirea imaginii/selectiei
    -aplicarea unor filtre
    -salvarea imaginii
    -oprirea programului

# Operatia LOAD
#### Utilizare:
```
LOAD <fisier>
```
#### Descriere:
```
Functia deschide fisierul cu numele "fisier" si verifica daca este de tip 
scii sau binar, pentru a determina modul de citire a datelor. Apoi citeste
metadatele (magic_word, width, height, max_value), ignorand spatiile si
comentariile. Ulterior aloca memorie pentru matricea de valori a pixelilor si
citeste aceste date.
```


# Operatia ROTATE
#### Utilizare:
```
ROTATE <unghi>
```
#### Descriere:
```
Functia are 2 scopuri:
    1.  Daca toata imaginea este selectata, aceasta se va roti cu "unghi" grade
      (multiplu de 90).
    2.  Daca nu toata imaginea este selectata, rotirea se va realiza doar daca
      zona selectata este un patrat.
```


# Operatia APPLY
#### Utilizare:
```
APPLY <PARAMETRU>
```
#### Descriere:
```
Functia este destinata pozelor color si poate aplica 4 filtre dupa cum urmeaza:
    1. EDGE - filtru utilizat pentru a gasi conturul formelor din imagine
    2. SHARPEN - filtru utilizat pentru a deblura o imagine
    3, BLUR - filtru utilizat pentru a blura o imagine
    4. GAUSSIAN_BLUR - o metoda mai buna pentru a blura o imagine
```


# Operatia SAVE
#### Utilizare:
```
SAVE <nume_fisier> [ascii]
```
#### Descriere:
```
Functia va salva imaginea din memorie intr-un fisier denumit "nume fisier".
Daca parametrul ascii este prezent, atunci imaginea va fi salvata intr-un
fisier text, sub forma human-readable. Daca acesta lipseste, imaginea va fi
salvata intr-un fisier binar.
```

# Operatia EXIT
#### Utilizare:
```
EXIT
```
#### Descriere:
```
Functia are ca scop dealocarea resurselor alocate si oprirea programului
```
