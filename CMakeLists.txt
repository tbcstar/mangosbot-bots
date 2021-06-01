#
# Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
#

CU_SET_PATH("CMAKE_MOD_PLAYERBOTS_DIR" "${CMAKE_CURRENT_LIST_DIR}")
CU_ADD_HOOK(AFTER_LOAD_CMAKE_MODULES "${CMAKE_CURRENT_LIST_DIR}/cmake/after_load_cmake_modules.cmake")
