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

#ifndef QXMPPTRANSFERMANAGER_H
#define QXMPPTRANSFERMANAGER_H

#include "QXmppClientExtension.h"

#include <QDateTime>
#include <QSharedData>
#include <QUrl>
#include <QVariant>

class QTcpSocket;
class QXmppByteStreamIq;
class QXmppIbbCloseIq;
class QXmppIbbDataIq;
class QXmppIbbOpenIq;
class QXmppIq;
class QXmppStreamInitiationIq;
class QXmppTransferFileInfoPrivate;
class QXmppTransferJobPrivate;
class QXmppTransferManager;
class QXmppTransferManagerPrivate;

class QXMPP_EXPORT QXmppTransferFileInfo
{
public:
    QXmppTransferFileInfo();
    QXmppTransferFileInfo(const QXmppTransferFileInfo &other);
    ~QXmppTransferFileInfo();

    QDateTime date() const;
    void setDate(const QDateTime &date);

    QByteArray hash() const;
    void setHash(const QByteArray &hash);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    qint64 size() const;
    void setSize(qint64 size);

    bool isNull() const;
    QXmppTransferFileInfo &operator=(const QXmppTransferFileInfo &other);
    bool operator==(const QXmppTransferFileInfo &other) const;

    /// \cond
    void parse(const QDomElement &element);
    void toXml(QXmlStreamWriter *writer) const;
    /// \endcond

private:
    QSharedDataPointer<QXmppTransferFileInfoPrivate> d;
};

class QXMPP_EXPORT QXmppTransferJob : public QXmppLoggable
{
    Q_OBJECT
    Q_FLAGS(Method Methods)
    /// The job's transfer direction
    Q_PROPERTY(Direction direction READ direction CONSTANT)
    /// The local file URL
    Q_PROPERTY(QUrl localFileUrl READ localFileUrl WRITE setLocalFileUrl NOTIFY localFileUrlChanged)
    /// The remote party's JID
    Q_PROPERTY(QString jid READ jid CONSTANT)
    /// The job's transfer method
    Q_PROPERTY(Method method READ method CONSTANT)
    /// The job's state
    Q_PROPERTY(State state READ state NOTIFY stateChanged)

    /// The name of the file
    Q_PROPERTY(QString fileName READ fileName CONSTANT)
    /// The size of the file
    Q_PROPERTY(qint64 fileSize READ fileSize CONSTANT)

public:
    /// This enum is used to describe the direction of a transfer job.
    enum Direction {
        IncomingDirection,  ///< The file is being received.
        OutgoingDirection   ///< The file is being sent.
    };
    Q_ENUM(Direction)

    /// This enum is used to describe the type of error encountered by a transfer job.
    enum Error {
        NoError = 0,       ///< No error occurred.
        AbortError,        ///< The file transfer was aborted.
        FileAccessError,   ///< An error was encountered trying to access a local file.
        FileCorruptError,  ///< The file is corrupt: the file size or hash do not match.
        ProtocolError      ///< An error was encountered in the file transfer protocol.
    };
    Q_ENUM(Error)

    /// This enum is used to describe a transfer method.
    enum Method {
        NoMethod = 0,      ///< No transfer method.
        InBandMethod = 1,  ///< \xep{0047}: In-Band Bytestreams
        SocksMethod = 2,   ///< \xep{0065}: SOCKS5 Bytestreams
        AnyMethod = 3      ///< Any supported transfer method.
    };
    Q_ENUM(Method)
    Q_DECLARE_FLAGS(Methods, Method)

    /// This enum is used to describe the state of a transfer job.
    enum State {
        OfferState = 0,     ///< The transfer is being offered to the remote party.
        StartState = 1,     ///< The transfer is being connected.
        TransferState = 2,  ///< The transfer is ongoing.
        FinishedState = 3   ///< The transfer is finished.
    };
    Q_ENUM(State)

    ~QXmppTransferJob() override;

    // documentation needs to be here, see https://stackoverflow.com/questions/49192523/
    /// Returns the job's transfer direction.
    QXmppTransferJob::Direction direction() const;
    /// Returns the remote party's JID.
    QString jid() const;
    /// Returns the job's transfer method.
    QXmppTransferJob::Method method() const;
    /// Returns the job's state.
    QXmppTransferJob::State state() const;

    QXmppTransferJob::Error error() const;
    QString sid() const;
    qint64 speed() const;

    // XEP-0096 : File transfer
    QXmppTransferFileInfo fileInfo() const;
    // documentation needs to be here, see https://stackoverflow.com/questions/49192523/
    /// Returns the local file URL.
    QUrl localFileUrl() const;
    void setLocalFileUrl(const QUrl &localFileUrl);

    /// \cond
    QDateTime fileDate() const;
    QByteArray fileHash() const;
    QString fileName() const;
    qint64 fileSize() const;
    /// \endcond

Q_SIGNALS:
    /// This signal is emitted when an error is encountered while
    /// processing the transfer job.
    void error(QXmppTransferJob::Error error);

    /// This signal is emitted when the transfer job is finished.
    ///
    /// You can determine if the job completed successfully by testing whether
    /// error() returns QXmppTransferJob::NoError.
    ///
    /// Note: Do not delete the job in the slot connected to this signal,
    /// instead use deleteLater().
    void finished();

    /// This signal is emitted when the local file URL changes.
    void localFileUrlChanged(const QUrl &localFileUrl);

    /// This signal is emitted to indicate the progress of this transfer job.
    void progress(qint64 done, qint64 total);

    /// This signal is emitted when the transfer job changes state.
    void stateChanged(QXmppTransferJob::State state);

public Q_SLOTS:
    void abort();
    void accept(const QString &filePath);
    void accept(QIODevice *output);

private Q_SLOTS:
    void _q_terminated();

private:
    QXmppTransferJob(const QString &jid, QXmppTransferJob::Direction direction, QXmppClient *client, QObject *parent);
    void setState(QXmppTransferJob::State state);
    void terminate(QXmppTransferJob::Error error);

    QXmppTransferJobPrivate *const d;
    friend class QXmppTransferManager;
    friend class QXmppTransferManagerPrivate;
    friend class QXmppTransferIncomingJob;
    friend class QXmppTransferOutgoingJob;
};

class QXMPP_EXPORT QXmppTransferManager : public QXmppClientExtension
{
    Q_OBJECT

    /// The JID of the bytestream proxy to use for outgoing transfers
    Q_PROPERTY(QString proxy READ proxy WRITE setProxy)
    /// Whether the proxy will systematically be used for outgoing SOCKS5 bytestream transfers
    Q_PROPERTY(bool proxyOnly READ proxyOnly WRITE setProxyOnly)
    /// The supported stream methods
    Q_PROPERTY(QXmppTransferJob::Methods supportedMethods READ supportedMethods WRITE setSupportedMethods)

public:
    QXmppTransferManager();
    ~QXmppTransferManager() override;

    // documentation needs to be here, see https://stackoverflow.com/questions/49192523/
    /// Return the JID of the bytestream proxy to use for outgoing transfers.
    QString proxy() const;
    void setProxy(const QString &proxyJid);

    // documentation needs to be here, see https://stackoverflow.com/questions/49192523/
    /// Return whether the proxy will systematically be used for outgoing
    /// SOCKS5 bytestream transfers.
    bool proxyOnly() const;
    void setProxyOnly(bool proxyOnly);

    // documentation needs to be here, see https://stackoverflow.com/questions/49192523/
    /// Return the supported stream methods.
    ///
    /// The methods are a combination of zero or more QXmppTransferJob::Method.
    QXmppTransferJob::Methods supportedMethods() const;
    void setSupportedMethods(QXmppTransferJob::Methods methods);

    /// \cond
    QStringList discoveryFeatures() const override;
    bool handleStanza(const QDomElement &element) override;
    /// \endcond

Q_SIGNALS:
    /// This signal is emitted when a new file transfer offer is received.
    ///
    /// To accept the transfer job, call the job's QXmppTransferJob::accept() method.
    /// To refuse the transfer job, call the job's QXmppTransferJob::abort() method.
    void fileReceived(QXmppTransferJob *job);

    /// This signal is emitted whenever a transfer job is started.
    void jobStarted(QXmppTransferJob *job);

    /// This signal is emitted whenever a transfer job is finished.
    ///
    /// \sa QXmppTransferJob::finished()
    void jobFinished(QXmppTransferJob *job);

public Q_SLOTS:
    QXmppTransferJob *sendFile(const QString &jid, const QString &filePath, const QString &description = QString());
    QXmppTransferJob *sendFile(const QString &jid, QIODevice *device, const QXmppTransferFileInfo &fileInfo, const QString &sid = QString());

protected:
    /// \cond
    void setClient(QXmppClient *client) override;
    /// \endcond

private Q_SLOTS:
    void _q_iqReceived(const QXmppIq &);
    void _q_jobDestroyed(QObject *object);
    void _q_jobError(QXmppTransferJob::Error error);
    void _q_jobFinished();
    void _q_jobStateChanged(QXmppTransferJob::State state);
    void _q_socksServerConnected(QTcpSocket *socket, const QString &hostName, quint16 port);

private:
    QXmppTransferManagerPrivate *d;

    void byteStreamIqReceived(const QXmppByteStreamIq &);
    void byteStreamResponseReceived(const QXmppIq &);
    void byteStreamResultReceived(const QXmppByteStreamIq &);
    void byteStreamSetReceived(const QXmppByteStreamIq &);
    void ibbCloseIqReceived(const QXmppIbbCloseIq &);
    void ibbDataIqReceived(const QXmppIbbDataIq &);
    void ibbOpenIqReceived(const QXmppIbbOpenIq &);
    void ibbResponseReceived(const QXmppIq &);
    void streamInitiationIqReceived(const QXmppStreamInitiationIq &);
    void streamInitiationResultReceived(const QXmppStreamInitiationIq &);
    void streamInitiationSetReceived(const QXmppStreamInitiationIq &);
    void socksServerSendOffer(QXmppTransferJob *job);

    friend class QXmppTransferManagerPrivate;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QXmppTransferJob::Methods)

#endif
