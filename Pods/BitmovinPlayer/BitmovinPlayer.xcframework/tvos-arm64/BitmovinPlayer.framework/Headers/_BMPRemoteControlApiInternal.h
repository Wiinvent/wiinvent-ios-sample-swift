//
// Bitmovin Player iOS SDK
// Copyright (C) 2021, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <BitmovinPlayer/BMPRemoteControlApi.h>
@class _BMPPlaybackPosition;

NS_ASSUME_NONNULL_BEGIN

/// :nodoc:
NS_SWIFT_NAME(_RemoteControlApiInternal)
@protocol _BMPRemoteControlApiInternal <BMPRemoteControlApi>
@property (nonatomic, readonly) BOOL isRemotePlayerStateAvailable;

- (void)loadMediaInfoWithPlaybackPosition:(nullable _BMPPlaybackPosition *)playbackPosition autoplay:(BOOL)autoplay;
- (void)showCastDialog;
@end

NS_ASSUME_NONNULL_END
