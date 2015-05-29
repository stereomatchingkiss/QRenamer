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
        ListElement { help:"Renaming photos"
            img: "../pics/methods/regexNumbering00.png"
            img_details: "If you have ever used a digital camera you’ll<br>
 know they aren’t very creative when they name your files.<br>
With Cute Renamer, you can make these more descriptive"}

        ListElement { help:"<em>Step 1</em> : Select the tag--<font color=\"red\">
                      Regex</font>"
            img: "../pics/methods/selectRegex.png"
            img_details: "This tag allow users to rename the files with regular expression."}

        ListElement { help:"<em>Step 2</em> : Select the folder"
            img: "../pics/methods/selectFolder.png"
            img_details: "This step will load the files in the folder."}

        ListElement { help:"<em>Step 3</em> : Captured the number"
            img: "../pics/methods/regexNumbering01.png"
            img_details: "Type the following regex in the Match field: <font color=\"blue\">\d+</font>
 <ul style=\"list-style-type:disc\">
  <li>The files will be highlighted blue to indicate they match</li>
  <li>The numbers will be removed from the filename in the preview column.</li>
</ul>"}

        ListElement { help:"<em>Step 4</em> : Change the number"
            img: "../pics/methods/regexNumbering02.png"
            img_details: "
 <ol>
  <li>Type the following regex in the Replace field: <font color=\"blue\">$#</font></li>
  <li>Click on the Numbering circle</li>
  <li>The new name column will now contain the  new filenames with the<br>
default numbering settings</li>
  <li>Note the order is still the same as the original filenames</li>
</ol> "}

        ListElement { help:"<em>Step 5(option)</em> : Configure the number sequence"
            img: "../pics/methods/regexNumbering03.png"
            img_details: "The defaults are (start at 1, pad to 3 digits,<br>
 increment by 1, don’t ever reset the sequence)"}

        ListElement { help:"<em>Step 6</em> : Rename the Files"
            img: "../pics/methods/renameFiles.png"
            img_details: "Click on the ok button to rename the files, if anything wrong,<br>
you can always revert the change with the revert button"}
    }
}
