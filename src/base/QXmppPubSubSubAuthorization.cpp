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

#include "QXmppPubSubSubAuthorization.h"

const auto FORM_TYPE_SUBSCRIBE_AUTHORIZATION = QStringLiteral("http://jabber.org/protocol/pubsub#subscribe_authorization");
const auto ALLOW_SUBSCRIPTION = QStringLiteral("pubsub#allow");
const auto NODE = QStringLiteral("pubsub#node");
const auto SUBSCRIBER_JID = QStringLiteral("pubsub#subscriber_jid");
const auto SUBID = QStringLiteral("pubsub#subid");

///
/// \class QXmppPubSubSubAuthorization
///
/// This class represents a PubSub subscribe authorization data form.
///
/// \since QXmpp 1.5
///

class QXmppPubSubSubAuthorizationPrivate : public QSharedData
{
public:
    std::optional<bool> allowSubscription;
    QString node;
    QString subscriberJid;
    QString subid;
};

///
/// Tries to parse a PubSub subscribe authorization form from a plain data form.
///
/// \returns The parsed data form on success.
///
std::optional<QXmppPubSubSubAuthorization> QXmppPubSubSubAuthorization::fromDataForm(const QXmppDataForm &form)
{
    if (auto parsed = QXmppPubSubSubAuthorization();
            QXmppDataFormBase::fromDataForm(form, parsed)) {
        return parsed;
    }
    return std::nullopt;
}

QXmppPubSubSubAuthorization::QXmppPubSubSubAuthorization()
    : d(new QXmppPubSubSubAuthorizationPrivate)
{
}

/// Copy-constructor.
QXmppPubSubSubAuthorization::QXmppPubSubSubAuthorization(const QXmppPubSubSubAuthorization &) = default;

QXmppPubSubSubAuthorization::~QXmppPubSubSubAuthorization() = default;

/// Assignment operator.
QXmppPubSubSubAuthorization &QXmppPubSubSubAuthorization::operator=(const QXmppPubSubSubAuthorization &) = default;

///
/// Returns whether the subscription is allowed.
///
std::optional<bool> QXmppPubSubSubAuthorization::allowSubscription() const
{
    return d->allowSubscription;
}

///
/// Sets whether the subscription is allowed.
///
void QXmppPubSubSubAuthorization::setAllowSubscription(std::optional<bool> allowSubscription)
{
    d->allowSubscription = allowSubscription;
}

///
/// Returns the node name of the relevant node.
///
QString QXmppPubSubSubAuthorization::node() const
{
    return d->node;
}

///
/// Sets the node name of the relevant node.
///
void QXmppPubSubSubAuthorization::setNode(const QString &node)
{
    d->node = node;
}

///
/// Returns the JID of the user requesting to subscribe.
///
QString QXmppPubSubSubAuthorization::subscriberJid() const
{
    return d->subscriberJid;
}

///
/// Sets the JID of the user requesting to subscribe.
///
void QXmppPubSubSubAuthorization::setSubscriberJid(const QString &subscriberJid)
{
    d->subscriberJid = subscriberJid;
}

///
/// Returns the subscription ID associated with the subscription request.
///
QString QXmppPubSubSubAuthorization::subid() const
{
    return d->subid;
}

///
/// Sets the subscription ID associated with the subscription request.
///
void QXmppPubSubSubAuthorization::setSubid(const QString &subid)
{
    d->subid = subid;
}

QString QXmppPubSubSubAuthorization::formType() const
{
    return FORM_TYPE_SUBSCRIBE_AUTHORIZATION;
}

bool QXmppPubSubSubAuthorization::parseField(const QXmppDataForm::Field &field)
{
    // ignore hidden fields
    using Type = QXmppDataForm::Field::Type;
    if (field.type() == Type::HiddenField) {
        return false;
    }

    const auto key = field.key();
    const auto value = field.value();

    if (key == ALLOW_SUBSCRIPTION) {
        d->allowSubscription = parseBool(value);
    } else if (key == NODE) {
        d->node = value.toString();
    } else if (key == SUBID) {
        d->subid = value.toString();
    } else if (key == SUBSCRIBER_JID) {
        d->subscriberJid = value.toString();
    } else {
        return false;
    }
    return true;
}

void QXmppPubSubSubAuthorization::serializeForm(QXmppDataForm &form) const
{
    using Type = QXmppDataForm::Field::Type;

    serializeOptional(form, Type::BooleanField, ALLOW_SUBSCRIPTION, d->allowSubscription);
    serializeNullable(form, Type::TextSingleField, NODE, d->node);
    serializeNullable(form, Type::TextSingleField, SUBID, d->subid);
    serializeNullable(form, Type::JidSingleField, SUBSCRIBER_JID, d->subscriberJid);
}
