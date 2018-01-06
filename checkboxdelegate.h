#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QApplication>
#include <QItemDelegate>
#include <QCheckBox>
#include <QPainter>

class CheckBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    CheckBoxDelegate(QObject *parent = 0);

    void paint( QPainter *painter,
                        const QStyleOptionViewItem &option,
                        const QModelIndex &index ) const;


    QWidget *createEditor( QWidget *parent,
                        const QStyleOptionViewItem &option,
                        const QModelIndex &index ) const;

    void setEditorData( QWidget *editor,
                        const QModelIndex &index ) const;

    void setModelData( QWidget *editor,
                        QAbstractItemModel *model,
                        const QModelIndex &index ) const;

    void updateEditorGeometry( QWidget *editor,
                        const QStyleOptionViewItem &option,
                        const QModelIndex &index ) const;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

    int checkBoxColumnIx;

signals:
    void rowChecked(QModelIndex);

public slots:

    void commitAndCloseEditor();
};

#endif // CHECKBOXDELEGATE_H
