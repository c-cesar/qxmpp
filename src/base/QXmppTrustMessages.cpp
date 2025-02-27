/*
 * Copyright (C) 2008-2022 The QXmpp developers
 *
 * Author:
 *  Melvin Keskin
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

#include "QXmppTrustMessages.h"

#include "QXmppConstants_p.h"
#include "QXmppUtils.h"

#include <QDomElement>

///
/// \class QXmppTrustMessageElement
///
/// \brief The QXmppTrustMessageElement class represents a trust message element
/// as defined by \xep{0434, Trust Messages (TM)}.
///
/// \since QXmpp 1.5
///

class QXmppTrustMessageElementPrivate : public QSharedData
{
public:
    QString usage;
    QString encryption;
    QList<QXmppTrustMessageKeyOwner> keyOwners;
};

///
/// Constructs a trust message element.
///
QXmppTrustMessageElement::QXmppTrustMessageElement()
    : d(new QXmppTrustMessageElementPrivate)
{
}

///
/// Constructs a copy of \a other.
///
/// \param other
///
QXmppTrustMessageElement::QXmppTrustMessageElement(const QXmppTrustMessageElement &other) = default;

QXmppTrustMessageElement::~QXmppTrustMessageElement() = default;

///
/// Assigns \a other to this trust message element.
///
/// \param other
///
QXmppTrustMessageElement &QXmppTrustMessageElement::operator=(const QXmppTrustMessageElement &other) = default;

///
/// Returns the namespace of the trust management protocol.
///
/// \return the trust management protocol namespace
///
QString QXmppTrustMessageElement::usage() const
{
    return d->usage;
}

///
/// Sets the namespace of the trust management protocol.
///
/// \param usage trust management protocol namespace
///
void QXmppTrustMessageElement::setUsage(const QString &usage)
{
    d->usage = usage;
}

///
/// Returns the namespace of the keys' encryption protocol.
///
/// \return the encryption protocol namespace
///
QString QXmppTrustMessageElement::encryption() const
{
    return d->encryption;
}

///
/// Sets the namespace of the keys' encryption protocol.
///
/// \param encryption encryption protocol namespace
///
void QXmppTrustMessageElement::setEncryption(const QString &encryption)
{
    d->encryption = encryption;
}

///
/// Returns the key owners containing the corresponding information for
/// trusting or distrusting their keys.
///
/// \return the owners of the keys for trusting or distrusting
///
QList<QXmppTrustMessageKeyOwner> QXmppTrustMessageElement::keyOwners() const
{
    return d->keyOwners;
}

///
/// Sets the key owners containing the corresponding information for trusting or
/// distrusting their keys.
///
/// \param keyOwners owners of the keys for trusting or distrusting
///
void QXmppTrustMessageElement::setKeyOwners(const QList<QXmppTrustMessageKeyOwner> &keyOwners)
{
    d->keyOwners = keyOwners;
}

///
/// Adds a key owner containing the corresponding information for trusting or
/// distrusting the owners keys.
///
/// \param keyOwner owner of the keys for trusting or distrusting
///
void QXmppTrustMessageElement::addKeyOwner(const QXmppTrustMessageKeyOwner &keyOwner)
{
    d->keyOwners.append(keyOwner);
}

/// \cond
void QXmppTrustMessageElement::parse(const QDomElement &element)
{
    d->usage = element.attribute("usage");
    d->encryption = element.attribute("encryption");

    for (auto keyOwnerElement = element.firstChildElement("key-owner");
         !keyOwnerElement.isNull();
         keyOwnerElement = keyOwnerElement.nextSiblingElement("key-owner")) {
        if (QXmppTrustMessageKeyOwner::isTrustMessageKeyOwner(keyOwnerElement)) {
            QXmppTrustMessageKeyOwner keyOwner;
            keyOwner.parse(keyOwnerElement);
            d->keyOwners.append(keyOwner);
        }
    }
}

void QXmppTrustMessageElement::toXml(QXmlStreamWriter *writer) const
{
    writer->writeStartElement("trust-message");
    writer->writeDefaultNamespace(ns_tm);
    writer->writeAttribute("usage", d->usage);
    writer->writeAttribute("encryption", d->encryption);

    for (const auto &keyOwner : d->keyOwners) {
        keyOwner.toXml(writer);
    }

    writer->writeEndElement();
}
/// \endcond

///
/// Determines whether the given DOM element is a trust message element.
///
/// \param element DOM element being checked
///
/// \return true if element is a trust message element, otherwise false
///
bool QXmppTrustMessageElement::isTrustMessageElement(const QDomElement &element)
{
    return element.tagName() == QStringLiteral("trust-message") &&
        element.namespaceURI() == ns_tm;
}

///
/// \class QXmppTrustMessageKeyOwner
///
/// \brief The QXmppTrustMessageKeyOwner class represents a key owner of the
/// trust message as defined by \xep{0434, Trust Messages (TM)}.
///
/// \since QXmpp 1.5
///

class QXmppTrustMessageKeyOwnerPrivate : public QSharedData
{
public:
    QString jid;
    QList<QByteArray> trustedKeys;
    QList<QByteArray> distrustedKeys;
};

///
/// Constructs a trust message key owner.
///
QXmppTrustMessageKeyOwner::QXmppTrustMessageKeyOwner()
    : d(new QXmppTrustMessageKeyOwnerPrivate)
{
}

///
/// Constructs a copy of \a other.
///
/// \param other
///
QXmppTrustMessageKeyOwner::QXmppTrustMessageKeyOwner(const QXmppTrustMessageKeyOwner &other) = default;

QXmppTrustMessageKeyOwner::~QXmppTrustMessageKeyOwner() = default;

///
/// Assigns \a other to this trust message key owner.
///
/// \param other
///
QXmppTrustMessageKeyOwner &QXmppTrustMessageKeyOwner::operator=(const QXmppTrustMessageKeyOwner &other) = default;

///
/// Returns the bare JID of the key owner.
///
/// \return the key owner's bare JID
///
QString QXmppTrustMessageKeyOwner::jid() const
{
    return d->jid;
}

///
/// Sets the bare JID of the key owner.
///
/// If a full JID is passed, it is converted into a bare JID.
///
/// \param jid key owner's bare JID
///
void QXmppTrustMessageKeyOwner::setJid(const QString &jid)
{
    d->jid = QXmppUtils::jidToBareJid(jid);
}

///
/// Returns the IDs of the keys that are trusted.
///
/// \return the IDs of trusted keys
///
QList<QByteArray> QXmppTrustMessageKeyOwner::trustedKeys() const
{
    return d->trustedKeys;
}

///
/// Sets the IDs of keys that are trusted.
///
/// \param keyIds IDs of trusted keys
///
void QXmppTrustMessageKeyOwner::setTrustedKeys(const QList<QByteArray> &keyIds)
{
    d->trustedKeys = keyIds;
}

///
/// Returns the IDs of the keys that are distrusted.
///
/// \return the IDs of distrusted keys
///
QList<QByteArray> QXmppTrustMessageKeyOwner::distrustedKeys() const
{
    return d->distrustedKeys;
}

///
/// Sets the IDs of keys that are distrusted.
///
/// \param keyIds IDs of distrusted keys
///
void QXmppTrustMessageKeyOwner::setDistrustedKeys(const QList<QByteArray> &keyIds)
{
    d->distrustedKeys = keyIds;
}

/// \cond
void QXmppTrustMessageKeyOwner::parse(const QDomElement &element)
{
    d->jid = element.attribute("jid");

    for (auto childElement = element.firstChildElement();
         !childElement.isNull();
         childElement = childElement.nextSiblingElement()) {
        if (const auto tagName = childElement.tagName(); tagName == "trust") {
            d->trustedKeys.append(QByteArray::fromBase64(childElement.text().toLatin1()));
        } else if (tagName == "distrust") {
            d->distrustedKeys.append(QByteArray::fromBase64(childElement.text().toLatin1()));
        }
    }
}

void QXmppTrustMessageKeyOwner::toXml(QXmlStreamWriter *writer) const
{
    writer->writeStartElement("key-owner");
    writer->writeAttribute("jid", d->jid);

    for (const auto &keyIdentifier : d->trustedKeys) {
        writer->writeTextElement("trust", keyIdentifier.toBase64());
    }

    for (const auto &keyIdentifier : d->distrustedKeys) {
        writer->writeTextElement("distrust", keyIdentifier.toBase64());
    }

    writer->writeEndElement();
}
/// \endcond

///
/// Determines whether the given DOM element is a trust message key owner.
///
/// \param element DOM element being checked
///
/// \return true if element is a trust message key owner, otherwise false
///
bool QXmppTrustMessageKeyOwner::isTrustMessageKeyOwner(const QDomElement &element)
{
    return element.tagName() == QStringLiteral("key-owner") &&
        element.namespaceURI() == ns_tm;
}
