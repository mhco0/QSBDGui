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

    ListModel {
        id: boundsList
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
        property int m_depth: 5
        property double m_minLon: -180.0
        property double m_maxLon: 180.0 
        property double m_minLat: -90.0
        property double m_maxLat: 90.0
        property var m_boxInPath: ({})
        property var m_lastDepthBox: ({})

        MapItemView {
            id: mapPointsView
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

        MapItemView {
            model: boundsList
            delegate: MapRectangle {
                color: fill_color
                border.color: bound_color
                border.width: 2
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

        function unitBox(topLeftLon, topLeftLat, bottomRightLon, bottomRightLat){
            let width = bottomRightLon - topLeftLon;
            let height = bottomRightLat - topLeftLat;
            return !(width > 1 || height > 1); 
        }

        function changeBox(topLeftLon, topLeftLat, bottomRightLon, bottomRightLat, dir){
            let centerX = (topLeftLon + bottomRightLon) / 2;
			let centerY = (topLeftLat + bottomRightLat) / 2;

			switch (dir){
				case 0 : {
					// ne
					return {
                            topLeftLon: centerX,
                            topLeftLat: topLeftLat,
                            bottomRightLon: bottomRightLon,
                            bottomRightLat: centerY
                            };
				}
				break;
				case 1 : {
					// nw
					return {
                            topLeftLon: topLeftLon,
                            topLeftLat: topLeftLat,
                            bottomRightLon: centerX,
                            bottomRightLat: centerY
                            };
				}
				break;
				case 2 : {
					// sw
					return {
                            topLeftLon: topLeftLon,
                            topLeftLat: centerY,
                            bottomRightLon: centerX,
                            bottomRightLat: bottomRightLat
                            };
				}
				break;
				case 3 : {
					// se
					return {
                            topLeftLon: centerX,
                            topLeftLat: centerY,
                            bottomRightLon: bottomRightLon,
                            bottomRightLat: bottomRightLat
                            };
				}
				break;
				default:{
					console.log("Invalid direction on quantile_quadtree::change_box");
				}
				break;
			}

            return {};
        }

        function direction(topLeftLon, topLeftLat, bottomRightLon, bottomRightLat, pointLon, pointLat){
            let centerX = (topLeftLon + bottomRightLon) / 2;
            let centerY = (topLeftLat + bottomRightLat) / 2;

            if(pointLon >= centerX && pointLat >= centerY) return 0;
            else if(pointLon < centerX && pointLat >= centerY) return 1;
            else if(pointLon < centerX && pointLat < centerY) return 2;
            else if(pointLon >= centerX && pointLat < centerY) return 3;
            else return 0;
        }

        function addPoint(mLon, mLat) {
            // change here later
            var coord = this.toCoordinate(Qt.point(mLon, mLat));
           /*if (newPoint.x() < minXdomain or newPoint.x() > maxXdomain or \
			newPoint.y() < minYdomain or newPoint.y() > maxYdomain) return;

		    minValueSeen = std::min(minValueSeen, val);
		    maxValueSeen = std::max(maxValueSeen, val);*/
            //let coord = QtPositioning.coordinate(mLat, mLon);
            let bound = {
                topLeftLon: this.m_minLon,
                topLeftLat: this.m_maxLat,
                bottomRightLon: this.m_maxLon,
                bottomRightLat: this.m_minLat
            };

            let whatChild = direction(bound.topLeftLon, bound.topLeftLat, bound.bottomRightLon, bound.bottomRightLat, coord.longitude, coord.latitude);
            let curDepth = 1;
            let path = "r"; //root node

            if(!(path in this.m_boxInPath)){
                addBound(this.m_minLon, this.m_maxLat, this.m_maxLon, this.m_minLat, path);
            }

            while(curDepth <= this.m_depth){
        
                let centerX = (bound.topLeftLon + bound.bottomRightLon) / 2;
                let centerY = (bound.topLeftLat + bound.bottomRightLat) / 2;

                if(!((path + "0") in this.m_boxInPath)){
                    addBound(centerX, bound.topLeftLat, bound.bottomRightLon, centerY, path + "0");
                }

                if(!((path + "1") in this.m_boxInPath)){
                    addBound(bound.topLeftLon, bound.topLeftLat, centerX, centerY, path + "1");
                }

                if(!((path + "2") in this.m_boxInPath)){
                    addBound(bound.topLeftLon, centerY, centerX, bound.bottomRightLat, path + "2");
                }

                if(!((path + "3") in this.m_boxInPath)){
                    addBound(centerX, centerY, bound.bottomRightLon, bound.bottomRightLat, path + "3");
                }

                path += whatChild.toString();
                
                bound = changeBox(bound.topLeftLon, bound.topLeftLat, bound.bottomRightLon, bound.bottomRightLat, whatChild);
                whatChild = direction(bound.topLeftLon, bound.topLeftLat, bound.bottomRightLon, bound.bottomRightLat, coord.longitude, coord.latitude);
                
                if(curDepth == this.m_depth){
                    if(!(path in this.m_lastDepthBox)){
                        this.m_lastDepthBox[path] = {bound: this.m_boxInPath[path], count: 1};
                    }else{
                        this.m_lastDepthBox[path].count += 1;
                    }
                }
            
                curDepth += 1;
            }

            mapPointsList.append({lat: coord.latitude, lon: coord.longitude});
            this.drawByDrawMode();
        }

        function addBound(topLeftLon, topLeftLat, bottomRightLon, bottomRightLat, path){
            let topCoord = QtPositioning.coordinate(topLeftLat, topLeftLon);
            let bottomCoord = QtPositioning.coordinate(bottomRightLat, bottomRightLon);

            boundsList.append({fill_color: "transparent", bound_color: "grey", topLeftLat: topCoord.latitude, topLeftLon: topCoord.longitude, bottomRightLat: bottomCoord.latitude, bottomRightLon: bottomCoord.longitude});
            this.m_boxInPath[path] = boundsList.get(boundsList.count - 1);
        }

        function addRectangle(topLeftLon, topLeftLat, bottomRightLon, bottomRightLat){
            let topCoord = QtPositioning.coordinate(topLeftLat, topLeftLon);
            let bottomCoord = QtPositioning.coordinate(bottomRightLat, bottomRightLon);

            queryRegionsList.append({map_color: "transparent", topLeftLat: topCoord.latitude, topLeftLon: topCoord.longitude, bottomRightLat: bottomCoord.latitude, bottomRightLon: bottomCoord.longitude});
        }

        function changeDrawMode(mode){
            this.m_drawMode = mode;
        }

        function drawByDrawMode(){
            switch (this.m_drawMode) {
                case 0: { // OnlyPoints

                    for(let i = 0; i < mapPointsList.count; i += 1){
                        for(let key in mapPointsList.get(i)){
                            console.log(key);
                        }
                    }

                    /*for(let path in this.m_boxInPath){
                        for(let prop in this.m_boxInPath[path]){
                            console.log(prop);
                        }
                        console.log(this.m_boxInPath[path].visible);
                        break;
                    }*/

                } break;
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
                //console.log(mapOsm.toCoordinate(Qt.point(mouse.x, mouse.y)));
                //}
            }

            onReleased: (mouse) =>{
                if (mouse.button == Qt.RightButton){
                    //console.log("release");
                }
            }
        }

        Component.onCompleted: {
            this.setBounds(-74.2628, -73.6983, 40.4762, 40.9177);
        }
    }
}