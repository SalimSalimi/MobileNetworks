import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick.Controls 2.5

MapQuickItem {
    id: antenne
    anchorPoint.x: icon.width * 0.5
    anchorPoint.y: icon.height * 0.8
    property var puissance
    property var frequence
    property var couleur
    property var nom

    sourceItem: Image {
        id: icon
        source: "marker.png"
        sourceSize.width: 60
        sourceSize.height: 60

    }

    MouseArea {
        id: mouseA
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            antenneMenu.visible = true
        }
    }

    ToolTip {
        id: toolTip
        text: textAntenneToolTip()
        delay: 1000
        visible: mouseA.containsMouse
    }

    function textAntenneToolTip() {
        return "Nom de l'antenne " + this.nom +"\nPuissance de l'antenne:" +this.puissance + "\nFréquence de l'antenne"+this.frequence
    }

    Menu {
        id: antenneMenu
        MenuItem {
            text:"Modifier l'antenne.."
            onTriggered: {
                var dialog = showDialogUpdate();
                dialog.label = "Modifier une antenne"
                dialog.visible = true
            }
        }

        MenuItem {
            text:"Supprimer l'antenne"
            onTriggered: deleteAntenne()
        }
    }

    function showDialogUpdate(){
        var component = Qt.createComponent("qrc:///add_antenne_dialog.qml");
        var dialog = component.createObject(window);
        dialog.label = "Modifier une antenne"
        dialog.
        dialog.getCoordinate(coordinate.latitude, coordinate.longitude);

        return dialog
    }

    function deleteAntenne(){
        var pos = listAntennes.indexOf(this)
        listAntennes.splice(pos,1)
        parent.removeMapItem(this)
        console.log(listAntennes.length + " nombre")
        assignAntenneToHexagone()
    }
}

