#ifndef SELECTIONRENDER_H
#define SELECTIONRENDER_H

class SelectionRender : public GOCFamily_Render, Singleton <SelectionRender>
{
	public:
		void setSelectionBox(int, int, int, int); //X1, Y1, X2, Y2 Screen Resolution

		bool getUpdated();
		void setUpdated(bool);
		
		bool getDragging();
		void setDragging(bool);
		
		static SelectionRender * get(){return Singleton <SelectionRender>::get();}
		
	private:
		void renderAt(const unsigned int & turn, const unsigned int & frame);
	
		bool m_updated;		//Finished dragging
		bool m_dragging;	//Currently dragging
	
	int m_X1, m_Y1, m_X2, m_Y2;
};

#endif
