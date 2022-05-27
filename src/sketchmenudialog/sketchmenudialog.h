/**
 * @file sketchmenudialog.h
 * @brief QSBD SketchMenuDialog class
 * @author Marcos H C Oliveira <mhco@cin.ufpe.br>
 * @version 1.0
 *
 */


#ifndef SKETCH_MENU_DIALOG_H
#define SKETCH_MENU_DIALOG_H
#include <QDialog>
#include <QBoxLayout>
//#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QString>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QDebug>
#include <QCheckBox>


class SketchMenuDialog : public QDialog {
    Q_OBJECT
    private:

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

    QHBoxLayout* resolutionContainer;
	QVBoxLayout* valueResolutionContainer;
	QHBoxLayout* minResolutionContainer;
	QHBoxLayout* maxResolutionContainer;
	QLabel* resolutionLabel;
	QDoubleSpinBox* minXResolution;
	QDoubleSpinBox* minYResolution;
	QDoubleSpinBox* xResolution;
	QDoubleSpinBox* yResolution;

    QHBoxLayout* depthContainer;
	QLabel* depthLabel;
	QSpinBox* depthBox;
	QCheckBox* leafsOption;

	QPushButton* constructButton;

    void setupUi();

    public:
    SketchMenuDialog(QWidget* parent = nullptr);

    /**
	* @brief The Destructor for the main window
	*/
	~SketchMenuDialog();

	/**
	* @brief The copy constructor is deleted
	*/
	SketchMenuDialog(SketchMenuDialog& other) = delete;

	/**
	* @brief The assigment operator is deleted
	*/
	SketchMenuDialog& operator=(SketchMenuDialog& rhs) = delete;

    /**
	 * @brief Makes the sketch container visible based on the configuration from the sketch's menu
	 * @param visible The visible option
	 * @param addUniverse A boolean saying if we need to add a universe config or not
	*/
	void setSketchConfigUiVisible(const bool& visible, const bool& addUniverse);

    signals:

    void constructQQ(const double& minXRes, const double& minYRes, const double& xRes, const double& yRes, const int& depth, const QString& sketch, const bool& leafsOpt, const double& sketchErr, const int& sketchUni);
};
#endif