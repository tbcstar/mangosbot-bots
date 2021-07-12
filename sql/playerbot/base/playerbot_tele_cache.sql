DROP TABLE IF EXISTS `playerbot_tele_cache`;
CREATE TABLE `playerbot_tele_cache` (
  `id` INT(11) auto_increment,
  `level` TINYINT(3) NOT NULL,
  `map_id` mediumint(8) NOT NULL,
  `x` float(8) NOT NULL,
  `y` float(8) NOT NULL,
  `z` float(8) NOT NULL,
PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Playerbot Tele Cache';
