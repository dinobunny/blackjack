#pragma once

#include <QObject>
#include <QLabel>
#include <QPoint>

#include "utils/Config_Constants.h"

namespace blackjack
{
    class Animator : public QObject
    {
        Q_OBJECT

    public:
        explicit Animator(QObject* parent = nullptr);
        QLabel* CreateChip(QWidget* parent, const QString& path = kChipRedWhitePath);

        void AnimateMove(QLabel* widget, const QPoint& start, const QPoint& end, int duration);


        QLabel* CreateCenteredCard(QWidget* parentWindow,
                                   QWidget* fromWidget,
                                   const QPixmap& px);

        void AnimateCardTo(QLabel* flying,
                           QLabel* target,
                           int duration = 250);
    signals:
        void Finished();
    };

}