-- Add these coulmns to your world.items_template DB

ALTER TABLE `item_template`
	ADD COLUMN `vip` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1' AFTER `VerifiedBuild`,
