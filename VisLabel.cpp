#include "VisLabel.hpp"

#include <QTextCursor>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

VisLabel::VisLabel(QString text, QGraphicsItem* parent)
    : QGraphicsTextItem(text, parent)
{
    setFlags(ItemIsSelectable | ItemIsMovable | ItemIsFocusable);
    setTextInteractionFlags(Qt::NoTextInteraction);
    setZValue(30);

    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
}

void VisLabel::set_highlight(int r,int g,int b,int a)
{
    highlight_color = QColor(r,g,b,a);
    is_highlighted = true;
}

void VisLabel::set_unhighlighted()
{
    is_highlighted = false;
}

void VisLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(toPlainText() != ""){
        if(is_highlighted){
            painter->setBrush(QBrush(highlight_color));
            painter->drawRect(boundingRect());
        }else{
            painter->setBrush(QBrush(QColor(255,255,255,150)));
            painter->drawRect(boundingRect());
        }
    }
    QGraphicsTextItem::paint(painter, option, widget);
}

void VisLabel::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *evt)
{
    if(textInteractionFlags() == Qt::TextEditorInteraction)
    {
        QGraphicsTextItem::mouseDoubleClickEvent(evt);
        return;
    }
    setTextInteraction(true);
    QGraphicsSceneMouseEvent *click = new QGraphicsSceneMouseEvent(QEvent::GraphicsSceneMousePress);
    click->setButton(evt->button());
    click->setPos(evt->pos());
    QGraphicsTextItem::mousePressEvent(click);
    delete click;
}

void VisLabel::setTextInteraction(bool on, bool selectAll)
{
    if(on && textInteractionFlags() == Qt::NoTextInteraction){
        setTextInteractionFlags(Qt::TextEditorInteraction);
        setFocus(Qt::MouseFocusReason);
        setSelected(true);
        if(selectAll){
            QTextCursor c = textCursor();
            c.select(QTextCursor::Document);
            setTextCursor(c);
        }
    }
    else if(!on && textInteractionFlags() == Qt::TextEditorInteraction){
        setTextInteractionFlags(Qt::NoTextInteraction);
        QTextCursor c = this->textCursor();
        c.clearSelection();
        this->setTextCursor(c);
        clearFocus();
    }
}

QVariant VisLabel::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemSelectedChange && textInteractionFlags() != Qt::NoTextInteraction && !value.toBool()){
        setTextInteraction(false); // leave editor mode
    }
    return QGraphicsTextItem::itemChange(change, value);
}
