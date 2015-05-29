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
        ListElement { help:"See the full contents of the <font color=\"red\">Original name</font>
 and <font color=\"red\">New Name</font>";
            img: "../pics/miscellaneous/spanHeader00.png"
            img_details: "Say the <font color=\"blue\">Original name</font> and
<font color=\"blue\">New name</font> are too long,<br>
you can not see the whole text, you can use the span function to adjust the space"}

        ListElement { help:"<em>Step 1</em> : Press the <font color=\"red\">Span header</font> icon";
            img: "../pics/miscellaneous/spanHeader01.png"
            img_details: "There are three ways to adjust the space
 <ul style=\"list-style-type:disc\">
  <li>Click on the <font color=\"blue\">Span header</font> icon</li>
  <li>Press the shortcut button \"Ctrl+S\"</li>
  <li>Drag on the header</li>
</ul>"}

        ListElement { help:"<em>Step 2</em> : Result after span";
            img: "../pics/miscellaneous/spanHeader02.png"
            img_details: "You can see the space of the headers are long enough to show the contents"}
    }
}

