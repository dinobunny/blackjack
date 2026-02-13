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

    void OnAnimFinished();
private slots:
    void on_btnStyle_clicked();

private:
    Ui::Style* ui;
};
