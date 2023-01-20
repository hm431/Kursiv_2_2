#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QLibraryInfo>
#include <QTextStream>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , TabelModelP(new TabelModel(this))
    , mProxy(new MProxy(this))
{

    ui->setupUi(this);
    createLanguageMenu();
     readSettings();
    ui->tableView->setItemDelegateForColumn(1, new CheckBoxDelegate(ui->tableView));
    ui->tableView->setItemDelegateForColumn(3, new CheckBoxDelegate(ui->tableView));
    ui->tableView->setItemDelegateForColumn(6, new CheckBoxDelegate(ui->tableView));
    ui->tableView->setItemDelegate(new maska);
    mProxy->setSourceModel(TabelModelP);
    ui->tableView->setModel(mProxy);
    ui->tableView->setSortingEnabled(true);
    connect(ui->actionAboutQT, &QAction::triggered, qApp, &QApplication::aboutQt);

    connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::saveAs);

    qApp->installTranslator(&appTranslator);
    qApp->installTranslator(&qtTranslator);

    qmPath = qApp->applicationDirPath() + "/tr";
    createLanguageMenu();
     readSettings();

}

MainWindow::~MainWindow()
{


    writeSettings();
    delete ui;
}


void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this);
   if (!fileName.isEmpty())
       saveFile(fileName);
}


void MainWindow::on_actionOpen_triggered()
{

    QString fileName = QFileDialog::getOpenFileName(this);
   if (!fileName.isEmpty())
       loadFile(fileName);

}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,
                             "Application",
                             QString("Cannot read file %1:\n%2")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }
   QApplication::setOverrideCursor(Qt::WaitCursor);

    while (!file.atEnd())
    {

        QString str = file.readLine();

        QStringList lst = str.split(";");

        TabelModelP->insertValue(Food( lst.at(0),
                                       lst.at(1),
                                       lst.at(2),
                                       lst.at(3),
                                       lst.at(4),
                                       lst.at(5),
                                       lst.at(6),
                                       lst.at(7).toFloat()));

    }

    QApplication::restoreOverrideCursor();

    ui->tableView->resizeColumnsToContents();

    normFileName = fileName;
}

bool MainWindow::saveFile(const QString &normFileName)
{

     QFile file(normFileName);
     if (!file.open(QFile::WriteOnly | QFile::Text)) {
         QMessageBox::warning(this,
                              tr("Application"),
                              tr("Cannot write file %1:\n%2.")
                              .arg(normFileName).arg(file.errorString()));
         return false;
     }

     QTextStream out(&file);

     QString To_Save;
     int _colon = TabelModelP->columnCount();
     int _line =TabelModelP->rowCount();

     for (int i = 0; i < _line; i++)
     {
         for (int j = 0; j < _colon; j++)
         {
             To_Save += TabelModelP->data(TabelModelP->index(i,j),0).toString();
             To_Save += ";";
         }
     To_Save += "\n";
     }
     out << To_Save;
     file.close();

     QApplication::restoreOverrideCursor();



        return true;
}


void MainWindow::createLanguageMenu()
{
     languageActionGrup = new QActionGroup(this);

     connect(languageActionGrup, &QActionGroup::triggered, this, &MainWindow::switchLanguage);

     QDir dir(qmPath);

     QStringList fileNames = dir.entryList(QStringList("Kursov2_2_*.qm"));

     for (int i = 0; i < fileNames.size(); ++i)
     {
         QTranslator translaror;

         translaror.load(fileNames[i], qmPath);

         QString language = translaror.translate("MainWinow", "English");

         QAction *action = new QAction(tr("&%1 %2") .arg(i+1) .arg(language), this );

         QString locale = fileNames[i];

         locale.remove(0, locale.indexOf('_')+ 1 );
          locale.remove(0, locale.indexOf('_')+ 1 );

         locale.truncate(locale.lastIndexOf('.'));


         action->setData(locale);
         action->setCheckable(true);

         ui->menuLanguage->addAction(action);
         languageActionGrup->addAction(action);

         if (language == "English")
                action->setChecked(true);


     }

}



void MainWindow::switchLanguage(QAction *action)
{
    QString locale = action->data().toString();

    appTranslator.load("Kursov2_2_" + locale + ".qm", qmPath);


    locale.chop(3);
    qtTranslator.load("qt_" + locale,
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));

    ui->retranslateUi(this);
}




void MainWindow::on_actionDelite_triggered()
{
    bool ok;

           int iValue = QInputDialog::getInt(this,
                                             tr("Deleting a row"),

                                             tr("Number of the row to delete"),
                                             1,
                                             -10000,
                                             100000,
                                             1,
                                             &ok);
           if (ok)
               TabelModelP->removeRows(iValue, QModelIndex());
}



void MainWindow::on_actionAdd_triggered()
{
    int row = ui->tableView->model()->rowCount();
    int column = ui->tableView->model()->columnCount();
    QModelIndex modelIndex = TabelModelP->index(row, column);
    TabelModelP->insertRows(ui->tableView->currentIndex().row(), 1, modelIndex);
}

void MainWindow::newFile()
{
    MainWindow *mainWindow = new MainWindow;
     mainWindow->show();

}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                      tr("Save As"),
                                                      normFileName);
      if (fileName.isEmpty())
          return false;

      return saveFile(fileName);

}


void MainWindow::on_actionSaveAs_triggered()
{

}

void MainWindow::writeSettings()
{
    QSettings settings("Home","MyProgramm");
    settings.beginGroup("MainWindowGeometry");
    settings.setValue("size",size());
    settings.setValue("pos",pos());
    settings.setValue("language", languageActionGrup->checkedAction()->data().toString());
    settings.endGroup();
}
void MainWindow::readSettings()
{
    QSettings settings("Home","MyProgramm");
    settings.beginGroup("MainWindowGeometry");
    resize(settings.value("size", QSize(400, 500)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    QString our_language = settings.value("language", "ru_RU").toString();
    int i = 0;
    int count = languageActionGrup->actions().count();
         while(i < count){
            if(languageActionGrup->actions().at(i)->data().toString() == our_language){
                    switchLanguage(languageActionGrup->actions().at(i));
                    break;
            }
            i++;
        }
    settings.endGroup();
}
void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{

        QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(QRegExp::FixedString);
        QRegExp regExp(arg1, Qt::CaseInsensitive, syntax);

        int columnIndex = ui->comboBox->currentIndex();
        mProxy->setFilterKeyColumn(columnIndex);
        mProxy->setFilterRegExp(regExp);

}


void MainWindow::on_actionAthor_triggered()
{
    about about(this);
    about.exec();
}


void MainWindow::on_actionnew_window_triggered()
{
    MainWindow *mainWindow = new MainWindow;
     mainWindow->show();
}


void MainWindow::on_actionCharts_triggered()
{

    int row =TabelModelP->rowCount();
    QBarSeries *series = new QBarSeries();

    for (int i = 0; i < row; i++)
    {
       QBarSet *set = new QBarSet(TabelModelP->data(TabelModelP->index(i,0),0).toString());
       *set << TabelModelP->data(TabelModelP->index(i,7),0).toFloat();
       series->append(set);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Marks");
    chart->setAnimationOptions(QChart::AllAnimations);





    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xffffff));
    pal.setColor(QPalette::WindowText, QRgb(0xffffff));
    qApp->setPalette(pal);


    QMainWindow window;



    chartView->resize(800, 500);
    chartView->show();
}

