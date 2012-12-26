#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20

struct datum {
  int tag;
  int monat;
  int jahr;
};

struct angestellt {
  char name[MAX];
  char vorname[MAX];
  struct datum alter;
  struct datum eingest;
  long gehalt;
  struct angestellt *next;
};

struct angestellt *next = NULL;
struct angestellt *anfang = NULL;

void anhaengen(char *n, char *v, int at, int am, int aj,
	       int eint, int einm, int einj, long g){
  struct angestellt *zeiger;
  if(anfang == NULL){
    if((anfang = malloc(sizeof(struct angestellt))) == NULL){
      fprintf(stderr, "Kein Speicherplatz vorhanden "
	     "fuer anfang\n");
      return;
    }
    strcpy(anfang->name, n);
    strcpy(anfang->vorname, v);
    anfang->alter.tag = at;
    anfang->alter.monat = am;
    anfang->alter.jahr = aj;
    anfang->eingest.tag = eint;
    anfang->eingest.monat = einm;
    anfang->eingest.jahr = einj;
    anfang->gehalt = g;
    anfang->next = NULL;
  } else {
    zeiger = anfang;
    while(zeiger->next != NULL)
      zeiger = zeiger->next;
    if((zeiger->next = malloc(sizeof(struct angestellt))) == NULL){
      fprintf(stderr, "Kein Speicherplatz fuer das "
	      "letzte Element\n");
      return;
    }
    zeiger = zeiger->next;
    strcpy(zeiger->name, n);
    strcpy(zeiger->vorname, v);
    zeiger->alter.tag = at;
    zeiger->alter.monat = am;
    zeiger->alter.jahr = aj;
    zeiger->eingest.tag = eint;
    zeiger->eingest.monat = einm;
    zeiger->eingest.jahr = einj;
    zeiger->gehalt = g;
    zeiger->next = NULL;
  }
}

void loesche(char *wen){
  struct angestellt *zeiger, *zeiger1;
  if(anfang != NULL){
    if(strcmp(anfang->name, wen) == 0){
      zeiger = anfang->next;
      free(anfang);
      anfang = zeiger;
    } else {
      zeiger = anfang;
      while(zeiger->next != NULL) {
	zeiger1=zeiger->next;
	if(strcmp(zeiger1->name, wen) == 0) {
	  zeiger->next = zeiger1->next;
	  free(zeiger1);
	  break;
	}
	zeiger = zeiger1;
      }
    }
  } else {
    printf("Es sind keine Daten zum Loeschen vorhanden!!!\n");
  }
}

void loesche_alles(void) {
  struct angestellt *zeiger, *zeiger1;

  if(anfang != NULL) {
    zeiger = anfang->next;
    while(zeiger != NULL){
      zeiger1 = anfang->next->next;
      anfang->next= zeiger1;
      free(zeiger);
      zeiger = zeiger1;
    }
    free(anfang->next);
    free(anfang);
    anfang = NULL;
    printf("Liste erfolgreich geloescht!!!\n");
  } else {
    fprintf(stderr,"Keine Liste zum Loeschen vorhanden!!\n");
  }
}

void ausgabe(void) {
  struct angestellt *zeiger = anfang;
  printf("||=======================================================||\n");
  printf("|%10cName%10c |Geburtsdatum|Eingestellt|Gehalt|\n",' ',' ');
  printf("||=======================================================||\n");
  while(zeiger != NULL) {
    printf("|%12s,%-12s| %02d.%02d.%04d| %02d.%02d.%04d| %06ld|\n",
	   zeiger->name,zeiger->vorname,
	   zeiger->alter.tag,zeiger->alter.monat,zeiger->alter.jahr,
	   zeiger->eingest.tag,zeiger->eingest.monat,zeiger->eingest.jahr,
	   zeiger->gehalt);
    printf("|---------------------------------------------------------|\n");
    zeiger=zeiger->next;
  }
}

void eingabe(void) {
  char nam[MAX], vorn[MAX];
  int atag, amon, ajahr, eintag, einmon, einjahr;
  long gehalt;
  char *ptr;
  printf("Name.............................: ");
  fgets(nam, MAX, stdin);
  ptr = strrchr(nam, '\n');
  *ptr = '\0';
  printf("Vorname..........................: ");
  fgets(vorn, MAX, stdin);
  ptr = strrchr(vorn, '\n');
  *ptr = '\0';
  printf("Alter...........(tt.mm.jjjj).....: ");
  scanf("%2d.%2d.%4d", &atag, &amon, &ajahr);
  printf("Eingestellt am..(tt.mm.jjjj).....: ");
  scanf("%2d.%2d.%4d", &eintag, &einmon, &einjahr);
  printf("Monatsgehalt.....................: ");
  scanf("%ld", &gehalt);
  getchar();
  anhaengen(nam, vorn, atag, amon, ajahr, 
	    eintag, einmon, einjahr, gehalt);
}

int main(void) {
  int wahl;
  char dname[MAX];
  do {
    printf("\n1 : Eingabe\n");
    printf("2 : Ausgabe\n");
    printf("3 : Name loeschen\n");
    printf("Ende: 9\n");
    printf("Ihre Wahl : ");
    scanf("%d", &wahl);
    getchar();
    switch(wahl){
    case 1 : eingabe();
      break;
    case 2 : ausgabe();
      break;
    case 3 : printf("Der Name zum loeschen: ");
      fgets(dname, MAX, stdin);
      loesche(strtok(dname, "\n")); 
      break;
    case 9 : break;
    default: printf("Falsche Eingabe!!!\n");
    }
  } while(wahl != 9);
  return EXIT_SUCCESS;
}
