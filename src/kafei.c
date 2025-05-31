#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "modelreplacer_api.h"
#include "globalobjects_api.h"
#include "assets/objects/object_test3/object_test3.h"
#include "assets/objects/object_link_child/object_link_child.h"

void preregisterLinkDLs() {
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanWaistDL);
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanRightThighDL);
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanRightShinDL);
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanRightFootDL);
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanLeftThighDL);
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanLeftShinDL);
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanLeftFootDL);
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanHeadDL);
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanHatDL);
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanCollarDL);
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanLeftShoulderDL);
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanLeftForearmDL);
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanLeftHandOpenDL);
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanRightShoulderDL);
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanRightForearmDL);
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanRightHandOpenDL);
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanTorsoDL);

    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanLeftHandClosedDL);
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanLeftHandHoldBottleDL);
    ZModelReplacer_preregisterDL(OBJECT_LINK_CHILD, gLinkHumanRightHandClosedDL);
}

#define SET_KAFEI_OVER_LINK(vanillaLinkDL, vanillaKafeiDL) ZModelReplacer_setCustomDL(OBJECT_LINK_CHILD, vanillaLinkDL, ZGlobalObj_getGlobalGfxPtr(OBJECT_TEST3, vanillaKafeiDL))

void replaceLink() {
    SET_KAFEI_OVER_LINK(gLinkHumanWaistDL, gKafeiWaistDL);
    SET_KAFEI_OVER_LINK(gLinkHumanRightThighDL, gKafeiRightThighDL);
    SET_KAFEI_OVER_LINK(gLinkHumanRightShinDL, gKafeiRightShinDL);
    SET_KAFEI_OVER_LINK(gLinkHumanRightFootDL, gKafeiRightFootDL);
    SET_KAFEI_OVER_LINK(gLinkHumanLeftThighDL, gKafeiLeftThighDL);
    SET_KAFEI_OVER_LINK(gLinkHumanLeftShinDL, gKafeiLeftShinDL);
    SET_KAFEI_OVER_LINK(gLinkHumanLeftFootDL, gKafeiLeftFootDL);
    SET_KAFEI_OVER_LINK(gLinkHumanHeadDL, gKafeiHeadDL);
    SET_KAFEI_OVER_LINK(gLinkHumanHatDL, gKafeiSunMaskEmptyDL);
    SET_KAFEI_OVER_LINK(gLinkHumanCollarDL, gKafeiSunMaskEmptyDL);
    SET_KAFEI_OVER_LINK(gLinkHumanLeftShoulderDL, gKafeiLeftShoulderDL);
    SET_KAFEI_OVER_LINK(gLinkHumanLeftForearmDL, gKafeiLeftForearmDL);
    SET_KAFEI_OVER_LINK(gLinkHumanLeftHandOpenDL, gKafeiLeftHandDL);
    SET_KAFEI_OVER_LINK(gLinkHumanRightShoulderDL, gKafeiRightShoulderDL);
    SET_KAFEI_OVER_LINK(gLinkHumanRightForearmDL, gKafeiRightForearmDL);
    SET_KAFEI_OVER_LINK(gLinkHumanRightHandOpenDL, gKafeiRightHandDL);
    SET_KAFEI_OVER_LINK(gLinkHumanTorsoDL, gKafeiTorsoDL);

    SET_KAFEI_OVER_LINK(gLinkHumanLeftHandClosedDL, gKafeiLeftHandDL);
    SET_KAFEI_OVER_LINK(gLinkHumanLeftHandHoldBottleDL, gKafeiLeftHandDL);
    //ZModelReplacer_setCustomDL(OBJECT_LINK_CHILD, gLinkHumanLeftHandHoldBottleDL);
    SET_KAFEI_OVER_LINK(gLinkHumanRightHandClosedDL, gKafeiRightHandDL);
}

extern TexturePtr sPlayerEyesTextures[];
extern TexturePtr sPlayerMouthTextures[];

TexturePtr gVanillaEyesTex[PLAYER_EYES_MAX];
TexturePtr gVanillaMouthsTex[PLAYER_MOUTH_MAX];

// make sure the sword can be replaced w/o an object reload
RECOMP_CALLBACK(YAZMT_Z64_MODEL_REPLACER_MOD_NAME, ZModelReplacer_onReady)
void onModelReplacerReady() {
    preregisterLinkDLs();
    replaceLink();

    // vanilla forms share these segmented ptrs
    for (u32 i = 0; i < PLAYER_EYES_MAX; ++i) {
        gVanillaEyesTex[i] = sPlayerEyesTextures[i];
    }

    for (u32 i = 0; i < PLAYER_MOUTH_MAX; ++i) {
        gVanillaMouthsTex[i] = sPlayerMouthTextures[i];
    }
}

RECOMP_HOOK("Player_Init")
void updateModel_on_Player_Init(Actor *thisx, PlayState *play) {

    if (GET_PLAYER_FORM == PLAYER_FORM_HUMAN) {
        u32 base = (uintptr_t)ZGlobalObj_getGlobalObject(OBJECT_TEST3);

        sPlayerEyesTextures[0] = (TexturePtr)(base + SEGMENT_OFFSET(gKafeiEyesOpenTex));
        sPlayerEyesTextures[1] = (TexturePtr)(base + SEGMENT_OFFSET(gKafeiEyesHalfTex));
        sPlayerEyesTextures[2] = (TexturePtr)(base + SEGMENT_OFFSET(gKafeiEyesClosedTex));
        sPlayerEyesTextures[3] = (TexturePtr)(base + SEGMENT_OFFSET(gKafeiEyesRollRightTex));
        sPlayerEyesTextures[4] = (TexturePtr)(base + SEGMENT_OFFSET(gKafeiEyesRollLeftTex));
        sPlayerEyesTextures[5] = (TexturePtr)(base + SEGMENT_OFFSET(gKafeiEyesRollUpTex));
        sPlayerEyesTextures[6] = (TexturePtr)(base + SEGMENT_OFFSET(gKafeiEyesRollDownTex));
        sPlayerEyesTextures[7] = (TexturePtr)(base + SEGMENT_OFFSET(object_test3_Tex_006680));

        sPlayerMouthTextures[0] = (TexturePtr)(base + SEGMENT_OFFSET(gKafeiMouthClosedTex));
        sPlayerMouthTextures[1] = (TexturePtr)(base + SEGMENT_OFFSET(gKafeiMouthTeethTex));
        sPlayerMouthTextures[2] = (TexturePtr)(base + SEGMENT_OFFSET(gKafeiMouthAngryTex));
        sPlayerMouthTextures[3] = (TexturePtr)(base + SEGMENT_OFFSET(gKafeiMouthHappyTex));
    }
    else {
        for (u32 i = 0; i < PLAYER_EYES_MAX; ++i) {
            sPlayerEyesTextures[i] = gVanillaEyesTex[i];
        }

        for (u32 i = 0; i < PLAYER_MOUTH_MAX; ++i) {
            sPlayerMouthTextures[i] = gVanillaMouthsTex[i];
        }
    }
}
