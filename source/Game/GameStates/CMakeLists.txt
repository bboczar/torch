# Subdirs
add_subdirectory(GamePlay)
add_subdirectory(MainMenu)

set(SOURCES
    ${SOURCES}
    source/Game/GameStates/GamePlayState.cpp
    source/Game/GameStates/MainMenuState.cpp
    PARENT_SCOPE
)