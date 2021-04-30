import QtQuick 2.0
import QtQuick.Controls 1.3

Rectangle{
    width: 640
    height: 480

    gradient: Gradient {
        GradientStop { position: 0.0; color: "lightblue" }
        GradientStop { position: 1.0; color: "blue" }
    }

    ListModel {
        id: page_model
        ListElement {
            title: "Methods"
            page: "qrc:/MethodsList.qml"
        }
        ListElement {
            title: "Filter"
            page: "qrc:/FilterList.qml"
        }
        ListElement {
            title: "Miscellaneous"
            page: "qrc:/Miscellaneous.qml"
        }
    }

    ListStackView{
        id: menu_stack_view
        anchors.fill: parent
        list_view_model: page_model
        focus: true
        should_disable_raining_particle: false
    }

    RainingParticle{
        id: raining_particle
        anchors.fill: parent
        particle_source: "../pics/bullet_star.png"
    }
}

