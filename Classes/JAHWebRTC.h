//
//  JAHWebRTC.h
//  
//
//  Created by Jon Hjelle on 1/20/14.
//  Copyright (c) 2014 Jon Hjelle. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "RTCSessionDescription.h"
#import "RTCICECandidate.h"
#import "RTCMediaStream.h"
#import "RTCTypes.h"

@class RTCICEServer;

@protocol JAHSignalDelegate;

@interface JAHWebRTC : NSObject

@property (nonatomic, weak) id <JAHSignalDelegate> signalDelegate;

- (id)initAllowingVideo:(BOOL)allowVideo;

- (void)addPeerConnectionForID:(NSString*)identifier;
- (void)removePeerConnectionForID:(NSString*)identifier;

- (void)createOfferForPeerWithID:(NSString*)peerID;
- (void)setRemoteDescription:(RTCSessionDescription*)remoteSDP forPeerWithID:(NSString*)peerID receiver:(BOOL)isReceiver;
- (void)addICECandidate:(RTCICECandidate*)candidate forPeerWithID:(NSString*)peerID;

// Add a STUN or TURN server, adding a STUN server replaces the previous STUN server, adding a TURN server appends it to the list
- (void)addICEServer:(RTCICEServer*)server;

// The WebRTC stream captured locally that will be sent to peers, useful for displaying a preview of the local camera
// in an RTCVideoRenderer and muting or blacking out th stream sent to peers
@property (readonly, nonatomic) RTCMediaStream* localMediaStream;

@end


@protocol JAHSignalDelegate <NSObject>

- (void)sendSDPOffer:(RTCSessionDescription*)offer forPeerWithID:(NSString*)peerID;
- (void)sendSDPAnswer:(RTCSessionDescription*)answer forPeerWithID:(NSString*)peerID;
- (void)sendICECandidate:(RTCICECandidate*)candidate forPeerWithID:(NSString*)peerID;
- (void)ICEConnectionStateChanged:(RTCICEConnectionState)state forPeerWithID:(NSString*)peerID;

- (void)addedStream:(RTCMediaStream*)stream forPeerWithID:(NSString*)peerID;
- (void)removedStream:(RTCMediaStream*)stream forPeerWithID:(NSString*)peerID;

@end