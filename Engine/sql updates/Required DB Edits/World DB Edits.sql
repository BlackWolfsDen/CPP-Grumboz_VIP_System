-- Add these tables to your World DB
-- Hearthstone gps table

CREATE TABLE IF NOT EXISTS `hearthstone` (
  `guid` mediumint(9) NOT NULL,
  `map_id` mediumint(9) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `o` float NOT NULL,
  PRIMARY KEY (`guid`),
  UNIQUE KEY `guid` (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
