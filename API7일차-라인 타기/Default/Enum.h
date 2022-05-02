#pragma once

//홍준수정 상호작용전용 오브젝트 추가 OBJ_INTERACTION 
// Hero: UI는 제일 마지막에 렌더 돼야합니다. 제일 뒤로 두세요.
enum OBJID { OBJ_PLAYER, OBJ_BULLET, OBJ_MONSTER, OBJ_MOUSE, OBJ_INTERACTION, OBJ_TEMP, OBJ_SHIELD, OBJ_COIN,OBJ_MUSHROOM, OBJ_BLOCK, OBJ_MOVINGBLOCK, OBJ_UI, OBJ_END };

enum SCENEID {SCENE_START, SCENE_PLAYE, SCENE_EDIT, SCENE_END};

enum DIRECTION	{ DIR_LEFT, DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_END };
enum BLOCKID	{BLK_BLOCK, BLK_MOVINGBLOCK, BLK_MOVINGBLOCKLR, BLK_GUMBA, BLK_TURTLE, BLK_KOOPA, BLK_COIN, BLK_END};

