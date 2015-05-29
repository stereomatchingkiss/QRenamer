import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Rectangle {
    width: parent.width
    height: parent.height

    gradient: Gradient {
        GradientStop { position: 0.0; color: "#f5baee" }
        GradientStop { position: 1.0; color: "#db44ca" }
    }

    ListModel {
        id: miscellaneous_page_model
        ListElement {
            title: "Add folder recursive"
            page: "miscellaneous/AddFolderRecursive.qml"
        }
        ListElement {
            title: "Span header"
            page: "miscellaneous/SpanHeader.qml"
        }        
        ListElement {
            title: "Back"
            page: "BackButton.qml"
        }
    }

    ListStackView{
        id: miscellaneous_stack_view
        anchors.fill: parent
        list_view_model: miscellaneous_page_model
        parent_stack_view: menu_stack_view
    }
}

