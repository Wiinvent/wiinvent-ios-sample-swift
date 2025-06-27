//
// Bitmovin Player iOS SDK
// Copyright (C) 2017, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
@class BMPSubtitleTrack;
@class BMPAudioTrack;

NS_ASSUME_NONNULL_BEGIN

/// :nodoc:
NS_SWIFT_NAME(_RemotePlayerState)
@interface _BMPRemotePlayerState : NSObject <NSCopying>
@property (nonatomic) BOOL isReady;
@property (nonatomic) BOOL isPlaying;
@property (nonatomic) BOOL hasEnded;
@property (nonatomic) BOOL isMuted;
@property (nonatomic) BOOL isStalled;
@property (nonatomic) BOOL isLive;
@property (nonatomic) NSInteger volume;
@property (nonatomic) NSTimeInterval currentTime;
@property (nonatomic) NSTimeInterval duration;
@property (nonatomic) NSTimeInterval maxTimeShift;
@property (nonatomic) NSTimeInterval timeShift;
@property (nonatomic, nullable, copy) BMPSubtitleTrack *subtitleTrack;
@property (nonatomic, nullable, copy) BMPAudioTrack *audioTrack;
@end

NS_ASSUME_NONNULL_END
