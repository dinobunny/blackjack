#include "animation.h"
#include <QPixmap>
#include <QPropertyAnimation>

namespace blackjack
{

    Animator::Animator(QObject* parent)
        : QObject(parent)
    {
    }

    QLabel* Animator::CreateChip(QWidget* parent, const QString& path)
    {
        auto* chip = new QLabel(parent);
        QPixmap chipPix(path);

        chip->setPixmap(chipPix);
        chip->resize(chipPix.size());
        chip->show();

        return chip;
    }

    void Animator::AnimateMove(QLabel* chip, const QPoint& start, const QPoint& end, int duration)
    {
        auto* anim = new QPropertyAnimation(chip, "pos");

        anim->setDuration(duration);
        anim->setStartValue(start);
        anim->setEndValue(end);

        connect(anim, &QPropertyAnimation::finished, this, &Animator::Finished);

        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }

}
