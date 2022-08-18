/**
 * @file qmlview.h
 * @brief QSBD View class
 * @author Marcos H C Oliveira <mhco@cin.ufpe.br>
 * @version 1.0
 *
 */

#ifndef QSBD_QMLVIEW_H
#define QSBD_QMLVIEW_H
#include <QtDebug>
#include <QQuickWidget>
#include <QQuickItem>

namespace qsbd {

    /** @class ViewDrawMode
     * @brief This is a enum class to handle the draw mode for the view aplication.
    */
    enum class ViewDrawMode {OnlyPoints = 0, QuadtreeDepth, Heatmap, KS};

    /** @class ClusterMethod
     * @brief This is a enum class to handle the clustering methods for the view aplication.
    */
    enum class ClusterMethod {KMedoids = 0, DBSCAN, KMeans};

    /** @class QmlView
    * @brief A Qt QQuickWidget that represents a view for a model in the MVC.
    */
    class QmlView : public QQuickWidget {
        Q_OBJECT
    protected:
        QQuickItem* map;
    private:

    public:

        /**
        * @brief A constructor for the view
        * @param parent The parent for this widget
        */
        explicit QmlView(QWidget* parent = nullptr);

        void changeDrawMode(const ViewDrawMode& mode);

        void addPoint(const QPointF& newPoint, const int& val);
    public slots:
    signals:
    };

} // namespace qsbd

#endif // QSBD_QMLVIEW_H
