#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WSIZE 30

/*
Task (PL) :
 Zaprogramowa� � zgodnie z przydzielonym wariantem �
wybrane operacje na tablicy z haszowaniem z adresowaniem otwartym oraz przeprowadzi�
odpowiednie testy/pomiary. Operacje przetestowa� na ma�ej tablicy, z wydrukiem kontrolnym,
natomiast w�a�ciwe testy/pomiary, wraz z kr�tkim opisem ich wyniku, przeprowadzi�
na kilku tablicach o wi�kszych i r�nych rozmiarach, np. rz�du kilku tysi�cy.
W tablicy haszowa� maj� by� struktury zawieraj�ce dwa pola:
� liczba � typu int;
� nazwisko � ci�g znak�w.
Kluczami maj� by� nazwiska (patrz przyk�adowe schematy zamiany w ALL.10.2). W
tablicy haszowa� mog� znajdowa� si� wska�niki na te struktury b�d� ca�e struktury. Pod
adresem www.futrega.org/etc/nazwiska.html znajduje si� wykaz zapis�w postaci
X Nazwisko,
gdzie X jest liczb� typu int okre�laj�c� popularno�� nazwiska Nazwisko. Mo�na wykorzysta�
ten plik do test�w.
Warianty operacji i pomiar�w
[W] Operacja WSTAW. Dany test nale�y wykona� przy r�nych wype�nieniach tablicy
rozmiaru m: 50%, 70% i 90%. Przy danym wype�nieniu tablicy wykonujemy 5m/100
operacji wstawienia elementu do tablicy i wyznaczamy �redni� liczby pr�b ze wstawienia
wszystkich testowanych element�w.
[U] Operacje USU�. Po wype�nieniu tablicy do 80% usuwamy po�ow� wstawionych element�w
(co drugi w kolejno�ci wstawiania), a nast�pnie znowu dope�niamy tablic� innymi
elementami (do tego samego stopnia zape�nienia). Po wykonaniu tych operacji zliczy�, ile
pozycji w tablicy jest wype�nionych znacznikiem DEL (miejsce po usuni�tym elemencie).
Warianty techniki rozwi�zywania kolizji
[OL] adresowanie otwarte liniowe
[OK] adresowanie otwarte kwadratowe
[OD] adresowanie otwarte podw�jne
Kombinacje wariant�w: [W+OL], [W+OK], [W+OD], [U+OL], [U+OK], [U+OD].
*/
// Jan Bienias
// Wariant : OK + U

typedef struct Dane{
    int liczba;
    char *nazwisko;
}dane;

int H(int k, int i, int size)
{
//[OK] adresowanie otwarte kwadratowe
//h(k) = k mod SIZE
//H(k, i) = (h(k) + i*i) mod SIZE
    int wynik;
    k = k%size;
    wynik = (k+i*i)%size;
    return wynik;
}

int string_to_int(char *slowo)
{
    int i;
    int wynik = 0;
    int x = 1;
    for(i=0; i<strlen(slowo); i++)
    {
        if((int)slowo[i] != 32)
            wynik = wynik * x + (int)slowo[i];
    }
    return wynik;
}

int HashInsert(dane T[], char* name, int size)
{
// warto�� NIL w tablicy to miejsce wolne == 0
// warto�� DEL w tablicy to miejsce po usuni�tym elemencie == -1

    int i, j;
    int x = 0;
    x = string_to_int(name);
    i = 0;
    do
    {
        j=H(x,i, size);
        if (T[j].liczba == 0 || T[j].liczba == -1) // -1 -> nasz DEL
        {
            //jesli bedzie mozna wstawic , licznik ++
            T[j].nazwisko = name;
            T[j].liczba = x;
            return j;
        }
        i=i+1;
    }
    while(i < size);
    //printf("Nie udalo sie wstawic elementu [%d] do tablicy haszujacej!\n", x);
    //licznik nieudanych prob wstawienia ++
    return 0;
}

int HashSearch(dane T[], char* name, int size)
{
// szuka klucza-slowo name w tablicy z haszowaniem T
    int i, j;
    int x = 0;
    x = string_to_int(name);
    i = 0;
    do
    {
        j=H(x,i,size);
        if(T[j].liczba == x)
        {
            printf("Udalo sie znalezc element [%s](%d) w tablicy haszujacej na poz. [%d]\n", name, x, j);
            return 1;
        }
        i=i+1;
    }
    while(T[j].liczba != 0 && i<size);
    printf("Nie udalo sie znalezc elementu [%s](%d) w tablicy haszujacej!\n", name, x);
    return 0;
}

int HashDelete(dane T[], int j, int size)
{
// usuwa element z pozycji j w tablicy T wpisuj�c na t� pozycj� znacznik DEL
    if(j < size)
    {
        T[j].liczba = -1;
        T[j].nazwisko = "DEL";
        return j;
    }
    return 0;
}


int max_len(char **tab, int ilosc_linii)
{
    int i, max=0;
    for(i=0;i<ilosc_linii;i++)
    {
        if(strlen(tab[i])>max)
        {
            max=strlen(tab[i]);
        }
    }
    return max;
}

void same_len(char **tab, int ilosc_linii, int max)
{
    int i, j;
    for (i=0; i<ilosc_linii; i++)
        for (j=strlen(tab[i]); j<max; j++)
            tab[i][j]=' ';
}

int lines_number(char *name)
{
	FILE *file = fopen(name, "r");
	if (file == NULL)
	{
		printf("\nNie mozna otworzyc pliku %s!\n", name);
		exit(0);
	}
	int counter=0;
	int ch;

	do
	{
		ch = fgetc(file);
		if(ch == '\n')
			counter++;
	} while (ch != EOF);

	if(ch != '\n' && counter != 0)
		counter++;

	fclose(file);
	return counter;
}

void stringarray_to_intarray(char **tab1, dane tab2[], int ilosc_linii, int max)
{
//w zmiennej "wynik" dajemy jakies wymyslone przez nas kodowanie znaku
//np. horner ze stala "x"
    int i, j;
    int wynik;
    int x = 1; //stala
    for (i=0; i<ilosc_linii; i++)
    {
        wynik = 0;
        for (j=0; j<max; j++)
        {
            if((int)tab1[i][j] != 32)
                wynik = wynik * x + (int)tab1[i][j];
                //wynik += (int)tab1[i][j];
        }
        tab2[i].liczba = wynik;
        tab2[i].nazwisko = tab1[i];
    }
}

void read_from_file(char **tab, char *name, int ilosc_linii)
{
    FILE *file;
    file = fopen(name, "r");
	if (file == NULL)
	{
		printf("\nNie mozna otworzyc pliku %s!\n", name);
		exit(0);
	}
    int i;
    for(i=0; i<ilosc_linii; i++)
    {
        int tmp;
        char slowo[WSIZE];
        fscanf(file, "%d", &tmp);
        fscanf(file, "%s", slowo);
        tab[i] = (char*)malloc(WSIZE * sizeof(char));
        strcpy(tab[i],slowo);
    }
    fclose(file);
}

void array_reset(dane arr[], int size)
{
    int i;
    for(i = 0; i<size; i++)
    {
        arr[i].liczba = 0;
        arr[i].nazwisko = NULL;
    }
}

void array_print(dane T[], int size)
{
    int i;
    for(i=0; i<size; i++)
    {
        printf("%-4d. [%s](%d)\n",i, T[i].nazwisko, T[i].liczba);
    }
}

int wypelnienie(dane T[], int size)
{
    int i;
    int count = 0;
    for(i=0; i<size; i++)
    {
        if(T[i].liczba != 0 && T[i].liczba != -1)
        {
            count++;
        }
    }
    return count;
}

void array_print_S(char **t, int size)
{
    int i;
    for(i=0; i<size; i++)
    {
        printf("[%s]\n",t[i]);
    }
}

void array_print_I(int t[], int size)
{
    int i;
    for(i=0; i<size; i++)
    {
        printf("[%d]\n",t[i]);
    }
}

void array_reset_I(int t[], int size)
{
    int i;
    for(i=0; i<size; i++)
    {
        t[i] = 0;
    }
}

int array_del_spots(dane T[], int size)
{
    int i;
    int count = 0;
    for(i=0; i<size; i++)
    {
        if(T[i].liczba == -1)
        {
            count++;
        }
    }
    return count;
}

int main()
{
    char *file_name = "nazwiska.txt";
    int n;
    n = lines_number(file_name);
    char **S;
    S = (char**) malloc(n * sizeof(char*));
    dane Sint[n]; //tablica z kodowaniem Stringow na liczby
    read_from_file(S,file_name, n);
    //int max = max_len(S, n);
    //same_len(S, n, max);
    stringarray_to_intarray(S, Sint, n, WSIZE);
    //array_print_S(S, 100);

    //printf("\n%s\n", S[1]);

    /* TEST
    int size = 10;
    dane T[size];
    array_reset(T, size);
    HashInsert(T, "Pomarancza", size);
    HashInsert(T, "Morawiecki", size);
    HashInsert(T, "Kowalski", size);
    HashInsert(T, "Bienias", size);
    HashInsert(T, "Bienias", size);
    array_print(T,size);
    printf("\n");
    HashSearch(T, "Kowalski", size);
    HashSearch(T, "Bienias", size);
    HashSearch(T, "Cienias", size);
    HashDelete(T, 4, size);
    printf("\n");
    array_print(T, size);
    printf("\n");
    */

    int m[] = {1000,1019,2000, 2003, 3000, 3023, 6000, 6007}; //4 pozytywne, 4 negatywne
    int i;
    printf("========================================================\n");
    for(i=0; i<8; i++)
    {
        dane T[m[i]];
        array_reset(T, m[i]);
        int kontrolka = 0.8 * m[i];
        //printf("Kontrolka = %d\n", kontrolka);
        int tmp[kontrolka]; //tablica indexow insertowanych danych do tab haszujacej
        array_reset_I(tmp, kontrolka);
        int j = 0;
        //Wypelnianie tablicy m[i] do 80%
        while(j < kontrolka)
        {
            tmp[j] = HashInsert(T, S[j], m[i]);
            j++;
        }
        printf("Zajete miejsca (poczatek) : \t\t\t%d\n", wypelnienie(T, m[i]));
        //Usuwanie co drugi element (co drugi wstawiony index)
        j = 1;
        while(j < kontrolka)
        {
            HashDelete(T, tmp[j], m[i]);
            j=j+2;
        }
        printf("Zajete miejsca (polowa poczatku) : \t\t%d\n", wypelnienie(T, m[i]));
        //array_print(T, m[i]);
        //array_print_I(tmp, kontrolka);
        //Ponowne wypelnianie do 80%
        j = wypelnienie(T, m[i]); //polowa z 0.8 * size
        int z=0;
        while(j < kontrolka)
        {
            HashInsert(T, S[kontrolka+z], m[i]);
            j++;
            z++;
        }
        printf("Zajete miejsca (do liczby poczatkowej) : \t%d\n", wypelnienie(T, m[i]));
        int wynik;
        wynik = array_del_spots(T, m[i]);
        printf("TAB[%d] - ilosc. miejsc usunietych\t\t%d DEL\n", m[i], wynik);
        printf("========================================================\n");
    }


}
