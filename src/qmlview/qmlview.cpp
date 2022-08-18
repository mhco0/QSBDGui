#include "qmlview.h"

namespace qsbd {

	QmlView::QmlView(QWidget* parent) : QQuickWidget(parent){
		this->setSource(QUrl::fromLocalFile("../assert/qml/map.qml"));
		this->setResizeMode(QQuickWidget::SizeRootObjectToView);
		this->setMinimumSize(700, 480);
		map = this->rootObject();
		if(map){
			map = map->findChild<QQuickItem*>(tr("mapOsm"));
			qDebug() << "checked";
			if(map){
				qDebug() << "map fully loaded";
			}
			

			this->addPoint(QPointF(-74.005253999999994, 40.729084), 1);
			this->changeDrawMode(ViewDrawMode::QuadtreeDepth);
		}
	}

	void QmlView::addPoint(const QPointF& newPoint, const int& val){
		QMetaObject::invokeMethod(map, "addPoint", Q_ARG(QVariant, newPoint.x()), Q_ARG(QVariant, newPoint.y()));
	}


	void QmlView::changeDrawMode(const ViewDrawMode& mode){
		QMetaObject::invokeMethod(map, "changeDrawMode", Q_ARG(QVariant, (int) mode));
	}


} // namespace qsbd
