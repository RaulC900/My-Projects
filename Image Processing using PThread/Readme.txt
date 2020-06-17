CREMENESCU RAUL-VALENTIN
333CB


Ex 1

->Am declarat urmatoarele structuri: pixel cu membrii r, g, b de tip
unsigned char; pixelInt cu membrii r, g, b de tip int; image cu membrii:
-char type[2]-string cu tipul pozei, int width, height- latimea si inaltimea
pozei, int max_rgbval-valoarea maxima a unui pixel de culoare, 
unsigned char** mat-o matrice de unsigned char-uri(pixeli cu val pana
in 255), pixel **mat_color-matrice cu elem de tip pixel- si threadS
cu membrii: int id, image *img_in si image *img_out (structura cu
id-ul unui thread, o imagine de input si una de output data ca argument
in functia pthread_create).

->Functia alloc_mat cu argumentele height si width imi aloca o matrice de
height*width cu elemente de tip unsigned char, iar functia alloc_mat_color
imi aloca o matrice de height*width cu elem de tip pixel.

->In functia readInput deschid fisierul fileName dat ca argument functiei
cu modul de acces "rb"(read-binary). Citesc tipul imaginii din primul rand
, width si height de pe al doilea rand si max_rgbval de pe al treilea
rand din fisier cu fscanf.
Apoi citim in 2 for-uri matricea img->mat de dimensiune height*width
cu fread(pt ca este text binar).
Daca tipul imaginii va fi "P5" (.pgm) vom citi o matrice cu elem de tip
unsigned char, iar daca tipul esti "P6" (.pnm) vom citi o matrice cu 
elem de tip pixel. Astfel vom creea o imagine.

->In writeData vom deschide un fisier cu modul de acces "wb" (write-binary) 
si vom scrie in aceeasi ordine in care am citit tinand cont de tipul 
imaginii.

->In functia resize(image *in, image *out), vom incepe prin a calcula
out->height ca in->height/resize_factor si pt width la fel(imaginea 
rezultata va fi de resize_factor ori mai mica decat cea initiala). 
Copiem tipul imaginii in in out cu str_cpy si max_rgbval in va fi egal 
cu max_rgbval din out.
Daca tipul imaginii este "P5", vom aloca o matrice pt out de unsigned 
char-uri, iar daca tipul este "P6", o matrice cu elem de tipul pixel.

->Creeam o matrice cu elemente de tip pthread_t de marime num_threads si 
o matrice cu elem de tipul threadS de marime num_threads.
Intr-un for de la 0 la num_threads vom calcula id-ul thread-ului ca 
fiind i si vom face ca img_in si img_out ai lui thread_id sa pointeze 
in acelasi loc ca in si out.

->Apoi, intr-un for apelam pthread_create(apeleaza threadFunction cu 
argumentul &(thread_id[i])- valoarea elem thread_id[i] la care se pointeaza, 
creeand astfel thread-uri-fire de executie.

->In urm for, apelam pthread_join care asteapta ca un thread sa se opreasca 
si il porneste pe urmatorul.

->In threadFunction vom declara si initializa sum, pixelInt sum_color, 
sum_color.r, sum_color.g, sum_color.b, gaussian[3][3] si thr.

->Incepem prin a compara tipul imaginii cu "P5" si "P6". 

->Daca tipul este "P5", comparam resize_factor. Daca acesta este 3, 
in 4 for-uri, vom inmulti matricea de 3*3 cu Kernel-ul Gaussian gaussian 
si vom aduna rezultatul in sum, urmand ca dupa parcurgerea matricei 
in sa impartim rezultatul la 16 si sa il punem in out->mat. 
Daca resize_factor este par, vom parcurge matricea imaginii in si 
vom face o medie aritmetica cu elementele acestei matrici de marime 
resize_factor*resize_factor, adunand elem si impartind la nr lor, adica 
resize_factor*resize_factor. 

->Daca tipul este "P6", vom face acelasi lucru ca la "P5" doar ca pt 
fiecare elem al pixelului, adica r, g si b.
Aici folosim pixelInt pt a calcula suma elementelor matricii pt 
ca valoarea ar fi trecut de 255.

->In primul for facem paralelizarea, pe coloane (thread-ul cu id-ul 1 va 
lua coloanele 1, 3, 5, 7, ..., iar cel cu id-ul 2 : 2, 4, 6, 8, ...).
Al doilea for parcurge matricea pe latime. Al treilea si al patrulea 
vor parcurge matricea de in de marime resize_factor*resize_factor care 
 corespunde valorii de la out->mat[i][j].


Ex 2

->Avem acelasi structuri image si threadS.

->In initialize vom initializa imaginea astfel: tipul ei va fi "P5"(grayscale), 
img->side va avea valoarea resolution(rezolutia pozei), iar max_rgbval 
va avea valoarea 255.
Alocam o matrice de unsigned int-uri, o parcurgem in 2 for-uri si o 
initializam cu 255(alb).
Functia render va initializa un vector tid de tip pthread_t si thread_id 
tip threadS, va face id = i intr-un for si va face im si thread_id[i].img 
sa pointeze in acelasi loc.
Apoi apelam pthread_create si pthread_join ca in functia resize din ex 1. 

->Functia writeData va scrie intr-un fisier si va creea o imagine. 

->In functia threadFunction, folosind formula de distanta de la o punct la 
o dreapta, vom calcula daca pixel-ul respectiv este alb sau negru. 
In primul for paralelizam pe coloane, iar in al doilea for parcurgem 
matricea pe latime. 
Respectand formula dreptei −1 ∗ x + 2 ∗ y + 0 = 0, calculam distanta 
de la aceasta la fiecare punct din imagine. Daca aceasta este mai mica 
de 3cm, pixel-ul va fi colorat in negru, daca nu va ramane alb. 
+0.5 desemneaza jumatatea pixelului, ce va trebui si ea colorata 
corespunzator.
100/resolution desemneaza spatiul patratic de 100cm*100cm din imagine. 
Coordonatele (0,0) desemneaza coltul stang de jos al imaginii, iar matricea 
este indexata din coltul stanga sus, astfel resolution - i va transforma 
in coordonatele imaginii, pt ca renderul dreptei sa inceapa de stanga jos.

