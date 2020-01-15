import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtLocation 5.6
import QtPositioning 5.6


ApplicationWindow {
    id: window
    width: 512
    height: 512
    visible: true
    menuBar: MenuBar {
        id: menu
        Menu {
            title: "Fichier"
            MenuItem {
                text: "Importer"
                onTriggered: fileDialogImport.visible = true
            }
            MenuItem {
                text: "Exporter"
                onTriggered: {
                    fileDialogExport.visible = true
                }
            }
            MenuSeparator { }
            MenuItem {
                text: "Quitter"
                onTriggered: Qt.quit()
            }
        }
    }

    property var listHexagones: []
    property var listAntennes: []

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(47.746, 7.3384) // Mulhouse
        zoomLevel: 14
        gesture.enabled: true

    }

    FileDialog {
        id: fileDialogImport
        title: "Veuillez choisir un fichier"
        folder: shortcuts.home
        nameFilters: "*.json"
        onAccepted: {
            middleware.readAntennesFromFile(fileDialogImport.fileUrl);
        }
        onRejected: {
            console.log("Canceled")
        }
    }


    FileDialog {
        id: fileDialogExport
        title: "Veuillez choisir un fichier"
        folder: shortcuts.home
        selectExisting: false
        nameFilters: "*.json"
        onAccepted: {
            for(var i =0; i < listAntennes.length; i++){
                middleware.constructListAntennes(listAntennes[i].puissance,
                                                 listAntennes[i].frequence,
                                                 listAntennes[i].coordinate.latitude,
                                                 listAntennes[i].coordinate.longitude,
                                                 listAntennes[i].couleur,
                                                 listAntennes[i].nom);
            }
            middleware.saveAntennesToFile(fileDialogExport.fileUrl)
        }
        onRejected: {
            console.log("Canceled")
        }

    }

    function addHexagone(latitude, longitude, r, g, b, centreLong, centreLat){

        var component = Qt.createComponent("qrc:///hexagone.qml");
        var polygon = component.createObject(window);
        var centreCoordinate = QtPositioning.coordinate(centreLat, centreLong);

        for(var i=0; i < latitude.length; i++){
            var coordinate = QtPositioning.coordinate(latitude[i], longitude[i]);
            polygon.addCoordinate(coordinate);
            polygon.color =  "#" + r + g+ b;
            polygon.coordinate = centreCoordinate;
            listHexagones.push(polygon);
            console.log("color" + polygon.color)
        }
        map.addMapItem(polygon);
    }

    function addAntenne(){
        var latitude = middleware.listLatitude;
        var longitude = middleware.listLongitude;
        var puissance = middleware.listPuissance;
        var frequence = middleware.listFrequence;
        var color = middleware.listColor;

        for (var i = 0; i < latitude.length; i++){
            var coordinate = QtPositioning.coordinate(latitude[i], longitude[i]);
            var component = Qt.createComponent("qrc:///antenne.qml");
            var antenne = component.createObject(window);
            antenne.coordinate = coordinate;
            antenne.puissance = puissance[i];
            antenne.couleur = color[i];
            antenne.frequence = frequence[i];
            listAntennes.push(antenne);
            map.addMapItem(antenne);
        }
        assignAntenneToHexagone();
    }

    function assignAntenneToHexagone(){
        var puissanceRecueMax;
        var positionAntenne = 0;
        for(var i = 0; i < listHexagones.length; i++){
            if(listAntennes.length == 0){
                listHexagones[i].antenne = undefined
                listHexagones[i].color = "#586036"
                listHexagones[i].opacity = 0.75
                listHexagones[i].puissanceRecue = 0

            } else {
                var puissanceRecueAncienne = 0;
                for(var j=0; j < listAntennes.length; j++){
                    var puissanceRecue = listAntennes[j].puissance / (4 * Math.PI * (listHexagones[i].coordinate.distanceTo(listAntennes[j].coordinate))+0.0005)*1000;
                    if(puissanceRecue > puissanceRecueAncienne){
                        puissanceRecueAncienne = puissanceRecue;
                        positionAntenne = j;

                    }
                }
                listHexagones[i].antenne = listAntennes[positionAntenne];
                listHexagones[i].color = listAntennes[positionAntenne].couleur;
                listHexagones[i].opacity = 0.75 * puissanceRecueAncienne / listAntennes[positionAntenne].puissance * 10;
                listHexagones[i].puissanceRecue = puissanceRecueAncienne
            }

        }
    }
}
