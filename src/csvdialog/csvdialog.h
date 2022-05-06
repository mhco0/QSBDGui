/**
 * @file csvdialog.h
 * @brief QSBD CsvDialog class
 * @author Marcos H C Oliveira <mhco@cin.ufpe.br>
 * @version 1.0
 *
 */


#ifndef CSV_DIALOG_H
#define CSV_DIALOG_H
#include <QDialog>
#include <QBoxLayout>
//#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QDebug>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class CsvDialog : public QDialog {
    Q_OBJECT
    private:
    QVBoxLayout* centralContainer;
    QHBoxLayout* lonContainer;
    //QLineEdit* lonEdit;
    QComboBox* lonBox;
    QLabel* lonLabel;
    QHBoxLayout* latContainer;
    //QLineEdit* latEdit;
    QComboBox* latBox;
    QLabel* latLabel;
    QHBoxLayout* indexContainer;
    QLabel* indexLabel;
    //QLineEdit* indexEdit;
    QComboBox* indexBox;
    QPushButton* confirmButton;

    void setupUi();

    public:
    CsvDialog(QWidget* parent = nullptr);

    /**
	* @brief The Destructor for the main window
	*/
	~CsvDialog();

	/**
	* @brief The copy constructor is deleted
	*/
	CsvDialog(CsvDialog& other) = delete;

	/**
	* @brief The assigment operator is deleted
	*/
	CsvDialog& operator=(CsvDialog& rhs) = delete;

    void setHeaders(const QString& filename);

    signals:

    void collumnsSelected(const QString lonCol, const QString latCol, const QString indexCol);
};
#endif