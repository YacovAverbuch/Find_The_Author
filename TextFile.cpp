//
// Created by Yacov Averbuch on 22/12/2018.
//

#include "TextFile.h"

#include <iostream>
#include <fstream>

#include <math.h>
#include <string>
#include <algorithm>

#include <boost/tokenizer.hpp>


/**
 * constructor.
 * @param fileStream file stream
 * @param fileName a string
 * @param wordsToSearch the map of words to search
 */
TextFile::TextFile(std::ifstream& fileStream, const std::string & fileName, const std::unordered_map<std::string, int>& wordsToSearch) :
                    wordsToSearch(wordsToSearch), wordsCounter(wordsToSearch.size()), fileName(fileName)
{
    findWords(fileStream);
    double sum = 0;
    for (auto num : wordsCounter)
    {
        sum += pow(num, 2);
    }
    norm = sqrt(sum);
}

/**
 * calculate the cos of the angle between the vector of the word frequency of the other file and this file
 * @param otherTextFile other file
 * @return double between 0 to 1
 */
double TextFile::calculateCos(const TextFile& otherTextFile) const
{
    const std::vector<int> & otherFileCounter = otherTextFile.getCounter();
    double sum = 0;
    for (int i = 0; i < wordsCounter.size(); i++)
    {
        sum += wordsCounter[i] * otherFileCounter[i];
    }
    if (norm == 0 | otherTextFile.getNorm() == 0)
    {
        return 0;
    }
    return sum / (norm * otherTextFile.getNorm());
}

/**
 * extract the words from the file and for each word, if it appear  in the map of frequent word, it add
 * 1 to the file vector of f.w. appearance.
 * @param file the file stream we analyze
 */
void TextFile::findWords(std::ifstream & file)
{
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    boost::char_separator<char> sep{",!:;\"\n\r "};
    std::string curLine;

    while (std::getline(file, curLine))
    {

        tokenizer tok{curLine, sep};
        for (auto word : tok)
        {
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            const auto cur_it = wordsToSearch.find(word);
            if (cur_it != wordsToSearch.cend())
            {
                wordsCounter[cur_it->second] += 1;
            }
        }
    }
}

