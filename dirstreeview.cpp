#include "dirstreeview.h"

#include <QFileSystemModel>
#include <QDebug>

DirsTreeView::DirsTreeView(QWidget *parent)
    : QTreeView(parent)
{
    QFileSystemModel *model = new QFileSystemModel();
    model->setFilter(QDir::AllDirs | QDir::NoDot | QDir::NoDotDot);
    qDebug() << QDir::homePath();
    model->setRootPath(QDir::homePath());
    setModel(model);
    setHeaderHidden(true);
    setColumnHidden(1, true);
    setColumnHidden(2, true);
    setColumnHidden(3, true);
}

void DirsTreeView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    if (selected.indexes().count() > 0)
        emit dirChanged(selected.indexes().at(0).
                    data(QFileSystemModel::FilePathRole).toString());
    QTreeView::selectionChanged(selected, deselected);
}
