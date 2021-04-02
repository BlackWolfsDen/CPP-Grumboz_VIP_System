{\rtf1\ansi\ansicpg1252\deff0\deflang1033{\fonttbl{\f0\fnil\fcharset0 Courier New;}{\f1\fnil Consolas;}{\f2\fnil\fcharset0 Consolas;}}
{\colortbl ;\red0\green0\blue255;\red255\green255\blue255;\red0\green0\blue0;\red163\green21\blue21;\red0\green128\blue0;\red43\green145\blue175;\red128\green128\blue128;}
{\*\generator Msftedit 5.41.21.2510;}\viewkind4\uc1\pard\f0\fs22 TDB 335.60\par
********************************************************************\par
C:\\Users\\Gamer\\Desktop\\Trinity Core Boost\\335 Realm\\BWD_335a 2 Bloody WoW\\src\\LuaEngine\\LuaFunctions.h\par
\par
add with the includes\par
[CODE]\par
\cf1\highlight2\f1\fs19 #include\cf3  \cf4 "Grumboz_VIP_Core.h"\cf3\par
\cf0\highlight0\f0\fs22 [/CODE]\par
\par
Global::Getters\par
[CODE]\par
\cf3\highlight2\f1\fs19\tab\cf5 // Grumboz VIP Engine global methods \cf3\par
\tab\{ \cf4 "GetVIPMAX"\cf3 , &LuaGlobalFunctions::GetVIPMAX \},\tab\tab\tab\cf5 // GetVIPMAX(); returns maximum VIP rank.\cf3\par
\tab\{ \cf4 "GetVIPVOTECOUNT"\cf3 , &LuaGlobalFunctions::GetVIPVOTECOUNT \},\cf5 // GetVIPVOTECOUNT(); returns how many votes to rank up VIP +1 rank.\cf3\par
\tab\{ \cf4 "GetVIPCOINID"\cf3 , &LuaGlobalFunctions::GetVIPCOINID \},\tab\tab\cf5 // GetVIPCOINID(); returns item id.\cf3\par
\tab\{ \cf4 "GetVIPSTONEID"\cf3 , &LuaGlobalFunctions::GetVIPSTONEID \},\tab\cf5 // GetVIPSTONEID(); returns item id.\cf3\par
\tab\{ \cf4 "GetVIPMGID"\cf3 , &LuaGlobalFunctions::GetVIPMGID \},\tab\tab\tab\cf5 // GetVIPMGID(); returns item id.\cf3\par
\tab\{ \cf4 "GetVIPOFFSET"\cf3 , &LuaGlobalFunctions::GetVIPOFFSET \},\tab\tab\cf5 // GetVIPOFFSET(); returns float offset value.\cf3\par
\tab\{ \cf4 "GetTALENTBONUS"\cf3 , &LuaGlobalFunctions::GetTALENTBONUS \},\tab\cf5 // GetTALENTBONUS(); returns how many extra tp per VIP rank.\cf3\par
\tab\{ \cf4 "GetLEVELBONUS"\cf3 , &LuaGlobalFunctions::GetLEVELBONUS \},\tab\cf5 // GetLEVELBONUS(); returns how many extra levels per VIP rank.\cf3\par
\cf0\highlight0\f0\fs22 [/CODE]\par
\par
Global::Boolian\par
[CODE]\par
\cf3\highlight2\f1\fs19\tab\cf5 // Grumboz VIP Engine global methods \cf3\par
\tab\{ \cf4 "GetVIPVOTE_ENABLE"\cf3 , &LuaGlobalFunctions::GetVIPVOTE_ENABLE \},\tab\tab\tab\cf5 // GetVIPVOTE_ENABLE(); returns bool value. ?Do Votes increase VIP ranks?\cf3\par
\tab\{ \cf4 "GetLEVELBONUS_ENABLE"\cf3 , &LuaGlobalFunctions::GetLEVELBONUS_ENABLE \},\tab\tab\cf5 // GetLEVELBONUS_ENABLE(); returns bool value. do players get extra levels per VIP rank.\cf3\par
\cf0\highlight0\f0\fs22 [/CODE]\par
\par
Player Methods::Getters\par
[CODE]\par
\cf3\highlight2\f1\fs19\tab\cf5 // Grumboz VIP Engine player \f2 getter \f1 methods\cf3\par
\tab\{ \cf4 "Get\cf3 Player\cf4 VIP"\cf3 , &LuaPlayer::GetPlayerVIP \},\tab\tab\tab\tab\cf5 // player:GetVIP(); returns uint8 value of a players VIP rank.\cf3\par
\tab\{ \cf4 "Get\cf3 Player\cf4 MG"\cf3 , &LuaPlayer::GetPlayerMG \},\tab\tab\tab\tab\tab\cf5 // player:GetMG(); returns uint32 value of players total mg stored.(NOT IN INVENTORY)\cf3\par
\tab\{ \cf4 "Get\cf3 Player\cf4 VOTES"\cf3 , &LuaPlayer::GetPlayerVOTES \},\tab\tab\tab\cf5 // player:GetVOTES(); returns uint32 value of players total voting count.\cf3\par
\cf0\highlight0\f0\fs22 [/CODE]\par
\par
Player Methods::Setters\par
[CODE]\par
\cf3\highlight2\f1\fs19\tab\cf5 // Grumboz VIP Engine player \f2 setter \f1 methods \cf3\par
\tab\{ \cf4 "Set\cf3 Player\cf4 VIP"\cf3 , &LuaPlayer::SetPlayerVIP \},\par
\tab\{ \cf4 "Set\cf3 Player\cf4 MG"\cf3 , &LuaPlayer::SetPlayerMG \},\par
\tab\{ \cf4 "Set\cf3 Player\cf4 VOTES"\cf3 , &LuaPlayer::SetPlayerVOTES \},\par
\cf0\highlight0\f0\fs22 [/CODE]\par
\par
Creature Methods::Getters\par
[CODE]\par
\cf3\highlight2\f1\fs19\tab\cf5 // Grumboz VIP Engine \f2 creature getter\f1  methods\cf3\par
\tab\{ \cf4 "GetCreatureVIP"\cf3 , &LuaCreature::GetCreatureVIP \},\tab\tab\tab\tab\cf5 // creature:GetCreatureVIP(uint32 creature_id); returns uint8 value of a creatures VIP rank.\cf3\par
\tab\{ \cf4 "GetCreatureMG"\cf3 , &LuaCreature::GetCreatureMG \},\tab\tab\tab\tab\cf5 // creature:GetCreatureMG(uint32 creature_id); returns uint32 value of creature mg .\cf3\par
\cf0\highlight0\f0\fs22 [/CODE]\line\par
Creature Methods::Setters\par
[CODE]\par
\cf3\highlight2\f1\fs19\tab\cf5 // Grumboz VIP Engine \f2 creature setter\f1  methods\cf3\par
\tab\{ \cf4 "\f2 S\f1 etCreatureVIP"\cf3 , &LuaCreature::\f2 S\f1 etCreatureVIP \},\tab\tab\tab\tab\cf5 // creature:\f2 S\f1 etCreatureVIP(uint32 creature_id); \f2 sets \f1  uint8 value of a creatures VIP rank.\cf3\par
\tab\{ \cf4 "\f2 S\f1 etCreatureMG"\cf3 , &LuaCreature::\f2 S\f1 etCreatureMG \},\tab\tab\tab\tab\cf5 // creature:\f2 S\f1 etCreatureMG(uint32 creature_id); \f2 sets \f1 uint32 value of creature mg .\cf3\par
\cf0\highlight0\f0\fs22 [/CODE]\par
\par
Item Methods::Getters\par
[CODE]\par
\cf3\highlight2\f1\fs19\tab\cf5 // Grumboz VIP Engine item \f2 getter \f1 methods \cf3\par
\tab\{ \cf4 "GetItemVIP"\cf3 , &LuaItem::GetItemVIP \},\par
\cf0\highlight0\f0\fs22 [/CODE]\par
\par
Player Methods::Setters\par
[CODE]\par
\cf3\highlight2\f1\fs19\tab\cf5 // Grumboz VIP Engine item \f2 Setter \f1 methods \cf3\par
\tab\{ \cf4 "SetItemVIP"\cf3 , &LuaItem::SetItemVIP \},\par
\cf0\highlight0\f0\fs22 [/CODE]\par
\par
*********************************************************\par
GlobalMethods.h\par
\par
add with the includes\par
[CODE]\par
\cf1\highlight2\f1\fs19 #include\cf3  \cf4 "Grumboz_VIP_Core.h"\cf3\par
\cf0\highlight0\f0\fs22 [/CODE]\par
\par
[CODE]\par
\cf3\highlight2\f1\fs19\tab\cf5 // Grumboz VIP Engine player methods\cf3\par
\tab\cf1 int\cf3  GetVIPMAX(Eluna* \cf5 /*E*/\cf3 , lua_State* L)\par
\tab\{\par
\tab\tab Eluna::Push(L, VIP::GetVIPMAX());\par
\tab\tab\cf1 return\cf3  1;\par
\tab\}\par
\tab\cf1 int\cf3  GetVIPVOTE_ENABLE(Eluna* \cf5 /*E*/\cf3 , lua_State* L)\par
\tab\{\par
\tab\tab Eluna::Push(L, VIP::GetVIPVOTE_ENABLE());\par
\tab\tab\cf1 return\cf3  1;\par
\tab\}\par
\tab\cf1 int\cf3  GetVIPVOTECOUNT(Eluna* \cf5 /*E*/\cf3 , lua_State* L)\par
\tab\{\par
\tab\tab Eluna::Push(L, VIP::GetVIPVOTECOUNT());\par
\tab\tab\cf1 return\cf3  1;\par
\tab\}\par
\tab\cf1 int\cf3  GetVIPCOINID(Eluna* \cf5 /*E*/\cf3 , lua_State* L)\par
\tab\{\par
\tab\tab Eluna::Push(L, VIP::GetVIPCOINID());\par
\tab\tab\cf1 return\cf3  1;\par
\tab\}\par
\tab\cf1 int\cf3  GetVIPSTONEID(Eluna* \cf5 /*E*/\cf3 , lua_State* L)\par
\tab\{\par
\tab\tab Eluna::Push(L, VIP::GetVIPSTONEID());\par
\tab\tab\cf1 return\cf3  1;\par
\tab\}\par
\tab\cf1 int\cf3  GetVIPMGID(Eluna* \cf5 /*E*/\cf3 , lua_State* L)\par
\tab\{\par
\tab\tab Eluna::Push(L, VIP::GetVIPMGID());\par
\tab\tab\cf1 return\cf3  1;\par
\tab\}\par
\tab\cf1 int\cf3  GetVIPOFFSET(Eluna* \cf5 /*E*/\cf3 , lua_State* L)\par
\tab\{\par
\tab\tab Eluna::Push(L, VIP::GetVIPOFFSET());\par
\tab\tab\cf1 return\cf3  1;\par
\tab\}\par
\tab\cf1 int\cf3  GetTALENTBONUS(Eluna* \cf5 /*E*/\cf3 , lua_State* L)\par
\tab\{\par
\tab\tab Eluna::Push(L, VIP::GetTALENTBONUS());\par
\tab\tab\cf1 return\cf3  1;\par
\tab\}\par
\tab\cf1 int\cf3  GetLEVELBONUS_ENABLE(Eluna* \cf5 /*E*/\cf3 , lua_State* L)\par
\tab\{\par
\tab\tab Eluna::Push(L, VIP::GetLEVELBONUS_ENABLE());\par
\tab\tab\cf1 return\cf3  1;\par
\tab\}\par
\tab\cf1 int\cf3  GetLEVELBONUS(Eluna* \cf5 /*E*/\cf3 , lua_State* L)\par
\tab\{\par
\tab\tab Eluna::Push(L, VIP::GetLEVELBONUS());\par
\tab\tab\cf1 return\cf3  1;\par
\tab\}\par
\cf0\highlight0\f0\fs22 [/CODE]\par
\par
PlayerMethods.h\par
\par
add with the includes\par
[CODE]\par
\cf1\highlight2\f1\fs19 #include\cf3  \cf4 "Grumboz_VIP_Core.h"\cf3\par
\cf0\highlight0\f0\fs22 [/CODE]\par
\par
[CODE]\par
\cf3\highlight2\f1\fs19\tab\tab\cf5 // Grumboz VIP Engine player methods\cf3\par
\tab\tab\cf1 int\cf3  GetPlayerVIP(\cf6 Eluna\cf3 * \cf5 /*E*/\cf3 , \cf6 lua_State\cf3 * \cf7 L\cf3 , \cf6 Player\cf3 * \cf7 player\cf3 )\par
\tab\tab\{\par
\tab\tab\cf6 uint32\cf3  acctId = \cf7 player\cf3 ->GetSession()->GetAccountId();\par
\tab\tab\cf6 Eluna\cf3 ::Push(\cf7 L\cf3 , \cf6 VIP\cf3 ::GetPlayerVIP(acctId));\par
\tab\tab\cf1 return\cf3  1;\par
\tab\tab\}\par
\tab\cf1 int\cf3  GetPlayerMG(\cf6 Eluna\cf3 * \cf5 /*E*/\cf3 , \cf6 lua_State\cf3 * \cf7 L\cf3 , \cf6 Player\cf3 * \cf7 player\cf3 )\par
\tab\tab\{\par
\tab\tab\cf6 uint32\cf3  acctId = \cf7 player\cf3 ->GetSession()->GetAccountId();\par
\tab\tab\cf6 Eluna\cf3 ::Push(\cf7 L\cf3 , \cf6 VIP\cf3 ::GetPlayerMG(acctId));\par
\tab\tab\cf1 return\cf3  1;\par
\tab\tab\}\par
\tab\cf1 int\cf3  GetPlayerVOTES(\cf6 Eluna\cf3 * \cf5 /*E*/\cf3 , \cf6 lua_State\cf3 * \cf7 L\cf3 , \cf6 Player\cf3 * \cf7 player\cf3 )\par
\tab\tab\{\par
\tab\tab\cf6 uint32\cf3  acctId = \cf7 player\cf3 ->GetSession()->GetAccountId();\par
\tab\tab\cf6 Eluna\cf3 ::Push(\cf7 L\cf3 , \cf6 VIP\cf3 ::GetPlayerVOTES(acctId));\par
\tab\tab\cf1 return\cf3  1;\par
\tab\tab\}\par
\tab\cf1 int\cf3  SetPlayerVIP(\cf6 Eluna\cf3 * \cf5 /*E*/\cf3 , \cf6 lua_State\cf3 * \cf7 L\cf3 , \cf6 Player\cf3 * \cf7 player\cf3 )\par
\tab\tab\{\par
\tab\tab\cf6 uint32\cf3  acctId = \cf7 player\cf3 ->GetSession()->GetAccountId();\par
\tab\tab\cf6 uint8\cf3  vip = \cf6 Eluna\cf3 ::CHECKVAL<\cf6 uint8\cf3 >(\cf7 L\cf3 , 2);\par
\tab\tab\cf6 VIP\cf3 ::SetPlayerVIP(acctId, vip);\par
\tab\tab\cf1 return\cf3  0;\par
\tab\tab\}\par
\tab\cf1 int\cf3  SetPlayerMG(\cf6 Eluna\cf3 * \cf5 /*E*/\cf3 , \cf6 lua_State\cf3 * \cf7 L\cf3 , \cf6 Player\cf3 * \cf7 player\cf3 )\par
\tab\tab\{\par
\tab\tab\cf6 uint32\cf3  acctId = \cf7 player\cf3 ->GetSession()->GetAccountId();\par
\tab\tab\cf6 uint32\cf3  mg = \cf6 Eluna\cf3 ::CHECKVAL<\cf6 uint32\cf3 >(\cf7 L\cf3 , 2);\par
\tab\tab\cf6 VIP\cf3 ::SetPlayerMG(acctId, mg);\par
\tab\tab\cf1 return\cf3  0;\par
\tab\tab\}\par
\tab\cf1 int\cf3  SetPlayerVOTES(\cf6 Eluna\cf3 * \cf5 /*E*/\cf3 , \cf6 lua_State\cf3 * \cf7 L\cf3 , \cf6 Player\cf3 * \cf7 player\cf3 )\par
\tab\tab\{\par
\tab\tab\cf6 uint32\cf3  acctId = \cf7 player\cf3 ->GetSession()->GetAccountId();\par
\tab\tab\cf6 uint32\cf3  votes = \cf6 Eluna\cf3 ::CHECKVAL<\cf6 uint32\cf3 >(\cf7 L\cf3 , 2);\par
\tab\tab\cf6 VIP\cf3 ::SetPlayerVOTES(acctId, votes);\par
\tab\tab\cf1 return\cf3  0;\par
\tab\tab\}\par
\cf0\highlight0\f0\fs22 [/CODE]\par
\par
*************************************************\par
creatureMethods.h\par
\par
add with the includes\par
[CODE]\par
\cf1\highlight2\f1\fs19 #include\cf3  \cf4 "Grumboz_VIP_Core.h"\cf3\par
\cf0\highlight0\f0\fs22 [/CODE]\par
\par
[CODE]\par
\cf3\highlight2\f1\fs19\tab\cf5 // Grumboz VIP Engine creature methods\cf3\par
\tab\cf1 int\cf3  GetCreatureVIP(\cf6 Eluna\cf3 * \cf5 /*E*/\cf3 , \cf6 lua_State\cf3 * \cf7 L\cf3 , \cf6 Creature\cf3 * \cf7 creature\cf3 )\par
\tab\{\par
\tab\tab\cf6 uint32\cf3  creature_id = \cf7 creature\cf3 ->GetEntry();\par
\tab\tab\par
\tab\tab\cf6 Eluna\cf3 ::Push(\cf7 L\cf3 , \cf6 VIP\cf3 ::GetCreatureVIP(creature_id));\par
\tab\tab\cf1 return\cf3  1;\par
\tab\}\par
\tab\cf1 int\cf3  GetCreatureMG(\cf6 Eluna\cf3 * \cf5 /*E*/\cf3 , \cf6 lua_State\cf3 * \cf7 L\cf3 , \cf6 Creature\cf3 * \cf7 creature\cf3 )\par
\tab\{\par
\tab\tab\cf6 uint32\cf3  creature_id = \cf7 creature\cf3 ->GetEntry();\par
\par
\tab\tab\cf6 Eluna\cf3 ::Push(\cf7 L\cf3 , \cf6 VIP\cf3 ::GetCreatureMG(creature_id));\par
\tab\tab\cf1 return\cf3  1;\par
\tab\}\par
\tab\cf1 int\cf3  SetCreatureVIP(\cf6 Eluna\cf3 * \cf5 /*E*/\cf3 , \cf6 lua_State\cf3 * \cf7 L\cf3 , \cf6 Creature\cf3 * \cf7 creature\cf3 )\par
\tab\{\par
\tab\tab\cf6 uint32\cf3  creature_id = \cf7 creature\cf3 ->GetEntry();\par
\tab\tab\cf6 uint8\cf3  vip = \cf6 Eluna\cf3 ::CHECKVAL<\cf6 uint8\cf3 >(\cf7 L\cf3 , 2);\par
\par
\tab\tab\cf6 VIP\cf3 ::SetCreatureVIP(creature_id, vip);\par
\tab\tab\cf1 return\cf3  0;\par
\tab\}\par
\tab\cf1 int\cf3  SetCreatureMG(\cf6 Eluna\cf3 * \cf5 /*E*/\cf3 , \cf6 lua_State\cf3 * \cf7 L\cf3 , \cf6 Creature\cf3 * \cf7 creature\cf3 )\par
\tab\{\par
\tab\tab\cf6 uint32\cf3  creature_id = \cf7 creature\cf3 ->GetEntry();\par
\tab\tab\cf6 uint32\cf3  mg = \cf6 Eluna\cf3 ::CHECKVAL<\cf6 uint32\cf3 >(\cf7 L\cf3 , 2);\par
\par
\tab\tab\cf6 VIP\cf3 ::SetCreatureMG(creature_id, mg);\par
\tab\tab\cf1 return\cf3  0;\par
\tab\}\par
\cf0\highlight0\f0\fs22 [/CODE]\par
\par
**************************************************\par
itemMethods.h\par
\par
add with the includes\par
[CODE]\par
\cf1\highlight2\f1\fs19 #include\cf3  \cf4 "Grumboz_VIP_Core.h"\cf3\par
\cf0\highlight0\f0\fs22 [/CODE]\par
\par
[CODE]\par
\cf3\highlight2\f1\fs19\tab\cf5 // Grumboz VIP Engine item methods\cf3\par
\tab\cf1 int\cf3  GetItemVIP(\cf6 Eluna\cf3 * \cf5 /*E*/\cf3 , \cf6 lua_State\cf3 * \cf7 L\cf3 , \cf6 Item\cf3 * \cf7 item\cf3 )\par
\tab\{\par
\tab\tab\cf6 uint32\cf3  item_id = \cf7 item\cf3 ->GetEntry();\par
\tab\tab\cf6 Eluna\cf3 ::Push(\cf7 L\cf3 , \cf6 VIP\cf3 ::GetItemVIP(item_id));\par
\tab\tab\cf1 return\cf3  1;\par
\tab\}\par
\tab\cf1 int\cf3  SetItemVIP(\cf6 Eluna\cf3 * \cf5 /*E*/\cf3 , \cf6 lua_State\cf3 * \cf7 L\cf3 , \cf6 Item\cf3 * \cf7 item\cf3 )\par
\tab\{\par
\tab\tab\cf6 uint32\cf3  item_id = \cf7 item\cf3 ->GetEntry();\par
\tab\tab\cf6 uint8\cf3  vip = \cf6 Eluna\cf3 ::CHECKVAL<\cf6 uint8\cf3 >(\cf7 L\cf3 , 2);\par
\tab\tab\cf6 VIP\cf3 ::SetItemVIP(item_id, vip);\par
\tab\tab\cf1 return\cf3  1;\par
\tab\}\par
\cf0\highlight0\f0\fs22 [/CODE]\par
\par
\par
\par
\par
\par
\par
\par
\par
\par
}
