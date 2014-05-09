#include "Sequence.h"


Sequence::Sequence(bool _isSequence, short _numFrames, const Vec3f& _distance, const Pnt3f& _startLook, const Pnt3f& _endLook)
{
	isSequence = _isSequence;
	numFrames = _numFrames;
	distance = Vec3f(_distance);
	startLook = Pnt3f(_startLook);
	endLook = Pnt3f(_endLook);

	// Default to focusing on look point
	startFocus = Pnt3f(_startLook);
	endFocus = Pnt3f(_endLook);
}

Sequence::Sequence(bool _isSequence)
{
	isSequence = _isSequence;
}

Sequence::Sequence()
{
	isSequence = false;
}

Sequence::~Sequence(void)
{
}

void Sequence::RackFocus(const Pnt3f& _startFocus, const Pnt3f& _endFocus)
{
	startFocus = Pnt3f(_startFocus);
	endFocus = Pnt3f(_endFocus);
}