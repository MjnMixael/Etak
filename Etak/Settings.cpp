/*
 * Copyright (C) Mike Nelson
 *
 * All source code herein is subject to the GPL license included.
 *
*/

#include "Settings.h"

SettingsDialog::SettingsDialog(Etak* m_etak, QWidget* parent) : QDialog(parent), m_etak(m_etak) {
    ui.setupUi(this);

    std::string g_sortingNames[Next_available_order] = { 
        "Parsing Order", 
        "XSTR ID Order", 
        "Filename Order" 
    };
    
    for (int i = 0; i < Next_available_order; i++) {
        ui.sorting_combo_box->addItem(QString::fromStdString(g_sortingNames[i]));
    }

    if (m_etak) {
        ui.comprehensive_button->setChecked(m_etak->getComprehensive());

        ui.fill_in_ids_button->setEnabled(m_etak->getComprehensive());
        ui.fill_in_ids_button->setChecked(m_etak->getFillInIds());

        ui.sorting_combo_box->setCurrentIndex(m_etak->getSortingType());

        ui.header_comments_button->setChecked(m_etak->getHeaderAnnotations());
        ui.verbose_comments_button->setChecked(m_etak->getVerboseAnnotations());

        ui.case_insensitive_button->setChecked(m_etak->getCaseInsensitive());
    }
}

void SettingsDialog::accept() {
    if (m_etak) {
        m_etak->setComprehensive(ui.comprehensive_button->isChecked());
        m_etak->setSortingType(ui.sorting_combo_box->currentIndex());
        m_etak->setHeaderAnnotations(ui.header_comments_button->isChecked());
        m_etak->setVerboseAnnotations(ui.verbose_comments_button->isChecked());

        if (ui.comprehensive_button->isChecked()) {
            m_etak->setFillInIds(ui.fill_in_ids_button->isChecked());
            m_etak->toggleOffsetControl(!ui.fill_in_ids_button->isChecked());
        } else {
            m_etak->setFillInIds(false);
            m_etak->toggleOffsetControl(true);
        }
    }

    QDialog::accept();
}

void SettingsDialog::on_comprehensive_button_clicked() {
    ui.fill_in_ids_button->setEnabled(ui.comprehensive_button->isChecked());
}

void SettingsDialog::on_sorting_combo_box_currentIndexChanged(int val) {
    if (val == XSTR_ID_ORDER) {
        ui.header_comments_button->setChecked(false);
        ui.header_comments_button->setEnabled(false);
    } else {
        ui.header_comments_button->setEnabled(true);
        ui.header_comments_button->setChecked(true);
    }
}