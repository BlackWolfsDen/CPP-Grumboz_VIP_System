local VIP_MAX_RANK = GetVIPMAX();
local VIP_VOTE_COUNT = GetVIPVOTECOUNT();
local VIP_COIN_ID = GetVIPCOINID();
local VIP_STONE_ID = GetVIPSTONEID();
local VIP_MG_ID = GetVIPMGID();
local VIP_OFFSET_VALUE = GetVIPOFFSET();
local VIP_TALENT_BONUS = GetTALENTBONUS();
local VIP_LEVEL_BONUS = GetLEVELBONUS();
local VIP_VOTE_ENABLE = GetVIPVOTE_ENABLE();
local VIP_LEVEL_BONUS_ENABLE = GetLEVELBONUS_ENABLE();

print("-----------------------");
print("   Grumboz VIP Core    ");
print("     Method demo       ");
print("-----------------------");
print("GLOBAL METHODS:");
print("-----------------------");
print("VIP_MAX_RANK "..VIP_MAX_RANK);
print("VIP_VOTE_COUNT "..VIP_VOTE_COUNT);
print("VIP_COIN_ID "..VIP_COIN_ID);
print("VIP_STONE_ID "..VIP_STONE_ID);
print("VIP_MG_ID "..VIP_MG_ID);
print("VIP_OFFSET_VALUE "..VIP_OFFSET_VALUE);
print("VIP_TALENT_BONUS "..VIP_TALENT_BONUS);
print("VIP_LEVEL_BONUS "..VIP_LEVEL_BONUS);
if(VIP_VOTE_ENABLE)then print("VIP_VOTE_ENABLE TRUE") end;
if not(VIP_VOTE_ENABLE)then print("VIP_VOTE_ENABLE FALSE") end;
if(VIP_LEVEL_BONUS_ENABLE)then print("VIP_LEVEL_BONUS_ENABLE TRUE") end;
if not(VIP_LEVEL_BONUS_ENABLE)then print("VIP_LEVEL_BONUS_ENABLE FALSE") end;
print("-----------------------");

local function OnLogin(event, player)

local VIP_PLAYER_VIP = player:GetPlayerVIP();
local VIP_PLAYER_MG = player:GetPlayerMG();
local VIP_PLAYER_VOTE_COUNT = player:GetPlayerVOTES();

print("-----------------------");
print("   Grumboz VIP Core    ");
print("     Method demo       ");
print("-----------------------");
print("PLAYER METHODS:");
print("-----------------------");
print("VIP_PLAYER_VIP "..VIP_PLAYER_VIP);
print("VIP_PLAYER_MG "..VIP_PLAYER_MG);
print("VIP_PLAYER_VOTE_COUNT "..VIP_PLAYER_VOTE_COUNT);
print("-----------------------");

end

local function OnEquipItem(event, player, item)
local VIP_ITEM_VIP = item:GetItemVIP();

print("-----------------------");
print("   Grumboz VIP Core    ");
print("     Method demo       ");
print("-----------------------");
print("ITEM METHODS:");
print("-----------------------");
print("ITEM_NAME "..item:GetName());
print("VIP_ITEM_VIP "..VIP_ITEM_VIP);
print("-----------------------");

end

RegisterPlayerEvent( 3, OnLogin )
RegisterPlayerEvent( 29, OnEquipItem )
