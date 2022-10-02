cmake_minimum_required(VERSION 3.19)
project(interface)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "/Users/kate/Qt/6.0.2/clang_64/lib/cmake")
set(QT_VERSION 6)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets)
find_package(oatpp REQUIRED)
find_package(oatpp-curl REQUIRED)
add_executable(${PROJECT_NAME} main.cpp
        GUI/Login/LoginViewController.cpp
        GUI/Registration/RegistrationController.cpp
        GUI/Registration/Admin/RegistrationAdminController.cpp
        GUI/Registration/Librarian/RegistrationLibrarianController.cpp
        GUI/Registration/Reader/RegistrationReaderController.cpp
        GUI/Main/Reader/ReaderMainPresenter.cpp
        GUI/Main/Admin/AdminMainPresenter.cpp
        GUI/Main/Librarain/LibrarianMainPresenter.cpp
        Model/Model.cpp Model/Model.h
        Model/Entities/Account/AdminAccount.cpp
        Model/Entities/Account/LibrarianAccount.cpp
        Model/Entities/Account/ReaderAccount.cpp
        Model/Entities/Library/Library.cpp
        Model/Entities/Book/Book.cpp
        Model/Entities/Account/Account.cpp
        GUI/Main/Admin/AdminMainView.ui
        GUI/Main/Librarain/LibrarianMainView.ui
        GUI/Main/Reader/ReaderMainView.ui
        GUI/Registration/Admin/RegistrationAdminView.ui
        GUI/Registration/Reader/RegistrationReaderView.ui
        GUI/Registration/Librarian/RegistrationLibrarianView.ui
        GUI/Registration/RegistrationView.ui
        GUI/Login/LoginView.ui
        ConsoleUI/ConsolePresenter.cpp ConsoleUI/ConsolePresenter.h ConsoleUI/ConsoleView.cpp ConsoleUI/ConsoleView.h Model/Entities/EBook/EBook.cpp Model/Entities/EBook/EBook.h)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED} oatpp::oatpp oatpp::oatpp-curl)
