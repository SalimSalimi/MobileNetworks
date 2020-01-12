import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

MapQuickItem {
            id: antenne
            anchorPoint.x: icon.width * 0.5
            anchorPoint.y: icon.height * 0.8
            sourceItem: Image {
                    id: icon
                    source: "marker.png"
                    sourceSize.width: 60
                    sourceSize.height: 60

             }            

}

