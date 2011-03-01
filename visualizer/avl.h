#ifndef AVL_H
#define AVL_H
#include <cstdlib>
#include <iostream>

template<class T>
class Avl
{
	public:
		/** Default constructor */
		Avl();
		/** Default destructor */
		~Avl();

		T * operator[](const unsigned int & i);
		void insert(const unsigned int & i, const T & data);
		void erase(const unsigned int & i);
		bool exists(const unsigned int & i);
		T * get(const unsigned int & i);

		//T * getClose(const unsigned int)

	protected:
		bool isInterpolating();

		struct node
		{
			node * m_parent;
			node * m_left;
			node * m_right;
			int m_bal;
			T m_data;
			unsigned int m_index;
			node(const unsigned int i, node*parent = NULL):m_parent(parent),m_left(NULL),m_right(NULL),m_bal(0),m_index(i){}

		};
		node * m_root;

		void rotateLeft(node * n);
		void rotateRight(node * n);
		void updateCosts(node * n);
		
		void removeNode(node * n);

		void delBranch(node * n);
		
		void swap(node * n1, node * n2);

		node * back(const unsigned int & i)
		{
			node * temp, * n;
			temp = m_root;

			if (m_root == NULL)
				return NULL;

			while (temp != NULL)
			{
				n = temp;
				if (n->m_index < i)
				{
					temp = n->m_left;
				}
				else if (n->m_index > i)
				{
					temp = n->m_right;
				}
				else
				{
					return n;
				}
			}

			if (i > n->m_index)
			{
				return n;
			}

			while (i < n->m_index && n->m_parent != NULL)
			{
				n = n->m_parent;
			}

			if (n->m_parent == NULL)
				return NULL;

			return n;
		}

		node * front(const unsigned int & i)
		{
			node * temp, *n;
			temp = m_root;

			if (m_root == NULL)
				return NULL;

			while (temp != NULL)
			{
				n = temp;
				if (n->m_index < i)
				{
					temp = n->m_left;
				}
				else if (n->m_index > i)
				{
					temp = n->m_right;
				}
				else
				{
					return n;
				}
			}

			if (i < n->m_index)
			{
				return n;
			}

			while (i > n->m_index && n->m_parent != NULL)
			{
				n = n->m_parent;
			}

			if (n->m_parent == NULL)
				return NULL;

			return n;
		}

		bool m_interp;

	private:
};

#include "avl.hpp"
#endif // AVL_H
