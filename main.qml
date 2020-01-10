import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6

Window {
    id: window
    width: 512
    height: 512
    visible: true

    Plugin {
        id: mapPlugin
        name: "osm" // "mapboxgl", "esri", ...
        // specify plugin parameters if necessary
        // PluginParameter {
        //     name:
        //     value:
        // }
    }

    function addHexagone(latitude, longitude){

        var component = Qt.createComponent("qrc:///hexagone.qml");
        var polygon = component.createObject(window);

        for(var i=0; i < latitude.length; i++){
            var coordinate = QtPositioning.coordinate(latitude[i], longitude[i]);
            console.log(coordinate + " iterate:" +i);
            polygon.addCoordinate(coordinate);
        }
        map.addMapItem(polygon);
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(47.746, 7.3384) // Mulhouse
        zoomLevel: 14
        gesture.enabled: true

    }

}
