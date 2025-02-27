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

#include "QXmppPubSubMetadata.h"

#include <QDateTime>

// helper for std::visit
template<class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};
// explicit deduction guide (not needed as of C++20)
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

const auto FORM_TYPE_METADATA = QStringLiteral("http://jabber.org/protocol/pubsub#metadata");

const auto CONTACT_JIDS = QStringLiteral("pubsub#contact");
const auto CREATION_DATE = QStringLiteral("pubsub#creation_date");
const auto CREATOR_JID = QStringLiteral("pubsub#creator");
const auto DESCRIPTION = QStringLiteral("pubsub#description");
const auto LANGUAGE = QStringLiteral("pubsub#language");
const auto ACCESS_MODEL = QStringLiteral("pubsub#access_model");
const auto PUBLISH_MODEL = QStringLiteral("pubsub#publish_model");
const auto SUBSCRIBER_COUNT = QStringLiteral("pubsub#num_subscribers");
const auto OWNER_JIDS = QStringLiteral("pubsub#owner");
const auto PUBLISHER_JIDS = QStringLiteral("pubsub#publisher");
const auto TITLE = QStringLiteral("pubsub#title");
const auto TYPE = QStringLiteral("pubsub#type");
const auto MAX_ITEMS = QStringLiteral("pubsub#max_items");

class QXmppPubSubMetadataPrivate : public QSharedData
{
public:
    QStringList contactJids;
    QDateTime creationDate;
    QString creatorJid;
    QString description;
    QString language;
    std::optional<QXmppPubSubNodeConfig::AccessModel> accessModel;
    std::optional<QXmppPubSubNodeConfig::PublishModel> publishModel;
    std::optional<quint64> subscriberCount;
    QStringList ownerJids;
    QStringList publisherJids;
    QString title;
    QString type;
    QXmppPubSubMetadata::ItemLimit maxItems = QXmppPubSubMetadata::Unset();
};

QXmppPubSubMetadata::QXmppPubSubMetadata()
    : d(new QXmppPubSubMetadataPrivate)
{
}

QXmppPubSubMetadata::QXmppPubSubMetadata(const QXmppPubSubMetadata &) = default;

QXmppPubSubMetadata::~QXmppPubSubMetadata() = default;

QXmppPubSubMetadata &QXmppPubSubMetadata::operator=(const QXmppPubSubMetadata &) = default;

QStringList QXmppPubSubMetadata::contactJids() const
{
    return d->contactJids;
}

void QXmppPubSubMetadata::setContactJids(const QStringList &contactJids)
{
    d->contactJids = contactJids;
}

QDateTime QXmppPubSubMetadata::creationDate() const
{
    return d->creationDate;
}

void QXmppPubSubMetadata::setCreationDate(const QDateTime &creationDate)
{
    d->creationDate = creationDate;
}

QString QXmppPubSubMetadata::creatorJid() const
{
    return d->creatorJid;
}

void QXmppPubSubMetadata::setCreatorJid(const QString &creatorJid)
{
    d->creatorJid = creatorJid;
}

QString QXmppPubSubMetadata::description() const
{
    return d->description;
}

void QXmppPubSubMetadata::setDescription(const QString &description)
{
    d->description = description;
}

QString QXmppPubSubMetadata::language() const
{
    return d->language;
}

void QXmppPubSubMetadata::setLanguage(const QString &language)
{
    d->language = language;
}

std::optional<QXmppPubSubNodeConfig::AccessModel> QXmppPubSubMetadata::accessModel() const
{
    return d->accessModel;
}

void QXmppPubSubMetadata::setAccessModel(std::optional<QXmppPubSubNodeConfig::AccessModel> accessModel)
{
    d->accessModel = accessModel;
}

std::optional<QXmppPubSubNodeConfig::PublishModel> QXmppPubSubMetadata::publishModel() const
{
    return d->publishModel;
}

void QXmppPubSubMetadata::setPublishModel(std::optional<QXmppPubSubNodeConfig::PublishModel> publishModel)
{
    d->publishModel = publishModel;
}

std::optional<quint64> QXmppPubSubMetadata::numberOfSubscribers() const
{
    return d->subscriberCount;
}

void QXmppPubSubMetadata::setNumberOfSubscribers(const std::optional<quint64> &numberOfSubscribers)
{
    d->subscriberCount = numberOfSubscribers;
}

QStringList QXmppPubSubMetadata::ownerJids() const
{
    return d->ownerJids;
}

void QXmppPubSubMetadata::setOwnerJids(const QStringList &ownerJids)
{
    d->ownerJids = ownerJids;
}

QStringList QXmppPubSubMetadata::publisherJids() const
{
    return d->publisherJids;
}

void QXmppPubSubMetadata::setPublisherJids(const QStringList &publisherJids)
{
    d->publisherJids = publisherJids;
}

QString QXmppPubSubMetadata::title() const
{
    return d->title;
}

void QXmppPubSubMetadata::setTitle(const QString &title)
{
    d->title = title;
}

QString QXmppPubSubMetadata::type() const
{
    return d->type;
}

void QXmppPubSubMetadata::setType(const QString &type)
{
    d->type = type;
}

auto QXmppPubSubMetadata::maxItems() const -> ItemLimit
{
    return d->maxItems;
}

void QXmppPubSubMetadata::setMaxItems(ItemLimit maxItems)
{
    d->maxItems = maxItems;
}

QString QXmppPubSubMetadata::formType() const
{
    return FORM_TYPE_METADATA;
}

bool QXmppPubSubMetadata::parseField(const QXmppDataForm::Field &field)
{
    // ignore hidden fields
    using Type = QXmppDataForm::Field::Type;
    if (field.type() == Type::HiddenField) {
        return false;
    }

    const auto key = field.key();
    const auto value = field.value();

    if (key == CONTACT_JIDS) {
        d->contactJids = value.toStringList();
    } else if (key == CREATION_DATE) {
        d->creationDate = QDateTime::fromString(field.value().toString(), Qt::ISODate).toUTC();
    } else if (key == CREATOR_JID) {
        d->creatorJid = value.toString();
    } else if (key == DESCRIPTION) {
        d->description = value.toString();
    } else if (key == LANGUAGE) {
        d->language = value.toString();
    } else if (key == ACCESS_MODEL) {
        d->accessModel = QXmppPubSubNodeConfig::accessModelFromString(value.toString());
    } else if (key == PUBLISH_MODEL) {
        d->publishModel = QXmppPubSubNodeConfig::publishModelFromString(value.toString());
    } else if (key == SUBSCRIBER_COUNT) {
        d->subscriberCount = parseULongLong(value);
    } else if (key == OWNER_JIDS) {
        d->ownerJids = value.toStringList();
    } else if (key == PUBLISHER_JIDS) {
        d->publisherJids = value.toStringList();
    } else if (key == TITLE) {
        d->title = value.toString();
    } else if (key == TYPE) {
        d->type = value.toString();
    } else if (key == MAX_ITEMS) {
        const auto string = value.toString();
        if (string == QStringLiteral("max")) {
            d->maxItems = Max();
        } else {
            bool ok;
            if (const auto maxItems = field.value().toString().toULongLong(&ok); ok) {
                d->maxItems = maxItems;
            }
        }
    } else {
        return false;
    }

    return true;
}

void QXmppPubSubMetadata::serializeForm(QXmppDataForm &form) const
{
    using Type = QXmppDataForm::Field::Type;
    const auto numberToString = [](quint64 value) {
        return QString::number(value);
    };

    serializeEmptyable(form, Type::JidMultiField, CONTACT_JIDS, d->contactJids);
    serializeDatetime(form, CREATION_DATE, d->creationDate);
    serializeNullable(form, Type::JidSingleField, CREATOR_JID, d->creatorJid);
    serializeNullable(form, Type::TextSingleField, DESCRIPTION, d->description);
    serializeNullable(form, Type::TextSingleField, LANGUAGE, d->language);
    serializeOptional(form, Type::ListSingleField, ACCESS_MODEL, d->accessModel, QXmppPubSubNodeConfig::accessModelToString);
    serializeOptional(form, Type::ListSingleField, PUBLISH_MODEL, d->publishModel, QXmppPubSubNodeConfig::publishModelToString);
    serializeOptional(form, Type::TextSingleField, SUBSCRIBER_COUNT, d->subscriberCount, numberToString);
    serializeEmptyable(form, Type::JidMultiField, OWNER_JIDS, d->ownerJids);
    serializeEmptyable(form, Type::JidMultiField, PUBLISHER_JIDS, d->publisherJids);
    serializeNullable(form, Type::TextSingleField, TITLE, d->title);
    serializeNullable(form, Type::TextSingleField, TYPE, d->type);
    serializeNullable(form, Type::TextSingleField, MAX_ITEMS,
                      std::visit(overloaded {
                                     [](Unset) { return QString(); },
                                     [](quint64 value) { return QString::number(value); },
                                     [](Max) { return QStringLiteral("max"); },
                                 },
                                 d->maxItems));
}
