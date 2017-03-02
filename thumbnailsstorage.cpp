#include "thumbnailsstorage.h"

#include <QDebug>

ThumbnailsStorage *ThumbnailsStorage::instance()
{
    static ThumbnailsStorage *g_thumbnailsStorageInstance = 0;
    if (!g_thumbnailsStorageInstance)
        g_thumbnailsStorageInstance = new ThumbnailsStorage();
    return g_thumbnailsStorageInstance;
}

ThumbnailsStorage::ThumbnailsStorage(QObject *parent) : QObject(parent)
{

}

void ThumbnailsStorage::init(int size)
{
    m_images.clear();
    m_images.resize(size);
}

const QImage &ThumbnailsStorage::image(int n) const
{
    return m_images[n];
}

void ThumbnailsStorage::setImage(int n, const QImage &img)
{
    m_images[n] = img;
    //qDebug() << "n " << n << " - " << m_images[n].isNull();
}
