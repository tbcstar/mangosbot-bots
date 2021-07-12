DROP TABLE IF EXISTS `playerbot_rnditem_cache`;
CREATE TABLE `playerbot_rnditem_cache` (
  `id` INT(11) auto_increment,
  `lvl` INT(11) NOT NULL,
  `type` INT(11) NOT NULL,
  `item` INT(11) NOT NULL,
PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Playerbot Random Item Cache';
