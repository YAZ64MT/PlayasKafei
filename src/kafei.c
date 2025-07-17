#include "global.h"
#include "modding.h"
#include "recomputils.h"
#include "globalobjects_api.h"
#include "assets/objects/object_test3/object_test3.h"
#include "overlays/actors/ovl_En_Test3/z_en_test3.h"
#include "kafei.h"

TexturePtr gKafeiEyeTextures[] = {
    gKafeiEyesOpenTex,
    gKafeiEyesHalfTex,
    gKafeiEyesClosedTex,
    gKafeiEyesRollRightTex,
    gKafeiEyesRollLeftTex,
    gKafeiEyesRollUpTex,
    gKafeiEyesRollDownTex,
    object_test3_Tex_006680,
};

TexturePtr gKafeiMouthTextures[] = {
    gKafeiMouthClosedTex,
    gKafeiMouthTeethTex,
    gKafeiMouthAngryTex,
    gKafeiMouthHappyTex,
};

Gfx *gKafeiLeftFist;
Gfx *gKafeiRightFist;
Gfx *gKafeiLeftHandBottle;

Gfx *gKafeiFPSRightHand;
Gfx *gKafeiFPSRightForearm;
Gfx *gKafeiFPSLeftHand;
Gfx *gKafeiFPSLeftForearm;

void *gKafeiSkeletonLimbs[] = {
    &gKafeiRootLimb,          /* KAFEI_LIMB_ROOT */
    &gKafeiWaistLimb,         /* KAFEI_LIMB_WAIST */
    &gKafeiLowerRootLimb,     /* KAFEI_LIMB_LOWER_ROOT */
    &gKafeiRightThighLimb,    /* KAFEI_LIMB_RIGHT_THIGH */
    &gKafeiRightShinLimb,     /* KAFEI_LIMB_RIGHT_SHIN */
    &gKafeiRightFootLimb,     /* KAFEI_LIMB_RIGHT_FOOT */
    &gKafeiLeftThighLimb,     /* KAFEI_LIMB_LEFT_THIGH */
    &gKafeiLeftShinLimb,      /* KAFEI_LIMB_LEFT_SHIN */
    &gKafeiLeftFootLimb,      /* KAFEI_LIMB_LEFT_FOOT */
    &gKafeiUpperRootLimb,     /* KAFEI_LIMB_UPPER_ROOT */
    &gKafeiHeadLimb,          /* KAFEI_LIMB_HEAD */
    &gKafeiHatLimb,           /* KAFEI_LIMB_HAT */
    &gKafeiCollarLimb,        /* KAFEI_LIMB_COLLAR */
    &gKafeiLeftShoulderLimb,  /* KAFEI_LIMB_LEFT_SHOULDER */
    &gKafeiLeftForearmLimb,   /* KAFEI_LIMB_LEFT_FOREARM */
    &gKafeiLeftHandLimb,      /* KAFEI_LIMB_LEFT_HAND */
    &gKafeiRightShoulderLimb, /* KAFEI_LIMB_RIGHT_SHOULDER */
    &gKafeiRightForearmLimb,  /* KAFEI_LIMB_RIGHT_FOREARM */
    &gKafeiRightHandLimb,     /* KAFEI_LIMB_RIGHT_HAND */
    &gKafeiSheathLimb,        /* KAFEI_LIMB_SHEATH */
    &gKafeiTorsoLimb,         /* KAFEI_LIMB_TORSO */
};

FlexSkeletonHeader gKafeiSkeleton = {{gKafeiSkeletonLimbs, ARRAY_COUNT(gKafeiSkeletonLimbs)}, 18};

void setupKafeiAssets() {
    void *kafeiObj = GlobalObjects_getGlobalObject(OBJECT_TEST3);

    gKafeiLeftFist = GlobalObjects_getGlobalGfxPtr(OBJECT_TEST3, gKafeiLeftHandDL);
    gKafeiRightFist = GlobalObjects_getGlobalGfxPtr(OBJECT_TEST3, gKafeiRightHandDL);
    gKafeiLeftHandBottle = gKafeiLeftFist;
    gKafeiFPSRightHand = gKafeiRightFist;
    gKafeiFPSRightForearm = GlobalObjects_getGlobalGfxPtr(OBJECT_TEST3, gKafeiRightForearmDL);
    gKafeiFPSLeftHand = gKafeiLeftFist;
    gKafeiFPSLeftForearm = GlobalObjects_getGlobalGfxPtr(OBJECT_TEST3, gKafeiLeftForearmDL);

    for (int i = 0; i < ARRAY_COUNT(gKafeiEyeTextures); ++i) {
        gKafeiEyeTextures[i] = SEGMENTED_TO_GLOBAL_PTR(kafeiObj, gKafeiEyeTextures[i]);
    }

    for (int i = 0; i < ARRAY_COUNT(gKafeiMouthTextures); ++i) {
        gKafeiMouthTextures[i] = SEGMENTED_TO_GLOBAL_PTR(kafeiObj, gKafeiMouthTextures[i]);
    }

    GlobalObjects_globalizeLodLimbSkeleton(kafeiObj, &gKafeiSkeleton);

    GlobalObjectsSegmentMap kafeiSegments = {0};
    kafeiSegments[0x06] = kafeiObj;
    kafeiSegments[0x04] = GlobalObjects_getGlobalObject(GAMEPLAY_KEEP);

    LodLimb **limbs = (LodLimb **)(gKafeiSkeleton.sh.segment);
    for (int i = 0; i < gKafeiSkeleton.sh.limbCount; ++i) {
        LodLimb *limb = limbs[i];

        if (limb->dLists[0]) {
            GlobalObjects_rebaseDL(limb->dLists[0], kafeiSegments);
            GlobalObjects_rebaseDL(limb->dLists[1], kafeiSegments);
        }
    }

}
