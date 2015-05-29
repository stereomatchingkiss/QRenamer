#include "quickCloseSignal.hpp"

quickCloseSignal::quickCloseSignal(QWidget *parent) :
    QQuickWidget(parent)
{

}

quickCloseSignal::~quickCloseSignal()
{

}

void quickCloseSignal::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit widget_close();
}

