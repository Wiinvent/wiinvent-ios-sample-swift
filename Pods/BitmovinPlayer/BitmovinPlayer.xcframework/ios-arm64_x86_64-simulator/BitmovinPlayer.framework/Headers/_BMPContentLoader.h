//
// Bitmovin Player iOS SDK
// Copyright (C) 2020, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import "_BMPContentLoaderDelegate.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(_ContentLoader)
@protocol _BMPContentLoader <NSObject>
/// Will be called whenever loading was successful or not
@property (weak, nonatomic, nullable) id<_BMPContentLoaderDelegate> delegate;
/**
 * Starts download for the given URL
 *
 * @param url The URL to download the data from.
 */
- (void)load:(NSURL *)url;
/**
 * Cancels any ongoing download
 */
- (void)cancel;
@end

NS_ASSUME_NONNULL_END
