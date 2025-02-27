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

#ifndef QXMPPBOOKMARKMANAGER_H
#define QXMPPBOOKMARKMANAGER_H

#include "QXmppClientExtension.h"

#include <QUrl>

class QXmppBookmarkManagerPrivate;
class QXmppBookmarkSet;

/// \brief The QXmppBookmarkManager class allows you to store and retrieve
/// bookmarks as defined by \xep{0048}: Bookmarks.
///

class QXMPP_EXPORT QXmppBookmarkManager : public QXmppClientExtension
{
    Q_OBJECT

public:
    QXmppBookmarkManager();
    ~QXmppBookmarkManager() override;

    bool areBookmarksReceived() const;
    QXmppBookmarkSet bookmarks() const;
    bool setBookmarks(const QXmppBookmarkSet &bookmarks);

    /// \cond
    bool handleStanza(const QDomElement &stanza) override;
    /// \endcond

Q_SIGNALS:
    /// This signal is emitted when bookmarks are received.
    void bookmarksReceived(const QXmppBookmarkSet &bookmarks);

protected:
    /// \cond
    void setClient(QXmppClient *client) override;
    /// \endcond

private Q_SLOTS:
    void slotConnected();
    void slotDisconnected();

private:
    QXmppBookmarkManagerPrivate *const d;
};

#endif
