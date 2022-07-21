#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_media_temp.h"


class media_temp : public QMainWindow
{
    Q_OBJECT

public:
    media_temp(QWidget *parent = nullptr);
    ~media_temp();

    void init();

    Ui::media_tempClass ui;

};
