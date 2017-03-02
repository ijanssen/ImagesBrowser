#include "dirimagesmodel.h"

#include <QDir>
#include <QImage>
#include <QDebug>

#include "thumbnailsstorage.h"

class ScaleFunctor : public std::unary_function<QString, QImage>
{
public:
    ScaleFunctor(const QDir &dir)
        : m_dir(dir)
    {
    }
    QImage operator()(const QString &fn) {
        QImage image(m_dir.absoluteFilePath(fn));
        return image.scaled(QSize(200, 200),
                            Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
private:
    QDir m_dir;
};

DirImagesModel::DirImagesModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_imageScaling(new QFutureWatcher<QImage>(this))
{
    connect(m_imageScaling, SIGNAL(progressRangeChanged(int,int)), SIGNAL(progressRangeChanged(int,int)));
    connect(m_imageScaling, SIGNAL(progressValueChanged(int)), SIGNAL(progressValueChanged(int)));
    connect(m_imageScaling, SIGNAL(resultReadyAt(int)), this, SLOT(onResultReadyAt(int)));
}

DirImagesModel::~DirImagesModel()
{
    m_imageScaling->cancel();
    m_imageScaling->waitForFinished();
}

int DirImagesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int DirImagesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant DirImagesModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return m_data[index.row()];
    return QVariant();
}

void DirImagesModel::setPath(const QString &path)
{
    if (m_imageScaling->isRunning()) {
        m_imageScaling->cancel();
        m_imageScaling->waitForFinished();
    }
    QDir dir(path);
    QStringList filters {"*.png", "*.jpg", "*.jpeg", "*.bmp", "*.gif"};
    beginResetModel();
    m_data = dir.entryList(filters, QDir::Files);
    ThumbnailsStorage::instance()->init(m_data.size());
    //qDebug() << m_data.count();
    endResetModel();
    if (m_data.isEmpty()) {
        emit progressRangeChanged(0, 1);
        emit progressValueChanged(1);
    } else
        m_imageScaling->setFuture(QtConcurrent::mapped(m_data, ScaleFunctor(path)));
}

void DirImagesModel::onResultReadyAt(int r)
{
    ThumbnailsStorage::instance()->setImage(r, m_imageScaling->resultAt(r));
    QModelIndex idx = index(r, 0);
    emit dataChanged(idx, idx);
}
