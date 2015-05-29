import QtQuick 2.0

import ".."

Rectangle {
    width: parent.width
    height: parent.height

    TutorialSteps{
        anchors.fill: parent
        stack_view: method_stack_view
        model: tutorial
    }

    ListModel {
        id: tutorial
        ListElement { help:"Changing special characters to underscore"
            img: "../pics/methods/regexGlobalModifier00.png"
            img_details: "Lets say your files have some evil spaces(a right royal pain<br>
 in some cases), unwanted characters, and you want to replace them.<br>
In this case, we want to replace each space or # character with an underscore"}

        ListElement { help:"<em>Step 1</em> : Select the tag--<font color=\"red\">
                      Regex</font>"
            img: "../pics/methods/selectRegex.png"
            img_details: "This tag allow users to rename the files with regular expression."}

        ListElement { help:"<em>Step 2</em> : Select the folder"
            img: "../pics/methods/selectFolder.png"
            img_details: "This step will load the files in the folder."}

        ListElement { help:"<em>Step 3</em> : Captured the unwanted characters"
            img: "../pics/methods/regexGlobalModifier01.png"
            img_details: "Type the following regex in the Match field: <font color=\"blue\">[ #]</font>(match either a space or a # character)<br>"}

        ListElement { help:"<em>Step 4</em> : Change the unwanted characters to \"_\""
            img: "../pics/methods/regexGlobalModifier02.png"
            img_details: "Type the following regex in the Replace field: <font color=\"blue\">[ #]</font>
 <ul style=\"list-style-type:disc\">
  <li>The files will be highlighted blue to indicate they match</li>
  <li>The space and # will be removed from the filename in the preview column.</li>
</ul>"}

        ListElement { help:"<em>Step 5</em> : Rename the Files"
            img: "../pics/methods/renameFiles.png"
            img_details: "Click on the ok button to rename the files, if anything wrong,<br>
you can always revert the change with the revert button"}
    }
}
