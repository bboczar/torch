add_subdirectory(Map)
add_subdirectory(Wave)

set(SOURCES
    ${SOURCES}
    source/Game/GameStates/GamePlay/GamePlay.cpp
    source/Game/GameStates/GamePlay/Tower.cpp
    PARENT_SCOPE
)