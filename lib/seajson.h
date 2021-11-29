//Zachary Keffaber / zachary7829, 2021/10/12, SeaJson 

//NOTE: This code is *really* bad, please use something else

#include <stdio.h>
#include <string.h>

char * getstring(char *funckey, char *dict) {
  char funckey1[strlen(funckey)];
  for (size_t i = 0; i < strlen(funckey); i++) {
    // Access each char in the string
    funckey1[i] = funckey[i];
  }
  int i = 0;
  char test[strlen(dict)];
  for (size_t i = 0; i < strlen(dict); i++) {
    // Access each char in the string
    test[i] = dict[i];
  }
  if (!(funckey1[strlen(funckey1) - 1] == '.')){
    strcat(funckey1,".");
  }
  int testt3, testt4, beginkey, endkey = 0;
  int c = 0;
  int keylength = strlen(funckey1);
  char sub[sizeof test + 1];
  char *returnkey;
  int ignore = 0;
  int instring = 0;
  int tempvar = 0;
  int charindex = 0;
  int dotcount2 = 0;
  int getdot = 0;
  int beginkeysegment = 0;
  int endkeysegment = 0;
  int keysegmentlength = 0;
  char dictkeysegment[sizeof funckey1];
  int c2 = 0;
  //Count number of dots in dictkey
  while (charindex < strlen(funckey1)){
    if (funckey1[charindex] == '.'){
      getdot++;
    } else {
    }
    charindex++;
  }
  charindex = 0;
  //Get part of dictkey after a dot
  while (tempvar == 0){
    if (funckey1[charindex] == '.'){
      dotcount2++;
    } else {
      if (dotcount2 == getdot - 1) {
        keysegmentlength++;
        endkeysegment = charindex;
      }
    }
    charindex++;
    if (!(charindex < sizeof funckey1)) {
      tempvar++;
    }
  }
  beginkeysegment = (endkeysegment - keysegmentlength) + 1;
  while (c2 < keysegmentlength) {
   dictkeysegment[c2] = funckey1[beginkeysegment+c2];
   c2++;
  }
  for(int i = 0; i < sizeof test; ++i) {
    if (test[i] == '\"'){
      //is "
      testt3 = 0;
      testt4 = 0;
      while (testt3 < keylength){
        testt3++;
        if (dictkeysegment[testt3-1] == test[i+testt3]){
          testt4++;
        }
      }
      if (keysegmentlength == testt4){
        testt4 = 0;
        if (test[i + keysegmentlength + 2] == ':'){
          if (test[i + keysegmentlength + 3] == '\"'){
            instring = 1;
          }
          while (testt3){
            if ((test[i + keysegmentlength + 4 + testt4] == '}' || test[i + keysegmentlength + 4 + testt4] == ']') && ignore > 0){
              ignore = ignore - 1;
            } else if (test[i + keysegmentlength + 3 + testt4] == '{' || test[i + keysegmentlength + 3 + testt4] == '['){
              ignore++;
            } else if (((test[i + keysegmentlength + 4 + testt4] == '\"') && instring == 1 && ignore == 0) || ((test[i + keysegmentlength + 4 + testt4] == ',') && instring == 0 && ignore == 0) || ((test[i + keysegmentlength + 4 + testt4] == '}') && instring == 0 && ignore == 0)){
              if (ignore == 0){
                if (test[i + keysegmentlength + 3] == '\"'){
                  beginkey = i + keysegmentlength + 5;
                } else {
                  beginkey = i + keysegmentlength + 4;
                }
                endkey = i + keysegmentlength + 4 + testt4;
                break;
              }
            }
            testt4++;
          }
          while (c < endkey - beginkey + 1) {
            sub[c] = test[beginkey+c-1];
            c++;
          }
          sub[c] = '\0';
          returnkey = sub;
          printf("%sIwouldLikeToRemoveThisButForSomeReasonCant", sub); // I have no idea why but getstring() doesn't work correctly if I don't print it, I don't know why, it just doesn't
        }
      };
    }
  }
  if (c == 0){
    return 0;
  } else {
    return returnkey;
  }
}

char * nonotgetstring(char *funckey, char *dict) {
  char funckey1[strlen(funckey)];
  for (size_t i = 0; i < strlen(funckey); i++) {
    // Access each char in the string
    funckey1[i] = funckey[i];
  }
  int i = 0;
  char test[strlen(dict)];
  for (size_t i = 0; i < strlen(dict); i++) {
    // Access each char in the string
    test[i] = dict[i];
  }
  int testt3, testt4, beginkey, endkey = 0;
  int c = 0;
  int keylength = strlen(funckey1);
  char sub[sizeof test + 1];
  char *returnkey;
  int ignore = 0;
  int instring = 0;
  int tempvar = 0;
  int charindex = 0;
  int beginkeysegment = 0;
  int endkeysegment = sizeof funckey1 - 1;
  int keysegmentlength = sizeof funckey1;
  int c2 = 0;
  for(int i = 0; i < sizeof test; ++i) {
    if (test[i] == '\"'){
      //is "
      testt4 = 0;
      testt3 = 0;
      while (testt3 < keylength){
        testt3++;
        if (funckey1[testt3-1] == test[i+testt3]){
          testt4++;
        }
      }
      if (keysegmentlength == testt4){
        testt4 = 0;
        if (test[i + keysegmentlength + 2] == ':'){
          if (test[i + keysegmentlength + 3] == '\"'){
            instring = 1;
          }
          while (testt3){
            if (test[i + keysegmentlength + 4 + testt4] == '}' && ignore > 0){
              ignore = ignore - 1;
            } else if (test[i + keysegmentlength + 3 + testt4] == '{'){
              ignore++;
            } else if (((test[i + keysegmentlength + 4 + testt4] == '\"') && instring == 1 && ignore == 0) || ((test[i + keysegmentlength + 4 + testt4] == ',') && instring == 0 && ignore == 0) || ((test[i + keysegmentlength + 4 + testt4] == '}') && instring == 0 && ignore == 0)){
              if (ignore == 0){
                if (test[i + keysegmentlength + 3] == '\"'){
                  beginkey = i + keysegmentlength + 5;
                } else {
                  beginkey = i + keysegmentlength + 4;
                }
                endkey = i + keysegmentlength + 4 + testt4;
                break;
              }
            }
            testt4++;
          }
          while (c < endkey - beginkey + 1) {
            sub[c] = test[beginkey+c-1];
            c++;
          }
          sub[c] = '\0';
          returnkey = sub;
          printf("%sIwouldLikeToRemoveThisButForSomeReasonCant", sub); // I have no idea why but getstring() doesn't work correctly if I don't print it, I don't know why, it just doesn't
        }
      };
    }
  }
  if (c == 0){
    return 0;
  } else {
    return returnkey;
  }
}