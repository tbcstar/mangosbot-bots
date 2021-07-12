DROP TABLE IF EXISTS `playerbot_rarity_cache`;
CREATE TABLE `playerbot_rarity_cache` (
  `id` INT(11) auto_increment,
  `item` INT(11) NOT NULL,
  `rarity` float NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Playerbot Rarity Cache';
