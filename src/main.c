#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "playermodelmanager_api.h"
#include "kafei.h"

PLAYERMODELMANAGER_CALLBACK_REGISTER_MODELS void registerKafei() {
    setupKafeiAssets();

    // PlayerModelManager stuff
    PlayerModelManagerHandle h = PLAYERMODELMANAGER_REGISTER_MODEL("mm_kafei_pmm_built_in", PMM_MODEL_TYPE_CHILD);

    PlayerModelManager_setAuthor(h, "Nintendo");
    PlayerModelManager_setDisplayName(h, "Kafei");
    PlayerModelManager_setEyesTextures(h, gKafeiEyeTextures);
    PlayerModelManager_setMouthTextures(h, gKafeiMouthTextures);

    PlayerModelManager_setSkeleton(h, &gKafeiSkeleton);

    PlayerModelManager_setDisplayList(h, PMM_DL_LFIST, gKafeiLeftFist);
    PlayerModelManager_setDisplayList(h, PMM_DL_RFIST, gKafeiRightFist);
    PlayerModelManager_setDisplayList(h, PMM_DL_LHAND_BOTTLE, gKafeiLeftHandBottle);
    PlayerModelManager_setDisplayList(h, PMM_DL_FPS_RHAND, gKafeiFPSRightHand);
    PlayerModelManager_setDisplayList(h, PMM_DL_FPS_RFOREARM, gKafeiFPSRightForearm);
    PlayerModelManager_setDisplayList(h, PMM_DL_FPS_LHAND, gKafeiFPSLeftHand);
    PlayerModelManager_setDisplayList(h, PMM_DL_FPS_LFOREARM, gKafeiFPSLeftForearm);
}
