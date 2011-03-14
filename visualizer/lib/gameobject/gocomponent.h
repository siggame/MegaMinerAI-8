#ifndef GOCOMPONENT_H
#define GOCOMPONENT_H

#include <string>
//to make changing the id type easy
typedef std::string GOC_IDType ;
class GameObject;

class GOComponent
{
	public:
		/** Default constructor */
		GOComponent():m_owner(NULL){}
		/** Default destructor */
		virtual ~GOComponent() = 0;

		virtual const GOC_IDType & componentID() const = 0;
		virtual const GOC_IDType & familyID() const = 0;

		virtual void update();

		void setOwner( GameObject * owner){m_owner = owner;}
		GameObject * getOwner(){return m_owner;}

	protected:
	private:
		GameObject * m_owner;
};

#endif // GOCOMPONENT_H
