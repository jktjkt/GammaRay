include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/3rdparty
)

add_subdirectory(actioninspector)
add_subdirectory(objectvisualizer)

if(QT_QTSCRIPTTOOLS_FOUND OR Qt5ScriptTools_FOUND)
  add_subdirectory(scriptenginedebugger)
endif()

add_subdirectory(statemachineviewer)
add_subdirectory(timertop)
add_subdirectory(kjobtracker)

if(QT_QTWEBKIT_FOUND OR Qt5WebKit_FOUND)
  add_subdirectory(webinspector)
endif()
