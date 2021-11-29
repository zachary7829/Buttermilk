# Buttermilk
Cool CLI tool to make shortcuts from Text.

# Compatible with:
Buttermilk is coded in 100% C, meaning you can run it on just about any device that can compile and execute C. Windows/macOS/Linux? Of course. iOS/Android? You'll need a third party app to compile it on-device, but yes. Your toaster? If it can compile/run C, likely yes.

## Actions Implemented:

OpenApp()

GetURL()

Alert()

Ask()

CreateFolder()

FilterPhotos()

Count()

Print()

GetItemFromList()

Comment()

Number()

SaveFile()

SetVol()

Date()

Flashlight()

List()

RunSSH()

OpenURL()

GetBattery()

Nothing()

Text()

MakeGIF()

GetVar()

OpenIn()

SetVar()

SetAppearance()

ChooseList()

ChooseMenu()

Base64()

AppendVar()

Hash()

HideApp()

GetShortcuts()

RunShortcuts()

Round()

Replace()

Split()

Match()

Combine()

ChangeCase()

SetBrightness()

SetClipboard()

EjectDisk()

MakeHTMLFromRTF()

Homescreen()

SpeakText()

SplitScreen()

(You can also use the action ids from WFActions.plist if they aren't in actionnamesrev.json (although I highly don't recommend this), for example is.workflow.actions.downloadurl())

## Smart Comments:

While you can use Comment() in your buttermilk, Buttermilk also has support for smart comments, meaning you can also use //.

## Smart Multi-Line Comments:

With buttermilk, you can use /* to start a multi-line comment, and */ to end it.

## Not yet implemented features:

-Smart Ifs

-Smart Untils

-Magic Variables

-Action Parameters

# Examples:
If you want some examples for Buttermilk, for shortcut to butter conversion use the file located in `put/AfterButter.dhortcut`. For butter to shortcut conversion, use the file located in `put/TestButter.butter`.

# What about an app?
Buttermilk is currently a CLI tool. While I was planning an app as well, I don't know if I really have enough time anymore to make one. If I do eventually free up my schedule for an extended period of time, then you can expect a Buttermilk app, which will be for pretty much every major platform, ex Windows/macOS/Linux/iOS/Android/Web. Don't count on it however.

# Open Source:
This project is open source under the GPLv3 license. It also uses a modified version of my SeaJson library for Shortcut to Buttermilk and Buttermilk to Shortcut conversion, which is open source under the MIT license at https://github.com/zachary7829/SeaJson, as well as my SeaXML library, which is open source under the MIT license at https://github.com/zachary7829/SeaXML.