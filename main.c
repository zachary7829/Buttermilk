//Zachary Keffaber / zachary7829, 2021/09/20, Buttermilk

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/seajson.h"
#include "lib/seaxml.h"

int main(void) {
  int mode;
  printf("Press 1 to convert from butter to shortcut, Press 2 to convert from shortcut to butter: ");
  scanf("%d",&mode);
  
  char ch;
  int size = 0;
  int charindex = 0;
  int charindex2 = 0;
  int charindex3 = 0;
  int tempint = 0;
  int instring = 0;
  int incomment = 0;
  int inmulticomment = 0;
  int charcount = 0;
  char tmpstring[100];
  char nocommentline[100];
  if (mode == 1){
  char wfactions[10000] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n<plist version=\"1.0\">\n<dict>\n  <key>WFWorkflowActions</key>\n  <array>\n";
  char * actionid;
  FILE *fp;

  fp = fopen("language/actionnamesrev.json", "r");
  fseek(fp, 0, SEEK_END); // seek to end of file
  size = ftell(fp); // get current file pointer
  fseek(fp, 0, SEEK_SET); // seek back to beginning of file
  char butternames[size];
  fscanf(fp, "%s", butternames);
  fclose(fp);
 
  //fp=fopen("testwrite.txt", "w");
  //fprintf(fp, "aba");
  //fclose(fp);
 
  char filename[100];
  printf("Enter in the file directory+name: "); // put/TestButter.butter
  scanf("%s",filename);
  fp = fopen(filename, "r");
  char line[100];
  while (fgets(line, sizeof (line), fp)){
    charindex = 0;
    charindex3 = 0;
    tempint = 0;
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
    while (tempint == 0){
      if (nocommentline[charindex+charindex3] == '(' || (nocommentline[charindex+charindex3] == ' ' && charindex > 0) || (nocommentline[charindex+charindex3] == '/' && nocommentline[charindex+charindex3+1] == '/')){
        tempint++;
      } else {
        if (nocommentline[charindex+charindex3] == ' '){
          charindex3++;
        } else {
          charindex++;
        }
      }
    }
    char params[charindex];
    memcpy(params,&nocommentline[charindex3],charindex);
    params[charindex] = '\0';
    charindex = 0;
    tempint = 0;
    for(int i = 0; i < sizeof params; ++i) {
      if (nocommentline[i] == '.'){
        charindex++;
      }
    }
    if (charindex == 0) {
      actionid = getstring(params,butternames);
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
      strcat(wfactions,"</string>\n      </dict>\n    </dict>\n");
    }
  }
  strcat(wfactions,"  </array>\n</dict>\n</plist>");
  system("clear");
  printf("%s",wfactions);
  fclose(fp);
  } else {
    char filename[100];
    printf("Enter in the file directory+name: "); // put/AfterButter.dhortcut
    scanf("%s",filename);
    int actionindex = 1;
    int stringsize = 0;
    int tempint2 = 0;
    char butter[1000] = "//Buttermilk\n";
    int actionlist = countvalue("WFWorkflowActionIdentifier", filename);
    char * actionid;
    char * butteraction;
    FILE *fp;
    fp = fopen("language/actionnames.json", "r");
    fseek(fp, 0, SEEK_END); // seek to end of file
    size = ftell(fp); // get current file pointer
    fseek(fp, 0, SEEK_SET); // seek back to beginning of file
    char butternames[size];
    fscanf(fp, "%s", butternames);
    fclose(fp);

    while(actionindex < actionlist+1) {
    charindex3 = 0;
    tempint = 0;
    actionid = getvalue("WFWorkflowActionIdentifier",actionindex, filename);
    butteraction = nonotgetstring(actionid,butternames);
    if (!(butteraction)){
      butteraction = getvalue("WFWorkflowActionIdentifier",actionindex, filename);
    }
    strcat(butteraction,"()\n");
    //I forgot strcat existed so I wrote the code below. It would probably be better with strcat but fuck it my code isn't going to go to waste for this update
    charindex3 = 0;
    stringsize = strlen(butter);
    while (charindex3 < strlen(butteraction)){
      butter[charindex3+stringsize] = butteraction[charindex3];
      charindex3++;
    }
    butter[charindex3+stringsize] = '\0';
    printf("\n\n%s",butteraction);
    actionindex++;
    }
    fclose(fp);
    system("clear");
    printf("%s",butter);
  }
  return 0;
}