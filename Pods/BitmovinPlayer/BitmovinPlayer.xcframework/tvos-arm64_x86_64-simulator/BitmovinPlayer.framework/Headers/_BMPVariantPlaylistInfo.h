//
// Bitmovin Player iOS SDK
// Copyright (C) 2019, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import "_BMPStartTimeHaving.h"
#import "_BMPSegmentInfo.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(_VariantPlaylistInfo)
@interface _BMPVariantPlaylistInfo : NSObject

/**
 #EXT-X-MEDIA-SEQUENCE number.
 */
@property (nonatomic, readonly) NSInteger mediaSequence;

/**
 #EXTINF media segments represented in the same order as in the playlist.
 */
@property (nonatomic, readonly) NSArray<_BMPSegmentInfo *> *segments;

/**
 Contains both - regular #EXTINF media segments and SCTE tags represented in the same order as in the playlist.
 */
@property (nonatomic, readonly) NSArray<id<_BMPStartTimeHaving>> *segmentsAggregatedWithScteTags;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)initWithSegmentsAggregatedWithScteTags:(NSArray<id<_BMPStartTimeHaving>> *)aggregatedSegments extInfSegments:(NSArray<_BMPSegmentInfo *> *)segments mediaSequence:(NSInteger)mediaSequence NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
