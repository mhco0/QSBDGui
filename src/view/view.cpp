#include "view.h"

namespace qsbd {
	
	void QueryGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
		emit dropEnd(this);
		QGraphicsRectItem::mouseReleaseEvent(event);
	}

	QueryGraphicsItem::QueryGraphicsItem(int myId){
		//setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
		id = myId;
		setZValue(2.0);
		setAcceptDrops(true);
		setFlag(QGraphicsItem::ItemIsSelectable);
		setFlag(QGraphicsItem::ItemIsMovable);
		setFlag(QGraphicsItem::ItemSendsGeometryChanges); 
	}
    
	View::View(QGraphicsScene* scene, QWidget* parent) : QGraphicsView(parent){
		this->scene = scene;
	}

	View::View(QWidget* parent) : QGraphicsView(parent){
		scene = new QGraphicsScene(this);
		setScene(scene);
		setFrameStyle(0);
		setAttribute(Qt::WA_StaticContents);
		setAttribute(Qt::WA_StyledBackground);
		setContentsMargins(0, 0, 0, 0);
		setMinimumSize(700, 480);
		//setFixedSize(700, 480);
		kCluster = 1;
		kSteps = 10;
		epsilon = 0.1;
		dbscanMin = 0;
		depthView = 0;
		clusterMethod = ClusterMethod::KMedoids;
		minValueSeen = 0x3f3f3f3f;
		maxValueSeen = -0x3f3f3f3f;
		maxXScene = 700.0;
		maxYScene = 480.0; 
		minXdomain = 0.0;
		minYdomain = 0.0;
		maxXdomain = 0.0;
		maxYdomain = 0.0;
		mapMinX = 0.0;
		mapMaxX = 0.0;
		mapMinY = 0.0;
		mapMaxY = 0.0;
		quantileToEstime = 0.5;
		drawMode = ViewDrawMode::OnlyPoints;
		queryCurId = 0;
		dragging = false;
		visiblePoints = true;
		showingAllQueries = true;
		queryRegion = nullptr;
		queriesColors[0] = Qt::red;
		queriesColors[1] = Qt::green;
		queriesColors[2] = Qt::blue;
		queriesColors[3] = Qt::magenta;
		queriesColors[4] = Qt::black;

		//svgBackground = new QGraphicsSvgItem("../assert/svg/USA_New_York_City_location_map.svg");
		/*QQuickWidget * osm = new QQuickWidget();

		osm->setSource(QUrl::fromLocalFile("../assert/qml/mapStatic.qml"));
		osm->setResizeMode(QQuickWidget::SizeRootObjectToView);
		osm->setMinimumSize(700, 480);
		*///osm->setSizePolicy( QSizePolicy::Expanding,  QSizePolicy::Expanding);
		// set view size		

		mapBackground = new QmlView();
		mapBackground->setMinimumSize(700, 480);
		mapBackground->setVisible(false);
		mapBackground->setZoom(startZoom);
		//mapBackground->installEventFilter(this);
		
		setRenderHints(QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);
    	setDragMode(QGraphicsView::ScrollHandDrag);
		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setMouseTracking(true);
		setStyleSheet(":disabled {background-color: darkGray} :enabled {background-color: white}");
		//background-image: url('../assert/svg/USA_New_York_City_location_map.svg')  0 0 0 0 stretch stretch; background-repeat: no-repeat; background-position: center;
		// 
		
		scene->addWidget(mapBackground);

		//qDebug() << mapBackground->getVisibleRegion();
		
		scene->setSceneRect(0, 0, maxXScene, maxYScene);
		fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
		originalTransform = transform(); 	
	}

	void View::mousePressEvent(QMouseEvent * event) {
		QGraphicsView::mousePressEvent(event);

		if(event->button() == Qt::RightButton){
			clickStart = event->pos();

			dragging = true;
		
			queryRegion = scene->addRect(QRectF(mapToScene(clickStart), QSize(2, 2)));
		}

		emit mousePressed();

		this->updateSceneStaticObjectsWithMap();
		this->updateSceneDynamicObjectsWithMap();
	}

	void View::mouseMoveEvent(QMouseEvent * event){
		QGraphicsView::mouseMoveEvent(event);

		curMousePos = event->pos();

		emit mouseMovement(curMousePos);

		if(dragging and queryRegion){
			QPoint topLeft = QPoint(qMin(clickStart.x(), event->x()), qMin(clickStart.y(), event->y()));
			QPoint bottomRight = QPoint(qMax(clickStart.x(), event->x()), qMax(clickStart.y(), event->y()));
			queryRegion->setRect(QRectF(mapToScene(topLeft), mapToScene(bottomRight)));
		}

		this->updateSceneStaticObjectsWithMap();
		if(mapBackground->dragging()){
			this->updateSceneDynamicObjectsWithMap();
		}
	}

	void View::mouseReleaseEvent(QMouseEvent * event) {
		QGraphicsView::mouseReleaseEvent(event);

		if(event->button() == Qt::RightButton){
			dragging = false;
		
			if(event->pos() != clickStart and queryCurId < 5){
				QPoint topLeft = QPoint(qMin(clickStart.x(), event->x()), qMin(clickStart.y(), event->y()));
				QPoint bottomRight = QPoint(qMax(clickStart.x(), event->x()), qMax(clickStart.y(), event->y()));
				QRectF query = QRectF(mapToScene(topLeft), mapToScene(bottomRight));
				//qDebug() << qSetRealNumberPrecision( 10 ) << query;

				// map screen points to lon / lat
				std::pair<double, double> translatedTopLeft = mapSceneToMapLonLat(query.topLeft());
				std::pair<double, double> translatedBottomRight = mapSceneToMapLonLat(query.bottomRight());
				QPointF topLeftMapped = QPointF(translatedTopLeft.first, translatedBottomRight.second);
				QPointF bottomRightMapped = QPointF(translatedBottomRight.first, translatedTopLeft.second);
				QRectF queryMapped = QRectF(topLeftMapped, bottomRightMapped);
				//qDebug() << queryMapped;

				logicQueries.push_back(queryMapped);
				//mapBackground->addRect(topLeftMapped.x(), topLeftMapped.y(), bottomRightMapped.x(), bottomRightMapped.y());
				
				if(!showingAllQueries) emit queryRequest(queryMapped);
				emit quantileRequest(queryMapped, queryCurId);
				//QGraphicsRectItem* item = scene->addRect(query);

				//item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
				//item->setZValue(2.0);	

				QueryGraphicsItem * item = new QueryGraphicsItem(queryCurId);
				item->setRect(query);
				item->setPen(QPen(queriesColors[queryCurId]));

				if (!showingAllQueries) item->setVisible(false);

				scene->addItem(item);

				QObject::connect(item, &QueryGraphicsItem::dropEnd, this, [&](QueryGraphicsItem* it){

					QRectF itemQueryBound = it->sceneBoundingRect();

					std::pair<double, double> itemTranslatedTopLeft = mapSceneToMapLonLat(itemQueryBound.topLeft());
					std::pair<double, double> itemTranslatedBottomRight = mapSceneToMapLonLat(itemQueryBound.bottomRight());
					
					QPointF itemTopLeftMapped = QPointF(itemTranslatedTopLeft.first, itemTranslatedBottomRight.second);
					QPointF itemBottomRightMapped = QPointF(itemTranslatedBottomRight.first, itemTranslatedTopLeft.second);
					//QRectF itemQueryMapped = QRectF(itemTopLeftMapped, itemBottomRightMapped);
					logicQueries[it->id].setTopLeft(itemTopLeftMapped);
					logicQueries[it->id].setBottomRight(itemBottomRightMapped);

					//mapBackground->addRect(itemTopLeftMapped.x(), itemTopLeftMapped.y(), itemBottomRightMapped.x(), itemBottomRightMapped.y());

					//qDebug() << qSetRealNumberPrecision( 10 ) << itemQueryBound;
					//qDebug() << qSetRealNumberPrecision( 10 ) << lonLatRectToSceneMapRect(logicQueries[it->id]);

					//qDebug() << itemQueryMapped;
					
					if(it->isVisible()) emit queryRequest(/*itemQueryMapped*/ logicQueries[it->id]);
					emit quantileRequest(/*itemQueryMapped*/ logicQueries[it->id], it->id);
				});

				queries.push_back(item);
				queryCurId++;
			}

			if(queryRegion){
				scene->removeItem(queryRegion);

				delete queryRegion;

				queryRegion = nullptr;
			}
		}

		this->updateSceneStaticObjectsWithMap();
		this->updateSceneDynamicObjectsWithMap();
	}

	void View::wheelEvent(QWheelEvent* pWheelEvent) {
		if (pWheelEvent->modifiers() & Qt::ControlModifier){
			// Do a wheel-based zoom about the cursor position
			double angle = pWheelEvent->angleDelta().y();
			double factor = qPow(1.0015, angle);

			/*auto targetViewportPos = pWheelEvent->pos();
			auto targetScenePos = mapToScene(pWheelEvent->pos());
			qDebug() << "factor : " << factor;
			scale(factor, factor);
			QTransform zoomedTransform = transform();
			zoomedTransform.setMatrix(qMax(originalTransform.m11(), zoomedTransform.m11()), zoomedTransform.m12(), zoomedTransform.m13(), zoomedTransform.m21(), qMax(originalTransform.m22(), zoomedTransform.m22()), zoomedTransform.m23(), zoomedTransform.m31(), zoomedTransform.m32(), zoomedTransform.m33());
			setTransform(zoomedTransform);
			centerOn(targetScenePos);
			QPointF deltaViewportPos = targetViewportPos - QPointF(viewport()->width() / 2.0, viewport()->height() / 2.0);
			QPointF viewportCenter = mapFromScene(targetScenePos) - deltaViewportPos;
			centerOn(mapToScene(viewportCenter.toPoint()));

			auto lonLat = mapScreenToLonLat(mapToScene(viewportCenter.toPoint()));*/

			//qDebug() << mapBackground->getVisibleRegion();

			mapBackground->setZoom(qMax(startZoom, mapBackground->getZoom()  + (factor - 1.0)));
			this->updateSceneStaticObjectsWithMap();
			this->updateSceneDynamicObjectsWithMap();

			return;
		}
    }

	void View::resizeEvent(QResizeEvent* event){
		QGraphicsView::resizeEvent(event);

		fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
		originalTransform = transform();
	}

	void View::updateBasedOnDrawMode(){
		//this->updateSceneStaticObjectsWithMap();

		switch(drawMode){
			case ViewDrawMode::OnlyPoints:
				for(auto& point : points){
					point->setVisible(visiblePoints);
				}

				for(auto& it : boxInPath){
					it.second->setVisible(false);
					it.second->setBrush(Qt::NoBrush);
				}
			break;
			case ViewDrawMode::QuadtreeDepth:
				for(auto& point : points){
					point->setVisible(visiblePoints);
				}
				
				for(auto& it : boxInPath){
					it.second->setBrush(Qt::NoBrush);
					if (it.first.size() - 1 == depthView){
						it.second->setVisible(true);
					}else{
						it.second->setVisible(false);
					}
				}
			break;
			case ViewDrawMode::Heatmap:
				for(auto& point : points){
					point->setVisible(visiblePoints);
				}

				for(auto& it : boxInPath){
					it.second->setVisible(false);
					//qDebug() << QString::fromUtf8(it.first.c_str());
					//qDebug() << it.second->sceneBoundingRect();
				}
				//qDebug() << "_______________\n";

				for(auto& it : lastDepthBoxesPath){
					//qDebug() << QString::fromUtf8(it.first.c_str());
					//qDebug() << it.second.first->sceneBoundingRect();
					it.second.first->setVisible(true);
					int total_points = points.size();
					int percent_points = ((it.second.second * 100) / total_points);
					int interval = 16;
					int index = percent_points / interval;

					switch(index) {
						case 0:
							it.second.first->setBrush(QBrush(QColor(239, 243, 255)));
						break; 
						case 1:
							it.second.first->setBrush(QBrush(QColor(198, 219, 239)));
						break;
						case 2:
							it.second.first->setBrush(QBrush(QColor(158, 202, 225)));
						break;
						case 3:
							it.second.first->setBrush(QBrush(QColor(107, 174, 214)));
						break;
						case 4:
							it.second.first->setBrush(QBrush(QColor(49, 130, 189)));
						break;
						case 5:
							it.second.first->setBrush(QBrush(QColor(8, 81, 156)));
						break;
						default:
							qDebug() << "This case should not be processed";
						break;
					}
				}
				//qDebug() << "_______________\n";
			break;
			case ViewDrawMode::KS:{
				for(auto& point : points){
					point->setVisible(visiblePoints);
				}

				for(auto& it : boxInPath){
					it.second->setBrush(Qt::NoBrush);
					if (it.first.size() - 1 == depthView){
						it.second->setVisible(true);
					}else{
						it.second->setVisible(false);
					}
				}

				//ksRegions = allPairsInResolution(depthView);
				cdfsRegions = regionsInResolution(depthView);

				std::vector<int> values_to_search = this->getKSLERP(5); 
				//std::vector<std::pair<QRectF, QRectF>> pairsBounds;
				std::vector<QRectF> regions_to_search;

				for(auto& it : cdfsRegions/*ksRegions*/){
					//pairsBounds.push_back({it.first->sceneBoundingRect(), it.second->sceneBoundingRect()});

					QRectF itemQueryBound = it->sceneBoundingRect();

					std::pair<double, double> itemTranslatedTopLeft = mapSceneToMapLonLat(itemQueryBound.topLeft());
					std::pair<double, double> itemTranslatedBottomRight = mapSceneToMapLonLat(itemQueryBound.bottomRight());
					
					QPointF itemTopLeftMapped = QPointF(itemTranslatedTopLeft.first, itemTranslatedBottomRight.second);
					QPointF itemBottomRightMapped = QPointF(itemTranslatedBottomRight.first,  itemTranslatedTopLeft.second);
					QRectF itemQueryMapped = QRectF(itemTopLeftMapped, itemBottomRightMapped);
					regions_to_search.emplace_back(itemQueryMapped);
				}

				emit cdfsRequest(regions_to_search, values_to_search);
			}
			break;
			case ViewDrawMode::QuantileEstimation:{
				for(auto& point : points){
					point->setVisible(visiblePoints);
				}

				for(auto& it : boxInPath){
					it.second->setBrush(Qt::NoBrush);
					if (it.first.size() - 1 == depthView){
						it.second->setVisible(true);
					}else{
						it.second->setVisible(false);
					}
				}

				medianEstimationRegions = regionsInResolution(depthView);

				std::vector<QRectF> regions_to_search;

				for(auto& it : medianEstimationRegions/*ksRegions*/){
					//pairsBounds.push_back({it.first->sceneBoundingRect(), it.second->sceneBoundingRect()});

					QRectF itemQueryBound = it->sceneBoundingRect();

					std::pair<double, double> itemTranslatedTopLeft = mapSceneToMapLonLat(itemQueryBound.topLeft());
					std::pair<double, double> itemTranslatedBottomRight = mapSceneToMapLonLat(itemQueryBound.bottomRight());
					
					QPointF itemTopLeftMapped = QPointF(itemTranslatedTopLeft.first, itemTranslatedBottomRight.second);
					QPointF itemBottomRightMapped = QPointF(itemTranslatedBottomRight.first,  itemTranslatedTopLeft.second);
					QRectF itemQueryMapped = QRectF(itemTopLeftMapped, itemBottomRightMapped);
					regions_to_search.emplace_back(itemQueryMapped);
				}

				emit quantileEstimationRequest(regions_to_search, quantileToEstime);
			}
			break;
			default:
			break;
		}
	}

	void View::change_box(aabb<double>& cur_box, short direction){
			double center_x = (cur_box.bounds().second.x() + cur_box.bounds().first.x()) / 2;
			double center_y = (cur_box.bounds().second.y() + cur_box.bounds().first.y()) / 2;

			switch (direction){
				case 0 : {
					// ne
					cur_box.bounds(center_x, center_y, cur_box.bounds().second.x(), cur_box.bounds().second.y());
				}
				break;
				case 1 : {
					// nw
					cur_box.bounds(cur_box.bounds().first.x(), center_y, center_x, cur_box.bounds().second.y());
				}
				break;
				case 2 : {
					// sw
					cur_box.bounds(cur_box.bounds().first.x(), cur_box.bounds().first.y(), center_x, center_y);
				}
				break;
				case 3 : {
					// se
					cur_box.bounds(center_x, cur_box.bounds().first.y(), cur_box.bounds().second.x(), center_y);
				}
				break;
				default:{
					qDebug() << "Invalid direction on quantile_quadtree::change_box";
				}
				break;
			}
		}

	short View::direction(const aabb<double>& box, const QPointF& pos){
		double center_x = (box.bounds().first.x() + box.bounds().second.x()) / 2;
		double center_y = (box.bounds().first.y() + box.bounds().second.y()) / 2;

		if(pos.x() >= center_x and pos.y() >= center_y) return 0;
		else if(pos.x() < center_x and pos.y() >= center_y) return 1;
		else if(pos.x() < center_x and pos.y() < center_y) return 2;
		else if(pos.x() >= center_x and pos.y() < center_y) return 3;
		else return 0;
	}

	bool View::unit_box(const aabb<double>& region){
		int width = region.bounds().second.x() - region.bounds().first.x();
		int height = region.bounds().second.y() - region.bounds().first.y();
		return not (width > 1 || height > 1);
	}

	std::pair<double, double> View::mapLonLatToScreen(double lon, double lat){
		double viewX = ((maxXScene / (maxXdomain - minXdomain)) * (lon - minXdomain));
		double viewY = maxYScene - ((maxYScene / (maxYdomain - minYdomain)) * (lat - minYdomain));

		return {viewX, viewY};
	}

	std::pair<double, double> View::mapScreenToLonLat(const QPointF& point){
		double lon = (point.x() / ((maxXScene / (maxXdomain - minXdomain)))) + minXdomain;
		double lat = ((point.y() - maxYScene) / -((maxYScene / (maxYdomain - minYdomain)))) + minYdomain;

		return {lon, lat}; 
	}

	std::pair<double, double> View::mapLonLatToSceneBasedOnMap(double lon, double lat){
		double viewX = (((lon - mapMinX) * maxXScene / (mapMaxX - mapMinX)));
		double viewY = maxYScene - ((lat - mapMinY) * (maxYScene / (mapMaxY - mapMinY)) );

		return {viewX, viewY};
	}

	std::pair<double, double> View::mapSceneToMapLonLat(const QPointF& point){
		double lon = ((mapMaxX - mapMinX) * point.x() / (maxXScene)) + mapMinX;
		double lat = ((mapMaxY - mapMinY) * (point.y() - maxYScene) / -(maxYScene)) + mapMinY;

		return {lon, lat}; 
	}

	std::vector<std::pair<QGraphicsRectItem*, QGraphicsRectItem*>> View::allPairsInResolution(const int& pdepth){
		std::vector<QGraphicsRectItem*> regions;
		std::vector<std::pair<QGraphicsRectItem*, QGraphicsRectItem*>> allPairs;

		for(auto& it : boxInPath){
			if (it.first.size() - 1 == pdepth){
				regions.emplace_back(it.second);
			}
		}

		for(size_t i = 0; i < regions.size(); i++){
			for(size_t j = 0; j < i; j++){
				allPairs.emplace_back(regions[i], regions[j]);
			}
		}

		return allPairs;
	}

	std::vector<QGraphicsRectItem*> View::regionsInResolution(const int& pdepth){
		std::vector<QGraphicsRectItem*> regions;

		for(auto& it : boxInPath){
			if (it.first.size() - 1 == pdepth){
				regions.emplace_back(it.second);
			}
		}

		return regions;
	}

	std::vector<int> View::getKSLERP(const int& n){
		assert(n > 0);
		std::vector<int> res;
		int range = maxValueSeen - minValueSeen;
		int step = range / n;


		for(int i = minValueSeen; i <= maxValueSeen and res.size() < n; i += step){
			res.push_back(i);
		}

		return res;
	}

	void View::setDrawingMode(const ViewDrawMode& option){
		drawMode = option;
		this->updateBasedOnDrawMode();
	}

	void View::setClusteringMethod(const ClusterMethod& option){
		clusterMethod = option;
		centroids.clear();
		//last_clustering.clear();
		this->updateBasedOnDrawMode();
	}

	void View::setDSBSCANEpsilon(const double& eps){
		epsilon = eps;
		this->updateBasedOnDrawMode();
	}

	void View::setDBSCANMin(const int& dbmin){
		dbscanMin = dbmin;
		this->updateBasedOnDrawMode();
	}

	void View::setQuantileEstimation(const double& quantile){
		this->quantileToEstime = quantile;
	}

	void View::setDomain(const double& minXRes, const double& minYRes, const double& maxXRes, const double& maxYRes){
		minXdomain = minXRes;
		minYdomain = minYRes;
		maxXdomain = maxXRes;
		maxYdomain = maxYRes;

		mapBackground->setBounds(minXRes, minYRes, maxXRes, maxYRes);

		this->updateMapDomain();
		/*auto pointEnd = scene->addEllipse(QRectF(maxXScene - 2, maxYScene - 2, 4, 4), QPen(Qt::blue));
		fitInView(scene->sceneRect());
		scene->removeItem(pointEnd);
		delete pointEnd;
		originalTransform = transform();*/
	}

	void View::updateMapDomain(){
		QRectF mapDomain = mapBackground->getVisibleRegion();

		mapMinX = mapDomain.topLeft().x();
		mapMaxX = mapDomain.bottomRight().x();
		mapMinY = mapDomain.bottomRight().y();
		mapMaxY = mapDomain.topLeft().y();
	}

	void View::updateSceneStaticObjectsWithMap(){
		this->updateMapDomain();

		assert(logicPoints.size() == points.size());

		for(size_t i = 0; i < logicPoints.size(); i++){
			auto translatedPoint = this->mapLonLatToSceneBasedOnMap(logicPoints[i].x(), logicPoints[i].y());
			QPointF point(translatedPoint.first, translatedPoint.second); 
			points[i]->setRect(QRectF(point.x() - 2, point.y() - 2, 4, 4));
		}

		assert(logicBoxInPath.size() == boxInPath.size());

		for(auto& key : logicBoxInPath){
			QRectF mapped = lonLatRectToSceneMapRect(key.second);

			boxInPath[key.first]->setRect(mapped);
		}

		show();
	}

	void View::updateSceneDynamicObjectsWithMap(){
		this->updateMapDomain();
		
		assert(logicQueries.size() == queries.size());

		for(size_t i = 0; i < logicQueries.size(); i++){
			/*QRectF itemQueryBound = it->sceneBoundingRect();

			std::pair<double, double> itemTranslatedTopLeft = mapSceneToMapLonLat(itemQueryBound.topLeft());
			std::pair<double, double> itemTranslatedBottomRight = mapSceneToMapLonLat(itemQueryBound.bottomRight());
			
			QPointF itemTopLeftMapped = QPointF(itemTranslatedTopLeft.first, itemTranslatedBottomRight.second);
			QPointF itemBottomRightMapped = QPointF(itemTranslatedBottomRight.first, itemTranslatedTopLeft.second);
			QRectF itemQueryMapped = QRectF(itemTopLeftMapped, itemBottomRightMapped);*/
			//qDebug() << logicQueries[i];
			//qDebug() << qSetRealNumberPrecision( 10 ) << lonLatRectToSceneMapRect(logicQueries[i]);
			QRectF mapped = lonLatRectToSceneMapRect(logicQueries[i]);

			queries[i]->setPos(mapped.topLeft());
			mapped.moveTo(0.0, 0.0);
			queries[i]->setRect(mapped);
			queries[i]->update();
		}

		show();
	}

	void View::setDepth(const int& maxDepth){
		depth = maxDepth;
		depthView = depth;
	}

	void View::setDepthView(const int& dpView){
		depthView = std::min(dpView, depth);
		centroids.clear();
		//last_clustering.clear();
		this->updateBasedOnDrawMode();
	}

	void View::setKCluster(const int& kc){
		kCluster = std::min(10, std::max(1, kc));
		centroids.clear();
		//last_clustering.clear();
		this->updateBasedOnDrawMode();
	}

	void View::addPoint(const QPointF& newPoint, const int& val){
		//qDebug() << newPoint;

		if (newPoint.x() < minXdomain or newPoint.x() > maxXdomain or \
			newPoint.y() < minYdomain or newPoint.y() > maxYdomain) return;

		minValueSeen = std::min(minValueSeen, val);
		maxValueSeen = std::max(maxValueSeen, val);

		//mapBackground->addPoint(newPoint.x(), newPoint.y());

		logicPoints.push_back(newPoint);

		auto translatedPoint = this->mapLonLatToSceneBasedOnMap(newPoint.x(), newPoint.y());

		QPointF point(translatedPoint.first, translatedPoint.second); 

		//qDebug() << point;

		auto pointPointer = scene->addEllipse(QRectF(point.x() - 2, point.y() - 2, 4, 4), QPen(Qt::blue));

		points.push_back(pointPointer);

		//aabb<double> bounds(0, 0, maxXScene, maxYScene);
		aabb<double> bounds(minXdomain, minYdomain, maxXdomain, maxYdomain);
		int what_child = direction(bounds, newPoint);
		int curDepth = 1;
		std::string path = "r"; //root node

		if(boxInPath.find(path) == boxInPath.end()){
			QRectF domainRect = QRectF(minXdomain, minYdomain, maxXdomain - minXdomain, maxYdomain - minYdomain);
			QRectF mapped = lonLatRectToSceneMapRect(domainRect);
			logicBoxInPath[path] = domainRect;

			//mapBackground->addRect(minXdomain, maxYdomain, maxXdomain, minYdomain);

			//auto rootPointer = scene->addRect(QRectF(0, 0, maxXScene, maxYScene), QPen(Qt::lightGray));
			auto rootPointer = scene->addRect(mapped, QPen(Qt::lightGray));
			boxInPath[path] = rootPointer;
		}

		while(curDepth <= this->depth /*and not unit_box(bounds)*/){
			// draw all childs
	
			double center_x = (bounds.bounds().first.x() + bounds.bounds().second.x()) / 2;
			double center_y = (bounds.bounds().first.y() + bounds.bounds().second.y()) / 2;

			// Bounds used by canvas

			QRectF neChild;
			neChild.setTopLeft(QPointF(center_x, center_y));
			neChild.setBottomRight(QPointF(bounds.bounds().second.x(), bounds.bounds().second.y()));
			
			QRectF nwChild;
			nwChild.setTopLeft(QPointF(bounds.bounds().first.x(), center_y));
			nwChild.setBottomRight(QPointF(center_x, bounds.bounds().second.y()));
			
			QRectF swChild;
			swChild.setTopLeft(QPointF(bounds.bounds().first.x(), bounds.bounds().first.y()));
			swChild.setBottomRight(QPointF(center_x, center_y));

			QRectF seChild;
			seChild.setTopLeft(QPointF(center_x, bounds.bounds().first.y()));
			seChild.setBottomRight(QPointF(bounds.bounds().second.x(), center_y));

			if(boxInPath.find(path + "0") == boxInPath.end()){
				QRectF mapped = lonLatRectToSceneMapRect(neChild);
				logicBoxInPath[path + "0"] = neChild;

				//mapBackground->addRect(neChild.topLeft().x(), neChild.topLeft().y(), neChild.bottomRight().x(), neChild.bottomRight().y());

				//auto nep = scene->addRect(neChild, QPen(Qt::lightGray));
				auto nep = scene->addRect(mapped, QPen(Qt::lightGray));
				boxInPath[path + "0"] = nep;
			}

			if(boxInPath.find(path + "1") == boxInPath.end()){
				QRectF mapped = lonLatRectToSceneMapRect(nwChild);
				logicBoxInPath[path + "1"] = nwChild;

				//mapBackground->addRect(nwChild.topLeft().x(), nwChild.topLeft().y(), nwChild.bottomRight().x(), nwChild.bottomRight().y());

				//auto nwp = scene->addRect(nwChild, QPen(Qt::lightGray));
				auto nwp = scene->addRect(mapped, QPen(Qt::lightGray));
				boxInPath[path + "1"] = nwp;
			}

			if(boxInPath.find(path + "2") == boxInPath.end()){
				QRectF mapped = lonLatRectToSceneMapRect(swChild);
				logicBoxInPath[path + "2"] = swChild;

				//mapBackground->addRect(swChild.topLeft().x(), swChild.topLeft().y(), swChild.bottomRight().x(), swChild.bottomRight().y());

				//auto swp = scene->addRect(swChild, QPen(Qt::lightGray));
				auto swp = scene->addRect(mapped, QPen(Qt::lightGray));
				boxInPath[path + "2"] = swp;
			}

			if(boxInPath.find(path + "3") == boxInPath.end()){
				QRectF mapped = lonLatRectToSceneMapRect(seChild);
				logicBoxInPath[path + "3"] = seChild;

				//mapBackground->addRect(seChild.topLeft().x(), seChild.topLeft().y(), seChild.bottomRight().x(), seChild.bottomRight().y());

				//auto sep = scene->addRect(seChild, QPen(Qt::lightGray));
				auto sep = scene->addRect(mapped, QPen(Qt::lightGray));
				boxInPath[path + "3"] = sep;
			}

			path += std::to_string(what_child);
			
			change_box(bounds, what_child);
			what_child = direction(bounds, newPoint);

			if(curDepth == this->depth){
				if(lastDepthBoxesPath.find(path) == lastDepthBoxesPath.end()){
					lastDepthBoxesPath[path] = {boxInPath[path], 1};
				}else{
					lastDepthBoxesPath[path].second += 1;
				}
			}

			curDepth++;
		}

		updateBasedOnDrawMode();
		show();
	}

	void View::onCdfsReady(const std::vector<std::vector<double>>& cdfs){
		if(cdfs.size() == 0) return;
		
		QColor cathegorys[10] = { QColor("#a6cee3"), QColor("#1f78b4"), QColor("#b2df8a"), QColor("#33a02c"), QColor("#fb9a99"), QColor("#e31a1c"), QColor("#fdbf6f"), QColor("#ff7f00"), QColor("#cab2d6"), QColor("#6a3d9a")}; 

		for(int i = 0; i < 10; i++){
			cathegorys[i].setAlpha(155);
		}

		auto ksFunction = [](const std::vector<double>& lhs, const std::vector<double>& rhs){
								double max_distance_distributions = std::numeric_limits<double>::min();

								for(size_t i = 0; i < lhs.size(); i++){
									double distribution_distance = fabs(lhs[i] - rhs[i]);
								
									max_distance_distributions = std::max(max_distance_distributions, distribution_distance);
								}

								return max_distance_distributions;
							};

		std::vector<int> region_clusters;
		switch(clusterMethod){
			case ClusterMethod::KMedoids:{
				auto ret = kmedoids<std::vector<double>>::cluster(kCluster, kSteps, cdfs, ksFunction, centroids);

				region_clusters = ret.first;
			}
			break;
			case ClusterMethod::DBSCAN:{
				std::vector<std::vector<double>> data = cdfs;

				auto dbscan = DBSCAN<std::vector<double>, double>();

				//std::cout << "minC: " << (float) (kCluster / 10.0) << std::endl;
				int ret = dbscan.Run(&data, cdfs[0].size(), epsilon, dbscanMin, ksFunction);

				auto clusters = dbscan.Clusters;
				auto noise = dbscan.Noise;

				region_clusters.resize(cdfs.size(), 0);

				//std::cout << "cluster sizes: " << clusters.size() << std::endl;
				//std::cout << "noise sizes: " << noise.size() << std::endl;

				size_t i = 0;
				for(; i < clusters.size(); i++){
					for(auto& it : clusters[i]){
						region_clusters[it] = i;
					}
				}

				for(size_t j = 0; j < noise.size(); j++){
					region_clusters[noise[j]] = std::min(i, (size_t)9);
					i++;
				}
			}
			break;
			case ClusterMethod::KMeans:{

				std::vector<std::vector<double>> data = cdfs;
				std::vector<carlosClustering::Point> cPoints;
				for(size_t i = 0; i < data.size(); i++){
					cPoints.emplace_back(i, data[i]);
				}

				//std::cout << "before" << std::endl;
				carlosClustering::KMeans cluster(kCluster, data.size(), data[0].size(), kSteps);
				//std::cout << "here" << std::endl; 
				cluster.run(cPoints);

				for(size_t i = 0; i < cPoints.size(); i++){
					region_clusters.emplace_back(cPoints[i].getCluster());
				}
			}
			break;
		}
		
		/*for(auto& it : centroids){
			std::cout << "cluster: " << region_clusters[it] << std::endl;
			for(size_t i = 0; i < cdfs[it].size(); i++){
				std::cout << cdfs[it][i] << " ";
			}
			std::cout << std::endl;
		}*/

		//qDebug() << cdfs.size() << " " << region_clusters.size();

		//assert(cdfs.size() == region_clusters.size());

		//if(last_clustering.size() == 0){
			//last_clustering.resize(region_clusters.size(), 0);

			for(size_t i = 0; i < cdfs.size(); i++){
				//last_clustering[i] = region_clusters[i];

				assert(region_clusters[i] >= 0 && region_clusters[i] < 10);
				

				//ksRegions[i].first->setBrush(QBrush(cathegorys[distribution(generator)]));
				//ksRegions[i].second->setBrush(QBrush(cathegorys[distribution(generator)]));
				//ksRegions[i].first->setVisible(true);
				//ksRegions[i].second->setVisible(true);

				cdfsRegions[i]->setBrush(QBrush(cathegorys[region_clusters[i]]));
				cdfsRegions[i]->setVisible(true);
			}
		/*}else{
			std::cout << "8--D" << std::endl;
			std::cout << region_clusters.size() << " " << last_clustering.size() << " " << cdfs.size() << std::endl;


			for(auto& it : region_clusters){
				std::cout << it << " ";
			}
			std::cout << std::endl;

			for(auto& it : last_clustering){
				std::cout << it << " ";
			}
			std::cout << std::endl;

			std::vector<int> last_clustering_frq;
			std::vector<int> clustering_frq;
			std::map<int, int> cluster_map;
			std::map<int, std::vector<int>> possible_choices;

			last_clustering_frq.resize(last_clustering.size(), 0);
			clustering_frq.resize(region_clusters.size(), 0);

			for(size_t i = 0; i < region_clusters.size(); i++){
				last_clustering_frq[last_clustering[i]] += 1;
				clustering_frq[region_clusters[i]] += 1;
				possible_choices[region_clusters[i]].emplace_back(last_clustering[i]);
			}

			for(size_t i = 0; i < region_clusters.size(); i++){
				if(last_clustering_frq[last_clustering[i]] == clustering_frq[region_clusters[i]]){
					cluster_map[region_clusters[i]] = last_clustering[i];
				}else{
					int probable_cluster = region_clusters[i];
					int max_frq = 0;
					for(auto& it: possible_choices[region_clusters[i]]){
						if(last_clustering_frq[it] > max_frq){
							max_frq = last_clustering_frq[it];
							probable_cluster = it;
						}
					}
				}
			}

			for(size_t i = 0; i < cdfs.size(); i++){
				last_clustering[i] = region_clusters[i];
				assert(region_clusters[i] >= 0 && region_clusters[i] < 10);
				

				//ksRegions[i].first->setBrush(QBrush(cathegorys[distribution(generator)]));
				//ksRegions[i].second->setBrush(QBrush(cathegorys[distribution(generator)]));
				//ksRegions[i].first->setVisible(true);
				//ksRegions[i].second->setVisible(true);

				cdfsRegions[i]->setBrush(QBrush(cathegorys[cluster_map[region_clusters[i]]]));
				cdfsRegions[i]->setVisible(true);
			}
		
		}*/

		show();
	}

	void View::onQuantileEstimationReady(const std::vector<int>& values){
		for(size_t i = 0; i < medianEstimationRegions.size(); i++){
			medianEstimationRegions[i]->setBrush(QBrush(QColor(0, 0, (((std::max(values[i], minValueSeen) - minValueSeen) * 255) / (double)maxValueSeen), 155)));
			medianEstimationRegions[i]->setVisible(true);
		}
	}

	void View::showOnlyQueryId(const int& queryId){
		for(size_t i = 0; i < queries.size(); i++){
			if (dynamic_cast<QueryGraphicsItem *>(queries[i])->id != queryId){
				queries[i]->setVisible(false);
			}else{
				queries[i]->setVisible(true);
			}
		}
		showingAllQueries = false;
	}

	void View::showAllQueries(){
		for(size_t i = 0; i < queries.size(); i++){
			queries[i]->setVisible(true);
		}
		showingAllQueries = true;
	}

	void View::hideAllQueries(){
		for(size_t i = 0; i < queries.size(); i++){
			queries[i]->setVisible(false);
		}
		showingAllQueries = false;
	}

	void View::clearQueries(){
		for(size_t i = 0; i < queries.size(); i++){
			scene->removeItem(queries[i]);

			delete queries[i];
		}

		queries.clear();
		logicQueries.clear();
		queryCurId = 0;
	}

	void View::clear(){
		clearQueries();

		for(size_t i = 0; i < points.size(); i++){
			scene->removeItem(points[i]);

			delete points[i];
		}

		points.clear();
		logicPoints.clear();
		minValueSeen = 0x3f3f3f3f;
		maxValueSeen = -0x3f3f3f3f;

		for(auto& it : boxInPath){
			scene->removeItem(it.second);

			delete it.second;
		}

		boxInPath.clear();
		logicBoxInPath.clear();
		lastDepthBoxesPath.clear();
		cdfsRegions.clear();
		
		drawMode = ViewDrawMode::OnlyPoints;
		depthView = 0;
	}

	void View::setRankAndQuantileQueryRequest(const int& id){
		for(size_t i = 0; i < queries.size(); i++){
			if (dynamic_cast<QueryGraphicsItem *>(queries[i])->id == id){
				QRectF itemQueryBound = queries[i]->sceneBoundingRect();

				//std::pair<double, double> itemTranslatedTopLeft = mapScreenToLonLat(itemQueryBound.topLeft());
				//std::pair<double, double> itemTranslatedBottomRight = mapScreenToLonLat(itemQueryBound.bottomRight());
				std::pair<double, double> itemTranslatedTopLeft = mapSceneToMapLonLat(itemQueryBound.topLeft());
				std::pair<double, double> itemTranslatedBottomRight = mapSceneToMapLonLat(itemQueryBound.bottomRight());
				
				QPointF itemTopLeftMapped = QPointF(itemTranslatedTopLeft.first, itemTranslatedBottomRight.second);
				QPointF itemBottomRightMapped = QPointF(itemTranslatedBottomRight.first,  itemTranslatedTopLeft.second);
				QRectF itemQueryMapped = QRectF(itemTopLeftMapped, itemBottomRightMapped);

				emit queryRequest(itemQueryMapped);
				emit quantileRequest(itemQueryMapped, id);
			}
		}
	}

	void View::setMapVisible(const bool& val){
		mapBackground->setVisible(val);
	}

	void View::setPointsVisibility(const bool& val){
		visiblePoints = val;
	}


	QRectF View::lonLatRectToSceneMapRect(const QRectF& bound){
		std::pair<double, double> translatedTopLeft = mapLonLatToSceneBasedOnMap(bound.topLeft().x(), bound.topLeft().y());
		std::pair<double, double> translatedBottomRight = mapLonLatToSceneBasedOnMap(bound.bottomRight().x(), bound.bottomRight().y());
		QPointF topLeftMapped = QPointF(translatedTopLeft.first, translatedBottomRight.second);
		QPointF bottomRightMapped = QPointF(translatedBottomRight.first, translatedTopLeft.second);
		QRectF mapped = QRectF(topLeftMapped, bottomRightMapped);

		return mapped;
	}

} // namespace qsbd