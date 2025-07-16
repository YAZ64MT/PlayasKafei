#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "globalobjects_api.h"
#include "playermodelmanager_api.h"
#include "assets/objects/object_test3/object_test3.h"
#include "assets/objects/object_link_child/object_link_child.h"
#include "overlays/actors/ovl_En_Test3/z_en_test3.h"

PLAYERMODELMANAGER_CALLBACK_REGISTER_MODELS void registerKafei() {

    // Setup Kafei assets
    void *kafeiObj = GlobalObjects_getGlobalObject(OBJECT_TEST3);

    TexturePtr eyeTextures[] = {
        gKafeiEyesOpenTex,
        gKafeiEyesHalfTex,
        gKafeiEyesClosedTex,
        gKafeiEyesRollRightTex,
        gKafeiEyesRollLeftTex,
        gKafeiEyesRollUpTex,
        gKafeiEyesRollDownTex,
        object_test3_Tex_006680,
    };

    for (int i = 0; i < ARRAY_COUNT(eyeTextures); ++i) {
        eyeTextures[i] = SEGMENTED_TO_GLOBAL_PTR(kafeiObj, eyeTextures[i]);
    }

    TexturePtr mouthTextures[] = {
        gKafeiMouthClosedTex,
        gKafeiMouthTeethTex,
        gKafeiMouthAngryTex,
        gKafeiMouthHappyTex,
    };

    for (int i = 0; i < ARRAY_COUNT(mouthTextures); ++i) {
        mouthTextures[i] = SEGMENTED_TO_GLOBAL_PTR(kafeiObj, mouthTextures[i]);
    }

    Gfx *kafeiLeftFist = GlobalObjects_getGlobalGfxPtr(OBJECT_TEST3, gKafeiLeftHandDL);
    Gfx *kafeiRightFist = GlobalObjects_getGlobalGfxPtr(OBJECT_TEST3, gKafeiRightHandDL);
    Gfx *kafeiLeftHandBottle = kafeiLeftFist;

    Gfx *kafeiFPSRightHand = kafeiRightFist;
    Gfx *kafeiFPSRightForearm = GlobalObjects_getGlobalGfxPtr(OBJECT_TEST3, gKafeiRightForearmDL);
    Gfx *kafeiFPSLeftHand = kafeiLeftFist;
    Gfx *kafeiFPSLeftForearm = GlobalObjects_getGlobalGfxPtr(OBJECT_TEST3, gKafeiLeftForearmDL);

    FlexSkeletonHeader *kafeiSkel = SEGMENTED_TO_GLOBAL_PTR(kafeiObj, &gKafeiSkel);
    GlobalObjects_globalizeLodLimbSkeleton(kafeiObj, kafeiSkel);

    GlobalObjectsSegmentMap kafeiSegments = {0};
    kafeiSegments[0x06] = kafeiObj;
    kafeiSegments[0x04] = GlobalObjects_getGlobalObject(GAMEPLAY_KEEP);

    LodLimb **limbs = (LodLimb **)(kafeiSkel->sh.segment);
    for (int i = 0; i < kafeiSkel->sh.limbCount; ++i) {
        LodLimb *limb = limbs[i];

        if (limb->dLists[0]) {
            GlobalObjects_rebaseDL(limb->dLists[0], kafeiSegments);
            limb->dLists[1] = limb->dLists[0];
        }
    }

    // PlayerModelManager stuff
    PlayerModelManagerHandle h = PLAYERMODELMANAGER_REGISTER_MODEL("mm_kafei_pmm_built_in", PMM_MODEL_TYPE_CHILD);

    PlayerModelManager_setAuthor(h, "Nintendo");
    PlayerModelManager_setDisplayName(h, "Kafei");
    PlayerModelManager_setEyesTextures(h, eyeTextures);
    PlayerModelManager_setMouthTextures(h, mouthTextures);

    PlayerModelManager_setSkeleton(h, kafeiSkel);

    PlayerModelManager_setDisplayList(h, PMM_DL_LFIST, kafeiLeftFist);
    PlayerModelManager_setDisplayList(h, PMM_DL_RFIST, kafeiRightFist);
    PlayerModelManager_setDisplayList(h, PMM_DL_LHAND_BOTTLE, kafeiLeftHandBottle);
    PlayerModelManager_setDisplayList(h, PMM_DL_FPS_RHAND, kafeiFPSRightHand);
    PlayerModelManager_setDisplayList(h, PMM_DL_FPS_RFOREARM, kafeiFPSRightForearm);
    PlayerModelManager_setDisplayList(h, PMM_DL_FPS_LHAND, kafeiFPSLeftHand);
    PlayerModelManager_setDisplayList(h, PMM_DL_FPS_LFOREARM, kafeiFPSLeftForearm);
}
