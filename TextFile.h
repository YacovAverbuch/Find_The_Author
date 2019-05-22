//
// Created by Yacov Averbuch on 22/12/2018.
//

#ifndef EX2_TEXTFILE_H
#define EX2_TEXTFILE_H

#include <vector>
#include <unordered_map>

/**
 * represent text file with vector of num of appearance of a given f.w.
 */
class TextFile
{
public:
    /**
     * constructor
     * @param fileStream file stream
     * @param fileName string
     * @param wordsToSearch the map of the f.w. to search
     */
    TextFile(std::ifstream& fileStream, const std::string & fileName, const std::unordered_map<std::string, int>& wordsToSearch);

    /**
     * calculate the cos of the angle between the vector of the word frequency of the other file and this file
     * @param otherTextFile other file
     * @return double between 0 to 1
     */
    double calculateCos(const TextFile& otherTextFile) const;

    /**
     *
     * @return name
     */
    std::string getName() const { return fileName; }

    /**
     *
     * @return the vector of the f.w. counter
     */
    const std::vector<int> & getCounter() const { return wordsCounter; }

    /**
     *
     * @return the norm of the f.w. counter vector
     */
    double getNorm() const { return norm; }


    /**
     * extract the words from the file and for each word, if it appear  in the map of frequent word, it add
     * 1 to the file vector of f.w. appearance.
     * @param file the file stream we analyze
     */
    void findWords(std::ifstream& fileStream);


private:

    const std::string & fileName;
    const std::unordered_map<std::string, int> & wordsToSearch;
    std::vector<int> wordsCounter;
    double norm;

};

#endif //EX2_TEXTFILE_H
