import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

MapPolygon {
    id: marker
    opacity: 0.75
    property var centerLatitude
    property var centerLongitude
    MouseArea{
        id: mouse
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            addAntenne(centerLatitude, centerLongitude);
        }
    }

    function addAntenne(centerLatitude, centerLongitude){
        var component = Qt.createComponent("qrc:///antenne.qml");
        var antenne = component.createObject(window);

        var coordinate = QtPositioning.coordinate(centerLatitude, centerLongitude);
        antenne.coordinate = coordinate;
        console.log(antenne.coordinate);
        map.addMapItem(antenne);

    }
}


