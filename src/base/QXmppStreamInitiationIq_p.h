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

#ifndef QXMPPSTREAMINITIATIONIQ_P_H
#define QXMPPSTREAMINITIATIONIQ_P_H

#include "QXmppDataForm.h"
#include "QXmppIq.h"
#include "QXmppTransferManager.h"

#include <QDateTime>

//
//  W A R N I N G
//  -------------
//
// This file is not part of the QXmpp API.  It exists for the convenience
// of the QXmppTransferManager class.
//
// This header file may change from version to version without notice,
// or even be removed.
//
// We mean it.
//

/// \cond
class QXMPP_AUTOTEST_EXPORT QXmppStreamInitiationIq : public QXmppIq
{
public:
    enum Profile {
        None = 0,
        FileTransfer
    };

    QXmppDataForm featureForm() const;
    void setFeatureForm(const QXmppDataForm &form);

    QXmppTransferFileInfo fileInfo() const;
    void setFileInfo(const QXmppTransferFileInfo &info);

    QString mimeType() const;
    void setMimeType(const QString &mimeType);

    QXmppStreamInitiationIq::Profile profile() const;
    void setProfile(QXmppStreamInitiationIq::Profile profile);

    QString siId() const;
    void setSiId(const QString &id);

    static bool isStreamInitiationIq(const QDomElement &element);

protected:
    void parseElementFromChild(const QDomElement &element) override;
    void toXmlElementFromChild(QXmlStreamWriter *writer) const override;

private:
    QXmppDataForm m_featureForm;
    QXmppTransferFileInfo m_fileInfo;
    QString m_mimeType;
    Profile m_profile;
    QString m_siId;
};
/// \endcond

#endif
