//Zachary Keffaber, 2021/11/5, ButtermilkParamParser

#include <stdio.h>
#include <string.h>

char *butterparam(char *line, int type, int occurrence) {
  char *returnkey = "NULL"; //making returnkey a string that says NULL rather than actually being null. Maximum trolling capacity
  int c = 0;
  int occurrenceindex = 1;
  int charindex = 0;
  int charindex2 = 0;
  int charindex3 = 0;
  int tempint = 0;
  int instring = 0;
  char newparams[strlen(line)];
  char newvalue[strlen(line)];
 
  //fp=fopen("testwrite.txt", "w");
  //fprintf(fp, "aba");
  //fclose(fp);
    charindex = 0;
    charindex2 = 0;
    tempint = 0;
    c = 0;
    while (tempint == 0){
      if (line[charindex] == '(' || line[charindex] == ','){
        if (occurrence != occurrenceindex){
          occurrenceindex++;
        } else {
          tempint++;
        }
      }
      charindex++;
    }
    tempint = 0; //ignore spaces
    while (tempint == 0){
      if (line[charindex] == ' '){
        charindex++;
      } else {
        tempint++;
      }
    }
    tempint = 0;
    while (charindex+tempint<strlen(line)){
      if (line[charindex+tempint] == ')' || line[charindex+tempint] == ','){
        charindex2 = tempint;
      }
      tempint++;
    }
    tempint = 0;
    if (charindex+1==charindex2){
      return 0;
    }
    char params[charindex2];
    char value[charindex2];
    memcpy(params,&line[charindex],charindex2);
    params[charindex2] = '\0';
    //value[c] = '\0';
    charindex = 0;
    charindex2 = 1;
    charindex3 = 0;
    c = 0;
    instring = 0;
    for(int i = 0; i < strlen(params); ++i) {
      if (params[i] == '\"' && (!(params[i-1] == '\\'))){
        if (instring == 1) {
          instring = 0;
        } else {
          instring = 1;
        }
      }
      if (instring == 0 && params[i] == '=' && (!(params[i-1] == '\\'))){
        //printf("\nThis is me!!! i = %d charindex = %d params = %s\n",i,charindex,params);
        //the below while is where the printf issue is
        while (params[i-charindex-1] == ' ' && i-charindex > 0){
          charindex++;
        }
        //deadpos (printf)
        charindex2 = 1;
        while (params[i+charindex2] == ' ' && i+charindex2 < strlen(params)){
          charindex2++;
        }
        //deadpos (printf)
        charindex3 = 0;
        
        while (params[i+charindex2+charindex3] != ',' && i+charindex2+charindex3 < strlen(params)){
          charindex3++;
        }
        
        while (c < charindex3) {
            value[c] = params[i+charindex2+c];
            c++;
        }
        value[charindex3] = '\0';
        //deadpos (printf)
        
        /*
        memcpy(value,&line[i+charindex2],strlen(line)-(i+charindex2+charindex3));
        value[strlen(line)-(i+charindex2+charindex3)] = '\0';
        */
        
        params[i-charindex] = '\0';
        //char newparams[strlen(params)];
        unsigned int iicount = 0;
        while (!(iicount == i-charindex)){
          iicount = i-charindex;
        }
        unsigned int iisbg = 0;
        while (!(iisbg == 1)){
          iisbg = 1;
        }
        iisbg -= 1;
        while (iisbg<iicount){ //i think this is fixed now???
          //printf("\n\nis this safe? iisbg:%d%c\n\n",iisbg,params[iisbg]);
          newparams[iisbg] = params[iisbg];
          iisbg += 1;
        }
        newparams[iisbg] = '\0';
        //printf("\nii: %d%s\n",iisbg,newparams);
        //note: deadpos (printf) now safe!!! yaya!!!
        for (unsigned int ii = 0; ii < strlen(value); ii++){
          newvalue[ii] = value[ii];
        }
        newvalue[strlen(value)] = '\0';
        //deadpos (printf)
        //v
      }
      //deadpos (printf)
    }
    //semi-deadpos (printf)
    if (type == 0){ //type 0 is parameter, 1 is value
      printf("\n\n%s",newparams);
      returnkey = params;
      return returnkey;
    } else {
      printf("\n\n%s",newvalue);
      returnkey = value;
      return returnkey;
    }
    return 0;
}