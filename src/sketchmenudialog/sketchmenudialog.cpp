#include "sketchmenudialog.h"

void SketchMenuDialog::setupUi(){

    sketchsMenu = new QComboBox();
    sketchsMenu->addItem(tr("undefined"));
    sketchsMenu->addItem(tr("kll"));
    sketchsMenu->addItem(tr("q_digest"));
    sketchsMenu->addItem(tr("gk"));
    sketchsMenu->addItem(tr("dcs"));

    sketchsLabel = new QLabel();
    sketchsLabel->setText("Sketch: ");

    sketchFullContainer = new QVBoxLayout();

    sketchParamsContainer = new QHBoxLayout();

    errorLabel = new QLabel();
    errorLabel->setText("Error: ");
    errorLabel->setVisible(false);

    sketchError = new QDoubleSpinBox();
    sketchError->setDecimals(3);
    sketchError->setRange(0.001, 0.999);
    sketchError->setSingleStep(0.001);
    sketchError->setValue(0.003);
    sketchError->setVisible(false);

    universeLabel = new QLabel();
    universeLabel->setText("Universe: ");
    universeLabel->setVisible(false);

    sketchUniverse = new QSpinBox();
    sketchUniverse->setRange(1, 100000);
    sketchUniverse->setValue(1024);
    sketchUniverse->setVisible(false);

    sketchParamsContainer->addWidget(errorLabel);
    sketchParamsContainer->addWidget(sketchError);
    sketchParamsContainer->addWidget(universeLabel);
    sketchParamsContainer->addWidget(sketchUniverse);

    sketchContainer = new QHBoxLayout();
    sketchContainer->addWidget(sketchsLabel);
    sketchContainer->addWidget(sketchsMenu);

    sketchFullContainer->addLayout(sketchContainer);
    sketchFullContainer->addLayout(sketchParamsContainer);

    depthLabel = new QLabel();
    depthLabel->setText("Depth: ");
    
    depthBox = new QSpinBox();
    depthBox->setRange(0, 10);
    depthBox->setValue(3);

    leafsOption = new QCheckBox("Only use leafs");

    depthContainer = new QHBoxLayout();
    depthContainer->addWidget(depthLabel);
    depthContainer->addWidget(depthBox);
    depthContainer->addWidget(leafsOption);

    resolutionLabel = new QLabel();
    resolutionLabel->setText("Resolution: ");
    resolutionLabel->setVisible(false);
    
    minXResolution = new QDoubleSpinBox();
	minYResolution = new QDoubleSpinBox();
    xResolution = new QDoubleSpinBox();
    yResolution = new QDoubleSpinBox();

    minXResolution->setPrefix("x: ");
    minYResolution->setPrefix("y: ");
    xResolution->setPrefix("x: ");
    yResolution->setPrefix("y: ");

    minXResolution->setRange(-90.0, 90.0);
    minXResolution->setValue(-74.2628);
    minXResolution->setVisible(false);
    minYResolution->setRange(-180.0, 180.0);
    minYResolution->setValue(40.4762);
    minYResolution->setVisible(false);

    xResolution->setRange(-90.0, 90.0);
    xResolution->setValue(-73.6983);
    xResolution->setVisible(false);
    yResolution->setRange(-180.0, 180.0);
    yResolution->setValue(40.9177);
    yResolution->setVisible(false);

    resolutionContainer = new QHBoxLayout();
    valueResolutionContainer = new QVBoxLayout();
	minResolutionContainer = new QHBoxLayout();
	maxResolutionContainer = new QHBoxLayout();
    minResolutionContainer->addWidget(minXResolution);
    minResolutionContainer->addWidget(minYResolution);
    maxResolutionContainer->addWidget(xResolution);
    maxResolutionContainer->addWidget(yResolution);
    valueResolutionContainer->addLayout(minResolutionContainer);
    valueResolutionContainer->addLayout(maxResolutionContainer);
    resolutionContainer->addWidget(resolutionLabel);
    resolutionContainer->addLayout(valueResolutionContainer);
 

    constructButton = new QPushButton("Construct");
    constructButton->setVisible(false);

    rightContainer = new QVBoxLayout();
    rightContainer->addLayout(resolutionContainer);
    rightContainer->addLayout(depthContainer);
    rightContainer->addLayout(sketchFullContainer);
    rightContainer->addWidget(constructButton);

    setLayout(rightContainer);
}

SketchMenuDialog::SketchMenuDialog(QWidget* parent): QDialog(parent) {
    this->setupUi();

    QObject::connect(sketchsMenu, &QComboBox::currentTextChanged, this, [&](const QString &text){
        bool validSketch = text != tr("undefined");

        constructButton->setVisible(validSketch);
        setSketchConfigUiVisible(validSketch, text == tr("dcs") or text == tr("q_digest"));
    });

    QObject::connect(constructButton, &QAbstractButton::pressed, this, [&](){
        qDebug() << "ok pressed";
        
        emit constructQQ(minXResolution->value(), minYResolution->value(), xResolution->value(), yResolution->value(), depthBox->value(), sketchsMenu->currentText(), leafsOption->isChecked(), sketchError->value(), sketchUniverse->value());

        this->done(QDialog::Accepted);
    }); 
}

SketchMenuDialog::~SketchMenuDialog(){
}

void SketchMenuDialog::setSketchConfigUiVisible(const bool& visible, const bool& addUniverse){
    sketchError->setVisible(visible);
    errorLabel->setVisible(visible);
    universeLabel->setVisible(visible);
    sketchUniverse->setVisible(visible);

    if(not addUniverse){
        universeLabel->setVisible(false);
        sketchUniverse->setVisible(false);
    }
}