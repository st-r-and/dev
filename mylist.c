#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ausgabe(void){
  printf("Hallo\n");
}

void menu(void){
  int wahl;
  do {
    printf("\n1 : Print\n");
    printf("Ende: 9\n");
    printf("Auswahl: ");
    scanf("%d", &wahl);
    getchar();
    switch(wahl){
    case 1 : ausgabe();
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
