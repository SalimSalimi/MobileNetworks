import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

MapPolygon {
            id: marker
            opacity: 0.75
            color: "green"

            MouseArea{
                id: mouse
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                //property var coordinate: parent.parent.toCoordinate(Qt.point(mouseX, mouseY))
                onClicked: {
                    //console.log(coordinate);
                    //addAntenne(coordinate);
                }
            }


    function addAntenne(coordinateArea){
                var component = Qt.createComponent("qrc:///antenne.qml");
                var antenne = component.createObject(window);

                var coordinate = QtPositioning.coordinate(coordinateArea);
                antenne.coordinate = coordinateArea;
                console.log(antenne.coordinate);
                map.addMapItem(antenne);

            }
}


