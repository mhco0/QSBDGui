#include "qmlview.h"

namespace qsbd {

	
	
	void QmlView::mouseMoveEvent(QMouseEvent* event){
		QQuickWidget::mouseMoveEvent(event);
		//event->setAccepted(false);
	}
	
	void QmlView::mousePressEvent(QMouseEvent* event){
		QQuickWidget::mousePressEvent(event);
		//event->setAccepted(false);
	}
	
	void QmlView::mouseReleaseEvent(QMouseEvent* event){
		QQuickWidget::mouseReleaseEvent(event);
		//event->setAccepted(false);
	}


	QmlView::QmlView(QWidget* parent) : QQuickWidget(parent){
		this->setSource(QUrl::fromLocalFile("../assert/qml/mapStatic.qml"));
		this->setResizeMode(QQuickWidget::SizeRootObjectToView);
		this->setMouseTracking(false);
		//this->setMinimumSize(700, 480);

		map = this->rootObject();
		
		if(map){
			map = map->findChild<QQuickItem*>(tr("mapOSM"));
			qDebug() << "checked";
			if(map){
				qDebug() << "map fully loaded";
			}
			
			/*this->addPoint(QPointF(-74.005253999999994, 40.729084), 1);
			this->changeDrawMode(ViewDrawMode::QuadtreeDepth);
			*/
		}
	}

	void QmlView::setBounds(const double& minXRes, const double& minYRes, const double& maxXRes, const double& maxYRes){
		QMetaObject::invokeMethod(map, "setBounds", Q_ARG(QVariant, minXRes), Q_ARG(QVariant, maxXRes), Q_ARG(QVariant, minYRes), Q_ARG(QVariant, maxYRes));
	}

	void QmlView::pan(const int& dx, const int& dy){
		QMetaObject::invokeMethod(map, "pan", Q_ARG(QVariant, (int) dx), Q_ARG(QVariant, (int) dy));
	}

	void QmlView::setZoom(const double& zoom){
		QMetaObject::invokeMethod(map, "setZoom", Q_ARG(QVariant, (double) zoom));
	}

	double QmlView::getZoom(){
		QVariant returnedValue;

		QMetaObject::invokeMethod(map, "getZoom", Q_RETURN_ARG(QVariant, returnedValue));

		return returnedValue.toDouble();
	}

	void QmlView::centerOn(const double& lon, const double& lat){
		QMetaObject::invokeMethod(map, "centerOn", Q_ARG(QVariant, (double) lon), Q_ARG(QVariant, (double) lat));
	}

	void QmlView::addPoint(const double& lon, const double& lat){
		QMetaObject::invokeMethod(map, "addPoint", Q_ARG(QVariant, (double) lon), Q_ARG(QVariant, (double) lat));
	}

	void QmlView::addRect(const double& topLeftLon, const double& topLeftLat, const double& bottomRightLon, const double& bottomRightLat){
		QMetaObject::invokeMethod(map, "addRect", Q_ARG(QVariant, (double) topLeftLon), Q_ARG(QVariant, (double) topLeftLat),  Q_ARG(QVariant, (double) bottomRightLon), Q_ARG(QVariant, (double) bottomRightLat));
	}

	QRectF QmlView::getVisibleRegion(){
		
		QVariant returnedValue;

		QMetaObject::invokeMethod(map, "getVisibleRegion", Q_RETURN_ARG(QVariant, returnedValue));

		if(returnedValue.isNull()) return QRectF();


		QString converted = returnedValue.toString();

		QJsonObject object = QJsonDocument::fromJson(converted.toUtf8()).object();

		//qDebug() << object;

		QPointF topLeft(object["topLeftLon"].toDouble(), object["topLeftLat"].toDouble());
		//qDebug() << object["topLeftLon"].toDouble();
		//qDebug() << object["topLeftLat"].toDouble();
		QPointF bottomRight(object["bottomRightLon"].toDouble(), object["bottomRightLat"].toDouble());
		//qDebug() << object["bottomRightLon"].toDouble();
		//qDebug() << object["bottomRightLat"].toDouble();

		return QRectF(topLeft, bottomRight);
	}
} // namespace qsbd
