#include "mainwindow.h"

void MainWindow::setupUi(){
    //setFixedSize(1000, 500);

    view.setEnabled(false);

    newMenu = new QMenu("Simulation");
    newMenu->addAction(tr("New"), this, &MainWindow::onNewSimulation);
    newMenu->addSeparator();
    newMenu->addAction(tr("Quit"), this, &MainWindow::onQuit);

    menuBar = new QMenuBar();
    menuBar->addMenu(newMenu);

    this->setMenuBar(menuBar);

    sketchsMenu = new QComboBox();
    sketchsMenu->addItem(tr("undefined"));
    sketchsMenu->addItem(tr("kll"));
    sketchsMenu->addItem(tr("q_digest"));
    sketchsMenu->addItem(tr("gk"));
    sketchsMenu->addItem(tr("dcs"));

    sketchsLabel = new QLabel();
    sketchsLabel->setText("Sketch: ");

    sketchInfoContainer = new QHBoxLayout();

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

    simulationContainer = new QVBoxLayout();

	feedContainer = new QVBoxLayout();
	feedingMethod = new QComboBox();
    feedingMethod->addItem(tr("Uniform Int Stream"));
    feedingMethod->addItem(tr("Uniform Int Stream with weight"));
    feedingMethod->addItem(tr("Stream City"));
    feedingMethod->addItem(tr("Stream City with weight"));
    feedingMethod->setVisible(false);
    

	fSizeLabel = new QLabel("Stream size: ");
    fSizeLabel->setVisible(false);
	fSize = new QSpinBox();
    fSize->setRange(1, 10000000);
    fSize->setValue(1000);
    fSize->setVisible(false);

    fSizeContainer = new QHBoxLayout();
    fSizeContainer->addWidget(fSizeLabel);
    fSizeContainer->addWidget(fSize);

	fMaxValueLabel = new QLabel("Max value on Stream: ");
    fMaxValueLabel->setVisible(false);
	fMaxValue = new QSpinBox();
    fMaxValue->setRange(0, 10000);
    fMaxValue->setValue(1000);
    fMaxValue->setVisible(false);

    fMaxValueContainer = new QHBoxLayout();
    fMaxValueContainer->addWidget(fMaxValueLabel);
    fMaxValueContainer->addWidget(fMaxValue);

	fMaxWeightLabel = new QLabel("Max weight for a element: ");
    fMaxWeightLabel->setVisible(false);
	fMaxWeight = new QSpinBox();
    fMaxWeight->setRange(1, 1000);
    fMaxWeight->setValue(10);
    fMaxWeight->setVisible(false);

    fMaxWeightContainer = new QHBoxLayout();
    fMaxWeightContainer->addWidget(fMaxWeightLabel);
    fMaxWeightContainer->addWidget(fMaxWeight);

	fCitiesLabel = new QLabel("Cities: ");
    fCitiesLabel->setVisible(false);
    fCities = new QSpinBox();
    fCities->setMinimum(1);
    fCities->setValue(10);
    fCities->setVisible(false);

    fCitiesContainer = new QHBoxLayout();
    fCitiesContainer->addWidget(fCitiesLabel);
    fCitiesContainer->addWidget(fCities);

	fMaxRadiusLabel = new QLabel("Max Radius for next elements: ");
    fMaxRadiusLabel->setVisible(false);
	fMaxRadius = new QDoubleSpinBox();
    fMaxRadius->setMinimum(0.1);
    fMaxRadius->setVisible(false);

    fMaxRadiusContainer = new QHBoxLayout();
    fMaxRadiusContainer->addWidget(fMaxRadiusLabel);
    fMaxRadiusContainer->addWidget(fMaxRadius);

    loadStreamMethodButton = new QPushButton("Feed from file");
    loadStreamMethodButton->setVisible(false);

    feedContainer->addWidget(feedingMethod);
    feedContainer->addLayout(fSizeContainer);
    feedContainer->addLayout(fMaxValueContainer);
    feedContainer->addLayout(fMaxWeightContainer);
    feedContainer->addLayout(fCitiesContainer);
    feedContainer->addLayout(fMaxRadiusContainer);
    feedContainer->addWidget(loadStreamMethodButton);

	batchContainer = new QVBoxLayout();

    bTimeContainer = new QHBoxLayout();
	bTimeLabel = new QLabel("Batch Time: ");
    bTimeLabel->setVisible(false);
	bTime = new QDoubleSpinBox();
    bTime->setMinimum(0.01);
    bTime->setValue(0.5);
    bTime->setSuffix(" s");
    bTime->setVisible(false);

    bTimeContainer->addWidget(bTimeLabel);
    bTimeContainer->addWidget(bTime);

    bItemQuantContainer = new QHBoxLayout();
    bItemQuantLabel = new QLabel("Items per batch");
    bItemQuantLabel->setVisible(false);
	bItemQuant = new QSpinBox();
    bItemQuant->setRange(1, 100);
    bItemQuant->setVisible(false);

    bItemQuantContainer->addWidget(bItemQuantLabel);
    bItemQuantContainer->addWidget(bItemQuant);

    batchContainer->addLayout(bTimeContainer);
    batchContainer->addLayout(bItemQuantContainer);

	simulationButton = new QPushButton("Start Simulation");
    simulationButton->setVisible(false);

    simulationContainer->addLayout(feedContainer);
    simulationContainer->addLayout(batchContainer);
    simulationContainer->addWidget(simulationButton);

    rankQueryContainer = new QHBoxLayout();
	rankQueryLabel = new QLabel("Rank query: ");
    rankQueryLabel->setVisible(false);
    valueForRankQuery = new QSpinBox();
    valueForRankQuery->setRange(0, 10000);
    valueForRankQuery->setVisible(false);

    drawOptionsContainer = new QVBoxLayout();

    drawModesContainer = new QHBoxLayout();
	drawModesLabel = new QLabel("Draw mode: ");
    drawModesLabel->setVisible(false);

    drawModes = new QComboBox();
    drawModes->addItem(tr("Raw data"));
    drawModes->addItem(tr("Raw data with Bounds"));
    drawModes->addItem(tr("Heat map"));
    drawModes->addItem(tr("KS"));
    drawModes->setVisible(false);

    depthDraw = new QSlider();
    depthDraw->setMinimum(0);
    depthDraw->setSingleStep(1);
    depthDraw->setValue(0);
    depthDraw->setVisible(false);
    depthDraw->setOrientation(Qt::Horizontal);
    depthDraw->setMaximumWidth(250);  

    drawModesContainer->addWidget(drawModesLabel);
    drawModesContainer->addWidget(drawModes);
    drawOptionsContainer->addLayout(drawModesContainer);
    drawOptionsContainer->addWidget(depthDraw);

    rankQueryContainer->addWidget(rankQueryLabel);
    rankQueryContainer->addWidget(valueForRankQuery);

    freezeButton = new QPushButton("Freeze Simulation");
    freezeButton->setVisible(false);

    sketchInfo = new QLabel();
    sketchInfo->setAlignment(Qt::AlignCenter);
    sketchInfo->setText("");

    customPlot = new QCustomPlot();

    customPlot->setMinimumHeight(150);

    statistical = new QCPStatisticalBox(customPlot->xAxis, customPlot->yAxis);
    QBrush boxBrush(QColor(60, 60, 255, 100));
    boxBrush.setStyle(Qt::Dense6Pattern); // make it look oldschool
    statistical->setBrush(boxBrush);
    
    // specify data:
    //statistical->addData(1, 1.1, 1.9, 2.25, 2.7, 4.2);
    //statistical->addData(2, 0.8, 1.6, 2.2, 3.2, 4.9, QVector<double>() << 0.7 << 0.34 << 0.45 << 6.2 << 5.84); // provide some outliers as QVector
    //statistical->addData(3, 0.2, 0.7, 1.1, 1.6, 2.9);
    
    // prepare manual x axis labels:
    customPlot->xAxis->setSubTicks(false);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->setTickLabelRotation(20);
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTick(1, "Red");
    textTicker->addTick(2, "Green");
    textTicker->addTick(3, "Blue");
    textTicker->addTick(4, "Magenta");
    textTicker->addTick(5, "Black");
    customPlot->xAxis->setTicker(textTicker);
    
    // prepare axes:
    customPlot->yAxis->setLabel(QString::fromUtf8("Elements"));
    customPlot->rescaleAxes();
    customPlot->xAxis->scaleRange(2.0, customPlot->xAxis->range().center());
    customPlot->yAxis->setRange(0, 7);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    
    customPlot->setVisible(false);

    sketchInfoContainer->addWidget(sketchInfo);

    rightContainer = new QVBoxLayout();
    //rightContainer->addLayout(resolutionContainer);
    //rightContainer->addLayout(depthContainer);
    //rightContainer->addLayout(sketchFullContainer);
    //rightContainer->addWidget(constructButton);
    rightContainer->addLayout(simulationContainer);
    rightContainer->addWidget(freezeButton);
    rightContainer->addLayout(rankQueryContainer);
    rightContainer->addLayout(drawOptionsContainer);
    rightContainer->addLayout(sketchInfoContainer);
    rightContainer->addWidget(customPlot);
    rightContainer->addStretch();

    mainContainer = new QHBoxLayout();
    mainContainer->addWidget(&view);
    mainContainer->addLayout(rightContainer);

    window = new QWidget();
    window->setLayout(mainContainer);
    setCentralWidget(window);

    freezed = false;
}

/*void MainWindow::setSketchConfigUiVisible(const bool& visible, const bool& addUniverse){
    sketchError->setVisible(visible);
    errorLabel->setVisible(visible);
    universeLabel->setVisible(visible);
    sketchUniverse->setVisible(visible);

    if(not addUniverse){
        universeLabel->setVisible(false);
        sketchUniverse->setVisible(false);
    }
}*/

/*void MainWindow::hideConstructUi(){
    sketchsMenu->setVisible(false);
    sketchsLabel->setVisible(false);
    errorLabel->setVisible(false);
    sketchError->setVisible(false);
    universeLabel->setVisible(false);
    sketchUniverse->setVisible(false);
    depthLabel->setVisible(false);
    depthBox->setVisible(false);
    leafsOption->setVisible(false);
    resolutionLabel->setVisible(false);
    minXResolution->setVisible(false);
	minYResolution->setVisible(false);
    xResolution->setVisible(false);
    yResolution->setVisible(false);
    constructButton->setVisible(false);
}*/

void MainWindow::hideFeedUi(){
    feedingMethod->setVisible(false);
    fSizeLabel->setVisible(false);
    fSize->setVisible(false);
    fMaxValueLabel->setVisible(false);
    fMaxValue->setVisible(false);
    fMaxWeightLabel->setVisible(false);
    fMaxWeight->setVisible(false);
    fCitiesLabel->setVisible(false);
    fCities->setVisible(false);
    fMaxRadiusLabel->setVisible(false);
    fMaxRadius->setVisible(false);
    bTimeLabel->setVisible(false);
    bTime->setVisible(false);
    bItemQuantLabel->setVisible(false);
    bItemQuant->setVisible(false);
    loadStreamMethodButton->setVisible(false);
    simulationButton->setVisible(false);
}

void MainWindow::startUpSimulation(void){
    controller.setTimeInterval(bTime->value());
    controller.setWindowSize(bItemQuant->value());
    controller.startSimulation();

    hideFeedUi();
    //hideConstructUi();

    freezeButton->setVisible(true);

    rankQueryLabel->setVisible(true);
    valueForRankQuery->setVisible(true);
    drawModes->setVisible(true);
    drawModesLabel->setVisible(true);
    bTimeLabel->setVisible(true);
    bTime->setVisible(true);
    valueForRankQuery->setMaximum(fMaxValue->value());
    customPlot->setVisible(true);

    QObject::connect(bTime,  QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double d){
        controller.setTimeInterval(d);
        if(not freezed){
            controller.startSimulation();
        }
    });
}

void MainWindow::setupFeedUi(const QString& sketch){
    QStandardItemModel* model = qobject_cast<QStandardItemModel *>(feedingMethod->model());

    for(int i = 0; i < 4; i++){
        QStandardItem * item = model->item(i);

        if(sketch == tr("q_digest") or sketch == tr("dcs")){
            item->setFlags((i & 1) ? item->flags() | Qt::ItemIsEnabled
                            : item->flags() & ~Qt::ItemIsEnabled);
        }else{
            item->setFlags(not (i & 1) ? item->flags() | Qt::ItemIsEnabled
                            : item->flags() & ~Qt::ItemIsEnabled);
        }

    }

    feedingMethod->setCurrentIndex(sketch == tr("q_digest") or sketch == tr("dcs"));
    configFeedUi(feedingMethod->currentText());
    feedingMethod->show();

    bTimeLabel->setVisible(true);
    bTime->setVisible(true);
    bItemQuantLabel->setVisible(true);
    bItemQuant->setVisible(true);
    loadStreamMethodButton->setVisible(true);
    simulationButton->setVisible(true);
}

void MainWindow::configFeedUi(const QString& method){
    fSizeLabel->setVisible(false);
    fSize->setVisible(false);
    fMaxValueLabel->setVisible(false);
    fMaxValue->setVisible(false);
    fMaxWeightLabel->setVisible(false);
    fMaxWeight->setVisible(false);
    fCitiesLabel->setVisible(false);
    fCities->setVisible(false);
    fMaxRadiusLabel->setVisible(false);
    fMaxRadius->setVisible(false);

    if(method == tr("Uniform Int Stream")){
        fSizeLabel->setVisible(true);
        fSize->setVisible(true);
        fMaxValueLabel->setVisible(true);
        fMaxValue->setVisible(true);
    }else if(method == tr("Uniform Int Stream with weight")){
        fSizeLabel->setVisible(true);
        fSize->setVisible(true);
        fMaxValueLabel->setVisible(true);
        fMaxValue->setVisible(true);
        fMaxWeightLabel->setVisible(true);
        fMaxWeight->setVisible(true);
    }else if(method == tr("Stream City")){
        fSizeLabel->setVisible(true);
        fSize->setVisible(true);
        fMaxValueLabel->setVisible(true);
        fMaxValue->setVisible(true);
        fCitiesLabel->setVisible(true);
        fCities->setVisible(true);
        fMaxRadiusLabel->setVisible(true);
        fMaxRadius->setVisible(true);
    }else if(method == tr("Stream City with weight")){
        fSizeLabel->setVisible(true);
        fSize->setVisible(true);
        fMaxValueLabel->setVisible(true);
        fMaxValue->setVisible(true);
        fMaxWeightLabel->setVisible(true);
        fMaxWeight->setVisible(true);
        fCitiesLabel->setVisible(true);
        fCities->setVisible(true);
        fMaxRadiusLabel->setVisible(true);
        fMaxRadius->setVisible(true);
    }else{
        qDebug() << "Invalid Method";
    }
}

void MainWindow::onNewSimulation(){
    SketchMenuDialog sketchMenu(this);

    QObject::connect(&sketchMenu, &SketchMenuDialog::constructQQ, this, [&](const double& minXRes, const double& minYRes, const double& xRes, const double& yRes, const int& depth, const QString& sketch, const bool& leafsOpt, const double& sketchErr, const int& sketchUni){
        qsbd::aabb<double> bounds(minXRes, minYRes, xRes, yRes);
        
        depthDraw->setMaximum(depth);

        if(sketch == tr("kll")){
            model.initKll(bounds, depth, leafsOpt, sketchErr);
        }else if(sketch == tr("q_digest")){
            model.initQDigest(bounds, depth, leafsOpt, sketchErr, sketchUni);
        }else if(sketch == tr("gk")){
            model.initGk(bounds, depth, leafsOpt, sketchErr);
        }else if(sketch == tr("dcs")){
            model.initDcs(bounds, depth, leafsOpt, sketchErr, sketchUni);
        }else{
            qDebug() << "Invalid sketch";
        }

        if(not view.isEnabled()){
            view.setDomain(minXRes, minYRes, xRes, yRes);
            view.setDepth(depth);
            view.setEnabled(true);
        }

        setupFeedUi(sketch);
    });

    if(sketchMenu.exec()){
        qDebug() << "New teste";
    }
}

void MainWindow::onQuit(){
    QApplication::quit();
}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), view(this), model(this), controller(view, model, this){
    setupUi();

    /*QObject::connect(sketchsMenu, &QComboBox::currentTextChanged, this, [&](const QString &text){
        bool validSketch = text != tr("undefined");

        constructButton->setVisible(validSketch);
        setSketchConfigUiVisible(validSketch, text == tr("dcs") or text == tr("q_digest"));
    });


    QObject::connect(constructButton, &QAbstractButton::pressed, this, [&](){
        qsbd::aabb<double> bounds(minXResolution->value(), minYResolution->value(), xResolution->value(), yResolution->value());
        
        int depth = depthBox->value();
        depthDraw->setMaximum(depth);

        QString sketch = sketchsMenu->currentText();

        if(sketch == tr("kll")){
            model.initKll(bounds, depth, leafsOption->isChecked(), sketchError->value());
        }else if(sketch == tr("q_digest")){
            model.initQDigest(bounds, depth, leafsOption->isChecked(), sketchError->value(), sketchUniverse->value());
        }else if(sketch == tr("gk")){
            model.initGk(bounds, depth, leafsOption->isChecked(), sketchError->value());
        }else if(sketch == tr("dcs")){
            model.initDcs(bounds, depth, leafsOption->isChecked(), sketchError->value(), sketchUniverse->value());
        }else{
            qDebug() << "Invalid sketch";
        }

        if(not view.isEnabled()){
            view.setDomain(minXResolution->value(), minYResolution->value(), xResolution->value(), yResolution->value());
            view.setDepth(depth);
            view.setEnabled(true);
        }

        setupFeedUi(sketch);
    });*/

    QObject::connect(freezeButton, &QAbstractButton::pressed, this, [&](){
        if(not freezed){
            freezeButton->setText("Restart Simulation");

            freezed = true;

            controller.freeze();
        }else{
            freezeButton->setText("Freeze Simulation");

            freezed = false;

            controller.startSimulation();
        }
    });

    QObject::connect(feedingMethod, &QComboBox::currentTextChanged, this, &MainWindow::configFeedUi);

    QObject::connect(simulationButton, &QAbstractButton::pressed, this, [&](){
        QString method = feedingMethod->currentText();

        if(method == tr("Uniform Int Stream")){
            controller.feedStreamInRegion(fSize->value(), minXResolution->value(), minYResolution->value(), xResolution->value(), yResolution->value(), 0, fMaxValue->value());
        }else if(method == tr("Uniform Int Stream with weight")){
            controller.feedStreamInRegionWithWeight(fSize->value(), minXResolution->value(), minYResolution->value(), xResolution->value(), yResolution->value(), 0, fMaxValue->value(), 1, fMaxWeight->value());
        }else if(method == tr("Stream City")){
            controller.feedRandomStreamCity(fSize->value(), minXResolution->value(), minYResolution->value(), xResolution->value(), yResolution->value(), 0, fMaxValue->value(), fCities->value(), fMaxRadius->value());
        }else if(method == tr("Stream City with weight")){
            controller.feedRandomStreamCityWithWeight(fSize->value(), minXResolution->value(), minYResolution->value(), xResolution->value(), yResolution->value(), 0, fMaxValue->value(), 1, fMaxWeight->value(), fCities->value(), fMaxRadius->value());
        }else{
            qDebug() << "Invalid Method";
        }

        startUpSimulation();
    });
    

    QObject::connect(loadStreamMethodButton, &QAbstractButton::pressed, this, [&](){
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::ExistingFile);
        dialog.setNameFilter(tr("JSON (*.json);;CSV (*.csv)"));

        if (dialog.exec()){
            QString path = dialog.selectedFiles()[0];

            qDebug() << path;

            if (path.endsWith("json")){
                controller.loadFileAndFeed(path);
                startUpSimulation();
            }else if (path.endsWith("csv")){
                CsvDialog csvWindow(this);

                csvWindow.setHeaders(path);

                QObject::connect(&csvWindow, &CsvDialog::collumnsSelected, this, [&](const QString lonCol, const QString latCol, const QString indexCol){
                    controller.loadStreamByCsv(path, lonCol, latCol, indexCol);
                    startUpSimulation();
                });

                //qDebug() << "here";
                if(csvWindow.exec()) qDebug() << "ok";
            }else{
                qDebug() << "not supported";
            }
        }
    });

    QObject::connect(&model, &qsbd::Model::requestReady, this, [&](const int& rank){
        if(not freezed){
            controller.startSimulation();
        }

        sketchInfo->setText(tr("rank : %1").arg(rank));
    });

    QObject::connect(&model, &qsbd::Model::quantileReady, this, [&](const std::vector<int>& quants, const int& queryId){
        if(not freezed){
            controller.startSimulation();
        }
        
        ASSERT(quants.size() == 5);

        bool findData = false;
        auto statisticalData = statistical->data().data();

        for(auto element = statisticalData->begin(); element != statisticalData->end(); element++){
            if((int) (element->key) == (queryId + 1)){
                element->minimum = quants[0];
                element->lowerQuartile = quants[1];
                element->median = quants[2];
                element->upperQuartile = quants[3];
                element->maximum = quants[4];
                findData = true;
                break;
            }
        }

        if(not findData){
            statistical->addData(queryId + 1, quants[0], quants[1], quants[2], quants[3], quants[4]);
        }
        customPlot->rescaleAxes();
        customPlot->xAxis->scaleRange(2.0, customPlot->xAxis->range().center());
        customPlot->replot();
    });

    QObject::connect(&view, &qsbd::View::queryRequest, this, [&](const QRectF& region){
        controller.freeze();
        //qDebug() << tr("Loading... [%1, %2, %3, %4]").arg(region.bottomLeft().x()).arg(region.topRight().y()).arg(region.topRight().x()).arg(region.bottomLeft().y());
        sketchInfo->setText(tr("Loading... [%1, %2, %3, %4]").arg(region.bottomLeft().x()).arg(region.topRight().y()).arg(region.topRight().x()).arg(region.bottomLeft().y()));
        model.onQuery(region, valueForRankQuery->value());
    });

    QObject::connect(&view, &qsbd::View::quantileRequest, this, [&](const QRectF& region, const int& queryId){
        controller.freeze();
        model.onMultiQuantile(region, {0.1, 0.25, 0.5, 0.75, 0.9}, queryId);
    });

    QObject::connect(depthDraw, &QAbstractSlider::valueChanged, this, [&](int value){
        view.setDepthView(value);
    });

    QObject::connect(drawModes, &QComboBox::currentTextChanged, this, [&](){
        QString method = drawModes->currentText();
        
        if(method == tr("Raw data")){
            depthDraw->setVisible(false);
            view.setDrawingMode(0);
        }else if(method == tr("Raw data with Bounds")){
            depthDraw->setVisible(true);
            view.setDepthView(depthDraw->value());
            view.setDrawingMode(1);
        }else if(method == tr("Heat map")){
            depthDraw->setVisible(false);
            view.setDrawingMode(2);
        }else if(method == tr("KS")){
            depthDraw->setVisible(false);
            view.setDrawingMode(3);
        }else{
            depthDraw->setVisible(false);
            view.setDrawingMode(0);
        }

    });

    QObject::connect(&view, &qsbd::View::ksRequest, &model, &qsbd::Model::onKsRequest);
    QObject::connect(&model, &qsbd::Model::ksReady, &view, &qsbd::View::onKsReady);
}

MainWindow::~MainWindow(){
}

