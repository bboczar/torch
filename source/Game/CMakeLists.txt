# Subdirs
add_subdirectory(GameStates)
add_subdirectory(Traits)

# Sources
set(SOURCES
   ${SOURCES}
   source/Game/Game.cpp
   PARENT_SCOPE
)