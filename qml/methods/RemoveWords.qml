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
                      Remove words</font>";
            img: "../pics/methods/removeWords00.png"
            img_details: "This tag allow users to remove words."}
        ListElement { help:"<em>Step 2</em> : Select the folder";
            img: "../pics/methods/selectFolder.png"
            img_details: "This step will load the files in the folder."}
        ListElement { help:"<em>Step 3</em> : Select the position and range";
            img: "../pics/methods/removeWords01.png"
            img_details: "Enter the position you want to start to remove the words,<br>
then select the range(how many characters you want to remove).<br>
Example : if the RemoveAt is 0, range is 5, then the file [shirobako_001] will become [bako_001].<br>
If the RemoveAt is 1, range is 3, then the file [shirobako_001] will become [sobako_001]"}
        ListElement { help:"<em>Step 4</em> : Rename the Files";
            img: "../pics/methods/renameFiles.png"
            img_details: "Click on the ok button to rename the files, if anything wrong,<br>
you can always revert the change with the revert button"}
    }
}
