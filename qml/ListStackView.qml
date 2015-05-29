import QtQuick 2.0
import QtQuick.Controls 1.3

FocusScope{
    width: parent.width
    height: parent.height

    property alias list_view_model: list_view.model
    property variant parent_stack_view

    property bool should_disable_raining_particle: true

    function pop(){
        stack_view.pop()
    }

    Item{
        width: parent.width
        height: parent.height

        StackView {
            id: stack_view
            anchors.fill: parent
            focus: true

            Keys.onReleased: if ((event.key === Qt.Key_Backspace)
                                     && stack_view.depth > 1) {
                                 stack_view.pop();
                                 raining_particle.emit_enabled = true
                                 event.accepted = true;
                             }

            initialItem: Item {
                width: parent.width
                height: parent.height
                ListView {
                    id: list_view
                    anchors.fill: parent
                    delegate: ButtonDelegate {
                        text: title

                        //onClicked: stack_view.push(Qt.resolvedUrl(page))
                        onClicked: {
                            if(title != "Back"){
                                if(should_disable_raining_particle){
                                    raining_particle.emit_enabled = false;
                                }
                                stack_view.push(Qt.resolvedUrl(page));
                            }else if(parent_stack_view){
                                parent_stack_view.pop();
                            }
                        }
                    }
                }
            }
        }
    }
}
