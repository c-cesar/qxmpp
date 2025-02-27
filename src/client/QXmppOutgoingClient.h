/*
 * Copyright (C) 2008-2022 The QXmpp developers
 *
 * Authors:
 *  Manjeet Dahiya
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

#ifndef QXMPPOUTGOINGCLIENT_H
#define QXMPPOUTGOINGCLIENT_H

#include "QXmppClient.h"
#include "QXmppStanza.h"
#include "QXmppStream.h"

class QDomElement;
class QSslError;

class QXmppConfiguration;
class QXmppPresence;
class QXmppIq;
class QXmppMessage;

class QXmppOutgoingClientPrivate;

/// \brief The QXmppOutgoingClient class represents an outgoing XMPP stream
/// to an XMPP server.
///

class QXMPP_EXPORT QXmppOutgoingClient : public QXmppStream
{
    Q_OBJECT

public:
    QXmppOutgoingClient(QObject *parent);
    ~QXmppOutgoingClient() override;

    void connectToHost();
    bool isAuthenticated() const;
    bool isConnected() const override;
    bool isClientStateIndicationEnabled() const;
    bool isStreamManagementEnabled() const;
    bool isStreamResumed() const;

    /// Returns the used socket
    QSslSocket *socket() const { return QXmppStream::socket(); };
    QXmppStanza::Error::Condition xmppStreamError();

    QXmppConfiguration &configuration();

Q_SIGNALS:
    /// This signal is emitted when an error is encountered.
    void error(QXmppClient::Error);

    /// This signal is emitted when an element is received.
    void elementReceived(const QDomElement &element, bool &handled);

    /// This signal is emitted when a presence is received.
    void presenceReceived(const QXmppPresence &);

    /// This signal is emitted when a message is received.
    void messageReceived(const QXmppMessage &);

    /// This signal is emitted when an IQ response (type result or error) has
    /// been received that was not handled by elementReceived().
    void iqReceived(const QXmppIq &);

    /// This signal is emitted when SSL errors are encountered.
    void sslErrors(const QList<QSslError> &errors);

protected:
    /// \cond
    // Overridable methods
    void handleStart() override;
    void handleStanza(const QDomElement &element) override;
    void handleStream(const QDomElement &element) override;
    /// \endcond

public Q_SLOTS:
    void disconnectFromHost() override;

private Q_SLOTS:
    void _q_dnsLookupFinished();
    void _q_socketDisconnected();
    void socketError(QAbstractSocket::SocketError);
    void socketSslErrors(const QList<QSslError> &);

    void pingStart();
    void pingStop();
    void pingSend();
    void pingTimeout();

private:
    bool setResumeAddress(const QString &address);
    static std::pair<QString, int> parseHostAddress(const QString &address);

    friend class QXmppOutgoingClientPrivate;
    friend class tst_QXmppOutgoingClient;

    QXmppOutgoingClientPrivate *const d;
};

#endif  // QXMPPOUTGOINGCLIENT_H
