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

#include "QXmppIbbIq.h"

#include "QXmppConstants_p.h"

#include <QDomElement>
#include <QXmlStreamWriter>

///
/// \class QXmppIbbOpenIq
///
/// The QXmppIbbOpenIq represents an IBB open request as defined by \xep{0047,
/// In-Band Bytestreams}.
///
/// \ingroup Stanzas
///

QXmppIbbOpenIq::QXmppIbbOpenIq() : QXmppIq(QXmppIq::Set), m_block_size(1024)
{
}

///
/// Returns the maximum size in bytes of each data chunk (which MUST NOT be
/// greater than 65535).
///
long QXmppIbbOpenIq::blockSize() const
{
    return m_block_size;
}

///
/// Sets the maximum size in bytes of each data chunk (which MUST NOT be greater
/// than 65535).
///
void QXmppIbbOpenIq::setBlockSize(long block_size)
{
    m_block_size = block_size;
}

///
/// Returns the unique session ID for this IBB session (which MUST match the
/// NMTOKEN datatype).
///
QString QXmppIbbOpenIq::sid() const
{
    return m_sid;
}

///
/// Sets the unique session ID for this IBB session (which MUST match the
/// NMTOKEN datatype).
///
void QXmppIbbOpenIq::setSid(const QString &sid)
{
    m_sid = sid;
}

/// \cond
bool QXmppIbbOpenIq::isIbbOpenIq(const QDomElement &element)
{
    QDomElement openElement = element.firstChildElement("open");
    return openElement.namespaceURI() == ns_ibb;
}

void QXmppIbbOpenIq::parseElementFromChild(const QDomElement &element)
{
    QDomElement openElement = element.firstChildElement("open");
    m_sid = openElement.attribute("sid");
    m_block_size = openElement.attribute("block-size").toLong();
}

void QXmppIbbOpenIq::toXmlElementFromChild(QXmlStreamWriter *writer) const
{
    writer->writeStartElement("open");
    writer->writeDefaultNamespace(ns_ibb);
    writer->writeAttribute("sid", m_sid);
    writer->writeAttribute("block-size", QString::number(m_block_size));
    writer->writeEndElement();
}
/// \endcond

///
/// \class QXmppIbbCloseIq
///
/// The QXmppIbbCloseIq represents an IBB close request as defined by \xep{0047,
/// In-Band Bytestreams}.
///
/// \ingroup Stanzas
///

QXmppIbbCloseIq::QXmppIbbCloseIq() : QXmppIq(QXmppIq::Set)
{
}

///
/// Returns the unique session ID for this IBB session (which MUST match the
/// NMTOKEN datatype).
///
QString QXmppIbbCloseIq::sid() const
{
    return m_sid;
}

///
/// Sets the unique session ID for this IBB session (which MUST match the
/// NMTOKEN datatype).
///
void QXmppIbbCloseIq::setSid(const QString &sid)
{
    m_sid = sid;
}

/// \cond
bool QXmppIbbCloseIq::isIbbCloseIq(const QDomElement &element)
{
    QDomElement openElement = element.firstChildElement("close");
    return openElement.namespaceURI() == ns_ibb;
}

void QXmppIbbCloseIq::parseElementFromChild(const QDomElement &element)
{
    QDomElement openElement = element.firstChildElement("close");
    m_sid = openElement.attribute("sid");
}

void QXmppIbbCloseIq::toXmlElementFromChild(QXmlStreamWriter *writer) const
{
    writer->writeStartElement("close");
    writer->writeDefaultNamespace(ns_ibb);
    writer->writeAttribute("sid", m_sid);
    writer->writeEndElement();
}
/// \endcond

///
/// \class QXmppIbbCloseIq
///
/// The QXmppIbbCloseIq represents an IBB data request as defined by \xep{0047,
/// In-Band Bytestreams}.
///
/// \ingroup Stanzas
///

QXmppIbbDataIq::QXmppIbbDataIq() : QXmppIq(QXmppIq::Set), m_seq(0)
{
}

///
/// Returns the data chunk sequence counter.
///
/// The value starts at 0 (zero) for each sender and MUST be incremented for
/// each packet sent by that entity. The counter loops at maximum, so that after
/// value 65535 the sequence MUST start again at 0.
///
quint16 QXmppIbbDataIq::sequence() const
{
    return m_seq;
}

///
/// Sets the data chunk sequence counter.
///
/// The value starts at 0 (zero) for each sender and MUST be incremented for
/// each packet sent by that entity. The counter loops at maximum, so that after
/// value 65535 the sequence MUST start again at 0.
///
void QXmppIbbDataIq::setSequence(quint16 seq)
{
    m_seq = seq;
}

///
/// Returns the unique session ID for this IBB session (which MUST match the
/// NMTOKEN datatype).
///
QString QXmppIbbDataIq::sid() const
{
    return m_sid;
}

///
/// Sets the unique session ID for this IBB session (which MUST match the
/// NMTOKEN datatype).
///
void QXmppIbbDataIq::setSid(const QString &sid)
{
    m_sid = sid;
}

///
/// Returns the current data chunk
///
QByteArray QXmppIbbDataIq::payload() const
{
    return m_payload;
}

///
/// Sets the current data chunk
///
void QXmppIbbDataIq::setPayload(const QByteArray &data)
{
    m_payload = data;
}

/// \cond
bool QXmppIbbDataIq::isIbbDataIq(const QDomElement &element)
{
    QDomElement dataElement = element.firstChildElement("data");
    return dataElement.namespaceURI() == ns_ibb;
}

void QXmppIbbDataIq::parseElementFromChild(const QDomElement &element)
{
    QDomElement dataElement = element.firstChildElement("data");
    m_sid = dataElement.attribute("sid");
    m_seq = dataElement.attribute("seq").toLong();
    m_payload = QByteArray::fromBase64(dataElement.text().toLatin1());
}

void QXmppIbbDataIq::toXmlElementFromChild(QXmlStreamWriter *writer) const
{
    writer->writeStartElement("data");
    writer->writeDefaultNamespace(ns_ibb);
    writer->writeAttribute("sid", m_sid);
    writer->writeAttribute("seq", QString::number(m_seq));
    writer->writeCharacters(m_payload.toBase64());
    writer->writeEndElement();
}
/// \endcond
