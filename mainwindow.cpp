#include <QDebug>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stylesheetblockwidget.h"
#include "cssblock.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mCssBlocks.resize(6);

    QStringList names;
    names << "QPushButton"
          << "QPushButton:hover"
          << "QPushButton:pressed"
          << "QPushButton:focus"
          << "QPushButton:checked"
          << "QPushButton:disabled";

    QString tabName;
    for (QStringList::const_iterator it = names.begin(); it != names.end(); ++it)
    {
        StyleSheetBlockWidget* w = new StyleSheetBlockWidget;
        w->setBlockName(*it);

        int index = it->indexOf(':');
        if (-1 != index)
        {
            tabName = it->mid(index + 1);
        }
        else
        {
            tabName = "normal";
        }
        ui->tabWidget->addTab(w, tabName);

        connect(w, SIGNAL(styleSheetChanged(QWidget*,QString)), this, SLOT(updateStyleSheet(QWidget*,QString)));
    }

    connect(ui->menuCreateQPushButton, SIGNAL(triggered(bool)), this, SLOT(onSetStackWidgetToQPushBtn()));
    connect(ui->menuCreateQToolButton3State, SIGNAL(triggered(bool)), this, SLOT(onSetStackWidgetToQToolBtn()));
    connect(ui->btnReadImg, SIGNAL(clicked(bool)), this, SLOT(onClickedOpenImg()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSetStackWidgetToQPushBtn()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::onSetStackWidgetToQToolBtn()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void makeBtnToFlat(const QString& imgPath, QToolButton* btn)
{
    QStringList qss;
    qss.append(QString("QToolButton{border-style:none;background:url(%1);background-position:left;}").arg(imgPath));
    qss.append(QString("QToolButton:hover{border-style:none;background:url(%1);background-position:center;}").arg(imgPath));
    qss.append(QString("QToolButton:pressed{border-style:none;background:url(%1);background-position:right;}").arg(imgPath));
    btn->setStyleSheet(qss.join(""));
}

void MainWindow::onClickedOpenImg()
{
    QString filePath = QFileDialog::getOpenFileName(
                this,
                "打开文件",
                "",
                "Image(*.png;*.jpg)"
                );
    if (filePath.isNull())
    {
        return;
    }

    QPixmap pixmap(filePath);
    ui->imgPreview->setPixmap(pixmap);

    CssBlock* normal = new CssBlock("QToolButton");
    normal->addParam("border-style", "none");
    normal->addParam("min-width", pixmap.width() / 3, "px");
    normal->addParam("min-height", pixmap.height(), "px");
    normal->addParam("max-width", pixmap.width() / 3, "px");
    normal->addParam("max-height", pixmap.height(), "px");
    normal->addParam("background", QString("url(%1)").arg(filePath));
    normal->addParam("background-position", "left");

    CssBlock* hover = new CssBlock("QToolButton:hover");
    hover->addParam("border-style", "none");
    hover->addParam("background", QString("url(%1)").arg(filePath));
    hover->addParam("background-position", "center");

    CssBlock* pressed = new CssBlock("QToolButton:pressed");
    pressed->addParam("border-style", "none");
    pressed->addParam("background", QString("url(%1)").arg(filePath));
    pressed->addParam("background-position", "right");

    QString ss = normal->toString() + hover->toString() + pressed->toString();
    ui->toolButtonDemo->setStyleSheet(ss);
    ui->textBrowserForToolBtn->setText(ss);
}

void MainWindow::updateStyleSheet(QWidget* w, const QString& styleSheet)
{
    StyleSheetBlockWidget* blockWidget = (StyleSheetBlockWidget*)w;
    if (blockWidget)
    {
        QString name = blockWidget->getBlockName();
        if (0 == name.compare("QPushButton"))
        {
            updateStyleSheetNormal(styleSheet);
        }
        else if (0 == name.compare("QPushButton:hover"))
        {
            updateStyleSheetHover(styleSheet);
        }
        else if (0 == name.compare("QPushButton:pressed"))
        {
            updateStyleSheetPressed(styleSheet);
        }
        else if (0 == name.compare("QPushButton:focus"))
        {
            updateStyleSheetFocus(styleSheet);
        }
        else if (0 == name.compare("QPushButton:checked"))
        {
            updateStyleSheetChecked(styleSheet);
        }
        else if (0 == name.compare("QPushButton:disabled"))
        {
            updateStyleSheetDisabled(styleSheet);
        }
    }


    QString sum;
    for (QVector<QString>::const_iterator it = mCssBlocks.begin(); it != mCssBlocks.end(); ++it)
    {
        sum += *it;
    }

    ui->textBrowser->setText(sum);
    ui->demoBtn1->setStyleSheet(sum);
    ui->demoBtn2->setStyleSheet(sum);
    ui->demoBtn3->setStyleSheet(sum);
}

void MainWindow::updateStyleSheetNormal(const QString& styleSheet)
{
    mCssBlocks[INDEX_NORMAL] = styleSheet;
}

void MainWindow::updateStyleSheetHover(const QString& styleSheet)
{
    mCssBlocks[INDEX_HOVER] = styleSheet;
}

void MainWindow::updateStyleSheetPressed(const QString& styleSheet)
{
    mCssBlocks[INDEX_PRESSED] = styleSheet;
}

void MainWindow::updateStyleSheetFocus(const QString& styleSheet)
{
    mCssBlocks[INDEX_FOCUS] = styleSheet;
}

void MainWindow::updateStyleSheetChecked(const QString& styleSheet)
{
    mCssBlocks[INDEX_CHECKED] = styleSheet;
}

void MainWindow::updateStyleSheetDisabled(const QString& styleSheet)
{
    mCssBlocks[INDEX_DISABLED] = styleSheet;
}
