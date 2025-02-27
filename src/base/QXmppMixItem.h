/*
 * Copyright (C) 2008-2022 The QXmpp developers
 *
 * Author:
 *  Linus Jahn
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

#ifndef QXMPPMIXITEM_H
#define QXMPPMIXITEM_H

#include "QXmppElement.h"

#include <QSharedDataPointer>

class QXmppMixInfoItemPrivate;
class QXmppMixParticipantItemPrivate;

class QXMPP_EXPORT QXmppMixInfoItem
{
public:
    QXmppMixInfoItem();
    QXmppMixInfoItem(const QXmppMixInfoItem &);
    ~QXmppMixInfoItem();

    QXmppMixInfoItem &operator=(const QXmppMixInfoItem &);

    QString name() const;
    void setName(const QString &);

    QString description() const;
    void setDescription(const QString &);

    QStringList contactJids() const;
    void setContactJids(const QStringList &);

    /// \cond
    void parse(const QXmppElement &itemContent);
    QXmppElement toElement() const;
    /// \endcond

    static bool isMixChannelInfo(const QDomElement &);

private:
    QSharedDataPointer<QXmppMixInfoItemPrivate> d;
};

class QXMPP_EXPORT QXmppMixParticipantItem
{
public:
    QXmppMixParticipantItem();
    QXmppMixParticipantItem(const QXmppMixParticipantItem &);
    ~QXmppMixParticipantItem();

    QXmppMixParticipantItem &operator=(const QXmppMixParticipantItem &);

    QString nick() const;
    void setNick(const QString &);

    QString jid() const;
    void setJid(const QString &);

    /// \cond
    void parse(const QXmppElement &itemContent);
    QXmppElement toElement() const;
    /// \endcond

    static bool isMixParticipantItem(const QDomElement &);

private:
    QSharedDataPointer<QXmppMixParticipantItemPrivate> d;
};

#endif  // QXMPPMIXITEM_H
