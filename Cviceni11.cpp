

#include "Cviceni11.h"

using namespace std;

struct album {
    char interpret[50];
    char nazevAlba[50];
    int rokVydani;
    struct album* dalsi;
}; // Definuje strukturu 'album' s daty o albu.

struct album* prvni = NULL; // globální ukazatel na první album

void show() // Funkce pro tisk alb vydaných po zadaném roce.
{
    int zvolenyRok;
    printf("Zadejte rok, po kterem chcete hledat alba: ");
    scanf("%d", &zvolenyRok);

    struct album* aktAlbum = prvni; // ukazatel na aktuální album
    int nalezeno = 0;

    while (aktAlbum) // procházení seznamu
    {
        if (aktAlbum->rokVydani > zvolenyRok) {
            printf("%s - %s (%d)\n", aktAlbum->interpret, aktAlbum->nazevAlba, aktAlbum->rokVydani);
            nalezeno = 1;
        }
        aktAlbum = aktAlbum->dalsi; // posun na další album
    }

    if (!nalezeno) {
        printf("Nebyly nalezeny zadne zaznamy vydane po roce %d.\n", zvolenyRok);
    }
}
 
void add(const char* interpret, const char* nazevAlba, int rokVydani) {  // Funkce pro přidání nového alba.
    struct album* noveAlbum = (struct album*)malloc(sizeof(struct album));
    if (noveAlbum == NULL) {
        printf("Chyba pri alokaci pameti pro nove album.\n");
        return;
    }
    strcpy(noveAlbum->interpret, interpret);
    strcpy(noveAlbum->nazevAlba, nazevAlba);
    noveAlbum->rokVydani = rokVydani;
    noveAlbum->dalsi = NULL;

    struct album** ukazatel = &prvni;
    while (*ukazatel && strcmp((*ukazatel)->interpret, interpret) < 0) {
        ukazatel = &(*ukazatel)->dalsi;
    }
    noveAlbum->dalsi = *ukazatel;
    *ukazatel = noveAlbum;
}

void deleteAlbum(const char* interpret) { // Funkce pro odstranění alba podle interpreta.
    struct album** ukazatel = &prvni;
    while (*ukazatel && strcmp((*ukazatel)->interpret, interpret) != 0) {
        ukazatel = &(*ukazatel)->dalsi;
    }
    if (*ukazatel != NULL) {
        struct album* tempAlbum = *ukazatel;
        *ukazatel = tempAlbum->dalsi; // Přepojení ukazatele před smazáním
        free(tempAlbum);
    }
}

int main() {
    char volba;
    char interpret[50];
    char nazevAlba[50];
    int rokVydani;


    do {
        printf("\nA: Pridat D: Smazat P: Tisk Q: Konec\n");
        printf("Zadejte volbu: ");
        scanf(" %c", &volba);

        switch (volba) {
        case 'A':
            printf("Zadejte jmeno interpreta: ");
            scanf("%49s", interpret); // Zabrání přetečení bufferu
            printf("Zadejte nazev alba: ");
            scanf("%49s", nazevAlba);
            printf("Zadejte rok vydani: ");
            scanf("%d", &rokVydani);
            add(interpret, nazevAlba, rokVydani);
            printf("Pridano: %s - %s (%d)\n", interpret, nazevAlba, rokVydani);
            break;
        case 'D':
            printf("Zadejte jmeno interpreta, ktereho chcete smazat: ");
            scanf("%49s", interpret);
            deleteAlbum(interpret);
            break;
        case 'P':
            show();
            break;
        case 'Q':
            printf("Ukonceni programu.\n");
            break;
        default:
            printf("Neplatna volba!\n");
        }
    } while (volba != 'Q' && volba != 'q');

    struct album* aktAlbum = prvni;
    while (aktAlbum != NULL) {
        struct album* tempAlbum = aktAlbum;
        aktAlbum = aktAlbum->dalsi;
        free(tempAlbum); // Uvolnění paměti pro každé album
    }

    return 0;
}

