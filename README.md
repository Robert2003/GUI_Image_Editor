#### Copyright Damian Mihai-Robert 312CAb 2022-2023
<br>

## Programul reprezinta un editor de imagini, care poate realiza:
    -deschiderea unei imagini
    -selectie unei zone de lucru
    -histograma imaginii
    -egalizarea imaginii
    -rotirea imaginii/selectiei
    -decuparea selectiei
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


# Operatia SELECT
#### Utilizare:
```
1. SELECT <x1> <y1> <x2> <y2>
2. SELECT ALL
```
#### Descriere:
```
1.  Functia primeste 4 parametri, care delimiteaza dreptunghiul/patratul
  determinat de coordonatele (y1, x1) - coltul stanga-sus si (y2, x2) - coltul
  dreapta-jos. Daca selectia se afla in interiorul imaginii, zona de lucru se
  va schimba la acele coordonate.
2.  Functia selecteaza zona de lucru ca fiind toata imaginea.
```


# Operatia HISTOGRAM
#### Utilizare:
```
HISTOGRAM <x> <y>
```
#### Descriere:
```
Daca imaginea este de tip grayscale, functia afiseaza histograma intregii
imagini, folosind maxim y intervale si x stelute. Cele 256 de valori posibil
ale unui pixel sunt impartite in y grupe de cate (256 / y) elemente, numarul
de aparitii ale acestora cumulandu-se. Pentru a calcula numarul de stelute
relativ la x, se aplica formula: 
    nr_stelute = (frecventa_valoare / max_frecventa) * x.
```


# Operatia EQUALIZE
#### Utilizare:
```
EQUALIZE
```
#### Descriere:
```
Functia va realiza egalizarea imeginilor grayscale, pentru imaginile cu o
expunere incorecta prin care se va calibra contrastul.
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


# Operatia CROP
#### Utilizare:
```
CROP
```
#### Descriere:
```
Functia va inlocui in memorie imaginea intreaga cu selectia curenta.
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
