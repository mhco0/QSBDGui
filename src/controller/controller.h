/**
 * @file controller.h
 * @brief QSBD Controller class
 * @author Marcos H C Oliveira <mhco@cin.ufpe.br>
 * @version 1.0
 */

#ifndef QSBD_CONTROLLER_H
#define QSBD_CONTROLLER_H

#include "../view/view.h"
#include "../model/model.h"
#include <string>
#include <QObject>
#include <QString>
#include <QPointF>
#include <QTimer>
#include <stream_maker/stream_maker.h>
#include <nlohmann/json.hpp>
#include <csv_parser/csv.h>

namespace qsbd {

	/** @class Controller
	 * @brief A Controller using the MVC architecture
	 * This class has the responsability of managing the inputs for both view and model
	*/
	class Controller : public QObject {
		Q_OBJECT
	private:
		std::vector<std::pair<std::pair<int, int>, std::pair<double, double>>> dataSourceWithWeight;
		std::vector<std::pair<int, std::pair<double, double>>> dataSource;
		int feedInterval;
		int batchWindowSize;
		bool usingDataWithWeight;
		int currentWindow;
		QTimer* feedTimer;
		Model* myModel;
		View* myView;

		/**
		 * @brief Converts seconds value to a milliseconds
		 * @param seconds The time in seconds;
		 * @return The same time in milliseconds
		*/
		int convertSToMs(const double& seconds);
	public:

		/**
		 * @brief Constructor for the controller
		 * @param parent The parent for this object
		*/
		explicit Controller(QObject* parent = nullptr);

		/**
		 * @brief Constructor for the controller
		 * @param viewTrack A reference for the view for this controller
		 * @param modelTrack A reference for the model for this controller
		 * @param parent The parent for this object
		*/
		explicit Controller(View& viewTrack, Model& modelTrack, QObject* parent = nullptr);

		public slots:

		/**
		 * @brief A method for updates both model and view using a uniform int stream creation
		 * @param vector_size The vector size
		 * @param minx The minimum y coordenate for the points
		 * @param miny The minimum y coordenate for the points
		 * @param maxx The maximum x coordenate for the points
		 * @param maxy The maximum y coordenate for the points
		 * @param min_v The minimum value saw in the stream
		 * @param max_v The maximum value saw in the stream 
		*/
		void feedStreamInRegion(int vector_size, double minx, double miny, double maxx, double maxy, int min_v, int max_v);
		
		/**
		 * @brief A method for updates both model and view using a uniform int stream with weights creation
		 * @param vector_size The vector size
		 * @param minx The minimum y coordenate for the points
		 * @param miny The minimum y coordenate for the points
		 * @param maxx The maximum x coordenate for the points
		 * @param maxy The maximum y coordenate for the points
		 * @param min_v The minimum value saw in the stream
		 * @param max_v The maximum value saw in the stream 
		 * @param min_w The minimum weight in the stream
		 * @param max_w The maximum weight in the stream
		*/
		void feedStreamInRegionWithWeight(int vector_size, double minx, double miny, double maxx, double maxy, int min_v, int max_v, int min_w, int max_w);
		
		/**
		 * @brief A method for updates both model and view using a city stream creation
		 * @param vector_size The vector size
		 * @param minx The minimum y coordenate for the points
		 * @param miny The minimum y coordenate for the points
		 * @param maxx The maximum x coordenate for the points
		 * @param maxy The maximum y coordenate for the points
		 * @param min_v The minimum value saw in the stream
		 * @param max_v The maximum value saw in the stream 
		 * @param cities The number of cities in the stream
		 * @param max_radius The max radius for the distribution of points in the cities
		*/
		void feedRandomStreamCity(int vector_size, double minx, double miny, double maxx, double maxy, int min_v, int max_v, int cities, double max_radius);
		
		/**
		 * @brief A method for updates both model and view using a city stream with weights creation
		 * @param vector_size The vector size
		 * @param minx The minimum y coordenate for the points
		 * @param miny The minimum y coordenate for the points
		 * @param maxx The maximum x coordenate for the points
		 * @param maxy The maximum y coordenate for the points
		 * @param min_v The minimum value saw in the stream
		 * @param max_v The maximum value saw in the stream 
		 * @param min_w The minimum weight in the stream
		 * @param max_w The maximum weight in the stream
		 * @param cities The number of cities in the stream
		 * @param max_radius The max radius for the distribution of points in the cities
		*/
		void feedRandomStreamCityWithWeight(int vector_size, double minx, double miny, double maxx, double maxy, int min_v, int max_v, int min_w, int max_w, int cities, double max_radius);
		
		/**
		 * @brief A method for updates both model and view using the stream loaded by the csv
		*/
		void feedStreamByCsv(void);
		
		/**
		 * @brief Loads a certain csv file for the @sa feedStreamByCsv method
		 * @param path The path for the file
		 * @param lon_col The collumn in the csv to extract the logitude
		 * @param lat_col The collumn in the csv to extract the latitude
		 * @param value_col The collumn in the csv to extract the value to be indexed
		*/
		void loadStreamByCsv(const QString& filename, const QString& lon_col, const QString& lat_col, const QString& value_col);
		
	
		/**
		 * @brief Loads a certain json file with some feeding method
		 * @param path The path for the file
		*/
		void loadFileAndFeed(const QString& path);

		/***
		 * @brief Sets the batch time for updates
		 * @param seconds A time in seconds for the batch update interval
		*/
		void setTimeInterval(const double& seconds);

		/***
		 * @brief Sets the window size for the batch
		 * @param windowSize The window size for the batch
		*/
		void setWindowSize(const int& windowSize);

		/**
		 * @brief Starts the simulation for both Model and View
		*/
		void startSimulation();

		/**
		 * @brief Freezes the simulation for both Model and View
		*/
		void freeze();
	};
}

#endif // CONTROLLER_H
