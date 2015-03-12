/*
 * Open-BLDC QSim - Open BrushLess DC Motor Controller QT Simulator GUI
 * Copyright (C) 2012 by Piotr Esden-Tempski <piotr@esden.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "simrunner.h"

#include <QDebug>

SimRunner::SimRunner(QObject *parent) :
    QObject(parent)
{
    running = false;
    thread = NULL;
    sim = NULL;
}

void SimRunner::runSim(void)
{

    if (sim == NULL) {
        sim = new Sim();
    }

    if ((thread == NULL) || (thread->isFinished())) {
        running = true;
        qDebug() << "Activating simulation.";

        if (thread == NULL) {
            thread = new QThread();
        }
        sim->moveToThread(thread);
        connect(thread, SIGNAL(started()), sim, SLOT(start()), Qt::QueuedConnection);
        connect(sim, SIGNAL(newDataPoints(QVector<double>*,QVector<QVector<double> *>*)), this, SLOT(onNewDataPoints(QVector<double>*,QVector<QVector<double> *>*)), Qt::QueuedConnection);
        //connect(sim, SIGNAL(finished()), thread, SLOT(quit()), Qt::QueuedConnection);
        //connect(sim, SIGNAL(finished()), sim, SLOT(deleteLater()), Qt::QueuedConnection);
        connect(sim, SIGNAL(finished()), this, SLOT(simFinished()));

        thread->start();
    } else {
        qDebug() << "Thread still running ...";
    }
}

void SimRunner::onNewDataPoints(QVector<double> *dataTimes, QVector<QVector<double> *> *dataValues)
{
    emit newDataPoints(dataTimes, dataValues);
}

void SimRunner::simFinished()
{
    qDebug() << "Simulator finished signal...";
    running = false;
    qDebug() << "Starting to wait for the thread...";
    thread->wait();
    delete sim;
    delete thread;
    thread = NULL;
    sim = NULL;
    qDebug() << "Cleaned up simulator.";
}

void SimRunner::stopSim()
{
    sim->stopSim();
}

void SimRunner::setPWMDuty(double duty)
{
    sim->setPWMDuty(duty);
}

double SimRunner::getPWMDuty()
{
    if (sim == NULL) {
        return 0;
    } else {
        return sim->getPWMDuty();
    }
}

bool SimRunner::isRunning()
{
    return running;
}
