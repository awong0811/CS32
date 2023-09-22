// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
#include <algorithm>
#include <vector>
using namespace std;

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

// This class does the real work of the implementation.

class DictionaryImpl
{
public:
    DictionaryImpl(int maxBuckets);
    ~DictionaryImpl();
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
private:
    unsigned int hash(string word) const;
    vector<list<string>*> m_words;
};

DictionaryImpl::DictionaryImpl(int maxBuckets)
{
    for (int i = 0; i < maxBuckets; i++)
    {
        m_words.push_back(nullptr);
    }
}

DictionaryImpl::~DictionaryImpl()
{
    for (unsigned int i = 0; i < m_words.size(); i++)
    {
        if (m_words[i] != nullptr)
            delete m_words[i];
    }
}

unsigned int DictionaryImpl::hash(string word) const
{
    sort(word.begin(), word.end());
    return std::hash<string>()(word) % m_words.size();
}

void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
    if (!word.empty())
    {
        unsigned int bucket = hash(word);
        if (m_words[bucket] == nullptr)
        {
            m_words[bucket] = new list<string>;
            m_words[bucket]->push_back(word);
        }
        else
        m_words[bucket]->push_back(word);
    }
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;

    /*
    string permutation = letters;

    do
    {
        for (list<string>::const_iterator wordp = m_words.begin();
            wordp != m_words.end(); wordp++)
        {
            if (permutation == *wordp)
                callback(*wordp);
        }
        generateNextPermutation(permutation);
    } while (permutation != letters);
    */
    sort(letters.begin(), letters.end());
    unsigned int bucket = hash(letters);
    if (m_words[bucket] != nullptr)
    for (list<string>::iterator p = m_words[bucket]->begin(); p!= m_words[bucket]->end(); p++)
    {
        string copy = *p;
        sort(copy.begin(), copy.end());
        if (copy == letters)
            callback(*p);
    }
}

void removeNonLetters(string& s)
{
    /*string removed;
    for (int i = 0; i < s.length(); i++)
        if (isalpha(s[i]))
            removed += tolower(s[i]);
    s = removed;*/
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());
}

// Each successive call to this function generates the next permutation of the
// characters in the parameter.  For example,
//    string s = "eel";
//    generateNextPermutation(s);  // now s == "ele"
//    generateNextPermutation(s);  // now s == "lee"
//    generateNextPermutation(s);  // now s == "eel"
// You don't have to understand this function's implementation.
void generateNextPermutation(string& permutation)
{
    string::iterator last = permutation.end() - 1;
    string::iterator p;

    for (p = last; p != permutation.begin() && *p <= *(p - 1); p--)
        ;
    if (p != permutation.begin())
    {
        string::iterator q;
        for (q = p + 1; q <= last && *q > *(p - 1); q++)
            ;
        swap(*(p - 1), *(q - 1));
    }
    for (; p < last; p++, last--)
        swap(*p, *last);
}

//******************** Dictionary functions ******************************

// These functions simply delegate to DictionaryImpl's functions
// You probably don't want to change any of this code

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters, callback);
}
