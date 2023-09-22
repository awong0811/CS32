#include <iostream>
#include "Sequence.h"
#include <cassert>
#include <string>
using namespace std;

int main()
{
    Sequence a; // empty sequence
    a.insert(0, "apple"); // insert into first spot
    a.insert(1, "banana"); // insert into second spot
    a.insert(1, "cantaloupe"); // insert into second spot
    a.dump(); // making sure banana did not get deleted
    Sequence b(a); // copy constructor
    b.dump(); // making sure items were copied over
    assert(a.size()==3); // test size
    assert(a.insert("deer") == 3); // insert into last spot
    assert(a.insert("ban") == 1); // insert into second spot
    assert(a.erase(1)); // erase second item (ban)
    assert(a.size()==4); // test size
    a.dump(); // testing if things inserted correctly
    b.dump(); // should be different from a
    for(int i = 0; i < 5; i++)
    assert(b.insert("cantaloupe") == 1); // insert cantaloupe 5 times
    b.dump();
    assert(b.remove("cantaloupe") == 6); // test remove
    b.dump();
    assert(b.insert("cantaloupe")==2); // test insert
    assert(b.size() == 3); // test size
    assert(a.size() == 4); // test size
    b.dump();
    assert(b.set(2, "celery")); // test set
    string s;
    assert(b.get(2, s)); // test get
    assert(!b.get(3, s)); // test get
    assert(!a.get(4, s)); // test get
    assert(s == "celery"); // test set
    assert(b.find("banana") == 1); // test find
    assert(b.find("celery") == 2); // test find
    assert(b.find("carrot") == -1); // test find
    a.swap(b); // test swap
    assert(b.size() == 4); // test size
    assert(a.size() == 3); // test size
    a.dump();
    b.dump();

    Sequence c;
    c.insert("aaron"); // just making the sequence, already know insert works
    c.insert("brandon");
    c.insert("charlie");
    c.insert("darren");
    c.insert("ethan");
    Sequence d(c);
    d.remove("aaron"); // copying and removing, already know they work
    d.remove("ethan");
    c.dump();
    d.dump();
    assert(subsequence(c, d) == 1); // test subsequence
    assert(subsequence(d, c) == -1); // test subsequence
    d.insert(3, "aaron");
    d.dump();
    assert(subsequence(c, d) == -1); // test subsequence
    assert(c.size() == 5); // test size
    assert(d.size() == 4); // test size
    Sequence e;
    concatReverse(c, d, e); // test concatReverse
    e.dump();
    assert(e.size() == 9); // test size
    Sequence f;
    concatReverse(c, f, f); // test concatReverse
    f.dump();
    assert(f.size() == 5); // test size
    assert(f.find("ethan") == 0); // test find
    concatReverse(f, f, f); // test concatReverse
    f.dump();
    assert(f.size() == 10);

//INT TESTS
    //Sequence a;
    //Sequence b;
    //assert(a.insert(0, 30)==0);
    //assert(a.insert(1, 21)==1);
    //assert(a.insert(2, 63)==2);
    //assert(a.insert(3, 42)==3);
    //assert(a.insert(4, 17)==4);
    //assert(a.insert(5, 63)==5);
    //assert(a.insert(6, 17)==6);
    //assert(a.insert(7, 29)==7);
    //assert(a.insert(8, 8)==8);
    //assert(a.insert(9, 32)==9);
    //assert(b.insert(0, 63)==0);
    //assert(b.insert(1, 17)==1);
    //assert(b.insert(2, 29)==2);
    //assert(subsequence(a, b)==5);
    //assert(b.remove(17) == 1);
    //assert(b.insert(0, 17) == 0);
    //b.dump();
    //assert(subsequence(a, b) == -1);
}
//#include "Sequence.h"
//#include <type_traits>
//
//#define CHECKTYPE(c, f, r, a)  \
//        {  \
//         static_assert(std::is_same<decltype(&c::f), r (c::*)a>::value, \
//             "You did not declare " #c "::" #f " as the Project 2 spec does");  \
//         auto p = static_cast<r (c::*)a>(&c::f);  \
//         (void) p;  \
//        }
//#define CHECKTYPENONMEMBER(f, r, a)  \
//        {  \
//         static_assert(std::is_same<decltype(&f), r (*)a>::value, \
//             "You did not declare " #f " as the Project 2 spec does");  \
//         auto p = static_cast<r (*)a>(f);  \
//         (void) p;  \
//        }
//
//static_assert(std::is_default_constructible<Sequence>::value,
//    "Sequence must be default-constructible.");
//static_assert(std::is_copy_constructible<Sequence>::value,
//    "Sequence must be copy-constructible.");
//static_assert(std::is_copy_assignable<Sequence>::value,
//    "Sequence must be assignable.");
//
//void thisFunctionWillNeverBeCalled()
//{
//    CHECKTYPE(Sequence, empty, bool, () const);
//    CHECKTYPE(Sequence, size, int, () const);
//    CHECKTYPE(Sequence, erase, bool, (int));
//    CHECKTYPE(Sequence, remove, int, (const ItemType&));
//    CHECKTYPE(Sequence, get, bool, (int, ItemType&) const);
//    CHECKTYPE(Sequence, set, bool, (int, const ItemType&));
//    CHECKTYPE(Sequence, find, int, (const ItemType&) const);
//    CHECKTYPE(Sequence, swap, void, (Sequence&));
//    CHECKTYPENONMEMBER(subsequence, int, (const Sequence&, const Sequence&));
//    CHECKTYPENONMEMBER(concatReverse, void, (const Sequence&, const Sequence&, Sequence&));
//    { auto p = static_cast<int (Sequence::*)(int, const ItemType&)>(&Sequence::insert); (void)p; }
//    { auto p = static_cast<int (Sequence::*)(const ItemType&)>(&Sequence::insert); (void)p; }
//}
//
//int main()
//{}