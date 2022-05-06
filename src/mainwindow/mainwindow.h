/**
 * @file mainwindow.h
 * @brief QSBD MainWindow class
 * @author Marcos H C Oliveira <mhco@cin.ufpe.br>
 * @version 1.0
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../view/view.h"
#include "../model/model.h"
#include "../controller/controller.h"
#include "../qcustomplot/qcustomplot.h"
#include "../csvdialog/csvdialog.h"
#include <QMainWindow>
#include <QBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include <QString>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QFileDialog>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QSlider>
#include <aabb/aabb.hpp>
#include <utils/utils.h>

/** @class MainWindow
* @brief A Class to represent the main window of the program
*/
class MainWindow : public QMainWindow {
	Q_OBJECT
private:
	qsbd::View view;
	qsbd::Model model;
	qsbd::Controller controller;

	QHBoxLayout* mainContainer;
	QWidget* window;
	
	QVBoxLayout* rightContainer;
	QVBoxLayout* sketchFullContainer;
	QHBoxLayout* sketchContainer;
	QHBoxLayout* sketchParamsContainer;

	QComboBox* sketchsMenu;
	QLabel* sketchsLabel;
	QLabel* errorLabel;
	QLabel* universeLabel;
	QDoubleSpinBox* sketchError;
	QSpinBox* sketchUniverse;

	QVBoxLayout* simulationContainer;

	QVBoxLayout* feedContainer;
	QComboBox* feedingMethod;
	QHBoxLayout* fSizeContainer;
	QLabel* fSizeLabel;
	QSpinBox* fSize;
	QHBoxLayout* fMaxValueContainer;
	QLabel* fMaxValueLabel;
	QSpinBox* fMaxValue;
	QHBoxLayout* fMaxWeightContainer;
	QLabel* fMaxWeightLabel;
	QSpinBox* fMaxWeight;
	QHBoxLayout* fCitiesContainer;
	QLabel* fCitiesLabel;
	QSpinBox* fCities;
	QHBoxLayout* fMaxRadiusContainer;
	QLabel* fMaxRadiusLabel;
	QDoubleSpinBox* fMaxRadius;

	QVBoxLayout* batchContainer;
	QHBoxLayout* bTimeContainer;
	QLabel* bTimeLabel;
	QDoubleSpinBox* bTime;
	QHBoxLayout* bItemQuantContainer;
	QLabel* bItemQuantLabel;
	QSpinBox* bItemQuant;

	QPushButton* simulationButton;
	
	QHBoxLayout* depthContainer;
	QLabel* depthLabel;
	QSpinBox* depthBox;
	QCheckBox* leafsOption;

	QHBoxLayout* resolutionContainer;
	QVBoxLayout* valueResolutionContainer;
	QHBoxLayout* minResolutionContainer;
	QHBoxLayout* maxResolutionContainer;
	QLabel* resolutionLabel;
	QDoubleSpinBox* minXResolution;
	QDoubleSpinBox* minYResolution;
	QDoubleSpinBox* xResolution;
	QDoubleSpinBox* yResolution;

	QPushButton* constructButton;

	QHBoxLayout* rankQueryContainer;
	QLabel* rankQueryLabel;
	QSpinBox* valueForRankQuery;

	QVBoxLayout* drawOptionsContainer;
	QHBoxLayout* drawModesContainer;
	QLabel* drawModesLabel;
	QComboBox* drawModes;
	QSlider* depthDraw;

	QPushButton* freezeButton;
	QPushButton* loadStreamMethodButton;

	QHBoxLayout* sketchInfoContainer;
	QLabel* sketchInfo;
	QCustomPlot* customPlot;
	QCPStatisticalBox* statistical;

	bool freezed;

	/**
	* @brief Setup's the Ui on the main window
	*/
	void setupUi();


	/**
	 * @brief Makes the sketch container visible based on the configuration from the sketch's menu
	 * @param visible The visible option
	 * @param addUniverse A boolean saying if we need to add a universe config or not
	*/
	void setSketchConfigUiVisible(const bool& visible, const bool& addUniverse);

	/**
	 * @brief Hides from ui alls widgets relateds with the construction for the model
	*/
	void hideConstructUi();

	/**
	 * @brief Hides from ui alls widgets relateds with the feed for the model
	*/
	void hideFeedUi();

	/**
	 * @brief Setup's the Feeding Form by the sketch used to construct the model
	 * @param sketch A Qt string to setup the Feeding Form UI
	*/
	void setupFeedUi(const QString& sketch);

	/**
	 * @brief Configurates the Feeding Form by the stream method passed in @p method
	 * @param method A Qt string to configurate the Feeding Form UI
	*/
	void configFeedUi(const QString& method);

	/**
	 * @brief Starts Up Simulation
	*/
	void startUpSimulation();
public:

	/**
	* @brief The Constructor for the main window
	* @param parent The parent for this class
	*/
	MainWindow(QWidget *parent = nullptr);

	/**
	* @brief The Destructor for the main window
	*/
	~MainWindow();

	/**
	* @brief The copy constructor is deleted
	*/
	MainWindow(MainWindow& other) = delete;

	/**
	* @brief The assigment operator is deleted
	*/
	MainWindow& operator=(MainWindow& rhs) = delete;

};
#endif // MAINWINDOW_H
