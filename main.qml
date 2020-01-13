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

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    function addHexagone(latitude, longitude, r, g, b){

        var component = Qt.createComponent("qrc:///hexagone.qml");
        var polygon = component.createObject(window);
        for(var i=0; i < latitude.length; i++){
            var coordinate = QtPositioning.coordinate(latitude[i], longitude[i]);
            polygon.addCoordinate(coordinate);
            polygon.color =  "#" + r + b+ g;

            listHexagones.push(polygon);
        }
        map.addMapItem(polygon);
    }

    function addAntenne(){

        var latitude = middleware.listLatitude;
        var longitude = middleware.listLongitude;
        console.log(latitude.length);
        for (var i = 0; i < latitude.length; i++){
            var coordinate = QtPositioning.coordinate(latitude[i], longitude[i]);
            var component = Qt.createComponent("qrc:///antenne.qml");
            var antenne = component.createObject(window);

            antenne.coordinate = coordinate;
            map.addMapItem(antenne);
        }
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
            Qt.quit()
        }
        Component.onCompleted: visible = true
    }

}
