import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Rectangle {
    width: parent.width
    height: parent.height

    gradient: Gradient {
        GradientStop { position: 0.0; color: "tomato" }
        GradientStop { position: 1.0; color: "coral" }
    }

    ListModel {
        id: filter_page_model
        ListElement {
            title: "Exclude"
            page: "filter/Exclude.qml"
        }
        ListElement {
            title: "Include"
            page: "filter/Include.qml"
        }        
        ListElement {
            title: "Remove filter"
            page: "filter/RemoveFilter.qml"
        }
        ListElement {
            title: "Back"
            page: "BackButton.qml"
        }
    }

    ListStackView{
        id: filter_stack_view
        anchors.fill: parent
        list_view_model: filter_page_model
        parent_stack_view: menu_stack_view
    }
}

