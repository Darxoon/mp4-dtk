#include "game/objsub.h"
#include "game/gamework_data.h"
#include "game/object.h"
#include "game/data.h"

MgInfo mgInfoTbl[] = {
    {
        OVL_M401, // ovl
        0, // type
        3, // flag
        255, // record_idx
        0x170001, // name_mess
        DATADIR_M401, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 0), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 0), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210000, // rules_mess
        0x210001, // control_mess[0]
        0, // control_mess[1]
        0x210003, // advice_mess
    },
    {
        OVL_M402, // ovl
        0, // type
        3, // flag
        255, // record_idx
        0x170002, // name_mess
        DATADIR_M402, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 1), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 1), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210004, // rules_mess
        0x210005, // control_mess[0]
        0, // control_mess[1]
        0x210007, // advice_mess
    },
    {
        OVL_M403, // ovl
        0, // type
        3, // flag
        255, // record_idx
        0x170003, // name_mess
        DATADIR_M403, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 2), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 2), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210008, // rules_mess
        0x210009, // control_mess[0]
        0, // control_mess[1]
        0x21000B, // advice_mess
    },
    {
        OVL_M404, // ovl
        4, // type
        2, // flag
        255, // record_idx
        0x170004, // name_mess
        DATADIR_M404, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 3), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 3), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x21000C, // rules_mess
        0x21000D, // control_mess[0]
        0, // control_mess[1]
        0x21000F, // advice_mess
    },
    {
        OVL_M405, // ovl
        0, // type
        2, // flag
        0, // record_idx
        0x170005, // name_mess
        DATADIR_M405, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 4), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 4), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210010, // rules_mess
        0x210011, // control_mess[0]
        0, // control_mess[1]
        0x210013, // advice_mess
    },
    {
        OVL_M406, // ovl
        0, // type
        2, // flag
        255, // record_idx
        0x170006, // name_mess
        DATADIR_M406, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 5), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 5), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210014, // rules_mess
        0x210015, // control_mess[0]
        0, // control_mess[1]
        0x210017, // advice_mess
    },
    {
        OVL_M407, // ovl
        0, // type
        3, // flag
        1, // record_idx
        0x170007, // name_mess
        DATADIR_M407, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 6), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 6), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210018, // rules_mess
        0x210019, // control_mess[0]
        0, // control_mess[1]
        0x21001B, // advice_mess
    },
    {
        OVL_M408, // ovl
        0, // type
        3, // flag
        255, // record_idx
        0x170008, // name_mess
        DATADIR_M408, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 7), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 7), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x21001C, // rules_mess
        0x21001D, // control_mess[0]
        0, // control_mess[1]
        0x21001F, // advice_mess
    },
    {
        OVL_M409, // ovl
        0, // type
        3, // flag
        255, // record_idx
        0x170009, // name_mess
        DATADIR_M409, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 8), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 8), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210020, // rules_mess
        0x210021, // control_mess[0]
        0, // control_mess[1]
        0x210023, // advice_mess
    },
    {
        OVL_M410, // ovl
        0, // type
        3, // flag
        255, // record_idx
        0x17000A, // name_mess
        DATADIR_M410, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 9), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 9), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210024, // rules_mess
        0x210025, // control_mess[0]
        0, // control_mess[1]
        0x210027, // advice_mess
    },
    {
        OVL_M411, // ovl
        0, // type
        3, // flag
        255, // record_idx
        0x17000B, // name_mess
        DATADIR_M411, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 10), // inst_pic[0]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 11), // inst_pic[1]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 12), // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 62), // mg_pic[0]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 11), // mg_pic[1]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 12), // mg_pic[2]
        0x210028, // rules_mess
        0x210029, // control_mess[0]
        0, // control_mess[1]
        0x21002B, // advice_mess
    },
    {
        OVL_M412, // ovl
        0, // type
        3, // flag
        255, // record_idx
        0x17000C, // name_mess
        DATADIR_M412, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 13), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 13), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x21002C, // rules_mess
        0x21002D, // control_mess[0]
        0, // control_mess[1]
        0x21002F, // advice_mess
    },
    {
        OVL_M413, // ovl
        0, // type
        2, // flag
        255, // record_idx
        0x17000D, // name_mess
        DATADIR_M413, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 14), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 63), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210030, // rules_mess
        0x210031, // control_mess[0]
        0, // control_mess[1]
        0x210033, // advice_mess
    },
    {
        OVL_M414, // ovl
        0, // type
        3, // flag
        255, // record_idx
        0x17000E, // name_mess
        DATADIR_M414, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 15), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 15), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210034, // rules_mess
        0x210035, // control_mess[0]
        0, // control_mess[1]
        0x210037, // advice_mess
    },
    {
        OVL_M415, // ovl
        0, // type
        3, // flag
        255, // record_idx
        0x17000F, // name_mess
        DATADIR_M415, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 16), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 16), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210038, // rules_mess
        0x210039, // control_mess[0]
        0, // control_mess[1]
        0x21003B, // advice_mess
    },
    {
        OVL_M416, // ovl
        1, // type
        1, // flag
        255, // record_idx
        0x170010, // name_mess
        DATADIR_M416, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 17), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 17), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x21003C, // rules_mess
        0x21003D, // control_mess[0]
        0x21003E, // control_mess[1]
        0x21003F, // advice_mess
    },
    {
        OVL_M417, // ovl
        1, // type
        1, // flag
        255, // record_idx
        0x170011, // name_mess
        DATADIR_M417, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 18), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 18), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210040, // rules_mess
        0x210041, // control_mess[0]
        0x210042, // control_mess[1]
        0x210043, // advice_mess
    },
    {
        OVL_M418, // ovl
        1, // type
        1, // flag
        255, // record_idx
        0x170012, // name_mess
        DATADIR_M418, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 19), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 19), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210044, // rules_mess
        0x210045, // control_mess[0]
        0x210046, // control_mess[1]
        0x210047, // advice_mess
    },
    {
        OVL_M419, // ovl
        1, // type
        1, // flag
        255, // record_idx
        0x170013, // name_mess
        DATADIR_M419, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 20), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 20), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210048, // rules_mess
        0x210049, // control_mess[0]
        0x21004A, // control_mess[1]
        0x21004B, // advice_mess
    },
    {
        OVL_M420, // ovl
        1, // type
        0, // flag
        255, // record_idx
        0x170014, // name_mess
        DATADIR_M420, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 21), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 21), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x21004C, // rules_mess
        0x21004D, // control_mess[0]
        0x21004E, // control_mess[1]
        0x21004F, // advice_mess
    },
    {
        OVL_M421, // ovl
        1, // type
        1, // flag
        255, // record_idx
        0x170015, // name_mess
        DATADIR_M421, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 22), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 22), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210050, // rules_mess
        0x210051, // control_mess[0]
        0x210052, // control_mess[1]
        0x210053, // advice_mess
    },
    {
        OVL_M422, // ovl
        1, // type
        1, // flag
        255, // record_idx
        0x170016, // name_mess
        DATADIR_M422, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 23), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 23), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210054, // rules_mess
        0x210055, // control_mess[0]
        0x210056, // control_mess[1]
        0x210057, // advice_mess
    },
    {
        OVL_M423, // ovl
        1, // type
        0, // flag
        255, // record_idx
        0x170017, // name_mess
        DATADIR_M423, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 24), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 24), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210058, // rules_mess
        0x210059, // control_mess[0]
        0x21005A, // control_mess[1]
        0x21005B, // advice_mess
    },
    {
        OVL_M424, // ovl
        1, // type
        0, // flag
        255, // record_idx
        0x170018, // name_mess
        DATADIR_M424, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 25), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 25), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x21005C, // rules_mess
        0x21005D, // control_mess[0]
        0x21005E, // control_mess[1]
        0x21005F, // advice_mess
    },
    {
        OVL_M425, // ovl
        2, // type
        3, // flag
        255, // record_idx
        0x170019, // name_mess
        DATADIR_M425, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 26), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 26), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210060, // rules_mess
        0x210061, // control_mess[0]
        0, // control_mess[1]
        0x210063, // advice_mess
    },
    {
        OVL_M426, // ovl
        2, // type
        3, // flag
        255, // record_idx
        0x17001A, // name_mess
        DATADIR_M426, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 27), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 27), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210064, // rules_mess
        0x210065, // control_mess[0]
        0, // control_mess[1]
        0x210067, // advice_mess
    },
    {
        OVL_M427, // ovl
        2, // type
        2, // flag
        2, // record_idx
        0x17001B, // name_mess
        DATADIR_M427, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 28), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 28), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210068, // rules_mess
        0x210069, // control_mess[0]
        0, // control_mess[1]
        0x21006B, // advice_mess
    },
    {
        OVL_M428, // ovl
        2, // type
        3, // flag
        255, // record_idx
        0x17001C, // name_mess
        DATADIR_M428, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 29), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 29), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x21006C, // rules_mess
        0x21006D, // control_mess[0]
        0, // control_mess[1]
        0x21006F, // advice_mess
    },
    {
        OVL_M429, // ovl
        2, // type
        2, // flag
        255, // record_idx
        0x17001D, // name_mess
        DATADIR_M429, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 30), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 64), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210070, // rules_mess
        0x210071, // control_mess[0]
        0, // control_mess[1]
        0x210073, // advice_mess
    },
    {
        OVL_M430, // ovl
        2, // type
        3, // flag
        255, // record_idx
        0x17001E, // name_mess
        DATADIR_M430, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 31), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 31), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210074, // rules_mess
        0x210075, // control_mess[0]
        0x210076, // control_mess[1]
        0x210077, // advice_mess
    },
    {
        OVL_M431, // ovl
        2, // type
        3, // flag
        255, // record_idx
        0x17001F, // name_mess
        DATADIR_M431, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 32), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 32), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210078, // rules_mess
        0x210079, // control_mess[0]
        0, // control_mess[1]
        0x21007B, // advice_mess
    },
    {
        OVL_M432, // ovl
        2, // type
        3, // flag
        3, // record_idx
        0x170020, // name_mess
        DATADIR_M432, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 33), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 33), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x21007C, // rules_mess
        0x21007D, // control_mess[0]
        0x21007E, // control_mess[1]
        0x21007F, // advice_mess
    },
    {
        OVL_M433, // ovl
        7, // type
        3, // flag
        255, // record_idx
        0x170021, // name_mess
        DATADIR_M433, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 34), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 34), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210080, // rules_mess
        0x37001F, // control_mess[0]
        0, // control_mess[1]
        0x210083, // advice_mess
    },
    {
        OVL_M434, // ovl
        2, // type
        2, // flag
        255, // record_idx
        0x170022, // name_mess
        DATADIR_M434, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 35), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 35), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210084, // rules_mess
        0x210085, // control_mess[0]
        0, // control_mess[1]
        0x210087, // advice_mess
    },
    {
        OVL_M435, // ovl
        3, // type
        3, // flag
        255, // record_idx
        0x170023, // name_mess
        DATADIR_M435, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 36), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 36), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // rules_mess
        0x210089, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        OVL_M436, // ovl
        3, // type
        3, // flag
        255, // record_idx
        0x170024, // name_mess
        DATADIR_M436, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 37), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 37), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // rules_mess
        0x21008D, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        OVL_M437, // ovl
        3, // type
        3, // flag
        255, // record_idx
        0x170025, // name_mess
        DATADIR_M437, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 38), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 38), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // rules_mess
        0x210091, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        OVL_M438, // ovl
        4, // type
        3, // flag
        255, // record_idx
        0x170026, // name_mess
        DATADIR_M438, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 39), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 39), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210094, // rules_mess
        0x210095, // control_mess[0]
        0, // control_mess[1]
        0x210097, // advice_mess
    },
    {
        OVL_M439, // ovl
        4, // type
        2, // flag
        255, // record_idx
        0x170027, // name_mess
        DATADIR_M439, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 40), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 40), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x210098, // rules_mess
        0x210099, // control_mess[0]
        0, // control_mess[1]
        0x21009B, // advice_mess
    },
    {
        OVL_M440, // ovl
        4, // type
        3, // flag
        255, // record_idx
        0x170028, // name_mess
        DATADIR_M440, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 41), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 41), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x21009C, // rules_mess
        0x21009D, // control_mess[0]
        0, // control_mess[1]
        0x21009F, // advice_mess
    },
    {
        OVL_M441, // ovl
        4, // type
        3, // flag
        255, // record_idx
        0x170029, // name_mess
        DATADIR_M441, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 42), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 42), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x2100A0, // rules_mess
        0x2100A1, // control_mess[0]
        0, // control_mess[1]
        0x2100A3, // advice_mess
    },
    {
        OVL_M442, // ovl
        7, // type
        3, // flag
        255, // record_idx
        0x17002A, // name_mess
        DATADIR_M442, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 43), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 65), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x2100A4, // rules_mess
        0x370010, // control_mess[0]
        0, // control_mess[1]
        0x2100A7, // advice_mess
    },
    {
        OVL_M443, // ovl
        0, // type
        2, // flag
        5, // record_idx
        0x17002B, // name_mess
        DATADIR_M443, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 44), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 44), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x2100A8, // rules_mess
        0x2100A9, // control_mess[0]
        0, // control_mess[1]
        0x2100AB, // advice_mess
    },
    {
        OVL_M444, // ovl
        5, // type
        3, // flag
        255, // record_idx
        0x17002C, // name_mess
        DATADIR_M444, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 45), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 45), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // rules_mess
        0, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        OVL_M445, // ovl
        6, // type
        0, // flag
        255, // record_idx
        0x17002D, // name_mess
        DATADIR_M445, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 46), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 46), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x2100AC, // rules_mess
        0x2100AD, // control_mess[0]
        0, // control_mess[1]
        0x2100AF, // advice_mess
    },
    {
        OVL_M446, // ovl
        6, // type
        0, // flag
        255, // record_idx
        0x17002E, // name_mess
        DATADIR_M446, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 47), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 47), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x2100B0, // rules_mess
        0x2100B1, // control_mess[0]
        0, // control_mess[1]
        0x2100B3, // advice_mess
    },
    {
        OVL_M447, // ovl
        6, // type
        0, // flag
        255, // record_idx
        0x17002F, // name_mess
        DATADIR_M447, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 48), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 48), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x2100B4, // rules_mess
        0x2100B5, // control_mess[0]
        0, // control_mess[1]
        0x2100B7, // advice_mess
    },
    {
        OVL_M448, // ovl
        6, // type
        0, // flag
        255, // record_idx
        0x170030, // name_mess
        DATADIR_M448, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 49), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 49), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x2100B8, // rules_mess
        0x2100B9, // control_mess[0]
        0, // control_mess[1]
        0x2100BB, // advice_mess
    },
    {
        OVL_M449, // ovl
        6, // type
        0, // flag
        255, // record_idx
        0x170031, // name_mess
        DATADIR_M449, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x2100BC, // rules_mess
        0x2100BD, // control_mess[0]
        0, // control_mess[1]
        0x2100BF, // advice_mess
    },
    {
        OVL_M450, // ovl
        8, // type
        0, // flag
        255, // record_idx
        0x170032, // name_mess
        DATADIR_M450, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 51), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 51), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x2100C0, // rules_mess
        0x2100C1, // control_mess[0]
        0, // control_mess[1]
        0x2100C3, // advice_mess
    },
    {
        OVL_M451, // ovl
        7, // type
        0, // flag
        255, // record_idx
        0x170033, // name_mess
        DATADIR_M451, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 52), // inst_pic[0]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 53), // inst_pic[1]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 54), // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 52), // mg_pic[0]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 53), // mg_pic[1]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 54), // mg_pic[2]
        0x2100C4, // rules_mess
        0x37000D, // control_mess[0]
        0, // control_mess[1]
        0x2100C7, // advice_mess
    },
    {
        OVL_M450, // ovl
        7, // type
        0, // flag
        255, // record_idx
        0x170033, // name_mess
        DATADIR_M450, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 55), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 55), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // rules_mess
        0, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        OVL_M453, // ovl
        7, // type
        0, // flag
        255, // record_idx
        0x170034, // name_mess
        DATADIR_M450, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x2100C8, // rules_mess
        0x37000A, // control_mess[0]
        0, // control_mess[1]
        0x2100CB, // advice_mess
    },
    {
        OVL_M450, // ovl
        7, // type
        0, // flag
        255, // record_idx
        0x170033, // name_mess
        DATADIR_M450, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 55), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 55), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // rules_mess
        0, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        OVL_M455, // ovl
        4, // type
        3, // flag
        255, // record_idx
        0x170035, // name_mess
        DATADIR_M455, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 56), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 56), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x2100CC, // rules_mess
        0x2100CD, // control_mess[0]
        0, // control_mess[1]
        0x2100CF, // advice_mess
    },
    {
        OVL_M456, // ovl
        0, // type
        3, // flag
        255, // record_idx
        0x170036, // name_mess
        DATADIR_M456, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 57), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 57), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0x2100D0, // rules_mess
        0x2100D1, // control_mess[0]
        0, // control_mess[1]
        0x2100D3, // advice_mess
    },
    {
        OVL_M457, // ovl
        8, // type
        0, // flag
        255, // record_idx
        0x170037, // name_mess
        DATADIR_M457, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 58), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 58), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // rules_mess
        0, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        OVL_M458, // ovl
        8, // type
        0, // flag
        255, // record_idx
        0x170038, // name_mess
        DATADIR_M458, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 59), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 59), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // rules_mess
        0, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        OVL_M459, // ovl
        7, // type
        0, // flag
        255, // record_idx
        0x170038, // name_mess
        DATADIR_M458, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // rules_mess
        0x370013, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        OVL_M460, // ovl
        7, // type
        0, // flag
        255, // record_idx
        0x170038, // name_mess
        DATADIR_M458, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // rules_mess
        0x370016, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        OVL_M461, // ovl
        7, // type
        0, // flag
        255, // record_idx
        0x170038, // name_mess
        DATADIR_M458, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // rules_mess
        0x370019, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        OVL_M462, // ovl
        7, // type
        0, // flag
        255, // record_idx
        0x170038, // name_mess
        DATADIR_M458, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // rules_mess
        0x37001C, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        OVL_M463, // ovl
        7, // type
        0, // flag
        255, // record_idx
        0x170038, // name_mess
        DATADIR_M458, // data_dir
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        DATA_MAKE_NUM(DATADIR_INSTPIC, 50), // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // rules_mess
        0x370007, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
    {
        ((u16)OVL_INVALID), // ovl
        0, // type
        0, // flag
        255, // record_idx
        0, // name_mess
        0, // data_dir
        0, // inst_pic[0]
        0, // inst_pic[1]
        0, // inst_pic[2]
        0, // mg_pic[0]
        0, // mg_pic[1]
        0, // mg_pic[2]
        0, // rules_mess
        0, // control_mess[0]
        0, // control_mess[1]
        0, // advice_mess
    },
};

void MGSeqPracticeExitCheck(omObjData*);

s16 mgTypeCurr;
s16 mgBattleStar[4];
s16 mgBattleStarMax;
u8 lbl_801D3E94;
s32 mgRecordExtra;
s32 mgQuitExtraF;
s32 mgPracticeEnableF;
s32 mgInstExitEnableF;
u8 mgBoardHostEnableF;

s16 mgTicTacToeGrid[3][3];
u8 mgIndexList[256];
GameStat mgGameStatBackup;

s32 omMgIndexGet(s16 overlay) {
    s32 i;
    MgInfo *info;

    info = mgInfoTbl;
    
    for (i = 0; info->ovl != ((u16)OVL_INVALID); i++) {
        if (info->ovl == overlay) {
            return (s16)i;
        }
        info++;
    }

    return -1;
}

void omGameSysInit(Process *objman) {
    s32 i;
    omObjData* obj;

    omSystemKeyCheckSetup(objman);
    Hu3DCameraScissorSet(1, 0, 0, 0x280, 0x1E0);
    omSysPauseEnable(0);
    
    for (i = 0; i < 4; i++) {
        if (_CheckFlag(0x1000C) == 0) {
            GWPlayer[i].coins_mg_gain = 0;
        }
        
        GWPlayer[i].unk_26 = 0;
    }
    
    if (mgPracticeEnableF != 0) {
        obj = omAddObjEx(objman, 0x7FDC, 0, 0, -1, MGSeqPracticeExitCheck);
        omSetStatBit(obj, 0xA0U);
    }
}

void omVibrate(s16 player, s16 duration, s16 off, s16 on) {
    s32 rumble = GWGameStat.rumble;
    
    if (rumble != 0 && GWPlayerCfg[player].iscom == 0) {
        HuPadRumbleSet(GWPlayerCfg[player].pad_idx, duration, off, on);
    }
}
