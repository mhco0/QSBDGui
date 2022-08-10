#include "qmlview.h"

namespace qsbd {

	QmlView::QmlView(QWidget* parent) : QQuickWidget(parent){
		this->setSource(QUrl::fromLocalFile("../assert/qml/map.qml"));
		this->setResizeMode(QQuickWidget::SizeRootObjectToView);
		this->setMinimumSize(700, 480);
	}

} // namespace qsbd
