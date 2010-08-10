/**
 ******************************************************************************
 *
 * @file       scopegadget.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup ScopePlugin Scope Gadget Plugin
 * @{
 * @brief The scope Gadget, graphically plots the states of UAVObjects
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "scopegadget.h"
#include "scopegadgetconfiguration.h"
#include "scopegadgetwidget.h"

#include <QtGui/qcolor.h>

ScopeGadget::ScopeGadget(QString classId, ScopeGadgetWidget *widget, QWidget *parent) :
        IUAVGadget(classId, parent),
        m_widget(widget)
{
}

void ScopeGadget::loadConfiguration(IUAVGadgetConfiguration* config)
{
    ScopeGadgetConfiguration *sgConfig = qobject_cast<ScopeGadgetConfiguration*>(config);
    ScopeGadgetWidget* widget = qobject_cast<ScopeGadgetWidget*>(m_widget);

    widget->setXWindowSize(sgConfig->dataSize());
    widget->setRefreshInterval(sgConfig->refreshInterval());

    if(sgConfig->plotType() == SequencialPlot )
        widget->setupSequencialPlot();
    else if(sgConfig->plotType() == ChronoPlot)
        widget->setupChronoPlot();
    //    else if(sgConfig->plotType() == UAVObjectPlot)
    //        widget->setupUAVObjectPlot();

    foreach (PlotCurveConfiguration* plotCurveConfig,  sgConfig->plotCurveConfigs()) {

        QString uavObject = plotCurveConfig->uavObject;
        QString uavField = plotCurveConfig->uavField;
        int scale = plotCurveConfig->yScalePower;
        QRgb color = plotCurveConfig->color;

        widget->addCurvePlot(
                uavObject,
                uavField,
                scale,
                QPen(
                        QBrush(QColor(color),Qt::SolidPattern),
                        (qreal)2,
                        Qt::SolidLine,
                        Qt::SquareCap,
                        Qt::BevelJoin)
                );
    }   
}

ScopeGadget::~ScopeGadget()
{

}
