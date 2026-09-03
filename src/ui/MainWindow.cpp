#include "MainWindow.h"

#include "Canvas.h"
#include "model/Wall.h"

#include <QAction>
#include <QKeySequence>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1000, 700);

    QMenu *fileMenu = menuBar()->addMenu("&File");
    QAction *closeAction = fileMenu->addAction("&Close");
    closeAction->setShortcut(QKeySequence::Quit);
    connect(closeAction, &QAction::triggered, this, &QWidget::close);

    Canvas *canvas = new Canvas(this);
    setCentralWidget(canvas);

    // Set up toolbar
    QToolBar *toolbar = addToolBar("Main Toolbar");
    currentLevelLabel_ = new QLabel(this);
    toolbar->addWidget(currentLevelLabel_);
    upAction_ = toolbar->addAction("Up", canvas, [this, canvas]() {
        canvas->setCurrentLevel(canvas->currentLevel() + 1);
        updateCurrentLevel(canvas->currentLevel());
    });
    downAction_ = toolbar->addAction("Down", canvas, [this, canvas]() {
        canvas->setCurrentLevel(canvas->currentLevel() - 1);
        updateCurrentLevel(canvas->currentLevel());
    });

    // Set up layer bar
    QToolBar *layerBar = addToolBar("Layer Toolbar");
    addToolBar(Qt::RightToolBarArea, layerBar);
    layerBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);

    // Set up status bar
    selectedItemLabel_ = new QLabel(this);
    selectedItemLabel_->setText("Selected Wall: None");
    statusBar()->addPermanentWidget(selectedItemLabel_);
    QLabel *cursorPositionLabel = new QLabel(this);
    statusBar()->addPermanentWidget(cursorPositionLabel);
    scaleLabel_ = new QLabel(this);
    statusBar()->addPermanentWidget(scaleLabel_);
    offsetLabel_ = new QLabel(this);
    statusBar()->addPermanentWidget(offsetLabel_);

    // Listen to canvas events and update the status bar accordingly
    connect(canvas, &Canvas::wallSelected,
        this, &MainWindow::wallSelected);
    connect(canvas, &Canvas::cursorPositionChanged,
        cursorPositionLabel, [cursorPositionLabel](const QPointF &position) {
            cursorPositionLabel->setText(QString("Cursor X: %1mm  Y: %2mm").arg(position.x() * 1000.0, 0, 'f', 0).arg(position.y() * 1000.0, 0, 'f', 0));
        });
    connect(canvas, &Canvas::scaleChanged,
        this, &MainWindow::updateScale);
    connect(canvas, &Canvas::offsetChanged,
        this, &MainWindow::updateOffset);

    // Update the status bar with the initial values from the canvas
    updateScale(canvas->scale());
    updateOffset(canvas->offset());

    // Load our sample plan
    loadFile("data/McKeefry.json");
    canvas->setPlan(currentPlan_);
    updateCurrentLevel(canvas->currentLevel());

    statusBar()->showMessage("Ready");
}

void MainWindow::updateScale(double scale)
{
    scaleLabel_->setText(QString("Scale: %1 px/m").arg(scale, 0, 'f', 2));
}

void MainWindow::updateOffset(const QPointF &offset)
{
    offsetLabel_->setText(QString("Offset X: %1mm  Y: %2mm").arg(offset.x() * 1000.0, 0, 'f', 0).arg(offset.y() * 1000.0, 0, 'f', 0));
}

void MainWindow::wallSelected(const Wall &wall)
{
    qInfo() << "Wall selected in MainWindow: " << wall.id();
    selectedWall_ = &wall;
    selectedItemLabel_->setText(QString("Selected Wall: %1").arg(wall.id()));
}

void MainWindow::loadFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open file for reading:" << file.errorString();
        return;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    if (!jsonDoc.isObject()) {
        qWarning() << "Invalid JSON format in file:" << filePath;
        return;
    }
    QJsonObject jsonObj = jsonDoc.object();
    auto planResult = Plan::fromJson(jsonObj);
    if (!planResult) {
        qWarning() << "Failed to load plan from JSON:" << planResult.error();
        return;
    }
    qInfo() << "Successfully loaded plan from JSON:" << filePath;

    currentPlan_ = new Plan(planResult.value());
}

void MainWindow::updateCurrentLevel(int level)
{
    qDebug() << "Updating current level to:" << level;
    qDebug() << "Current plan:" << currentPlan_;
    qDebug() << "Max level:" << (currentPlan_ ? currentPlan_->maxLevel() : -1);
    qDebug() << "Min level:" << (currentPlan_ ? currentPlan_->minLevel() : -1);
    upAction_->setEnabled(currentPlan_ && level < currentPlan_->maxLevel());
    downAction_->setEnabled(currentPlan_ && level > currentPlan_->minLevel());
    currentLevelLabel_->setText(QString("Level %1 ").arg(level));
}