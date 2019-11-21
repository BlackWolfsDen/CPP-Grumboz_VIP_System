REPLACE INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `BuyCount`, `SellPrice`, `InventoryType`, `ItemLevel`, `maxcount`, `stackable`, `BagFamily`, `VerifiedBuild`, `description`) VALUES 
(44209, 10, 0, -1, 'Magic Gold', 32282, 1, 64, 1, 0, 0, 0, 0, 2147483647, 8192, 12340, 'custom currency earned all over');

REPLACE INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `maxcount`, `stackable`, `ContainerSlots`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmRate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `bonding`, `description`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `ScriptName`) VALUES 
(63020, 15, 0, -1, 'VIP Coin', 32282, 1, 64, 0, 1, 0, 0, 0, -1, -1, 1, 1, 1, 0, 13567, 0, 0, 0, -1, 0, -1, 1, 'A MUST HAVE item for all your VIP needs.', 0, 0, 0, 0, 0, 'VIP_Coin_Script'),
(63021, 15, 0, -1, 'VIP Stone', 32282, 1, 64, 0, 1, 0, 0, 0, -1, -1, 1, 1, 1, 0, 13567, 0, 0, 0, -1, 0, -1, 1, '!!Wooooohooooooo!!\r\n!!ClickMe!!!ClickMe!!\r\n!!VIP+1!!SuperFun!!', 0, 1, 0, 0, 0, 'VIP_Stone_Script');

REPLACE INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `AIName`, `ScriptName`) VALUES 
(50001, 31048, 'World Trades Banker', 'Custom Banking', 'Buy', 0, 80, 80, 0, 35, 1, 1, 1.14286, 3.5, '', 'VIP_MG_BANKER');
