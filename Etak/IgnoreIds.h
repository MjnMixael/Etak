/*
 * Copyright (C) Mike Nelson
 *
 * All source code herein is subject to the GPL license included.
 *
*/

#pragma once

#include <QDialog>
#include "ui_IgnoreIds.h"

#include "Etak.h"

class Etak;

class IgnoreIdsDialog : public QDialog {
    Q_OBJECT
public:
    explicit IgnoreIdsDialog(Etak* etak, QWidget* parent = nullptr);
public slots:
    void accept() override;

    // Ignored IDs extensions widget
    void on_ignore_ids_add_button_clicked();
    void on_ignore_ids_update_button_clicked();
    void on_ignore_ids_remove_button_clicked();
    void on_ignore_ids_clear_button_clicked();
    void on_ignore_ids_list_widget_clicked();
private:
    Ui::IgnoreIdsDialog ui;
    Etak* m_etak;

    // UI Controls
    void addIgnoreIdsItem(QString id);
    void resetIgnoreIdsInput();
};
