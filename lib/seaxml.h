//Zachary Keffaber / zachary7829, 2021/11/29, SeaXML

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
            if ((line[tempint] == '>' && line[tempint-1] == 'g' && line[tempint-2] == 'n' && line[tempint-3] == 'i' && line[tempint-4] == 'r' && line[tempint-5] == 't' && line[tempint-6] == 's' && line[tempint-7] == '<') || (line[tempint] == '>' && line[tempint-1] == 'r' && line[tempint-2] == 'e' && line[tempint-3] == 'g' && line[tempint-4] == 'e' && line[tempint-5] == 't' && line[tempint-6] == 'n' && line[tempint-7] == 'i' && line[tempint-8] == '<') || (line[tempint] == '>' && line[tempint-1] == '/' && line[tempint-2] == 'e' && line[tempint-3] == 'u' && line[tempint-4] == 'r' && line[tempint-5] == 't' && line[tempint-6] == '<') || (line[tempint] == '>' && line[tempint-1] == '/' && line[tempint-2] == 'e' && line[tempint-3] == 's' && line[tempint-4] == 'l' && line[tempint-5] == 'a' && line[tempint-6] == 'f' && line[tempint-7] == '<')){
              if (line[tempint] == '>' && line[tempint-1] == '/' && line[tempint-2] == 'e' && line[tempint-3] == 'u' && line[tempint-4] == 'r' && line[tempint-5] == 't' && line[tempint-6] == '<'){
                testt1 = tempint - 6;
                testt2 = tempint;
            } else {
              if (line[tempint] == '>' && line[tempint-1] == '/' && line[tempint-2] == 'e' && line[tempint-3] == 's' && line[tempint-4] == 'l' && line[tempint-5] == 'a' && line[tempint-6] == 'f' && line[tempint-7] == '<') {
                testt1 = tempint - 7;
                testt2 = tempint;
              } else {
              testt1 = tempint+1;
              //reminder to not just check for < but for </string> in the future
              while (line[testt1+testt2] != '<' && testt2 < strlen(line) - testt1){
                printf("%c",line[testt1+testt2]);
                testt2++;
              }
              //ok
                }
              }
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

char *getdict(char *dict, int occurrence, char *name, int occurrence2) {
    //system("clear");
    int tempint, testt1, testt2;
    int dictionarypromotion = 0;
    int stringline = 0;
    char keyindict[100]; //change from fixed 100 size latr
    char *returnkey;
    char dictkey[strlen(dict)];
    for (size_t i = 0; i < strlen(dict); i++) {
      // Access each char in the string
      dictkey[i] = dict[i];
    }
    dictkey[strlen(dict)] = '\0';
    int occurrenceindex = 1;
    int occurrence2index = 1;
    FILE *fp = fopen(name, "r");
    char line[100];
    while (fgets(line, sizeof (line), fp)){
      tempint = 0;
      if (dictionarypromotion > 0){
        while (tempint < strlen(line)){
          if (line[tempint] == '>' && line[tempint-1] == 't' && line[tempint-2] == 'c' && line[tempint-3] == 'i' && line[tempint-4] == 'd' && line[tempint-5] == '<'){
            dictionarypromotion++;
          }
          if (line[tempint] == '>' && line[tempint-1] == 't' && line[tempint-2] == 'c' && line[tempint-3] == 'i' && line[tempint-4] == 'd' && line[tempint-5] == '/' && line[tempint-6] == '<'){
            dictionarypromotion -= 1;
          }
          if (line[tempint] == '>' && line[tempint-1] == 'y' && line[tempint-2] == 'e' && line[tempint-3] == 'k' && line[tempint-4] == '<'){
            if (occurrence2 == occurrence2index){
            testt1 = 0;
            testt2 = 0;
            while(line[tempint+testt1+1] != '<' && testt1 < strlen(line)-tempint){
              keyindict[testt1] = line[tempint+testt1+1];
              keyindict[testt1+1] = '\0';
              testt1++;
            }
            keyindict[strlen(keyindict)] = '\0';
            char value[strlen(keyindict)]; //end of keyindict won't be right and I don't know how to make it correct so instead we are just getting the correct chars in keyindict for value
            for (size_t i = 0; i < strlen(keyindict); i++) {
              value[i] = keyindict[i];
            }
            value[strlen(keyindict)] = '\0';
            returnkey = value;
            printf("%s",returnkey);
            return returnkey;
            }
            occurrence2index++;
            }
            tempint++;
          }
        }
      tempint = 0;
      if (stringline == 1){
        testt1 = 0;
        testt2 = 0;
        if (occurrence == occurrenceindex){
          while (tempint < strlen(line)){
            if (line[tempint] == '>' && line[tempint-1] == 't' && line[tempint-2] == 'c' && line[tempint-3] == 'i' && line[tempint-4] == 'd' && line[tempint-5] == '<'){
                dictionarypromotion++;
              }
              tempint++;
            }
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

char *getdictkeyvalue(char *dict, int occurrence, char *name, int occurrence2, char *specifiedkeyindict) {
    //system("clear");
    int tempint, testt1, testt2, checkcorrect;
    int dictionarypromotion = 0;
    int dictstringline = 0;
    int stringline = 0;
    char keyindict[100]; //change from fixed 100 size latr
    char *returnkey;
    char dictkey[strlen(dict)];
    for (size_t i = 0; i < strlen(dict); i++) {
      // Access each char in the string
      dictkey[i] = dict[i];
    }
    dictkey[strlen(dict)] = '\0';
    int occurrenceindex = 1;
    int occurrence2index = 1;
    FILE *fp = fopen(name, "r");
    char line[100];
    while (fgets(line, sizeof (line), fp)){
      tempint = 0;
      if (dictionarypromotion > 0){
        while (tempint < strlen(line)){
          if (line[tempint] == '>' && line[tempint-1] == 't' && line[tempint-2] == 'c' && line[tempint-3] == 'i' && line[tempint-4] == 'd' && line[tempint-5] == '<'){
            dictionarypromotion++;
          }
          if (line[tempint] == '>' && line[tempint-1] == 't' && line[tempint-2] == 'c' && line[tempint-3] == 'i' && line[tempint-4] == 'd' && line[tempint-5] == '/' && line[tempint-6] == '<'){
            dictionarypromotion -= 1;
          }
          if (line[tempint] == '>' && line[tempint-1] == 'y' && line[tempint-2] == 'e' && line[tempint-3] == 'k' && line[tempint-4] == '<'){
            if (occurrence2 == occurrence2index){
            testt1 = 0;
            testt2 = 0;
            while(line[tempint+testt1+1] != '<' && testt1 < strlen(line)-tempint){
              keyindict[testt1] = line[tempint+testt1+1];
              keyindict[testt1+1] = '\0';
              testt1++;
            }
            keyindict[strlen(keyindict)] = '\0';
            char value[strlen(keyindict)]; //end of keyindict won't be right and I don't know how to make it correct so instead we are just getting the correct chars in keyindict for value
            for (size_t i = 0; i < strlen(keyindict); i++) {
              value[i] = keyindict[i];
            }
            value[strlen(keyindict)] = '\0';
            checkcorrect = 0;
            for (size_t i = 0; i < strlen(specifiedkeyindict); i++) {
              if (specifiedkeyindict[i] == value[i]){
                checkcorrect++;
              }
            }
            if (checkcorrect == strlen(value)){
              stringline++;
              dictstringline++;
              occurrenceindex -= 2;
            }
            checkcorrect = 0;
            }
            occurrence2index++;
            }
            tempint++;
          }
        }
      tempint = 0;
      if (stringline == 1){
        testt1 = 0;
        testt2 = 0;
        if (occurrence == occurrenceindex){
          while (tempint < strlen(line)){
            if (line[tempint] == '>' && line[tempint-1] == 't' && line[tempint-2] == 'c' && line[tempint-3] == 'i' && line[tempint-4] == 'd' && line[tempint-5] == '<'){
              dictionarypromotion++;
            }
            if ((line[tempint] == '>' && line[tempint-1] == 'g' && line[tempint-2] == 'n' && line[tempint-3] == 'i' && line[tempint-4] == 'r' && line[tempint-5] == 't' && line[tempint-6] == 's' && line[tempint-7] == '<') || (line[tempint] == '>' && line[tempint-1] == 'r' && line[tempint-2] == 'e' && line[tempint-3] == 'g' && line[tempint-4] == 'e' && line[tempint-5] == 't' && line[tempint-6] == 'n' && line[tempint-7] == 'i' && line[tempint-8] == '<') || (line[tempint] == '>' && line[tempint-1] == '/' && line[tempint-2] == 'e' && line[tempint-3] == 'u' && line[tempint-4] == 'r' && line[tempint-5] == 't' && line[tempint-6] == '<') || (line[tempint] == '>' && line[tempint-1] == '/' && line[tempint-2] == 'e' && line[tempint-3] == 's' && line[tempint-4] == 'l' && line[tempint-5] == 'a' && line[tempint-6] == 'f' && line[tempint-7] == '<')){
              if (line[tempint] == '>' && line[tempint-1] == '/' && line[tempint-2] == 'e' && line[tempint-3] == 'u' && line[tempint-4] == 'r' && line[tempint-5] == 't' && line[tempint-6] == '<'){
                testt1 = tempint - 6;
                testt2 = tempint;
            } else {
              if (line[tempint] == '>' && line[tempint-1] == '/' && line[tempint-2] == 'e' && line[tempint-3] == 's' && line[tempint-4] == 'l' && line[tempint-5] == 'a' && line[tempint-6] == 'f' && line[tempint-7] == '<') {
                testt1 = tempint - 7;
                testt2 = tempint;
              } else {
              testt1 = tempint+1;
              //reminder to not just check for < but for </string> in the future
              while (line[testt1+testt2] != '<' && testt2 < strlen(line) - testt1){
                printf("%c",line[testt1+testt2]);
                testt2++;
              }
              //ok
                }
              }
            }
            tempint++;
            }
            if (testt1 > 0){
              char newvalue[testt2];
              for (size_t i = 0; i < testt2; i++) {
                newvalue[i] = line[testt1+i];
              }
              newvalue[testt2] = '\0';
              returnkey = newvalue;
              return returnkey;
            }
          }
        occurrenceindex++;
        tempint = 0;
        stringline = 0; //when string is found
        stringline = dictstringline;
        dictstringline = 0;
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
