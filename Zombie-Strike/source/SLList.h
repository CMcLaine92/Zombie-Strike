#pragma once


template<typename Type> class SLLIter;

template<typename Type>
class SLList
{
	struct Node
	{
		Type element;
		Node* next;
	};

	Node* head = NULL;
	unsigned int m_size = 0;

	friend class SLLIter<Type>;

public:

	SLList() = default;
	~SLList() { clear(); }
	SLList<Type>& operator=(const SLList<Type>& that);
	SLList(const SLList<Type>& that);
	void addHead(const Type& v);
	void insert(SLLIter<Type>& index, const Type& v);
	void remove(SLLIter<Type>& index);
	inline unsigned int size() const { return m_size; }
	void Recursive(Node* node);
	void clear();
};

template<typename Type>
class SLLIter
{
	typename SLList<Type>::Node* curr;
	typename SLList<Type>::Node* prev;
	SLList<Type>* list;

	friend class SLList<Type>;

public:
	SLLIter(SLList<Type>& listToIterate);
	void begin();
	bool end() const;
	SLLIter<Type>& operator++();
	Type& current() const;

};

template<typename Type>
void SLList<Type>::Recursive(Node* node)
{
	if (node)
	{
		Recursive(node->next);
		addHead(node->element);
	}
}

template<typename Type>
SLList<Type>& SLList<Type>::operator=(const SLList<Type>& that)
{
	if (this != &that)
	{
		clear();
		Node* temp = that.head;
		Recursive(temp);
		m_size = that.size();
	}
	return *this;
}

template<typename Type>
SLList<Type>::SLList(const SLList<Type>& that)
{
	Node* temp = that.head;
	Recursive(temp);
	m_size = that.size();
}

template<typename Type>
void SLList<Type>::addHead(const Type& v)
{
	Node* temp = new Node;
	temp->element = v;
	temp->next = head;
	head = temp;
	m_size++;
}

template<typename Type>
void SLList<Type>::clear()
{
	while (head != NULL)
	{
		Node* temp = head;
		head = head->next;
		delete temp;
	}
	m_size = 0;
}

template<typename Type>
void SLList<Type>::insert(SLLIter<Type>& index, const Type& v)
{
	if (index.curr == NULL)
		return;

	if (index.prev)
	{
		Node* temp = new Node;
		temp->element = v;
		temp->next = index.curr;
		index.prev->next = temp;
		index.curr = temp;
		m_size++;
	}
	else
	{
		addHead(v);
		index.curr = head;
	}
}

template<typename Type>
void SLList<Type>::remove(SLLIter<Type>& index)
{
	if (index.prev)
	{
		index.prev->next = index.curr->next;
		delete index.curr;
		index.curr = index.prev->next;
		m_size--;
	}
	else if (index.curr)
	{
		head = index.curr->next;
		delete index.curr;
		index.curr = head;
		m_size--;
	}
}

//Iterator methods

template<typename Type>
SLLIter<Type>::SLLIter(SLList<Type>& listToIterate)
{
	list = &listToIterate;
	curr = list->head;
	prev = NULL;
}

template<typename Type>
void SLLIter<Type>::begin()
{
	curr = list->head;
	prev = NULL;
}

template<typename Type>
bool SLLIter<Type>::end() const
{
	if (curr == NULL)
		return true;
	return false;
}

template<typename Type>
SLLIter<Type>& SLLIter<Type>::operator++()
{
	if (!end())
	{
		prev = curr;
		curr = curr->next;
	}
	return *this;
}

template<typename Type>
Type& SLLIter<Type>::current() const
{
	return curr->element;
}
