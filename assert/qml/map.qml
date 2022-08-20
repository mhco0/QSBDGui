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

    ListModel {
        id: queryRegionsList
    }

    Map {
        id: mapOsm
        objectName: "mapOsm"
        anchors.fill: parent
        plugin: mapPlugin
        //gesture.acceptedGestures: (MapGestureArea.PinchGesture | MapGestureArea.FlickGesture |MapGestureArea.RotationGesture | MapGestureArea.TiltGesture)
        center: QtPositioning.coordinate(40.69, -73.97) 
        zoomLevel: 10

        property int m_drawMode: 0
        property int m_depth: 0
        property double m_minLon: -180.0
        property double m_maxLon: 180.0 
        property double m_minLat: -90.0
        property double m_maxLat: 90.0

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

        MapItemView {
            model: queryRegionsList
            delegate: MapRectangle {
                color: map_color
                border.width: 20
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

        function setDepth(depth){
            this.m_depth = depth;
        }

        function setBounds(minLon, maxLon, minLat, maxLat){
            this.m_minLon = minLon;
            this.m_maxLon = maxLon;
            this.m_minLat = minLat;
            this.m_maxLat = maxLat;
            
            this.center = QtPositioning.coordinate((this.m_minLat + this.m_maxLat) / 2, (this.m_minLon + this.m_maxLon) / 2);
        }

        function addPoint(mLon, mLat) {
           // var coord = this.toCoordinate(Qt.point(mLon, mLat));
           /*if (newPoint.x() < minXdomain or newPoint.x() > maxXdomain or \
			newPoint.y() < minYdomain or newPoint.y() > maxYdomain) return;

		    minValueSeen = std::min(minValueSeen, val);
		    maxValueSeen = std::max(maxValueSeen, val);*/
            var coord = QtPositioning.coordinate(mLat, mLon);
            mapPointsList.append({lat: coord.latitude, lon: coord.longitude});
        }

        function addRectangle(topLeftLon, topLeftLat, bottomRightLon, bottomRightLat){
            var topCoord = QtPositioning.coordinate(topLeftLat, topLeftLon);
            var bottomCoord = QtPositioning.coordinate(bottomRightLat, bottomRightLon);

            queryRegionsList.append({map_color: "transparent", topLeftLat: topCoord.latitude, topLeftLon: topCoord.longitude, bottomRightLat: bottomCoord.latitude, bottomRightLon: bottomCoord.longitude});
        }

        function changeDrawMode(mode){
            this.m_drawMode = mode;

            console.log(mode);

            switch (mode) {
                case 0: // OnlyPoints
                    break;
            
                case 1: // DrawQuadtreeAndPoints
                    break;

                case 2: // Heatmap
                    break;

                case 3: // KS
                default:
                    break;
            }
        }

        MouseArea{
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            hoverEnabled: true

            onPressed: (mouse) => {
                if (mouse.button == Qt.RightButton){
                    mapOsm.addPoint(mouse.x, mouse.y);
                }
            }

            onPositionChanged: (mouse) => {
                //if (mouse.button == Qt.RightButton){
                console.log(mapOsm.toCoordinate(Qt.point(mouse.x, mouse.y)));
                //}
            }

            onReleased: (mouse) =>{
                if (mouse.button == Qt.RightButton){
                    console.log("release");
                }
            }
        }

        Component.onCompleted: {
            this.setBounds(-74.2628, -73.6983, 40.4762, 40.9177);
        }
    }
}