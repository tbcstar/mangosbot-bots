#
# Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
#

set(PUBLIC_INCLUDES
    ${PUBLIC_INCLUDES}
    ${CMAKE_MOD_PLAYERBOTS_DIR}/src
)

target_include_directories(game-interface
  INTERFACE
    ${PUBLIC_INCLUDES})

add_dependencies(game playerbots)

target_link_libraries(game
  PUBLIC
    playerbots)