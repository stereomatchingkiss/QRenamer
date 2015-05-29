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
                      Prepend zero on number</font>";
            img: "../pics/methods/prependZeroOnNum00.png"
            img_details: "This tag allow users to prepend zero on number.<br>
ex : make [rockman_0] to [rockman_00]"}

        ListElement { help:"<em>Step 2</em> : Select the folder";
            img: "../pics/methods/selectFolder.png"
            img_details: "This step will load the files in the folder."}

        ListElement { help:"<em>Step 3a-1</em> : Select how many 0 you want to<br>
 prepend on the last number";
            img: "../pics/methods/prependZeroOnNum01.png"
            img_details: "If you select 2(minimum is 1), [001_0] will become [001_00].<br>
If you select 3, [001_0] will become [001_000]"}

        ListElement { help:"<em>Step 3b-1</em> : Change the box from
<font color=\"red\">last number</font> to <font color=\"red\">custom</font>"
            img: "../pics/methods/prependZeroOnNum02.png"
            img_details: "This option will allow you to prepend 0 on specific number."}

        ListElement { help:"<em>Step 3b-2</em> : Select the number you want to prepend zero"
            img: "../pics/methods/prependZeroOnNum03.png"
            img_details: "If you select Position as 1 on [001_0] and set the
Number length as 4, the number will become [0001_0].<br>
If you select Position as 2 on [001_0] and set the
Number length as 4, the number will become [001_0000].<br>"}

        ListElement { help:"<em>Step 4</em> : Rename the Files";
            img: "../pics/methods/renameFiles.png"
            img_details: "Click on the ok button to rename the files, if anything wrong,<br>
you can always revert the change with the revert button"}
    }
}

