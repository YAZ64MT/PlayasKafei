#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "modelreplacer_api.h"
#include "globalobjects_api.h"
#include "assets/objects/object_test3/object_test3.h"
#include "assets/objects/object_link_child/object_link_child.h"
#include "overlays/actors/ovl_En_Test3/z_en_test3.h"

extern TexturePtr sPlayerEyesTextures[];
extern TexturePtr sPlayerMouthTextures[];

TexturePtr gKafeiEyesTextures[PLAYER_EYES_MAX];
TexturePtr gKafeiMouthTextures[PLAYER_MOUTH_MAX];

extern TexturePtr sEyesTextures[];

u32 gIsKafeiOverLink = 999;

u32 gIsLinkOverKafei = 999;

void setLinkFaceTexOnKafei() {
    u32 base = (uintptr_t)ZGlobalObj_getGlobalObject(OBJECT_LINK_CHILD);

    gKafeiEyesTextures[0] = (TexturePtr)(base + SEGMENT_OFFSET(gLinkHumanEyesOpenTex));
    gKafeiEyesTextures[1] = (TexturePtr)(base + SEGMENT_OFFSET(gLinkHumanEyesHalfTex));
    gKafeiEyesTextures[2] = (TexturePtr)(base + SEGMENT_OFFSET(gLinkHumanEyesClosedTex));
    gKafeiEyesTextures[3] = (TexturePtr)(base + SEGMENT_OFFSET(gLinkHumanEyesRollRightTex));
    gKafeiEyesTextures[4] = (TexturePtr)(base + SEGMENT_OFFSET(gLinkHumanEyesRollLeftTex));
    gKafeiEyesTextures[5] = (TexturePtr)(base + SEGMENT_OFFSET(gLinkHumanEyesRollUpTex));
    gKafeiEyesTextures[6] = (TexturePtr)(base + SEGMENT_OFFSET(gLinkHumanEyesRollDownTex));
    gKafeiEyesTextures[7] = (TexturePtr)(base + SEGMENT_OFFSET(object_link_child_Tex_003800));

    gKafeiMouthTextures[0] = (TexturePtr)(base + SEGMENT_OFFSET(gLinkHumanMouthClosedTex));
    gKafeiMouthTextures[1] = (TexturePtr)(base + SEGMENT_OFFSET(gLinkHumanMouthTeethTex));
    gKafeiMouthTextures[2] = (TexturePtr)(base + SEGMENT_OFFSET(gLinkHumanMouthAngryTex));
    gKafeiMouthTextures[3] = (TexturePtr)(base + SEGMENT_OFFSET(gLinkHumanMouthHappyTex));
}

void setKafeiFaceTexOnLink() {
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

void setKafeiFaceTexOnKafei() {
    gKafeiEyesTextures[0] = gKafeiEyesOpenTex;
    gKafeiEyesTextures[1] = gKafeiEyesHalfTex;
    gKafeiEyesTextures[2] = gKafeiEyesClosedTex;
    gKafeiEyesTextures[3] = gKafeiEyesRollRightTex;
    gKafeiEyesTextures[4] = gKafeiEyesRollLeftTex;
    gKafeiEyesTextures[5] = gKafeiEyesRollUpTex;
    gKafeiEyesTextures[6] = gKafeiEyesRollDownTex;
    gKafeiEyesTextures[7] = object_test3_Tex_006680;

    gKafeiMouthTextures[0] = gKafeiMouthClosedTex;
    gKafeiMouthTextures[1] = gKafeiMouthTeethTex;
    gKafeiMouthTextures[2] = gKafeiMouthAngryTex;
    gKafeiMouthTextures[3] = gKafeiMouthHappyTex;
}

void setLinkFaceTexOnLink() {
    sPlayerEyesTextures[0] = gLinkHumanEyesOpenTex;
    sPlayerEyesTextures[1] = gLinkHumanEyesHalfTex;
    sPlayerEyesTextures[2] = gLinkHumanEyesClosedTex;
    sPlayerEyesTextures[3] = gLinkHumanEyesRollRightTex;
    sPlayerEyesTextures[4] = gLinkHumanEyesRollLeftTex;
    sPlayerEyesTextures[5] = gLinkHumanEyesRollUpTex;
    sPlayerEyesTextures[6] = gLinkHumanEyesRollDownTex;
    sPlayerEyesTextures[7] = object_link_child_Tex_003800;

    sPlayerMouthTextures[0] = gLinkHumanMouthClosedTex;
    sPlayerMouthTextures[1] = gLinkHumanMouthTeethTex;
    sPlayerMouthTextures[2] = gLinkHumanMouthAngryTex;
    sPlayerMouthTextures[3] = gLinkHumanMouthHappyTex;
}

// handless ocarina
Gfx gLinkHumanOcarinaDL[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPClearGeometryMode(G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_CULL_BACK | G_FOG | G_LIGHTING),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(gLinkHumanOcarinaTex, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, 5, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_childVtx_00E858[53], 23, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 3, 2, 0, 4, 2, 1, 0),
    gsSP2Triangles(5, 6, 7, 0, 8, 9, 10, 0),
    gsSP2Triangles(10, 6, 8, 0, 5, 8, 6, 0),
    gsSP2Triangles(11, 9, 0, 0, 10, 9, 11, 0),
    gsSP2Triangles(12, 1, 13, 0, 11, 3, 14, 0),
    gsSP2Triangles(11, 0, 3, 0, 0, 9, 1, 0),
    gsSP2Triangles(12, 4, 1, 0, 1, 9, 8, 0),
    gsSP2Triangles(1, 8, 5, 0, 14, 10, 11, 0),
    gsSP2Triangles(1, 5, 13, 0, 15, 13, 5, 0),
    gsSP2Triangles(15, 5, 7, 0, 7, 14, 15, 0),
    gsSP2Triangles(10, 14, 6, 0, 6, 14, 7, 0),
    gsSP2Triangles(12, 13, 16, 0, 12, 16, 17, 0),
    gsSP2Triangles(17, 18, 15, 0, 15, 16, 13, 0),
    gsSP2Triangles(17, 15, 14, 0, 17, 14, 19, 0),
    gsSP2Triangles(14, 20, 21, 0, 14, 21, 19, 0),
    gsSP2Triangles(4, 20, 3, 0, 3, 20, 14, 0),
    gsSP2Triangles(12, 17, 19, 0, 12, 19, 22, 0),
    gsSP2Triangles(12, 22, 4, 0, 21, 20, 4, 0),
    gsSPEndDisplayList(),
};

// handless first person hookshot
Gfx gLinkHumanFirstPersonHookshotDL[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal256(object_link_child_TLUT_018A40),
    gsDPLoadTextureBlock(object_link_child_Tex_01B380, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_MIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_WRAP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 0x80, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&object_link_childVtx_010538[452], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(2, 4, 5, 0, 2, 5, 0, 0),
    gsSP2Triangles(6, 3, 0, 0, 7, 8, 9, 0),
    gsSP2Triangles(10, 9, 11, 0, 10, 7, 9, 0),
    gsSP2Triangles(12, 13, 14, 0, 15, 12, 14, 0),
    gsSP2Triangles(15, 16, 12, 0, 17, 18, 19, 0),
    gsSP2Triangles(10, 17, 19, 0, 10, 20, 17, 0),
    gsSP2Triangles(21, 22, 23, 0, 24, 23, 25, 0),
    gsSP2Triangles(26, 27, 28, 0, 29, 28, 30, 0),
    gsSPVertex(&object_link_childVtx_010538[483], 31, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP2Triangles(3, 4, 0, 0, 5, 6, 7, 0),
    gsSP2Triangles(5, 7, 2, 0, 8, 5, 2, 0),
    gsSP2Triangles(9, 10, 11, 0, 12, 9, 11, 0),
    gsSP2Triangles(12, 13, 9, 0, 14, 15, 16, 0),
    gsSP2Triangles(17, 18, 19, 0, 14, 17, 19, 0),
    gsSP2Triangles(19, 20, 14, 0, 20, 15, 14, 0),
    gsSP2Triangles(21, 22, 23, 0, 24, 21, 25, 0),
    gsSP2Triangles(26, 27, 28, 0, 29, 26, 30, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal256(object_link_child_TLUT_018A40),
    gsDPLoadTextureBlock(object_link_child_Tex_01A280, G_IM_FMT_CI, G_IM_SIZ_8b, 16, 16, 0, G_TX_MIRROR | G_TX_CLAMP,
                         G_TX_MIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_childVtx_010538[514], 18, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
    gsSP2Triangles(4, 5, 3, 0, 6, 0, 2, 0),
    gsSP2Triangles(3, 0, 4, 0, 2, 7, 6, 0),
    gsSP2Triangles(8, 9, 10, 0, 10, 9, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 15, 13, 12, 0),
    gsSP2Triangles(4, 16, 17, 0, 17, 5, 4, 0),
    gsSP2Triangles(6, 17, 16, 0, 6, 7, 17, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal256(object_link_child_TLUT_018A40),
    gsDPLoadTextureBlock(object_link_child_Tex_019A80, G_IM_FMT_CI, G_IM_SIZ_8b, 32, 64, 0, G_TX_MIRROR | G_TX_CLAMP,
                         G_TX_MIRROR | G_TX_CLAMP, 5, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&object_link_childVtx_010538[532], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(4, 5, 6, 0, 6, 5, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 11, 12, 0, 0),
    gsSP2Triangles(13, 14, 15, 0, 15, 8, 10, 0),
    gsSP2Triangles(0, 13, 11, 0, 4, 16, 17, 0),
    gsSP2Triangles(10, 13, 15, 0, 18, 19, 20, 0),
    gsSP2Triangles(13, 10, 11, 0, 7, 21, 17, 0),
    gsSP2Triangles(17, 20, 19, 0, 22, 23, 24, 0),
    gsSP2Triangles(17, 16, 7, 0, 25, 22, 16, 0),
    gsSP2Triangles(25, 26, 22, 0, 24, 16, 22, 0),
    gsSP2Triangles(27, 21, 28, 0, 24, 7, 16, 0),
    gsSP2Triangles(6, 26, 25, 0, 24, 23, 6, 0),
    gsSP2Triangles(6, 7, 24, 0, 23, 29, 6, 0),
    gsSP2Triangles(25, 4, 6, 0, 6, 29, 26, 0),
    gsSP1Triangle(30, 27, 31, 0),
    gsSPVertex(&object_link_childVtx_010538[564], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 4, 0),
    gsSP2Triangles(5, 6, 7, 0, 8, 6, 5, 0),
    gsSP2Triangles(8, 9, 6, 0, 0, 2, 4, 0),
    gsSP2Triangles(10, 11, 12, 0, 0, 13, 1, 0),
    gsSP2Triangles(0, 14, 13, 0, 15, 4, 16, 0),
    gsSP2Triangles(17, 18, 3, 0, 4, 15, 0, 0),
    gsSP2Triangles(18, 19, 3, 0, 16, 4, 20, 0),
    gsSP2Triangles(3, 21, 22, 0, 15, 11, 23, 0),
    gsSP2Triangles(16, 11, 15, 0, 22, 20, 3, 0),
    gsSP2Triangles(20, 22, 23, 0, 20, 24, 16, 0),
    gsSP2Triangles(25, 26, 27, 0, 22, 28, 0, 0),
    gsSP1Triangle(29, 30, 31, 0),
    gsSPVertex(&object_link_childVtx_010538[596], 11, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 0, 4, 0, 4, 6, 7, 0),
    gsSP2Triangles(4, 2, 6, 0, 8, 4, 7, 0),
    gsSP2Triangles(8, 5, 4, 0, 7, 9, 10, 0),
    gsSP1Triangle(7, 6, 9, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal256(object_link_child_TLUT_018A40),
    gsSPEndDisplayList(),
};

Gfx gKafeiRightHandHoldingOcarinaDL[2];

Gfx gKafeiRightHandHoldingBowFirstPersonDL[2];

Gfx gKafeiRightHandHoldingHookshotFirstPersonDL[2];

void setupCustomDLs() {
    void *human = ZGlobalObj_getGlobalObject(OBJECT_LINK_CHILD);

    ZGlobalObj_rebaseDL(human, gLinkHumanOcarinaDL, 0x06);
    ZGlobalObj_rebaseDL(human, gLinkHumanFirstPersonHookshotDL, 0x06);

    gSPDisplayList(&gKafeiRightHandHoldingOcarinaDL[0], ZGlobalObj_getGlobalGfxPtr(OBJECT_TEST3, gKafeiRightHandDL));
    gSPBranchList(&gKafeiRightHandHoldingOcarinaDL[1], gLinkHumanOcarinaDL);

    gSPDisplayList(&gKafeiRightHandHoldingBowFirstPersonDL[0], ZGlobalObj_getGlobalGfxPtr(OBJECT_TEST3, gKafeiRightHandDL));
    gSPBranchList(&gKafeiRightHandHoldingBowFirstPersonDL[1], ZGlobalObj_getGlobalGfxPtr(OBJECT_LINK_CHILD, gLinkHumanBowDL));

    gSPDisplayList(&gKafeiRightHandHoldingHookshotFirstPersonDL[0], ZGlobalObj_getGlobalGfxPtr(OBJECT_TEST3, gKafeiRightHandDL));
    gSPBranchList(&gKafeiRightHandHoldingHookshotFirstPersonDL[1], gLinkHumanFirstPersonHookshotDL);
}

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

#define SET_KAFEI_OVER_LINK(vanillaLinkDL, vanillaKafeiDL) ZModelReplacer_addCustomDL(OBJECT_LINK_CHILD, vanillaLinkDL, ZGlobalObj_getGlobalGfxPtr(OBJECT_TEST3, vanillaKafeiDL))

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
    SET_KAFEI_OVER_LINK(gLinkHumanRightHandClosedDL, gKafeiRightHandDL);

    ZModelReplacer_addCustomDL(OBJECT_LINK_CHILD, gLinkHumanRightHandHoldingOcarinaDL, gKafeiRightHandHoldingOcarinaDL);
    ZModelReplacer_addCustomDL(OBJECT_LINK_CHILD, object_link_child_DL_018490, gKafeiRightHandHoldingBowFirstPersonDL);
    ZModelReplacer_addCustomDL(OBJECT_LINK_CHILD, object_link_child_DL_017B40, gKafeiRightHandHoldingHookshotFirstPersonDL);
}

#define REMOVE_KAFEI_OVER_LINK(vanillaLinkDL, vanillaKafeiDL) ZModelReplacer_removeCustomDL(OBJECT_LINK_CHILD, vanillaLinkDL, ZGlobalObj_getGlobalGfxPtr(OBJECT_TEST3, vanillaKafeiDL))

void restoreLink() {
    REMOVE_KAFEI_OVER_LINK(gLinkHumanWaistDL, gKafeiWaistDL);
    REMOVE_KAFEI_OVER_LINK(gLinkHumanRightThighDL, gKafeiRightThighDL);
    REMOVE_KAFEI_OVER_LINK(gLinkHumanRightShinDL, gKafeiRightShinDL);
    REMOVE_KAFEI_OVER_LINK(gLinkHumanRightFootDL, gKafeiRightFootDL);
    REMOVE_KAFEI_OVER_LINK(gLinkHumanLeftThighDL, gKafeiLeftThighDL);
    REMOVE_KAFEI_OVER_LINK(gLinkHumanLeftShinDL, gKafeiLeftShinDL);
    REMOVE_KAFEI_OVER_LINK(gLinkHumanLeftFootDL, gKafeiLeftFootDL);
    REMOVE_KAFEI_OVER_LINK(gLinkHumanHeadDL, gKafeiHeadDL);
    REMOVE_KAFEI_OVER_LINK(gLinkHumanHatDL, gKafeiSunMaskEmptyDL);
    REMOVE_KAFEI_OVER_LINK(gLinkHumanCollarDL, gKafeiSunMaskEmptyDL);
    REMOVE_KAFEI_OVER_LINK(gLinkHumanLeftShoulderDL, gKafeiLeftShoulderDL);
    REMOVE_KAFEI_OVER_LINK(gLinkHumanLeftForearmDL, gKafeiLeftForearmDL);
    REMOVE_KAFEI_OVER_LINK(gLinkHumanLeftHandOpenDL, gKafeiLeftHandDL);
    REMOVE_KAFEI_OVER_LINK(gLinkHumanRightShoulderDL, gKafeiRightShoulderDL);
    REMOVE_KAFEI_OVER_LINK(gLinkHumanRightForearmDL, gKafeiRightForearmDL);
    REMOVE_KAFEI_OVER_LINK(gLinkHumanRightHandOpenDL, gKafeiRightHandDL);
    REMOVE_KAFEI_OVER_LINK(gLinkHumanTorsoDL, gKafeiTorsoDL);

    REMOVE_KAFEI_OVER_LINK(gLinkHumanLeftHandClosedDL, gKafeiLeftHandDL);
    REMOVE_KAFEI_OVER_LINK(gLinkHumanLeftHandHoldBottleDL, gKafeiLeftHandDL);
    REMOVE_KAFEI_OVER_LINK(gLinkHumanRightHandClosedDL, gKafeiRightHandDL);

    ZModelReplacer_removeCustomDL(OBJECT_LINK_CHILD, gLinkHumanRightHandHoldingOcarinaDL, gKafeiRightHandHoldingOcarinaDL);
    ZModelReplacer_removeCustomDL(OBJECT_LINK_CHILD, object_link_child_DL_018490, gKafeiRightHandHoldingBowFirstPersonDL);
    ZModelReplacer_removeCustomDL(OBJECT_LINK_CHILD, object_link_child_DL_017B40, gKafeiRightHandHoldingHookshotFirstPersonDL);
}

#define SET_LINK_OVER_KAFEI(vanillaKafeiDL, vanillaLinkDL) ZModelReplacer_addCustomDL(OBJECT_TEST3, vanillaKafeiDL, ZGlobalObj_getGlobalGfxPtr(OBJECT_LINK_CHILD, vanillaLinkDL))

void replaceKafei() {
    SET_LINK_OVER_KAFEI(gKafeiWaistDL, gLinkHumanWaistDL);
    SET_LINK_OVER_KAFEI(gKafeiRightThighDL, gLinkHumanRightThighDL);
    SET_LINK_OVER_KAFEI(gKafeiRightShinDL, gLinkHumanRightShinDL);
    SET_LINK_OVER_KAFEI(gKafeiRightFootDL, gLinkHumanRightFootDL);
    SET_LINK_OVER_KAFEI(gKafeiLeftThighDL, gLinkHumanLeftThighDL);
    SET_LINK_OVER_KAFEI(gKafeiLeftShinDL, gLinkHumanLeftShinDL);
    SET_LINK_OVER_KAFEI(gKafeiLeftFootDL, gLinkHumanLeftFootDL);
    SET_LINK_OVER_KAFEI(gKafeiHeadDL, gLinkHumanHeadDL);
    SET_LINK_OVER_KAFEI(gKafeiSunMaskEmptyDL, gLinkHumanHatDL);
    SET_LINK_OVER_KAFEI(gKafeiSunMaskEmptyDL, gLinkHumanCollarDL);
    SET_LINK_OVER_KAFEI(gKafeiLeftShoulderDL, gLinkHumanLeftShoulderDL);
    SET_LINK_OVER_KAFEI(gKafeiLeftForearmDL, gLinkHumanLeftForearmDL);
    SET_LINK_OVER_KAFEI(gKafeiLeftHandDL, gLinkHumanLeftHandOpenDL);
    SET_LINK_OVER_KAFEI(gKafeiRightShoulderDL, gLinkHumanRightShoulderDL);
    SET_LINK_OVER_KAFEI(gKafeiRightForearmDL, gLinkHumanRightForearmDL);
    SET_LINK_OVER_KAFEI(gKafeiRightHandDL, gLinkHumanRightHandOpenDL);
    SET_LINK_OVER_KAFEI(gKafeiTorsoDL, gLinkHumanTorsoDL);
}

#define REMOVE_LINK_OVER_KAFEI(vanillaKafeiDL, vanillaLinkDL) ZModelReplacer_removeCustomDL(OBJECT_TEST3, vanillaKafeiDL, ZGlobalObj_getGlobalGfxPtr(OBJECT_LINK_CHILD, vanillaLinkDL))

void restoreKafei() {
    REMOVE_LINK_OVER_KAFEI(gKafeiWaistDL, gLinkHumanWaistDL);
    REMOVE_LINK_OVER_KAFEI(gKafeiRightThighDL, gLinkHumanRightThighDL);
    REMOVE_LINK_OVER_KAFEI(gKafeiRightShinDL, gLinkHumanRightShinDL);
    REMOVE_LINK_OVER_KAFEI(gKafeiRightFootDL, gLinkHumanRightFootDL);
    REMOVE_LINK_OVER_KAFEI(gKafeiLeftThighDL, gLinkHumanLeftThighDL);
    REMOVE_LINK_OVER_KAFEI(gKafeiLeftShinDL, gLinkHumanLeftShinDL);
    REMOVE_LINK_OVER_KAFEI(gKafeiLeftFootDL, gLinkHumanLeftFootDL);
    REMOVE_LINK_OVER_KAFEI(gKafeiHeadDL, gLinkHumanHeadDL);
    REMOVE_LINK_OVER_KAFEI(gKafeiSunMaskEmptyDL, gLinkHumanHatDL);
    REMOVE_LINK_OVER_KAFEI(gKafeiSunMaskEmptyDL, gLinkHumanCollarDL);
    REMOVE_LINK_OVER_KAFEI(gKafeiLeftShoulderDL, gLinkHumanLeftShoulderDL);
    REMOVE_LINK_OVER_KAFEI(gKafeiLeftForearmDL, gLinkHumanLeftForearmDL);
    REMOVE_LINK_OVER_KAFEI(gKafeiLeftHandDL, gLinkHumanLeftHandOpenDL);
    REMOVE_LINK_OVER_KAFEI(gKafeiRightShoulderDL, gLinkHumanRightShoulderDL);
    REMOVE_LINK_OVER_KAFEI(gKafeiRightForearmDL, gLinkHumanRightForearmDL);
    REMOVE_LINK_OVER_KAFEI(gKafeiRightHandDL, gLinkHumanRightHandOpenDL);
    REMOVE_LINK_OVER_KAFEI(gKafeiTorsoDL, gLinkHumanTorsoDL);
}

void switchModelsIfNeeded() {
    u32 cfgKafeiOverLink = recomp_get_config_u32("kafei_over_link");
    u32 cfgLinkOverKafei = recomp_get_config_u32("link_over_kafei");
    if (gIsKafeiOverLink != cfgKafeiOverLink) {
        gIsKafeiOverLink = cfgKafeiOverLink;

        if (gIsKafeiOverLink) {
            replaceLink();

            if (GET_PLAYER_FORM == PLAYER_FORM_HUMAN) {
                setKafeiFaceTexOnLink();
            }
        } else {
            restoreLink();
            setLinkFaceTexOnLink();
        }
    }

    if (gIsLinkOverKafei != cfgLinkOverKafei) {
        gIsLinkOverKafei = cfgLinkOverKafei;

        if (gIsLinkOverKafei) {
            replaceKafei();
            setLinkFaceTexOnKafei();
        } else {
            restoreKafei();
            setKafeiFaceTexOnKafei();
        }
    }
}

// make sure the sword can be replaced w/o an object reload
RECOMP_CALLBACK(YAZMT_Z64_MODEL_REPLACER_MOD_NAME, ZModelReplacer_onReady)
void onModelReplacerReady() {
    preregisterLinkDLs();
    setupCustomDLs();
    switchModelsIfNeeded();
}

RECOMP_HOOK("Player_Init")
void updateModel_on_Player_Init(Actor *thisx, PlayState *play) {
    if (GET_PLAYER_FORM == PLAYER_FORM_HUMAN && gIsKafeiOverLink) {
        setKafeiFaceTexOnLink();
    } else {
        setLinkFaceTexOnLink();
    }
}

Player *gPlayer;
PlayerTransformation gPlayerTransformation;
PlayState *gPlayState;
s32 gLimbIndex;
Gfx **gFirstPersonDList;

// restore left forearm display list
RECOMP_HOOK("Player_OverrideLimbDrawGameplayFirstPerson")
void pre_OverrideLimbDrawFirstPerson(PlayState *play, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *actor) {
    gPlayState = play;
    gLimbIndex = limbIndex;
    gFirstPersonDList = dList;
}

RECOMP_HOOK_RETURN("Player_OverrideLimbDrawGameplayFirstPerson")
void post_OverrideLimbDrawFirstPerson() {
    if (gLimbIndex == PLAYER_LIMB_RIGHT_FOREARM) {
        *gFirstPersonDList = gLinkHumanRightForearmDL;
    }
}

Actor *gKafeiActor = NULL;

RECOMP_HOOK("EnTest3_Draw")
void grabKafei_on_EnTest3_Draw(Actor *thisx, PlayState *play2) {
    gKafeiActor = thisx;
}

RECOMP_HOOK_RETURN("EnTest3_Draw")
void releaseKafei_post_EnTest3_Draw() {
    gKafeiActor = NULL;
}

typedef struct {
    /* 0x0 */ u8 eyeIndex;
    /* 0x1 */ u8 mouthIndex;
} KafeiFace; // size = 0x2

static KafeiFace sFaceExpressions[] = {
    {0, 0},
    {1, 0},
    {2, 0},
    {0, 0},
    {1, 0},
    {2, 0},
    {4, 0},
    {5, 1},
    {7, 2},
    {0, 2},
    {3, 0},
    {4, 0},
    {2, 2},
    {1, 1},
    {0, 2},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
};

RECOMP_HOOK("SkelAnime_DrawFlexLod")
void replaceKafeiEyes_on_SkelAnime_DrawFlexLod(PlayState *play, void **skeleton, Vec3s *jointTable, s32 dListCount, OverrideLimbDrawFlex overrideLimbDraw, PostLimbDrawFlex postLimbDraw, Actor *actor, s32 lod) {
    if (gKafeiActor == actor) {
        Player *this = (Player *)actor;
        s32 eyeTexIndex = GET_EYE_INDEX_FROM_JOINT_TABLE(this->skelAnime.jointTable);
        s32 mouthTexIndex = GET_MOUTH_INDEX_FROM_JOINT_TABLE(this->skelAnime.jointTable);

        if (eyeTexIndex < 0) {
            eyeTexIndex = sFaceExpressions[this->actor.shape.face].eyeIndex;
        }
        if (mouthTexIndex < 0) {
            mouthTexIndex = sFaceExpressions[this->actor.shape.face].mouthIndex;
        }

        gSegments[0x08] = (uintptr_t)gKafeiEyesTextures[eyeTexIndex];
        gSegments[0x09] = (uintptr_t)gKafeiMouthTextures[mouthTexIndex];
    }
}

RECOMP_HOOK("Player_Update")
void pollModelChange(Actor *thisx, PlayState *play) {
    gKafeiActor = NULL;
    switchModelsIfNeeded();
}

RECOMP_HOOK("EnTest3_Init")
on_EnTest3_Init(Actor *thisx, PlayState *play2) {

}
