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
  struct person *thpointer;
  if((thpointer = malloc(sizeof(struct person))) == NULL)
    fprintf(stderr,"Kein Speicherplatz");
  printf("%s %s \n", n, v);
  if(pers != NULL){
    thpointer = pers;
    while(thpointer != NULL){
      if((strcmp(thpointer->nachname, n) == 0) && (strcmp(thpointer->vorname, v) == 0)){
	printf("gefunden \n");
	return thpointer;
      }
      thpointer = thpointer->next;
    }
    thpointer = NULL;
  } else {
    thpointer = NULL;
  }
  return thpointer;
}

void eigen_an_person(char *n, char *v, char *en, char *ew){
  struct person *pointer;
  struct eigenschaft *eig;
  pointer = pers_suchen(n, v);
  if(pointer != NULL){
    if((eig = malloc(sizeof(struct person))) == NULL)
      fprintf(stderr,"Kein Speicherplatz");
    strcpy(eig->eigname, en);
    strcpy(eig->eigwert, ew);
    eig->next = NULL;
    eigen_anhaengen(pointer, eig);
  } else {
    printf("Name nicht gefunden \n");
  }
}

void ausgabe_eig(struct person *p){
  struct eigenschaft *pointer;
  if(p->eig != NULL){
    pointer = p->eig;
    printf(": %s - %s", pointer->eigname, pointer->eigwert);
    while(pointer->next != NULL){
      pointer = pointer->next;
      printf(", %s - %s ", pointer->eigname, pointer->eigwert);
    }
  } else
    printf("keine Eigenschaft da ");
}

void eigen_ausgabe(char *n, char *v){
  struct person *pointer;
  pointer = pers_suchen(n, v);
  ausgabe_eig(pointer);
}

void eigen_eingabe_abfrage(void){
  char n[MAX], v[MAX], en[MAX], ew[MAX];
  char *pointer;
  printf("Nachname : ");
  fgets(n, MAX, stdin);
  pointer = strrchr(n, '\n');
  *pointer = '\0';
  printf("Vorname : ");
  fgets(v, MAX, stdin);
  pointer = strrchr(v, '\n');
  *pointer = '\0';
  printf("Eigenschaft : ");
  fgets(en, MAX, stdin);
  pointer = strrchr(en, '\n');
  *pointer = '\0';
  printf("Wert : ");
  fgets(ew, MAX, stdin);
  pointer = strrchr(ew, '\n');
  *pointer = '\0';
  eigen_an_person(n,v,en,ew);
}

void eigen_ausgabe_abfrage(void){
  char n[MAX], v[MAX];
  char *pointer;
  printf("Nachname : ");
  fgets(n, MAX, stdin);
  pointer = strrchr(n, '\n');
  *pointer = '\0';
  printf("Vorname : ");
  fgets(v, MAX, stdin);
  pointer = strrchr(v, '\n');
  *pointer = '\0';
  eigen_ausgabe(n, v);
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
  int eigwahl;
  do {
    printf("\n1 : print\n");
    printf("2 : Write properties\n");
    printf("Ende: 9\n");
    printf("Auswahl: ");
    scanf("%d", &eigwahl);
    getchar();
    switch(eigwahl){
    case 1 : eigen_ausgabe_abfrage();
      break;
    case 2 : eigen_eingabe_abfrage();
      break;
    case 9 :
      break;
    default :
      printf("Falsche Eingabe!!!\n");
    }
  } while(eigwahl != 9);
}

void menu(void){
  int wahl, i;
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
