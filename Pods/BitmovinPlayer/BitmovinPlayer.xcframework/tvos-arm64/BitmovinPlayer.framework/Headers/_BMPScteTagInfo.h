//
// Bitmovin Player iOS SDK
// Copyright (C) 2019, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import "_BMPStartTimeHaving.h"

@protocol BMPMetadataEntry;

NS_ASSUME_NONNULL_BEGIN

// TODO: Delete this class and create an according property in the `_BMPSegmentInfo` for the SCTE tag.

/**
 Describes default properties of the custom SCTE35 tag from the playlist as well as some additional calculated information.
 */
NS_SWIFT_NAME(_ScteTagInfo)
@interface _BMPScteTagInfo : NSObject <_BMPStartTimeHaving>

/**
 Holds the contents of the SCTE tag as it has been represented in the playlist, e.g. CUE parameter would
 we accessed like `info[@"CUE"]`.
 */
@property (strong, nonatomic, readonly) NSDictionary *info;

/// :nodoc:
- (instancetype)init NS_UNAVAILABLE;
/// :nodoc:
+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithDictionary:(NSDictionary *)info
                         rawString:(NSString *)rawString
                    sequenceNumber:(NSInteger)sequenceNumber
                         startTime:(NSTimeInterval)startTime NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
