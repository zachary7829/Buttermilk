#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char * getvalue(char *dict, int occurrence, char *name) {
    //system("clear");
    int tempint, testt1, testt2;
    int stringline = 0;
    char *returnkey;
    char dictkey[strlen(dict)];
    for (size_t i = 0; i < strlen(dict); i++) {
      // Access each char in the string
      dictkey[i] = dict[i];
    }
    dictkey[strlen(dict)] = '\0';
    int occurrenceindex = 1;
    FILE *fp = fopen(name, "r");
    char line[100];
    while (fgets(line, sizeof (line), fp)){
      tempint = 0;
      if (stringline == 1){
        testt1 = 0;
        testt2 = 0;
        if (occurrence == occurrenceindex){
          while (tempint < strlen(line)){
            if (line[tempint] == '>' && line[tempint-1] == 'g' && line[tempint-2] == 'n' && line[tempint-3] == 'i' && line[tempint-4] == 'r' && line[tempint-5] == 't' && line[tempint-6] == 's' && line[tempint-7] == '<'){
              testt1 = tempint+1;
              //reminder to not just check for < but for </string> in the future
              while (line[testt1+testt2] != '<' && testt2 < strlen(line) - testt1){
                printf("%c",line[testt1+testt2]);
                testt2++;
              }
              //ok
            }
            tempint++;
          }
          char value[testt2];
          for (size_t i = 0; i < testt2; i++) {
            value[i] = line[testt1+i];
          }
          value[testt2] = '\0';
          returnkey = value;
          return returnkey;
        }
        occurrenceindex++;
        tempint = 0;
        stringline = 0; //when string is found
      }
      while (tempint < strlen(line)){
        //printf("%c",line[tempint]);
        if (line[tempint] == '>' && line[tempint-1] == 'y' && line[tempint-2] == 'e' && line[tempint-3] == 'k' && line[tempint-4] == '<'){
          testt1 = 0;
          testt2 = 0;
          while(line[tempint+testt1+1] != '<' && testt1 < strlen(dictkey)){
            if (line[tempint+testt1+1] == dictkey[testt1]){
              //printf("%c",line[tempint+testt1+1]);
              testt2++;
            }
            testt1++;
          }
          if (testt2 == strlen(dictkey) && testt1 == strlen(dictkey)){
            stringline++;
            /*
            for(int i = 0; i < testt1; ++i) {
              //printf("%c",line[tempint+i+1]);
            } 
            */
          }
        }
        tempint++;
      }
    }

    fclose(fp);
    return 0;
}

int countvalue(char *dict, char *name) {
    //system("clear");
    int c = 0;
    int tempint, testt1, testt2;
    char dictkey[strlen(dict)];
    for (size_t i = 0; i < strlen(dict); i++) {
      // Access each char in the string
      dictkey[i] = dict[i];
    }
    dictkey[strlen(dict)] = '\0';
    FILE *fp = fopen(name, "r");
    char line[100];
    while (fgets(line, sizeof (line), fp)){
      tempint = 0;
      while (tempint < strlen(line)){
        //printf("%c",line[tempint]);
        if (line[tempint] == '>' && line[tempint-1] == 'y' && line[tempint-2] == 'e' && line[tempint-3] == 'k' && line[tempint-4] == '<'){
          testt1 = 0;
          testt2 = 0;
          while(line[tempint+testt1+1] != '<' && testt1 < strlen(dictkey)){
            if (line[tempint+testt1+1] == dictkey[testt1]){
              //printf("%c",line[tempint+testt1+1]);
              testt2++;
            }
            testt1++;
          }
          if (testt2 == strlen(dictkey) && testt1 == strlen(dictkey)){
            c++;
            /*
            for(int i = 0; i < testt1; ++i) {
              //printf("%c",line[tempint+i+1]);
            } 
            */
          }
        }
        tempint++;
      }
    }

    fclose(fp);
    return c;
}