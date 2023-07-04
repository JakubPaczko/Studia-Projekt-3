cmake_minimum_required(VERSION 3.11)
project(Rogalik)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_compile_options(-Wall -Wextra)

# ustawienia SFML-a dla Linuksa/MacOS i Windows - proszę zostawić obie konfiguracje,
# CMake automatycznie użyje właściwej
if (UNIX)
    # konfiguracja dla systemów Unix/Linux/MacOS
    # proszę nie modyfkować pierwszego wpisu, można dopisać kolejne katalogi
    # wpis dla antycznego Ubuntu (dla SFML 2.4)
    set ( CMAKE_MODULES_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULES_PATH})

    # katalog, w którym jest plik SFMLConfig.cmake
    # nowe Ubuntu (SFML 2.5)
    # NIE ZMIENIAĆ, NIE KASOWAĆ !!!
    set ( CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/SFML" ${CMAKE_PREFIX_PATH})

    # dla MacOS lub innej dystrybucji Linuksa - można dopisać DODATKOWY CMAKE_PREFIX_PATH
    # set ( CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/SFML" ${CMAKE_PREFIX_PATH})
endif(UNIX)

if (WIN32)
    # próbujemy linkować statycznie (nie trzeba kopiować plików dll do katalogu projektu)
    set( SFML_STATIC_LIBRARIES TRUE )

    # Jeśli zainstalowaliście w innym miejscu to trzeba tu zmienić katalog na właściwy
    set ( SFML_DIR "C:/SFML-2.6.0/lib/cmake/SFML/")
endif(WIN32)

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)

add_executable(Rogalik main.cpp RGmap.cpp RGmap.h Entity/Player.h Entity/Player.cpp Game.h Game.cpp GameDisplay.h GameDisplay.cpp Entity/Projectile.cpp Entity/Projectile.h Entity/Entity.cpp Entity/Entity.h Entity/EntityContainer.cpp Entity/EntityContainer.h Entity/Enemy.cpp Entity/Enemy.h Controller/PlayerController.cpp Controller/PlayerController.h GameManager.cpp GameManager.h Controller/EnemyController.cpp Controller/EnemyController.h Menu.cpp Menu.h Sound/SoundManager.cpp Sound/SoundManager.h)

target_link_libraries(Rogalik sfml-graphics sfml-audio)

#add_custom_command(
#        TARGET Rogalik POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        "${PROJECT_SOURCE_DIR}/leptonica/lib/liblept168.dll"
#        "$<TARGET_FILE_DIR:Rogalik>")