-- Add these coulmns to your world.creature_template DB

ALTER TABLE `creature_template`
	ADD COLUMN `vip` TINYINT(1) UNSIGNED NOT NULL DEFAULT '1' AFTER `VerifiedBuild`;
	ADD COLUMN `mg` TINYINT(1) UNSIGNED NOT NULL DEFAULT '0' AFTER `vip`;
