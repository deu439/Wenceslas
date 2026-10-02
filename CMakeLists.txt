cmake_minimum_required(VERSION 3.5)
project(Wenceslas)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set (CMAKE_CXX_FLAGS "-Wall")

# Find the QtWidgets library
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

# 3. Find Poppler-Qt5 using PkgConfig
find_package(PkgConfig REQUIRED)
pkg_check_modules(POPPLER_QT5 REQUIRED IMPORTED_TARGET poppler-qt5)

set(wenceslasii_SRC
  src/main_wenceslasii.cpp
  src/wenceslasii.cpp
  src/mytablemodelii.cpp
  src/mycategories.cpp
  src/mygenderitemdelegate.cpp
  src/mytimeitemdelegate.cpp
  src/spinboxdelegate.cpp
  src/mysortfilterproxymodel.cpp
  #src/evaltablemodel.cpp
  src/evaltablemodelii.cpp
  src/noteditabledelegate.cpp
  src/resultsupload.cpp
  src/uploadresultsdialog.cpp
  src/printingwindow.cpp
  src/joinproxymodel.cpp
  src/statusled.cpp
)

# Create code from a list of Qt designer ui files.
#set(CMAKE_AUTOUIC ON) # use this if you have CMake 3.x instead of the following
qt5_wrap_ui(wenceslasii_SRC src/wenceslasii.ui src/printingwindow.ui)

# Tell CMake to create the helloworld executable
add_executable(wenceslasii ${wenceslasii_SRC} resources.qrc)
target_include_directories(wenceslasii PRIVATE src)

# Use the Widgets module from Qt 5.
target_link_libraries(wenceslasii Qt5::Widgets Qt5::Sql Qt5::Network Qt5::PrintSupport PkgConfig::POPPLER_QT5)

# Install the executable
install(TARGETS wenceslasii DESTINATION bin)
