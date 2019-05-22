

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <fstream>

#include "TextFile.h"


using string = std::string;

/**
 * extruct the words from the file and give each word a unique number
 * @param keywordFile the file
 * @param wordsMap the map to insert to
 * @return the map
 */
std::unordered_map<string, int> & parseKeywordFile(std::ifstream&  keywordFile, std::unordered_map<string, int> & wordsMap)
{
    string curWord;
    int numerator = 0;
    while(keywordFile >> curWord)
    {
        if (wordsMap.find(curWord) == wordsMap.end())
        {
            wordsMap[curWord] = numerator;
            numerator += 1;
        }
    }
    return wordsMap;
}

/**
 *
 * @param argc num of argv
 * @param argv the list of string represent the program arguments
 * @param wordsToSearch the map of words to search
 * @param unknownFileText the unknown file
 */
void parseAllFilesAndPrintScore(int argc, const char* argv[] , const std::unordered_map<string, int>  & wordsToSearch,
                                const TextFile & unknownFileText)
{
    std::pair<string, double> theGreatestScore("", 0.0);
    for (int i = 3; i < argc; i ++)
    {
        string curFileName = argv[i];
        std::ifstream curFile(curFileName);
        if (not curFile)
        {
            std::cerr << "ERROR: Cannot Open File '" << curFileName << "\n";
            continue;
        }
        TextFile curTextFile = TextFile(curFile, curFileName, wordsToSearch);
        double curFileScore = curTextFile.calculateCos(unknownFileText);

        std::cout << curTextFile.getName() << ' ' << curFileScore << std::endl;
        if (curFileScore > theGreatestScore.second)
        {
            theGreatestScore = std::make_pair(curFileName, curFileScore);
        }
    }
    if (theGreatestScore.second > 0)
    {

        std::cout << "Best matching author is " << theGreatestScore.first << " score " <<  theGreatestScore.second << '\n';
    }
}


/**
 * run the program
 * @param argv the list of string represent the program arguments
 * @param wordsToSearch the map of words to search
 * @return 0 in case of success. 1 if has less then 3 argument or cannot open the frequent words file or the unknown file
 */
int main(int argc, const char* argv[])
{
    if(argc < 4)
    {
        std::cerr << "ERROR: not enough parameters";
        return 1;
    }

    string wordsToVectorFileName = argv[1];
    std::ifstream keywordFile(wordsToVectorFileName);
    if (not keywordFile)
    {
        std::cerr << "ERROR: Cannot Open File '" << wordsToVectorFileName << "\n";
        return 1;
    }

    std::unordered_map<string, int> __words;  // init to send it as a parameter
    // each word has a unique value between (0 : num_of_words)
    const std::unordered_map<string, int> wordsToSearch = parseKeywordFile(keywordFile, __words);

    string unknownFileName = argv[2];
    std::ifstream unknownFile(unknownFileName);
    if (not unknownFile)
    {
        std::cerr << "ERROR: Cannot Open File '" << argv[2] << "\n";
        return 1;
    }
    TextFile unknownFileText = TextFile(unknownFile, unknownFileName, wordsToSearch);
    parseAllFilesAndPrintScore(argc, argv, wordsToSearch, unknownFileText);

    return 0;
}

