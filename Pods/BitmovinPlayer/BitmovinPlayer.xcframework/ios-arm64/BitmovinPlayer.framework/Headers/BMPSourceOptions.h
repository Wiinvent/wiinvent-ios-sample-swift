//
// Bitmovin Player iOS SDK
// Copyright (C) 2019, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import <BitmovinPlayer/_BMPJsonEncodable.h>
#import <BitmovinPlayer/BMPTimelineReferencePoint.h>

NS_ASSUME_NONNULL_BEGIN
NS_SWIFT_NAME(SourceOptions)
@interface BMPSourceOptions : NSObject <NSCopying, _BMPJsonEncodable>
/**
 The position where the stream should be started. Number can be positive or negative depending on the used TimelineReferencePoint.
 Invalid numbers will be corrected according to the stream boundaries.
 For VOD this is applied at the time the stream is loaded, for LIVE when the playback starts.

 Default: NAN
 */
@property (nonatomic) NSTimeInterval startOffset;
/**
 Timeline reference point to calculate BMPSourceOptions.startOffset from.

 Default for live: BMPTimelineReferencePointEnd
 Default for VOD: BMPTimelineReferencePointStart
 */
@property (nonatomic) BMPTimelineReferencePoint startOffsetTimelineReference;
/**
 The identifier for the `SourceConfig` in a SharePlay session.
 This identifier is used:
 - to validate that received SharePlay commands are intended for the currently active `Source`'s `SourceConfig` when receiving them.
 - for caching the playback state within the SharePlay session
   If there is a stored playback state for the given identifier, it will be applied when a `SourceConfig` with the same identifier becomes active.

 @note The identifier must match for all participants in the SharePlay session.
 If no identifier is provided, the URL of the `SourceConfig` will be used.
 */
@property (nonatomic, nullable, copy) NSString *sharePlayIdentifier;

- (instancetype)initWithStartOffset:(NSTimeInterval)startOffset
  startOffsetTimelineReferencePoint:(BMPTimelineReferencePoint)startOffsetTimelineReference;
- (instancetype)initWithStartOffset:(NSTimeInterval)startOffset
  startOffsetTimelineReferencePoint:(BMPTimelineReferencePoint)startOffsetTimelineReference
                sharePlayIdentifier:(nullable NSString *)sharePlayIdentifier NS_DESIGNATED_INITIALIZER;
@end

NS_ASSUME_NONNULL_END
