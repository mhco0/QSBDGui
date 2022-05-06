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

    confirmButton = new QPushButton("Confirm");

    centralContainer = new QVBoxLayout();
    centralContainer->addLayout(lonContainer);
    centralContainer->addLayout(latContainer);
    centralContainer->addLayout(indexContainer);
    centralContainer->addWidget(confirmButton);

    setLayout(centralContainer);
}

CsvDialog::CsvDialog(QWidget* parent): QDialog(parent) {
    this->setupUi();

    QObject::connect(confirmButton, &QAbstractButton::pressed, this, [&](){
        qDebug() << "ok pressed";
        //qDebug() << lonEdit->text();
        //qDebug() << latEdit->text();
        //qDebug() << indexEdit->text();
        qDebug() << lonBox->currentText();
        qDebug() << latBox->currentText();
        qDebug() << indexBox->currentText();

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
