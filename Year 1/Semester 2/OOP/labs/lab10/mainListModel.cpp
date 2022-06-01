//
// Created by Diana-Elena Stancu on 01/06/2022.
//

#include "MainListModel.h"

MainListModel::MainListModel(const vector<Activitate>& activitati) : activitati{ activitati }{};

int MainListModel::rowCount(const QModelIndex&) const {
    return this->activitati.size();
}

QVariant MainListModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::DisplayRole) {
        auto activitata = this->activitati[index.row()];
        return QString("%1").arg(QString::fromStdString(activitata.getTitlu()));
    }

    return QVariant();
}

void MainListModel::setActivitati(const vector<Activitate>& activitati) {
    this->activitati = activitati;
    auto topIndex = createIndex(0, 0);
    auto bottomIndex = createIndex(activitati.size(), 0);
    emit dataChanged(topIndex, bottomIndex);
}