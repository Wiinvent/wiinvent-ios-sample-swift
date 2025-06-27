//
// Bitmovin Player iOS SDK
// Copyright (C) 2019, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <BitmovinPlayer/_BMPAssetDownloadTaskCancelationReason.h>

NS_ASSUME_NONNULL_BEGIN

/// :nodoc:
NS_SWIFT_NAME(_DownloadTask)
@protocol _BMPDownloadTask <NSObject>
@property (nonatomic, readonly) NSURLSessionTaskState state;
@property (nonatomic, copy, readonly) NSString *identifier;
@property (nonatomic, readonly, nullable) NSError *error;
@property (nonatomic, readonly) _BMPAssetDownloadTaskCancelationReason cancelationReason;
- (void)suspend;
- (void)resume;
- (void)cancelWithReason:(_BMPAssetDownloadTaskCancelationReason)cancelationReason;
@end

NS_ASSUME_NONNULL_END
