#include "mainwindow.h"

void MainWindow::resizeEvent(QResizeEvent *event){
    this->repaint();
    QMainWindow::resizeEvent(event);
}

void MainWindow::setupUi(){
    //setMaximumSize(1000, 500);

    view.setEnabled(false);

    newMenu = new QMenu("Simulation");
    newMenu->addAction(tr("New"), this, &MainWindow::onNewSimulation);
    newMenu->addSeparator();
    newMenu->addAction(tr("Quit"), this, &MainWindow::onQuit);

    freezeButton = new QPushButton("Freeze Simulation");
    freezeButton->setVisible(false);
    
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

    menuBar = new QMenuBar();
    menuBar->addMenu(newMenu);

    this->setMenuBar(menuBar);

    topDock = new QDockWidget();
    topContainer = new QHBoxLayout();

    topContainer->addWidget(freezeButton);
    topContainer->addLayout(bTimeContainer);
    topContainer->addStretch();

    QWidget* topWidget = new QWidget();
    topWidget->setLayout(topContainer);

    topDock->setWidget(topWidget);
    topDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    topDock->setVisible(false);
    topDock->setMaximumHeight(100);

    bottomDock = new QDockWidget();
    bottomContainer = new QHBoxLayout();
    
    drawBounds = new QCheckBox();
    drawBounds->setCheckState(Qt::Unchecked);

    drawBoundsLabel = new QLabel("Show Grid");
    drawBoundsLabel->setVisible(false);

    depthDrawLabel = new QLabel("Depth:");
    depthDrawLabel->setVisible(false);

    depthDraw = new QSpinBox();
    depthDraw->setMinimum(0);
    depthDraw->setSingleStep(1);
    depthDraw->setValue(0);
    depthDraw->setVisible(false);
    //depthDraw->setOrientation(Qt::Horizontal);
    depthDraw->setMaximumWidth(250);

    bottomContainer->addWidget(drawBounds);
    bottomContainer->setAlignment(drawBounds, Qt::AlignCenter);
    bottomContainer->addWidget(drawBoundsLabel);
    bottomContainer->setAlignment(drawBoundsLabel, Qt::AlignCenter);
    bottomContainer->addWidget(depthDrawLabel);
    bottomContainer->setAlignment(depthDrawLabel, Qt::AlignCenter);
    bottomContainer->addWidget(depthDraw);
    bottomContainer->setAlignment(depthDraw, Qt::AlignCenter);
    bottomContainer->addStretch();

    QWidget* bottomWidget = new QWidget();
    bottomWidget->setLayout(bottomContainer);

    bottomDock->setWidget(bottomWidget);
    bottomDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    bottomDock->setVisible(false);
    bottomDock->setMaximumHeight(100);

    this->addDockWidget(Qt::TopDockWidgetArea, topDock);
    this->addDockWidget(Qt::BottomDockWidgetArea, bottomDock);

    //toolBar = new QToolBar();

    //toolBar->addWidget(freezeButton);
    //toolBar->addLayout(bTimeContainer);

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
    feedingMethod->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    
	fSizeLabel = new QLabel("Stream size: ");
    fSizeLabel->setVisible(false);
    fSizeLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	fSize = new QSpinBox();
    fSize->setRange(1, 10000000);
    fSize->setValue(1000);
    fSize->setVisible(false);
    fSize->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    fSizeContainer = new QHBoxLayout();
    fSizeContainer->addWidget(fSizeLabel);
    fSizeContainer->addWidget(fSize);

	fMaxValueLabel = new QLabel("Max value on Stream: ");
    fMaxValueLabel->setVisible(false);
    fMaxValueLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	fMaxValue = new QSpinBox();
    fMaxValue->setRange(0, 10000);
    fMaxValue->setValue(1000);
    fMaxValue->setVisible(false);
    fMaxValue->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    fMaxValueContainer = new QHBoxLayout();
    fMaxValueContainer->addWidget(fMaxValueLabel);
    fMaxValueContainer->addWidget(fMaxValue);

	fMaxWeightLabel = new QLabel("Max weight for a element: ");
    fMaxWeightLabel->setVisible(false);
    fMaxWeightLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	fMaxWeight = new QSpinBox();
    fMaxWeight->setRange(1, 1000);
    fMaxWeight->setValue(10);
    fMaxWeight->setVisible(false);
    fMaxWeight->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    fMaxWeightContainer = new QHBoxLayout();
    fMaxWeightContainer->addWidget(fMaxWeightLabel);
    fMaxWeightContainer->addWidget(fMaxWeight);

	fCitiesLabel = new QLabel("Cities: ");
    fCitiesLabel->setVisible(false);
    fCitiesLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    fCities = new QSpinBox();
    fCities->setMinimum(1);
    fCities->setValue(10);
    fCities->setVisible(false);
    fCities->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    fCitiesContainer = new QHBoxLayout();
    fCitiesContainer->addWidget(fCitiesLabel);
    fCitiesContainer->addWidget(fCities);

	fMaxRadiusLabel = new QLabel("Max Radius for next elements: ");
    fMaxRadiusLabel->setVisible(false);
    fMaxRadiusLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	fMaxRadius = new QDoubleSpinBox();
    fMaxRadius->setMinimum(0.1);
    fMaxRadius->setVisible(false);
    fMaxRadius->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    fMaxRadiusContainer = new QHBoxLayout();
    fMaxRadiusContainer->addWidget(fMaxRadiusLabel);
    fMaxRadiusContainer->addWidget(fMaxRadius);

    loadStreamMethodButton = new QPushButton("Feed from file");
    loadStreamMethodButton->setVisible(false);
    loadStreamMethodButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    feedContainer->addWidget(feedingMethod);
    feedContainer->addLayout(fSizeContainer);
    feedContainer->addLayout(fMaxValueContainer);
    feedContainer->addLayout(fMaxWeightContainer);
    feedContainer->addLayout(fCitiesContainer);
    feedContainer->addLayout(fMaxRadiusContainer);
    feedContainer->addWidget(loadStreamMethodButton);

	batchContainer = new QVBoxLayout();

    bItemQuantContainer = new QHBoxLayout();
    bItemQuantLabel = new QLabel("Items per batch");
    bItemQuantLabel->setVisible(false);
    bItemQuantLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	bItemQuant = new QSpinBox();
    bItemQuant->setRange(1, 100);
    bItemQuant->setVisible(false);
    bItemQuant->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    bItemQuantContainer->addWidget(bItemQuantLabel);
    bItemQuantContainer->addWidget(bItemQuant);

    //batchContainer->addLayout(bTimeContainer);
    batchContainer->addLayout(bItemQuantContainer);

	simulationButton = new QPushButton("Start Simulation");
    simulationButton->setVisible(false);
    simulationButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    simulationContainer->addLayout(feedContainer);
    simulationContainer->addLayout(batchContainer);
    simulationContainer->addWidget(simulationButton);
    simulationContainer->addStretch();

    sketchInfo = new QLabel();
    sketchInfo->setAlignment(Qt::AlignCenter);
    sketchInfo->setText("");
    sketchInfo->setVisible(false);
    sketchInfo->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    sketchInfoContainer->addWidget(sketchInfo);

    controlTab = new QTabWidget();
    controlTab->setVisible(false);

	clearButton = new QPushButton("Clear");

    queryIdContainer = new QHBoxLayout();
    queryIdLabel = new QLabel("Show:");
    queryIdLabel->setVisible(false);
    queryIdComboBox = new QComboBox();
    queryIdComboBox->addItem(tr("Show all"));
    /*queryIdComboBox->addItem(tr("Red"));
    queryIdComboBox->addItem(tr("Green"));
    queryIdComboBox->addItem(tr("Blue"));
    queryIdComboBox->addItem(tr("Magenta"));
    queryIdComboBox->addItem(tr("Black"));*/
    queryIdComboBox->setVisible(false);

    queryIdContainer->addWidget(queryIdLabel);
    queryIdContainer->addWidget(queryIdComboBox);

    rankQueryContainer = new QHBoxLayout();
	rankQueryLabel = new QLabel("Rank query: ");
    rankQueryLabel->setVisible(false);
    valueForRankQuery = new QSpinBox();
    valueForRankQuery->setRange(0, 10000);
    valueForRankQuery->setVisible(false);
    rankQueryButton =  new QPushButton("Query");
    rankQueryButton->setVisible(false);

    rankQueryContainer->addWidget(rankQueryLabel);
    rankQueryContainer->addWidget(valueForRankQuery);
    rankQueryContainer->addWidget(rankQueryButton);

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
    customPlot->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    selectionPageContainer = new QVBoxLayout();
    selectionPageContainer->addWidget(clearButton);
    selectionPageContainer->addLayout(queryIdContainer);
    selectionPageContainer->addLayout(rankQueryContainer);
    selectionPageContainer->addLayout(sketchInfoContainer);
    selectionPageContainer->addWidget(customPlot);

    selectionPage = new QWidget();
    controlTab->insertTab(0, selectionPage, tr("Selection"));
    controlTab->widget(0)->setLayout(selectionPageContainer);

    clusterPageContainer = new QVBoxLayout();

    /*drawModesContainer = new QHBoxLayout();
	drawModesLabel = new QLabel("Draw mode: ");
    drawModesLabel->setVisible(false);

    drawModes = new QComboBox();
    drawModes->addItem(tr("Raw data"));
    drawModes->addItem(tr("Raw data with Bounds"));
    drawModes->addItem(tr("Heat map"));
    drawModes->addItem(tr("KS"));
    drawModes->setVisible(false);*/

    kClusterContainer = new QHBoxLayout();

    kClusterLabel = new QLabel("Clusters:");
    kClusterLabel->setVisible(false);

    kCluster = new QSpinBox();
    kCluster->setMinimum(1);
    kCluster->setMaximum(10);
    kCluster->setSingleStep(1);
    kCluster->setValue(0);
    kCluster->setVisible(false);
    //kCluster->setOrientation(Qt::Horizontal);
    kCluster->setMaximumWidth(250);

    kClusterContainer->addWidget(kClusterLabel);
    kClusterContainer->addWidget(kCluster);

    epsilonContainer = new QHBoxLayout();

    epsilonLabel = new QLabel("Epsilon: ");
    epsilonLabel->setVisible(false);

    epsilonBox = new QDoubleSpinBox();
    epsilonBox->setDecimals(1);
    epsilonBox->setRange(0.1, 0.9);
    epsilonBox->setSingleStep(0.1);
    epsilonBox->setValue(0.1);
    epsilonBox->setVisible(false);

    epsilonContainer->addWidget(epsilonLabel);
    epsilonContainer->addWidget(epsilonBox);

    dbscanContainer = new QHBoxLayout();

    dbscanMinLabel = new QLabel("Min Points for Epsilon:");
    dbscanMinLabel->setVisible(false);

    dbscanMin = new QSpinBox();
    dbscanMin->setMinimum(1);
    dbscanMin->setMaximum(10);
    dbscanMin->setSingleStep(1);
    dbscanMin->setValue(0);
    dbscanMin->setVisible(false);

    dbscanContainer->addWidget(dbscanMinLabel);
    dbscanContainer->addWidget(dbscanMin);

    kClusterMethodContainer = new QHBoxLayout();

    kClusterMethodLabel = new QLabel("Algorithms: ");

    kClusterMethod = new QComboBox();
    kClusterMethod->addItem(tr("K-Medoids"));
    kClusterMethod->addItem(tr("DBSCAN"));
    kClusterMethod->addItem(tr("K-Means"));
    kClusterMethod->setVisible(false);

    kClusterMethodContainer->addWidget(kClusterMethodLabel);
    kClusterMethodContainer->addWidget(kClusterMethod);

    /*drawModesContainer->addWidget(drawModesLabel);
    drawModesContainer->addWidget(drawModes);
    clusterPageContainer->addLayout(drawModesContainer);*/
    clusterPageContainer->addLayout(kClusterMethodContainer);
    clusterPageContainer->addLayout(kClusterContainer);
    clusterPageContainer->addLayout(epsilonContainer);
    clusterPageContainer->addLayout(dbscanContainer);
    clusterPageContainer->addStretch();

    clusterPage = new QWidget();
    controlTab->insertTab(1, clusterPage, tr("Cluster"));
    controlTab->widget(1)->setLayout(clusterPageContainer);

    controlTab->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    rightContainer = new QVBoxLayout();
    //rightContainer->addLayout(resolutionContainer);
    //rightContainer->addLayout(depthContainer);
    //rightContainer->addLayout(sketchFullContainer);
    //rightContainer->addWidget(constructButton);
    rightContainer->addLayout(simulationContainer);
    //rightContainer->addLayout(sketchInfoContainer);
    rightContainer->addWidget(controlTab);
    //rightContainer->addStretch();

    mainContainer = new QHBoxLayout();
    mainContainer->addWidget(&view, 80);
    mainContainer->addLayout(rightContainer, 20);

    window = new QWidget();
    window->setLayout(mainContainer);
    setCentralWidget(window);

    freezed = false;

    useDoubleOnIndex = false;

    this->m_minIdxDomain = 0.0;
    this->m_maxIdxDomain = 0.0;
    this->m_depthIdxDomain = 0;
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
    // remeber to add this spacer again in the loop
    simulationContainer->removeItem(simulationContainer->itemAt(simulationContainer->count() - 1));
}

void MainWindow::startUpSimulation(void){
    controller.setTimeInterval(bTime->value());
    controller.setWindowSize(bItemQuant->value());
    controller.startSimulation();

    hideFeedUi();
    //hideConstructUi();

    controlTab->setVisible(true);

    topDock->setVisible(true);

    freezeButton->setVisible(true);
    bTimeLabel->setVisible(true);
    bTime->setVisible(true);

    QObject::connect(bTime,  QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [&](double d){
        controller.setTimeInterval(d);
        if(not freezed){
            controller.startSimulation();
        }
    });

    bottomDock->setVisible(true);

    drawBoundsLabel->setVisible(true);
    drawBounds->setVisible(true);

    QObject::connect(drawBounds, &QCheckBox::stateChanged, this, [&](int state){
        if(state == Qt::Checked){
            depthDrawLabel->setVisible(true);
            depthDraw->setVisible(true);
            view.setDepthView(depthDraw->value());
            view.setDrawingMode(qsbd::ViewDrawMode::QuadtreeDepth);
        }else{
            depthDrawLabel->setVisible(false);
            depthDraw->setVisible(false);
            view.setDrawingMode(qsbd::ViewDrawMode::OnlyPoints);
        }
    });

    queryIdLabel->setVisible(true);
    queryIdComboBox->setVisible(true);
    //rankQueryLabel->setVisible(true);
    //valueForRankQuery->setVisible(true);
    //drawModes->setVisible(true);
    //drawModesLabel->setVisible(true);
    
    valueForRankQuery->setMaximum(fMaxValue->value());
    customPlot->setVisible(true);
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
            view.setEnabled(true);
            view.setMapVisible(true);
            view.setDomain(minXRes, minYRes, xRes, yRes);
            view.setDepth(depth);
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

    QObject::connect(clearButton, &QAbstractButton::pressed, this, [&](){
        sketchInfo->setVisible(false);
        queryIdComboBox->clear();
        queryIdComboBox->addItem(tr("Show all"));
        view.clearQueries();
        statistical->data().data()->clear();
        customPlot->rescaleAxes();
        customPlot->xAxis->scaleRange(2.0, customPlot->xAxis->range().center());
        customPlot->replot();
    });

    QObject::connect(queryIdComboBox,  &QComboBox::currentTextChanged, this, [&](){
        QString curQueryId = queryIdComboBox->currentText();

        if(curQueryId == tr("Show all")){
            view.showAllQueries();

            sketchInfo->setVisible(false);
            rankQueryLabel->setVisible(false);
            valueForRankQuery->setVisible(false);
            rankQueryButton->setVisible(false);
        }else{
            int queryId = 0;

            if(curQueryId == tr("Red")) queryId = 0;
            else if(curQueryId == tr("Green")) queryId = 1;
            else if(curQueryId == tr("Blue")) queryId = 2;
            else if(curQueryId == tr("Magenta")) queryId = 3;
            else if(curQueryId == tr("Black")) queryId = 4;

            sketchInfo->setVisible(true);
            rankQueryLabel->setVisible(true);
            valueForRankQuery->setVisible(true);
            rankQueryButton->setVisible(true);
            view.showOnlyQueryId(queryId);
        }
    });

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
        dialog.setNameFilter(tr("CSV (*.csv);;JSON (*.json)"));

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

                QObject::connect(&csvWindow, &CsvDialog::collumnsSelectedWithMap, this, [&](const QString lonCol, const QString latCol, const QString indexCol, const double& minIdxDomain, const double& maxIdxDomain, const int& depthIdxDomain){
                    this->useDoubleOnIndex = true;
                    this->m_minIdxDomain = minIdxDomain;
                    this->m_maxIdxDomain = maxIdxDomain;
                    this->m_depthIdxDomain = depthIdxDomain;

                    controller.loadStreamByCsvWithMap(path, lonCol, latCol, indexCol, minIdxDomain, maxIdxDomain, depthIdxDomain);
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
                if(not useDoubleOnIndex){
                    element->minimum = quants[0];
                    element->lowerQuartile = quants[1];
                    element->median = quants[2];
                    element->upperQuartile = quants[3];
                    element->maximum = quants[4];
                }else{
                    element->minimum = qsbd::map_coord_inv(quants[0], this->m_minIdxDomain, this->m_maxIdxDomain, this->m_depthIdxDomain);
                    element->lowerQuartile = qsbd::map_coord_inv(quants[1], this->m_minIdxDomain, this->m_maxIdxDomain, this->m_depthIdxDomain);
                    element->median = qsbd::map_coord_inv(quants[2], this->m_minIdxDomain, this->m_maxIdxDomain, this->m_depthIdxDomain);
                    element->upperQuartile = qsbd::map_coord_inv(quants[3], this->m_minIdxDomain, this->m_maxIdxDomain, this->m_depthIdxDomain);
                    element->maximum = qsbd::map_coord_inv(quants[4], this->m_minIdxDomain, this->m_maxIdxDomain, this->m_depthIdxDomain);
                }
                
                findData = true;
                break;

            }
        }

        /*if(useDoubleOnIndex){
            for(int i = 0; i < 5; i++ ){
                std::cout << quants[i] << " -> " << qsbd::map_coord_inv(quants[i], this->m_minIdxDomain, this->m_maxIdxDomain, this->m_depthIdxDomain) << std::endl;
            }
            std::cout << std::endl;
        }*/

        if(not findData){
            if(not useDoubleOnIndex) statistical->addData(queryId + 1, quants[0], quants[1], quants[2], quants[3], quants[4]);
            else statistical->addData(queryId + 1, qsbd::map_coord_inv(quants[0], this->m_minIdxDomain, this->m_maxIdxDomain, this->m_depthIdxDomain), qsbd::map_coord_inv(quants[1], this->m_minIdxDomain, this->m_maxIdxDomain, this->m_depthIdxDomain), qsbd::map_coord_inv(quants[2], this->m_minIdxDomain, this->m_maxIdxDomain, this->m_depthIdxDomain), qsbd::map_coord_inv(quants[3], this->m_minIdxDomain, this->m_maxIdxDomain, this->m_depthIdxDomain), qsbd::map_coord_inv(quants[4], this->m_minIdxDomain, this->m_maxIdxDomain, this->m_depthIdxDomain));

            if(queryId + 1 == 1) queryIdComboBox->addItem(tr("Red"));
            if(queryId + 1 == 2) queryIdComboBox->addItem(tr("Green"));
            if(queryId + 1 == 3) queryIdComboBox->addItem(tr("Blue"));
            if(queryId + 1 == 4) queryIdComboBox->addItem(tr("Magenta"));
            if(queryId + 1 == 5) queryIdComboBox->addItem(tr("Black"));
        }
        customPlot->rescaleAxes();
        customPlot->xAxis->scaleRange(2.0, customPlot->xAxis->range().center());
        customPlot->replot();
    });

    QObject::connect(rankQueryButton, &QAbstractButton::pressed, this, [&](){
        QString curQueryId = queryIdComboBox->currentText();

        if(curQueryId == tr("Show all")){
            // make the emit for the all regions
        }else{
            int queryId = 0;

            if(curQueryId == tr("Red")) queryId = 0;
            else if(curQueryId == tr("Green")) queryId = 1;
            else if(curQueryId == tr("Blue")) queryId = 2;
            else if(curQueryId == tr("Magenta")) queryId = 3;
            else if(curQueryId == tr("Black")) queryId = 4;

            view.setRankAndQuantileQueryRequest(queryId);
        }
    });

    QObject::connect(&view, &qsbd::View::queryRequest, this, [&](const QRectF& region){
        controller.freeze();
        //qDebug() << tr("Loading... [%1, %2, %3, %4]").arg(region.bottomLeft().x()).arg(region.topRight().y()).arg(region.topRight().x()).arg(region.bottomLeft().y());
        //sketchInfo->setVisible(true);
        sketchInfo->setText(tr("Loading... [%1, %2, %3, %4]").arg(region.bottomLeft().x()).arg(region.topRight().y()).arg(region.topRight().x()).arg(region.bottomLeft().y()));
        model.onQuery(region, valueForRankQuery->value());
    });

    QObject::connect(&view, &qsbd::View::quantileRequest, this, [&](const QRectF& region, const int& queryId){
        controller.freeze();
        model.onMultiQuantile(region, {0.1, 0.25, 0.5, 0.75, 0.9}, queryId);
    });

    QObject::connect(depthDraw, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [&](int value){
        view.setDepthView(value);
    });

    QObject::connect(kCluster, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [&](int value){
        view.setKCluster(value);
    });

    QObject::connect(epsilonBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, [&](double value){
        view.setDSBSCANEpsilon(value);
    });

    QObject::connect(dbscanMin, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [&](int value){
        view.setDBSCANMin(value);
    });

    QObject::connect(kClusterMethod, &QComboBox::currentTextChanged, this, [&](){
        QString method = kClusterMethod->currentText();

        kClusterLabel->setVisible(true);
        kCluster->setVisible(true);
        epsilonLabel->setVisible(false);
        epsilonBox->setVisible(false);
        dbscanMinLabel->setVisible(false);
        dbscanMin->setVisible(false);

        if (method == tr("K-Medoids")){
            kClusterLabel->setText(tr("Clusters:"));
            view.setClusteringMethod(qsbd::ClusterMethod::KMedoids);            
        }else if(method == tr("DBSCAN")){
            kClusterLabel->setVisible(false);
            kCluster->setVisible(false);
            epsilonLabel->setVisible(true);
            epsilonBox->setVisible(true);
            dbscanMinLabel->setVisible(true);
            dbscanMin->setVisible(true);
            view.setClusteringMethod(qsbd::ClusterMethod::DBSCAN);
        }else if(method == tr("K-Means")){
            kClusterLabel->setText(tr("Clusters:"));
            view.setClusteringMethod(qsbd::ClusterMethod::KMeans);
        }else{
            kClusterLabel->setText(tr("Clusters:"));
            view.setClusteringMethod(qsbd::ClusterMethod::KMedoids);
        }


    });

    QObject::connect(controlTab, &QTabWidget::currentChanged, this, [&](int index){
        if(index != -1){
            if (controlTab->tabText(index) == "Cluster"){
                drawBounds->setCheckState(Qt::Checked);
                drawBounds->setEnabled(false);
                depthDrawLabel->setVisible(true);
                depthDraw->setVisible(true);
                kClusterLabel->setVisible(true);
                kCluster->setVisible(true);
                kClusterMethod->setVisible(true);
                view.setDrawingMode(qsbd::ViewDrawMode::KS);
            }
            
            if(controlTab->tabText(index) == "Selection"){
                drawBounds->setEnabled(true);
                depthDrawLabel->setVisible(true);
                depthDraw->setVisible(true);
                kClusterLabel->setVisible(false);
                kCluster->setVisible(false);
                kClusterMethod->setVisible(false);
                view.setKCluster(kCluster->value());
                view.setDepthView(depthDraw->value());
                view.setDrawingMode(qsbd::ViewDrawMode::QuadtreeDepth);
            }
        }
    });

    /*QObject::connect(drawModes, &QComboBox::currentTextChanged, this, [&](){
        QString method = drawModes->currentText();
        
        if(method == tr("Raw data")){
            depthDrawLabel->setVisible(false);
            depthDraw->setVisible(false);
            kClusterLabel->setVisible(false);
            kCluster->setVisible(false);
            kClusterMethod->setVisible(false);
            view.setDrawingMode(qsbd::ViewDrawMode::OnlyPoints);
        }else if(method == tr("Raw data with Bounds")){
            depthDrawLabel->setVisible(true);
            depthDraw->setVisible(true);
            kClusterLabel->setVisible(false);
            kCluster->setVisible(false);
            kClusterMethod->setVisible(false);
            view.setKCluster(kCluster->value());
            view.setDepthView(depthDraw->value());
            view.setDrawingMode(qsbd::ViewDrawMode::QuadtreeDepth);
        }else if(method == tr("Heat map")){
            depthDraw->setVisible(false);
            kClusterLabel->setVisible(false);
            kCluster->setVisible(false);
            kClusterMethod->setVisible(false);
            view.setDrawingMode(qsbd::ViewDrawMode::Heatmap);
        }else if(method == tr("KS")){
            depthDrawLabel->setVisible(true);
            depthDraw->setVisible(true);
            kClusterLabel->setVisible(true);
            kCluster->setVisible(true);
            kClusterMethod->setVisible(true);
            view.setDrawingMode(qsbd::ViewDrawMode::KS);
        }else{
            depthDrawLabel->setVisible(false);
            depthDraw->setVisible(false);
            kClusterLabel->setVisible(false);
            kCluster->setVisible(false);
            kClusterMethod->setVisible(false);
            view.setKCluster(kCluster->value());
            view.setDepthView(depthDraw->value());
            view.setDrawingMode(qsbd::ViewDrawMode::OnlyPoints);
        }

    });*/

    QObject::connect(&view, &qsbd::View::cdfsRequest, &model, &qsbd::Model::onCdfsQueries);
    QObject::connect(&model, &qsbd::Model::cdfsReady, &view, &qsbd::View::onCdfsReady);
}

MainWindow::~MainWindow(){
}

