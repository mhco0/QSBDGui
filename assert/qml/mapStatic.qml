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

    Map {
        id: mapOSM 
        objectName: "mapOSM"
        anchors.fill: parent
        plugin: mapPlugin
        gesture.acceptedGestures: (MapGestureArea.PinchGesture | MapGestureArea.FlickGesture |MapGestureArea.RotationGesture | MapGestureArea.TiltGesture)
        center: QtPositioning.coordinate(40.69, -73.97) 
        zoomLevel: 0   

        property double m_minLon: -180.0
        property double m_maxLon: 180.0 
        property double m_minLat: -90.0
        property double m_maxLat: 90.0

        function setBounds(minLon, maxLon, minLat, maxLat){
            mapOSM.m_minLon = minLon;
            mapOSM.m_maxLon = maxLon;
            mapOSM.m_minLat = minLat;
            mapOSM.m_maxLat = maxLat;
            
            mapOSM.center = QtPositioning.coordinate((mapOSM.m_minLat + mapOSM.m_maxLat) / 2, (mapOSM.m_minLon + mapOSM.m_maxLon) / 2);
        }

        function setZoom(zoom){
            console.log(zoom);
            mapOSM.zoomLevel = zoom;
        }

        function getZoom(){
            return mapOSM.zoomLevel;
        }
    }
}