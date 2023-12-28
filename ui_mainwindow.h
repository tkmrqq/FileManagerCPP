/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *closeButton;
    QPushButton *maximizeButton;
    QPushButton *minimizeButton;
    QVBoxLayout *favLayout;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *Favourites;
    QPushButton *Desktop;
    QPushButton *Downloads;
    QPushButton *Docs;
    QPushButton *Music;
    QPushButton *Video;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *layout;
    QLabel *Locations;
    QPushButton *Disk1;
    QPushButton *Disk2;
    QPushButton *Disk3;
    QVBoxLayout *verticalLayout_4;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *backButton;
    QPushButton *nextButton;
    QSpacerItem *horizontalSpacer;
    QLabel *pathLabel;
    QPushButton *searchButton;
    QPushButton *themeButton;
    QFrame *foldersFrame;
    QHBoxLayout *horizontalLayout_4;
    QScrollArea *scrollArea;
    QWidget *folderWidget;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1280, 720);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMaximumSize(QSize(3840, 2560));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(34, 34, 34, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(51, 51, 51, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(42, 42, 42, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(17, 17, 17, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(22, 22, 22, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush6(QColor(0, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush4);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        QBrush brush8(QColor(255, 255, 255, 128));
        brush8.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush8);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush8);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush8);
#endif
        MainWindow->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("Inter"));
        font.setPointSize(10);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/windowIcon/Resources/Icons/windowIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("border-radius: 30% 30% 30% 30%\n"
""));
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("QFrame#frame {\n"
"background-color: rgb(21,21,21);\n"
"}\n"
"\n"
"QFrame{\n"
"background-color: transparent;\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame_3 = new QFrame(frame);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setEnabled(true);
        frame_3->setStyleSheet(QString::fromUtf8("background-color: transparent;"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        closeButton = new QPushButton(frame_3);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(closeButton->sizePolicy().hasHeightForWidth());
        closeButton->setSizePolicy(sizePolicy1);
        closeButton->setCursor(QCursor(Qt::ArrowCursor));
        closeButton->setAcceptDrops(false);
        closeButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/windowIcon/Resources/Icons/close.svg"), QSize(), QIcon::Normal, QIcon::Off);
        closeButton->setIcon(icon1);
        closeButton->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(closeButton);

        maximizeButton = new QPushButton(frame_3);
        maximizeButton->setObjectName(QString::fromUtf8("maximizeButton"));
        maximizeButton->setEnabled(true);
        maximizeButton->setCursor(QCursor(Qt::ArrowCursor));
        maximizeButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/windowIcon/Resources/Icons/maximize.svg"), QSize(), QIcon::Normal, QIcon::Off);
        maximizeButton->setIcon(icon2);
        maximizeButton->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(maximizeButton);

        minimizeButton = new QPushButton(frame_3);
        minimizeButton->setObjectName(QString::fromUtf8("minimizeButton"));
        minimizeButton->setEnabled(true);
        minimizeButton->setStyleSheet(QString::fromUtf8(""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/windowIcon/Resources/Icons/minimize.svg"), QSize(), QIcon::Normal, QIcon::Off);
        minimizeButton->setIcon(icon3);
        minimizeButton->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(minimizeButton);


        verticalLayout->addWidget(frame_3, 0, Qt::AlignLeft|Qt::AlignTop);

        favLayout = new QVBoxLayout();
        favLayout->setSpacing(0);
        favLayout->setObjectName(QString::fromUtf8("favLayout"));

        verticalLayout->addLayout(favLayout);

        frame_4 = new QFrame(frame);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: \"transparent\";\n"
"	color: white;\n"
"	text-align: left;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"	color: gray;\n"
"}\n"
"\n"
"QLabel{\n"
"	color: white;\n"
"}"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_4);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(10, 0, 0, 0);
        Favourites = new QLabel(frame_4);
        Favourites->setObjectName(QString::fromUtf8("Favourites"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Inter"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        Favourites->setFont(font1);
        Favourites->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_2->addWidget(Favourites);

        Desktop = new QPushButton(frame_4);
        Desktop->setObjectName(QString::fromUtf8("Desktop"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Inter Medium"));
        font2.setPointSize(8);
        Desktop->setFont(font2);
        Desktop->setStyleSheet(QString::fromUtf8(""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/windowIcon/Resources/Icons/desktop.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Desktop->setIcon(icon4);

        verticalLayout_2->addWidget(Desktop);

        Downloads = new QPushButton(frame_4);
        Downloads->setObjectName(QString::fromUtf8("Downloads"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Inter Medium"));
        Downloads->setFont(font3);
        Downloads->setLayoutDirection(Qt::LeftToRight);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/new/windowIcon/Resources/Icons/download.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Downloads->setIcon(icon5);

        verticalLayout_2->addWidget(Downloads);

        Docs = new QPushButton(frame_4);
        Docs->setObjectName(QString::fromUtf8("Docs"));
        Docs->setFont(font3);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/new/windowIcon/Resources/Icons/desc.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Docs->setIcon(icon6);

        verticalLayout_2->addWidget(Docs);

        Music = new QPushButton(frame_4);
        Music->setObjectName(QString::fromUtf8("Music"));
        Music->setFont(font3);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/new/windowIcon/Resources/Icons/music.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Music->setIcon(icon7);

        verticalLayout_2->addWidget(Music);

        Video = new QPushButton(frame_4);
        Video->setObjectName(QString::fromUtf8("Video"));
        Video->setFont(font3);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/new/windowIcon/Resources/Icons/video.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Video->setIcon(icon8);

        verticalLayout_2->addWidget(Video);


        verticalLayout->addWidget(frame_4, 0, Qt::AlignLeft);

        frame_5 = new QFrame(frame);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: \"transparent\";\n"
"	color: white;\n"
"	text-align: left;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"	color: gray;\n"
"}\n"
"\n"
"QLabel{\n"
"	color: white;\n"
"}"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_5);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(10, 0, 0, 40);
        layout = new QVBoxLayout();
        layout->setObjectName(QString::fromUtf8("layout"));
        Locations = new QLabel(frame_5);
        Locations->setObjectName(QString::fromUtf8("Locations"));
        Locations->setFont(font);

        layout->addWidget(Locations);

        Disk1 = new QPushButton(frame_5);
        Disk1->setObjectName(QString::fromUtf8("Disk1"));
        Disk1->setEnabled(true);
        Disk1->setFont(font3);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/new/windowIcon/Resources/Icons/hardDrive.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Disk1->setIcon(icon9);

        layout->addWidget(Disk1);

        Disk2 = new QPushButton(frame_5);
        Disk2->setObjectName(QString::fromUtf8("Disk2"));
        Disk2->setFont(font3);
        Disk2->setIcon(icon9);

        layout->addWidget(Disk2);

        Disk3 = new QPushButton(frame_5);
        Disk3->setObjectName(QString::fromUtf8("Disk3"));
        Disk3->setFont(font3);
        Disk3->setIcon(icon9);

        layout->addWidget(Disk3);


        verticalLayout_3->addLayout(layout);


        verticalLayout->addWidget(frame_5, 0, Qt::AlignLeft);

        verticalLayout->setStretch(1, 2);
        verticalLayout->setStretch(2, 2);
        verticalLayout->setStretch(3, 2);

        horizontalLayout->addWidget(frame);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetFixedSize);
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border-bottom: 1px solid #131313;\n"
"}\n"
"\n"
"QPushButton{\n"
"border: none;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"background-color: #131313;\n"
"border: 5px solid #131313;\n"
"border-radius: 5px;\n"
"width: 16px;\n"
"height: 16px;\n"
"}"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_2);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(16, 0, 0, 0);
        backButton = new QPushButton(frame_2);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/new/windowIcon/Resources/Icons/arrowBack.svg"), QSize(), QIcon::Normal, QIcon::Off);
        backButton->setIcon(icon10);
        backButton->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(backButton);

        nextButton = new QPushButton(frame_2);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/new/windowIcon/Resources/Icons/arrowForward.svg"), QSize(), QIcon::Normal, QIcon::Off);
        nextButton->setIcon(icon11);
        nextButton->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(nextButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pathLabel = new QLabel(frame_2);
        pathLabel->setObjectName(QString::fromUtf8("pathLabel"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Inter SemiBold"));
        font4.setPointSize(12);
        font4.setBold(true);
        font4.setWeight(75);
        pathLabel->setFont(font4);
        pathLabel->setStyleSheet(QString::fromUtf8("color: white;"));
        pathLabel->setFrameShape(QFrame::NoFrame);
        pathLabel->setText(QString::fromUtf8(""));

        horizontalLayout_3->addWidget(pathLabel);

        searchButton = new QPushButton(frame_2);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/new/windowIcon/Resources/Icons/search.svg"), QSize(), QIcon::Normal, QIcon::Off);
        searchButton->setIcon(icon12);
        searchButton->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(searchButton);

        themeButton = new QPushButton(frame_2);
        themeButton->setObjectName(QString::fromUtf8("themeButton"));
        themeButton->setStyleSheet(QString::fromUtf8("color: white;"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/new/windowIcon/Resources/Icons/light.svg"), QSize(), QIcon::Normal, QIcon::Off);
        themeButton->setIcon(icon13);
        themeButton->setIconSize(QSize(24, 24));

        horizontalLayout_3->addWidget(themeButton);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 1);
        horizontalLayout_3->setStretch(3, 40);

        verticalLayout_4->addWidget(frame_2);

        foldersFrame = new QFrame(centralwidget);
        foldersFrame->setObjectName(QString::fromUtf8("foldersFrame"));
        foldersFrame->setStyleSheet(QString::fromUtf8("border: 0;"));
        foldersFrame->setFrameShape(QFrame::StyledPanel);
        foldersFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(foldersFrame);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(foldersFrame);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setStyleSheet(QString::fromUtf8("QScrollBar:vertical {\n"
"           border: 2px solid grey;\n"
"            background: #32CC99;\n"
"            width: 15px;\n"
"            margin: 22px 0 22px 0;\n"
"        }\n"
"        QScrollBar::handle:vertical {\n"
"            background: white;\n"
"           min-height: 20px;\n"
"        }\n"
"        QScrollBar::add-line:vertical {\n"
"            border: 2px solid grey;\n"
"            background: #32CC99;\n"
"            height: 20px;\n"
"            subcontrol-position: bottom;\n"
"            subcontrol-origin: margin;\n"
"}\n"
"QScrollBar::sub-line:vertical {\n"
"            border: 2px solid grey;\n"
"            background: #32CC99;\n"
"            height: 20px;\n"
"            subcontrol-position: top;\n"
"            subcontrol-origin: margin;\n"
"        }"));
        scrollArea->setFrameShape(QFrame::StyledPanel);
        scrollArea->setFrameShadow(QFrame::Sunken);
        scrollArea->setWidgetResizable(true);
        folderWidget = new QWidget();
        folderWidget->setObjectName(QString::fromUtf8("folderWidget"));
        folderWidget->setGeometry(QRect(0, 0, 1118, 665));
        scrollArea->setWidget(folderWidget);

        horizontalLayout_4->addWidget(scrollArea);


        verticalLayout_4->addWidget(foldersFrame);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(1, 20);

        horizontalLayout->addLayout(verticalLayout_4);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 7);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1280, 20));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "FileManager", nullptr));
        closeButton->setText(QString());
        maximizeButton->setText(QString());
        minimizeButton->setText(QString());
        Favourites->setText(QCoreApplication::translate("MainWindow", "Favourites", nullptr));
        Desktop->setText(QCoreApplication::translate("MainWindow", "Desktop", nullptr));
        Downloads->setText(QCoreApplication::translate("MainWindow", "Downloads", nullptr));
        Docs->setText(QCoreApplication::translate("MainWindow", "Docs", nullptr));
        Music->setText(QCoreApplication::translate("MainWindow", "Music", nullptr));
        Video->setText(QCoreApplication::translate("MainWindow", "Video", nullptr));
        Locations->setText(QCoreApplication::translate("MainWindow", "Locations", nullptr));
        Disk1->setText(QCoreApplication::translate("MainWindow", "Disk 1", nullptr));
        Disk2->setText(QCoreApplication::translate("MainWindow", "Disk 2", nullptr));
        Disk3->setText(QCoreApplication::translate("MainWindow", "Disk 3", nullptr));
        backButton->setText(QString());
        nextButton->setText(QString());
        searchButton->setText(QString());
        themeButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
