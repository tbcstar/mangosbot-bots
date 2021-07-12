DROP TABLE IF EXISTS `playerbot_equip_cache`;
CREATE TABLE `playerbot_equip_cache` (
  `id` INT(11) auto_increment,
  `clazz` TINYINT(3) NOT NULL,
  `lvl` INT(11) NOT NULL,
  `slot` TINYINT(8) NOT NULL,
  `quality` INT(11) NOT NULL,
  `item` INT(11) NOT NULL,
PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Playerbot equip Cache';
