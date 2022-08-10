import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

Rectangle {
    Plugin {
        id: mapPlugin
        name: "osm" // "mapboxgl", "esri", ...
        // specify plugin parameters if necessary
        // PluginParameter {
        //     name:
        //     value:
        // }

        PluginParameter {
            name: "osm.mapping.providersrepository.disabled"
            value: "true"
        }
        PluginParameter {
            name: "osm.mapping.providersrepository.address"
            value: "http://maps-redirect.qt.io/osm/5.6/"
        }
    }

    ListModel {
        id: mapPointsList
    }

    Map {
        id: mapOsm
        anchors.fill: parent
        plugin: mapPlugin
        //gesture.acceptedGestures: (MapGestureArea.PinchGesture | MapGestureArea.FlickGesture |MapGestureArea.RotationGesture | MapGestureArea.TiltGesture)
        center: QtPositioning.coordinate(40.69, -73.97) 
        zoomLevel: 10

        MapItemView {
            model: mapPointsList
            delegate: MapCircle {
                radius: 200
                color: 'cyan'
                center {
                    latitude: lat
                    longitude: lon
                }
            }
        }

        function addPoint(mLat, mLon) {
            var coord = this.toCoordinate(Qt.point(mLat, mLon));
            mapPointsList.append({lat: coord.latitude, lon: coord.longitude});
        }

        function addRectangle(topLeftLat, topLeftLon, bottomRightLat, bottomRightLon){

        }

        MouseArea{
            anchors.fill: parent
            onPressed: {
                mapOsm.addPoint(mouse.x, mouse.y);
            }
        }
    }
}