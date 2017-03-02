#ifndef DIRIMAGESMODEL_H
#define DIRIMAGESMODEL_H

#include <QAbstractListModel>
#include <QtConcurrent>

/**
 * @brief The DirImagesModel class
 * Contains all images from selected directory
 * Uses multi threading for loading images and scaling
 */

class DirImagesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit DirImagesModel(QObject *parent = nullptr);
    virtual ~DirImagesModel();

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

public slots:
    void setPath(const QString &path);

signals:
    void progressRangeChanged(int minimum, int maximum);
    void progressValueChanged(int progressValue);

private slots:
    void onResultReadyAt(int r);

private:
    QStringList m_data;
    QFutureWatcher<QImage> *m_imageScaling;
};

#endif // DIRIMAGESMODEL_H
