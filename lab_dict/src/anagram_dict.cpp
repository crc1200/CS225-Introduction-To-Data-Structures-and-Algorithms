/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;
#include <iostream>

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
            std::string keyWord = word;
            std::sort(keyWord.begin(), keyWord.end());
            if (dict.find(keyWord) != dict.end()) {
                std::vector<std::string> vals = dict.at(keyWord);
                vals.push_back(word);
                dict.at(keyWord) = vals;
            } else {
                std::vector<std::string> vals;
                vals.push_back(word);
                dict.insert({keyWord, vals});
                
            }
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words) {
    for (std::string w : words) {
        std::string keyWord = w;
        std::sort(keyWord.begin(), keyWord.end());
        if (dict.find(keyWord) != dict.end()) {
            std::vector<std::string> vals = dict.at(keyWord);
            vals.push_back(w);
            dict.at(keyWord) = vals;
        } else {
            std::vector<std::string> vals;
            vals.push_back(w);
            dict.insert({keyWord, vals});
        }
    }
    
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    std::string key = word;
    std::sort(key.begin(), key.end());

    if (dict.find(key) == dict.end() || dict.at(key).size() == 0) {
        std::vector<std::string> res;
        return res; 
    }
    return dict.at(key);
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    std::vector<std::vector<std::string>> res;
    for (auto m = dict.begin(); m != dict.end(); m++) {
        if (m -> second.size() > 1) {
            res.push_back(m -> second);     
        }
        
    }
    return res;
}
