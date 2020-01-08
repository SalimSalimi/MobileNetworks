import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6

Window {
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

    Map {
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(47.746, 7.3384) // Mulhouse
        zoomLevel: 14
        gesture.enabled: true
        gesture.maximumZoomLevelChange: 15

        Repeater {
            model: 6
            MapPolygon {
                        color: "red"
                        border.color: "green"
                        border.width: 2
                        smooth: true
                        opacity: 0.25
                        geoShape: poly
            }
        }

    }

}
