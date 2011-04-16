#ifndef PIRATERENDER_H
#define PIRATERENDER_H

#include "../lib/gocfamily_render.h"

class PirateRender : public GOCFamily_Render
{
	public:
		PirateRender();
		~PirateRender();

		virtual const GOC_IDType componentID() const;

		void update();
		virtual void renderAt(
			const unsigned int& turn,
			const unsigned int& frame );
};
#endif
