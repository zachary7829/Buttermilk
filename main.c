//Zachary Keffaber / zachary7829, 2021/09/20, Buttermilk

#include <stdio.h>
#include <string.h>
#include "lib/seajson.h"

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
  char wfactions[2000] = "{\"WFWorkflowClientVersion\":\"100\",\"WFWorkflowClientRelease\":\"3.0\",\"WFWorkflowMinimumClientVersion\":\"100\",\"WFWorkflowMinimumClientVersionString\":\"100\",\"WFWorkflowImportQuestions\":[],\"WFWorkflowTypes\":[\"NCWidget\",\"WatchKit\"],\"WFWorkflowInputContentItemClasses\":[\"WFAppStoreAppContentItem\",\"WFArticleContentItem\",\"WFContactContentItem\",\"WFDateContentItem\",\"WFEmailAddressContentItem\",\"WFGenericFileContentItem\",\"WFImageContentItem\",\"WFiTunesProductContentItem\",\"WFLocationContentItem\",\"WFDCMapsLinkContentItem\",\"WFAVAssetContentItem\",\"WFPDFContentItem\",\"WFPhoneNumberContentItem\",\"WFRichTextContentItem\",\"WFSafariWebPageContentItem\",\"WFStringContentItem\",\"WFURLContentItem\"],\"WFWorkflowIcon\":{\"WFWorkflowIconStartColor\":431817727,\"WFWorkflowIconGlyphNumber\":61440},\"WFWorkflowActions\":[";
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
 
  fp = fopen("put/TestButter.butter", "r");
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
      //Here is the issue :/
      actionid = getstring(params,butternames);
    } else {
      actionid = params;
    }
    if (!(strlen(params) < 2)){
      charindex2++;
      printf("\n\n");
      if (charindex2 > 1){
        strcat(wfactions,",");
      }
      strcat(wfactions,"{\"WFWorkflowActionIdentifier\":\"");
      strcat(wfactions,actionid);
      strcat(wfactions,"\",\"WFWorkflowActionParameters\":{\"UUID\":\"Buttermilk");
      sprintf(tmpstring, "%d", charindex2);
      strcat(wfactions,tmpstring);
      strcat(wfactions,"\"}}");
    }
  }
  strcat(wfactions,"]}");
  system("clear");
  printf("%s",wfactions);
  fclose(fp);
  } else {
    int stringsize = 0;
    int tempint2 = 0;
    char butter[1000] = "//Buttermilk\n";
    char * actionlist;
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

    fp = fopen("put/TestCut.json", "r");
    fseek(fp, 0, SEEK_END); // seek to end of file
    size = ftell(fp); // get current file pointer
    fseek(fp, 0, SEEK_SET); // seek back to beginning of file
    char testcut[size];
    fscanf(fp, "%s", testcut);
    char * wfactions = getstring("WFWorkflowActions",testcut);
    printf("\n\n%s",wfactions);
    while(tempint2 == 0) {
    wfactions = getstring("WFWorkflowActions",testcut);
    charindex2 += charindex;
    charindex = 0;
    charindex3 = 0;
    tempint = 0; // I am a fucking idiot, I spent an hour wondering why this wouldn't work and then I just realized I just needed tempint = 0 :/
    while (tempint == 0){
      if (wfactions[charindex+charindex2] == ',' && !(wfactions[charindex+charindex2+1] == '\"') && !(charindex2 == charindex2+charindex)){
        tempint++;
      }
      if (charindex+charindex2 == strlen(wfactions)){
        tempint++;
        tempint2++;
      } else {
        charindex++;
      }
    }
    printf("\nCharindex : %d Charindex2 : %d WFActions : %lu\n",charindex,charindex2,strlen(wfactions));
    char action[strlen(wfactions)];
    memcpy(action,&wfactions[charindex2],charindex);
    action[charindex] = '\0';
    action[charindex-1] = '}';
    actionid = (getstring("WFWorkflowActionIdentifier",action));
    butteraction = nonotgetstring(actionid,butternames);
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
    }
    fclose(fp);
    system("clear");
    printf("%s",butter);
  }
  return 0;
}