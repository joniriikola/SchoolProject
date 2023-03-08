#pragma once

#include <algorithm>
#include <limits>

#include <QDebug>
#include <QFile>
#include <QObject>
#include <QSet>

/**
 * @brief AutoCompleter is a class that provides completion suggestions based on
 * given strings. It also allows updating database of suggestions.
 */
class AutoCompleter : public QObject
{
public:
    /**
     * @brief Constructor.
     * @param parent: Pointer to parent QObject.
     */
    explicit AutoCompleter(QObject* parent = nullptr);
    /**
     * @brief Reads given file to internal memory and uses values in file as suggestion database
     * @param filePath: Path to csv file of suggestions.
     */
    void openDictionary(const QString& filePath);
    /**
     * @brief Returns a suggestion based on parameter string. Suggestion must start with given
     * string and is then one with lowest levenshtein distance to given string.
     * @param string: Basis for suggestion.
     * @return QString: Suggestion.
     */
    QString getSuggestion(const QString& string) const;
    /**
     * @brief Adds given suggestion to dictionary opened prior with openDictionary().
     * @param suggestion: Suggestion to be added to suggestions.
     */
    void addSuggestion(const QString& suggestion);

private:
    /**
     * @brief Calculates Levenshtein Distance between given strings
     * @param string1: First string.
     * @param strgin2: Second string.
     * @return size_t: Levenshtein distance between string1 and string2.
     */
    size_t levenshteinDist(const QString& string1, const QString& string2) const;
    QFile m_dictionaryFile;
    QSet<QString> m_dictionary;
};
