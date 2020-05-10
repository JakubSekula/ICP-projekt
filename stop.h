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

    /**
     * @brief stop::boundingRect Vytvori kruh, znacku zastavky
     * @return  Vracia objekt, kruh
     */
    QRectF boundingRect() const override;

    /**
     * @brief stop::paint Vykreslenie kruhu
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    QString name;
    QString id;

public:
    stop();

    /**
     * @brief stop::initialize Nastavenie ID a mena zastavky
     * @param identif
     * @param name
     */
    void initialize( QString identif, QString name );

    /**
     * @brief stop::getName
     * @return Vrati meno zastavky
     */
    QString getName();

    /**
     * @brief stop::getID
     * @return Vrati ID zastavky
     */
    QString getID();
    QRectF midd;
};

#endif // STOP_H
