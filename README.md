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

# Convert output to Shortcut
In Buttermilk's current state, you'll need to take the json it outputs and convert it to plist. Keep in mind this will change evetnually. I recommend this website https://wtools.io/convert-json-to-plist. Rename this plist to .shortcut, sign the file, import it and BOOM! You just made a shortcut with Buttermilk!

# What about an app?
Buttermilk is currently a CLI tool. While I was planning an iOS app as well, I don't know if I really have enough time anymore to make one. If I do eventually free up my schedule for an extended period of time, then you can expect a Buttermilk app. Don't count on it however.

# Open Source:
This project is open source under the GPLv3 license. It also uses a modified version of my SeaJson library, which is open source under the MIT license at https://github.com/zachary7829/SeaJson.