#
# Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
#

add_subdirectory(${CMAKE_MOD_PLAYERBOTS_DIR}/src)

add_definitions(-DPLAYERBOTS)

CU_ADD_HOOK(AFTER_GAME_LIBRARY "${CMAKE_MOD_PLAYERBOTS_DIR}/cmake/after_gs_install.cmake")

AC_ADD_SCRIPT_LOADER("Playerbots" "${CMAKE_MOD_PLAYERBOTS_DIR}/loader.h")

AC_ADD_CONFIG_FILE("${CMAKE_MOD_PLAYERBOTS_DIR}/conf/playerbots.conf.dist")
