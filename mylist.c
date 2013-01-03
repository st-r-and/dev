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

void eigen_anhaengen(struct person *p, struct eigenschaft *e){
  struct eigenschaft *pointer;
  if(p->eig == NULL){
    if((p->eig = malloc(sizeof(struct eigenschaft))) == NULL){
      fprintf(stderr, "Kein Speicherplatz");
      return;
    }
    pointer = p->eig;
    strcpy(pointer->eigname, e->eigname);
    strcpy(pointer->eigwert, e->eigwert);
    pointer->next = NULL;
  } else {
    pointer = p->eig;
    while(pointer->next != NULL)
      pointer = pointer->next;
    if((pointer->next = malloc(sizeof(struct eigenschaft))) == NULL){
      fprintf(stderr, "Kein Speicherplatz");
      return;
    }
    pointer = pointer->next;
    strcpy(pointer->eigname, e->eigname);
    strcpy(pointer->eigwert, e->eigwert);
    pointer->next = NULL;
  }
}


struct person *pers_suchen(char *n, char *v){
  struct person *pointer;
  if(pers != NULL){
    pointer = pers;
    while(pointer->next != NULL){
      if((strcmp(pointer->nachname, n) == 0) && (strcmp(pointer->vorname, v) == 0)){
	printf("gefunden \n");
	return pointer;
      }
      pointer = pointer->next;
    }
    pointer = NULL;
  } else {
    pointer = NULL;
  }
  return pointer;
}

void eigen_an_person(char *n, char *v, char *en, char *ew){
  struct person *pointer;
  pointer = pers_suchen(n, v);
  if(pointer != NULL){
    struct eigenschaft *eig;
    strcpy(eig->eigname, en);
    strcpy(eig->eigwert, ew);
    eig->next = NULL;
    eigen_anhaengen(pointer, eig);
  } else {
    printf("Name nicht gefunden \n");
  }
}

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

void ausgabe_eig(struct person *p){
  if(p != NULL)
    printf("Eigenschaften vorhanden ");
}

void ausgabe(void){
  struct person *pointer = pers;
  while(pointer != NULL) {
    printf("%s - %s ", pointer->nachname, pointer->vorname);
    if(pointer->eig != NULL){
      ausgabe_eig(pointer);
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
  pers_anhaengen(naname, voname);
}

void eigen_menu(void){
  printf ("properties \n");
  int wahl;
  do {
    printf("\n1 : print\n");
    printf("2 : Write properties\n");
    printf("Ende: 9\n");
    printf("Auswahl: ");
    scanf("%d", &wahl);
    getchar();
    switch(wahl){
    case 1 : printf("Nachname : \n");
      printf("Vorname : \n");
      break;
    case 2 : printf("Nachname : \n");
      printf("Vorname : \n");
      printf("Eigenschaft : \n");
      printf("Wert : \n");
      break;
    case 9 :
      break;
    default :
      printf("Falsche Eingabe!!!\n");
    }
  } while(wahl != 9);
}

void menu(void){
  int wahl;
  do {
    printf("\n1 : Print\n");
    printf("2 : Write person\n");
    printf("3 : properties menu\n");
    printf("Ende: 9\n");
    printf("Auswahl: ");
    scanf("%d", &wahl);
    getchar();
    switch(wahl){
    case 1 : ausgabe();
      break;
    case 2 : pers_eingabe();
      break;
    case 3 : eigen_menu();
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
