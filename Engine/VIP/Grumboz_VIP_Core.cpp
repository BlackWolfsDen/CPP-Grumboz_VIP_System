// Vip core engine
// By slp13at420 of EmuDevs.com
// TDB 335.19111

#include "AccountMgr.h"
#include "chat.h"
#include "Config.h"
#include "DatabaseEnv.h"
#include "Group.h"
#include "Grumboz_VIP_Core.h"
#include "Language.h"
#include "Log.h"
#include "Movement\MotionMaster.h"
#include "ObjectMgr.h"
#include "player.h"
#include "RBAC.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include <unordered_map>
#include "World.h"
#include "WorldSession.h"


// color definitions since i hate yellow..
std::string green = "|cff00cc00";
std::string red = "|cffFF0000";
std::string white = "|cffFFFFFF";
std::string blue = "|cff3333FF";
std::string black = "|cff000000";

float ver = 3.15f;

int VIPBUFFS[24] = { 24752, 48074, 43223, 36880, 467, 48469, 48162, 48170, 16877, 10220, 13033, 11735, 10952, 23948, 26662, 47440, 53307, 132, 23737, 48470, 43002, 26393, 24705, 69994 };

VIP::VIP() { }

VIP::~VIP()
{
	for (std::unordered_map<uint32, VipElements>::iterator itr = Vip.begin(); itr != Vip.end(); ++itr)
		delete &itr->second;
	for (std::unordered_map<uint32, ItemVIP>::iterator itr = ItemVip.begin(); itr != ItemVip.end(); ++itr)
		delete &itr->second;
	for (std::unordered_map<uint8, VipMallGPS>::iterator itr = MALL.begin(); itr != MALL.end(); ++itr)
		delete &itr->second;
	for (std::unordered_map<uint8, VipHomeGPS>::iterator itr = HOME.begin(); itr != HOME.end(); ++itr)
		delete &itr->second;
	for (std::unordered_map<uint32, VipHearthStoneGPS>::iterator itr = HearthStone.begin(); itr != HearthStone.end(); ++itr)
		delete &itr->second;
	for (std::unordered_map<uint32, CreatureVIP>::iterator itr = CKR.begin(); itr != CKR.end(); ++itr)
		delete &itr->second;

	Vip.clear();
	ItemVip.clear();
	MALL.clear();
	HOME.clear();
	HearthStone.clear();
	CKR.clear();
}

VIP* VIP::instance()
{
	static VIP instance;
	return &instance;
}

std::string ConvertNumberToString(uint64 numberX)
{
	auto number = numberX;
	std::stringstream convert;
	std::string number32_to_string;
	convert << number;
	number32_to_string = convert.str();

	return number32_to_string;
};

void AnnounceLoggingToWorld(Player* player, uint8 type)
{
	std::string pName = player->GetName();
	uint32 acct_id = player->GetSession()->GetAccountId();
	uint8 PlayerLogInVip = sVIP->GetPlayerVIP(acct_id);

	SessionMap sessions = sWorld->GetAllSessions(); // GetPlayersInWorld

	for (SessionMap::iterator itr = sessions.begin(); itr != sessions.end(); ++itr)
	{
		if (!itr->second)
			continue;

		uint8 ItrVip = sVIP->GetPlayerVIP(itr->second->GetAccountId());

		if (PlayerLogInVip <= ItrVip) // if target is same as or higher. won't announce to lower vip's.
		{
			std::string msg = "[" + green + "VIP" + ConvertNumberToString(PlayerLogInVip) + "|r]:";
			msg = msg + pName + green + " has logged";

			if (type == 0) { msg = msg + " out.|r"; };
			if (type == 1) { msg = msg + " in.|r"; };

			if (itr->second->GetPlayer()) { ChatHandler(itr->second->GetPlayer()->GetSession()).PSendSysMessage(msg.c_str()); };
		}
	}
};

class VIP_Load_Conf : public WorldScript
{
public: VIP_Load_Conf() : WorldScript("VIP_Load_Conf") { };

		virtual void OnConfigLoad(bool /*reload*/)
		{
			TC_LOG_INFO("server.loading", "___________________________________");
			TC_LOG_INFO("server.loading", "| Grumbo'z  VIP  Engine : Loading |");
			TC_LOG_INFO("server.loading", "|__________By_Slp13at420__________|");
			TC_LOG_INFO("server.loading", "|_________of__EmuDevs.com_________|");
			TC_LOG_INFO("server.loading", "|-                               -|");
			TC_LOG_INFO("server.loading", "|____________Ver:%.2f_____________|", ver);

			QueryResult VIPItemQery = WorldDatabase.PQuery("SELECT entry, vip FROM item_template;");

			if (VIPItemQery)
			{
				do
				{
					Field* fields = VIPItemQery->Fetch();
					uint32 item_id = fields[0].GetUInt32();
					uint32 vip = fields[1].GetUInt8();

					ItemVIP& data1 = sVIP->ItemVip[item_id];
					// Save the DB values to the MyData object
					data1.item_id = item_id;
					data1.vip = vip;

				} while (VIPItemQery->NextRow());
			}

			QueryResult VIPCreatureQery = WorldDatabase.PQuery("SELECT entry, vip, mg FROM creature_template;");

			if (VIPCreatureQery)
			{
				do
				{
					Field* fields = VIPCreatureQery->Fetch();
					uint32 entry_id = fields[0].GetUInt32();
					uint32 vip = fields[1].GetUInt8();
					uint32 mg = fields[2].GetUInt32();

					CreatureVIP& data2 = sVIP->CKR[entry_id];
					// Save the DB values to the MyData object
					data2.vip = vip;
					data2.mg = mg;

				} while (VIPCreatureQery->NextRow());
			}

			QueryResult gpsQery = WorldDatabase.PQuery("SELECT * FROM hearthstone;");

			if (gpsQery)
			{
				do
				{
					// unpacks the results of `result` into fields and appoint data to variable.
					Field* fields = gpsQery->Fetch();
					uint32 guid = fields[0].GetUInt32();
					uint32 map_id = fields[1].GetUInt32();
					float x = fields[2].GetFloat();
					float y = fields[3].GetFloat();
					float z = fields[4].GetFloat();
					float o = fields[5].GetFloat();

					VipHearthStoneGPS& data3 = sVIP->HearthStone[guid];
					// Save the DB values to the MyData object
					data3.guid = guid;
					data3.map_id = map_id;
					data3.x = x;
					data3.y = y;
					data3.z = z;
					data3.o = o;

				} while (gpsQery->NextRow());
			}

			VipMallGPS& data4 = sVIP->MALL[0];
			// Save the DB values to the MyData object
			data4.map_id = 530;
			data4.x = -1800.3104f;
			data4.y = 5315.0424f;
			data4.z = -12.4276f;
			data4.o = 2.1062f;

			VipMallGPS& data5 = sVIP->MALL[1]; // like Lua table VIP[acctId].vip
											   // Save the DB values to the MyData object
			data5.map_id = 530;
			data5.x = -1921.8005f;
			data5.y = 5546.6264f;
			data5.z = -12.4278f;
			data5.o = 5.2321f;

			VipHomeGPS& data6 = sVIP->HOME[0]; // like Lua table VIP[acctId].vip
											   // Save the DB values to the MyData object
			data6.map_id = 0;
			data6.x = -4906.3911f;
			data6.y = -970.9063f;
			data6.z = 501.4540f;
			data6.o = 2.3338f;

			VipHomeGPS& data7 = sVIP->HOME[1]; // like Lua table VIP[acctId].vip
											   // Save the DB values to the MyData object
			data7.map_id = 1;
			data7.x = 1604.4882f;
			data7.y = -4394.3603f;
			data7.z = 9.9671f;
			data7.o = 3.5517f;

			TC_LOG_INFO("server.loading", "|  VIP Teleport GPS's : Loaded    ");

			sVIP->SetVIPMAX(sConfigMgr->GetIntDefault("VIP.MAX", 6));
            sVIP->SetVIPSTART(sConfigMgr->GetIntDefault("VIP.START", 0));
			sVIP->SetVIPVOTE_ENABLE(sConfigMgr->GetBoolDefault("VIP.VOTE_ENABLE", true));
			sVIP->SetVIPVOTECOUNT(sConfigMgr->GetIntDefault("VIP.VOTE_COUNT", 125));
			sVIP->SetVIPCOINID(sConfigMgr->GetIntDefault("VIP.COIN", 63020));
			sVIP->SetVIPSTONEID(sConfigMgr->GetIntDefault("VIP.STONE", 63021));
			sVIP->SetVIPMGID(sConfigMgr->GetIntDefault("VIP.MAGIC_GOLD", 44209));
			sVIP->SetVIPOFFSET(sConfigMgr->GetFloatDefault("VIP.OFFSET", 0.05f));
			sVIP->SetTALENTBONUS(sConfigMgr->GetIntDefault("VIP.TP_BONUS", 14));
			sVIP->SetLEVELBONUS_ENABLE(sConfigMgr->GetBoolDefault("VIP.LEVEL_BONUS_ENABLE", true));
			sVIP->SetLEVELBONUS(sConfigMgr->GetIntDefault("VIP.LEVEL_BONUS", 1));
            sVIP->SetVIPTEST(sConfigMgr->GetBoolDefault("VIP.TEST", 0));

			TC_LOG_INFO("server.loading", "|  VIP MAX_VIP : %u", sVIP->GetVIPMAX());
            if (sVIP->GetVIPSTART()) { TC_LOG_INFO("server.loading", "|  VIP START RANK : 1"); } else { TC_LOG_INFO("server.loading", "|  VIP START RANK : 0"); }

			if (sVIP->GetVIPVOTE_ENABLE())
			{
				TC_LOG_INFO("server.loading", "|  VIP VOTES : ENABLED             ");
			}

			TC_LOG_INFO("server.loading", "|  VIP TP BONUS : %u", sVIP->GetVIPVOTECOUNT());

			if (sVIP->GetLEVELBONUS_ENABLE())
			{
				TC_LOG_INFO("server.loading", "|  VIP LEVEL BONUS : ENABLED       ");
				TC_LOG_INFO("server.loading", "|  VIP LEVEL BONUS : %u", sVIP->GetLEVELBONUS());
				TC_LOG_INFO("server.loading", "|  VIP offset : %.2f", sVIP->GetVIPOFFSET());
			}

			if (!sObjectMgr->GetItemTemplate(sVIP->GetVIPCOINID()))
            {
                TC_LOG_INFO("server.loading", "! VIP COIN %u MISSING FROM DB ! SERVER CRASHING !", sVIP->GetVIPCOINID());
            }

            TC_LOG_INFO("server.loading", "|  VIP Coin ID : %u", sVIP->GetVIPCOINID());
            TC_LOG_INFO("server.loading", "|  VIP Stone ID : %u", sVIP->GetVIPSTONEID());

			sVIP->SetVIP_COIN_NAME(sObjectMgr->GetItemTemplate(sVIP->GetVIPCOINID())->Name1);

			TC_LOG_INFO("server.loading", "___________________________________");
			TC_LOG_INFO("server.loading", "|  VIP Config : Loaded            |");
			TC_LOG_INFO("server.loading", "|  Grumbo'z VIP Engine : Loaded   |");
			TC_LOG_INFO("server.loading", "|_________________________________|");
		}
};

void VIP::SetHearthStone(uint32 guid, uint32 map_id, float x, float y, float z, float o)
{
	WorldDatabase.PExecute("REPLACE INTO `hearthstone` SET `guid`='%u', `map_id`='%u', `x`='%f', `y`='%f', `z`='%f', `o`='%f';", guid, map_id, x, y, z, o);

	VipHearthStoneGPS& data = sVIP->HearthStone[guid];
	// Save the DB values to the MyData object
	data.guid = guid;
	data.map_id = map_id;
	data.x = x;
	data.y = y;
	data.z = z;
	data.o = o;
}

void VIP::SetPlayerVIP(uint32 acct_id, uint8 pvip)
{ // you must update votes first for the dead mans check

	LoginDatabase.PExecute("UPDATE account SET `vip`='%u' WHERE `id`='%u';", pvip, acct_id);

	sVIP->Vip[acct_id].vip = pvip;
}

void VIP::SetPlayerMG(uint32 acct_id, uint32 pmg)
{
	LoginDatabase.PExecute("UPDATE account SET `mg`='%u' WHERE `id`='%u';", pmg, acct_id);

	sVIP->Vip[acct_id].mg = pmg;
}

void VIP::SetPlayerVOTES(uint32 acct_id, uint32 pvotes)
{
	LoginDatabase.PExecute("UPDATE account SET `votes`='%u' WHERE `id`='%u';", pvotes, acct_id);

	sVIP->Vip[acct_id].votes = pvotes;
}

void VIP::SetItemVIP(uint32 item_id, uint8 item_vip)
{
	uint8 sVmax = sVIP->GetVIPMAX();

	if (item_vip < 1) { item_vip = 1; };
	if (item_vip > sVmax) { item_vip = sVmax; };

	WorldDatabase.PExecute("REPLACE INTO item_template SET `vip`='%u' WHERE `id`='%u';", item_vip, item_id);

	sVIP->ItemVip[item_id].vip = item_vip;
}

void VIP::SetCreatureVIP(uint32 creature_id, uint8 creature_vip)
{
	uint8 sVmax = sVIP->GetVIPMAX();

	if (creature_vip < 1) { creature_vip = 1; };
	if (creature_vip > sVmax) { creature_vip = sVmax; };

	WorldDatabase.PExecute("REPLACE INTO creature_template SET `vip`='%u' WHERE `id`='%u';", creature_vip, creature_id);

	sVIP->CKR[creature_id].vip = creature_vip;
}

void VIP::SetCreatureMG(uint32 creature_id, uint8 creature_mg)
{
	WorldDatabase.PExecute("REPLACE INTO creature_template SET `mg`='%u' WHERE `id`='%u';", creature_mg, creature_id);

	sVIP->CKR[creature_id].mg = creature_mg;
}

class Grumboz_VIP_Account_Engine : public AccountScript
{
public: Grumboz_VIP_Account_Engine() : AccountScript("Grumboz_VIP_Account_Engine") { };

		virtual void OnAccountLogout(uint32 accountId)
		{
			TC_LOG_INFO("server.loading", "ACCOUNT::LOGOUT ID:%u VIP:%u", accountId, sVIP->Vip[accountId].vip);

			sVIP->Vip.erase(accountId);
		}

		virtual void OnAccountLogin(uint32 accountId)
		{
			if (accountId > 0)
			{
				QueryResult PlayerVIPQuery = LoginDatabase.PQuery("SELECT `vip`, `mg`, `votes` FROM account WHERE `id`='%u';", accountId);

				if (!PlayerVIPQuery)
				{
					TC_LOG_INFO("server.loading", "XX ERROR Loading a VIP table ID %u XX", accountId);
				}

				if (PlayerVIPQuery)
				{
					// unpacks the results of `result` into fields and appoint data to variable.
					Field* fields = PlayerVIPQuery->Fetch();
					uint8 pvip = fields[0].GetUInt8();
					uint32 pmg = fields[1].GetUInt32();
					uint32 pvotes = fields[2].GetUInt32();

					VipElements& data = sVIP->Vip[accountId]; // like Lua table VIP[acctId].vip
															  // Save the DB values to the MyData object
					data.vip = pvip;
					data.mg = pmg;
					data.votes = pvotes;

                    if (sVIP->Vip[accountId].vip < (sVIP->GetVIPSTART() || 0)) { sVIP->SetPlayerVIP(accountId, (sVIP->GetVIPSTART() || 0)); }

                    if (sVIP->Vip[accountId].vip > sVIP->GetVIPMAX()) { sVIP->SetPlayerVIP(accountId, sVIP->GetVIPMAX()); }

                    if (sVIP->GetVIPTEST()) { TC_LOG_INFO("server.loading", "[ACCOUNT]::LOGIN ID:%u VIP:%u", accountId, sVIP->Vip[accountId].vip); }
				}
			}
		}
};

class Grumboz_VIP_Player_Engine : public PlayerScript
{
public: Grumboz_VIP_Player_Engine() : PlayerScript("Grumboz_VIP_Player_Engine") { };

		virtual void OnLogout(Player* player)
		{
			AnnounceLoggingToWorld(player, 0);
		}

		virtual void OnLogin(Player* player, bool firstLogin)
		{
			AnnounceLoggingToWorld(player, 1);

			uint32 guid = player->GetGUID();
            uint32 acct_id = player->GetSession()->GetAccountId();
			uint8 Pvip = sVIP->GetPlayerVIP(acct_id);
			bool lvl_enable = sVIP->GetLEVELBONUS_ENABLE();
			uint8 xtra_levels = sVIP->GetLEVELBONUS();
			uint8 Plvl = player->GetLevel();
			uint32 Php = player->GetHealth();
			uint8 max_level = sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);
            bool VIP_START = sVIP->GetVIPSTART();
            uint8 VIP_level_cap = (max_level + (xtra_levels * Pvip)); // has to compensate for base VIP 1

			ChatHandler(player->GetSession()).PSendSysMessage("Welcome %s, you are VIP %u.", player->GetName().c_str(), sVIP->Vip[acct_id].vip);
			ChatHandler(player->GetSession()).PSendSysMessage("%stype `.vip` for a list of VIP commands.", green.c_str());

			if (sVIP->HearthStone[guid].guid != guid)
			{
				sVIP->SetHearthStone(guid, player->GetMapId(), player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetOrientation());
			}

            if (Plvl != VIP_level_cap)
			{
				if (lvl_enable)
				{
					player->SetLevel(VIP_level_cap);
				}
			}

			player->SetMaxHealth(Php + ((Php * sVIP->GetVIPOFFSET()) * Pvip));

            if (sVIP->GetVIPTEST()) { TC_LOG_INFO("server.loading", "[PLAYER]::LOGIN ID:%u VIP:%u MAX HP:%u", acct_id, sVIP->Vip[acct_id].vip, player->GetHealth()); }
        }

		virtual void OnCreatureKill(Player* player, Creature* creature)
		{
			uint32 itemId = sVIP->GetVIPMGID();
			uint32 creatureId = creature->GetEntry();
			uint8 cVip = urand(1, sVIP->GetCreatureVIP(creatureId));
			uint32 cMg = sVIP->GetCreatureMG(creatureId);
			uint32 accountId = player->GetSession()->GetAccountId();
			uint32 MG = sVIP->GetPlayerMG(accountId);
			uint8 pVip = sVIP->GetPlayerVIP(accountId);
            uint32 reward = 0;

			if (cMg > 0)
			{
				if (player->GetGroup())
				{
					Group* group = player->GetGroup();

					Group::MemberSlotList const &members = group->GetMemberSlots();

					for (Group::MemberSlotList::const_iterator itr = members.begin(); itr != members.end(); ++itr)
					{
						Group::MemberSlot const &slot = *itr;
						Player* player = ObjectAccessor::FindPlayer((*itr).guid);

						if (player && player->GetSession())
						{

							reward = (cMg * cVip) * pVip;

							ChatHandler(player->GetSession()).PSendSysMessage("+%u", reward);
							if (!player->AddItem(itemId, reward))
							{
								sVIP->SetPlayerMG(accountId, MG + reward);

								ChatHandler(player->GetSession()).PSendSysMessage("Banked.");
							}

                        }
					}
				}
				else
				{
					reward = (cMg * cVip) * pVip;

					if (!player->AddItem(itemId, reward))
					{
						sVIP->SetPlayerMG(accountId, MG + reward);

						ChatHandler(player->GetSession()).PSendSysMessage("+%u Banked.", reward);
					}
				}

                if (sVIP->GetVIPTEST()) { TC_LOG_INFO("server.loading", "[CREATURE_KILL]:: ACCT_ID:%u ACCT_VIP:%u NPC_ID:%u NPC_VIP:%u NPC_DB_MG:%u REWARD_MG:%u", accountId, sVIP->Vip[accountId].vip, creatureId, cVip, cMg, reward); }
			}
		}
};

class VIP_commands : public CommandScript
{
public:
	VIP_commands() : CommandScript("VIP_commands") { }

	std::vector<ChatCommand> GetCommands() const
	{
		static std::vector<ChatCommand> vipCommandChangeTable =
		{
			{ "race", rbac::RBAC_IN_GRANTED_LIST, true, &HandleChangeRaceCommand, "allows the player to change there race during next login." },
		    { "faction", rbac::RBAC_IN_GRANTED_LIST, true, &HandleChangeFactionCommand, "allows the player to change there faction during next login." },
		    { "custom", rbac::RBAC_IN_GRANTED_LIST, true, &HandleCustomizeCommand, "allows the player to re-costumize there character during next login." },
		    { "scale", rbac::RBAC_IN_GRANTED_LIST, true, &HandleScaleCommand, "allows the player to re-size there character." },
		};

		static std::vector<ChatCommand> vipCommandSetTable =
		{
			{ "hearthstone", rbac::RBAC_IN_GRANTED_LIST, true, &HandleVipSetHearthstoneCommand, "stores players current gps to VIP hearthstone command." },
		};

		std::string repair_info = "repairs all the players items. Requires the player to possess a " + sVIP->GetVIP_COIN_NAME() + ".";

		static std::vector<ChatCommand> vipCommandTable =
		{
			{ "mall",		rbac::RBAC_IN_GRANTED_LIST, true, &HandleVipMallCommand, "Teleports the player to a VIP mall." },
		    { "home",		rbac::RBAC_IN_GRANTED_LIST, true, &HandleHomeCommand, "Teleports the player to there faction home mall." },
		    { "hearthstone",rbac::RBAC_IN_GRANTED_LIST, true, &HandleHearthStoneCommand, "Teleports a player to there custom pre-set location." },
		    { "repair",		rbac::RBAC_IN_GRANTED_LIST, true, &HandleRepairCommand, repair_info },
		    { "morph",		rbac::RBAC_IN_GRANTED_LIST, true, &HandleMORPHCommand, "Allows players to temporarily morph there characters." },
		    { "demorph",	rbac::RBAC_IN_GRANTED_LIST, true, &HandleDeMORPHCommand, "Allows players to demorph there characters." },
		    { "buff",		rbac::RBAC_IN_GRANTED_LIST, true, &HandleBuffCommand, "VIP Command used to Buff your character. Amount of Buffs are based on VIP level." },
		    { "set",		rbac::RBAC_IN_GRANTED_LIST, true, NULL, "Player customizable commands.", vipCommandSetTable },
		    { "change",		rbac::RBAC_IN_GRANTED_LIST, true, NULL, "Character customizing commands.", vipCommandChangeTable },
		};

		static std::vector<ChatCommand> commandTable =
		{
			{ "vip", rbac::RBAC_IN_GRANTED_LIST, true, NULL, "custom VIP commands by Grumbo. Some commands may require player has an item.", vipCommandTable },
		};
		return commandTable;
	}

	static bool HandleVipMallCommand(ChatHandler* handler, const char* args)
	{

		Player* player = handler->GetSession()->GetPlayer();

		auto team_id = player->GetTeamId();

		if (player->IsInCombat())
		{
			handler->SendSysMessage(LANG_YOU_IN_COMBAT);
			handler->SetSentErrorMessage(true);
			return false;
		}

		// stop flight if need
		if (player->IsInFlight())
		{
            player->GetMotionMaster()->Remove(EFFECT_MOTION_TYPE); // MovementExpired();
			player->CleanupAfterTaxiFlight();
		}
		// save only in non-flight case
		else
			player->SaveRecallPosition();

		player->TeleportTo(sVIP->MALL[team_id].map_id, sVIP->MALL[team_id].x, sVIP->MALL[team_id].y, sVIP->MALL[team_id].z, sVIP->MALL[team_id].o);
		return true;
	}

	static bool HandleChangeRaceCommand(ChatHandler* handler, const char* args)
	{
		Player* player = handler->GetSession()->GetPlayer();
		player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
		handler->PSendSysMessage("Relog to change race of your character.");
		return true;
	}

	static bool HandleChangeFactionCommand(ChatHandler* handler, const char* args)
	{
		Player* player = handler->GetSession()->GetPlayer();
		player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
		handler->PSendSysMessage("Relog to change faction of your character.");
		return true;
	}

	static bool HandleCustomizeCommand(ChatHandler* handler, const char* args)
	{
		Player* player = handler->GetSession()->GetPlayer();
		player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
		handler->PSendSysMessage("Relog to customize your character.");
		return true;
	}

	static bool HandleScaleCommand(ChatHandler* handler, const char* args)
	{
		if (!*args)
			return false;

		Player* player = handler->GetSession()->GetPlayer();

		float Scale = (float)atof((char*)args);

		if (Scale > 10.0f || Scale < 0.1f)
		{
			handler->SendSysMessage(LANG_BAD_VALUE);
			handler->SetSentErrorMessage(true);
			return false;
		}

		player->SetObjectScale(Scale);

		return true;
	}

	static bool HandleHomeCommand(ChatHandler* handler, const char* args)
	{

		Player* player = handler->GetSession()->GetPlayer();

		auto team_id = player->GetTeamId();

		if (player->IsInCombat())
		{
			handler->SendSysMessage(LANG_YOU_IN_COMBAT);
			handler->SetSentErrorMessage(true);
			return false;
		}

		// stop flight if need
		if (player->IsInFlight())
		{
			player->GetMotionMaster()->Remove(EFFECT_MOTION_TYPE); // MovementExpired();
			player->CleanupAfterTaxiFlight();
		}
		// save only in non-flight case
		else
			player->SaveRecallPosition();

		player->TeleportTo(sVIP->HOME[team_id].map_id, sVIP->HOME[team_id].x, sVIP->HOME[team_id].y, sVIP->HOME[team_id].z, sVIP->HOME[team_id].o);
		return true;
	}

	static bool HandleRepairCommand(ChatHandler* handler, const char* args)
	{
		Player* player = handler->GetSession()->GetPlayer();

		if (!player->HasItemCount(sVIP->GetVIPCOINID(), 1, false))
		{
			handler->PSendSysMessage("You must have a %s to use this command.", sVIP->GetVIP_COIN_NAME().c_str());
			return false;
		}

		if (player->HasItemCount(sVIP->GetVIPCOINID(), 1, false))
		{
			player->DurabilityRepairAll(0, 0, false);
			handler->PSendSysMessage("Done.");
			return true;
		}
		return true;
	}

	static bool HandleMORPHCommand(ChatHandler* handler, const char* args)
	{
		Player* player = handler->GetSession()->GetPlayer();

		if (!*args)
			return false;

		uint16 display_id = (uint16)atoi((char*)args);

		player->SetDisplayId(display_id);

		return true;
	}

	static bool HandleDeMORPHCommand(ChatHandler* handler, const char* /*args*/)
	{
		handler->GetSession()->GetPlayer()->DeMorph();

		return true;
	}

	static bool HandleBuffCommand(ChatHandler* handler, const char* args)
	{
		Player* player = handler->GetSession()->GetPlayer();
		uint32 acct_id = handler->GetSession()->GetAccountId();
		uint8 Pvip = sVIP->GetPlayerVIP(acct_id);
		uint8 max_level = sVIP->GetVIPMAX();

		for (uint8 i = 0; i < (((sizeof(VIPBUFFS) / sizeof(*VIPBUFFS)) / max_level) * Pvip); i++)
		{
			player->AddAura(VIPBUFFS[i], player);
		}

		// player->SetMaxHealth(1);
		player->SetHealth(player->GetMaxHealth());

		return true;
	}

	static bool HandleVipSetHearthstoneCommand(ChatHandler* handler, const char* args)
	{

		Player* player = handler->GetSession()->GetPlayer();

		auto team_id = player->GetTeamId();

		if (player->IsInCombat())
		{
			handler->SendSysMessage(LANG_YOU_IN_COMBAT);
			handler->SetSentErrorMessage(true);
			return false;
		}

		// stop flight if need
		if (player->IsInFlight())
		{
			player->GetMotionMaster()->Remove(EFFECT_MOTION_TYPE); // MovementExpired();
			player->CleanupAfterTaxiFlight();
		}
		// save only in non-flight case
		else
			player->SaveRecallPosition();

		sVIP->SetHearthStone(player->GetGUID(), player->GetMapId(), player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetOrientation());
		handler->PSendSysMessage("%s, your location has been stored.", player->GetName().c_str());
		return true;
	}

	static bool HandleHearthStoneCommand(ChatHandler* handler, const char* args)
	{

		Player* player = handler->GetSession()->GetPlayer();

		uint32 guid = player->GetGUID();

		if (player->IsInCombat())
		{
			handler->SendSysMessage(LANG_YOU_IN_COMBAT);
			handler->SetSentErrorMessage(true);
			return false;
		}

		// stop flight if need
		if (player->IsInFlight())
		{
			player->GetMotionMaster()->Remove(EFFECT_MOTION_TYPE); // MovementExpired();
			player->CleanupAfterTaxiFlight();
		}

		if (sVIP->HearthStone[guid].guid != guid)
		{
			WorldDatabase.PExecute("REPLACE INTO hearthstone SET `guid`='%u';", guid);

			sVIP->SetHearthStone(guid, player->GetMapId(), player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetOrientation());

			handler->PSendSysMessage("You must store a location first to be able to use this command.");
			handler->PSendSysMessage("Default location is your current location.");
			return false;
		}

		if (sVIP->HearthStone[guid].guid == guid)
		{
			// save only in non-flight case and a location is stored
			player->SaveRecallPosition();

			player->TeleportTo(sVIP->HearthStone[guid].map_id, sVIP->HearthStone[guid].x, sVIP->HearthStone[guid].y, sVIP->HearthStone[guid].z, sVIP->HearthStone[guid].o);
			return true;
		}
		return true;
	}
};

class VIP_Coin_Script : public ItemScript
{
public: VIP_Coin_Script() : ItemScript("VIP_Coin_Script") { };

		virtual bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
		{
			uint32 acct_id = player->GetSession()->GetAccountId();
			uint8 pVip = sVIP->GetPlayerVIP(acct_id);
			uint32 pMg = sVIP->GetPlayerMG(acct_id);
			uint32 pVotes = sVIP->GetPlayerVOTES(acct_id);
			std::string Votes_Required_Ann;
			bool voting = sVIP->GetVIPVOTE_ENABLE();

			ChatHandler(player->GetSession()).PSendSysMessage("%s**********************************", green.c_str());
			ChatHandler(player->GetSession()).PSendSysMessage("%sYou are VIP:%s%u%s of %s%u.", green.c_str(), white.c_str(), pVip, green.c_str(), white.c_str(), sVIP->GetVIPMAX());
			ChatHandler(player->GetSession()).PSendSysMessage("%sYou have %s%u %smg's", green.c_str(), white.c_str(), pMg, green.c_str());
			ChatHandler(player->GetSession()).PSendSysMessage("%sYou recieve a %s%u%s %sstat increase.", green.c_str(), white.c_str(), uint8(sVIP->GetVIPOFFSET() * 100)*pVip, "%", green.c_str());
			ChatHandler(player->GetSession()).PSendSysMessage("%sYou have %s%u%s VIP Vote Points.", green.c_str(), white.c_str(), pVotes, green.c_str());
			ChatHandler(player->GetSession()).PSendSysMessage("%s**********************************", green.c_str());
			ChatHandler(player->GetSession()).PSendSysMessage("%s**********************************", green.c_str());

			return true;
		}
};

void RemoveItem(uint32 id, Player* player)
{
	player->DestroyItemCount(uint32(id), 1, true);

	ChatHandler(player->GetSession()).PSendSysMessage("%s+1 VIP.", green.c_str());
}

class VIP_Stone_Script : public ItemScript
{
public: VIP_Stone_Script() : ItemScript("VIP_Stone_Script") { };

		virtual bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
		{
			uint32 acct_id = player->GetSession()->GetAccountId();
			uint8 pVip = sVIP->GetPlayerVIP(acct_id);

			if (pVip >= sVIP->GetVIPMAX())
			{
				ChatHandler(player->GetSession()).PSendSysMessage("%sYou are allready the maximum VIP rank:%s%u.", red.c_str(), white.c_str(), sVIP->GetVIPMAX());

			}

			if (pVip < sVIP->GetVIPMAX())
			{
				RemoveItem(sVIP->GetVIPSTONEID(), player);

				sVIP->SetPlayerVIP(acct_id, pVip + 1);

				return true;
			}
			return true;
		}
};

class VIP_MG_BANKER : public CreatureScript
{
    public:
        VIP_MG_BANKER() : CreatureScript("VIP_MG_BANKER") { }

        class VS_VIP_MG_BANKERAI : public ScriptedAI
        {
        public:
            VS_VIP_MG_BANKERAI(Creature* creature) : ScriptedAI(creature) {}

            bool GossipHello(Player* player) override
            {
                return OnGossipHello(player, me);
            }

            static bool OnGossipHello(Player* player, Creature* creature)
            {

                uint32 accountId = player->GetSession()->GetAccountId();
                uint8 pVIP = sVIP->GetPlayerVIP(accountId);
                uint32 MG = sVIP->GetPlayerMG(accountId);
                uint32 itemId = sVIP->GetVIPMGID();
                uint32 pMg = player->GetItemCount(itemId);
                uint32 pVotes = sVIP->GetPlayerVOTES(accountId);
                std::string itemName = sObjectMgr->GetItemTemplate(itemId)->Name1;
                std::string currency_inBank;
                std::string deposit_amt;

                if (pMg == 1) { deposit_amt = "Total:" + ConvertNumberToString(pMg) + " " + itemName; };
                if (pMg == 0 || pMg > 1) { deposit_amt = "Total:" + ConvertNumberToString(pMg) + " " + itemName + "'s"; };

                std::string withdraw10 = "Withdraw 10 " + itemName + "'s. Fee:0 " + itemName + "'s.";
                std::string withdraw100 = "Withdraw 100 " + itemName + "'s. Fee:1 " + itemName + ".";
                std::string withdraw1000 = "Withdraw 1,000 " + itemName + "'s. Fee:10 " + itemName + "'s.";
                std::string withdraw10000 = "Withdraw 10,000 " + itemName + "'s. Fee:100 " + itemName + "'s.";
                std::string withdraw100000 = "Withdraw 100,000 " + itemName + "'s. Fee:1,000 " + itemName + "'s.";
                std::string rankup1 = "Rank up your VIP by using";
                std::string rankup2 = "your VIP vote points.";

                if (MG == 1)
                    currency_inBank = "Balance:" + ConvertNumberToString(MG) + " " + itemName;
                else
                {
                    currency_inBank = "Balance:" + ConvertNumberToString(MG) + " " + itemName + "'s.";
                };

                std::string current_VOTES = "Votes:" + ConvertNumberToString(pVotes);
                std::string current_VIP = "VIP:" + ConvertNumberToString(pVIP);

                if (pMg > 0)
                {
                    AddGossipItemFor(player, 10, "-----------------------", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);
                    AddGossipItemFor(player, 10, "-Deposit-", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);
                    AddGossipItemFor(player, 10, "-----------------------", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);
                    AddGossipItemFor(player, 10, "Deposit all my custom currency.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2001);
                    AddGossipItemFor(player, 10, deposit_amt.c_str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2001);
                    AddGossipItemFor(player, 10, "-----------------------", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);
                }

                if (MG >= 10)
                {
                    AddGossipItemFor(player, 10, "-----------------------", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);
                    AddGossipItemFor(player, 10, "-WithDrawl-", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);
                    AddGossipItemFor(player, 10, "-----------------------", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);
                    AddGossipItemFor(player, 10, withdraw10.c_str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2002);

                    if (MG >= 101) { AddGossipItemFor(player, 10, withdraw100.c_str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2003); };
                    if (MG >= 1010) { AddGossipItemFor(player, 10, withdraw1000.c_str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2004); };
                    if (MG >= 10100) { AddGossipItemFor(player, 10, withdraw10000.c_str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2005); };
                    if (MG >= 101000) { AddGossipItemFor(player, 10, withdraw100000.c_str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2006); };
                }

                if (sVIP->GetPlayerVIP(accountId) < sVIP->GetVIPMAX())
                {

                    if (sVIP->GetVIPTEST()) { TC_LOG_INFO("server.loading", "MG_BANKER::[MENU]Buy VIP Stone [CHECK]. PLAYER_VIP:%u MAX_VIP:%u", sVIP->GetPlayerVIP(accountId), sVIP->GetVIPMAX()); }

                    if (sVIP->GetVIPVOTE_ENABLE() && pVotes >= sVIP->GetVIPVOTECOUNT())
                    {
                        AddGossipItemFor(player, 10, "-----------------------", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);
                        AddGossipItemFor(player, 10, rankup1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);
                        AddGossipItemFor(player, 10, rankup2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);
                        AddGossipItemFor(player, 10, "         -Buy-         ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2007);
                        AddGossipItemFor(player, 10, "-----------------------", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);
                    }
               }

                AddGossipItemFor(player, 10, "-----------------------", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);
                AddGossipItemFor(player, 10, "-----------------------", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);
                AddGossipItemFor(player, 10, "-Bank Balance-", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);
                AddGossipItemFor(player, 10, currency_inBank.c_str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);
                AddGossipItemFor(player, 10, current_VOTES.c_str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);
                AddGossipItemFor(player, 10, current_VIP.c_str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);
                AddGossipItemFor(player, 10, "-----------------------", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2000);

                SendGossipMenuFor(player, 1, creature->GetGUID());

                return true;
            };

            bool GossipSelect(Player* player, uint32 /*menu_id*/, uint32 gossipListId) override
            {
                uint32 sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);
                uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
                return OnGossipSelect(player, me, sender, action);
            }

            static bool OnGossipSelect(Player* player, Creature* creature, uint32 /* sender */, uint32 actions)
            {
                if (sVIP->GetVIPTEST()) { TC_LOG_INFO("server.loading", "MG_BANKER::OnSelect :%u", actions); }

                uint32 accountId = player->GetSession()->GetAccountId();
                uint8 pVIP = sVIP->GetPlayerVIP(accountId);
                uint32 MG = sVIP->GetPlayerMG(accountId);
                uint32 itemId = sVIP->GetVIPMGID();
                uint32 vipitemid = sVIP->GetVIPSTONEID();
                uint32 pMg = player->GetItemCount(itemId);
                uint32 pVotes = sVIP->GetPlayerVOTES(accountId);
                uint32 vipvotecount = sVIP->GetVIPVOTECOUNT();

                switch (actions)
                {
                case GOSSIP_ACTION_INFO_DEF + 2000: // loopbacks

                    player->PlayerTalkClass->ClearMenus();

                    OnGossipHello(player, creature);
                    break;

                case GOSSIP_ACTION_INFO_DEF + 2001: // Deposit all

                    player->DestroyItemCount(itemId, pMg, true);

                    if (player->GetItemCount(itemId) == 0)
                    {
                        sVIP->SetPlayerMG(accountId, MG + pMg);
                    }

                    player->PlayerTalkClass->ClearMenus();

                    OnGossipHello(player, creature);
                    break;

                case GOSSIP_ACTION_INFO_DEF + 2002: // Withdraw 10

                    player->PlayerTalkClass->ClearMenus();

                    if (player->AddItem(itemId, 10))
                    {
                        sVIP->SetPlayerMG(accountId, MG - 10);
                    }

                case GOSSIP_ACTION_INFO_DEF + 2003: // Withdraw 100

                    player->PlayerTalkClass->ClearMenus();

                    if (player->AddItem(itemId, 100))
                    {
                        sVIP->SetPlayerMG(accountId, MG - 101);
                    }

                case GOSSIP_ACTION_INFO_DEF + 2004: // Withdraw 1,000
                    player->PlayerTalkClass->ClearMenus();

                    if (player->AddItem(itemId, 1000))
                    {
                        sVIP->SetPlayerMG(accountId, MG - 1010);
                    }

                case GOSSIP_ACTION_INFO_DEF + 2005: // Withdraw 10,000
                    player->PlayerTalkClass->ClearMenus();

                    if (player->AddItem(itemId, 10000))
                    {
                        sVIP->SetPlayerMG(accountId, MG - 10100);
                    }

                case GOSSIP_ACTION_INFO_DEF + 2006: // Withdraw 100,000
                    player->PlayerTalkClass->ClearMenus();

                    if (player->AddItem(itemId, 100000))
                    {
                        sVIP->SetPlayerMG(accountId, MG - 101000);
                    }

                case GOSSIP_ACTION_INFO_DEF + 2007: // trade VIP votes for Rank increase item
                    player->PlayerTalkClass->ClearMenus();

                    if (sVIP->GetPlayerVIP(accountId) < sVIP->GetVIPMAX())
                    {
                        if (player->AddItem(vipitemid, 1))
                        {
                            sVIP->SetPlayerVOTES(accountId, (pVotes - vipvotecount));
                        }
                    }
                    else
                    {
                        ChatHandler(player->GetSession()).PSendSysMessage("%sYou are allready the maximum VIP rank:%s%u%s and dont require an upgrade.", red.c_str(), white.c_str(), sVIP->GetVIPMAX(), red.c_str());
                    }

                    OnGossipHello(player, creature);
                    break;
                }
                return true;
            }
        };
        CreatureAI* GetAI(Creature* creature) const override
        {
            return new VS_VIP_MG_BANKERAI(creature);
        }
};

void AddSC_Grumboz_VIP_Core()
{
	new VIP_Load_Conf();
	new Grumboz_VIP_Account_Engine();
	new Grumboz_VIP_Player_Engine();
	new VIP_commands();
	new VIP_Coin_Script();
	new VIP_Stone_Script();
	new VIP_MG_BANKER();
}
