import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.0
import QtQuick.Controls 2.0
import QtLocation 5.6
import QtPositioning 5.6

Window {
    id: window
    width: 512
    height: 512
    visible: true
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
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
            middleware.readAntennesFromFile(fileDialog.fileUrl);
        }
        onRejected: {
            console.log("Canceled")
        }
        Component.onCompleted: visible = true
    }


    function addHexagone(latitude, longitude, r, g, b, centreLong, centreLat){

        var component = Qt.createComponent("qrc:///hexagone.qml");
        var polygon = component.createObject(window);
        for(var i=0; i < latitude.length; i++){
            var coordinate = QtPositioning.coordinate(latitude[i], longitude[i]);
            polygon.addCoordinate(coordinate);
            polygon.color =  "#" + r + b+ g;
            polygon.centerLatitude = centreLat
            polygon.centerLongitude = centreLong
            listHexagones.push(polygon);
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
            listAntennes.push(antenne);
            map.addMapItem(antenne);
        }
        assignAntenneToHexagone();
    }

    function assignAntenneToHexagone(){
        var puissanceRecueMax;
        var positionAntenne = 0;
        for(var i = 0; i < listHexagones.length; i++){
            var coordinate = QtPositioning.coordinate(listHexagones[i].centerLatitude+0.005, listHexagones[i].centerLongitude+0.005);
            var puissanceRecueAncienne = 0;
            for(var j=0; j < listAntennes.length; j++){
                var puissanceRecue = 4000 / (4 * Math.PI * (coordinate.distanceTo(listAntennes[j].coordinate)));
                if(puissanceRecue > puissanceRecueAncienne){

                    puissanceRecueAncienne = puissanceRecue;
                    positionAntenne = j;

                }
            }
            listHexagones[i].color = listAntennes[positionAntenne].couleur;
            //listHexagones[i].opacity = 0.75 * puissanceRecue / 4000;
            console.log("recu " + i +" " + puissanceRecue + " max: " + 4000 +" position " + positionAntenne);
        }
    }
}
