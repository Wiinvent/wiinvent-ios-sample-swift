//
// Bitmovin Player iOS SDK
// Copyright (C) 2019, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// :nodoc:
@protocol _BMPStartTimeHaving <NSObject>
@property (assign, nonatomic, readonly) NSTimeInterval startTime;
- (void)increaseStartTimeBy:(NSTimeInterval)duration;
@end

NS_ASSUME_NONNULL_END
