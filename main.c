//Zachary Keffaber / zachary7829, 2021/09/20, Buttermilk

#include <stdio.h>
#include <string.h>
#include "lib/seajson.h"

int main(void) {
  char ch;
  int size = 0;
  int charindex = 0;
  int charindex2 = 0;
  int tempint = 0;
  int instring = 0;
  char tmpstring[100];
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
    charindex2++;
    charindex = 0;
    tempint = 0;
    while (tempint == 0){
      if (line[charindex] == '('){
        tempint++;
      } else {
      }
      charindex++;
    }
    char params[charindex-1];
    memcpy(params,&line[0],charindex-1);
    params[charindex-1] = '\0';
    charindex = 0;
    tempint = 0;
    if (charindex2 > 1){
      strcat(wfactions,",");
    }
    strcat(wfactions,"{\"WFWorkflowActionIdentifier\":\"");
    for(int i = 0; i < sizeof params; ++i) {
      if (line[i] == '.'){
        charindex++;
      }
    }
    if (charindex == 0) {
      actionid = getstring(params,butternames);
    } else {
      actionid = params;
    }
    printf("\n\n");
    strcat(wfactions,actionid);
    strcat(wfactions,"\",\"WFWorkflowActionParameters\":{\"UUID\":\"Buttermilk");
    sprintf(tmpstring, "%d", charindex2);
    strcat(wfactions,tmpstring);
    strcat(wfactions,"\"}}");
  }
  strcat(wfactions,"]}");
  system("clear");
  printf("%s",wfactions);
  fclose(fp);
  return 0;
}