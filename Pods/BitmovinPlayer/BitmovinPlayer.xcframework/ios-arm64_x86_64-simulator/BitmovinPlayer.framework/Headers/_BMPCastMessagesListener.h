//
// Bitmovin Player iOS SDK
// Copyright (C) 2017, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
@class BMPAudioAddedEvent;
@class BMPAudioRemovedEvent;
@class BMPSubtitleAddedEvent;
@class BMPSubtitleRemovedEvent;
@class _BMPRemotePlayerStateEvent;
@class _BMPGetAvailableSubtitlesEvent;
@class _BMPGetAvailableAudioEvent;

NS_ASSUME_NONNULL_BEGIN

/// :nodoc:
NS_SWIFT_NAME(_CastMessagesListener)
@protocol _BMPCastMessagesListener <NSObject>
@optional
- (void)onGetAvailableAudio:(_BMPGetAvailableAudioEvent *)event;
- (void)onGetAvailableSubtitles:(_BMPGetAvailableSubtitlesEvent *)event;
- (void)onRemotePlayerState:(_BMPRemotePlayerStateEvent *)event;
- (void)onCurrentTimeApproximation:(NSTimeInterval)currentTime;
@end

NS_ASSUME_NONNULL_END
