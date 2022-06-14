#include "controller.h"

namespace qsbd{
	int Controller::convertSToMs(const double& seconds){
		return (int) (seconds * 1000);
	}

	Controller::Controller(QObject* parent): QObject(parent){
		myView = nullptr;
		myModel = nullptr;
		feedTimer = new QTimer(this);
		feedTimer->setSingleShot(false);
		feedInterval = 1;
		batchWindowSize = 1;
		usingDataWithWeight = false;
		currentWindow = 0;
	}

	Controller::Controller(View& viewTrack, Model& modelTrack, QObject* parent) : QObject(parent), myView(&viewTrack), myModel(&modelTrack){
		feedTimer = new QTimer(this);
		feedTimer->setSingleShot(false);
		feedInterval = 1;
		batchWindowSize = 1;
		usingDataWithWeight = false;
		currentWindow = 0;
	}

	void Controller::feedStreamInRegion(int vector_size, double minx, double miny, double maxx, double maxy, int min_v, int max_v){
		currentWindow = 0;
		usingDataWithWeight = false;
		dataSource = stream_maker::random_stream_in_region(vector_size, minx, miny, maxx, maxy, min_v, max_v);

		feedTimer->disconnect();

		QObject::connect(feedTimer, &QTimer::timeout, this, [&](){
			for(int i = currentWindow, j = 0; i < dataSource.size() and j < batchWindowSize; i++, j++){
				myView->addPoint(QPointF(dataSource[i].second.first, dataSource[i].second.second), dataSource[i].first);
				myModel->onUpdate(point<double>(dataSource[i].second.first, dataSource[i].second.second), dataSource[i].first);
				currentWindow++;
			}
		});

	}
	
	void Controller::feedStreamInRegionWithWeight(int vector_size, double minx, double miny, double maxx, double maxy, int min_v, int max_v, int min_w, int max_w){
		currentWindow = 0;
		usingDataWithWeight = true;
		dataSourceWithWeight = stream_maker::random_stream_in_region_with_weight(vector_size, minx, miny, maxx, maxy, min_v, max_v, min_w, max_w);

		feedTimer->disconnect();

		QObject::connect(feedTimer, &QTimer::timeout, this, [&](){
			for(int i = currentWindow, j = 0; i < dataSourceWithWeight.size() and j < batchWindowSize; i++, j++){
				myView->addPoint(QPointF(dataSourceWithWeight[i].second.first, dataSourceWithWeight[i].second.second), dataSourceWithWeight[i].first.first);
				myModel->onUpdate(point<double>(dataSourceWithWeight[i].second.first, dataSourceWithWeight[i].second.second), dataSourceWithWeight[i].first.first, dataSourceWithWeight[i].first.second);
				currentWindow++;
			}
		});
	}
	
	void Controller::feedRandomStreamCity(int vector_size, double minx, double miny, double maxx, double maxy, int min_v, int max_v, int cities, double max_radius){
		currentWindow = 0;
		usingDataWithWeight = false;
		dataSource = stream_maker::random_stream_city(vector_size, minx, miny, maxx, maxy, min_v, max_v, cities, max_radius);

		feedTimer->disconnect();

		QObject::connect(feedTimer, &QTimer::timeout, this, [&](){
			for(int i = currentWindow, j = 0; i < dataSource.size() and j < batchWindowSize; i++, j++){
				myView->addPoint(QPointF(dataSource[i].second.first, dataSource[i].second.second), dataSource[i].first);
				myModel->onUpdate(point<double>(dataSource[i].second.first, dataSource[i].second.second), dataSource[i].first);
				currentWindow++;
			}
		});
	}
	
	void Controller::feedRandomStreamCityWithWeight(int vector_size, double minx, double miny, double maxx, double maxy, int min_v, int max_v, int min_w, int max_w, int cities, double max_radius){
		currentWindow = 0;
		usingDataWithWeight = true;
		dataSourceWithWeight = stream_maker::random_stream_city_with_weight(vector_size, minx, miny, maxx, maxy, min_v, max_v, min_w, max_w, cities, max_radius);

		feedTimer->disconnect();

		QObject::connect(feedTimer, &QTimer::timeout, this, [&](){
			for(int i = currentWindow, j = 0; i < dataSourceWithWeight.size() and j < batchWindowSize; i++, j++){
				myView->addPoint(QPointF(dataSourceWithWeight[i].second.first, dataSourceWithWeight[i].second.second), dataSourceWithWeight[i].first.first);
				myModel->onUpdate(point<double>(dataSourceWithWeight[i].second.first, dataSourceWithWeight[i].second.second), dataSourceWithWeight[i].first.first, dataSourceWithWeight[i].first.second);
				currentWindow++;
			}
		});
	}

	void Controller::feedStreamByCsv(void){
		currentWindow = 0;
		usingDataWithWeight = false;

		feedTimer->disconnect();
		
		QObject::connect(feedTimer, &QTimer::timeout, this, [&](){
			for(int i = currentWindow, j = 0; i < dataSource.size() and j < batchWindowSize; i++, j++){
				myView->addPoint(QPointF(dataSource[i].second.first, dataSource[i].second.second), dataSource[i].first);
				myModel->onUpdate(point<double>(dataSource[i].second.first, dataSource[i].second.second), dataSource[i].first);
				currentWindow++;
			}
		});
	}

	void Controller::loadStreamByCsv(const QString& filename, const QString& lon_col, const QString& lat_col, const QString& value_col){
		io::CSVReader<3, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::throw_on_overflow, io::empty_line_comment> in(filename.toUtf8().constData());
		in.read_header(io::ignore_extra_column, value_col.toUtf8().constData(), lon_col.toUtf8().constData(), lat_col.toUtf8().constData());
		double lon, lat;
		int value;
		
		while(in.read_row(value, lon, lat)){
			//cout << value << " " << lon << " " << lat << endl;
			dataSource.push_back({value, {lon, lat}});
		}

		feedStreamByCsv();
	}

	void Controller::loadFileAndFeed(const QString& path){
		using json = nlohmann::json;

		std::string stdPath = path.toUtf8().constData();
		std::ifstream config_file(stdPath);

		if(config_file.is_open()) {
    		json config = json::parse(config_file);

			std::string method = config["method"].get<std::string>();
			json temp;

			if(method == "random_stream_in_region"){
				int vector_size = config["args"]["vector_size"].get<int>();
				double minx = config["args"]["minx"].get<double>();
				double miny = config["args"]["miny"].get<double>();
				double maxx = config["args"]["maxx"].get<double>();
				double maxy = config["args"]["maxy"].get<double>();
				int min_v = config["args"]["min_v"].get<int>();
				int max_v = config["args"]["max_v"].get<int>();

				feedStreamInRegion(vector_size, minx, miny, maxx, maxy, min_v, max_v);		
			}else if(method == "random_stream_in_region_with_weight"){
				int vector_size = config["args"]["vector_size"].get<int>();
				double minx = config["args"]["minx"].get<double>();
				double miny = config["args"]["miny"].get<double>();
				double maxx = config["args"]["maxx"].get<double>();
				double maxy = config["args"]["maxy"].get<double>();
				int min_v = config["args"]["min_v"].get<int>();
				int max_v = config["args"]["max_v"].get<int>();
				int min_w = config["args"]["min_w"].get<int>();
				int max_w = config["args"]["max_w"].get<int>();

				feedStreamInRegionWithWeight(vector_size, minx, miny, maxx, maxy, min_v, max_v, min_w, max_w);
			}else if(method == "random_stream_city"){
				int vector_size = config["args"]["vector_size"].get<int>();
				double minx = config["args"]["minx"].get<double>();
				double miny = config["args"]["miny"].get<double>();
				double maxx = config["args"]["maxx"].get<double>();
				double maxy = config["args"]["maxy"].get<double>();
				int min_v = config["args"]["min_v"].get<int>();
				int max_v = config["args"]["max_v"].get<int>();
				int cities = config["args"]["cities"].get<int>();
				double max_radius = config["args"]["max_radius"].get<double>();

				feedRandomStreamCity(vector_size, minx, miny, maxx, maxy, min_v, max_v, cities, max_radius);
			}else if(method == "random_stream_city_with_weight"){
				int vector_size = config["args"]["vector_size"].get<int>();
				double minx = config["args"]["minx"].get<double>();
				double miny = config["args"]["miny"].get<double>();
				double maxx = config["args"]["maxx"].get<double>();
				double maxy = config["args"]["maxy"].get<double>();
				int min_v = config["args"]["min_v"].get<int>();
				int max_v = config["args"]["max_v"].get<int>();
				int min_w = config["args"]["min_w"].get<int>();
				int max_w = config["args"]["max_w"].get<int>();
				int cities = config["args"]["cities"].get<int>();
				double max_radius = config["args"]["max_radius"].get<double>();

				feedRandomStreamCityWithWeight(vector_size, minx, miny, maxx, maxy, min_v, max_v, min_w, max_w, cities, max_radius);
			}else{
				std::cout << "Method not supported" << std::endl; 
			}

			config_file.close();
		}else{
			std::cout << "Couldn't open the file" << std::endl;
		}
	}

	void Controller::setTimeInterval(const double& seconds){
		feedInterval = convertSToMs(seconds);
	}
	
	void Controller::setWindowSize(const int& windowSize){
		batchWindowSize = windowSize;
	}

	void Controller::startSimulation(){
		feedTimer->start(feedInterval);
	}

	void Controller::freeze(){
		feedTimer->stop();
	}
}
