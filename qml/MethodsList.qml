import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import "methods"

Rectangle {
    width: parent.width
    height: parent.height

    gradient: Gradient {
        GradientStop { position: 0.0; color: "darkgreen" }
        GradientStop { position: 0.33; color: "green" }
        GradientStop { position: 1.0; color: "lightgreen" }
    }

    ListModel {
        id: method_page_model
        ListElement {
            title: "Append words"
            page: "qrc:/methods/AppendWords.qml"
        }
        ListElement {
            title: "Insert words"
            page: "qrc:/methods/InsertWords.qml"
        }
        ListElement {
            title: "Prepend words"
            page: "qrc:/methods/PrependWords.qml"
        }
        ListElement {
            title: "Prepend zero on number"
            page: "qrc:/methods/PrependZeroOnNum.qml"
        }
        ListElement {
            title: "Regex--Global modifier"
            page: "qrc:/methods/RegexGlobalModifier.qml"
        }
        ListElement {
            title: "Regex--Numbering files"
            page: "qrc:/methods/RegexNumbering.qml"
        }
        ListElement {
            title: "Regex--Using captures"
            page: "qrc:/methods/RegexUsingCaptures.qml"
        }
        ListElement {
            title: "Remove words"
            page: "qrc:/methods/RemoveWords.qml"
        }
        ListElement {
            title: "Replace suffix"
            page: "qrc:/methods/ReplaceSuffix.qml"
        }
        ListElement {
            title: "Replace words"
            page: "qrc:/methods/ReplaceWords.qml"
        }
        ListElement {
            title: "Back"
            page: "qrc:/BackButton.qml"
        }
    }

    ListStackView{
        id: method_stack_view
        anchors.fill: parent
        list_view_model: method_page_model
        parent_stack_view: menu_stack_view
    }
}

