import QtQuick 2.0

import ".."

Rectangle {
    width: parent.width
    height: parent.height

    TutorialSteps{
        anchors.fill: parent
        stack_view: miscellaneous_stack_view
        model: tutorial
    }

    ListModel {
        id: tutorial
        ListElement { help:"Adding a lot of folders";
            img: "../pics/miscellaneous/addRecursiveFolder00.png"
            img_details: "Say you have a lot of folders want to add, it will be tedious
if you have to add them one by one.<br>
If the folders have subfolders, things could go from bad to worse"}

        ListElement { help:"<em>Step 1</em> : Press the add recursive folder icon";
            img: "../pics/miscellaneous/addRecursiveFolder01.png"
            img_details: "You can add the folder recursive by clicking on the recursive icons<br>
or press the shortcut \"F3\""}

        ListElement { help:"<em>Step 2</em> : Add the folders recursive";
            img: "../pics/miscellaneous/addRecursiveFolder02.png"
            img_details: "Go into the folder you want to add recursively,<br>
then press the button <font color=\"blue\">Select Folder</font>"}

        ListElement { help:"<em>Step 3</em> : The results";
            img: "../pics/miscellaneous/addRecursiveFolder03.png"
            img_details: "All of the files under the folder will be added"}
    }
}

