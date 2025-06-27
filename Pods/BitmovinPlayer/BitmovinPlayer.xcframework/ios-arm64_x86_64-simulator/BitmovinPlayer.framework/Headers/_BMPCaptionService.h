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

NS_ASSUME_NONNULL_BEGIN

/// :nodoc:
NS_SWIFT_NAME(_CaptionService)
@protocol _BMPCaptionService <_BMPService>
@property (nonatomic, readonly) NSArray<BMPSubtitleTrack *> *availableSubtitles;
@property (nonatomic, readonly) BMPSubtitleTrack *subtitle;

- (void)addSubtitle:(BMPSubtitleTrack *)subtitleTrack;
- (void)removeSubtitle:(NSString *)subtitleTrackID;
- (void)setSubtitleWithIdentifier:(nullable NSString *)subtitleTrackID;
@end

NS_ASSUME_NONNULL_END
