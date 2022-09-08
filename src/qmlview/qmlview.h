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
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

namespace qsbd {

    /** @class QmlView
    * @brief A Qt QQuickWidget that represents a quick widget for qt maps plugins
    */
    class QmlView : public QQuickWidget {
        Q_OBJECT
    protected:
        QQuickItem* map;
    private:

        /**
        * @brief A method to handle a mouse movement event
        * @param event The mouse event 
        */
        virtual void mouseMoveEvent(QMouseEvent* event) override;

        /**
        * @brief A method to handle a mouse press event
        * @param event The mouse event 
        */
        virtual void mousePressEvent(QMouseEvent* event) override;

        /**
        * @brief A method to handle a mouse release event
        * @param event The mouse event 
        */
        virtual void mouseReleaseEvent(QMouseEvent* event) override;

    public:

        /**
        * @brief A constructor for the view
        * @param parent The parent for this widget
        */
        explicit QmlView(QWidget* parent = nullptr);

        /**
        * @brief A setter for the virtual resolution that this view will represent 
        * @param minXRes The virtual min x resolution
        * @param minYRes The virtual min y resolution
        * @param maxXRes The virtual max x resolution
        * @param maxYRes The virtual max y resolution
        */
        void setBounds(const double& minXRes, const double& minYRes, const double& maxXRes, const double& maxYRes);

        void pan(const int& dx, const int& dy);

        void setZoom(const double& zoom);

        double getZoom();

        void centerOn(const double& lon, const double& lat);

        void addPoint(const double& lon, const double& lat);

        void addRect(const double& topLeftLon, const double& topLeftLat, const double& bottomRightLon, const double& bottomRightLat);

        QRectF getVisibleRegion();
    public slots:
    signals:
    };

} // namespace qsbd

#endif // QSBD_QMLVIEW_H
