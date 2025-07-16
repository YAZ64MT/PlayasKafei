#ifndef __KAFEI_H__
#define __KAFEI_H__

#include "global.h"

extern TexturePtr gKafeiEyeTextures[];
extern TexturePtr gKafeiMouthTextures[];
extern Gfx *gKafeiLeftFist;
extern Gfx *gKafeiRightFist;
extern Gfx *gKafeiLeftHandBottle;
extern Gfx *gKafeiFPSRightHand;
extern Gfx *gKafeiFPSRightForearm;
extern Gfx *gKafeiFPSLeftHand;
extern Gfx *gKafeiFPSLeftForearm;
extern FlexSkeletonHeader gKafeiSkeleton;

void setupKafeiAssets();

#endif
