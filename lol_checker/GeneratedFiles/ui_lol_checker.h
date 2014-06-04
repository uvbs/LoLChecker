/********************************************************************************
** Form generated from reading UI file 'lol_checker.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOL_CHECKER_H
#define UI_LOL_CHECKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *captcha_input;
    QLabel *counter_label;
    QPushButton *button_check;
    QGraphicsView *captcha_view;
    QLabel *status_label;
    QPushButton *button_list;
    QLabel *region_label;
    QPushButton *button_save;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(361, 171);
        MainWindow->setMinimumSize(QSize(361, 171));
        MainWindow->setMaximumSize(QSize(361, 171));
        MainWindow->setAcceptDrops(true);
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        MainWindow->setAnimated(false);
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setAcceptDrops(false);
        captcha_input = new QLineEdit(centralwidget);
        captcha_input->setObjectName(QStringLiteral("captcha_input"));
        captcha_input->setGeometry(QRect(10, 80, 341, 20));
        captcha_input->setAlignment(Qt::AlignCenter);
        captcha_input->setDragEnabled(true);
        counter_label = new QLabel(centralwidget);
        counter_label->setObjectName(QStringLiteral("counter_label"));
        counter_label->setEnabled(true);
        counter_label->setGeometry(QRect(20, 150, 16, 16));
        counter_label->setLayoutDirection(Qt::LeftToRight);
        counter_label->setAlignment(Qt::AlignCenter);
        counter_label->setWordWrap(false);
        button_check = new QPushButton(centralwidget);
        button_check->setObjectName(QStringLiteral("button_check"));
        button_check->setGeometry(QRect(110, 110, 131, 31));
        button_check->setAutoDefault(true);
        button_check->setDefault(true);
        captcha_view = new QGraphicsView(centralwidget);
        captcha_view->setObjectName(QStringLiteral("captcha_view"));
        captcha_view->setGeometry(QRect(10, 10, 341, 61));
        captcha_view->setMinimumSize(QSize(341, 61));
        captcha_view->setMaximumSize(QSize(341, 61));
        status_label = new QLabel(centralwidget);
        status_label->setObjectName(QStringLiteral("status_label"));
        status_label->setEnabled(true);
        status_label->setGeometry(QRect(60, 150, 16, 16));
        status_label->setLayoutDirection(Qt::LeftToRight);
        status_label->setAlignment(Qt::AlignCenter);
        status_label->setWordWrap(false);
        button_list = new QPushButton(centralwidget);
        button_list->setObjectName(QStringLiteral("button_list"));
        button_list->setGeometry(QRect(10, 110, 81, 31));
        region_label = new QLabel(centralwidget);
        region_label->setObjectName(QStringLiteral("region_label"));
        region_label->setEnabled(true);
        region_label->setGeometry(QRect(100, 150, 16, 16));
        region_label->setLayoutDirection(Qt::LeftToRight);
        region_label->setAlignment(Qt::AlignCenter);
        region_label->setWordWrap(false);
        button_save = new QPushButton(centralwidget);
        button_save->setObjectName(QStringLiteral("button_save"));
        button_save->setGeometry(QRect(260, 110, 91, 31));
        MainWindow->setCentralWidget(centralwidget);
        QWidget::setTabOrder(button_check, captcha_input);
        QWidget::setTabOrder(captcha_input, captcha_view);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "LoLChecker bY S3RB31 - priv8 t00l xD", 0));
        captcha_input->setText(QString());
        counter_label->setText(QApplication::translate("MainWindow", "0/0", 0));
        button_check->setText(QApplication::translate("MainWindow", "Check", 0));
        status_label->setText(QApplication::translate("MainWindow", "Select list ...", 0));
        button_list->setText(QApplication::translate("MainWindow", "Select list ...", 0));
        region_label->setText(QApplication::translate("MainWindow", "NA", 0));
        button_save->setText(QApplication::translate("MainWindow", "Save results ...", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOL_CHECKER_H
