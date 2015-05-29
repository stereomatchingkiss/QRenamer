#ifndef QUICKCLOSESIGNAL_H
#define QUICKCLOSESIGNAL_H

#include <QQuickWidget>

class quickCloseSignal : public QQuickWidget
{
    Q_OBJECT
public:
    explicit quickCloseSignal(QWidget *parent = nullptr);
    ~quickCloseSignal();

signals:
    void widget_close();

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // QUICKCLOSESIGNAL_H
