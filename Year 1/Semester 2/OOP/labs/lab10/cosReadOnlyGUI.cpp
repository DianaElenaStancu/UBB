//
// Created by Diana-Elena Stancu on 24/05/2022.
//

#include "cosReadOnlyGUI.h"


CosReadOnlyGUI::CosReadOnlyGUI(CosActivitati& cos) : cos{ cos } {
    this->cos.addObserver(this);
    this->repaint();
}

void CosReadOnlyGUI::paintEvent(QPaintEvent* event) {
    QPainter g{ this };
    g.setPen(Qt::green);


    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> x_coord(0, this->width());
    std::uniform_int_distribution<> y_coord(0, this->height());
    std::uniform_int_distribution<> width(32, RECTANGLE_MAX_DIM);
    std::uniform_int_distribution<> height(32, RECTANGLE_MAX_DIM);

    for (const auto& masina : this->cos.getAll()) {
        g.drawEllipse(x_coord(mt), y_coord(mt), width(mt), height(mt));

    }
}

void CosReadOnlyGUI::update() {
    this->repaint();
}