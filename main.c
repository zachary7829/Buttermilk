//Zachary Keffaber / zachary7829, 2021/09/20, Buttermilk

#include <stdio.h>
#include <string.h>
#include "lib/seajson.h"

int main() {
 int size = 0;
 int charindex = 0;
 int charindex2 = 0;
 int tempint = 0;
 FILE *fp;

 //fp=fopen("testwrite.txt", "w");
 //fprintf(fp, "aba");
 //fclose(fp);

 fp = fopen("language/actionnamesrev.json", "r");
 fseek(fp, 0, SEEK_END); // seek to end of file
 size = ftell(fp); // get current file pointer
 fseek(fp, 0, SEEK_SET); // seek back to beginning of file
 char butternames[size];
 fscanf(fp, "%s", butternames);
 fclose(fp);

 fp = fopen("language/actioncontentrev.json", "r");
 fseek(fp, 0, SEEK_END); // seek to end of file
 size = ftell(fp); // get current file pointer
 fseek(fp, 0, SEEK_SET); // seek back to beginning of file
 char buttercontent[size];
 fscanf(fp, "%s", buttercontent);
 fclose(fp);

 fp = fopen("put/TestButter.butter", "r");
 fseek(fp, 0, SEEK_END); // seek to end of file
 size = ftell(fp); // get current file pointer
 fseek(fp, 0, SEEK_SET); // seek back to beginning of file
 char butter[size];
 fscanf(fp, "%s", butter);
 fclose(fp);

 while (tempint == 0){
    if (butter[charindex] == '('){
      tempint++;
    } else {
      charindex++;
    }
 }
 char actionname[charindex];
 tempint = 0;
 while (charindex2 < charindex) {
   actionname[charindex2] = ("%c",butter[charindex2]);
   charindex2++;
 }
 actionname[sizeof actionname] = '\0';
 charindex = 0;
 charindex2 = 0;

 // printf("Read Buffer: %s\n", buffer);
 char * actionid = getstring(actionname,butternames);
 char * actioncontent = getstring(actionname,buttercontent);
 printf("\n\n");
 printf("{\"WFWorkflowActions\":[{WFWorkflowActionIdentifier\":\"%s\",\"WFWorkflowActionParameters\":{},}]",actionid);
 return 0;
}