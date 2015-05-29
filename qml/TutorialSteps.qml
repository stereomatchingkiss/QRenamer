import QtQuick 2.0

import ".."
import "../js/globalConstant.js" as Global

Item {
    width: parent.width
    height: parent.height

    property variant stack_view
    property alias model: list_view.model

    Rectangle{
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#4a4a4a" }
            GradientStop { position: 1.0; color: "#2b2b2b" }
        }
    }

    ListView {
        id: list_view

        anchors.fill: parent

        delegate: StepLabel{
            help_str: help
            img_src : img
            details : img_details
        }

        //model: tutorial //this model is come from the other methods(ex : AppendWords, PrependWords)
        footer: Rectangle{
            id: foot
            height: Global.global_const.list_view_foot_height()
            width: list_view.width
            color: "silver"

            Text{
                anchors.fill: parent
                text: "Back"
                horizontalAlignment: Text.AlignHCenter
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    parent.state = "press";
                    stack_view.pop();
                }
                onReleased: {
                    raining_particle.emit_enabled = true;
                    parent.state = ""
                }
            }

            states: [
                State {
                    name: "press"

                    PropertyChanges { target: foot; color: "blue"}
                }
            ]

            transitions: [
                Transition {
                    ColorAnimation {
                        to: "blue"
                        duration: 500
                    }
                }
            ]
        }
    }
}

