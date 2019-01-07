#ifndef RICHTEXTDELEGATE_H
#define RICHTEXTDELEGATE_H

#include <QStyledItemDelegate>
#include <QTextDocument>
#include <QPainter>
#include <QAbstractTextDocumentLayout>

class RichTextDelegate : public QStyledItemDelegate
{
public:
    RichTextDelegate();

protected:
    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};

#endif // RICHTEXTDELEGATE_H
