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

private slots:
    void on_btnSelect_clicked();
    void on_btnBack_clicked();

private:
    void installRecursive(QWidget* root);
    void setSelectedPair(QWidget* on, QWidget* off);
    void applySelected(QWidget* widget, const char* prop, bool on);
    bool eventFilter(QObject* obj, QEvent* event);

private:
    Ui::Style* m_ui;
};
