#ifndef DIALOGIMAGE_H
#define DIALOGIMAGE_H

#include <QString>
#include <QDialog>
#include <QPixmap>

namespace Ui {
class DialogImage;
}

class DialogImage : public QDialog
{
    Q_OBJECT

public:
    explicit DialogImage(QString filename, QWidget *parent = 0);
    ~DialogImage();

private:
    Ui::DialogImage *ui;
    QPixmap pixmap;
};

#endif // DIALOGIMAGE_H
