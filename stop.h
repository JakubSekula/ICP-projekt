/******************************************************************************
 * Projekt: Aplikace zobrazující autobusovou dopravu                          *
 * Předmet: Seminář C++ - FIT VUT v Brně                                      *
 * Rok:     2019/2020                                                         *
 * Autoři:                                                                    *
 *          Jakub Sekula (xsekul01) - xsekul00@stud.fit.vutbr.cz              *
 *          Ondrej Potúček (xpotuc06) - xpotuc06@stud.fit.vutbr.cz            *
 ******************************************************************************/

/**
 * @file stop.h
 * @author Jakub Sekula (xsekul01)
 * @author Ondrej Potúček (xpotuc06)
 * @date 10.05.2020
 * @brief Informace o zastávkách
 */

#ifndef STOP_H
#define STOP_H

#include <QString>
#include <QDebug>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QGraphicsItem>

/**
 * @brief The stop class Informace o zastávkách
 */
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
};

#endif // STOP_H
