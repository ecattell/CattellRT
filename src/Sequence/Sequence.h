#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

#include "../MathUtil/Vec3f.h"
typedef Vec3f Pnt3f;

/*
 * Sequence class used to manage camera movement, rack focuses, and number of frames
 */

struct Sequence
{
public:
	Sequence(bool,short,const Vec3f&,const Pnt3f&,const Pnt3f&);
	Sequence(bool);
	Sequence();
	~Sequence(void);
	void RackFocus(const Pnt3f& _startFocus, const Pnt3f& _endFocus);
	bool isSequence;
	short numFrames;
	Vec3f distance;
	Pnt3f startLook, endLook;
	Pnt3f startFocus, endFocus;
};

#endif // __SEQUENCE_H__

