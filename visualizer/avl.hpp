
#include "avl.h"

/** @brief rotateRight
  *
  * @todo: document this function
  */
template<class T>
void Avl<T>::rotateRight(node * n)
{
	if (n)
	{
		if (n->m_left)
		{
			node * left = n->m_left;
			node * parent = n->m_parent;

			left->m_parent = parent;
			left->m_right = n;
			n->m_parent = left;
			n->m_left = NULL;

			if (!parent)
			{
				m_root = left;
			}
			else
			{
				if (parent->m_left == n)
				{
					parent->m_left = left;
				}
				else
				{
					parent->m_right = left;
				}
			}
			updateCosts(left);
		}
		else
		{
			//silent fail
		}
	}
}

/** @brief rotateLeft
  *
  * @todo: document this function
  */
template<class T>
void Avl<T>::rotateLeft(node * n)
{
	if (n)
	{
		if (n->m_right)
		{
			node * right = n->m_right;
			node * parent = n->m_parent;

			right->m_parent = parent;
			right->m_left = n;
			n->m_parent = right;
			n->m_right = NULL;

			if (!parent)
			{
				m_root = right;
			}
			else
			{
				if (parent->m_left == n)
				{
					parent->m_left = right;
				}
				else
				{
					parent->m_right = right;
				}
			}
		}
		else
		{
			//silent fail
		}
	}
}




/** @brief exists
  *
  * @todo: document this function
  */
template<class T>
bool Avl<T>::exists(const unsigned int & i)
{
	node * temp = back(i);

	if (temp)
		if (temp->m_index == i)
			return true;

	return false;
}

/** @brief erase
  *
  * @todo: document this function
  */
template<class T>
void Avl<T>::erase(const unsigned int & i)
{
	node * erasable = back(i);
	
	if (erasable)
	{
		if (erasable->m_index == i)
			removeNode(erasable);
	}
}

template <class T> 
void Avl<T>::swap(node * n1, node * n2)
{
	T t_temp = n1->m_data; 
	unsigned int i_temp = n1->m_index;
	n1->m_data = n2->m_data;
	n1->m_index = n2->m_index;
	
	n2->m_data = t_temp;
	n2->m_index = i_temp;
}

/** @brief removeNode
  *
  * @todo: document this function
  */
template<class T>
void Avl<T>::removeNode(node * n)
{
	if (n->m_left == NULL && n->m_right == NULL)
	{
		//drop the node
		if (n->m_parent != NULL)
		{
			node * parent = n->m_parent;
			if (n->m_parent->m_right == n)
			{
				n->m_parent->m_right = NULL;
			}
			else
			{
				n->m_parent->m_left = NULL;
			}
		}
		else
		{		
			m_root = NULL;
		}
		
		delete n;
	}
	else if (n->m_left != NULL)
	{
		//left right most
		node * temp = n->m_left;
		node * delable;
		while (temp != NULL)
		{
			delable = temp;
			temp = temp->m_right;
		}
		
		//swap values
		swap(delable,n);
		
		//recall
		removeNode(delable);
	}
	else
	{
		//right left most
		node * temp = n->m_right;
		node * delable;
		while (temp != NULL)
		{
			delable = temp;
			temp = temp->m_left;
		}
		
		//swap values
		swap(delable,n);
		
		//recall
		removeNode(delable);
	}
}

/** @brief insert
  *
  * @todo: document this function
  */
template<class T>
void Avl<T>::insert(const unsigned int & i, const T & data)
{
	if (!m_root)
	{
		m_root = new node(i);
		m_root->m_data = data;
		return;
	}

	node * temp = m_root;
	node * n;
	while (temp)
	{
		n = temp;
		if (temp->m_index < i)
		{
			temp = temp->m_left;
		}
		else if (temp->m_index > i)
		{
			temp = temp->m_right;
		}
		else
		{
			break;
		}
	}

	if (n->m_index < i)
	{
		n->m_left = new node(i,n);
		n->m_left->m_data = data;
		n->m_bal -= 1;
		updateCosts(n->m_left);
	}
	else if (n->m_index > i)
	{
		n->m_right = new node(i,n);
		n->m_right->m_data = data;
		n->m_bal += 1;
		updateCosts(n->m_right);
	}
	else
	{
		n->m_data = data;
	}
}

template<class T>
T * interpolate(T*t1,T*t2)
{
	return new T();
}

/** @brief operator[]
  *
  * @todo: document this function
  */
template<class T>
T * Avl<T>::operator[](const unsigned int & i)
{
	if (!m_root)
		return NULL;

	if (m_interp)
	{
		std::cout << "interpolating?\n";
		return interpolate(&back(i)->m_data,&front(i)->m_data);
	}

	node * temp = back(i);
	

	if (temp)
		return &temp->m_data;

	return NULL;
}

/** @brief ~Avl
  *
  * @todo: document this function
  */
template<class T>
 Avl<T>::~Avl()
{
	delBranch(m_root);
}

/** @brief Avl
  *
  * @todo: document this function
  */
template<class T>
 Avl<T>::Avl(): m_root(NULL), m_interp(false)
{
}

/** @brief delBranch
  *
  * @todo: document this function
  */
template<class T>
void Avl<T>::delBranch(node * n)
{
	if (n)
	{
		delBranch(n->m_left);
		delBranch(n->m_right);
		delete n;
	}
}

/** @brief isInterpolating
  *
  * @todo: document this function
  */
template<class T>
bool Avl<T>::isInterpolating()
{
	return m_interp;
}

inline int _abs(const int & i)
{
	return (i<0)?-1*i:i;
}

/** @brief updateCosts
  *
  * @todo: document this function
  */
template<class T>
void Avl<T>::updateCosts(node * n)
{
	if (n)
	{
		n->m_bal = 0;

		if (n->m_left)
		{
			n->m_bal -= 1;
			n->m_bal -= _abs(n->m_left->m_bal);
		}

		if (n->m_right)
		{
			n->m_bal += 1;
			n->m_bal += _abs(n->m_right->m_bal);
		}


		if (n->m_bal > 1 )
		{
			if ( n->m_right->m_bal > 0)
			{
				rotateLeft(n);
			}
			else
			{
				rotateRight(n->m_right);
			}
		}

		if (n->m_bal < -1)
		{
			if ( n->m_left->m_bal < 0)
			{
				rotateRight(n);
			}
			else
			{
				rotateLeft(n->m_left);
			}
		}

		updateCosts(n->m_parent);
	}

}
/** @brief get
  *
  * @todo: document this function
  */
template<class T>
T* Avl<T>::get(const unsigned int & i)
{
	node * temp = back(i);
	if (temp)
		if (temp->m_index == i)
			return &temp->m_data;

	return NULL;
}



