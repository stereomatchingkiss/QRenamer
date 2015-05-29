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
        ListElement { help:"Converting logfile dates(1)"
            img: "../pics/methods/regexUsingCaptures00.png"
            img_details: "Say you have a bunch of access logs with every day<br>
in the format: accesslog_dd_mm_yyyy.txt"}

        ListElement { help:"Converting logfile dates(2)"
            img: "../pics/methods/regexUsingCaptures01.png"
            img_details: "Using captures we can easily rename these files to a yyyy_mm_dd format"}

        ListElement { help:"<em>Step 1</em> : Select the tag--<font color=\"red\">
                      Regex</font>"
            img: "../pics/methods/selectRegex.png"
            img_details: "This tag allow users to rename the files with regular expression."}

        ListElement { help:"<em>Step 2</em> : Select the folder"
            img: "../pics/methods/selectFolder.png"
            img_details: "This step will load the files in the folder."}

        ListElement { help:"<em>Step 3</em> : Captured the format(dd_mm_yyyy)"
            img: "../pics/methods/regexUsingCaptures02.png"
            img_details: "Type the following regex in the Match field: <font color=\"blue\">(\d+)_(\d+)_(\d+)</font>
 <ul style=\"list-style-type:disc\">
  <li>The files will be highlighted blue to indicate they match</li>
  <li>The numbers will be removed from the filename in the preview column.</li>
</ul>"}

        ListElement { help:"<em>Step 4</em> : Change the format"
            img: "../pics/methods/regexUsingCaptures03.png"
            img_details: "Type the following regex in the Replace field: <font color=\"blue\">\\3_\\2_\\1</font><br>
 You will see the format of date change to yyyy_mm_dd"}

        ListElement { help:"<em>Step 5</em> : Rename the Files"
            img: "../pics/methods/renameFiles.png"
            img_details: "Click on the ok button to rename the files, if anything wrong,<br>
you can always revert the change with the revert button"}
    }
}
