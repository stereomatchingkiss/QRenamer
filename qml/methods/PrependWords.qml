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
        ListElement { help:"<em>Step 1</em> : Select the tag--<font color=\"red\">
                      Prepend words</font>";
            img: "../pics/methods/prependWords00.png"
            img_details: "This tag allow users to prepend words."}
        ListElement { help:"<em>Step 2</em> : Select the folder";
            img: "../pics/methods/selectFolder.png"
            img_details: "This step will load the files in the folder."}
        ListElement { help:"<em>Step 3</em> : prepend the words";
            img: "../pics/methods/prependWords01.png"
            img_details: "Enter the words you want to prepend"}
        ListElement { help:"<em>Step 4</em> : Rename the Files";
            img: "../pics/methods/renameFiles.png"
            img_details: "Click on the ok button to rename the files, if anything wrong,<br>
you can always revert the change with the revert button"}
    }
}
