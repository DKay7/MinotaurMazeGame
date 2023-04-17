
add_executable(${PROJECT_NAME}
    main.cpp
    StateManager.cpp
    Button.cpp
    MainMenu.cpp
    GamePlay.cpp
    AssetManager.cpp
    Context.cpp
    Game.cpp
    TextBox.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
)