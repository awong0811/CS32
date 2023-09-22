#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <string>

using ItemType = std::string;

class Sequence
{
public:
    Sequence();
    Sequence(const Sequence& other);
    ~Sequence();
    Sequence& operator=(const Sequence& other);
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    void dump() const;

private:
    int m_size;
    struct Node
    {
        ItemType m_value;
        Node* m_next;
        Node* m_prev;
    };
    Node* head;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result);


#endif