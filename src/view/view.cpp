#include "view.h"

namespace qsbd {
	
	void QueryGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
		QGraphicsRectItem::mouseReleaseEvent(event);	
		emit dropEnd(this);
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
		maxXResolution = 700.0;
		maxYResolution = 480.0; 
		minXdomain = 0.0;
		minYdomain = 0.0;
		maxXdomain = 0.0;
		maxYdomain = 0.0;
		drawMode = ViewDrawMode::OnlyPoints;
		queryCurId = 0;
		dragging = false;
		showingAllQueries = true;
		queryRegion = nullptr;
		queriesColors[0] = Qt::red;
		queriesColors[1] = Qt::green;
		queriesColors[2] = Qt::blue;
		queriesColors[3] = Qt::magenta;
		queriesColors[4] = Qt::black;

		//svgBackground = new QGraphicsSvgItem("../assert/svg/USA_New_York_City_location_map.svg");
		QQuickWidget * osm = new QQuickWidget();

		osm->setSource(QUrl::fromLocalFile("../assert/qml/map.qml"));
		osm->setResizeMode(QQuickWidget::SizeRootObjectToView);
		osm->setMinimumSize(700, 480);
		//osm->setSizePolicy( QSizePolicy::Expanding,  QSizePolicy::Expanding);
		// set view size		
		
		auto pointBegin = scene->addEllipse(QRectF(-2, -2, 4, 4), QPen(Qt::blue));
		auto pointEnd = scene->addEllipse(QRectF(maxXResolution - 2, maxYResolution - 2, 4, 4), QPen(Qt::blue));
		//fitInView(scene->sceneRect());
		scene->removeItem(pointBegin);
		scene->removeItem(pointEnd);
		delete pointBegin;
		delete pointEnd;
		originalTransform = transform();
		
		setRenderHints(QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);
    	setDragMode(QGraphicsView::ScrollHandDrag);
		setMouseTracking(true);
		setStyleSheet(":disabled {background-color: darkGray} :enabled {background-color: white}");
		//background-image: url('../assert/svg/USA_New_York_City_location_map.svg')  0 0 0 0 stretch stretch; background-repeat: no-repeat; background-position: center;
		// 

		//svgBackground->setTransform(svgBackground->transform().scale(0.87500, 0.63408)); // fit to current view map scale based on svg file size. This only works with the current view port, change this scale after
		//scene->addItem(svgBackground);
		scene->addWidget(osm);

		fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);

		show();
	}

	void View::mousePressEvent(QMouseEvent * event) {
		if(event->button() == Qt::RightButton){
			clickStart = event->pos();

			dragging = true;
		
			queryRegion = scene->addRect(QRectF(mapToScene(clickStart), QSize(2, 2)));
		}

		emit mousePressed();

		QGraphicsView::mousePressEvent(event);
	}

	void View::mouseMoveEvent(QMouseEvent * event){
		curMousePos = event->pos();

		emit mouseMovement(curMousePos);

		if(dragging and queryRegion){
			QPoint topLeft = QPoint(qMin(clickStart.x(), event->x()), qMin(clickStart.y(), event->y()));
			QPoint bottomRight = QPoint(qMax(clickStart.x(), event->x()), qMax(clickStart.y(), event->y()));
			queryRegion->setRect(QRectF(mapToScene(topLeft), mapToScene(bottomRight)));
		}

		show();

		QGraphicsView::mouseMoveEvent(event);
	}

	void View::mouseReleaseEvent(QMouseEvent * event) {
		if(event->button() == Qt::RightButton){
			dragging = false;
		
			if(event->pos() != clickStart and queryCurId < 5){
				QPoint topLeft = QPoint(qMin(clickStart.x(), event->x()), qMin(clickStart.y(), event->y()));
				QPoint bottomRight = QPoint(qMax(clickStart.x(), event->x()), qMax(clickStart.y(), event->y()));
				QRectF query = QRectF(mapToScene(topLeft), mapToScene(bottomRight));

				// map screen points to lon / lat
				std::pair<double, double> translatedTopLeft = mapScreenToLonLat(query.topLeft());
				std::pair<double, double> translatedBottomRight = mapScreenToLonLat(query.bottomRight());
				QPointF topLeftMapped = QPointF(translatedTopLeft.first, translatedBottomRight.second);
				QPointF bottomRightMapped = QPointF(translatedBottomRight.first, translatedTopLeft.second);
				QRectF queryMapped = QRectF(topLeftMapped, bottomRightMapped);
				
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
					// Need to make query back to coord positions

					QRectF itemQueryBound = it->sceneBoundingRect();

					std::pair<double, double> itemTranslatedTopLeft = mapScreenToLonLat(itemQueryBound.topLeft());
					std::pair<double, double> itemTranslatedBottomRight = mapScreenToLonLat(itemQueryBound.bottomRight());
					
					QPointF itemTopLeftMapped = QPointF(itemTranslatedTopLeft.first, itemTranslatedBottomRight.second);
					QPointF itemBottomRightMapped = QPointF(itemTranslatedBottomRight.first,  itemTranslatedTopLeft.second);
					QRectF itemQueryMapped = QRectF(itemTopLeftMapped, itemBottomRightMapped);

					if(it->isVisible()) emit queryRequest(itemQueryMapped);
					emit quantileRequest(itemQueryMapped, it->id);
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

		show();
		QGraphicsView::mouseReleaseEvent(event);
	}

	void View::wheelEvent(QWheelEvent* pWheelEvent) {
		if (pWheelEvent->modifiers() & Qt::ControlModifier){
			// Do a wheel-based zoom about the cursor position
			double angle = pWheelEvent->angleDelta().y();
			double factor = qPow(1.0015, angle);

			auto targetViewportPos = pWheelEvent->pos();
			auto targetScenePos = mapToScene(pWheelEvent->pos());

			scale(factor, factor);
			QTransform zoomedTransform = transform();
			zoomedTransform.setMatrix(qMax(originalTransform.m11(), zoomedTransform.m11()), zoomedTransform.m12(), zoomedTransform.m13(), zoomedTransform.m21(), qMax(originalTransform.m22(), zoomedTransform.m22()), zoomedTransform.m23(), zoomedTransform.m31(), zoomedTransform.m32(), zoomedTransform.m33());
			setTransform(zoomedTransform);
			centerOn(targetScenePos);
			QPointF deltaViewportPos = targetViewportPos - QPointF(viewport()->width() / 2.0, viewport()->height() / 2.0);
			QPointF viewportCenter = mapFromScene(targetScenePos) - deltaViewportPos;
			centerOn(mapToScene(viewportCenter.toPoint()));

			return;
		}
    }

	void View::updateBasedOnDrawMode(){
		switch(drawMode){
			case ViewDrawMode::OnlyPoints:
				for(auto& point : points){
					point->setVisible(true);
				}

				for(auto& it : boxInPath){
					it.second->setVisible(false);
					it.second->setBrush(Qt::NoBrush);
				}
			break;
			case ViewDrawMode::QuadtreeDepth:
				for(auto& point : points){
					point->setVisible(true);
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
					point->setVisible(false);
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
					point->setVisible(true);
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

					std::pair<double, double> itemTranslatedTopLeft = mapScreenToLonLat(itemQueryBound.topLeft());
					std::pair<double, double> itemTranslatedBottomRight = mapScreenToLonLat(itemQueryBound.bottomRight());
					
					QPointF itemTopLeftMapped = QPointF(itemTranslatedTopLeft.first, itemTranslatedBottomRight.second);
					QPointF itemBottomRightMapped = QPointF(itemTranslatedBottomRight.first,  itemTranslatedTopLeft.second);
					QRectF itemQueryMapped = QRectF(itemTopLeftMapped, itemBottomRightMapped);
					regions_to_search.emplace_back(itemQueryMapped);
				}

				emit cdfsRequest(regions_to_search, values_to_search);
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
		double viewX = ((maxXResolution / (maxXdomain - minXdomain)) * (lon - minXdomain));
		double viewY = maxYResolution - ((maxYResolution / (maxYdomain - minYdomain)) * (lat - minYdomain));

		return {viewX, viewY};
	}

	std::pair<double, double> View::mapScreenToLonLat(const QPointF& point){
		double lon = (point.x() / ((maxXResolution / (maxXdomain - minXdomain)))) + minXdomain;
		double lat = ((point.y() - maxYResolution) / -((maxYResolution / (maxYdomain - minYdomain)))) + minYdomain;

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

	void View::setDomain(const double& minXRes, const double& minYRes, const double& maxXRes, const double& maxYRes){
		minXdomain = minXRes;
		minYdomain = minYRes;
		maxXdomain = maxXRes;
		maxYdomain = maxYRes;

		auto pointEnd = scene->addEllipse(QRectF(maxXResolution - 2, maxYResolution - 2, 4, 4), QPen(Qt::blue));
		fitInView(scene->sceneRect());
		scene->removeItem(pointEnd);
		delete pointEnd;
		originalTransform = transform();
	}

	void View::setDepth(const int& maxDepth){
		depth = maxDepth;
		depthView = depth;
	}

	void View::setDepthView(const int& dpView){
		depthView = std::min(dpView, depth);
	}

	void View::setKCluster(const int& kc){
		kCluster = std::min(10, std::max(1, kc));
		centroids.clear();
	}

	void View::addPoint(const QPointF& newPoint, const int& val){
		//qDebug() << newPoint;

		if (newPoint.x() < minXdomain or newPoint.x() > maxXdomain or \
			newPoint.y() < minYdomain or newPoint.y() > maxYdomain) return;

		minValueSeen = std::min(minValueSeen, val);
		maxValueSeen = std::max(maxValueSeen, val);

		auto translatedPoint = this->mapLonLatToScreen(newPoint.x(), newPoint.y());

		QPointF point(translatedPoint.first, translatedPoint.second); 

		//qDebug() << point;

		auto pointPointer = scene->addEllipse(QRectF(point.x() - 2, point.y() - 2, 4, 4), QPen(Qt::blue));

		points.push_back(pointPointer);

		aabb<double> bounds(0, 0, maxXResolution, maxYResolution);
		int what_child = direction(bounds, point);
		int curDepth = 1;
		std::string path = "r"; //root node

		if(boxInPath.find(path) == boxInPath.end()){
			auto rootPointer = scene->addRect(QRectF(0, 0, maxXResolution, maxYResolution), QPen(Qt::lightGray));
			boxInPath[path] = rootPointer;
		}

		while(curDepth <= this->depth and not unit_box(bounds)){
			// draw all childs
	
			double center_x = (bounds.bounds().first.x() + bounds.bounds().second.x()) / 2;
			double center_y = (bounds.bounds().first.y() + bounds.bounds().second.y()) / 2;

			// Bounds used by canvas

			QRectF neChild;
			neChild.setTopLeft(QPoint(center_x, center_y));
			neChild.setBottomRight(QPoint(bounds.bounds().second.x(), bounds.bounds().second.y()));
			
			QRectF nwChild;
			nwChild.setTopLeft(QPoint(bounds.bounds().first.x(), center_y));
			nwChild.setBottomRight(QPoint(center_x, bounds.bounds().second.y()));
			
			QRectF swChild;
			swChild.setTopLeft(QPoint(bounds.bounds().first.x(), bounds.bounds().first.y()));
			swChild.setBottomRight(QPoint(center_x, center_y));

			QRectF seChild;
			seChild.setTopLeft(QPoint(center_x, bounds.bounds().first.y()));
			seChild.setBottomRight(QPoint(bounds.bounds().second.x(), center_y));

			if(boxInPath.find(path + "0") == boxInPath.end()){
				auto nep = scene->addRect(neChild, QPen(Qt::lightGray));
				boxInPath[path + "0"] = nep;
			}

			if(boxInPath.find(path + "1") == boxInPath.end()){
				auto nwp = scene->addRect(nwChild, QPen(Qt::lightGray));
				boxInPath[path + "1"] = nwp;
			}

			if(boxInPath.find(path + "2") == boxInPath.end()){
				auto swp = scene->addRect(swChild, QPen(Qt::lightGray));
				boxInPath[path + "2"] = swp;
			}

			if(boxInPath.find(path + "3") == boxInPath.end()){
				auto sep = scene->addRect(seChild, QPen(Qt::lightGray));
				boxInPath[path + "3"] = sep;
			}

			path += std::to_string(what_child);
			
			change_box(bounds, what_child);
			what_child = direction(bounds, point);

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

				std::cout << "before" << std::endl;
				carlosClustering::KMeans cluster(kCluster, data.size(), data[0].size(), kSteps);
				std::cout << "here" << std::endl; 
				cluster.run(cPoints);

				
				for(size_t i = 0; i < cPoints.size(); i++){
					region_clusters.emplace_back(cPoints[i].getCluster() + 1);
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

		for(size_t i = 0; i < cdfs.size(); i++){
			assert(region_clusters[i] >= 0 && region_clusters[i] < 10);
			

			//ksRegions[i].first->setBrush(QBrush(cathegorys[distribution(generator)]));
			//ksRegions[i].second->setBrush(QBrush(cathegorys[distribution(generator)]));
			//ksRegions[i].first->setVisible(true);
			//ksRegions[i].second->setVisible(true);

			cdfsRegions[i]->setBrush(QBrush(cathegorys[region_clusters[i]]));
			cdfsRegions[i]->setVisible(true);
		}

		show();
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

	void View::clearQueries(){
		for(size_t i = 0; i < queries.size(); i++){
			scene->removeItem(queries[i]);

			delete queries[i];
		}

		queries.clear();
		queryCurId = 0;
	}

	void View::setRankAndQuantileQueryRequest(const int& id){
		for(size_t i = 0; i < queries.size(); i++){
			if (dynamic_cast<QueryGraphicsItem *>(queries[i])->id == id){
				QRectF itemQueryBound = queries[i]->sceneBoundingRect();

				std::pair<double, double> itemTranslatedTopLeft = mapScreenToLonLat(itemQueryBound.topLeft());
				std::pair<double, double> itemTranslatedBottomRight = mapScreenToLonLat(itemQueryBound.bottomRight());
				
				QPointF itemTopLeftMapped = QPointF(itemTranslatedTopLeft.first, itemTranslatedBottomRight.second);
				QPointF itemBottomRightMapped = QPointF(itemTranslatedBottomRight.first,  itemTranslatedTopLeft.second);
				QRectF itemQueryMapped = QRectF(itemTopLeftMapped, itemBottomRightMapped);

				emit queryRequest(itemQueryMapped);
				emit quantileRequest(itemQueryMapped, id);
			}
		}
	}

	/*
	void Canvas::mouseMoveEvent(QMouseEvent * event){
		curMousePos = event->pos();

		emit mouseMovement(curMousePos);

		update();
	}

	void Canvas::mousePressEvent(QMouseEvent * event){
		clickStart = event->pos();

		dragging = true;

		emit mousePressed();
	}

	void Canvas::mouseReleaseEvent(QMouseEvent * event){
		dragging = false;
	
		if(event->pos() != clickStart){
			QPoint topLeft = QPoint(qMin(clickStart.x(), event->x()), qMin(clickStart.y(), event->y()));
			
			int maxx = qMax(clickStart.x(), event->x());
			int maxy = qMax(clickStart.y(), event->y());
			int minx = topLeft.x();
			int miny = topLeft.y();

			QSize size = QSize(maxx - minx, maxy - miny);
			query = QRect(topLeft, size);

			emit queryRequest(convertRegion(query));
		}
	}


	void Canvas::wheelEvent(QWheelEvent * event){
		if(not applyZoom and event->angleDelta().y() > 0){
			zoomPoint = event->pos();
			applyZoom = true;
			update();
		}else if(applyZoom and event->angleDelta().y() < 0){
			zoomPoint = event->pos();
			applyZoom = false;
			update();
		}
	}

	void Canvas::change_box(QRect& cur_box, short direction){
			int center_x = (cur_box.topRight().x() + cur_box.bottomLeft().x()) / 2;
			int center_y = (cur_box.topRight().y() + cur_box.bottomLeft().y()) / 2;

			switch (direction){
				case 0 : {
					// ne
					cur_box.setBottomLeft(QPoint(center_x, center_y));
					cur_box.setTopRight(QPoint(cur_box.topRight().x(), cur_box.topRight().y()));

				}
				break;
				case 1 : {
					// nw
					cur_box.setBottomLeft(QPoint(cur_box.bottomLeft().x(), center_y));
					cur_box.setTopRight(QPoint(center_x, cur_box.topRight().y()));

				}
				break;
				case 2 : {
					// sw
					cur_box.setBottomLeft(QPoint(cur_box.bottomLeft().x(), cur_box.bottomLeft().y()));
					cur_box.setTopRight(QPoint(center_x, center_y));

				}
				break;
				case 3 : {
					// se
					cur_box.setBottomLeft(QPoint(center_x, cur_box.bottomLeft().y()));
					cur_box.setTopRight(QPoint(cur_box.topRight().x(), center_y));

				}
				break;
				default:{
					qDebug() << ("Invalid direction on quantile_quadtree::change_box");
				}
				break;
			}
		}

	short Canvas::direction(const QRect& box, const QPointF& pos){
		int center_x = (box.bottomLeft().x() + box.topRight().x()) / 2;
		int center_y = (box.bottomLeft().y() + box.topRight().y()) / 2;

		if(pos.x() >= center_x and pos.y() >= center_y) return 3;
		else if(pos.x() < center_x and pos.y() >= center_y) return 2;
		else if(pos.x() < center_x and pos.y() < center_y) return 1;
		else if(pos.x() >= center_x and pos.y() < center_y) return 0;
		else return 0;
	}

	bool Canvas::unit_box(const QRect& region){
		int width = region.topRight().x() - region.bottomLeft().x();
		int height = region.topRight().y() - region.bottomLeft().y();
		return not (width > 1 || height > 1);
	}

	QRect Canvas::convertRegion(const QRect& region){
		QPoint topL = region.topLeft();
		QPoint bottomR = region.bottomRight();

		topL.setX(qMax((topL.x() * maxXResolution) / minimumWidth(), 0.0));
		topL.setY(qMin((topL.y() * maxYResolution) / minimumHeight(), maxYResolution));
		bottomR.setX(qMin((bottomR.x() * maxXResolution) / minimumWidth(), maxXResolution));
		bottomR.setY(qMax((bottomR.y() * maxYResolution) / minimumHeight(), 0.0));

		return QRect(topL, bottomR);
	}

	QColor Canvas::colorBasedOnFrequency(const uint& points){
		int frequencyForColor[6]  = {1, 10, 50, 100, 500, 1000};

		for(int i = 0; i < 6; i++){
			if(points <= frequencyForColor[i]){
				return boxGradient[i];
			}
		}

		return boxGradient[5];
	}

	Canvas::Canvas(QWidget* parent) : QWidget(parent), myPen(Qt::SolidLine), myBrush(Qt::CrossPattern), query(0, 0, 0, 0){
		setAttribute(Qt::WA_StaticContents);
		setAttribute(Qt::WA_StyledBackground);
		setContentsMargins(0, 0, 0, 0);
		setMinimumSize(620, 480);
		maxXResolution = 620.0;
		maxYResolution = 480.0;
		setMouseTracking(true);
		setStyleSheet(":disabled {background-color: darkGray } :enabled {background-color: white}");

		myBrush.setColor(Qt::black);

		zoomScale = 1.5;
		applyZoom = false;
		dragging = false;
		drawBounds = false;

		boxGradient[0] = QColor(239, 243, 255);
		boxGradient[1] = QColor(198, 219, 239);
		boxGradient[2] = QColor(158, 202, 225);
		boxGradient[3] = QColor(107, 174, 214);
		boxGradient[4] = QColor(49, 130, 189);
		boxGradient[5] = QColor(8, 81, 156);

		show();
	}

	void Canvas::paintEvent(QPaintEvent* event){
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);
		int backgroundWidth = 1;
		int pointWidth = 5;

		if(applyZoom){
			painter.translate(-zoomPoint.x() * zoomScale + minimumWidth() * zoomScale / 2, -zoomPoint.y() * zoomScale + minimumHeight() * zoomScale / 2);
			painter.scale(zoomScale, zoomScale);
			backgroundWidth *= zoomScale;
			pointWidth *= zoomScale;
		}

		for(auto& it : data){
			myPen.setColor(Qt::blue);
			myPen.setWidth(pointWidth);

			painter.setPen(myPen);
			painter.setBackground(myBrush);
			painter.drawPoint(it);

			myPen.setColor(Qt::black);
			myPen.setWidth(backgroundWidth);
			painter.setPen(myPen);
			painter.setBackground(myBrush);

			QRect bounds(0, 0, minimumWidth() - 1, minimumHeight() - 1);
			painter.drawRect(bounds);

			if (drawBounds){
				int what_child = direction(bounds, it);
				int curDepth = 1;
				std::string path = std::to_string(what_child);

				myPen.setColor(Qt::lightGray);
				painter.setPen(myPen);

				while(curDepth <= this->depth and not unit_box(bounds)){
					// draw all childs
			
					int center_x = (bounds.topRight().x() + bounds.bottomLeft().x()) / 2;
					int center_y = (bounds.topRight().y() + bounds.bottomLeft().y()) / 2;

					// Bounds used by canvas
					QRect nwChild(QPoint(center_x, bounds.topRight().y()), QPoint(bounds.topRight().x(), center_y));
					QRect neChild(QPoint(bounds.bottomLeft().x(), bounds.topRight().y()), QPoint(center_x, center_y));
					QRect seChild(QPoint(bounds.bottomLeft().x(), center_y), QPoint(center_x, bounds.bottomLeft().y()));
					QRect swChild(QPoint(center_x, center_y), QPoint(bounds.topRight().x(), bounds.bottomLeft().y()));

					painter.drawRect(nwChild);
					painter.drawRect(neChild);
					painter.drawRect(seChild);
					painter.drawRect(swChild);

					if(curDepth == this->depth){
						QRect copy;
						bool find = false;
						int leaf_child = direction(bounds, it);
						switch(leaf_child){
							case 0:
								copy = nwChild;
							break;
							case 1:
								copy = neChild;
							break;
							case 2:
								copy = seChild;
							break;
							case 3:
								copy = swChild;
							break;
						}

						path += std::to_string(leaf_child);

						if(boxInPath.find(path) == boxInPath.end()){
							boxInPath[path] = {copy, 1};
						}else{
							boxInPath[path].second += 1;
						}
					}

					change_box(bounds, what_child);
					what_child = direction(bounds, it);
					path += std::to_string(what_child);

					curDepth++;
				}
			}
		}

		if(drawBounds){
			for(auto& it : boxInPath){
				painter.fillRect(it.second.first, colorBasedOnFrequency(it.second.second));
				it.second.second = 0;
			}
		}

		if(dragging){
			QPainter painterQuery(this);
			QPoint topLeft = QPoint(qMin(clickStart.x(), curMousePos.x()), qMin(clickStart.y(), curMousePos.y()));
			
			int maxx = qMax(clickStart.x(), curMousePos.x());
			int maxy = qMax(clickStart.y(), curMousePos.y());
			int minx = topLeft.x();
			int miny = topLeft.y();

			QSize size = QSize(maxx - minx, maxy - miny);
			query = QRect(topLeft, size);

			painterQuery.setPen(myPen);
			painterQuery.setBackground(myBrush);
			painterQuery.drawRect(query);
		} 
	}

	void Canvas::addPoint(const QPointF& newPoint){
		double xScale = (newPoint.x() * minimumWidth()) / maxXResolution;
		double yScale = (newPoint.y() * minimumHeight()) / maxYResolution;

		QPointF scalePoint(xScale, yScale);

		data.push_back(scalePoint);
		update();
	}

	void Canvas::setDepth(const int& maxDepth){
		depth = maxDepth;
	}

	
	void Canvas::setBoundsDrawing(const bool& option){
		drawBounds = option;
		update();
	}

	void Canvas::setResolution(const double& xRes, const double& yRes){
		maxXResolution = xRes;
		maxYResolution = yRes;
	}*/

} // namespace qsbd
