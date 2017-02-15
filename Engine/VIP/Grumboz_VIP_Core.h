#ifndef GRUMBOZ_VIP_CORE_H
#define GRUMBOZ_VIP_CORE_H

#include <unordered_map>

struct VipElements
{
	uint8 vip;
	uint32 mg;
	uint32 votes;
};

struct ItemVIP
{
	uint32 item_id;
	uint8 vip;
};

struct CreatureVIP
{
	uint8 vip;
	uint8 mg;
};

struct VipMallGPS
{
	uint32 map_id;
	float x;
	float y;
	float z;
	float o;
};

struct VipHomeGPS
{
	uint32 map_id;
	float x;
	float y;
	float z;
	float o;
};

struct VipHearthStoneGPS
{
	uint32 guid;
	uint32 map_id;
	float x;
	float y;
	float z;
	float o;
};

class VIP
{

private:
	VIP();
	~VIP();

public:
	static VIP* instance();

	// Global
		// Getterz
		uint8 GetVIPMAX() { return VIP_MAX; }
		bool GetVIPVOTE_ENABLE() { return VIP_VOTE_ENABLE != 0; }
		uint32 GetVIPVOTECOUNT() { return VIP_VOTE_COUNT;	}
		uint32 GetVIPCOINID() { return VIP_COIN_ID; }
		std::string GetVIP_COIN_NAME() { return VIP_COIN_NAME; }
		uint32 GetVIPSTONEID() { return VIP_STONE_ID; }
		uint32 GetVIPMGID() { return VIP_MG_ID; }
		float GetVIPOFFSET() { return VIP_OFFSET; }
		uint8 GetTALENTBONUS() { return VIP_TP_BONUS; }
		bool GetLEVELBONUS_ENABLE() { return VIP_LEVEL_BONUS_ENABLE != 0; }
		uint8 GetLEVELBONUS() { return VIP_LEVEL_BONUS; }

		// Setters
		void SetVIPMAX(uint8 v) { VIP_MAX = v; }
		void SetVIPVOTE_ENABLE(bool v) { VIP_VOTE_ENABLE = v; }
		void SetVIPVOTECOUNT(uint32 v) { VIP_VOTE_COUNT = v; }
		void SetVIPCOINID(uint32 v) { VIP_COIN_ID = v; }
		void SetVIP_COIN_NAME(std::string v) { VIP_COIN_NAME = v; }
		void SetVIPSTONEID(uint32 v) { VIP_STONE_ID =  v; }
		void SetVIPMGID(uint32 v) { VIP_MG_ID = v; }
		void SetVIPOFFSET(float v) { VIP_OFFSET = v; }
		void SetTALENTBONUS(uint8 v) { VIP_TP_BONUS = v; }
		void SetLEVELBONUS_ENABLE(bool v) { VIP_LEVEL_BONUS_ENABLE = v; }
		void SetLEVELBONUS(uint8 v) { VIP_LEVEL_BONUS = v; }

	// Player
		// Getters
		uint8 GetPlayerVIP(uint32 v) { return Vip[v].vip; }
		uint32 GetPlayerMG(uint32 v) { return Vip[v].mg; }
		uint32 GetPlayerVOTES(uint32 v) { return Vip[v].votes; }

		// Setterz
		static void SetPlayerVIP(uint32 acct_id, uint8 pvip);
		static void SetPlayerMG(uint32 acct_id, uint32 pmg);
		static void SetPlayerVOTES(uint32 acct_id, uint32 pvotes);
		static void SetHearthStone(uint32 guid, uint32 map_id, float x, float y, float z, float o);

	// Items
		// Getters
		uint8 GetItemVIP(uint32 v) { return ItemVip[v].vip; }

		// Setters
		static void SetItemVIP(uint32 item_id, uint8 item_vip);

	// Creature
		// Getters
		uint8 GetCreatureVIP(uint32 v) { return CKR[v].vip; }
		uint32 GetCreatureMG(uint32 v) { return CKR[v].mg; }

		// Setters
		static void SetCreatureVIP(uint32 creature_id, uint8 creature_vip);
		static void SetCreatureMG(uint32 creature_id, uint8 creature_mg);

		// tools
		std::string ConvertNumberToString(uint64 numberX);
		void RemoveItem(uint32 id, Player* player);
		void AnnounceLoggingToWorld(Player* player, uint8 type);

		// Public Tables
	std::unordered_map<uint32, VipElements> Vip;
	std::unordered_map<uint32, ItemVIP> ItemVip;
	std::unordered_map<uint8, VipMallGPS> MALL;
	std::unordered_map<uint8, VipHomeGPS> HOME;
	std::unordered_map<uint32, VipHearthStoneGPS> HearthStone;
	std::unordered_map<uint32, CreatureVIP>CKR;

private:
	// Local Variables
	uint8 VIP_MAX;
	uint8 VIP_LEVEL_BONUS;
	uint8 VIP_TP_BONUS;
	uint32 VIP_STONE_ID;
	uint32 VIP_COIN_ID;
	uint32 VIP_MG_ID;
	uint32 VIP_VOTE_COUNT;
	float VIP_OFFSET;
	bool VIP_VOTE_ENABLE;
	bool VIP_LEVEL_BONUS_ENABLE;
	std::string VIP_COIN_NAME;

};

#define sVIP VIP::instance()
#endif
