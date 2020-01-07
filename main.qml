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

        MapPolygon {
                color: 'green'
                path: [
                    { latitude: 47.74579, longitude: 7.3383 },
                    { latitude: 47.74571, longitude: 7.33659 },
                    { latitude: 47.74452, longitude: 7.33662 },
                    { latitude: 47.74453, longitude: 7.33821 },
                    { latitude: 47.74605, longitude: 7.33718 },
                    { latitude: 47.74578, longitude: 7.33652 }
                ]
            }
    }


}
