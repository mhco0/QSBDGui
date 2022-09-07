#include "csvdialog.h"

void CsvDialog::setupUi(){

    lonContainer = new QHBoxLayout();
    lonLabel = new QLabel("Set the longitude collumn");
    //lonEdit = new QLineEdit();
    lonBox = new QComboBox();
    
    lonContainer->addWidget(lonLabel);
    //lonContainer->addWidget(lonEdit);
    lonContainer->addWidget(lonBox);

    latContainer = new QHBoxLayout();
    latLabel = new QLabel("Set the latitude collumn");
    //latEdit = new QLineEdit();
    latBox = new QComboBox();
    
    latContainer->addWidget(latLabel);
    //latContainer->addWidget(latEdit);
    latContainer->addWidget(latBox);

    indexContainer = new QHBoxLayout();
    indexLabel = new QLabel("Set the index collumn");
    //indexEdit = new QLineEdit();
    indexBox = new QComboBox();

    indexContainer->addWidget(indexLabel);
    //indexContainer->addWidget(indexEdit);
    indexContainer->addWidget(indexBox);


    indexOptionsContainer = new QHBoxLayout();
    indexTypeLabel = new QLabel("Index type is double ?");
    indexType = new QCheckBox();
    
    minValueLabel = new QLabel("Min value:");
    minValueLabel->setVisible(false);
    minValue = new QSpinBox();
    minValue->setVisible(false);
    minValue->setRange(-1000, 1000); 

    maxValueLabel = new QLabel("Max value:");
    maxValueLabel->setVisible(false);
    maxValue = new QSpinBox();
    maxValue->setVisible(false);
    maxValue->setRange(-1000, 1000); 
    
    depthLabel = new QLabel("Discretization Depth:");
    depthLabel->setVisible(false);
    depth = new QSpinBox();
    depth->setVisible(false);

    indexOptionsContainer->addWidget(indexTypeLabel);
    indexOptionsContainer->addWidget(indexType);
    indexOptionsContainer->addWidget(minValueLabel);
    indexOptionsContainer->addWidget(minValue);
    indexOptionsContainer->addWidget(maxValueLabel);
    indexOptionsContainer->addWidget(maxValue);
    indexOptionsContainer->addWidget(depthLabel);
    indexOptionsContainer->addWidget(depth);

    confirmButton = new QPushButton("Confirm");

    centralContainer = new QVBoxLayout();
    centralContainer->addLayout(lonContainer);
    centralContainer->addLayout(latContainer);
    centralContainer->addLayout(indexContainer);
    centralContainer->addLayout(indexOptionsContainer);
    centralContainer->addWidget(confirmButton);

    setLayout(centralContainer);
}

CsvDialog::CsvDialog(QWidget* parent): QDialog(parent) {
    this->setupUi();

    QObject::connect(indexType, &QCheckBox::stateChanged, this, [&](){
        minValueLabel->setVisible(indexType->isChecked());
        minValue->setVisible(indexType->isChecked());
        maxValueLabel->setVisible(indexType->isChecked());
        maxValue->setVisible(indexType->isChecked());
        depthLabel->setVisible(indexType->isChecked());
        depth->setVisible(indexType->isChecked());
    });

    QObject::connect(confirmButton, &QAbstractButton::pressed, this, [&](){
        qDebug() << "ok pressed";
        //qDebug() << lonEdit->text();
        //qDebug() << latEdit->text();
        //qDebug() << indexEdit->text();
        qDebug() << lonBox->currentText();
        qDebug() << latBox->currentText();
        qDebug() << indexBox->currentText();

        if(indexType->isChecked()){
            double minDomainValue = minValue->value();
            double maxDomainValue = maxValue->value();
            int domainDepth = depth->value();

            emit collumnsSelectedWithMap(lonBox->currentText(), latBox->currentText(), indexBox->currentText(), minDomainValue, maxDomainValue, domainDepth);
            this->done(QDialog::Accepted);
            return;
        } /// save here the function to discretize and save all double to int values than pass it to the feeding function


        emit collumnsSelected(lonBox->currentText(), latBox->currentText(), indexBox->currentText());

        this->done(QDialog::Accepted);
    }); 
}

CsvDialog::~CsvDialog(){
}

void CsvDialog::setHeaders(const QString& filename){
    std::ifstream file(filename.toStdString());
    std::string header;
    std::size_t found = std::string::npos;
    std::size_t start_pos = 0;
    std::vector<std::string> collumns;

    std::getline(file, header);

    qDebug() << header.c_str();

    do{
        found = header.find(",", start_pos);
        if (found == std::string::npos) break;
        std::string collumn = header.substr(start_pos, found - start_pos);
        if (collumn.size() > 0) collumns.emplace_back(collumn);
        start_pos = (found + 1);
    }while(true);

    for(auto& it : collumns){
        lonBox->addItem(tr(it.c_str()));
        latBox->addItem(tr(it.c_str()));
        indexBox->addItem(tr(it.c_str()));
    }
}
