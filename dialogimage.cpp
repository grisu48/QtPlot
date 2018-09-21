#include "dialogimage.h"
#include "ui_dialogimage.h"

DialogImage::DialogImage(QString filename, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogImage)
{
    ui->setupUi(this);
    if(!this->pixmap.load(filename)) {
        throw "Error reading image file";
    }

    ui->lblPixmap->setPixmap(this->pixmap);

}

DialogImage::~DialogImage()
{
    delete ui;
}
