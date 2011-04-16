#ifndef TREASURERENDER_H
#define TRESURERENDER_H

#include "../lib/gocfamily_render.h"

class TreasureRender : public GOCFamily_Render
{
	public:
		TreasureRender();
		~TreasureRender();

		virtual const GOC_IDType componentID() const;

		void update();
		virtual void renderAt(
			const unsigned int& turn,
			const unsigned int& frame );
};
#endif
