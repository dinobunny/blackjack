#pragma once
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Style;
}
QT_END_NAMESPACE

class Style : public QMainWindow
{
    Q_OBJECT

public:
    Style(QWidget* parent = nullptr);
    ~Style();

private:
    Ui::Style* ui;
};
