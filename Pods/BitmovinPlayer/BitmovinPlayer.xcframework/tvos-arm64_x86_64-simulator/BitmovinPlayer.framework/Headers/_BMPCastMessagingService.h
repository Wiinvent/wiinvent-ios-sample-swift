//
// Bitmovin Player iOS SDK
// Copyright (C) 2017, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import "_BMPService.h"
@class BMPSubtitleTrack;
@class _BMPRemotePlayerStateEvent;

@protocol _BMPCastMessagesListener;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(_CastMessagingService)
@protocol _BMPCastMessagingService <_BMPService>
/**
 * Adds an event listener
 *
 * @param listener The event listener to be added.
 */
- (void)addEventListener:(id<_BMPCastMessagesListener>)listener NS_SWIFT_NAME(add(listener:));

/**
 * Removes an event listener.
 *
 * @param listener The event listener to be removed.
 */
- (void)removeEventListener:(id<_BMPCastMessagesListener>)listener NS_SWIFT_NAME(remove(listener:));

/**
 * Sends the setSubtitle API call to the cast device
 */
- (void)sendSetSubtitle:(NSString *)subtitleIdentifier;

/**
 * Sends the setSubtitle API call to the cast device in a way that the subtitles are turned off
 */
- (void)sendSetSubtitleToOff;

/**
 * Sends the setAudio API call to the cast device
 */
- (void)sendSetAudio:(NSString *)audioTrackIdentifier;

/**
 * Sends the setPlaybackSpeed API call to the cast device
 */
 - (void)sendSetPlaybackSpeed:(float)playbackSpeed;

/**
 * Sends the timeShift API call to the cast device
 */
- (void)sendTimeShift:(NSTimeInterval)offset completionHandler:(void(^)(void))completionHandler;
@end

NS_ASSUME_NONNULL_END
