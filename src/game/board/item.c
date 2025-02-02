#include "game/board/item.h"
#include "game/audio.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfanim.h"
#include "game/hsfman.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/window.h"
#include "game/wipe.h"
#include "game/board/audio.h"
#include "game/board/com.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/ui.h"
#include "game/board/window.h"

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ float unk04;
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ Vec unk10;
} UnkItemProcUserData; // Size unknown

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ float unk04;
    /* 0x08 */ float unk08;
    /* 0x0C */ char unk0C[4];
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
    /* 0x18 */ float unk18;
    /* 0x1C */ s16 unk1C;
} UnkItemShowProcStruct; // Size unknown

typedef struct {
    /* 0x00 */ float unk00;
    /* 0x04 */ Vec unk04;
    /* 0x04 */ Vec unk10;
} UnkGenieCameraStruct; // Size 0x1C

u32 frandmod(u32);
void CharModelCreateParticle(s32, Vec*);
void CharModelLayerSetAll(s32);
void BoardBowserSuitInit(s32);
s16 BoardBowserSuitPlayerModelGet(void);
void fn_8004F578(s16, s32);

static void ItemProcess(void);
static void RestoreProcess(void);
static void ItemDestroy(void);
static void RestoreDestroy(void);
static void ItemSizeShowAnim(void);
static void ItemRotProc(void);
static Process *ItemShowProc(UnkItemShowProcStruct *arg0, Vec *arg1);
static s16 ItemGetTarget(void);
static void ItemSizeSet(s32 arg0);
static void ExecItemMini(void);
static void ExecItemMega(void);
static void ExecItemMiniSuper(void);
static void ExecItemMegaSuper(void);
static void ExecItemHammer(void);
static void ExecItemPipe(void);
static void ExecItemSwap(void);
static void ExecItemSpark(void);
static void ExecItemLight(void);
static void ExecItemWhistle(void);
static void ExecItemBowser(void);
static void ExecItemBooBall(void);
static void LampParticleUpdate(s32 arg0, ParticleData *arg1);
static void GenieParticleUpdate(s32 arg0, ParticleData *arg1);
static void GenieCameraProc(void);
static void GenieCameraCalc(UnkGenieCameraStruct *arg0, s32 arg1, float arg2, Vec *arg3, Vec *arg4);
static void GenieSceneExec(void);
static void ExecItemGenie(void);
static void ExecItemBagJump(void);
static void ExecItemBagShow(void);
static void ExecItemBag(void);
static void RestoreItemNull(void);
static void RestoreItemMini(void);
static void RestoreItemMega(void);
static void RestoreItemMiniSuper(void);
static void RestoreItemMegaSuper(void);
static void RestoreItemBowser(void);

// BSS
static Vec booBallScale;
static Vec booBallPos;
static Vec booCamUp;
static Vec booCamTarget;
static Vec booCamPos;

// SBSS
static s16 itemBagItems[3];
static s8 currItemRestore;
static s8 currItem;
static s16 suitMdl;
static s32 suitMot[2];
static s32 suitCommonMot[2];
// ...
static float genieFov;
static AnimData *genieParticleAnim;
static s16 geniePlayerMot[3];
static Process *itemProc;

// SDATA
s32 lbl_801D37A0[2] = { 0x00070075, -1 };

// DATA
static void (*itemFuncTbl[])(void) = {
    ExecItemMini,
    ExecItemMega,
    ExecItemMiniSuper,
    ExecItemMegaSuper,
    ExecItemHammer,
    ExecItemPipe,
    ExecItemSwap,
    ExecItemSpark,
    ExecItemLight,
    ExecItemWhistle,
    ExecItemBowser,
    ExecItemBooBall,
    ExecItemGenie,
    ExecItemBag
};

// DATA + 0x38
static void (*itemRestoreFuncTbl[])(void) = {
    RestoreItemMini,
    RestoreItemMega,
    RestoreItemMiniSuper,
    RestoreItemMegaSuper,
    RestoreItemNull,
    RestoreItemNull,
    RestoreItemNull,
    RestoreItemNull,
    RestoreItemNull,
    RestoreItemNull,
    RestoreItemBowser,
    RestoreItemNull,
    RestoreItemNull,
    RestoreItemNull
};

// DATA + 0x70
static s32 itemMdlTbl[] = {
    0x0007006D,
    0x0007006E,
    0x0007006F,
    0x00070070,
    0x00070071,
    0x00070072,
    0x00070073,
    0x00070074,
    0x00070076,
    0x00070077,
    0x00070078,
    0x00070079,
    0x0007007A,
    0x0007007B
};

// DATA + 0xA8
static s32 forceMoveSfxTbl[] = {
    0x38, 0x45, 0x42, 0x4D, 0x48, 0x3F
};

// DATA + 0xC0
static s32 callMotTbl[] = {
    0x005F0052,
    0x001A0052,
    0x006D0052,
    0x008A0052,
    0x00850052,
    0x00110052,
    0x000D0052,
    0x00810052
};

// DATA + 0xE0
// callHookTbl items

// DATA + 0x178
static char *callHookTbl[] = {
    "c000m01-itemhook-r",
    "c001m01-itemhook-r",
    "c002m01-itemhook-r",
    "c003m01-itemhook-r",
    "c004m01-itemhook-r",
    "c005m01-itemhook-r",
    "c006m01-itemhook-r",
    "c007m01-itemhook-r"
};

// DATA + 0x198
static s32 callAttackMotTbl[] = {
    0x0075001F,
    0x00760005,
    0x0077001D,
    0x00780009,
    0x00790007,
    0x007A0013
};

// DATA + 0x1B0
static s32 callAttackMotTbl2[] = {
    0x00750020,
    0x00760006,
    0x0077001E,
    0x0078000A,
    0x00790008,
    0x007A0014
};

// DATA + 0x1C8
static s32 suitMotTbl[][2] = {
    { 0x00040001, 0x00040002 },
    { 0x00040004, 0x00040005 },
    { 0x00040007, 0x00040008 },
    { 0x0004000A, 0x0004000B },
    { 0x0004000D, 0x0004000E },
    { 0x00040010, 0x00040011 },
    { 0x00040013, 0x00040014 },
    { 0x00040016, 0x00040017 }
};

void BoardItemStart(s32 arg0, s32 arg1) {
    currItemRestore = arg0;
    currItem = arg1;
    suitMdl = -1;
    itemProc = HuPrcChildCreate(ItemProcess, 0x2004, 0x1000, 0, boardMainProc);
    HuPrcDestructorSet2(itemProc, ItemDestroy);
}

BOOL BoardItemDoneCheck(void) {
    if (itemProc) {
        return FALSE;
    } else {
        return TRUE;
    }
}

void BoardItemPlayerRestore(s32 arg0, s32 arg1) {
    currItemRestore = arg0;
    currItem = arg1;
    itemProc = HuPrcChildCreate(RestoreProcess, 0x2004, 0x1000, 0, boardMainProc);
    HuPrcDestructorSet2(itemProc, RestoreDestroy);
}

static void ItemProcess(void) {
    void (*temp_r31)(void) = itemFuncTbl[currItem];

    HuPrcChildCreate(temp_r31, 0x2003, 0x1000, 0, HuPrcCurrentGet());
    HuPrcChildWatch();
    HuPrcEnd();
}

static void RestoreProcess(void) {
    void (*temp_r31)(void) = itemRestoreFuncTbl[currItem];

    HuPrcChildCreate(temp_r31, 0x2003, 0x1000, 0, HuPrcCurrentGet());
    HuPrcChildWatch();
    HuPrcEnd();
}

static void ItemDestroy(void) {
    itemProc = NULL;
}

static void RestoreDestroy(void) {
    itemProc = NULL;
}

static void ItemSizeShowAnim(void) {
    Vec sp24;
    Vec sp18;
    Vec spC;
    float sp8;
    float var_f31;
    s32 i;

    sp8 = 1.0f;
    var_f31 = 180.0f;
    BoardPlayerPosGet(currItemRestore, &sp24);
    BoardPlayerRotGet(currItemRestore, &spC);
    sp24.y += 300.0f;
    sp18.x = sp18.y = sp18.z = 1.0f;
    BoardModelRotSetV(suitMdl, &spC);
    BoardModelPosSetV(suitMdl, &sp24);
    for (i = 0; i < 120; i++) {
        sp24.y += 3.0 * sin(M_PI * var_f31 / 180.0);
        BoardModelPosSetV(suitMdl, &sp24);
        var_f31 += 9.0f;
        if (var_f31 >= 360.0f) {
            var_f31 -= 360.0f;
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 30; i++) {
        sp24.y -= 6.6666665f;
        sp18.x -= 0.03f;
        sp18.y -= 0.03f;
        sp18.z -= 0.03f;
        BoardModelScaleSetV(suitMdl, &sp18);
        BoardModelPosSetV(suitMdl, &sp24);
        HuPrcVSleep();
    }
    BoardModelKill(suitMdl);
}

static void ItemRotProc(void) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    UnkItemProcUserData *temp_r31;

    temp_r31 = HuPrcCurrentGet()->user_data;
    BoardModelPosGet(temp_r31->unk02, &sp20);
    BoardModelRotGet(temp_r31->unk02, &sp8);
    temp_r31->unk0C = 0.0f;
    while (1) {
        if (temp_r31->unk00 == 0) {
            sp14 = sp20;
            sp14.y += temp_r31->unk04 * sin(M_PI * temp_r31->unk0C / 180.0);
            BoardModelPosSetV(temp_r31->unk02, &sp14);
            temp_r31->unk0C += temp_r31->unk08;
            if (temp_r31->unk0C >= 360.0f) {
                temp_r31->unk0C -= 360.0f;
            }
            PSVECAdd(&sp8, &temp_r31->unk10, &sp8);
            if (sp8.x < 0.0f) {
                sp8.x += 360.0f;
            }
            if (sp8.x >= 360.0f) {
                sp8.x -= 360.0f;
            }
            if (sp8.y < 0.0f) {
                sp8.y += 360.0f;
            }
            if (sp8.y >= 360.0f) {
                sp8.y -= 360.0f;
            }
            if (sp8.z < 0.0f) {
                sp8.z += 360.0f;
            }
            if (sp8.z >= 360.0f) {
                sp8.z -= 360.0f;
            }
            BoardModelRotSetV(temp_r31->unk02, &sp8);
        }
        HuPrcVSleep();
    }
}

// TODO: needs the inline keyword to be inlined into ExecItemHammer, but adding it messes up sdata2.
// sdata2 order should be: 1000.0f, 0.15f, then 20.0f.
// With the inline keyword, it becomes 0.15f, 20.0f, then 1000.0f (workaround in BoardUiInlineFunc02 below).
static inline void BoardUiInlineFunc01(Vec *arg0) {
    Vec sp30;
    Vec sp3C;
    Vec sp48;
    Vec sp54;
    float spC;
    float var_f31;
    s32 i;

    spC = 1.0f;
    BoardPlayerPosGet(currItemRestore, &sp30);
    BoardPlayerRotGet(currItemRestore, &sp48);
    sp3C = sp30;
    sp3C.y += 1000.0f;
    sp54.x = sp54.y = sp54.z = 1.0f;
    BoardModelRotSetV(suitMdl, &sp48);
    BoardModelPosSetV(suitMdl, &sp3C);
    while (1) {
        var_f31 = 0.15f * (sp3C.y - (sp30.y + 300.0f));
        if (var_f31 > 20.0f) {
            var_f31 = 20.0f;
        }
        if (var_f31 < 1.0f) {
            var_f31 = 1.0f;
        }
        if (fabs(sp3C.y - (sp30.y + 300.0f)) < var_f31) {
            break;
        }
        sp3C.y -= var_f31;
        BoardModelPosSetV(suitMdl, &sp3C);
        PSVECAdd(&sp48, arg0, &sp48);
        for (i = 0; i < 3; i++) {
            if (((float*) &sp48)[i] < 0.0f) {
                ((float*) &sp48)[i] += 360.0f;
            }
            if (((float*) &sp48)[i] >= 360.0f) {
                ((float*) &sp48)[i] -= 360.0f;
            }
        }
        BoardModelRotSetV(suitMdl, &sp48);
        HuPrcVSleep();
    }
    sp3C.y = sp30.y + 300.0f;
    BoardModelPosSetV(suitMdl, &sp3C);
}

static void BoardUiInlineFunc02(void) {
    Vec sp18;
    Vec sp24;
    float sp8;
    float var_f30;

    (void) 1000.0f; // TODO: fix this.
    sp8 = 1.0f;
    BoardModelPosGet(suitMdl, &sp24);
    BoardPlayerPosGet(currItemRestore, &sp18);
    while (1) {
        var_f30 = 0.15f * (sp24.y - sp18.y - 300.0f);
        if (var_f30 > 20.0f) {
            var_f30 = 20.0f;
        }
        if (var_f30 < 1.0f) {
            var_f30 = 1.0f;
        }
        if (fabs(sp24.y - 1000.0f) <= var_f30) {
            break;
        }
        sp24.y += var_f30;
        BoardModelPosSetV(suitMdl, &sp24);
        HuPrcVSleep();
    }
    sp24.y = 1000.0f;
    BoardModelPosSetV(suitMdl, &sp24);
}

static inline void BoardUiInlineFunc03(s32 arg0) {
    Vec sp8;
    Vec sp14;

    BoardSpacePosGet(0, GWPlayerSpaceCurrGet(arg0), &sp14);
    BoardPlayerPosGet(arg0, &sp8);
    BoardPlayerPosLerpStart(arg0, &sp8, &sp14, 0x14);
    while (GWPlayer[arg0].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotBlendSet(arg0, 0, 7);
    while (!BoardPlayerMotBlendCheck(arg0)) {
        HuPrcVSleep();
    }
    BoardRotateDiceNumbers(arg0);
}

static inline void BoardUiInlineFunc04(Process *arg0, s32 arg1) {
    UnkItemShowProcStruct *temp_r19 = arg0->user_data;

    temp_r19->unk00 = arg1;
}

static inline Process *BoardUiInlineFunc05(UnkItemShowProcStruct *arg0) {
    Process *temp_r27;

    temp_r27 = HuPrcCreate(ItemRotProc, 0x2004, 0x1000, 0);
    temp_r27->user_data = arg0;
    BoardUiInlineFunc04(temp_r27, 0);
    return temp_r27;
}

static Process *ItemShowProc(UnkItemShowProcStruct *arg0, Vec *arg1) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    Process *var_r29;

    var_r29 = NULL;
    BoardPlayerPosGet(currItemRestore, &sp20);
    BoardPlayerRotGet(currItemRestore, &sp14);
    sp20.y += 300.0f;
    if (currItem == 0xD) {
        sp20.y -= 50.0f;
    }
    if (arg1 == NULL) {
        sp8.x = sp8.y = sp8.z = 1.0f;
    } else {
        sp8 = *arg1;
    }
    if (suitMdl >= 0) {
        BoardModelLayerSet(suitMdl, 2);
        BoardModelRotSetV(suitMdl, &sp14);
        BoardModelPosSetV(suitMdl, &sp20);
        BoardModelScaleSetV(suitMdl, &sp8);
        BoardModelVisibilitySet(suitMdl, 0);
    }
    BoardCameraRotGet(&sp14);
    if (arg0 == NULL || arg0->unk1C != 0) {
        CharModelLayerSetAll(3);
        sp20.y += 35.0f;
        sp20.z += 50.0 * cos(sp14.y * M_PI / 180.0);
        sp20.x += 50.0 * sin(sp14.y * M_PI / 180.0);
        CharModelCreateParticle(1, &sp20);
        HuPrcSleep(0xA);
    }
    if (suitMdl >= 0) {
        BoardModelVisibilitySet(suitMdl, 1);
        if (arg0 != NULL) {
            var_r29 = BoardUiInlineFunc05(arg0);
        }
    }
    HuPrcSleep(30);
    return var_r29;
}

static s16 ItemGetTarget(void) {
    s32 sp20[4];
    s32 sp10[4];
    float sp8[2];
    s16 temp_r22;
    s16 temp_r29;
    s32 temp_r24;
    s32 var_r28;
    s32 temp_r21;
    s32 var_r27;
    u8 var_r26;
    s32 var_r25;
    s32 var_r30;
    s32 var_r31;
    s32 temp_r23;

    var_r28 = 0;
    var_r27 = 0;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (var_r31 != currItemRestore) {
            sp20[var_r27++] = var_r31;
            HuWinInsertMesSizeGet(GWPlayerCfg[var_r31].character, var_r28);
            var_r28++;
        }
    }
    HuWinMesMaxSizeGet(1, sp8, 0x12000E);
    temp_r29 = HuWinCreate(-10000.0f, -10000.0f, sp8[0], sp8[1], 0);
    if (!GWPlayer[currItemRestore].com) {
        winData[temp_r29].active_pad = (1 << GWPlayer[currItemRestore].port);
    }
    for (var_r31 = 0; var_r31 < var_r27; var_r31++) {
        HuWinInsertMesSet(temp_r29, GWPlayerCfg[sp20[var_r31]].character, var_r31);
    }
    HuWinMesSet(temp_r29, 0x12000E);
    if (GWPlayer[currItemRestore].com) {
        var_r26 = 0xF;
    } else {
        var_r26 = 0;
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if (var_r31 != currItemRestore) {
                var_r26 = (1 << GWPlayer[var_r31].port);
            }
        }
    }
    HuWinDisablePlayerSet(temp_r29, var_r26);
    if (GWPlayer[currItemRestore].com) {
        temp_r23 = GWPlayer[currItemRestore].port;
        temp_r21 = frandmod(3);
        temp_r24 = GWMessDelayGet();
        for (var_r25 = 0; var_r25 < temp_r21; var_r25++) {
            for (var_r30 = 0; var_r30 < 4; var_r30++) {
                sp10[var_r30] = 0;
            }
            sp10[temp_r23] = 4;
            HuWinComKeyWait(sp10[0], sp10[1], sp10[2], sp10[3], temp_r24);
        }
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            sp10[var_r30] = 0;
        }
        sp10[temp_r23] = 0x100;
        HuWinComKeyWait(sp10[0], sp10[1], sp10[2], sp10[3], temp_r24);
    }
    HuWinAttrSet(temp_r29, 0x10);
    HuWinMesSpeedSet(temp_r29, 0);
    temp_r22 = sp20[HuWinChoiceGet(temp_r29, 0)];
    HuWinKill(temp_r29);
    return temp_r22;
}

static void ItemSizeSet(s32 arg0) {
    float sp24[9];
    float sp14[4];
    float sp8[3] = { 1.0f, 0.3f, 2.5f };
    float var_f31;
    float temp_f30;
    s16 temp_r28;
    s32 var_r27;
    s16 temp_r26;
    s32 i;
    s32 j;

    var_f31 = sp8[BoardPlayerSizeGet(currItemRestore)];
    sp14[0] = var_f31;
    sp14[1] = var_f31 + (sp8[arg0] - var_f31) / 3.0f;
    sp14[2] = var_f31 + (sp8[arg0] - var_f31) / 1.5f;
    sp14[3] = sp8[arg0];
    sp24[0] = sp14[1];
    sp24[1] = sp14[0];
    sp24[2] = sp14[1];
    sp24[3] = sp14[2];
    sp24[4] = sp14[1];
    sp24[5] = sp14[2];
    sp24[6] = sp14[3];
    sp24[7] = sp14[2];
    sp24[8] = sp14[3];
    temp_r26 = BoardPlayerModelGet(currItemRestore);
    temp_r28 = BoardModelIDGet(temp_r26);
    Hu3DModelAttrSet(temp_r28, 0x40000002);
    var_r27 = 0;
    for (i = 0; i < 9; i++) {
        temp_f30 = (sp24[var_r27++] - var_f31) / 10.0f;
        for (j = 0; j < 10; j++) {
            BoardPlayerScaleSet(currItemRestore, var_f31, var_f31, var_f31);
            var_f31 += temp_f30;
            HuPrcVSleep();
        }
    }
    Hu3DModelAttrReset(temp_r28, 0x40000002);
    BoardPlayerSizeSet(currItemRestore, arg0);
}

static void ExecItemMini(void) {
    suitMdl = BoardModelCreate(itemMdlTbl[currItem], NULL, 0);
    BoardModelLayerSet(suitMdl, 2);
    HuAudFXPlay(0x350);
    ItemShowProc(NULL, NULL);
    ItemSizeShowAnim();
    HuAudFXPlay(0x314);
    omVibrate(currItemRestore, 90, 6, 6);
    HuAudFXPlay(0x313);
    ItemSizeSet(1);
    HuPrcSleep(0x3C);
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

static void ExecItemMega(void) {
    suitMdl = BoardModelCreate(itemMdlTbl[currItem], NULL, 0);
    BoardModelLayerSet(suitMdl, 2);
    HuAudFXPlay(0x350);
    ItemShowProc(NULL, NULL);
    ItemSizeShowAnim();
    HuAudFXPlay(0x312);
    omVibrate(currItemRestore, 90, 4, 2);
    HuAudFXPlay(0x311);
    ItemSizeSet(2);
    HuPrcSleep(0x3C);
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

static void ExecItemMiniSuper(void) {
    suitMdl = BoardModelCreate(itemMdlTbl[currItem], NULL, 0);
    BoardModelLayerSet(suitMdl, 2);
    HuAudFXPlay(0x350);
    ItemShowProc(NULL, NULL);
    ItemSizeShowAnim();
    HuAudFXPlay(0x314);
    omVibrate(currItemRestore, 90, 4, 2);
    HuAudFXPlay(0x313);
    ItemSizeSet(1);
    HuPrcSleep(0x3C);
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

static void ExecItemMegaSuper(void) {
    suitMdl = BoardModelCreate(itemMdlTbl[currItem], NULL, 0);
    BoardModelLayerSet(suitMdl, 2);
    HuAudFXPlay(0x350);
    ItemShowProc(NULL, NULL);
    ItemSizeShowAnim();
    HuAudFXPlay(0x312);
    omVibrate(currItemRestore, 90, 0xC, 0);
    HuAudFXPlay(0x311);
    ItemSizeSet(2);
    HuPrcSleep(0x3C);
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

static void ExecItemHammer(void) {
    Vec sp6C;
    Vec sp60;
    float sp10[2];
    s32 i;
    s16 temp_r28;
    s16 temp_r27;
    s16 var_r26;
    s16 var_r30;

    HuAudFXPlay(0x350);
    ItemShowProc(NULL, NULL);
    temp_r27 = ItemGetTarget();
    suitMdl = BoardModelCreate(itemMdlTbl[currItem], NULL, 0);
    BoardModelLayerSet(suitMdl, 2);
    var_r30 = frand() & 1;
    if (var_r30 != 0) {
        BoardModelMotionTimeSet(suitMdl, 1.5f);
    } else {
        BoardModelMotionTimeSet(suitMdl, 0.0f);
    }
    BoardModelAttrSet(suitMdl, 0x40000002);
    sp60.x = sp60.y = sp60.z = 2.0f;
    BoardModelScaleSetV(suitMdl, &sp60);
    sp6C.x = sp6C.y = sp6C.z = 0.0f;
    BoardUiInlineFunc01(&sp6C);
    HuWinMesMaxSizeGet(1, sp10, 0x120011);
    temp_r28 = HuWinCreate(-10000.0f, 320.0f, sp10[0], sp10[1], 0);
    HuWinMesSet(temp_r28, 0x120011);
    HuWinBGTPLvlSet(temp_r28, 0.0f);
    HuWinMesSpeedSet(temp_r28, 0);
    if (GWPlayer[currItemRestore].com) {
        var_r26 = frandmod(0x78) + 0x1E;
    }
    for (i = 1; i <= 0x12C; i++) {
        if (i % 10 == 0) {
            HuAudFXPlay(0x315);
            var_r30 ^= 1;
            if (var_r30 != 0) {
                BoardModelMotionTimeSet(suitMdl, 1.5f);
            } else {
                BoardModelMotionTimeSet(suitMdl, 0.0f);
            }
        }
        if (GWPlayer[currItemRestore].com) {
            var_r26--;
            if (var_r26 == 0) {
                break;
            }
        } else {
            if (HuPadBtnDown[GWPlayerCfg[currItemRestore].pad_idx] & 0x100) {
                break;
            }
        }
        HuPrcVSleep();
    }
    BoardModelAttrSet(suitMdl, 0x40000002);
    HuAudFXPlay(0x316);
    HuWinKill(temp_r28);
    omVibrate(temp_r27, 0xC, 6, 6);
    if (var_r30 != 0) {
        BoardPlayerAutoSizeSet(temp_r27, 2);
    } else {
        BoardPlayerAutoSizeSet(temp_r27, 1);
    }
    HuPrcSleep(30);
    BoardUiInlineFunc02();
    BoardModelKill(suitMdl);
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

// https://decomp.me/scratch/QqVh2
static void ExecItemPipe(void) {
}

// https://decomp.me/scratch/r8MWA
static void ExecItemSwap(void) {
    (void) 0.033333335f;
    (void) 3.3333333f;
    (void) 5.0f;
    (void) 0.05f;
    (void) 0.65f;
    (void) 1.08f;
    (void) 19.0f;
    (void) 0.06666667f;
    (void) 0.25f;
    (void) 8.0f;
    (void) 0.044444446f;
    (void) 45.0f;
    (void) 0.94f;
    (void) 6.0f;
    (void) 0.6f;
    (void) 255.0f;
    (void) 1.02f;
    (void) 5.6666665f;
    (void) 4503601774854144.0;
    (void) 106.0;
}

void ExecItemSpark(void) {
    Vec sp68;
    Vec sp5C;
    Vec sp50;
    Vec sp44;
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    float var_f31;
    float var_f30;
    s32 temp_r28;
    s16 temp_r30;
    s32 i;

    temp_r30 = BoardModelCreate(0x70067, NULL, 0);
    BoardModelLayerSet(temp_r30, 3);
    BoardModelVisibilitySet(temp_r30, 0);
    HuAudFXPlay(0x350);
    suitMdl = BoardModelCreate(itemMdlTbl[currItem], lbl_801D37A0, 0);
    BoardModelLayerSet(suitMdl, 2);
    ItemShowProc(NULL, NULL);
    temp_r28 = GWPlayer[currItemRestore].space_curr;
    sp38.x = sp38.y = sp38.z = 1.0f;
    for (i = 0; i < 0x1E; i++) {
        sp38.x += 0.033333335f;
        sp38.y += 0.033333335f;
        sp38.z += 0.033333335f;
        BoardModelScaleSetV(suitMdl, &sp38);
        HuPrcVSleep();
    }
    sp38.x = sp38.y = sp38.z = 2.0f;
    BoardModelScaleSetV(suitMdl, &sp38);
    HuAudFXPlay(0x31A);
    BoardPlayerPosGet(currItemRestore, &sp44);
    BoardSpaceCornerPosGet(temp_r28, 0, &sp50);
    BoardPlayerPosLerpStart(currItemRestore, &sp44, &sp50, 0x14);
    while (GWPlayer[currItemRestore].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotBlendSet(currItemRestore, 0, 7);
    while (!BoardPlayerMotBlendCheck(currItemRestore)) {
        HuPrcVSleep();
    }
    BoardRotateDiceNumbers(currItemRestore);
    BoardSpacePosGet(0, temp_r28, &sp5C);
    BoardModelPosSetV(temp_r30, &sp5C);
    sp5C.y += 106.0f;
    BoardModelPosGet(suitMdl, &sp68);
    var_f30 = -3.0f;
    while (1) {
        sp68.y += var_f30;
        if (sp68.y <= sp5C.y) {
            break;
        }
        BoardModelPosSetV(suitMdl, &sp68);
        var_f30 *= 1.08f;
        HuPrcVSleep();
    }
    sp68.y = sp5C.y;
    BoardModelPosSetV(suitMdl, &sp68);
    sp5C.y -= 106.0f;
    BoardSpaceRotGet(0, GWPlayer[currItemRestore].space_curr, &sp20);
    BoardModelRotSetV(suitMdl, &sp20);
    BoardModelPosGet(suitMdl, &sp2C);
    sp2C.z += 106.0 * sin(M_PI * sp20.x / 180.0);
    sp2C.x -= 106.0 * sin(M_PI * sp20.z / 180.0);
    BoardModelPosSetV(suitMdl, &sp2C);
    HuAudFXPlay(0x31B);
    BoardModelMotionStart(suitMdl, 1, 0);
    BoardModelMotionTimeSet(suitMdl, 0.0f);
    while (BoardModelMotionTimeGet(suitMdl) < BoardModelMotionMaxTimeGet(suitMdl)) {
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        omVibrate(i, 0xC, 4, 2);
    }
    HuAudFXPlay(0x31C);
    BoardModelVisibilitySet(temp_r30, 1);
    BoardModelMotionTimeSet(temp_r30, 0.0f);
    while (BoardModelMotionTimeGet(temp_r30) < BoardModelMotionMaxTimeGet(temp_r30)) {
        HuPrcVSleep();
    }
    var_f31 = 255.0f;
    for (i = 0; i < 0x2D; i++) {
        var_f31 -= 5.6666665f;
        BoardModelAlphaSet(suitMdl, var_f31);
        HuPrcVSleep();
    }
    BoardModelAlphaSet(suitMdl, 0);
    BoardUiInlineFunc03(currItemRestore);
    BoardModelKill(suitMdl);
    BoardModelKill(temp_r30);
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

static void ExecItemLight(void) {
    s16 temp_r31;

    HuAudFXPlay(0x350);
    ItemShowProc(NULL, NULL);
    BoardWinCreateChoice(2, 0x12000F, -1, 0);
    BoardWinInsertMesSet(0x80008, 3);
    if (GWPlayer[currItemRestore].com) {
        BoardComKeySetRight();
    }
    BoardWinWait();
    temp_r31 = BoardWinChoiceGet();
    BoardWinKill();
    if (temp_r31 == -1 || temp_r31 == 0) {
        BoardPlayerItemAdd(boardItemUser, currItem);
    }
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

// https://decomp.me/scratch/gbgTk
static void ExecItemWhistle(void) {
    (void) 0.003921569f;
    (void) 0.5f;
    (void) 120.0f;
    (void) 120.0;
    (void) 100.0f;
    (void) 90.0f;
    (void) 200.0f;
    (void) 0.03448276f;
    (void) 30.0f;
    (void) 95.0f;
    (void) 185.0f;
    (void) 275.0f;
    (void) -1.0f;
    (void) -35.0f;
    (void) 0.16f;
    (void) 1.0;
    (void) 4.0f;
    (void) 4.5f;
    (void) 1.7f;
    (void) 0.083333336f;
    (void) 0.945f;
    (void) 500.0f;
}

static void ExecItemBowser(void) {
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float var_f31;
    s16 temp_r31;
    s32 var_r29;
    s32 i;

    BoardBowserSuitInit(currItemRestore);
    suitMdl = BoardBowserSuitModelGet();
    temp_r31 = BoardBowserSuitPlayerModelGet();
    suitMot[0] = BoardModelMotionCreate(suitMdl, 0x4001C);
    suitMot[1] = BoardModelMotionCreate(suitMdl, 0x4001D);
    suitCommonMot[0] = BoardModelMotionCreate(temp_r31, suitMotTbl[GWPlayer[currItemRestore].character][0]);
    suitCommonMot[1] = BoardModelMotionCreate(temp_r31, suitMotTbl[GWPlayer[currItemRestore].character][1]);
    BoardModelVisibilitySet(temp_r31, 0);
    HuAudFXPlay(0x350);
    sp20.x = sp20.y = sp20.z = 0.3f;
    ItemShowProc(NULL, &sp20);
    for (i = 0; i < 0x1E; i++) {
        sp20.x += 0.023333333f;
        sp20.y += 0.023333333f;
        sp20.z += 0.023333333f;
        BoardModelScaleSetV(suitMdl, &sp20);
        HuPrcVSleep();
    }
    sp20.x = sp20.y = sp20.z = 1.0f;
    BoardModelScaleSetV(suitMdl, &sp20);
    HuAudFXPlay(0x325);
    var_r29 = GWPlayer[currItemRestore].space_curr;
    BoardSpacePosGet(0, var_r29, &sp14);
    BoardModelPosGet(suitMdl, &sp2C);
    var_f31 = -4.0f;
    sp8.x = sp8.y = sp8.z = 1.0f;
    while (1) {
        sp2C.y += var_f31;
        if (sp2C.y <= sp14.y + 100.0f) {
            sp8.y = (sp2C.y - sp14.y) / 100.0f;
            BoardPlayerScaleSetV(currItemRestore, &sp8);
        }
        if (sp2C.y <= sp14.y) {
            break;
        }
        BoardModelPosSetV(suitMdl, &sp2C);
        var_f31 *= 1.09f;
        HuPrcVSleep();
    }
    sp2C.y = sp14.y;
    BoardModelPosSetV(suitMdl, &sp2C);
    BoardModelVisibilitySet(BoardPlayerModelGet(currItemRestore), 0);
    omVibrate(currItemRestore, 0xC, 4, 2);
    HuAudFXPlay(0x326);
    BoardModelVisibilitySet(temp_r31, 1);
    BoardModelHookSet(suitMdl, "itemhook_head", temp_r31);
    BoardModelMotionShiftSet(suitMdl, suitMot[1], 0.0f, 5.0f, 0);
    BoardModelMotionShiftSet(temp_r31, suitCommonMot[1], 0.0f, 5.0f, 0);
    while (!BoardModelMotionEndCheck(suitMdl)) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(suitMdl, suitMot[0], 0.0f, 5.0f, 0);
    BoardModelMotionShiftSet(temp_r31, suitCommonMot[0], 0.0f, 5.0f, 0);
    HuPrcSleep(0x28);
    HuAudPlayerVoicePlay(currItemRestore, 0x129);
    omVibrate(currItemRestore, 0xC, 4, 2);
    HuPrcSleep(0x3C);
    BoardModelMotionShiftSet(suitMdl, 0, 0.0f, 5.0f, 0x40000001);
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

// DATA + 0x218
// ...
static u8 data_offset_temp[0xC] = { 0 };

// https://decomp.me/scratch/0M6lm
static void ExecItemBooBall(void) {
    (void) 4.25f;
    (void) 0.016666668f;
    (void) 0.33333334f;
    (void) 8.5f;
    (void) 0.6666667f;
    (void) 325.0f;
    (void) -0.5f;
    (void) 40.0f;
    (void) 125.0f;
    (void) booBallPos;
    (void) booBallScale;
}

static void LampParticleUpdate(s32 arg0, ParticleData *arg1) {
    HsfanimStruct01 *var_r31;
    Vec spC;
    float sp8;
    float temp_f31;
    float temp_f30;
    s32 i;
    s32 j;

    if (arg1->unk_34 == 0) {
        var_r31 = arg1->unk_48;
        for (i = 0; i < arg1->unk_30; i++, var_r31++) {
            var_r31->unk2C = 0.0f;
            var_r31->unk40.a = 0;
        }
        arg1->unk_04 = 0.0f;
        arg1->unk_00 = 0;
    }
    if (arg1->unk_00 == 0) {
        arg1->unk_00 = 2;
        BoardModelRotGet(suitMdl, &spC);
        for (i = 0; i < 2; i++) {
            var_r31 = arg1->unk_48;
            for (j = 0; j < arg1->unk_30; j++, var_r31++) {
                if (var_r31->unk2C == 0.0f) {
                    break;
                }
            }
            if (j != arg1->unk_30) {
                var_r31->unk34.x = 60.0 * sin((spC.y - 90.0f) * M_PI / 180.0);
                var_r31->unk34.y = 30.0f;
                var_r31->unk34.z = 60.0 * cos((spC.y - 90.0f) * M_PI / 180.0);
                sp8 = 12.0f;
                var_r31->unk08.x = 12.0 * cos((i * 110.0f + 35.0f) * M_PI / 180.0);
                var_r31->unk08.y = 12.0 * sin((i * 110.0f + 35.0f) * M_PI / 180.0);
                var_r31->unk08.z = 3.0f + (frand() & 0xFF) * 5.0f * 0.003921569f;
                var_r31->unk14.y = 255.0f;
                var_r31->unk2C = 25.0f;
                temp_f30 = 175.0f + (frand() & 0xFF) * 0x50 * 0.003921569f;
                var_r31->unk40.r = var_r31->unk40.g = var_r31->unk40.b = temp_f30;
                var_r31->unk00_s16 = 0;
            }
        }
    } else {
        arg1->unk_00--;
    }
    var_r31 = arg1->unk_48;
    for (i = 0; i < arg1->unk_30; i++, var_r31++) {
        if (var_r31->unk2C != 0.0f) {
            if (var_r31->unk00_s16 == 0) {
                PSVECAdd(&var_r31->unk34, &var_r31->unk08, &var_r31->unk34);
                PSVECScale(&var_r31->unk08, &var_r31->unk08, 0.95f);
                var_r31->unk2C += 8.0f;
                var_r31->unk14.y -= 2.8333333f;
                if (var_r31->unk14.y <= 120.0f) {
                    var_r31->unk14.y = 200.0f;
                    temp_f31 = (frand() & 0xFF) * 180.0f * 0.003921569f;
                    var_r31->unk08.x = 6.0 * cos(temp_f31 * M_PI / 180.0);
                    var_r31->unk08.y = -4.0f;
                    var_r31->unk08.z = 6.0 * sin(temp_f31 * M_PI / 180.0);
                    var_r31->unk00_s16 = 1;
                }
                var_r31->unk40.a = var_r31->unk14.y;
            } else {
                PSVECAdd(&var_r31->unk34, &var_r31->unk08, &var_r31->unk34);
                var_r31->unk2C += 0.2f;
                var_r31->unk14.y -= 1.8214285f;
                if (var_r31->unk14.y <= 55.0f) {
                    var_r31->unk14.y = 0.0f;
                    var_r31->unk2C = 0.0f;
                }
                var_r31->unk40.a = var_r31->unk14.y;
            }
        }
    }
}

static void GenieParticleUpdate(s32 arg0, ParticleData *arg1) {
    HsfanimStruct01* var_r31;
    float temp_f31;
    float temp_f30;
    s32 var_r28;
    s32 i;

    if (arg1->unk_34 == 0) {
        var_r31 = arg1->unk_48;
        for (i = 0; i < arg1->unk_30; i++, var_r31++) {
            var_r31->unk34.x = -50.0f + (frand() & 0xFF) * 100.0f * 0.003921569f;
            var_r31->unk34.y = -50.0f + (frand() & 0xFF) * 100.0f * 0.003921569f;
            var_r31->unk34.z = -10.0f + (frand() & 0xFF) * 20.0f * 0.003921569f;
            temp_f31 = 0.5f + (frand() & 0xFF) * 3.0f * 0.003921569f;
            var_r31->unk08.x = temp_f31 * cos((i * 110.0f + 35.0f) * M_PI / 180.0);
            var_r31->unk08.y = temp_f31 * sin((i * 110.0f + 35.0f) * M_PI / 180.0);
            var_r31->unk08.z = 0.0f;
            var_r31->unk14.y = 255.0f;
            temp_f30 = 125.0f + (frand() & 0xFF) * 0x64 * 0.003921569f;
            var_r31->unk40.r = var_r31->unk40.g = var_r31->unk40.b = temp_f30;
            var_r31->unk00 = 0;
            var_r31->unk2C = 80.0f + (frand() & 0xFF) * 60.0f * 0.003921569f;
        }
    }
    var_r31 = arg1->unk_48;
    var_r28 = 0;
    for (i = 0; i < arg1->unk_30; i++, var_r31++) {
        if (var_r31->unk2C != 0.0f) {
            var_r28++;
            PSVECAdd(&var_r31->unk34, &var_r31->unk08, &var_r31->unk34);
            PSVECScale(&var_r31->unk08, &var_r31->unk08, 0.995f);
            var_r31->unk2C -= 0.2f;
            var_r31->unk14.y -= 1.59375f;
            if (var_r31->unk14.y <= 20.0f) {
                var_r31->unk14.y = 0.0f;
                var_r31->unk2C = 0.0f;
            }
            var_r31->unk40.a = var_r31->unk14.y;
        }
    }
    if (var_r28 == 0) {
        arg1->unk_02 = 0;
    }
}

// DATA + 0x224
static Vec shadowPos = { 0.0f, 4500.0f, 500.0f };
static Vec shadowTarget = { 0.0f, 0.9f, -0.1f };
static Vec shadowUp = { 0.0f, 0.0f, 500.0f };

static void GenieCameraProcInlineFunc(void) {
    Hu3DShadowPosSet(&shadowPos, &shadowTarget, &shadowUp);
}

static void GenieCameraProc(void) {
    while (1) {
        Hu3DCameraPerspectiveSet(2, genieFov, 10.0f, 20000.0f, 1.2f);
        Hu3DCameraPosSetV(2, &booCamPos, &booCamTarget, &booCamUp);
        Hu3DShadowData.unk_08.x = genieFov;
        C_MTXLightPerspective(Hu3DShadowData.unk_68, Hu3DShadowData.unk_08.x, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
        GenieCameraProcInlineFunc();
        Hu3DShadowTPLvlSet(0.8f);
        HuPrcVSleep();
    }
}

static void GenieCameraCalc(UnkGenieCameraStruct *arg0, s32 arg1, float arg2, Vec *arg3, Vec *arg4) {
    Vec spC = { 0.0f, 0.0f, 0.0f };
    float temp_f31 = arg2 * arg2;
    float sp8 = temp_f31 * arg2;
    Vec *temp_r31;
    Vec *temp_r30;
    Vec *temp_r29;
    Vec *temp_r28;
    Vec *temp_r27;
    Vec *temp_r26;
    Vec *temp_r25;
    Vec *temp_r24;

    if (arg1 == 0) {
        temp_r31 = &arg0[arg1].unk04;
        temp_r29 = &arg0[arg1 + 1].unk04;
        temp_r28 = &arg0[arg1 + 2].unk04;
        temp_r30 = &arg0[arg1].unk10;
        temp_r27 = &arg0[arg1 + 1].unk10;
        temp_r26 = &arg0[arg1 + 2].unk10;
        arg3->x = 0.5f * ((temp_r31->x - temp_r29->x * 2.0f + temp_r28->x) * temp_f31 + (temp_r31->x * -3.0f + temp_r29->x * 4.0f - temp_r28->x) * arg2 + temp_r31->x * 2.0f);
        arg3->y = 0.5f * ((temp_r31->y - temp_r29->y * 2.0f + temp_r28->y) * temp_f31 + (temp_r31->y * -3.0f + temp_r29->y * 4.0f - temp_r28->y) * arg2 + temp_r31->y * 2.0f);
        arg3->z = 0.5f * ((temp_r31->z - temp_r29->z * 2.0f + temp_r28->z) * temp_f31 + (temp_r31->z * -3.0f + temp_r29->z * 4.0f - temp_r28->z) * arg2 + temp_r31->z * 2.0f);
        arg4->x = 0.5f * ((temp_r30->x - temp_r27->x * 2.0f + temp_r26->x) * temp_f31 + (temp_r30->x * -3.0f + temp_r27->x * 4.0f - temp_r26->x) * arg2 + temp_r30->x * 2.0f);
        arg4->y = 0.5f * ((temp_r30->y - temp_r27->y * 2.0f + temp_r26->y) * temp_f31 + (temp_r30->y * -3.0f + temp_r27->y * 4.0f - temp_r26->y) * arg2 + temp_r30->y * 2.0f);
        arg4->z = 0.5f * ((temp_r30->z - temp_r27->z * 2.0f + temp_r26->z) * temp_f31 + (temp_r30->z * -3.0f + temp_r27->z * 4.0f - temp_r26->z) * arg2 + temp_r30->z * 2.0f);
    } else {
        temp_r31 = &arg0[arg1 - 1].unk04;
        temp_r29 = &arg0[arg1].unk04;
        temp_r28 = &arg0[arg1 + 1].unk04;
        temp_r25 = &arg0[arg1 + 2].unk04;
        temp_r30 = &arg0[arg1 - 1].unk10;
        temp_r27 = &arg0[arg1].unk10;
        temp_r26 = &arg0[arg1 + 1].unk10;
        temp_r24 = &arg0[arg1 + 2].unk10;
        arg3->x = 0.5f * ((-temp_r31->x + temp_r29->x * 3.0f - temp_r28->x * 3.0f + temp_r25->x) * temp_f31 * arg2 + (temp_r31->x * 2.0f - temp_r29->x * 5.0f + temp_r28->x * 4.0f - temp_r25->x) * temp_f31 + (-temp_r31->x + temp_r28->x) * arg2 + temp_r29->x * 2.0f);
        arg3->y = 0.5f * ((-temp_r31->y + temp_r29->y * 3.0f - temp_r28->y * 3.0f + temp_r25->y) * temp_f31 * arg2 + (temp_r31->y * 2.0f - temp_r29->y * 5.0f + temp_r28->y * 4.0f - temp_r25->y) * temp_f31 + (-temp_r31->y + temp_r28->y) * arg2 + temp_r29->y * 2.0f);
        arg3->z = 0.5f * ((-temp_r31->z + temp_r29->z * 3.0f - temp_r28->z * 3.0f + temp_r25->z) * temp_f31 * arg2 + (temp_r31->z * 2.0f - temp_r29->z * 5.0f + temp_r28->z * 4.0f - temp_r25->z) * temp_f31 + (-temp_r31->z + temp_r28->z) * arg2 + temp_r29->z * 2.0f);
        arg4->x = 0.5f * ((-temp_r30->x + temp_r27->x * 3.0f - temp_r26->x * 3.0f + temp_r24->x) * temp_f31 * arg2 + (temp_r30->x * 2.0f - temp_r27->x * 5.0f + temp_r26->x * 4.0f - temp_r24->x) * temp_f31 + (-temp_r30->x + temp_r26->x) * arg2 + temp_r27->x * 2.0f);
        arg4->y = 0.5f * ((-temp_r30->y + temp_r27->y * 3.0f - temp_r26->y * 3.0f + temp_r24->y) * temp_f31 * arg2 + (temp_r30->y * 2.0f - temp_r27->y * 5.0f + temp_r26->y * 4.0f - temp_r24->y) * temp_f31 + (-temp_r30->y + temp_r26->y) * arg2 + temp_r27->y * 2.0f);
        arg4->z = 0.5f * ((-temp_r30->z + temp_r27->z * 3.0f - temp_r26->z * 3.0f + temp_r24->z) * temp_f31 * arg2 + (temp_r30->z * 2.0f - temp_r27->z * 5.0f + temp_r26->z * 4.0f - temp_r24->z) * temp_f31 + (-temp_r30->z + temp_r26->z) * arg2 + temp_r27->z * 2.0f);
    }
}

// DATA + 0x248
static s32 armUpMotTbl[] = {
    0x005F005C,
    0x001A005C,
    0x006D005C,
    0x008A005C,
    0x0085005C,
    0x0011005C,
    0x000D005C,
    0x0081005C
};

// DATA + 0x268
static s32 scareMotTbl[] = {
    0x005F001C,
    0x001A001C,
    0x006D001C,
    0x008A001C,
    0x0085001C,
    0x0011001C,
    0x000D001C,
    0x0081001C
};

// DATA + 0x288
static s32 impactMotTbl[] = {
    0x005F005E,
    0x001A005E,
    0x006D005E,
    0x008A005E,
    0x0085005E,
    0x0011005E,
    0x000D005E,
    0x0081005E
};

// DATA + 0x2A8
static UnkGenieCameraStruct cameraDataTbl[] = {
    60.0f, {    0.0f, 100.0f,  950.0f }, { 0.0f, 100.0f, 600.0f },
    60.0f, { -353.0f, 100.0f,  662.5f }, { 0.0f, 100.0f, 600.0f },
    60.0f, { -500.0f, 100.0f,  375.0f }, { 0.0f, 100.0f, 600.0f },
    60.0f, { -353.0f, 100.0f,   87.5f }, { 0.0f, 100.0f, 600.0f },
     1.0f, {    0.0f, 100.0f, -200.0f }, { 0.0f, 100.0f, 600.0f },
    89.0f, {    0.0f, 100.0f, -200.0f }, { 0.0f, 100.0f, 600.0f },
     1.0f, {    0.0f, 100.0f, -200.0f }, { 0.0f, 100.0f, 600.0f },
     9.0f, {    0.0f, 100.0f, -200.0f }, { 0.0f, 100.0f, 600.0f },
     1.0f, {    0.0f, 100.0f, -200.0f }, { 0.0f, 500.0f, 600.0f },
     5.0f, {    0.0f, 100.0f, -200.0f }, { 0.0f, 500.0f, 600.0f },
     5.0f, {    0.0f, 100.0f, -200.0f }, { 0.0f, 500.0f, 600.0f }
};

// DATA + 0x3DC
static s32 genieMotTbl[] = {
    0x0007007D,
    0x0007007E,
    0x0007007F,
    -1
};

static void GenieSceneExec(void) {
    GXColor sp1C = { 0xFF, 0xFF, 0xFF, 0xFF };
    Vec sp50;
    Vec sp44;
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Process *temp_r21;
    float temp_f30;
    float var_f31;
    s16 temp_r25;
    s16 temp_r28;
    s16 temp_r24;
    s16 temp_r27;
    s16 var_r22;
    s16 temp_r20;
    s32 var_r26;
    s32 i;
    ParticleData *temp_r23;

    BoardModelHideSetAll(1);
    BoardSpaceHide(1);
    for (i = 0; i < 4; i++) {
        BoardStatusShowSet(i, 0);
    }
    BoardLightResetExec();
    temp_r25 = BoardModelCreate(0x70080, NULL, 0);
    sp50.x = sp50.y = sp50.z = 0.0f;
    BoardModelPosSetV(temp_r25, &sp50);
    BoardModelCameraSet(temp_r25, 2);
    Hu3DModelAmbSet(BoardModelIDGet(temp_r25), 1.0f, 1.0f, 1.0f);
    temp_r24 = BoardModelCreate(0x70081, NULL, 0);
    BoardModelPosSetV(temp_r24, &sp50);
    BoardModelCameraSet(temp_r24, 2);
    Hu3DModelAmbSet(BoardModelIDGet(temp_r24), 1.0f, 1.0f, 1.0f);
    temp_r28 = BoardModelCreate(0x7007C, genieMotTbl, 0);
    sp50.x = sp50.y = 0.0f;
    sp50.z = 600.0f;
    sp44.x = sp44.z = 0.0f;
    sp44.y = 180.0f;
    BoardModelPosSetV(temp_r28, &sp50);
    BoardModelRotSetV(temp_r28, &sp44);
    BoardModelCameraSet(temp_r28, 2);
    BoardModelAttrSet(temp_r28, 0x40000001);
    sp38.x = sp38.y = sp38.z = 0.0f;
    BoardPlayerCameraSet(currItemRestore, 2);
    BoardPlayerPosSetV(currItemRestore, &sp38);
    BoardModelVisibilitySet(BoardPlayerModelGet(currItemRestore), 1);
    PSVECSubtract(&shadowUp, &shadowPos, &sp2C);
    PSVECNormalize(&sp2C, &sp2C);
    temp_r20 = Hu3DGLightCreateV(&shadowPos, &sp2C, &sp1C);
    Hu3DShadowCreate(60.0f, 10.0f, 20000.0f);
    Hu3DModelShadowSet(BoardModelIDGet(BoardPlayerModelGet(currItemRestore)));
    Hu3DModelShadowSet(BoardModelIDGet(temp_r28));
    Hu3DModelShadowMapSet(BoardModelIDGet(temp_r25));
    Hu3DShadowSizeSet(0xF0);
    Hu3DCameraCreate(2);
    booCamPos.x = 0.0f;
    booCamPos.y = 100.0f;
    booCamPos.z = 950.0f;
    booCamTarget.x = booCamTarget.z = 0.0f;
    booCamTarget.y = 1.0f;
    booCamUp.x = 0.0f;
    booCamUp.y = 100.0f;
    booCamUp.z = 600.0f;
    genieFov = 15.0f;
    Hu3DShadowData.unk_08.x = genieFov;
    C_MTXLightPerspective(Hu3DShadowData.unk_68, Hu3DShadowData.unk_08.x, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
    temp_r21 = HuPrcChildCreate(GenieCameraProc, 0x2005, 0x1000, 0, HuPrcCurrentGet());
    Hu3DBGColorSet(0xFF, 0xFF, 0xFF);
    temp_r27 = Hu3DParticleCreate(genieParticleAnim, 0x32);
    Hu3DParticleHookSet(temp_r27, &GenieParticleUpdate);
    Hu3DParticleBlendModeSet(temp_r27, 1);
    Hu3DParticleColSet(temp_r27, 0xFF, 0xFF, 0xFF);
    Hu3DParticleAnimModeSet(temp_r27, 0);
    Hu3DParticleAttrSet(temp_r27, 1);
    Hu3DModelLayerSet(temp_r27, 7);
    Hu3DModelPosSet(temp_r27, booCamPos.x, booCamPos.y, booCamPos.z - 175.0f);
    temp_r23 = Hu3DData[temp_r27].unk_120;
    temp_r23->unk_02 = 1;
    WipeCreate(1, 0, 0x2D);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    BoardMusStart(1, 9, 0x7F, 0);
    while (temp_r23->unk_02 != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(0x2D);
    HuAudPlayerVoicePlay(currItemRestore, 0x128);
    BoardPlayerMotionStart(currItemRestore, geniePlayerMot[1], 0);
    BoardPlayerMotionEndWait(currItemRestore);
    HuPrcSleep(0x19);
    Hu3DModelKill(temp_r27);
    for (i = 0; i < 0xA; i++) {
        genieFov += 4.5f;
        HuPrcVSleep();
    }
    genieFov = 60.0f;
    HuPrcSleep(0x5A);
    var_f31 = 0.0f;
    var_r26 = 0;
    while (1) {
        GenieCameraCalc(&cameraDataTbl[0], var_r26, var_f31 / cameraDataTbl[var_r26].unk00, &booCamPos, &booCamUp);
        var_f31 += 1.0f;
        if (var_f31 >= cameraDataTbl[var_r26].unk00) {
            var_r26++;
            var_f31 = 0.0f;
        }
        if (var_r26 >= 8) {
            break;
        }
        HuPrcVSleep();
    }
    GenieCameraCalc(&cameraDataTbl[0], var_r26, 1.0f, &booCamPos, &booCamUp);
    HuPrcSleep(0x96);
    BoardRotateDiceNumbers(currItemRestore);
    sp2C = booCamPos;
    sp20 = booCamUp;
    booCamUp.x = sp38.x + (sp50.x - sp38.x) * 0.7f;
    booCamUp.y = sp38.y + 400.0f;
    booCamUp.z = sp38.z + (sp50.z - sp38.z) * 0.7f;
    booCamPos.x = booCamUp.x + sin(-5 * M_PI / 9) * 1100.0;
    booCamPos.y = booCamUp.y + 950.0f;
    booCamPos.z = booCamUp.z + cos(-5 * M_PI / 9) * 1100.0;
    HuAudFXPlay(0x356);
    BoardWinCreate(2, 0x12001B, -1);
    BoardWinWait();
    BoardWinKill();
    booCamUp = sp20;
    booCamPos = sp2C;
    HuAudFXPlay(0x33E);
    HuAudFXPlay(0x367);
    BoardModelMotionStart(temp_r28, 1, 0);
    var_r22 = 0;
    while (BoardModelMotionTimeGet(temp_r28) <= 30.0f) {
        HuPrcVSleep();
    }
    var_f31 = 0.0f;
    while (1) {
        temp_f30 = 40.0f - var_f31 * var_f31 * 0.25f * 0.0125f;
        if (temp_f30 <= 0.0f && var_r22 == 0) {
            var_r22 = 1;
            BoardModelMotionShiftSet(temp_r28, 3, 0.0f, 4.0f, 0);
        }
        var_f31 += 1.0f;
        sp50.y += temp_f30;
        if (sp50.y <= 0.0f) {
            break;
        }
        BoardModelPosSetV(temp_r28, &sp50);
        booCamUp.y = sp50.y + 140.0f;
        HuPrcVSleep();
    }
    HuAudFXPlay(0x368);
    sp50.y = 0.0f;
    BoardModelPosSetV(temp_r28, &sp50);
    booCamUp.y = sp38.y + 100.0f;
    BoardModelMotionStart(temp_r28, 2, 0);
    omVibrate(currItemRestore, 0xC, 0xC, 0);
    booCamUp.y = 500.0f;
    HuAudFXPlay(0x35B);
    HuAudFXPlay((GWPlayer[currItemRestore].character << 6) + 0x123);
    var_f31 = 0.0f;
    while (1) {
        temp_f30 = 60.0f - var_f31 * var_f31 * 0.25f * 0.009166667f;
        var_f31 += 1.0f;
        sp38.y += temp_f30;
        BoardPlayerPosSetV(currItemRestore, &sp38);
        if (booCamUp.y < 1100.0f) {
            booCamUp.y = sp38.y + 160.0f;
        }
        if (sp38.y >= 2800.0f) {
            break;
        }
        HuPrcVSleep();
    }
    WipeCreate(2, 0, 0x2D);
    BoardAudSeqFadeOut(1, 0x3E8);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    BoardModelKill(temp_r28);
    BoardModelKill(temp_r25);
    BoardModelKill(temp_r24);
    Hu3DCameraKill(2);
    Hu3DGLightKill(temp_r20);
    BoardModelHideSetAll(0);
    BoardSpaceHide(0);
    for (i = 0; i < 4; i++) {
        BoardStatusShowSet(i, 1);
    }
    HuPrcKill(temp_r21);
    BoardPlayerCameraSet(currItemRestore, 1);
    BoardLightSetExec();
    HuAudFXPauseAll(0);
}

static void ExecItemGenie(void) {
    UnkItemShowProcStruct sp24;
    Vec sp18;
    Vec spC;
    ParticleData *sp8;
    Process *temp_r27;
    float var_f29;
    float var_f31;
    float var_f30;
    s16 temp_r31;
    s16 var_r26;
    s32 temp_r28;
    s32 temp_r25;
    s32 var_r30;

    suitMdl = BoardModelCreate(itemMdlTbl[currItem], NULL, 1);
    BoardModelLayerSet(suitMdl, 2);
    genieParticleAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x70069, MEMORY_DEFAULT_NUM, HEAP_DATA));
    HuSprAnimLock(genieParticleAnim);
    geniePlayerMot[0] = BoardPlayerMotionCreate(currItemRestore, armUpMotTbl[GWPlayer[currItemRestore].character]);
    geniePlayerMot[1] = BoardPlayerMotionCreate(currItemRestore, scareMotTbl[GWPlayer[currItemRestore].character]);
    geniePlayerMot[2] = BoardPlayerMotionCreate(currItemRestore, impactMotTbl[GWPlayer[currItemRestore].character]);
    sp24.unk02 = suitMdl;
    sp24.unk04 = 4.0f;
    sp24.unk08 = 3.0f;
    sp24.unk10 = sp24.unk14 = sp24.unk18 = 0.0f;
    sp24.unk14 = 4.0f;
    sp24.unk1C = 1;
    HuAudFXPlay(0x350);
    temp_r27 = ItemShowProc(&sp24, NULL);
    BoardCameraViewSet(3);
    HuAudFXPlay(0x323);
    var_r30 = 0;
    while (1) {
        if (var_r30 == 0x69) {
            BoardPlayerMotionStart(currItemRestore, geniePlayerMot[0], 0);
        }
        BoardModelRotGet(suitMdl, &spC);
        if (90.0f - spC.y <= sp24.unk14 && 90.0f - spC.y >= 0.0f && var_r30 >= 0x78) {
            break;
        }
        HuPrcVSleep();
        var_r30++;
    }
    HuAudPlayerVoicePlay(currItemRestore, 0x125);
    temp_r25 = HuAudFXPlay(0x34D);
    temp_r31 = Hu3DParticleCreate(genieParticleAnim, 0x96);
    Hu3DParticleHookSet(temp_r31, &LampParticleUpdate);
    Hu3DParticleBlendModeSet(temp_r31, 0);
    Hu3DParticleColSet(temp_r31, 0xFF, 0xFF, 0xFF);
    Hu3DParticleAnimModeSet(temp_r31, 0);
    Hu3DParticleAttrSet(temp_r31, 1);
    Hu3DModelLayerSet(temp_r31, 7);
    BoardModelPosGet(suitMdl, &spC);
    Hu3DModelPosSet(temp_r31, spC.x, spC.y, spC.z);
    sp8 = Hu3DData[temp_r31].unk_120;
    omVibrate(currItemRestore, 0xB5, 6, 6);
    HuPrcSleep(0x87);
    BoardAudSeqPause(0, 1, 0x3E8);
    HuAudFXStop(temp_r25);
    HuAudFXPauseAll(1);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreate(2, 0, 0x2D);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    Hu3DModelKill(temp_r31);
    BoardModelKill(suitMdl);
    HuPrcKill(temp_r27);
    BoardRotateDiceNumbers(currItemRestore);
    GenieSceneExec();
    BoardCameraMoveSet(0);
    BoardCameraViewSet(2);
    temp_r28 = BoardSpaceStarGetCurr();
    BoardCameraTargetSpaceSet(temp_r28);
    GWPlayer[currItemRestore].space_curr = temp_r28;
    BoardSpacePosGet(0, temp_r28, &spC);
    sp18 = spC;
    spC.y += 1000.0f;
    BoardPlayerPosSetV(currItemRestore, &spC);
    BoardCameraMotionWait();
    BoardCameraMoveSet(1);
    WipeCreate(1, 0, 0x2D);
    HuPrcSleep(0xF);
    BoardAudSeqPause(0, 0, 1000);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x35E);
    fn_8004F578(GWPlayer[currItemRestore].character, 0);
    BoardPlayerMotionStart(currItemRestore, 6, 0x40000001);
    var_f29 = 0.0f;
    var_f31 = 1.0f;
    var_r26 = 0;
    while (1) {
        var_f30 = var_f29 - var_f31 * var_f31 * 0.25f * 0.06666667f;
        if (var_f30 < -35.0f) {
            var_f30 = -35.0f;
        }
        if (var_f30 > 35.0f) {
            var_f30 = 35.0f;
        }
        var_f31 += 1.0f;
        spC.y += var_f30;
        if (spC.y <= sp18.y) {
            omVibrate(currItemRestore, 0xC, 6, 6);
            spC.y = sp18.y;
            var_f29 = -var_f30 * 0.2f;
            if (fabs(var_f29) <= 5.0) {
                var_f31 = -1.0f;
                break;
            }
            var_f31 = 1.0f;
            if (var_r26 == 0) {
                BoardPlayerMotionStart(currItemRestore, geniePlayerMot[2], 0);
            }
        }
        BoardPlayerPosSetV(currItemRestore, &spC);
        HuPrcVSleep();
    }
    BoardRotateDiceNumbers(currItemRestore);
    fn_8004F578(GWPlayer[currItemRestore].character, 1);
    HuSprAnimKill(genieParticleAnim);
    BoardPlayerMotionKill(currItemRestore, geniePlayerMot[0]);
    BoardPlayerMotionKill(currItemRestore, geniePlayerMot[1]);
    BoardPlayerMotionKill(currItemRestore, geniePlayerMot[2]);
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

void BoardItemBagItemSet(s16 *arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        itemBagItems[i] = arg0[i];
    }
}

static void ExecItemBagJump(void) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f29;
    float var_f30;
    float var_f31;
    s16 temp_r31;

    temp_r31 = (s16) HuPrcCurrentGet()->user_data;
    BoardModelScaleGet(temp_r31, &sp20);
    BoardModelPosGet(temp_r31, &sp14);
    sp8 = sp14;
    sp8.y += 80.0f;
    var_f31 = 0.0f;
    var_f30 = 0.0f;
    HuAudFXPlay(0x310);
    while (1) {
        temp_f29 = 8.0f - var_f30 * var_f30 * 0.25f * 0.075f;
        var_f31 += 0.1f;
        if (var_f31 > 1.0f) {
            var_f31 = 1.0f;
        }
        sp20.x = sp20.y = sp20.z = var_f31;
        sp14.y += temp_f29;
        BoardModelPosSetV(temp_r31, &sp14);
        BoardModelScaleSetV(temp_r31, &sp20);
        var_f30 += 1.0f;
        if (temp_f29 < 0.0f) {
            break;
        }
        HuPrcVSleep();
    }
    CharModelLayerSetAll(3);
    CharModelCreateParticle(1, &sp14);
    BoardModelVisibilitySet(temp_r31, 0);
    HuAudFXPlay(0x30D);
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

static void ExecItemBagShow(void) {
    Vec sp14;
    Vec sp8;
    float var_f31;
    Process *temp_r31;
    UnkItemShowProcStruct *temp_r30;
    UnkItemShowProcStruct *temp_r29;

    temp_r31 = HuPrcCurrentGet()->user_data;
    temp_r30 = temp_r31->user_data;
    temp_r30->unk00 = 1;
    BoardModelPosGet(suitMdl, &sp14);
    var_f31 = 0.0f;
    while (1) {
        if (var_f31 >= 180.0f) {
            break;
        }
        sp8 = sp14;
        sp8.y += 15.0 * sin(M_PI * var_f31 / 180.0);
        BoardModelPosSetV(suitMdl, &sp8);
        var_f31 += 36.0f;
        HuPrcVSleep();
    }
    BoardModelPosSetV(suitMdl, &sp14);
    temp_r29 = temp_r31->user_data;
    temp_r29->unk00 = 0;
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

static void ExecItemBag(void) {
    UnkItemShowProcStruct sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    float temp_f31;
    float sp10[2];
    s16 sp8[3];
    s16 temp_r28;
    s16 temp_r27;
    s16 var_r26;
    s16 var_r30;
    s16 temp_r23;
    s16 i;
    u16 var_r25;
    Process *temp_r29;
    Process *temp_r24;

    for (i = 0; i < 3; i++) {
        if (itemBagItems[i] == -1) {
            itemBagItems[i] = rand8() % 13;
        }
    }
    temp_r23 = GWPlayer[currItemRestore].port;
    suitMdl = BoardModelCreate(itemMdlTbl[currItem], NULL, 1);
    BoardModelLayerSet(suitMdl, 2);
    BoardCameraRotGet(&sp18);
    BoardModelRotYSet(suitMdl, sp18.y);
    temp_r27 = var_r30 = 3 - BoardPlayerItemCount(currItemRestore);
    for (i = 0; i < temp_r27; i++) {
        sp8[i] = BoardModelCreate(itemMdlTbl[itemBagItems[i]], NULL, 1);
        if (itemBagItems[i] == 0xB) {
            BoardModelAttrSet(sp8[i], 0x40000001);
        }
        if (itemBagItems[i] == 5) {
            temp_f31 = -50.0f;
            Hu3DData[BoardModelIDGet(sp8[i])].unk_F0[1][3] = temp_f31;
        }
        BoardModelRotYSet(sp8[i], sp18.y);
        BoardModelLayerSet(sp8[i], 2);
        BoardModelVisibilitySet(sp8[i], 0);
    }
    sp3C.unk02 = suitMdl;
    sp3C.unk04 = 2.0f;
    sp3C.unk08 = 5.0f;
    sp3C.unk10 = sp3C.unk14 = sp3C.unk18 = 0.0f;
    sp3C.unk1C = 0;
    HuAudFXPlay(0x350);
    temp_r24 = ItemShowProc(&sp3C, NULL);
    HuWinMesMaxSizeGet(1, sp10, 0x120014);
    temp_r28 = HuWinCreate(-10000.0f, 320.0f, sp10[0], sp10[1], 0);
    HuWinMesSet(temp_r28, 0x120014);
    HuWinBGTPLvlSet(temp_r28, 0.0f);
    HuWinMesSpeedSet(temp_r28, 0);
    var_r26 = frandmod(0x28) + 0x1E;
    var_r30 = 0;
    sp24.x = sp24.y = sp24.z = 0.0f;
    while (var_r30 < temp_r27) {
        if (GWPlayerCfg[currItemRestore].iscom == 1) {
            if (--var_r26 == 0) {
                var_r25 = 0x100;
                var_r26 = frandmod(0x28) + 0x1E;
            }
        } else {
            var_r25 = HuPadBtnDown[temp_r23];
        }
        if (!(var_r25 & 0x100)) {
            HuPrcVSleep();
        } else {
            BoardPlayerDiceJumpStart(currItemRestore);
            while (!BoardPlayerDiceJumpCheck(currItemRestore)) {
                HuPrcVSleep();
            }
            HuAudFXPlay(0x324);
            BoardModelPosGet(suitMdl, &sp30);
            BoardModelPosSetV(sp8[var_r30], &sp30);
            BoardModelScaleSetV(sp8[var_r30], &sp24);
            BoardModelVisibilitySet(sp8[var_r30], 1);
            temp_r29 = HuPrcChildCreate(ExecItemBagJump, 0x2004, 0x1000, 0, HuPrcCurrentGet());
            temp_r29->user_data = (void*) sp8[var_r30];
            temp_r29 = HuPrcChildCreate(ExecItemBagShow, 0x2004, 0x1000, 0, HuPrcCurrentGet());
            temp_r29->user_data = temp_r24;
            while (GWPlayer[currItemRestore].field08_bit3) {
                HuPrcVSleep();
            }
            HuPrcChildWatch();
            BoardPlayerItemAdd(currItemRestore, itemBagItems[var_r30]);
            BoardPlayerMotionShiftSet(currItemRestore, 1, 0.0f, 10.0f, 0x40000001);
            HuPrcSleep(0xA);
            var_r30++;
        }
    }
    HuWinKill(temp_r28);
    BoardModelPosGet(suitMdl, &sp30);
    CharModelLayerSetAll(3);
    CharModelCreateParticle(1, &sp30);
    HuAudFXPlay(0x351);
    HuPrcSleep(0xA);
    HuPrcKill(temp_r24);
    BoardModelKill(suitMdl);
    for (i = 0; i < temp_r27; i++) {
        BoardModelKill(sp8[i]);
    }
    HuPrcSleep(0x1E);
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

static void RestoreItemNull(void) {
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

static void RestoreItemMini(void) {
    HuAudFXPlay(0x311);
    ItemSizeSet(0);
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

static void RestoreItemMega(void) {
    HuAudFXPlay(0x313);
    ItemSizeSet(0);
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

static void RestoreItemMiniSuper(void) {
    HuAudFXPlay(0x311);
    ItemSizeSet(0);
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

static void RestoreItemMegaSuper(void) {
    HuAudFXPlay(0x313);
    ItemSizeSet(0);
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

static void RestoreItemBowser(void) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    s16 temp_r31;
    s16 temp_r29;
    s16 i;

    temp_r31 = BoardModelCreate(0x70063, NULL, 0);
    BoardModelVisibilitySet(temp_r31, 0);
    BoardModelLayerSet(temp_r31, 3);
    BoardPlayerPosGet(currItemRestore, &sp14);
    sp20.x = sp20.y = sp20.z = 0.0f;
    sp14.y += 100.0f;
    BoardModelPosSetV(temp_r31, &sp14);
    BoardModelScaleSetV(temp_r31, &sp20);
    BoardModelAttrSet(temp_r31, 0x40000001);
    BoardModelAttrSet(temp_r31, 0x400000);
    suitMdl = BoardBowserSuitModelGet();
    temp_r29 = BoardBowserSuitPlayerModelGet();
    BoardModelMotionShiftSet(suitMdl, suitMot[0], 0.0f, 5.0f, 0);
    BoardModelMotionShiftSet(temp_r29, suitCommonMot[0], 0.0f, 5.0f, 0);
    HuPrcSleep(0x28);
    HuAudPlayerVoicePlay(currItemRestore, 0x129);
    HuPrcSleep(0x14);
    HuAudFXPlay(0x32B);
    BoardModelVisibilitySet(temp_r31, 1);
    for (i = 0; i < 0x3C; i++) {
        sp20.x += 0.15f;
        sp20.y += 0.15f;
        sp20.z += 0.15f;
        BoardModelScaleSetV(temp_r31, &sp20);
        HuPrcVSleep();
    }
    sp20.x = sp20.y = sp20.z = 9.0f;
    BoardModelScaleSetV(temp_r31, &sp20);
    HuPrcSleep(0x3C);
    HuAudFXPlay(0x313);
    BoardModelHookReset(suitMdl);
    BoardBowserSuitKill(currItemRestore);
    sp8.x = sp8.y = sp8.z = 1.0f;
    BoardPlayerScaleSetV(currItemRestore, &sp8);
    BoardModelVisibilitySet(BoardPlayerModelGet(currItemRestore), 1);
    for (i = 0; i < 0x3C; i++) {
        sp20.x -= 0.15f;
        sp20.y -= 0.15f;
        sp20.z -= 0.15f;
        BoardModelScaleSetV(temp_r31, &sp20);
        HuPrcVSleep();
    }
    BoardModelKill(temp_r31);
    HuPrcKill(NULL);
    while (1) {
        HuPrcVSleep();
    }
}
