/*
 * Copyright (C) 2008-2022 The QXmpp developers
 *
 * Author:
 *  Jeremy Lainé
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

#ifndef QXMPPINCOMINGSERVER_H
#define QXMPPINCOMINGSERVER_H

#include "QXmppStream.h"

class QXmppDialback;
class QXmppIncomingServerPrivate;
class QXmppOutgoingServer;

/// \brief The QXmppIncomingServer class represents an incoming XMPP stream
/// from an XMPP server.
///

class QXMPP_EXPORT QXmppIncomingServer : public QXmppStream
{
    Q_OBJECT

public:
    QXmppIncomingServer(QSslSocket *socket, const QString &domain, QObject *parent);
    ~QXmppIncomingServer() override;

    bool isConnected() const override;
    QString localStreamId() const;

Q_SIGNALS:
    /// This signal is emitted when a dialback verify request is received.
    void dialbackRequestReceived(const QXmppDialback &result);

    /// This signal is emitted when an element is received.
    void elementReceived(const QDomElement &element);

protected:
    /// \cond
    void handleStanza(const QDomElement &stanzaElement) override;
    void handleStream(const QDomElement &streamElement) override;
    /// \endcond

private Q_SLOTS:
    void slotDialbackResponseReceived(const QXmppDialback &dialback);
    void slotSocketDisconnected();

private:
    Q_DISABLE_COPY(QXmppIncomingServer)
    QXmppIncomingServerPrivate *d;
    friend class QXmppIncomingServerPrivate;
};

#endif
