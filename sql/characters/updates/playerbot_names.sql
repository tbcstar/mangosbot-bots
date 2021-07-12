DROP TABLE IF EXISTS `playerbot_names`;
CREATE TABLE `playerbot_names` (
  `name_id` INT(11) NOT NULL UNIQUE,
  `name` varchar(255) NOT NULL,
  `gender` tinyint(3) unsigned NOT NULL,
PRIMARY KEY (`name_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Playerbot RandomBot names';

LOAD DATA LOCAL INFILE './characters_ai_playerbot_names.csv' INTO TABLE `playerbot_names` FIELDS TERMINATED BY ';';

DELETE FROM `playerbot_names` WHERE LENGTH(`name`) > 12;
ALTER TABLE `playerbot_names` MODIFY `name` varchar(12);
