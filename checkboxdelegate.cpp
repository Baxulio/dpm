#include "checkboxdelegate.h"

CheckBoxDelegate::CheckBoxDelegate(QObject *parent ):QItemDelegate(parent)
{

    checkBoxColumnIx = 1;
}

void CheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if (index.column() ==checkBoxColumnIx)
    {
        QWidget *w = dynamic_cast<QWidget *>(painter->device());
        if (w)
        {
            QItemDelegate::drawBackground( painter, option, index );

            drawCheck( painter, option, QRect(option.rect.left()+(option.rect.width()-15)/2,option.rect.top()+(option.rect.height()-15)/2,15,15), index.data(Qt::EditRole).toBool() ? Qt::Checked : Qt::Unchecked );
            drawFocus(painter, option, option.rect);
        }
        else
            QItemDelegate::paint(painter, option, index);
    }
}

QWidget *CheckBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == checkBoxColumnIx)
    {
        QCheckBox* chb = new QCheckBox(parent);
        //this->connect(chb,SIGNAL(toggled(bool)),SIGNAL(rowChecked(bool,index,option)));
        //chb->setStyleSheet("QCheckBox {margin-left: 37%; margin-right: 53%; margin:5px;}");
        return chb;
    }

    return QItemDelegate::createEditor(parent, option, index);
}

void CheckBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() == checkBoxColumnIx)
    {
        int checked = index.model()->data(index, Qt::DisplayRole).toInt();
        QCheckBox* chb = qobject_cast<QCheckBox*>(editor);
        chb->setChecked(checked == 1);
    } else
        QItemDelegate::setEditorData(editor, index);
}

void CheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.column() == checkBoxColumnIx)
    {
        QCheckBox* chb = qobject_cast<QCheckBox*>(editor);
        int value;
        if(chb->isChecked()){
            value= 1;
        }
        else{
            value=0;
        }

        model->setData(index, value);
    }
    else
        QItemDelegate::setModelData(editor, model, index);
}
void CheckBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(QRect(option.rect.left()+(option.rect.width()-15)/2,option.rect.top()+(option.rect.height()-15)/2,15,15));
}

void CheckBoxDelegate::commitAndCloseEditor()
{
    QCheckBox* editor = qobject_cast<QCheckBox*>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
bool CheckBoxDelegate::editorEvent(QEvent * event, QAbstractItemModel * model,
                                   const QStyleOptionViewItem & option, const QModelIndex & index)
{
    Q_UNUSED(option);
    if (index.column()==checkBoxColumnIx && event->type()==QEvent::MouseButtonPress){

        if(index.data(Qt::DisplayRole).toInt()==0)
        {
            model->setData(index,1);
            emit rowChecked(index);
        }
        else
            model->setData(index,0);

        return true;
    }
    return false;
}
