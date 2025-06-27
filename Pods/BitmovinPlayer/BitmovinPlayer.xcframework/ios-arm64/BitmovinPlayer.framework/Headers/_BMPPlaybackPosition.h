//
// Bitmovin Player iOS SDK
// Copyright (C) 2019, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import "BMPTimelineReferencePoint.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(_PlaybackPosition)
@interface _BMPPlaybackPosition : NSObject
@property (nonatomic, readonly) NSTimeInterval startOffset;
@property (nonatomic, readonly) BMPTimelineReferencePoint startOffsetTimelineReference;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)initWithStartOffset:(NSTimeInterval)startOffset
       startOffsetTimelineReference:(BMPTimelineReferencePoint)startOffsetTimelineReference NS_DESIGNATED_INITIALIZER;
@end

NS_ASSUME_NONNULL_END
