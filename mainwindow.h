#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QApplication>
#include <QtWidgets/QMainWindow>


#include <QtCharts/QChartView>


#include <QtCharts/QBarSeries>


#include <QtCharts/QBarSet>


#include <QtCharts/QLegend>


#include <QtCharts/QBarCategoryAxis>

#include <QtCharts/QHorizontalStackedBarSeries>

#include <QtCharts/QLineSeries>

#include <QtCharts/QCategoryAxis>



#include "tabelmodel.h"
#include "food.h"
#include "mproxy.h"
#include "maska.h"
#include "checkboxdelegate.h"
#include "about.h"
QT_CHARTS_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QActionGroup;

class MainWindow : public QMainWindow
{
    /**
     * @brief Класс главного окна
     *
     * Данный класс описывает интерфейс для работы с главным окном программы
     */
    Q_OBJECT
class Shop : public QMainWindow
{

};

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void switchLanguage(QAction *action);

    void on_actionDelite_triggered();

    void on_actionAdd_triggered();

    void on_actionSaveAs_triggered();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_actionAthor_triggered();

    void on_actionnew_window_triggered();

    void on_actionCharts_triggered();

private:
    Ui::MainWindow *ui;

    QString normFileName;

    QTranslator appTranslator;
    QTranslator qtTranslator;

    QActionGroup *languageActionGrup;

    QString qmPath;

    void newFile();
    bool saveAs();
    void createLanguageMenu();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void readSettings();
    void writeSettings();

    TabelModel *TabelModelP;

    MProxy *mProxy;

};
#endif // MAINWINDOW_H
