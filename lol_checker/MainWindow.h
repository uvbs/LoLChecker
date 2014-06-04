#ifndef LOL_CHECKER_H
#define LOL_CHECKER_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QGraphicsPixmapItem>

#include "ui_lol_checker.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	bool saveResults();
	void setCaptcha(QImage image);
	void nextEntry();

private slots:
	void on_Check_clicked();
	void on_Save_clicked();
	void on_List_clicked();

private:
	Ui::MainWindow ui;
};

#endif // LOL_CHECKER_H
