/**
 * @file view.h
 * @brief QSBD View class
 * @author Marcos H C Oliveira <mhco@cin.ufpe.br>
 * @version 1.0
 *
 */

#ifndef QSBD_VIEW_H
#define QSBD_VIEW_H

#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QRect>
#include <QVector>
#include <QtGlobal>
#include <QPointF>
#include <QSize>
#include <QtDebug>
#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QtMath>
#include <QGraphicsSvgItem>
#include <aabb/aabb.hpp>
#include <map>
#include <string>
#include "../kmedoids/kmedoids.hpp"

namespace qsbd {

    /** @class ViewDrawMode
     * @brief This is a enum class to handle the draw mode for the view aplication.
    */
    enum class ViewDrawMode {OnlyPoints, QuadtreeDepth, Heatmap, KS};

    /** @class QueryGraphicsItem
    * @brief A Qt QGraphicsItem that represents a query in the view
    */
    class QueryGraphicsItem : public QObject, public QGraphicsRectItem {
        Q_OBJECT
    protected:
        /**
        * @brief A method to handle a mouse release event
        * @param event The mouse event 
        */
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    public:
        int id;
        QueryGraphicsItem(int myId);
    signals:
        void dropEnd(QueryGraphicsItem* it);
    };

    /** @class View
    * @brief A Qt QGraphicsView that represents a view for a model in the MVC.
    */
    class View : public QGraphicsView {
        Q_OBJECT
    protected:

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

        /**
        * @brief A method to handle a mouse wheel event
        * @param event The mouse wheel event 
        */
        virtual void wheelEvent(QWheelEvent* event) override;

        /**
         * @brief Updates the view based on the Draw mode.
        */
        void updateBasedOnDrawMode();
    private:
        QGraphicsScene* scene;
        std::map<std::string, QGraphicsRectItem*> boxInPath;
        std::map<std::string, std::pair<QGraphicsRectItem*, uint>> lastDepthBoxesPath;
        //std::vector<std::pair<QGraphicsRectItem*, QGraphicsRectItem*>> ksRegions;
        std::vector<QGraphicsRectItem*> cdfsRegions;
        std::vector<int> centroids;
        int depth;
        int depthView;
        int kCluster;
        int kSteps;
        int minValueSeen;
        int maxValueSeen;
        ViewDrawMode drawMode;
        int queryCurId;
        bool dragging;
        double maxXResolution;
        double maxYResolution;
        double minXdomain;
        double maxXdomain;
        double minYdomain;
        double maxYdomain;
        QTransform originalTransform;
        QPoint clickStart;
        QPoint curMousePos;
        QGraphicsRectItem* queryRegion;
        QVector<QGraphicsEllipseItem*> points;
        QVector<QGraphicsRectItem*> queries;
        QGraphicsSvgItem* svgBackground;
        Qt::GlobalColor queriesColors[5];

        /**
		 * @brief A private quantile quadtree function copy that changes the bounds of the @p cur_box to the bounds of it's childs in the position @p direction
		 * This method copys the quantile quadtree behaviar but changes it to match with the view coordenate system
         * 
		 * @param cur_box The AABB to have the bounds changed
		 * @param direction A short value in range [0 .. 3] 
		 * 
		 * @warning 
		 * The @p cur_box will be changed.
		*/
		void change_box(aabb<double>& cur_box, short direction);

        /**
		 * @brief A private quantile quadtree copy function that changes the bounds of the @p cur_box to the bounds of it's childs in the position @p direction
		 * This method copys the quantile quadtree behaviar but changes it to match with the view coordenate system
         * 
         * @param cur_box The AABB to have the bounds changed
		 * @param direction A short value in range [0 .. 3] 
		 * 
		 * @warning 
		 * The @p cur_box will be changed.
		*/
        short direction(const aabb<double>& box, const QPointF& pos);

        /**
		 * @brief A private quantile quadtree copy function, that checks if some aabb @p regions is a box 1 x 1.
		 * @param region A AABB to be tested
		 * @return true if it's is a box 1x1, false otherwise.
		*/
		bool unit_box(const aabb<double>& region);

        /**
         * @brief A private function that maps some point @p lon and @p lat coordenates as lon / lat coordenates and returns the view points coordenates.
         * @param lon The longitude parameter for the point.
         * @param lat The latitude parameter for the point.
         * @return A pair with the view points for the coordenate.
         * @warning This function only works if you use @sa View::setDomain first.
        */
        std::pair<double, double> mapLonLatToScreen(double lon, double lat);

        /**
         * @brief A private function that maps some point @p point coordenates as scene view coordenates and returns the lon / lat coordenates.
         * @param point The point with the coordenate in the scene to be mapped.
         * @return A pair with the lon / lat coordenates (lon -> pair.first , lat -> pair.second).
         * @warning This function only works if you use @sa View::setDomain first.
        */
        std::pair<double, double> mapScreenToLonLat(const QPointF& point);


        /**
         * @brief A private function that returns all pairs in some resolution
         * @param depth the depth to be calculed
         * @return A vector with all pairs in the @p depth
        */
        std::vector<std::pair<QGraphicsRectItem*, QGraphicsRectItem*>> allPairsInResolution(const int& depth);

        /**
         * @brief A private function that returns all regions in some resolution
         * @param depth the depth to be calculed
         * @return A vector with  in the @p depth
        */
        std::vector<QGraphicsRectItem*> regionsInResolution(const int& depth);


        /**
         * @brief A private function to get @p n or less values from minValueSeen to maxValueSeen  
         * @param n The number of values asked.
         * @return A vector with n or less points in the between of the two values.
        */
        std::vector<int> getKSLERP(const int& n);
    public:

        /**
        * @brief A constructor for the view
        * @param scene The scene where the view belongs
        * @param parent The parent for this widget
        */
        explicit View(QGraphicsScene* scene, QWidget* parent = nullptr);

        /**
        * @brief A constructor for the view
        * @param parent The parent for this widget
        */
        explicit View(QWidget* parent = nullptr);

        
    public slots:

        /**
        * @brief A setter for the virtual resolution that this view will represent 
        * @param minXRes The virtual min x resolution
        * @param minYRes The virtual min y resolution
        * @param maxXRes The virtual max x resolution
        * @param maxYRes The virtual max y resolution
        */
        void setDomain(const double& minXRes, const double& minYRes, const double& maxXRes, const double& maxYRes);

        /**
         * @brief A setter to set how the view will draw the data
         * @param option A @sa ViewDrawMode to set the draw mode for the view. 
        */
        void setDrawingMode(const ViewDrawMode& option);

        /**
         * @brief A setter for the virtual max depth on the quadtree model
         * @param maxDepth The depth
        */
        void setDepth(const int& maxDepth);

        /**
         * @brief A setter for the virtual max depth view on the quadtree model
         * @param dpView The depth view
        */
        void setDepthView(const int& dpView);

        /**
         * @brief A setter for the k value in the K-Medoids cluster
         * @param kc The K value
         * @warning The values should be between 1 and 10
        */
        void setKCluster(const int& kc);

        /**
        * @brief A function to add a new point on the plot
        * @param newPoint The new point 
        */
        void addPoint(const QPointF& newPoint, const int& val);

        /**
         * @brief This function is called when the view receves the cdfs for each region queried
        */
        void onCdfsReady(const std::vector<std::vector<double>>& cdfs);

    signals:

        /**
        * @brief A Qt signal, this signal is triggered when we have some movent on the view region
        * @param coord The point in the view where the movement occured
        */
        void mouseMovement(const QPoint& coord);
        
        /**
        * @brief A Qt signal, this signal is triggered when the mouse is pressed on the view
        */
        void mousePressed();

        /**
        * @brief A Qt signal, this signal is triggered when the mouse is released on the view
        */
        void mouseRelease();

        /**
        * @brief A Qt signal, this signal is triggered when we have some movent on the wigdet region
        * @param region The region queried in the view
        */
        void queryRequest(const QRectF& region);

        /**
        * @brief A Qt signal, this signal is triggered when we have some movent on the wigdet region
        * @param region The region queried in the view
        * @param queryId The query region Id
        */
        void quantileRequest(const QRectF& region, int queryId);

        /**
        * @brief A Qt signal, this signal is triggered when we have some request for the cdfs in @p regions
        * @param regions The regions queried in the view
        * @param values The values queried in the view
        */
        void cdfsRequest(const std::vector<QRectF>& regions, const std::vector<int>& values);
    };

    
    /** @class Canvas
    * @brief A Qt widget that represents a canvas in a read-only mode
    */
    /*
    class Canvas : public QWidget {
        Q_OBJECT
    protected:
        /**
        * @brief A method to handle a mouse movement event
        * @param event The mouse event 
        *//*
        virtual void mouseMoveEvent(QMouseEvent * event) override;

        /**
        * @brief A method to handle a mouse press event
        * @param event The mouse event 
        *//*
        virtual void mousePressEvent(QMouseEvent * event) override;

        /**
        * @brief A method to handle a mouse release event
        * @param event The mouse event 
        *//*
        virtual void mouseReleaseEvent(QMouseEvent * event) override;

        /**
        * @brief A method to handle a mouse wheel event
        * @param event The mouse wheel event 
        *//*
        virtual void wheelEvent(QWheelEvent * event) override;

        /**
		 * @brief A private quantile quadtree function copy that changes the bounds of the @p cur_box to the bounds of it's childs in the position @p direction
		 * This method copys the quantile quadtree behaviar but changes it to match with the canvas coordenate system
         * 
		 * @param cur_box The AABB to have the bounds changed
		 * @param direction A short value in range [0 .. 3] 
		 * 
		 * @warning 
		 * The @p cur_box will be changed.
		*//*
		void change_box(QRect& cur_box, short direction);

        /**
		 * @brief A private quantile quadtree copy function that changes the bounds of the @p cur_box to the bounds of it's childs in the position @p direction
		 * This method copys the quantile quadtree behaviar but changes it to match with the canvas coordenate system
         * 
         * @param cur_box The AABB to have the bounds changed
		 * @param direction A short value in range [0 .. 3] 
		 * 
		 * @warning 
		 * The @p cur_box will be changed.
		*//*
        short direction(const QRect& box, const QPointF& pos);

        /**
		 * @brief A private quantile quadtree copy function, that checks if some aabb @p regions is a box 1 x 1.
		 * @param region A AABB to be tested
		 * @return true if it's is a box 1x1, false otherwise.
		*//*
		bool unit_box(const QRect& region);

        /**
         * @brief Converts the queried canvas resolution to the actual query resolution
         * @param region The region to be queried in the Canvas
        *//*
        QRect convertRegion(const QRect& region);

        /**
         * @brief Return some color from the valiable boxGradient[9], based on the frequency of elements in a given region
         * @param points The number of points in a given region;
         * @return The color for this number of points
        *//*
        QColor colorBasedOnFrequency(const uint& points);
    private:
        QBrush myBrush;
        QPen myPen;
        QColor boxGradient[6];
        std::map<std::string, std::pair<QRect, uint>> boxInPath;
        QVector<QPointF> data;
        QRect query;
        QPoint clickStart;
        QPoint curMousePos;
        QPoint zoomPoint;
        qreal zoomScale;

        bool applyZoom;
        bool dragging;
        bool drawBounds;

        int depth;
        
        double maxXResolution;
        double maxYResolution;
    public:

        /**
        * @brief A constructor for the canvas
        * @param parent The parent for this widget
        *//*
        explicit Canvas(QWidget *parent = nullptr);

        /**
        * @brief A method to handle a paint event
        * @param event The paint event 
        *//*
        virtual void paintEvent(QPaintEvent* event) override;

    public slots:

        /**
        * @brief A setter for the virtual resolution that this canvas will represent 
        * @param xRest The virtual x resolution
        * @param yRest The virtual y resolution
        *//*
        void setResolution(const double& xRes, const double& yRes);

        /**
         * @brief A setter to see if the canvas will draw the quadtree bounds or not
         * @param option A boolean to set if we draw the bounds for the quadtree. 
        *//*
        void setBoundsDrawing(const bool& option);

        /**
         * @brief A setter for the virtual max depth on the quadtree model
         * @param maxDepth The depth
        *//*
        void setDepth(const int& maxDepth);
        
        /**
        * @brief A function to add a new point on the plot
        * @param newPoint The new point 
        *//*
        void addPoint(const QPointF& newPoint);
        //void onClickStart();
        //void onClickStop();

    signals:
        /**
        * @brief A Qt signal, this signal is triggered when we have some movent on the canvas region
        * @param coord The point in the canvas where the movement occured
        *//*
        void mouseMovement(const QPoint& coord);
        
        /**
        * @brief A Qt signal, this signal is triggered when the mouse is pressed on the canvas
        *//*
        void mousePressed();

        /**
        * @brief A Qt signal, this signal is triggered when the mouse is released on the canvas
        *//*
        void mouseRelease();

        /**
        * @brief A Qt signal, this signal is triggered when we have some movent on the wigdet region
        * @param region The region queried in the canvas
        *//*
        void queryRequest(const QRect& region);

    };*/

} // namespace qsbd

#endif // QSBD_VIEW_H
