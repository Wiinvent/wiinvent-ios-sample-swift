//
// Bitmovin Player iOS SDK
// Copyright (C) 2017, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import "_BMPService.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(_PlaybackService)
@protocol _BMPPlaybackService <_BMPService>
@property (nonatomic) NSInteger volume;
@property (nonatomic) float playbackSpeed;
@property (nonatomic) NSUInteger maxSelectableBitrate;
@property (nonatomic, readonly) float currentVideoFrameRate;
@property (nonatomic, readonly) BOOL isMuted;
@property (nonatomic, readonly) BOOL isPaused;
@property (nonatomic, readonly) BOOL isPlaying;
@property (nonatomic, readonly) BOOL isLive;
@property (nonatomic, readonly) BOOL isAirPlayActive;
@property (nonatomic, readonly) BOOL isAirPlayAvailable;
@property (nonatomic, readonly) BOOL isWaiting;
@property (nonatomic, readonly) BOOL canStartPlaybackImmediately;

- (void)play;
- (void)playImmediately;
- (void)pause;
- (void)pauseWithSuppressEvents:(BOOL)suppressEvents NS_SWIFT_NAME(pause(suppressEvents:));
- (void)mute;
- (void)unmute;
@end

NS_ASSUME_NONNULL_END
