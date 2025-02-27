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

#ifndef QXMPPVERSIONMANAGER_H
#define QXMPPVERSIONMANAGER_H

#include "QXmppClientExtension.h"

class QXmppVersionIq;
class QXmppVersionManagerPrivate;

///
/// \brief The QXmppVersionManager class makes it possible to request for
/// the software version of an entity as defined by \xep{0092}: Software Version.
///
/// \note Its object should not be created using its constructor. Instead
/// \c QXmppClient::findExtension<QXmppVersionManager>() should be used to get
/// the instantiated object of this class.
///
/// \ingroup Managers
///
class QXMPP_EXPORT QXmppVersionManager : public QXmppClientExtension
{
    Q_OBJECT

public:
    QXmppVersionManager();
    ~QXmppVersionManager() override;

    QString requestVersion(const QString &jid);

    void setClientName(const QString &);
    void setClientVersion(const QString &);
    void setClientOs(const QString &);

    QString clientName() const;
    QString clientVersion() const;
    QString clientOs() const;

    /// \cond
    QStringList discoveryFeatures() const override;
    bool handleStanza(const QDomElement &element) override;
    /// \endcond

Q_SIGNALS:
    /// \brief This signal is emitted when a version response is received.
    void versionReceived(const QXmppVersionIq &);

private:
    QXmppVersionManagerPrivate *d;
};

#endif  // QXMPPVERSIONMANAGER_H
