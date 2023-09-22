#include "Sequence.h"
#include <string>
#include <iostream>

Sequence::Sequence() // default constructor
{
	m_size = 0;
	Node* dummy = new Node;
	dummy->m_next = dummy;
	dummy->m_prev = dummy;
	head = dummy;
}

Sequence::Sequence(const Sequence& other) // copy constructor
{
	m_size = other.m_size;
	Node* dummy = new Node;
	head = dummy;
	dummy->m_next = dummy;
	dummy->m_prev = dummy;
	for (Node* p = other.head->m_next; p != other.head; p = p->m_next) // loop runs through the other linked list
	{
		Node* q = new Node; //for each node in other that's not the head, make a new node for this linked list
		q->m_value = p->m_value; //copy other's nodes' values into this nodes' values
		q->m_next = dummy; //set the next pointer of the new node to dummy/head
		q->m_prev = dummy->m_prev; //set prev pointer of new node to where dummy's prev pointer is set to
		q->m_next->m_prev = q; //adjust the pointers of the adjacent nodes to point to q
		q->m_prev->m_next = q;
	}
}

Sequence& Sequence::operator=(const Sequence& other) // assignment operator
{
	if (head != other.head)
	{
		Sequence temp(other); // creates a temp copy of other and swaps this with temp
		this->swap(temp);
	}
	return *this;
}

Sequence::~Sequence() // destructor
{
	while (head->m_next != head)
	{ // while head's next node is not itself, 
		head->m_next = head->m_next->m_next; // move head's next pointer to the next object
		delete head->m_next->m_prev; // delete the object in between head and the new next object
		head->m_next->m_prev = head; // set the new next object's prev pointer to head
	}
	delete head;
}

bool Sequence::empty() const
{
	return m_size == 0;
}

int Sequence::size() const
{
	return m_size;
}



int Sequence::insert(int pos, const ItemType& value)
{
	if (pos > m_size || pos < 0)
	{
		return -1;
	}
	else
	{
		m_size++;
		Node* q = new Node; // make a new node with value
		q->m_value = value;
		Node* front = head; // make two pointers
		Node* back = head;
		int count = 0;
		Node* i = head->m_next; // make an index pointer
		while (count != pos) 
		{ // loop until index pointer points to the node with the index where the new node will be inserted 
			i = i->m_next;
			count++;
		}
		front = i; // front pointer points where the index pointer is
		back = i->m_prev; // back pointer points to the node before
		//for (Node* i = head->m_next; i!=head; i = i->m_next)
		//{
		//	if (count == pos)
		//	{
		//		front = i;
		//		back = i->m_prev;
		//		break;
		//	}
		//	count++;
		//}
		q->m_next = front; // insert the new node the same way the copy constructor inserts
		q->m_prev = back;
		q->m_next->m_prev = q;
		q->m_prev->m_next = q;
		return pos;
	}
}

int Sequence::insert(const ItemType& value)
{
	int count = 0; // loop through the list using count
	for (Node* i = head->m_next; count != m_size; i = i->m_next)
	{
		if (value <= i->m_value)
		{ // if value satisfies the condition, break the loop, count is the index where the new node will be inserted
			break;
		}
		count++;
	} // if the condition is not satisfied, count is now equal to the size of the loop, where the new node will be inserted
	return insert(count, value);;
}

bool Sequence::erase(int pos)
{
	if (pos < 0 || pos >= m_size)
	{
		return false;
	}
	else
	{
		int count = 0;
		Node* back = head->m_next;
		while ( count != pos) // loop through until back is pointing at index pos
		{
			back = back->m_next;
			count++;
		}
		Node* front = back->m_prev; // front points at the node preceding back
		front->m_next = back->m_next; // adjust the pointers of the nodes before and after back
		back->m_next->m_prev = front;
		delete back; // delete the node that back is pointing to
		m_size--;
		return true;
	}
}

int Sequence::remove(const ItemType& value)
{
	int itemsRemoved = 0;
	Node* i = head->m_next; // i starts at the node after head
	int pos = 0; // integer index variable
	while (i != head) // loop through the list until i points at head
	{
		if (i->m_value == value) // when the value of the node that i points at satisfies this condition
		{
			i = i->m_prev; // point i to the node before so the pointer doesn't get deleted
			erase(pos); // erase the node at position pos
			pos--; // subtract 1 from pos to offset the increment that happens next
			itemsRemoved++; // increase # of items removed
		}
		i = i->m_next; // i points at the next node
		pos++; // index increases
	}
	return itemsRemoved;
}

bool Sequence::get(int pos, ItemType& value) const
{
	if (pos < 0 || pos >= m_size)
	{
		return false;
	}
	else
	{
		int count = 0; // integer index variable
		for (Node* i = head->m_next; i != head; i = i->m_next)
		{
			if (count == pos)
			{ // when the pos index has been reached
				value = i->m_value; // copy the value of the node into value
				break; // exit the loop
			}
			count++;
		}
		return true;
	}
}

bool Sequence::set(int pos, const ItemType& value)
{
	if (pos < 0 || pos >= m_size)
	{
		return false;
	}
	else
	{
		int count = 0; // integer index variable
		for (Node* i = head->m_next; i != head; i = i->m_next)
		{ // loop through the list until i is pointing at the index that needs to be set
			if (count == pos)
			{ // once the node at the specified index is set, exit the loop
				i->m_value = value;
				break;
			}
			count++;
		}
		return true;
	}
}

int Sequence::find(const ItemType& value) const
{
	int p = -1; // set p to -1, this is what we're returning
	int count = 0; // integer index variable
	for (Node* i = head->m_next; i != head; i = i->m_next)
	{ // loop through the list
		if (i->m_value == value)
		{ // if the value of the node satisfies this condition, p is set to the index
			p = count;
			break;
		}
		count++;
	} // if none of the nodes satisfy the condition, p is still -1
	return p;
}

void Sequence::swap(Sequence& other)
{
	if (head != other.head) // check for aliasing
	{ // use the builting swap function to swap the sizes and the pointers
		std::swap(m_size, other.m_size);
		std::swap(head, other.head);
	}
}

void Sequence::dump() const
{
	for (Node* p = head->m_next; p != head; p = p->m_next)
	{
		std::cerr << p->m_value << std::endl;
	}
	std::cerr << "- - -" << std::endl;
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	if (&seq2 == &seq1) // check for aliasing
	{
		return 0;
	}
	else if (seq1.size() < seq2.size() || seq2.size() == 0)
	{
		return -1;
	}
	else
	{
		/*int retvalue = -1;
		bool in = false;
		ItemType item2;
		ItemType item1;
		for (int i = 0; i < seq1.size() - seq2.size(); i++)
		{
			seq2.get(0, item2);
			seq1.get(i, item1);
			if (item2 == item1)
			{
				in = true;
				for (int j = 0; j < seq2.size(); j++)
				{
					seq2.get(j, item2);
					seq1.get(i + j, item1);
					if (item2 != item1)
						in = false;
				}
				if (in)
				{
					retvalue = i;
					break;
				}
			}
		}
		return retvalue;*/
		int retvalue = -1; // this is the value we will be returning
		ItemType item2; // create two items that the items of seq1 and seq2 will be copied into with get()
		ItemType item1;
		for (int i = 0; i <= seq1.size() - seq2.size(); i++)
		{ // loop through seq1, using the difference in their sizes; looping more than that will cause some issues
			seq2.get(0, item2); //get() the first element of seq2
			seq1.get(i, item1); //get() the ith element of seq1
			if (item2 == item1) //compare them
			{ // if the condition is satisfied
				retvalue = i; //retvalue is set to ith index for now
				for (int j = 0; j < seq2.size(); j++)
				{//loop through seq2
					seq2.get(j, item2); //copy each item from seq2 into item2
					seq1.get(i + j, item1); //copy the respective items from seq1 into item1; index is offset from i by j because we are starting from the ith position
					if (item2 != item1) //if the items don't match, reset retvalue to -1 and continue the search
						retvalue = -1;
				} // if the inner loop has finished and retvalue is not -1, that means all the values are matching and retvalue did not get reset to -1
				if (retvalue != -1)
					break; // exit the outer loop, we have found the lowest index
			}
		}
		return retvalue;
	}
}

void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	Sequence copy1(seq1); // copy seq1 and seq2 into copies to prevent problems with aliasing
	Sequence copy2(seq2);
	Sequence copy3; // make a new empty sequence using the default constructor and assign that to result
	result = copy3;
	if (copy1.size() == 0 && copy2.size() == 0)
	{
		//do nothing
	}
	else if (copy1.size() == 0)
	{ // if the first sequence is empty, just get the items from the second sequence in reverse
		ItemType item;
		for (int i = 0; i < copy2.size(); i++)
		{
			copy2.get(copy2.size()-i-1, item);
			result.insert(result.size(), item);
		}
	}
	else if (copy2.size() == 0)
	{ // if the second sequence is empty, just get the items from the first sequence in reverse
		ItemType item;
		for (int i = 0; i < copy1.size(); i++)
		{
			copy1.get(copy1.size() - i - 1, item);
			result.insert(result.size(), item);
		}
	}
	else
	{ // get the items from both sequences in reverse
		ItemType item;
		for (int i = 0; i < copy1.size(); i++)
		{
			copy1.get(copy1.size() - i - 1, item);
			result.insert(result.size(), item);
		}
		for (int i = 0; i < copy2.size(); i++)
		{
			copy2.get(copy2.size() - i - 1, item);
			result.insert(result.size(), item); // inserting to size() because we don't know how big result is
		}
	}

}