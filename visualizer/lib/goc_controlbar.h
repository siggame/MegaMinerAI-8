

#ifndef GOC_CONTROLBAR_H
#define GOC_CONTROLBAR_H

#include "gameobject/gocomponent.h"

class GOC_ControlBar : public GOCFamily_ControlBar
{
	public:
		/** Default constructor */
		GOC_ControlBar();
		/** Default destructor */
		virtual ~GOC_ControlBar() = 0;

		virtual const GOC_IDType & familyID() const {return GOC_IDType("ControlBar");}
		virtual void renderAt(const unsigned int & turn, const unsigned int & frame) = 0;
		/** switches the label on the play/pause button when it is pushed */
		virtual void playPause() = 0;
		/**
		 * retrieves the number of turns that were played in the game
		 * @return the number of turns that were played in the game */
		virtual int numTurns() = 0;
		/**
		 * retrieves the turn that playback is currently on
		 * @return the turn that playback is currently on */
		virtual int currentTurn() = 0;
	protected:
	private:
};

#endif // GOC_CONTROLBAR_H
