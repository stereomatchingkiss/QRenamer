#ifndef STRINGUTILITY_HPP
#define STRINGUTILITY_HPP

#include <QChar>
#include <QStringList>

class QRegularExpression;

QString prepend_symbol_on_match(QString const &old_file_name,
                                     int number_length,
                                     QRegularExpression const &reg,
                                     QChar symbol);

QStringList prepend_symbol_on_match(QStringList const &input,
                                         int number_length,
                                         QRegularExpression const &reg,
                                         QChar symbol);

QString prepend_symbol_on_nth_match(QString const &input,
                                    int number_length,
                                    int nth,
                                    QRegularExpression const &reg,
                                    QChar symbol);

QStringList prepend_symbol_on_nth_match(QStringList const &input,
                                        int number_length,
                                        int nth,
                                        QRegularExpression const &reg,
                                        QChar symbol);

#endif // STRINGUTILITY_HPP
