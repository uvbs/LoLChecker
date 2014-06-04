#include "MainWindow.h"
#include "LolChecker.h"
#include <sstream>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w; w.show();
	return a.exec();
}

CLoLChecker LoLChecker;
CListIn *InList = nullptr;

int iSuccess = 0, iFailed = 0;

std::deque<CList::UserData> vListIn;
std::deque<CList::UserData> vListOut;

int iRegionIndex = 0;

std::vector<std::string> vRegions = 
	{ "na", "euw", "br", "eune", "lan", "tr", "oce", "las", "ru", "kr" };

/* class MainWindow */

MainWindow::~MainWindow() { }

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	ui.status_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	ui.region_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	ui.counter_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);	
	this->statusBar()->addPermanentWidget(ui.counter_label, 1);
	this->statusBar()->addPermanentWidget(ui.status_label, 6);
	this->statusBar()->addPermanentWidget(ui.region_label, 1);
	this->statusBar()->setSizeGripEnabled(false);
	ui.counter_label->setToolTip(QString("Success / Fail"));
	ui.region_label->setToolTip(QString("Region"));

	ui.captcha_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.captcha_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	
	this->setCaptcha(QImage(":/lol_checker/banner.png"));

	ui.button_save->setDisabled(true);
	ui.button_check->setDisabled(true);	
	ui.captcha_input->setDisabled(true);

	connect(ui.button_check, SIGNAL(clicked()), this, SLOT(on_Check_clicked()));
	connect(ui.button_list, SIGNAL(clicked()), this, SLOT(on_List_clicked()));	
	connect(ui.button_save, SIGNAL(clicked()), this, SLOT(on_Save_clicked()));
}

/* Methods */

bool MainWindow::saveResults()
{
	QString qstrListOut = QFileDialog::getSaveFileName(this, tr("Save results"), "", tr(".txt File (*.txt)"));

	CListOut OutList(qstrListOut.toStdString().c_str());
	
	if (OutList.WriteList(vListOut))
		return true;

	return false;
}

void MainWindow::setCaptcha(QImage image)
{
	QGraphicsScene *scene = new QGraphicsScene(ui.captcha_view);
	scene->setSceneRect(ui.captcha_view->rect());

	QPixmap pixmap(QPixmap::fromImage(image));
	scene->addPixmap(pixmap);

	ui.captcha_view->setScene(scene);
	ui.captcha_view->show();
	ui.captcha_input->clear();
}

void MainWindow::nextEntry()
{	
	if (vListIn.size() == 0)
	{
		vListIn = InList->GetChunk(2048);
			
		if (vListIn.size() == 0)
		{
			if (vListOut.size() > 0)
			{				
				MessageBoxA(0, "Okay. We're done so far. Save the results nao...", "", 0);

				if (!this->saveResults())
					MessageBoxA(0, "Couldn\'t save results.", "Error", 0);
			}
			else MessageBoxA(0, "Don't select shit, bro!", "", 0);

			ExitProcess(0);
		}		
	} 
	else vListIn.pop_front();

	std::string strMsg = std::string("Checking -> ")
		.append(vListIn.front().strUser).append(":").append(vListIn.front().strPass);

	ui.status_label->setText(QString(strMsg.c_str()));
}

/* Signals */

void MainWindow::on_Save_clicked()
{
	if (vListOut.size() > 0)
		this->saveResults();
}

void MainWindow::on_List_clicked()
{
	ui.button_list->setDisabled(true);	
	
	QString qstrListIn = QFileDialog::getOpenFileName(this, tr("Open list"), "", tr(".txt Files (*.txt)"));
	
	if (qstrListIn.size() == 0)
	{
		ui.button_list->setDisabled(false);
		return;
	}	
	
	InList = new CListIn(qstrListIn.toStdString().c_str());
	
	ui.button_check->setDisabled(false);
	ui.captcha_input->setDisabled(false);

	this->setCaptcha(QImage(LoLChecker.GetCaptcha().c_str()));	
	this->nextEntry();
}

void MainWindow::on_Check_clicked()
{
	ui.button_save->setDisabled(true);
	ui.button_check->setDisabled(true);

	LoLChecker.SetCaptcha(ui.captcha_input->text().toStdString());

	CLoLChecker::LoginResponse Response
		= LoLChecker.CheckLogin(vListIn.front(), vRegions.at(iRegionIndex));

	std::string strCaptcha = LoLChecker.GetCaptcha();

	if (Response.strSuccess == "true" || Response.strError == "Not Authorized." )
	{
		std::stringstream stream;

		if (Response.strError.size() == 0)
		{
			vListIn.front().strRegion = vRegions.at(iRegionIndex);
			vListOut.push_back(vListIn.front());

			iSuccess++;
			iRegionIndex = 0;

			stream << iSuccess << "/" << iFailed;
			ui.counter_label->setText(QString(stream.str().c_str()));			
			ui.region_label->setText(QString(vRegions.at(0).c_str()).toUpper());

			this->nextEntry();
		}
		else
		{
			if (iRegionIndex < vRegions.size())
			{
				iRegionIndex++;
				ui.region_label->setText(QString(vRegions.at(iRegionIndex).c_str()).toUpper());
			}
			else
			{
				iFailed++;
				
				stream << iSuccess << "/" << iFailed;
				ui.counter_label->setText(QString(stream.str().c_str()));
				
				this->nextEntry();
			}
		}
	}
	else ui.status_label->setText(QString(Response.strError.c_str()));
	
	this->setCaptcha(QImage(strCaptcha.c_str()));

	if(iSuccess > 0)
		ui.button_save->setDisabled(false);
	
	ui.button_check->setDisabled(false);
}