import QtQuick 2.0

import "../js/globalConstant.js" as Global

Rectangle {
    id : root
    width: parent.width
    height: 90

    property string details
    property string help_str
    property string img_src

    Rectangle {
        id: brief
        width: parent.width * 3 / 4
        height: parent.height

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        color: "#333"
        border.color: Qt.lighter(color, 1.2)
        Text {
            id: help_text

            anchors.fill: parent
            font.pointSize: 12
            color: "white"            
            text: help_str
            textFormat: Text.RichText
        }
    }

    Rectangle{
        id: image

        width: parent.width / 4
        height: parent.height

        anchors.right: brief.right
        anchors.top: parent.top

        color: "black"

        Image {
            anchors.fill: parent

            fillMode: Image.PreserveAspectFit
            source: img_src
            asynchronous: true
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if(parent.state.length == 0){
                parent.state = "expanded"
            }else{
                parent.state = ""
            }
        }
    }

    Item {
        id: detailsView

        anchors.top: image.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        opacity: 0

        Rectangle {
            anchors.fill: parent

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#fcd978" }
                GradientStop { position: 1.0; color: "#fccc4f" }
            }
            border.color: "black"
            border.width: 2

            Text {
                anchors.fill: parent
                anchors.margins: 5

                clip: true
                wrapMode: Text.WordWrap
                color: "black"
                font.pixelSize: 12
                textFormat: Text.RichText

                text: details                
            }
        }
    }

    states: [
        State {
            name: "expanded"

            PropertyChanges { target: root; height: list_view.height}
            PropertyChanges { target: image; width: list_view.width; height: list_view.height * 0.6; anchors.topMargin: 30 }
            PropertyChanges { target: detailsView; opacity: 1 }
            PropertyChanges { target: root.ListView.view; contentY: root.y; interactive: false }
            PropertyChanges { target: image; rotation: 360 }
        }
    ]

    transitions: [
        Transition {
            ParallelAnimation{
                NumberAnimation {
                    duration: 200;
                    properties: "height,width,rotation,anchors.topMargin,opacity,contentY"
                }
            }
        }
    ]
}

