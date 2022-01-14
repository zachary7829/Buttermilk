//Zachary Keffaber / zachary7829, 2021/09/20, Buttermilk

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
    /*
    memcpy(params,&nocommentline[charindex3],charindex);
    params[charindex] = '\0';
    */
    if (!(strchr(nocommentline, '.'))) {
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
        strcat(wfactions,"</key>\n        <string>");
        strcat(wfactions,butterparam(nocommentline, 1, butterparamindex));
        printf("\n\nCountButterParam: %d\nButterParamIndex: %d\n",countbutterparam,butterparamindex);
        strcat(wfactions,"</string>\n");
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