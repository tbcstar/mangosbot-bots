#
# Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
#

# Add scripts in project
AC_ADD_SCRIPTS("${CMAKE_CURRENT_LIST_DIR}/src/")

# Add scripts to script loader
# AC_ADD_SCRIPT_LOADER("MyModule" "${CMAKE_CURRENT_LIST_DIR}/src/my_module_loader.h")

# Add config file
AC_ADD_CONFIG_FILE("${CMAKE_CURRENT_LIST_DIR}/conf/players_bot.conf.dist")
