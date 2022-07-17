#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
void reset() {
    printf("\033[0m");
}

void red() {
    printf("\033[31m");
}

void green() {
    printf("\033[32m");
}

void blue() {
    printf("\033[34m");
}
void horna_cast(){ //horne ohranicenie ramcekov
    printf(" ");

    for(int l = 0; l<15;l++){
        if(l %3==0){
            printf("+");
        }
        printf("-");
    }
    printf("+\n");

}
void uvod(){ //len printf
    printf("Pravidlá:\n"
           "1: maximálny počet pokusov je 6                      |\n"
           "2: slovo musí mať 5 písmen!                          |\n"
           "Nápoveda:\n"
           "1. slová su po anglicky                              |\n"
           "2. keď ti ukáže červenú, môže to naznačovať aj       |\n"
           "   písmeno, ktoré už máš zelené                      |\n");
    red();
    printf("|  červená : netrafil si pozíciu, ale písmenko áno   |\n");
    green();
    printf("|  zelená  :  trafil si pozíciu, aj písmenko         |\n");
    reset();
    printf("|  default :  netrafil si ani pozíciu, ani písmenko  |\n");
}

void pismena(const char slovo[5], const int pozicia_cervena[5], const int pozicia_zelena[5], int counter)
{                  //toto vsetko je vlastne vypisovanie toho stredneho riadku
    int posun = 0; //premenne
    int index = 0;
    printf("%d",counter);
    for(int l = 0; l<5;l++){ //cyklus iba 5 krat pretoze mame 5 pismen a pred kazde davame "|"
            printf("| ");
            if(index == pozicia_cervena[index]){ //zapne sa cervena ked ma
                red();
            }
            if(index == pozicia_zelena[index]){ //zapne sa zelena ak je na tej istej pozicii
                green();
            }
            printf("%c ",slovo[index]); //cez malloc mi neslo farbit takze takto to printujem
            index++;
            posun += 2;
            reset();
    }
    printf("|\n");
}
void dolna_cast(){  //vypisanie dolneho ohranicenia
    printf(" ");
        for(int l = 0; l<15;l++){
            if(l %3==0){
                printf("+");
            }
            printf("-");
        }
        printf("+");
        printf("\n");
}
int main() {
    int pokusy = 1;
    int slovorandom;

    int zelena_index[] = {5, 5, 5, 5, 5};
    int cervena_index[] = {5, 5, 5, 5, 5};

    char scanner[30];
    char pole_slov[][6] = {"apple", "shirt", "chest", "socks", "notes", "smile", "laugh", "thumb", "cabin"};
    //inicalizacia vsetkych premennych


    srand(time(0)); //nastavenie seedu podla aktualneho casu na pc (takze seed je iny zakazdym a nahodnost je velka)
    slovorandom = rand()%9;  //oznacenie pseudo nahodneho cisla ktore bude reprezentovat slovo z pola
                            // %9 aby sme dostali cislo od 0 po 8 (9 cisel) kedze mame 9 slov s indx <0,8>

    uvod();

   // printf("%s\n",pole_slov[slovorandom]); //vyprintovanie slova ktore hadas, odstran koment na testing ak chces
    printf("zadaj slovo: ");
    fflush(stdout);  //pokial sa builduje vo WSL toto NETREBA! ale mingw to potrebuje, pretoze si print nechava nakoniec
                    //takze trocha neprakticke, ale bez toho to na mingw nejde, wsl bez toho je ok
    while(pokusy <7)
    {

        scanf("%s",scanner);
    while(strlen(scanner)!=5){
        red();
        printf("Dĺžka slova musí byť 5 !\n"); //pokial zadane slovo nie je presne na 5 pismen
        reset();
        printf("zadaj slovo: ");
        fflush(stdout);
        scanf("%s",scanner);

    }

    int vyhra = 0;
    for (int i = 0; i < 5; i++)
    {

        if (scanner[i] == pole_slov[slovorandom][i])
        {
            zelena_index[i] = i;
            vyhra++;

        }
        if (scanner[i] != pole_slov[slovorandom][i])
        {
            for (int p = 0; p < 5; p++) {
                if (scanner[i] == pole_slov[slovorandom][p])
                {
                    cervena_index[i] = i;
                }
            }
        }


    }
    horna_cast();                                           //celkove vypisanie pomocou troch voidov
    pismena(scanner, cervena_index, zelena_index,pokusy);
    dolna_cast();

    fflush(stdout);

        if(vyhra ==5){ //pokial sa napocita 5 uhadnutych pismenok da sa print vyhry a program sa ukonci
            green();
            printf("gratulujem ! uhádol si slovo !\n");
            fflush(stdout);
            reset();
            return 0;
        }

    pokusy++; //pocitanie pokusov ktore sa printuju + pouzivaju vo while
    for(int i = 0;i<5;i++){   //resetovanie farieb
        cervena_index[i] = 5;
        zelena_index[i] = 5;
    }

}
    red();
    printf("využil si všetky pokusy !");
    reset();
    return 0;
}