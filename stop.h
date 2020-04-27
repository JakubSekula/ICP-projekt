#ifndef STOP_H
#define STOP_H

#include <QString>
#include <QDebug>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QGraphicsItem>

class stop : public QGraphicsItem
{

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    QString name;
    QString id;

public:
    stop();
    void initialize( QString identif, QString name );
    QString getName();
    QRectF midd;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // STOP_H
