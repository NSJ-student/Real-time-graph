#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_CustomPlot( 0 )
{
    ui->setupUi(this);

    //  main widget
    mainLayout = new QHBoxLayout;
    mainWidget = new QWidget(this);
    mainWidget->setLayout(mainLayout);

    // left side (tree widget)
    treeView = new QTreeView(this);
    mainLayout->addWidget(treeView, 20);
    treeView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    // right side (stacked widget)
    mainStackWidget = new QStackedWidget(this);
    mainLayout->addWidget(mainStackWidget, 80);
    mainStackWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // stacked widget 1
    stack1Widget = new QWidget();
    stack1Layout = new QVBoxLayout();
    mainStackWidget->addWidget(stack1Widget);
    stack1Widget->setLayout(stack1Layout);

    //      button
    controlWidget = new QWidget();
    controlLayout = new QGridLayout();
    openButton = new QPushButton("Open");
    openButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    openButton->setMaximumWidth(100);
    connect(openButton, SIGNAL(clicked(bool)), this, SLOT(openFile(bool)));
    openFileName = new QLabel("");
    controlLayout->addWidget(openButton, 0, 0);
    controlLayout->addWidget(openFileName, 0, 1);
    controlWidget->setLayout(controlLayout);
    controlWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    stack1Layout->addWidget(controlWidget, 10);
    //      graph
    m_CustomPlot = new QCustomPlot(this);
    m_CustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    stack1Layout->addWidget(m_CustomPlot, 90);

    this->setCentralWidget(mainWidget);

    // graph setting
    int n = 50; // number of points in graph
    QVector<double> x(n), y(n);
    for (int i=0; i<n; i++)
    {
      x[i] = i;
      y[i] = qSin(i) + 2;
    }

    m_CustomPlot->addGraph();
    m_CustomPlot->graph()->setName(QString("New graph %1").arg(m_CustomPlot->graphCount()-1));
    m_CustomPlot->graph()->setData(x, y);
    m_CustomPlot->replot();

    connect(m_CustomPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(m_CustomPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(menuOpen(bool)));
    connect(ui->actionClose, SIGNAL(triggered(bool)), this, SLOT(menuClose(bool)));
    connect(ui->actionChange_Data, SIGNAL(triggered(bool)), this, SLOT(menuData(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::menuOpen(bool toggle)
{
    QMessageBox::information(this, "test", "test", "ok");
}

void MainWindow::menuClose(bool toggle)
{
    this->close();
}

void MainWindow::menuData(bool toggle)
{
    int n = rand() % 1000 + 500; // number of points in graph
    QVector<double> x(n), y(n);
    int mul = (rand() % 100);
    for (int i=0; i<n; i++)
    {
      x[i] = i;
      y[i] = mul * qSin(i*3.14/100) + 2;
    }
    m_CustomPlot->graph()->setData(x, y);
    m_CustomPlot->replot();
}

void MainWindow::mousePress()
{
    // if an axis is selected, only allow the direction of that axis to be dragged
    // if no axis is selected, both directions may be dragged

    if (m_CustomPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
      m_CustomPlot->axisRect()->setRangeDrag(m_CustomPlot->xAxis->orientation());
    else if (m_CustomPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
      m_CustomPlot->axisRect()->setRangeDrag(m_CustomPlot->yAxis->orientation());
    else
        m_CustomPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::openFile(bool click)
{
    QFileDialog fileDialog(this, tr("Open File"),
                tr("D:\\"),
                tr("Audios (*.mp3 *.wav *.wma)"));

    QStringList fileNames;
    if (fileDialog.exec()) {
        fileNames = fileDialog.selectedFiles();
        openFileName->setText(fileNames[0]);
    }
}

void MainWindow::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  if (m_CustomPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    m_CustomPlot->axisRect()->setRangeZoom(m_CustomPlot->xAxis->orientation());
  else if (m_CustomPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    m_CustomPlot->axisRect()->setRangeZoom(m_CustomPlot->yAxis->orientation());
  else
    m_CustomPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}
