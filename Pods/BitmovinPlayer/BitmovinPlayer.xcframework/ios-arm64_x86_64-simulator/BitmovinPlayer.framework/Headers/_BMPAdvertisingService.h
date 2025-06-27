//
// Bitmovin Player iOS SDK
// Copyright (C) 2017, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import "_BMPService.h"
#import <UIKit/UIKit.h>

@class BMPAdItem;

NS_ASSUME_NONNULL_BEGIN

/// :nodoc:
NS_SWIFT_NAME(_AdvertisingService)
@protocol _BMPAdvertisingService <_BMPService>
@property (nonatomic, readonly) BOOL isAd;
@property (nonatomic, readonly) BOOL isMuted;
@property (nonatomic, readonly) BOOL isPlaying;
@property (nonatomic, readonly) BOOL isPaused;
@property (nonatomic, readonly) NSTimeInterval currentTime;
@property (nonatomic, readonly) NSTimeInterval duration;

- (void)skipAd;
- (void)scheduleAd:(BMPAdItem *)adItem;
- (void)registerAdContainer:(UIView *)adContainer;
- (void)play;
- (void)pause;
- (void)mute;
- (void)unmute;
- (void)setVolume:(NSInteger)volume;
- (BOOL)hasAdsForPlaybackTime:(NSTimeInterval)playbackTime;
@end

NS_ASSUME_NONNULL_END
