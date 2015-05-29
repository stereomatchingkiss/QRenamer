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
                      Insert words</font>";
            img: "../pics/methods/insertWords00.png"
            img_details: "This tag allow users to insert words."}
        ListElement { help:"<em>Step 2</em> : Select the folder";
            img: "../pics/methods/selectFolder.png"
            img_details: "This step will load the files in the folder."}
        ListElement { help:"<em>Step 3</em> : Select the position to insert word";
            img: "../pics/methods/insertWords01.png"
            img_details: "Enter the position you want to insert the words"
        }
        ListElement { help:"<em>Step 4</em> : Enter the words want to insert";
            img: "../pics/methods/insertWords02.png"
            img_details: "Enter the words you want to insert.<br>
Example : Remove At is 3, Insert Words is CowBoy, then [shirobako_001] will<br>
become [shiCowBoyrobako_001]"
        }
        ListElement { help:"<em>Step 5</em> : Rename the Files";
            img: "../pics/methods/renameFiles.png"
            img_details: "Click on the ok button to rename the files, if anything wrong,<br>
you can always revert the change with the revert button"}
    }
}
