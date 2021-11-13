add_subdirectory(Wave)

set(SOURCES
    ${SOURCES}
    source/Game/GameStates/GamePlay/Background.cpp
    source/Game/GameStates/GamePlay/GamePlay.cpp
    source/Game/GameStates/GamePlay/Map.cpp
    source/Game/GameStates/GamePlay/MapConfig.cpp
    source/Game/GameStates/GamePlay/Tower.cpp
    PARENT_SCOPE
)