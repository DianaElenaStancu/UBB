//
// Created by Diana-Elena Stancu on 24/05/2022.
//

#ifndef LAB10_COSREADONLYGUI_H
#define LAB10_COSREADONLYGUI_H

#include "Observer.h"
#include "domain.h"
#include "cosActivitati.h"
#include <qwidget.h>
#include <qpainter.h>
#include <random>
#include <cmath>

#define RECTANGLE_MAX_DIM 256

class CosReadOnlyGUI : public QWidget, public Observer {
private:
    CosActivitati& cos;

public:
    CosReadOnlyGUI(CosActivitati& cos);

    void update() override;

    void paintEvent(QPaintEvent* event) override;

    ~CosReadOnlyGUI() {
        this->cos.removeObserver(this);
    }
};



#endif //LAB10_COSREADONLYGUI_H
