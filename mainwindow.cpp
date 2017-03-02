#include "mainwindow.h"

#include <QVBoxLayout>
#include <QSplitter>
#include <QProgressBar>
#include <QTreeView>
#include "imagesview.h"
#include "dirimagesmodel.h"
#include "dirstreeview.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QObject::tr("Images Browser"));
    resize(800, 600);

    QWidget *widget = new QWidget(parent);
    QSplitter *splitter = new QSplitter(widget);
    QProgressBar *m_progressBar = new QProgressBar(widget);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(splitter);
    layout->addWidget(m_progressBar);
    widget->setLayout(layout);
    setCentralWidget(widget);

    DirsTreeView *dirsView = new DirsTreeView();
    ImagesView *imagesView = new ImagesView();
    splitter->addWidget(dirsView);
    splitter->addWidget(imagesView);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);

    DirImagesModel *dirModel = new DirImagesModel(this);
    imagesView->setModel(dirModel);

    connect(dirsView, &DirsTreeView::dirChanged, dirModel, &DirImagesModel::setPath);
    connect(dirsView, &DirsTreeView::dirChanged, this, &MainWindow::setPath);
    connect(dirModel, SIGNAL(progressRangeChanged(int,int)), m_progressBar, SLOT(setRange(int,int)));
    connect(dirModel, SIGNAL(progressValueChanged(int)), m_progressBar, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::setPath(const QString &path)
{
    setWindowTitle(QObject::tr("Images Browser (%1)").arg(path));
}
