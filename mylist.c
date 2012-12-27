#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

struct eigenschaft {
  char eigname[MAX];
  char eigwert[MAX];
  struct eigenschaft *next;
};

struct person {
  char nachname[MAX];
  char vorname[MAX];
  struct eigenschaft *eig;
  struct person *next;
};

struct person *pers = NULL;

void pers_anhaengen(char *n, char *v){
  struct person *pointer;
  if(pers == NULL){
    if((pers = malloc(sizeof(struct person))) == NULL){
      fprintf(stderr, "Kein Speicherplatz");
      return;
    }
    strcpy(pers->nachname, n);
    strcpy(pers->vorname, v);
    pers->eig = NULL;
    pers->next = NULL;
  } else {
    pointer = pers;
    while(pointer->next != NULL)
      pointer = pointer->next;
    if((pointer->next = malloc(sizeof(struct person))) == NULL){
      fprintf(stderr, "Kein Speicherplatz");
      return;
    }
    pointer = pointer->next;
    strcpy(pointer->nachname, n);
    strcpy(pointer->vorname, v);
    pointer->eig = NULL;
    pointer->next = NULL;
  }
}

void ausgabe_eig(char *n, char *v){
  printf("Hallo\n");
}

void ausgabe(void){
  struct person *pointer = pers;
  while(pointer != NULL) {
    printf("%s - %s ", pointer->nachname, pointer->vorname);
    if(pointer->eig != NULL){
      ausgabe_eig(pointer->nachname, pointer->vorname);
    } else {
      printf("keine Eigenschaften");
    }
    printf("\n");
    pointer = pointer->next;
  }
}

void pers_eingabe(void){
  char naname[MAX], voname[MAX];
  char *pointer;
  printf("Nachname   : ");
  fgets(naname, MAX, stdin);
  pointer = strrchr(naname, '\n');
  *pointer = '\0';
  printf("Vorname    : ");
  fgets(voname, MAX, stdin);
  pointer = strrchr(voname, '\n');
  *pointer = '\0';
  //getchar();
  pers_anhaengen(naname, voname);
}

void menu(void){
  int wahl;
  do {
    printf("\n1 : Print\n");
    printf("2 : Write person\n");
    printf("Ende: 9\n");
    printf("Auswahl: ");
    scanf("%d", &wahl);
    getchar();
    switch(wahl){
    case 1 : ausgabe();
      break;
    case 2 : pers_eingabe();
      break;
    case 9 :
      break;
    default :
      printf("Falsche Eingabe!!!\n");
    }
  } while(wahl != 9);
}

int main(void){
  menu();
  return EXIT_SUCCESS;
}
