#include "animation.h"
#include <QPixmap>
#include <QPropertyAnimation>

using namespace blackjack;

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

QLabel* Animator::CreateCenteredCard(QWidget* parent, QWidget* from, const QPixmap& px)
{
    QLabel* card = new QLabel(parent);
    card->setPixmap(px);
    card->resize(px.size());

    const QPoint start = from->mapTo(parent, QPoint(0, 0));
    const int offsetX = (from->width() - card->width()) / 2;
    const int offsetY = (from->height() - card->height()) / 2;
    const QPoint centered = start + QPoint(offsetX, offsetY);

    card->move(centered);
    card->show();
    card->raise();

    return card;
}

void Animator::AnimateCardTo(QLabel* flying, QLabel* target, int duration)
{
    QWidget* parentWindow = flying->parentWidget();
    if (!parentWindow)
        parentWindow = target->parentWidget();

    const QPoint end = target->mapTo(parentWindow, QPoint(0, 0));

    auto* anim = new QPropertyAnimation(flying, "pos", parentWindow);

    anim->setDuration(duration);
    anim->setStartValue(flying->pos());
    anim->setEndValue(end);
    anim->setEasingCurve(QEasingCurve::OutCubic);

    connect(anim, &QPropertyAnimation::finished, this, [flying, target] ()
            {
                target->setPixmap(flying->pixmap());
                flying->deleteLater();
            });

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}
