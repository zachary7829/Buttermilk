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

char *buttermilk(int mode, char *text) {
  char *returnkey;

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
  char tmpstring2;
  char nocommentline[100];
  int buttermilklinecount = 1;
  signed int textpos = -1;
  int textpossave = 0;
  char wfactions[10000] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n<plist version=\"1.0\">\n<dict>\n  <key>WFWorkflowActions</key>\n  <array>\n";

char butternames[2369] = "{\"OpenApp\":\"is.workflow.actions.openapp\",\"GetURL\":\"is.workflow.actions.downloadurl\",\"Alert\":\"is.workflow.actions.alert\",\"Ask\":\"is.workflow.actions.ask\",\"CreateFolder\":\"is.workflow.actions.file.createfolder\",\"FilterPhotos\":\"is.workflow.actions.filter.photos\",\"Count\":\"is.workflow.actions.count\",\"Print\":\"is.workflow.actions.print\",\"GetItemFromList\":\"is.workflow.actions.getitemfromlist\",\"Comment\":\"is.workflow.actions.comment\",\"Number\":\"is.workflow.actions.number\",\"SaveFile\":\"is.workflow.actions.documentpicker.save\",\"SetVol\":\"is.workflow.actions.setvolume\",\"Date\":\"is.workflow.actions.date\",\"Flashlight\":\"is.workflow.actions.flashlight\",\"List\":\"is.workflow.actions.list\",\"RunSSH\":\"is.workflow.actions.runsshscript\",\"OpenURL\":\"is.workflow.actions.openurl\",\"GetBattery\":\"is.workflow.actions.getbatterylevel\",\"Nothing\":\"is.workflow.actions.nothing\",\"Text\":\"is.workflow.actions.gettext\",\"MakeGIF\":\"is.workflow.actions.makegif\",\"GetVar\":\"is.workflow.actions.getvariable\",\"OpenIn\":\"is.workflow.actions.openin\",\"SetVar\":\"is.workflow.actions.setvariable\",\"SetAppearance\":\"is.workflow.actions.appearance\",\"ChooseList\":\"is.workflow.actions.choosefromlist\",\"ChooseMenu\":\"is.workflow.actions.choosefrommenu\",\"Base64\":\"is.workflow.actions.base64encode\",\"AppendVar\":\"is.workflow.actions.appendvariable\",\"Hash\":\"is.workflow.actions.hash\",\"HideApp\":\"is.workflow.actions.hide.app\",\"GetShortcuts\":\"is.workflow.actions.getmyworkflows\",\"RunShortcuts\":\"is.workflow.actions.runworkflow\",\"Round\":\"is.workflow.actions.round\",\"Replace\":\"is.workflow.actions.text.replace\",\"Split\":\"is.workflow.actions.text.split\",\"Match\":\"is.workflow.actions.text.match\",\"Combine\":\"is.workflow.actions.text.combine\",\"ChangeCase\":\"is.workflow.actions.text.changecase\",\"SetBrightness\":\"is.workflow.actions.setbrightness\",\"SetClipboard\":\"is.workflow.actions.setclipboard\",\"EjectDisk\":\"is.workflow.actions.ejectdisk\",\"MakeHTMLFromRTF\":\"is.workflow.actions.gethtmlfromrichtext\",\"Homescreen\":\"is.workflow.actions.returntohomescreen\",\"SpeakText\":\"is.workflow.actions.speaktext\",\"SplitScreen\":\"is.workflow.actions.splitscreen\"}";

    char butteractions[158] = "{\"SaveFile\":{\"AskWhereToSave\":\"WFAskWhereToSave\",\"Directory\":\"WFFileDestinationPath\",\"Overwrite\":\"WFSaveFileOverwrite\"},\"SetVar\":{\"VarName\":\"WFVariableName\"}}";

    char ParameterTypes[54] = "{\"WFFileDestinationPath\":\"string\",\"WriteOn\":\"integer\"}";
 
  char line[strlen(text)];
    for (unsigned int i = 0; i < strlen(text); i++) {
      // Access each char in the string
      if (text[i] == '\n'){
        buttermilklinecount++;
      }
    }
      printf("\nButtermilk Line Count: %d\n",buttermilklinecount);
    for (unsigned int i = 0; i < buttermilklinecount; i++) {
      textpos++;
      while (text[textpos] != '\n' && text[textpos] != '\0'){
        textpos++;
      }
      for (unsigned int i = 0; i < textpos; i++) {
        line[i] = text[i+textpossave];
      }
      line[textpos] = '\0';
      textpossave = textpos + 1;
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
        strncat(butternames,",\"",2);
        strncat(butternames,newKey,strlen(newKey));
        strncat(butternames,"\":\"",3);
        strncat(butternames,newValue,strlen(newValue));
        strncat(butternames,"\"}",2);
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
        strncat(butteractions,",\"",2);
        strncat(butteractions,newKey,strlen(newKey));
        strncat(butteractions,"\":\"",3);
        strncat(butteractions,newValue,strlen(newValue));
        strncat(butteractions,"\"}",2);
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
        strncat(ParameterTypes,",\"",2);
        strncat(ParameterTypes,newKey,strlen(newKey));
        strncat(ParameterTypes,"\":\"",3);
        strncat(ParameterTypes,newValue,strlen(newValue));
        strncat(ParameterTypes,"\"}",2);
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
      //#define ParameterType = "{}"
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
      char newType[charindex]; //in new ParameterType "WFFileDestinationPath" = "string" this would be WFFileDestinationPath
      c = 0;
      while (c < charindex) {
        newType[c] = nocommentline[charindex3+c];
        c++;
      }
      newType[c] = '\0';
      charindex3 += charindex + 1;
      charindex = 0;
      while(1){
        if ((nocommentline[charindex+charindex3] == ' ' || nocommentline[charindex+charindex3] == '\n') && charindex > 0){
          break;
        } else {
          if (nocommentline[charindex+charindex3] == ' ' || nocommentline[charindex+charindex3] == '='){
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
      //ported from new
      ret = strncmp(newType, "ActionNamesRev", strlen(newType));
      if (strlen(newType) == 0){
        ret = 1;
      }
      if (ret == 0){
        strncpy(butternames, newValue, strlen(newValue));
      }
      ret = strncmp(newType, "ActionContentRev", strlen(newType));
      if (strlen(newType) == 0){
        ret = 1;
      }
      if (ret == 0){
        strncpy(butteractions, newValue, strlen(newValue));
      }
      ret = strncmp(newType, "ParameterTypes", strlen(newType));
      if (strlen(newType) == 0){
        ret = 1;
      }
      if (ret == 0){
        strncpy(ParameterTypes, newValue, strlen(newValue));
      }
      //#define ParameterTypes = "{"WFFileDestinationPath":"string"}"
    }
    ret = strncmp(params, "#blink", strlen(params));
    if (strlen(params) == 0){
      ret = 1;
    }
    if (ret == 0){
      //#blink "put/extbutter.butter"
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
      strncat(wfactions,"    <dict>\n      <key>WFWorkflowActionIdentifier</key>\n      <string>",69);
      strncat(wfactions,actionid,strlen(actionid));
      strncat(wfactions,"</string>\n      <key>WFWorkflowActionParameters</key>\n      <dict>\n        <key>GroupingIdentifier</key>\n        <string>Buttermilk",131);
      char tmpstring3[sizeof(charindex2)*3+2] = "NULL";
      snprintf(tmpstring3, sizeof tmpstring3, "%d", charindex2);
      //sprintf(tmpstring, "%d", charindex2); (The number actfer Buttermilk in GroupingIdentifier)
      strncat(wfactions,tmpstring3,strlen(tmpstring3));
      strncat(wfactions,"</string>\n",10);
      if(!(strlen(butterparam(nocommentline, 0, 1))<1)){
        countbutterparam = 1;
        while (strlen(butterparams) != 0){
          countbutterparam++;
          butterparams = butterparam(nocommentline, 0, countbutterparam);
        }
        countbutterparam -= 1;
        butterparamindex = 1;
        while (butterparamindex < countbutterparam+1){
        strncat(wfactions,"        <key>",13);
        printf("\nStartLoop\nButterParamIndex: %d\nNoCommentLine: %s\n",butterparamindex,nocommentline);
        butterparams = butterparam(nocommentline, 0, butterparamindex);
        butterparams = nonotgetstring(butterparams,butteractions);
        printf("\na%s\n",butterparams);
        printf("\na%s\n",nonotgetstring(butterparams,butteractions));
        strncat(wfactions,butterparams,strlen(butterparams));
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
          strncat(wfactions,"</key>\n        <string>",23);
        }
        isnotint = strncmp(nonotgetstring(butterparams,ParameterTypes),"integer",strlen(nonotgetstring(butterparams,ParameterTypes)));
        if (isnotint == 0){
          strncat(wfactions,"</key>\n        <integer>",24);
        }
        strncat(wfactions,butterparam(nocommentline, 1, butterparamindex),strlen(butterparam(nocommentline, 1, butterparamindex)));
        printf("\n\nCountButterParam: %d\nButterParamIndex: %d\n",countbutterparam,butterparamindex);
        //deadpos
        if (isnotint == 0){
          strncat(wfactions,"</integer>\n",11);
        } else {
          strncat(wfactions,"</string>\n",10);
        }
        butterparamindex++;
        }
      }
      strncat(wfactions,"      </dict>\n    </dict>\n",26);
    }
  }
  strncat(wfactions,"  </array>\n</dict>\n</plist>",28);
  //fclose(fp);
  //system("clear");
    printf("%s",wfactions); // the bug has been better fixed and it's location to be determined to be sprintf (now snprintf). however it still appears to append @ to the beginning...
    returnkey = wfactions;
  printf("%sIwouldliketoremovethisbutIcant",returnkey);
  return returnkey;
  } else {
    int actionindex = 1;
    int actionparametercount = 1;
    int actionparamindex = 1;
    char *currentactionparam = "Value";
    char *actionparam;
    char butter[10000] = "//Buttermilk\n";
    int actionlist = countvalue("WFWorkflowActionIdentifier", text);
    char * butteraction;
    char butternames[2080] = "{\"is.workflow.actions.hide.app\":\"HideApp\",\"is.workflow.actions.appendvariable\":\"AppendVar\",\"is.workflow.actions.alert\":\"Alert\",\"is.workflow.actions.openin\":\"OpenIn\",\"is.workflow.actions.filter.photos\":\"FilterPhotos\",\"is.workflow.actions.date\":\"Date\",\"is.workflow.actions.setvariable\":\"SetVar\",\"is.workflow.actions.text.changecase\":\"ChangeCase\",\"is.workflow.actions.openurl\":\"OpenURL\",\"is.workflow.actions.runsshscript\":\"RunSSH\",\"is.workflow.actions.openapp\":\"OpenApp\",\"is.workflow.actions.setbrightness\":\"SetBrightness\",\"is.workflow.actions.nothing\":\"Nothing\",\"is.workflow.actions.getvariable\":\"GetVar\",\"is.workflow.actions.text.replace\":\"Replace\",\"is.workflow.actions.makegif\":\"MakeGIF\",\"is.workflow.actions.documentpicker.save\":\"SaveFile\",\"is.workflow.actions.print\":\"Print\",\"is.workflow.actions.flashlight\":\"Flashlight\",\"is.workflow.actions.getmyworkflows\":\"GetShortcuts\",\"is.workflow.actions.downloadurl\":\"GetURL\",\"is.workflow.actions.setclipboard\":\"SetClipboard\",\"is.workflow.actions.getbatterylevel\":\"GetBattery\",\"is.workflow.actions.round\":\"Round\",\"is.workflow.actions.appearance\":\"SetAppearance\",\"is.workflow.actions.count\":\"Count\",\"is.workflow.actions.text.match\":\"Match\",\"is.workflow.actions.runworkflow\":\"RunShortcuts\",\"is.workflow.actions.base64encode\":\"Base64\",\"is.workflow.actions.file.createfolder\":\"CreateFolder\",\"is.workflow.actions.choosefromlist\":\"ChooseList\",\"is.workflow.actions.ask\":\"Ask\",\"is.workflow.actions.getitemfromlist\":\"GetItemFromList\",\"is.workflow.actions.choosefrommenu\":\"ChooseMenu\",\"is.workflow.actions.text.split\":\"Split\",\"is.workflow.actions.hash\":\"Hash\",\"is.workflow.actions.comment\":\"Comment\",\"is.workflow.actions.text.combine\":\"Combine\",\"is.workflow.actions.gettext\":\"Text\",\"is.workflow.actions.list\":\"List\",\"is.workflow.actions.setvolume\":\"SetVol\",\"is.workflow.actions.number\":\"Number\",\"is.workflow.actions.ejectdisk\":\"EjectDisk\",\"is.workflow.actions.gethtmlfromrichtext\":\"MakeHTMLFromRTF\",\"is.workflow.actions.returntohomescreen\":\"Homescreen\",\"is.workflow.actions.speaktext\":\"SpeakText\",\"is.workflow.actions.splitscreen\":\"SplitScreen\"}}";

    while(actionindex < actionlist+1) {
    butteraction = nonotgetstring((getvalue("WFWorkflowActionIdentifier",actionindex, text)),butternames);
    if (!(butteraction)){
      butteraction = getvalue("WFWorkflowActionIdentifier",actionindex, text);
    }
    strncat(butteraction,"(",1);
    actionparametercount = 1;
    currentactionparam = "Value";
    while (currentactionparam != NULL){
      currentactionparam = getdict("WFWorkflowActionParameters", actionindex, text, actionparametercount);
      actionparametercount++;
    }
    actionparametercount -= 2;
    actionparamindex = 1;
    while(actionparamindex < actionparametercount+1)
    {
    actionparam = getdict("WFWorkflowActionParameters", actionindex, text, actionparamindex);
    strncat(butteraction,actionparam,strlen(actionparam));
    strncat(butteraction," = ",3);
    char tmpactionparam[strlen(actionparam)];
    for (unsigned int i = 0; i < strlen(actionparam); i++){
      tmpactionparam[i] = actionparam[i];
    }
    tmpactionparam[strlen(actionparam)] = '\0';
    strcat(butteraction,getdictkeyvalue("WFWorkflowActionParameters", actionindex, text, actionparamindex, tmpactionparam)); //error with this one
    actionparamindex++;
    if (actionparamindex < actionparametercount+1){
      strncat(butteraction,", ",2);
    }
    }
    strncat(butteraction,")\n",2);
    strncat(butter,butteraction,strlen(butteraction));
    printf("\n\n%s",butteraction);
    actionindex++;
    }
    //fclose(fp);
    //system("clear");
    printf("%s",butter);
    returnkey = butter;
    return returnkey;
  }
  return 0;
}
