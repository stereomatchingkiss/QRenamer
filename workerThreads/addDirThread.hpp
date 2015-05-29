#ifndef ADDDIRTHREAD_HPP
#define ADDDIRTHREAD_HPP

#include <QObject>
#include <QStringList>
#include <QThread>

#include <memory>

class addDirThread : public QThread
{
    Q_OBJECT
public:
    explicit addDirThread(QObject *parent = nullptr);   
    addDirThread(addDirThread const&) = delete;
    addDirThread& operator=(addDirThread const&) = delete;

    QStringList get_old_file_name_complete() const;

    void set_dirs_to_scan(QStringList dirs);

signals:    
    void end();
    void increment(int value);

private:
    void run() override;

private:
    QStringList old_file_name_complete_;

    QStringList dirs_to_scan_;
};

#endif // ADDDIRTHREAD_HPP
