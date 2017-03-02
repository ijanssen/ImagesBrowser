#ifndef THUMBNAILSSTORAGE_H
#define THUMBNAILSSTORAGE_H

#include <QObject>
#include <QImage>

/**
 * @brief Thumbnails storage class with static instance
 * Storage for all thumbnails
 */

class ThumbnailsStorage : public QObject
{
    Q_OBJECT
public:
    static ThumbnailsStorage *instance();

    explicit ThumbnailsStorage(QObject *parent = 0);

    void init(int size);
    const QImage &image(int n) const;

    void setImage(int n, const QImage &img);

private:
    QVector<QImage> m_images;
};

#endif // THUMBNAILSSTORAGE_H
