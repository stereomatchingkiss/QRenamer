import QtQuick 2.0

import ".."

Rectangle {
    width: parent.width
    height: parent.height

    TutorialSteps{
        anchors.fill: parent
        stack_view: filter_stack_view
        model: tutorial
    }

    ListModel {
        id: tutorial
        ListElement { help:"Filter files";
            img: "../pics/filter/filterSample.png"
            img_details: "Say you want to rename part of the files in the folder"}

        ListElement { help:"<em>Step 1</em> : Select the folder";
            img: "../pics/methods/selectFolder.png"
            img_details: "This step will load the files in the folder"}

        ListElement { help:"<em>Step 2</em> : Open filter";
            img: "../pics/filter/filterSelect.png"
            img_details: "Open the filter dialog"}

        ListElement { help:"<em>Step 3</em> : Exclude files";
            img: "../pics/filter/filterExclude00.png"
            img_details: "Enter the key words you want to exclude(support regular expression)\n
and select the Exclude circle"}

        ListElement { help:"<em>Step 4</em> : Click ok";
            img: "../pics/filter/filterExclude01.png"
            img_details: "Click on the ok button to exclude the files,you can\n
press on F6 to remove the filter."}
    }
}

