#ifndef DIRSTREEVIEW_H
#define DIRSTREEVIEW_H

#include <QTreeView>

/**
 * @brief The DirsTreeView class
 * Tree view class with filesystem
 * Has signal for selected path
 */

class DirsTreeView : public QTreeView
{
    Q_OBJECT
public:
    DirsTreeView(QWidget *parent = nullptr);

signals:
    void dirChanged(const QString &path);

protected slots:
    virtual void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override;
};

#endif // DIRSTREEVIEW_H
