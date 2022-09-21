import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

Rectangle {
    Plugin {
        id: mapPlugin
        /*name: "osm" // "mapboxgl", "esri", ...
        // specify plugin parameters if necessary
        // PluginParameter {
        //     name:
        //     value:
        // }

        PluginParameter {
            name: "osm.mapping.providersrepository.disabled"
            value: true
        }

        PluginParameter {
            name: "osm.mapping.providersrepository.address"
            value: "http://maps-redirect.qt.io/osm/5.6/"
        }/*

        /*PluginParameter{
            name: "osm.mapping.custom.host"
            value: "https://tile.openstreetmap.org/"
        }*/

        name: "mapboxgl"

        PluginParameter {
            name: "mapboxgl.access_token"
            value: "pk.eyJ1IjoibWhjbyIsImEiOiJjbDhid2M2eTEwMzR5M3BxeDkwYmU3ZGF0In0.SnFxCUWcKSwCvPvsxLq0DQ"
        }

        PluginParameter {
            name: "mapboxgl.mapping.additional_style_urls"
            value: "https://api.maptiler.com/maps/toner/?key=72bqHhc8737Y2wmCBenD"
        }
    }

    ListModel {
        id: mapPointsList
    }

    ListModel {
        id: queryRegionsList
    }

    Map {
        id: mapOSM 
        objectName: "mapOSM"
        anchors.fill: parent
        plugin: mapPlugin
        activeMapType: supportedMapTypes[7] 
        gesture.acceptedGestures: (MapGestureArea.PanGesture | MapGestureArea.PinchGesture | MapGestureArea.FlickGesture |MapGestureArea.RotationGesture | MapGestureArea.TiltGesture)
        gesture.preventStealing: true
        center: QtPositioning.coordinate(40.69, -73.97) 
        zoomLevel: 0

          

        property double m_minLon: -180.0
        property double m_maxLon: 180.0 
        property double m_minLat: -90.0
        property double m_maxLat: 90.0

        MapItemView {
            id: mapPointsView
            model: mapPointsList
            delegate: MapCircle {
                radius: 2000
                color: 'green'
                center {
                    latitude: lat
                    longitude: lon
                }
            }
        }

        MapItemView {
            model: queryRegionsList
            delegate: MapRectangle {
                color: map_color
                border.width: 10
                topLeft {
                    latitude: topLeftLat
                    longitude: topLeftLon
                }
                bottomRight {
                    latitude: bottomRightLat
                    longitude: bottomRightLon
                }
            }
        }


        function setBounds(minLon, maxLon, minLat, maxLat){
            mapOSM.m_minLon = minLon;
            mapOSM.m_maxLon = maxLon;
            mapOSM.m_minLat = minLat;
            mapOSM.m_maxLat = maxLat;
            
            mapOSM.center = QtPositioning.coordinate((mapOSM.m_minLat + mapOSM.m_maxLat) / 2, (mapOSM.m_minLon + mapOSM.m_maxLon) / 2);
            
            
            /*for(let i = 0; i < mapOSM.supportedMapTypes.length; i++){
                console.log(mapOSM.supportedMapTypes[i]);
            }*/
        }

        function addPoint(mLon, mLat) {
            // change here later
           
            mapPointsList.append({lat: mLat, lon: mLon});
        }

        function addRect(topLeftLon, topLeftLat, bottomRightLon, bottomRightLat){
            let topCoord = QtPositioning.coordinate(topLeftLat, topLeftLon);
            let bottomCoord = QtPositioning.coordinate(bottomRightLat, bottomRightLon);

            queryRegionsList.append({map_color: "transparent", topLeftLat: topCoord.latitude, topLeftLon: topCoord.longitude, bottomRightLat: bottomCoord.latitude, bottomRightLon: bottomCoord.longitude});
        }


        function setZoom(zoom){
            //console.log(zoom);
            
            mapOSM.zoomLevel = zoom;   
        }

        function getZoom(){
            return mapOSM.zoomLevel;
        }

        function centerOn(lon, lat){
            mapOSM.center = QtPositioning.coordinate(lat, lon); 
        }

        function getVisibleRegion(){
            if(!mapOSM.visibleRegion.isValid) return null;

            var polygonShape = QtPositioning.shapeToPolygon(mapOSM.visibleRegion);
            //console.log(polygonShape.perimeter);
            var convertedRect = QtPositioning.rectangle(polygonShape.perimeter[2], polygonShape.perimeter[0]);
            /*console.log("{", convertedRect.topLeft.latitude, ", ", convertedRect.topLeft.latitude, "}");
            console.log("{", convertedRect.bottomRight.latitude, ", ", convertedRect.bottomRight.longitude, "}");
            console.log(Object.keys(polygonShape));*/
            
            //console.log(convertedRect);

            return JSON.stringify({topLeftLat: convertedRect.topLeft.latitude, topLeftLon: convertedRect.topLeft.longitude, bottomRightLat: convertedRect.bottomRight.latitude, bottomRightLon: convertedRect.bottomRight.longitude});
        }
    }
}