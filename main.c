//Zachary Keffaber / zachary7829, 2021/09/20, Buttermilk

//reminders:
//check for dot notation in filename entered and in #define
//dynamically size wfactions and butter
//in SeaXML make keyindict not always [100]

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/seajson.h"
#include "lib/seaxml.h"
#include "parsebutterparams.h"

int main(void) {
  int mode;
  printf("Press 1 to convert from butter to shortcut, Press 2 to convert from shortcut to butter: ");
  scanf("%d",&mode);
  char filename[100];
  printf("Enter in the file directory+name: "); // put/TestButter.butter
  scanf("%s",filename);
  
  FILE *fp;
  if ((fp = fopen(filename, "r"))){
    fclose(fp); //file exists
  } else {
    printf("\nCannot find file in specified filepath.\n");
    return 0;
  }
  if (mode == 1){
  int isnotint;
  int ret;
  int charindex2 = 0;
  int charindex, charindex3, c;
  int instring = 0;
  int incomment = 0;
  int inmulticomment = 0;
  char * actionid;
  int countbutterparam = 1;
  int butterparamindex = 1;
  char *butterparams = "Value";
  char tmpstring[100];
  char nocommentline[100];
  char wfactions[10000] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n<plist version=\"1.0\">\n<dict>\n  <key>WFWorkflowActions</key>\n  <array>\n";

  fp = fopen("language/actionnamesrev.json", "r");
  fseek(fp, 0, SEEK_END); // seek to end of file
  int size = ftell(fp); // get current file pointer
  fseek(fp, 0, SEEK_SET); // seek back to beginning of file
  char butternames[size];
  fscanf(fp, "%s", butternames);
  fclose(fp);

  fp = fopen("language/actioncontentrev.json", "r");
  fseek(fp, 0, SEEK_END); // seek to end of file
  size = ftell(fp); // get current file pointer
  fseek(fp, 0, SEEK_SET); // seek back to beginning of file
  char butteractions[size];
  fscanf(fp, "%s", butteractions);
  fclose(fp);

  fp = fopen("language/ParameterTypes.json", "r");
  fseek(fp, 0, SEEK_END); // seek to end of file
  size = ftell(fp); // get current file pointer
  fseek(fp, 0, SEEK_SET); // seek back to beginning of file
  char ParameterTypes[size];
  fscanf(fp, "%s", ParameterTypes);
  fclose(fp);
 
  fp = fopen(filename, "r");
  char line[100];
  while (fgets(line, sizeof (line), fp)){
    charindex = 0;
    charindex3 = 0;
    while (charindex < strlen(line)){
      if (line[charindex] == '/' && line[charindex+1] == '/'){
        incomment = 1;
      }
      if (line[charindex] == '/' && line[charindex+1] == '*'){
        inmulticomment = 1;
      }
      if (line[charindex-2] == '*' && line[charindex-1] == '/'){
        inmulticomment = 0;
      }
      if (inmulticomment == 0 && incomment == 0){
        nocommentline[charindex3] = line[charindex];
        charindex3++;
      }
      charindex++;
    }
    incomment = 0;
    nocommentline[charindex3] = '\0';
    charindex = 0;
    charindex3 = 0;
    while (1){
      if (nocommentline[charindex+charindex3] == '(' || (nocommentline[charindex+charindex3] == ' ' && charindex > 0) || (nocommentline[charindex+charindex3] == '/' && nocommentline[charindex+charindex3+1] == '/')){
        break;
      } else {
        if (nocommentline[charindex+charindex3] == ' '){
          charindex3++;
        } else {
          charindex++;
        }
      }
    }
    char params[charindex];
    c = 0;
    while (c < charindex) {
      params[c] = nocommentline[charindex3+c];
      c++;
    }
    params[c] = '\0';
    //reminder to port the down below code to short2butter
    ret = strncmp(params, "new", strlen(params));
    if (strlen(params) == 0){
      ret = 1;
    }
    if (ret == 0){
      charindex3 += charindex + 1;
      charindex = 0;
      while(1){
        if (nocommentline[charindex+charindex3] == ' ' && charindex > 0){
          break;
        } else {
          if (nocommentline[charindex+charindex3] == ' '){
            charindex3++;
          } else {
            charindex++;
          }
        }
      }
      char newType[charindex]; //in new ParameterType "WFFileDestinationPath" = "string" this would be ParameterType
      c = 0;
      while (c < charindex) {
        newType[c] = nocommentline[charindex3+c];
        c++;
      }
      newType[c] = '\0';
      charindex3 += charindex + 1;
      charindex = 0;
      while(1){
        if ((nocommentline[charindex+charindex3] == ' ' || nocommentline[charindex+charindex3] == '\"') && charindex > 0){
          break;
        } else {
          if (nocommentline[charindex+charindex3] == ' ' || nocommentline[charindex+charindex3] == '\"'){
            charindex3++;
          } else {
            charindex++;
          }
        }
      }
      char newKey[charindex]; //in new ParameterType "WFFileDestinationPath" = "string" this would be WFFileDestinationPath
      c = 0;
      while (c < charindex) {
        newKey[c] = nocommentline[charindex3+c];
        c++;
      }
      newKey[c] = '\0';
      charindex3 += charindex + 1;
      charindex = 0;
      while(1){
        if ((nocommentline[charindex+charindex3] == ' ' || nocommentline[charindex+charindex3] == '\"' || nocommentline[charindex+charindex3] == '\n') && charindex > 0){
          break;
        } else {
          if (nocommentline[charindex+charindex3] == ' ' || nocommentline[charindex+charindex3] == '\"' || nocommentline[charindex+charindex3] == '='){
            charindex3++;
          } else {
            charindex++;
          }
        }
      }
      char newValue[charindex]; //in new ParameterType "WFFileDestinationPath" = "string" this would be WFFileDestinationPath
      c = 0;
      while (c < charindex) {
        newValue[c] = nocommentline[charindex3+c];
        c++;
      }
      newValue[c] = '\0';
      ret = strncmp(newType, "ActionNamesRev", strlen(newType));
      if (strlen(newType) == 0){
        ret = 1;
      }
      if (ret == 0){
        charindex = strlen(butternames);
        charindex3 = 0;
        while (butternames[strlen(butternames)-charindex3] != '}'){
          charindex3++;
        }
        butternames[strlen(butternames)-charindex3] = '\0'; //null out }
        strcat(butternames,",\"");
        strcat(butternames,newKey);
        strcat(butternames,"\":\"");
        strcat(butternames,newValue);
        strcat(butternames,"\"}");
        butternames[strlen(butternames)] = '\0';
      }
      ret = strncmp(newType, "ActionContentRev", strlen(newType));
      if (strlen(newType) == 0){
        ret = 1;
      }
      if (ret == 0){
        charindex = strlen(butteractions);
        charindex3 = 0;
        while (butteractions[strlen(butteractions)-charindex3] != '}'){
          charindex3++;
        }
        butteractions[strlen(butteractions)-charindex3] = '\0'; //null out }
        strcat(butteractions,",\"");
        strcat(butteractions,newKey);
        strcat(butteractions,"\":\"");
        strcat(butteractions,newValue);
        strcat(butteractions,"\"}");
        butteractions[strlen(butteractions)] = '\0';
      }
      ret = strncmp(newType, "ParameterTypes", strlen(newType));
      if (strlen(newType) == 0){
        ret = 1;
      }
      if (ret == 0){
        charindex = strlen(ParameterTypes);
        charindex3 = 0;
        while (ParameterTypes[strlen(ParameterTypes)-charindex3] != '}'){
          charindex3++;
        }
        ParameterTypes[strlen(ParameterTypes)-charindex3] = '\0'; //null out }
        strcat(ParameterTypes,",\"");
        strcat(ParameterTypes,newKey);
        strcat(ParameterTypes,"\":\"");
        strcat(ParameterTypes,newValue);
        strcat(ParameterTypes,"\"}");
        ParameterTypes[strlen(ParameterTypes)] = '\0';
      }
      //newValue[c] = '\0';
      //}
      //printf("\n\nnew parsing: %s %s %s %s %lu\n\n",params, newType, newKey, newValue, strlen(params));
      //reminder to change later to instead of getting last character to instead get last }
      //new ParameterType "WFFileDestinationPath" = "string"
      //new actionnamesrev "GetURL" = "is.workflow.actions.downloadurl"
    }
    ret = strncmp(params, "#define", strlen(params));
    if (strlen(params) == 0){
      ret = 1;
    }
    if (ret == 0){
      //#define "language/ParameterTypes.json" = "{"WFFileDestinationPath":"string"}"
    }
    ret = strncmp(params, "if", strlen(params));
    if (strlen(params) == 0){
      ret = 1;
    }
    if (ret == 0){
      //smart ifs
    }
    ret = strncmp(params, "var", strlen(params));
    if (strlen(params) == 0){
      ret = 1;
    }
    if (ret == 0){
      //smart vars
    }
    /*
    memcpy(params,&nocommentline[charindex3],charindex);
    params[charindex] = '\0';
    */
    if (!(strchr(params, '.'))) {
      actionid = nonotgetstring(params,butternames);
    } else {
      actionid = params;
    }
    if (!(actionid == NULL)){
      charindex2++;
      printf("\n\n");
      strcat(wfactions,"    <dict>\n      <key>WFWorkflowActionIdentifier</key>\n      <string>");
      strcat(wfactions,actionid);
      strcat(wfactions,"</string>\n      <key>WFWorkflowActionParameters</key>\n      <dict>\n        <key>GroupingIdentifier</key>\n        <string>Buttermilk");
      sprintf(tmpstring, "%d", charindex2);
      strcat(wfactions,tmpstring);
      strcat(wfactions,"</string>\n");
      if(!(strlen(butterparam(nocommentline, 0, 1))<1)){
        countbutterparam = 1;
        while (strlen(butterparams) != 0){
          countbutterparam++;
          butterparams = butterparam(nocommentline, 0, countbutterparam);
        }
        countbutterparam -= 1;
        butterparamindex = 1;
        while (butterparamindex < countbutterparam+1){
        strcat(wfactions,"        <key>");
        printf("\nStartLoop\nButterParamIndex: %d\nNoCommentLine: %s\n",butterparamindex,nocommentline);
        butterparams = butterparam(nocommentline, 0, butterparamindex);
        butterparams = nonotgetstring(butterparams,butteractions);
        printf("\na%s\n",butterparams);
        printf("\na%s\n",nonotgetstring(butterparams,butteractions));
        strcat(wfactions,butterparams);
        /*
        for(int i = 0;i < (strlen(str) - 1);i++) {
		      if((int)str[i] < 10) {
			      return true;
		      } else {
			      return false;
		      }
	      }
        */
        ret = strncmp(nonotgetstring(butterparams,ParameterTypes),"string",strlen(nonotgetstring(butterparams,ParameterTypes)));
        if (ret == 0){
          strcat(wfactions,"</key>\n        <string>");
        }
        isnotint = strncmp(nonotgetstring(butterparams,ParameterTypes),"integer",strlen(nonotgetstring(butterparams,ParameterTypes)));
        if (isnotint == 0){
          strcat(wfactions,"</key>\n        <integer>");
        }
        strcat(wfactions,butterparam(nocommentline, 1, butterparamindex));
        printf("\n\nCountButterParam: %d\nButterParamIndex: %d\n",countbutterparam,butterparamindex);
        //deadpos
        if (isnotint == 0){
          strcat(wfactions,"</integer>\n");
        } else {
          strcat(wfactions,"</string>\n");
        }
        butterparamindex++;
        }
      }
      strcat(wfactions,"      </dict>\n    </dict>\n");
    }
  }
  strcat(wfactions,"  </array>\n</dict>\n</plist>");
  fclose(fp);
  system("clear");
  printf("\b\b\b\b\b\b\bstupid memory bug\n\n\n%s",wfactions);
  } else {
    int actionindex = 1;
    int actionparametercount = 1;
    int actionparamindex = 1;
    char *currentactionparam = "Value";
    char *actionparam;
    char butter[10000] = "//Buttermilk\n";
    int actionlist = countvalue("WFWorkflowActionIdentifier", filename);
    char * butteraction;
    fp = fopen("language/actionnames.json", "r");
    fseek(fp, 0, SEEK_END); // seek to end of file
    int size = ftell(fp); // get current file pointer
    fseek(fp, 0, SEEK_SET); // seek back to beginning of file
    char butternames[size];
    fscanf(fp, "%s", butternames);
    fclose(fp);

    while(actionindex < actionlist+1) {
    butteraction = nonotgetstring((getvalue("WFWorkflowActionIdentifier",actionindex, filename)),butternames);
    if (!(butteraction)){
      butteraction = getvalue("WFWorkflowActionIdentifier",actionindex, filename);
    }
    strcat(butteraction,"(");
    actionparametercount = 1;
    currentactionparam = "Value";
    while (currentactionparam != NULL){
      currentactionparam = getdict("WFWorkflowActionParameters", actionindex, filename, actionparametercount);
      actionparametercount++;
    }
    actionparametercount -= 2;
    actionparamindex = 1;
    while(actionparamindex < actionparametercount+1)
    {
    actionparam = getdict("WFWorkflowActionParameters", actionindex, filename, actionparamindex);
    strcat(butteraction,actionparam);
    strcat(butteraction," = ");
    char tmpactionparam[strlen(actionparam)];
    for (unsigned int i = 0; i < strlen(actionparam); i++){
      tmpactionparam[i] = actionparam[i];
    }
    tmpactionparam[strlen(actionparam)] = '\0';
    strcat(butteraction,getdictkeyvalue("WFWorkflowActionParameters", actionindex, filename, actionparamindex, tmpactionparam)); //error with this one
    actionparamindex++;
    if (actionparamindex < actionparametercount+1){
      strcat(butteraction,", ");
    }
    }
    strcat(butteraction,")\n");
    strcat(butter,butteraction);
    printf("\n\n%s",butteraction);
    actionindex++;
    }
    fclose(fp);
    system("clear");
    printf("%s",butter);
  }
  return 0;
}