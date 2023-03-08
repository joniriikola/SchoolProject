#include "autocompleter.h"

AutoCompleter::AutoCompleter(QObject* parent) : QObject(parent)
{
}

void AutoCompleter::openDictionary(const QString& filePath)
{
    m_dictionaryFile.setFileName(filePath);

    if (!m_dictionaryFile.open(QIODevice::ReadOnly))
    {
        qWarning() << "Autocompletion is disabled.";
        qWarning() << "Reason: Cant open dictionary for reading:" << filePath;
        return;
    }

    auto fileContents = m_dictionaryFile.readAll();
    auto split = fileContents.split(',');
    m_dictionary = QSet<QString>(split.begin(), split.end());
    m_dictionaryFile.close();

    if (!m_dictionaryFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qWarning() << "Autocompletion adaptation is disabled.";
        qWarning() << "Reason: Cant open dictionary for writing:" << filePath;
        return;
    }
}

QString AutoCompleter::getSuggestion(const QString& string) const
{
    QString cmpString = string.toLower();
    QString suggestion;
    size_t suggestionLed = std::numeric_limits<size_t>::max();

    for (const auto& word : m_dictionary)
    {
        if (word.startsWith(cmpString) || cmpString == word)
        {
            auto led = levenshteinDist(cmpString, word);
            if (led < suggestionLed)
            {
                suggestion = word;
                suggestionLed = led;
            }
        }
    }

    suggestion.replace(cmpString, string);
    return suggestion;
}

void AutoCompleter::addSuggestion(const QString& suggestion)
{
    QString suggestionLower = suggestion.toLower();
    if (m_dictionaryFile.isOpen() && !m_dictionary.contains(suggestionLower))
    {
        m_dictionary.insert(suggestionLower);
        m_dictionaryFile.write(suggestionLower.prepend(',').toUtf8());
    }
}

size_t AutoCompleter::levenshteinDist(const QString& string1, const QString& string2) const
{
    const auto size1 = string1.size();
    const auto size2 = string2.size();

    if (size1 == 0)
    {
        return size2;
    }

    if (size2 == 0)
    {
        return size1;
    }

    std::vector<size_t> costs(size2 + 1);
    std::iota(costs.begin(), costs.end(), 0);
    size_t i = 0;
    for (auto c1 : string1)
    {
        costs[0] = i + 1;
        size_t corner = i;
        size_t j = 0;
        for (auto c2 : string2)
        {
            size_t upper = costs[j + 1];
            costs[j + 1] = (c1 == c2) ? corner : 1 + std::min(std::min(upper, corner), costs[j]);
            corner = upper;
            ++j;
        }
        ++i;
    }
    return costs[size2];
}
