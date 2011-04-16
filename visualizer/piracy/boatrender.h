#ifndef BOATRENDER_H
#define BOATRENDER_H

#include "../lib/gocfamily_render.h"

class BoatRender : public GOCFamily_Render
{
	public:
		BoatRender();
		~BoatRender();
		virtual const GOC_IDType componentID() const;

		void update();

		virtual void renderAt(
			const unsigned int& turn,
			const unsigned int& frame );

};
#endif
