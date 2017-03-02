#ifndef IMAGESVIEW_H
#define IMAGESVIEW_H

#include <QAbstractItemView>

/**
 * @brief The ImagesView item view class
 * Has images grid with changable sizes (with mouse wheel)
 */

class ImagesView : public QAbstractItemView
{
    Q_OBJECT
public:
    ImagesView(QWidget *parent = nullptr);

    QRect visualRect(const QModelIndex &index) const Q_DECL_OVERRIDE;
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) Q_DECL_OVERRIDE;
    QModelIndex indexAt(const QPoint &point) const Q_DECL_OVERRIDE;

protected:
    QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction,
                           Qt::KeyboardModifiers modifiers) Q_DECL_OVERRIDE;

    int horizontalOffset() const Q_DECL_OVERRIDE;
    int verticalOffset() const Q_DECL_OVERRIDE;

    bool isIndexHidden(const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setSelection(const QRect&, QItemSelectionModel::SelectionFlags command) Q_DECL_OVERRIDE;

    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    QRegion visualRegionForSelection(const QItemSelection &selection) const Q_DECL_OVERRIDE;

    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

private:
    void doLayout();
    void updateGeometries();

    int m_spacing;
    int m_iconSize;
    int m_columns;
};

#endif // IMAGESVIEW_H
