#include <exception>
#include <stdexcept>
#include <iostream>

#define nullptr 0

using namespace std;

template<class T> class CyclicList; //forward declarations

template<class T = int> class SingleNode
{
public:
	SingleNode *getNext() const;
	T getData() const;

	SingleNode(const T &data, SingleNode<T> *next = NULL);
	~SingleNode();

private:
	T data;
	SingleNode *next;

	friend class CyclicList<T>;
};


template<class T> class CyclicList
{
private:
	SingleNode<T> *Head;
	SingleNode<T> *Tail;
	int Size;

public:
	//GETTERS
	int GetSize() const;
	bool IsEmpty() const;
	T GetFrontData() const;
	T GetBackData() const;
	const SingleNode<T> *GetHead() const;
	const SingleNode<T> *GetTail() const;
	const T GetNthNodeData(unsigned int n) const;
	int NumberOf(const T &keyword) const;

	//METHODS
	void push_front(const T &data);
	void push_back(const T &data);
	T pop_front();
	int erase(const T &keyword, bool bOnceOnly);
	void TransferList(CyclicList<T> &other);
	void SetParent();

	CyclicList<T> &operator=(const CyclicList<T> &rs);

	void Print();

	//CON/DE/STRUCTORS
	CyclicList(const CyclicList<T> &);
	CyclicList();
	~CyclicList();
};

template<class T> SingleNode<T>::SingleNode(const T &newData, SingleNode<T> *newNext)
{
	data = newData;
	next = newNext;
}

template<class T> SingleNode<T>::~SingleNode()
{

}

template<class T> SingleNode<T> *SingleNode<T>::getNext() const
{
	return next;
}

template<class T> T SingleNode<T>::getData() const
{
	return data;
}

template<class T> CyclicList<T>::CyclicList()
{
	Head = nullptr;
	Tail = nullptr;
	Size = 0;
}

template<class T> CyclicList<T>::CyclicList(const CyclicList<T> &rs)
{
	TransferList(rs);
}

template<class T> CyclicList<T> &CyclicList<T>::operator=(const CyclicList<T> &rs)
{
	TransferList(rs);
}

template<class T> void CyclicList<T>::TransferList(CyclicList<T> &other)
{
	while (!other.IsEmpty())
		push_back(other.pop_front());

	other.Head = nullptr;
}

template<class T> const T CyclicList<T>::GetNthNodeData(unsigned int n) const
{
	if (IsEmpty())
		return T(0);

	SingleNode<T> *iterator = Head;

	for (unsigned int i = 0; i < n; i++)
	{
		if (iterator->next == nullptr || iterator->next == Head)
			return T(0);

		iterator = iterator->next;
	}

	return iterator->data;
}

template<class T> CyclicList<T>::~CyclicList()
{
	if (Size == 0 || Head == nullptr)
		return;

	SingleNode<T> *iterator = Head;

	do
	{
		SingleNode<T> *prev = iterator;

		if (iterator->next != nullptr)
		iterator = iterator->next;


		delete prev;

	} while (iterator != Head); //address comparison, so ok that Head has already been deleted
}

template<class T> void CyclicList<T>::Print()
{
	if (Size > 0)
	{
		int n = 0;
		SingleNode<T> *i = Head;

		do
		{
			cout << "Node[" << n++ << "] = " << i->data << endl;
			i = i->next;
		} while (i != Head);

	}
}

template<class T> int CyclicList<T>::GetSize() const
{
	return Size;
}

template<class T> bool CyclicList<T>::IsEmpty() const
{
	return Size == 0;
}

template<class T> int CyclicList<T>::NumberOf(const T &keyword) const
{
	if (Head == nullptr)
		return 0;

	SingleNode<T> *ptr = Head; //begin at head
	int numTotal = 0;

	do //scan thru list until tail reached
	{
		if (ptr->getData() == keyword) //find nodes whose data matches search keyword
			numTotal++;

		ptr = ptr->getNext(); //go to next node in list
	} while (ptr != Head);

	return numTotal; //return total count
}

template<class T> T CyclicList<T>::GetFrontData() const
{
	try
	{
		if (Head == nullptr)
			throw std::underflow_error("An underflow has occurred");
	}
	catch (std::underflow_error &a)
	{
		cout << a.what() << endl;
		return 0;
	}

	return Head->data;
}

template<class T> T CyclicList<T>::GetBackData() const
{
	try
	{
		if (Tail == nullptr)
			throw std::underflow_error("An underflow has occurred");
	}
	catch (std::underflow_error &a)
	{
		cout << a.what() << endl;
		return 0;
	}

	return Tail->data;
}

template<class T> const SingleNode<T> *CyclicList<T>::GetHead() const
{
	return Head;
}

template<class T> const SingleNode<T> *CyclicList<T>::GetTail() const
{
	return Tail;
}

template<class T> void CyclicList<T>::push_front(const T & newData)
{
	SingleNode<T> *newNode = new SingleNode<T>(newData, Head);

	if (newNode->next == nullptr)
		Tail = newNode;

	Tail->next = newNode;

	Head = newNode;

	Size++;
}

template<class T> void CyclicList<T>::push_back(const T &newData)
{
	SingleNode<T> *newNode = new SingleNode<T>(newData, Head);

	if (newNode->next == nullptr)
		Head = newNode;

	else Tail->next = newNode;

	Tail = newNode;

	Size++;
}

template<class T> T CyclicList<T>::pop_front()
{
	T oldData;

	try
	{
		if (Head == nullptr)
			throw std::underflow_error("An underflow has occurred.");

		SingleNode<T> *oldHead = Head;
		oldData = oldHead->data;

		if (Head->next == Head)
		{
			Head = nullptr;
			Tail = nullptr;
		}

		else Head = Head->next;

		delete oldHead;

		Size--;
	}
	catch (std::underflow_error &a)
	{
		cout << a.what() << endl;
		return 0;
	}

	if (Size == 0)
	{
		Head = nullptr;
		Tail = nullptr;
	}

	return oldData;
}

template<class T> int CyclicList<T>::erase(const T &keyword, bool bOnceOnly)
{
	if (Head == nullptr) //no sense going thru empty list
		return 0;

	int NumFound = 0;
	SingleNode<T> *current = Head; //iterator that checks for keyword
	SingleNode<T> *prev = Tail; //iterator that trails current for linking nodes

	do //scan thru list until Tail is reached
	{
		Head = Tail->next;

		if (keyword == current->data) //if match found
		{
			NumFound++; //found one, so increment

			current = (Size == 1) ? nullptr : current->next; //current jumps to next node unless there is only one node in the list

			if (prev->next == Tail)
				Tail = prev; //if target node is the last node, move it to the "new" last node

			//if (prev->next == Head)
			//Head = current;

			if (prev->next == Head && Head != nullptr)
				Head = Head->next;

			delete prev->next; //take out target node
			Size--;

			if (current != nullptr)
				prev->next = current; //have prev->next "jump over" old node

			else //eliminated the only node, so list is empty
			{
				Tail = nullptr;
				Head = nullptr;
				return NumFound;
			}

			if (bOnceOnly)
				return NumFound;
		}

		else
		{
			prev = current; //trail current
			current = current->next; //iterate to next node
		}

	} while (current != Head);

	return NumFound;
}
