//
// Bitmovin Player iOS SDK
// Copyright (C) 2019, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import "_BMPStartTimeHaving.h"

NS_ASSUME_NONNULL_BEGIN

/// :nodoc:
NS_SWIFT_NAME(_SegmentInfo)
@interface _BMPSegmentInfo : NSObject <_BMPStartTimeHaving>

@property (assign, nonatomic, readonly) NSTimeInterval duration;
@property (strong, nonatomic, readonly) NSString *uri;

- (instancetype)initWithDuration:(NSTimeInterval)duration startTime:(NSTimeInterval)startTime uri:(NSString *)uri;

@end

NS_ASSUME_NONNULL_END
