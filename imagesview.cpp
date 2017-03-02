#include "imagesview.h"

#include <QPainter>
#include <QScrollBar>
#include <QResizeEvent>
#include <QDebug>

#include "thumbnailsstorage.h"

const int max_icon_size = 200;
const int min_icon_size = 50;
const int step_icon_size = 20;

ImagesView::ImagesView(QWidget *parent)
    : QAbstractItemView(parent)
    , m_spacing(10)
    , m_iconSize(200)
{
    setMinimumWidth(300);
    horizontalScrollBar()->setRange(0, 0);
    verticalScrollBar()->setRange(0, 0);
}

QRect ImagesView::visualRect(const QModelIndex &index) const
{
    int r = index.row();
    int c = r % m_columns;
    r /= m_columns;
    return QRect(m_spacing + c * (m_iconSize + m_spacing) - horizontalScrollBar()->value(),
                 m_spacing + r * (m_iconSize + m_spacing) - verticalScrollBar()->value(),
                 m_iconSize, m_iconSize);
}

void ImagesView::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint)
{
    Q_UNUSED(index);
    Q_UNUSED(hint);
    // No implementation for this case
}

QModelIndex ImagesView::indexAt(const QPoint &point) const
{
    Q_UNUSED(point);
    // No implementation for this case
    return QModelIndex();
}

QModelIndex ImagesView::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(cursorAction);
    Q_UNUSED(modifiers);
    // No implementation for this case
    return QModelIndex();
}

int ImagesView::horizontalOffset() const
{
    return 0;
}

int ImagesView::verticalOffset() const
{
    return verticalScrollBar()->value();
}

bool ImagesView::isIndexHidden(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return false;
}

void ImagesView::setSelection(const QRect &, QItemSelectionModel::SelectionFlags command)
{
    Q_UNUSED(command);
    // No implementation for this case
}

void ImagesView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    //qDebug() << "paint " << event->rect();
    QPainter painter(viewport());
    painter.setPen(Qt::black);
    //painter.setRenderHints(QPainter::Antialiasing);
    int rs = (verticalScrollBar()->value() - m_spacing) / (m_iconSize + m_spacing);
    //qDebug() << "RS = " << rs;
    rs *= m_columns;
    int re = (verticalScrollBar()->value() + viewport()->height()) / (m_iconSize + m_spacing) + 1;
    //qDebug() << "RE = " << re;
    re *= m_columns;
    for (int row = rs; row < qMin(re, model()->rowCount(rootIndex())); ++row) {
        QModelIndex index = model()->index(row, 0, rootIndex());
        QRect rect = visualRect(index);
        painter.drawRect(rect.adjusted(-1, -1, 0, 0));
        //qDebug() << rect.size();

        const QImage &img = ThumbnailsStorage::instance()->image(row);
        if (img.isNull())
            painter.fillRect(rect, Qt::lightGray);
        else {
            QImage simg = img.scaled(QSize(m_iconSize, m_iconSize),
                                Qt::KeepAspectRatio, Qt::SmoothTransformation);
            int x = rect.x();
            int y = rect.y();
            if (simg.width() < m_iconSize)
                x += (m_iconSize - simg.width()) / 2;
            if (simg.height() < m_iconSize)
                y += (m_iconSize - simg.height()) / 2;
            painter.drawImage(x, y, simg);
        }
        //QStyleOptionViewItem option = viewOptions();
        //option.rect = rect;
        //itemDelegate()->paint(&painter, option, index);
    }

}

void ImagesView::resizeEvent(QResizeEvent *event)
{
    doLayout();
    updateGeometries();
    QAbstractItemView::resizeEvent(event);
}

QRegion ImagesView::visualRegionForSelection(const QItemSelection &selection) const
{
    Q_UNUSED(selection);
    return QRegion();
}

void ImagesView::wheelEvent(QWheelEvent *event)
{
    m_iconSize += step_icon_size * event->angleDelta().y() / 120;
    if (m_iconSize > max_icon_size)
        m_iconSize = max_icon_size;
    if (m_iconSize < min_icon_size)
        m_iconSize = min_icon_size;
    doLayout();
    updateGeometries();
    viewport()->update();
}

void ImagesView::doLayout()
{
    m_columns = (viewport()->width() - m_spacing) / (m_iconSize + m_spacing);
}

void ImagesView::updateGeometries()
{
    int r = model()->rowCount(rootIndex());
    int l = r / m_columns + 1;
    int idealHeight = m_spacing + l * (m_spacing + m_iconSize);
    verticalScrollBar()->setSingleStep(20);
    verticalScrollBar()->setPageStep(viewport()->height());
    verticalScrollBar()->setRange(0,
          qMax(0, idealHeight - viewport()->height()));
}
