import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

MapPolygon {
    id: marker
    opacity: 0.75
    property var coordinate: {
        latitude: 5
        longitude : 0
    }
    property var antenne
    MouseArea{
        id: mouse
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            addAntenne(coordinate.latitude, coordinate.longitude);
            assignAntenneToHexagone();
        }
    }

    function addAntenne(centerLatitude, centerLongitude){
        var component = Qt.createComponent("qrc:///antenne.qml");
        var antenne = component.createObject(window);

        var coordinate = QtPositioning.coordinate(centerLatitude, centerLongitude);
        antenne.coordinate = coordinate;
        antenne.couleur = "#156593";
        console.log(antenne.coordinate);
        listAntennes.push(antenne);
        map.addMapItem(antenne);

    }
}


