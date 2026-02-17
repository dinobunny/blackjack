#pragma once
#include <type_traits>
#include <QWidget>

namespace blackjack
{
    template<typename T>
    concept QWidgetDerived = std::is_base_of_v<QWidget, T>;

    template<QWidgetDerived T>
    void NavigateTo(QWidget* current, bool deleteOnClose = false)
    {
        auto* next = new T();
        next->show();

        if (deleteOnClose)
            current->setAttribute(Qt::WA_DeleteOnClose);

        current->close();
    }
}// namespace blackjack
