import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import QtQuick.Window 2.0
import QtPositioning 5.6

Window {
    id: addWindow
    width: 512
    height: 512
    property var antennePos
    property var couleur
    property var puissance
    property var frequence
    property var nom
    property var coordinate
    property var label

    Rectangle {
        id: rectangle
        x: 169
        y: 93
        width: 201
        height: 326
        color: "#ffffff"

        Column {
            id: column
            x: 169
            y: 93
            anchors.rightMargin: 32
            anchors.fill: parent

            Label {
                id: labelShow
                text: label
            }

            Label {
                id: positionAntenne
                text: antennePos

            }

            TextField {
                id: txtNom
                text: nom
                placeholderText: "Nom de l'antenne"
            }

            TextField {
                id: txtPuissance
                text: puissance
                placeholderText: "Puissance de l'antenne"
            }

            TextField {
                id: txtFrequence
                text: frequence
                placeholderText: "Fréquence de l'antenne"
            }

            Button {
                id: showColorPicker
                text: qsTr("Choisir une couleur")
                onClicked: {
                    colorDialog.visible = true
                }
            }

            Button {
                id: addBtn
                text: qsTr("Confirmer")
                onClicked: {
                    if(label == "Ajouter une antenne"){
                        nom = txtNom.text
                        puissance = Number(txtPuissance.text)
                        frequence = Number(txtFrequence.text)
                        addAntenneDialog()
                        assignAntenneToHexagone();
                        addWindow.close()
                    } else if(label == "Modifier une antenne"){
                        console.log(antennePos)
                        var antenne = listAntennes[antennePos];
                        antenne.nom = txtNom.text
                        antenne.puissance = Number(txtPuissance.text)
                        antenne.frequence = Number(txtFrequence.text)
                        antenne.couleur = couleur
                        antenne.coordinate = coordinate;
                        console.log(couleur)
                        listAntennes[antennePos] = antenne

                        assignAntenneToHexagone();
                        addWindow.close()
                    }

                }
            }

            ColorDialog {
                id: colorDialog
                title: "Choissiez une couleur"
                onAccepted: {
                    couleur = colorDialog.color
                }
                onRejected: {
                    console.log("Canceled")
                }
            }

        }


    }

    function addAntenneDialog(){
        var component = Qt.createComponent("qrc:///antenne.qml");
        var antenne = component.createObject(window);

        antenne.coordinate = coordinate;
        antenne.couleur = couleur;
        antenne.puissance = puissance;
        antenne.nom = nom;
        antenne.frequence = frequence;
        listAntennes.push(antenne);
        map.addMapItem(antenne);
    }

    function getCoordinate(centerLatitude, centerLongitude) {
        var coordinateS = QtPositioning.coordinate(centerLatitude, centerLongitude);
        coordinate = coordinateS;
    }

    function setPos(pos){

        this.antennePos = pos
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2;anchors_height:400;anchors_width:200;anchors_x:169;anchors_y:88}
}
##^##*/
