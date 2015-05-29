#ifndef SCANDIRTHREAD_HPP
#define SCANDIRTHREAD_HPP

#include <QObject>
#include <QStringList>
#include <QThread>

#include <memory>

class scanDirThread : public QThread
{
    Q_OBJECT
public:
    explicit scanDirThread(QObject *parent = nullptr);    
    scanDirThread(scanDirThread const&) = delete;
    scanDirThread& operator=(scanDirThread const&) = delete;

    QStringList get_result_dirs() const Q_DECL_NOEXCEPT;

    void set_scan_dir(QString dir) Q_DECL_NOEXCEPT;

signals:
    /**
     * @brief scan_dir this signal will emit when dir was scanned
     * @param dir scanned directory
     * @param msec The longest time(milli seconds) to show the message
     */
    void scan_dir(QString dir, int msec);
    void end();

private:
    void run() override;

private:
    QString dir_;
    QStringList result_dirs_;
};

#endif // SCANDIRTHREAD_HPP
