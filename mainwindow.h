#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include "file.h"
#include "cpphighlighter.h"
#include "patternmatcher.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:

    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_menuCreateFile_triggered();

    void on_menuOpenFile_triggered();

    void on_menuSaveFile_triggered();

    void on_menuSaveFIleIn_triggered();

    void on_menuRepeat_triggered();

    void on_menuCancel_triggered();

    void on_menuQuit_triggered();

    void on_menuCopy_triggered();

    void on_menuCut_triggered();

    void on_menuInsert_triggered();

    void on_menuDelete_triggered();

    void on_menuSelect_triggered();

    void on_action_22_triggered();

    void on_action_21_triggered();

    void documentModified();

    void on_toolbarStart_triggered();

private:
    Ui::MainWindow *ui;
    File file;
    bool is_modified;
    std::unique_ptr<CppHighlighter> highlighter;
    TextPatternMatcher matcher;
};
#endif // MAINWINDOW_H
