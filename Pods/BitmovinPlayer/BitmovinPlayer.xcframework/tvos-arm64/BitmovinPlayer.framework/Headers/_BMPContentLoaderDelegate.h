//
// Bitmovin Player iOS SDK
// Copyright (C) 2018, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>

@class _BMPRequestMetadata;
@protocol _BMPContentLoader;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(_ContentLoaderDelegate)
@protocol _BMPContentLoaderDelegate <NSObject>
/**
 * Is called when the _BMPContentLoader has finished downloading successfully.
 *
 * @param loader The _BMPContentLoader which is calling the delegate method.
 * @param requestMetadata The BMPRequestMetadata containing data about the request.
 * @param data The content data of the requested file.
 */
- (void)contentLoader:(id<_BMPContentLoader>)loader didSucceedWithMetadata:(_BMPRequestMetadata *)requestMetadata data:(NSData *)data;
/**
 * Is called when the _BMPContentLoader has finished downloading with an error.
 *
 * @param loader The _BMPContentLoader which is calling the delegate method.
 * @param requestMetadata The BMPRequestMetadata containing data about the request.
 * @param error The NSError which occurred.
 */
- (void)contentLoader:(id<_BMPContentLoader>)loader didFailWithMetadata:(_BMPRequestMetadata *)requestMetadata error:(NSError *)error;
@end

NS_ASSUME_NONNULL_END
