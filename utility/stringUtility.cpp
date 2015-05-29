#include "stringUtility.hpp"

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

/**
 * @brief prepend the match string with specify symbol
 * @param input string need to prepend symbol
 * @param number_length the length of the number, will prepend symbol
 * if the length smaller than this number
 * @param symbol symbol prepand before the number
 * @return the name after alter
 * @example ex : number_length == 3, reg = (\\d+), symbol = '0'
 * then "1" == "001", "10" == "010"
 * ex : number_length == 2, reg = (\\d+), symbol = '0'
 * then "1" == "01", "10" == "10"
 */
QString prepend_symbol_on_match(QString const &input, int number_length,
                                QRegularExpression const &reg,
                                QChar symbol)
{    
    auto new_file_name = input;
    auto match = reg.match(new_file_name);

    if(match.hasMatch()){
        auto const Captured = match.captured(0);
        if(Captured.size() < number_length){
            new_file_name.insert(match.capturedStart(0),
                                 QString(number_length - match.capturedLength(1),
                                         symbol));
        }
    }

    return new_file_name;
}

/**
 * @brief prepend the match string with specify symbol
 * @param input string needed to rename
 * @param number_length the length of the number, will prepend symbol
 * if the length smaller than this number
 * @param symbol symbol prepand before the number
 * @return the name after alter
 * @example ex : number_length == 3, reg = (\\d+), symbol = '0'
 * then "1" == "001", "10" == "010"
 * ex : number_length == 2, reg = (\\d+), symbol = '0'
 * then "1" == "01", "10" == "10"
 */
QStringList prepend_symbol_on_match(QStringList const &input, int number_length,
                                    QRegularExpression const &reg, QChar symbol)
{    
    QStringList new_file_names = input;
    for(int i = 0; i != new_file_names.size(); ++i){
        new_file_names[i] = prepend_symbol_on_match(input[i], number_length,
                                                    reg, symbol);
    }

    return new_file_names;
}

/**
 * @brief prepend symbol on nth match
 * @param input input string
 * @param number_length the length of the number, will prepend symbol
 * if the length smaller than this number
 * @param nth the number of match
 * @param reg the pattern want to find
 * @param symbol symbol prepand before the number
 * @return the input after symbol prepend if match the condition; if the reg
 * found the match pattern but the target length less than number_length, do nothing;
 * if reg do not find any match, return "the number of match is out of range
 * or found no match in this string"
 */
QString prepend_symbol_on_nth_match(QString const &input, int number_length,
                                    int nth, const QRegularExpression &reg, QChar symbol)
{
    auto it = reg.globalMatch(input);
    QRegularExpressionMatch match;
    int count = 0;

    while (it.hasNext()){
        match = it.next();
        if(count == nth){
            if(match.hasMatch()){
                QString new_file_name = input;
                if(!match.captured(1).isEmpty()){
                    if(match.capturedLength(0) < number_length){
                        new_file_name.insert(match.capturedStart(0),
                                             QString(number_length - match.capturedLength(0),
                                                     symbol));
                    }
                }
                return new_file_name;
            }else{
                break;
            }
        }
        ++count;
    }

    return "the number of match is out of range or found no match in this string";
}

/**
 * @brief prepend symbol on nth match
 * @param input input string
 * @param number_length the length of the number, will prepend symbol
 * if the length smaller than this number
 * @param nth the number of match
 * @param reg the pattern want to find
 * @param symbol symbol prepand before the number
 * @return the input after symbol prepend if match the condition; if the reg
 * found the match pattern but the target length less than number_length, do nothing;
 * if reg do not find any match, return "the number of match is out of range
 * or not match in this string"
 */
QStringList prepend_symbol_on_nth_match(QStringList const &input, int number_length,
                                        int nth, const QRegularExpression &reg, QChar symbol)
{
    auto new_file_names = input;
    for(int i = 0; i != new_file_names.size(); ++i){
        new_file_names[i] = prepend_symbol_on_nth_match(input[i], number_length,
                                                        nth, reg, symbol);
    }

    return new_file_names;
}
