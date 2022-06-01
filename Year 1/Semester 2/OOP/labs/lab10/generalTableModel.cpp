//
// Created by Diana-Elena Stancu on 01/06/2022.
//

#include "generalTableModel.h"

GeneralTableModel::GeneralTableModel(const vector<Activitate>& activitati) : activitati{ activitati } {};

int GeneralTableModel::rowCount(const QModelIndex &) const {
    return this->activitati.size();
}

int GeneralTableModel::columnCount(const QModelIndex&) const {
    return 4;
}

bool GeneralTableModel::insertRows(int row, int count, const QModelIndex& parent) {
    beginInsertRows(parent, row, row + count - 1);
    endInsertRows();
    return true;
}

bool GeneralTableModel::removeRows(int row, int count, const QModelIndex& parent) {
    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
    return true;
}

QVariant GeneralTableModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::DisplayRole) {
        auto activitata = this->activitati[index.row()];

        if (index.column() == 0) {
            return QString::fromStdString(activitata.getTitlu());
        }
        else if (index.column() == 1) {
            return QString::fromStdString(activitata.getDescriere());
        }
        else if (index.column() == 2) {
            return QString::fromStdString(activitata.getTip());
        }
        else if (index.column() == 3) {
            return QString::number(activitata.getDurata());
        }
    }
    return QVariant{};
}

QVariant GeneralTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            if (section == 0) {
                return QString("Titlu");
            }
            else if (section == 1) {
                return QString("Descriere");
            }
            else if (section == 2) {
                return QString("Tip");
            }
            else {
                return QString("Durata");
            }
        }
    }
    return QVariant{};
}

void GeneralTableModel::setActivitati(const vector<Activitate>& activitati) {
    //if (rowCount()) {
    //	this->removeRows(0, rowCount());
    //}
    if (rowCount() > activitati.size()) {
        this->removeRows(activitati.size(), rowCount() - activitati.size());
    }
    else if (rowCount() < activitati.size()) {
        this->insertRows(rowCount(), activitati.size() - rowCount());
    }

    this->activitati = activitati;
    auto topIndex = createIndex(0, 0);
    auto bottomIndex = createIndex(rowCount(), columnCount());

    //this->insertRows(0, rowCount());

    emit dataChanged(topIndex, bottomIndex);
    qDebug() << bottomIndex.row() << " " << bottomIndex.column();
}