
add_executable(${PROJECT_NAME}
    main.cpp
    StateManager.cpp
    MainMenu.cpp
    AssetManager.cpp
    Context.cpp
    Game.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
)