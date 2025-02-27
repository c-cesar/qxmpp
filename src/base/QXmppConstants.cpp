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

#include "QXmppConstants_p.h"

const char* ns_stream = "http://etherx.jabber.org/streams";
const char* ns_client = "jabber:client";
const char* ns_server = "jabber:server";
const char* ns_roster = "jabber:iq:roster";
const char* ns_tls = "urn:ietf:params:xml:ns:xmpp-tls";
const char* ns_sasl = "urn:ietf:params:xml:ns:xmpp-sasl";
const char* ns_bind = "urn:ietf:params:xml:ns:xmpp-bind";
const char* ns_session = "urn:ietf:params:xml:ns:xmpp-session";
const char* ns_stanza = "urn:ietf:params:xml:ns:xmpp-stanzas";
const char* ns_pre_approval = "urn:xmpp:features:pre-approval";
const char* ns_rosterver = "urn:xmpp:features:rosterver";
// XEP-0009: Jabber-RPC
const char* ns_rpc = "jabber:iq:rpc";
// XEP-0020: Feature Negotiation
const char* ns_feature_negotiation = "http://jabber.org/protocol/feature-neg";
// XEP-0027: Current Jabber OpenPGP Usage
const char* ns_legacy_openpgp = "jabber:x:encrypted";
// XEP-0030: Service Discovery
const char* ns_disco_info = "http://jabber.org/protocol/disco#info";
const char* ns_disco_items = "http://jabber.org/protocol/disco#items";
// XEP-0033: Extended Stanza Addressing
const char* ns_extended_addressing = "http://jabber.org/protocol/address";
// XEP-0045: Multi-User Chat
const char* ns_muc = "http://jabber.org/protocol/muc";
const char* ns_muc_admin = "http://jabber.org/protocol/muc#admin";
const char* ns_muc_owner = "http://jabber.org/protocol/muc#owner";
const char* ns_muc_user = "http://jabber.org/protocol/muc#user";
// XEP-0047: In-Band Bytestreams
const char* ns_ibb = "http://jabber.org/protocol/ibb";
// XEP-0049: Private XML Storage
const char* ns_private = "jabber:iq:private";
// XEP-0054: vcard-temp
const char* ns_vcard = "vcard-temp";
// XEP-0059: Result Set Management
const char* ns_rsm = "http://jabber.org/protocol/rsm";
// XEP-0060: Publish-Subscribe
const char* ns_pubsub = "http://jabber.org/protocol/pubsub";
const char* ns_pubsub_errors = "http://jabber.org/protocol/pubsub#errors";
const char* ns_pubsub_event = "http://jabber.org/protocol/pubsub#event";
const char* ns_pubsub_owner = "http://jabber.org/protocol/pubsub#owner";
const char* ns_pubsub_rsm = "http://jabber.org/protocol/pubsub#rsm";
// XEP-0065: SOCKS5 Bytestreams
const char* ns_bytestreams = "http://jabber.org/protocol/bytestreams";
// XEP-0066: Out of Band Data
const char* ns_oob = "jabber:x:oob";
// XEP-0071: XHTML-IM
const char* ns_xhtml = "http://www.w3.org/1999/xhtml";
const char* ns_xhtml_im = "http://jabber.org/protocol/xhtml-im";
// XEP-0077: In-Band Registration
const char* ns_register = "jabber:iq:register";
const char* ns_register_feature = "http://jabber.org/features/iq-register";
// XEP-0078: Non-SASL Authentication
const char* ns_auth = "jabber:iq:auth";
const char* ns_authFeature = "http://jabber.org/features/iq-auth";
// XEP-0080: User Location
const char* ns_geoloc = "http://jabber.org/protocol/geoloc";
const char* ns_geoloc_notify = "http://jabber.org/protocol/geoloc+notify";
// XEP-0085: Chat State Notifications
const char* ns_chat_states = "http://jabber.org/protocol/chatstates";
// XEP-0091: Legacy Delayed Delivery
const char* ns_legacy_delayed_delivery = "jabber:x:delay";
// XEP-0092: Software Version
const char* ns_version = "jabber:iq:version";
const char* ns_data = "jabber:x:data";
// XEP-0095: Stream Initiation
const char* ns_stream_initiation = "http://jabber.org/protocol/si";
const char* ns_stream_initiation_file_transfer = "http://jabber.org/protocol/si/profile/file-transfer";
// XEP-0108: User Activity
const char* ns_activity = "http://jabber.org/protocol/activity";
// XEP-0115: Entity Capabilities
const char* ns_capabilities = "http://jabber.org/protocol/caps";
// XEP-0118: User Tune
const char* ns_tune = "http://jabber.org/protocol/tune";
const char* ns_tune_notify = "http://jabber.org/protocol/tune+notify";
// XEP-0136: Message Archiving
const char* ns_archive = "urn:xmpp:archive";
// XEP-0138: Stream Compression
const char* ns_compress = "http://jabber.org/protocol/compress";
const char* ns_compressFeature = "http://jabber.org/features/compress";
// XEP-0145: Annotations
const char* ns_rosternotes = "storage:rosternotes";
// XEP-0153: vCard-Based Avatars
const char* ns_vcard_update = "vcard-temp:x:update";
// XEP-0158: CAPTCHA Forms
const char* ns_captcha = "urn:xmpp:captcha";
// XEP-0166: Jingle
const char* ns_jingle = "urn:xmpp:jingle:1";
const char* ns_jingle_raw_udp = "urn:xmpp:jingle:transports:raw-udp:1";
const char* ns_jingle_ice_udp = "urn:xmpp:jingle:transports:ice-udp:1";
const char* ns_jingle_rtp = "urn:xmpp:jingle:apps:rtp:1";
const char* ns_jingle_rtp_audio = "urn:xmpp:jingle:apps:rtp:audio";
const char* ns_jingle_rtp_video = "urn:xmpp:jingle:apps:rtp:video";
// XEP-0184: Message Receipts
const char* ns_message_receipts = "urn:xmpp:receipts";
// XEP-0198: Stream Management
const char* ns_stream_management = "urn:xmpp:sm:3";
// XEP-0199: XMPP Ping
const char* ns_ping = "urn:xmpp:ping";
// XEP-0202: Entity Time
const char* ns_entity_time = "urn:xmpp:time";
// XEP-0203: Delayed Delivery
const char* ns_delayed_delivery = "urn:xmpp:delay";
// XEP-0220: Server Dialback
const char* ns_server_dialback = "jabber:server:dialback";
// XEP-0221: Data Forms Media Element
const char* ns_media_element = "urn:xmpp:media-element";
// XEP-0224: Attention
const char* ns_attention = "urn:xmpp:attention:0";
// XEP-0231: Bits of Binary
const char* ns_bob = "urn:xmpp:bob";
// XEP-0249: Direct MUC Invitations
const char* ns_conference = "jabber:x:conference";
// XEP-0280: Message Carbons
const char* ns_carbons = "urn:xmpp:carbons:2";
// XEP-0297: Stanza Forwarding
const char* ns_forwarding = "urn:xmpp:forward:0";
// XEP-0308: Last Message Correction
const char* ns_message_correct = "urn:xmpp:message-correct:0";
// XEP-0313: Message Archive Management
const char* ns_mam = "urn:xmpp:mam:2";
// XEP-0319: Last User Interaction in Presence
const char* ns_idle = "urn:xmpp:idle:1";
// XEP-0333: Chat Markers
const char* ns_chat_markers = "urn:xmpp:chat-markers:0";
// XEP-0334: Message Processing Hints
const char* ns_message_processing_hints = "urn:xmpp:hints";
// XEP-0352: Client State Indication
const char* ns_csi = "urn:xmpp:csi:0";
// XEP-0357: Push Notifications
const char* ns_push = "urn:xmpp:push:0";
// XEP-0359: Unique and Stable Stanza IDs
const char* ns_sid = "urn:xmpp:sid:0";
// XEP-0363: HTTP File Upload
const char* ns_http_upload = "urn:xmpp:http:upload:0";
// XEP-0364: Current Off-the-Record Messaging Usage
const char* ns_otr = "urn:xmpp:otr:0";
// XEP-0367: Message Attaching
const char* ns_message_attaching = "urn:xmpp:message-attaching:1";
// XEP-0369: Mediated Information eXchange (MIX)
const char* ns_mix = "urn:xmpp:mix:core:1";
const char* ns_mix_create_channel = "urn:xmpp:mix:core:1#create-channel";
const char* ns_mix_searchable = "urn:xmpp:mix:core:1#searchable";
const char* ns_mix_node_messages = "urn:xmpp:mix:nodes:messages";
const char* ns_mix_node_participants = "urn:xmpp:mix:nodes:participants";
const char* ns_mix_node_presence = "urn:xmpp:mix:nodes:presence";
const char* ns_mix_node_config = "urn:xmpp:mix:nodes:config";
const char* ns_mix_node_info = "urn:xmpp:mix:nodes:info";
// XEP-0373: OpenPGP for XMPP
const char* ns_ox = "urn:xmpp:openpgp:0";
// XEP-0380: Explicit Message Encryption
const char* ns_eme = "urn:xmpp:eme:0";
// XEP-0382: Spoiler messages
const char* ns_spoiler = "urn:xmpp:spoiler:0";
// XEP-0384: OMEMO Encryption
const char* ns_omemo = "eu.siacs.conversations.axolotl";
const char* ns_omemo_1 = "urn:xmpp:omemo:1";
const char* ns_omemo_2 = "urn:xmpp:omemo:2";
// XEP-0405: Mediated Information eXchange (MIX): Participant Server Requirements
const char* ns_mix_pam = "urn:xmpp:mix:pam:1";
const char* ns_mix_roster = "urn:xmpp:mix:roster:0";
const char* ns_mix_presence = "urn:xmpp:presence:0";
// XEP-0407: Mediated Information eXchange (MIX): Miscellaneous Capabilities
const char* ns_mix_misc = "urn:xmpp:mix:misc:0";
// XEP-0428: Fallback Indication
const char* ns_fallback_indication = "urn:xmpp:fallback:0";
// XEP-0434: Trust Messages (TM)
const char* ns_tm = "urn:xmpp:tm:1";
// XEP-0450: Automatic Trust Management (ATM)
const char* ns_atm = "urn:xmpp:atm:1";
