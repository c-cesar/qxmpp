/*
 * Copyright (C) 2008-2022 The QXmpp developers
 *
 * Author:
 *  Manjeet Dahiya
 *
 * Source:
 *  https://github.com/qxmpp-project/qxmpp
 *
 * This file is a part of QXmpp library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */

#include "QXmppEntityTimeManager.h"

#include "QXmppClient.h"
#include "QXmppConstants_p.h"
#include "QXmppEntityTimeIq.h"
#include "QXmppFutureUtils_p.h"
#include "QXmppUtils.h"

#include <QDateTime>
#include <QDomElement>

using namespace QXmpp::Private;

///
/// \typedef QXmppEntityTimeManager::EntityTimeResult
///
/// Contains the requested entity time or the returned error in case of a
/// failure.
///
/// \since QXmpp 1.5
///

///
/// Request the time from an XMPP entity.
///
/// The result is emitted on the timeReceived() signal.
///
/// \param jid
///
QString QXmppEntityTimeManager::requestTime(const QString &jid)
{
    QXmppEntityTimeIq request;
    request.setType(QXmppIq::Get);
    request.setTo(jid);
    if (client()->sendPacket(request))
        return request.id();
    else
        return QString();
}

///
/// Requests the time from an XMPP entity and reports it via a QFuture.
///
/// The timeReceived() signal is not emitted.
///
/// \param jid
///
/// \warning THIS API IS NOT FINALIZED YET!
///
/// \since QXmpp 1.5
///
auto QXmppEntityTimeManager::requestEntityTime(const QString &jid) -> QFuture<EntityTimeResult>
{
    QXmppEntityTimeIq iq;
    iq.setType(QXmppIq::Get);
    iq.setTo(jid);

    return chainIq<EntityTimeResult>(client()->sendIq(std::move(iq)), this);
}

/// \cond
QStringList QXmppEntityTimeManager::discoveryFeatures() const
{
    return QStringList() << ns_entity_time;
}

bool QXmppEntityTimeManager::handleStanza(const QDomElement &element)
{
    if (element.tagName() == "iq" && QXmppEntityTimeIq::isEntityTimeIq(element)) {
        QXmppEntityTimeIq entityTime;
        entityTime.parse(element);

        if (entityTime.type() == QXmppIq::Get) {
            // respond to query
            QXmppEntityTimeIq responseIq;
            responseIq.setType(QXmppIq::Result);
            responseIq.setId(entityTime.id());
            responseIq.setTo(entityTime.from());

            QDateTime currentTime = QDateTime::currentDateTime();
            QDateTime utc = currentTime.toUTC();
            responseIq.setUtc(utc);

            currentTime.setTimeSpec(Qt::UTC);
            responseIq.setTzo(utc.secsTo(currentTime));

            client()->sendPacket(responseIq);
        }

        emit timeReceived(entityTime);
        return true;
    }

    return false;
}
/// \endcond
