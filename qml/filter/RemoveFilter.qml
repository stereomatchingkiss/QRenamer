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
        ListElement { help:"<em>Step 1</em> : Select the <font color=\"red\">Remove filter</font> icons";
            img: "../pics/filter/removeFitler00.png"
            img_details: "<ul style=\"list-style-type:disc\">
  <li>The filter you apply before will be removed</li>
  <li>You cannot press on this icon if you have not apply any filter</li>
  <li>You can press the short cut <font color=\"red\">\"F6\"</font> to remove the filter too</li>
</ul>"}
    }
}

