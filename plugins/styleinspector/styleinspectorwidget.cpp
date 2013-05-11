/*
  styleinspectorwidget.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2012-2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Volker Krause <volker.krause@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "styleinspectorwidget.h"
#include "complexcontrolmodel.h"
#include "controlmodel.h"
#include "primitivemodel.h"
#include "ui_styleinspectorwidget.h"

#include <include/objectmodel.h>

#include <common/network/objectbroker.h>

using namespace GammaRay;

StyleInspectorWidget::StyleInspectorWidget(QWidget *parent)
  : QWidget(parent),
    ui(new Ui::StyleInspectorWidget),
    m_primitiveModel(new PrimitiveModel(this)),
    m_controlModel(new ControlModel(this)),
    m_complexControlModel(new ComplexControlModel(this))
{
  ui->setupUi(this);

  ui->styleSelector->setModel(ObjectBroker::model("com.kdab.GammaRay.StyleList"));
  connect(ui->styleSelector, SIGNAL(activated(int)), SLOT(styleSelected(int)));

  ui->primitivePage->setModel(m_primitiveModel);
  ui->controlPage->setModel(m_controlModel);
  ui->complexControlPage->setModel(m_complexControlModel);

  ui->pixelMetricView->setModel(ObjectBroker::model("com.kdab.GammaRay.StyleInspector.PixelMetricModel"));
  ui->pixelMetricView->header()->setResizeMode(QHeaderView::ResizeToContents);

  ui->standardIconView->setModel(ObjectBroker::model("com.kdab.GammaRay.StyleInspector.StandardIconModel"));
  ui->standardIconView->header()->setResizeMode(QHeaderView::ResizeToContents);

  ui->standardPaletteView->setModel(ObjectBroker::model("com.kdab.GammaRay.StyleInspector.PaletteModel"));
  ui->standardIconView->header()->setResizeMode(QHeaderView::ResizeToContents);

  if (ui->styleSelector->count()) {
    styleSelected(0);
  }
}

StyleInspectorWidget::~StyleInspectorWidget()
{
  delete ui;
}

void StyleInspectorWidget::styleSelected(int index)
{
  QItemSelectionModel *selectionModel = ObjectBroker::selectionModel(ui->styleSelector->model());
  selectionModel->select(ui->styleSelector->model()->index(index, 0), QItemSelectionModel::ClearAndSelect);

  QObject *obj = ui->styleSelector->itemData(index, ObjectModel::ObjectRole).value<QObject*>();
  QStyle *style = qobject_cast<QStyle*>(obj);
  m_primitiveModel->setStyle(style);
  m_controlModel->setStyle(style);
  m_complexControlModel->setStyle(style);
}

#include "styleinspectorwidget.moc"