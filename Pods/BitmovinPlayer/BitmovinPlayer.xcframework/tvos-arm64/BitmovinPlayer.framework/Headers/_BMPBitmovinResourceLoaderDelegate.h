//
// Bitmovin Player iOS SDK
// Copyright (C) 2020, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>

@class _BMPBitmovinResourceLoader;
@class _BMPRequestMetadata;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(_BitmovinResourceLoaderDelegate)
@protocol _BMPBitmovinResourceLoaderDelegate <NSObject>
@optional
/**
 Is called when the BMPBitmovinResourceLoader has finished loading a master playlist.

 @param sender The BMPBitmovinResourceLoader which is calling the delegate method.
 @param masterData The NSData representing the raw master playlist.
 @param requestMetadata The BMPRequestMetadata which contains information about the request and response.
 */
- (void)bitmovinResourceLoader:(_BMPBitmovinResourceLoader *)sender didFinishLoadingMasterPlaylistData:(NSData *)masterData
               requestMetadata:(_BMPRequestMetadata *)requestMetadata;
/**
 Is called when the BMPBitmovinResourceLoader has finished loading a variant playlist.

 @param sender The BMPBitmovinResourceLoader which is calling the delegate method.
 @param variantData The NSData representing the raw variant playlist.
 @param requestMetadata The BMPRequestMetadata which contains information about the request and response.
 */
- (void)bitmovinResourceLoader:(_BMPBitmovinResourceLoader *)sender didFinishLoadingVariantPlaylistData:(NSData *)variantData
               requestMetadata:(_BMPRequestMetadata *)requestMetadata;

/**
 Is called when the BMPBitmovinResourceLoader encountered an HTTP status code (e.g. 404) indicating an unsuccessful request. This doesn't mean the BMPPlaylistLoader
 has finished its work. It could be that there are still retries upcoming.

 For now only the BMPPlaylistLoader notifies about failed requests.
 In case the last retry failed this method will be called before bitmovinResourceLoader:didFinishLoadingPlaylistWithError: is called.

 @param sender The BMPPlaylistLoader which is calling the delegate method.
 @param requestMetadata The BMPRequestMetadata which contains information about the request and response.
 */
- (void)bitmovinResourceLoader:(_BMPBitmovinResourceLoader *)sender playlistRequestFailedWithRequestMetadata:(_BMPRequestMetadata *)requestMetadata;
/**
 Is called if the BMPBitmovinResourceLoader has finished loading a playlist with an error.

 @param sender The BMPBitmovinResourceLoader which is calling the delegate method.
 @param error The NSError which occurred.
 */
- (void)bitmovinResourceLoader:(_BMPBitmovinResourceLoader *)sender didFinishLoadingPlaylistWithError:(NSError *)error;

/**
 Is called when the BMPBitmovinResourceLoader has finished loading AES key data

 @param sender The BMPBitmovinResourceLoader which is calling the delegate method.
 @param keyData The AES key data
 @param requestMetadata The BMPRequestMetadata which contains information about the request and response.
 */
- (void)bitmovinResourceLoader:(_BMPBitmovinResourceLoader *)sender didFinishLoadingAesKeyData:(NSData *)keyData
               requestMetadata:(_BMPRequestMetadata *)requestMetadata;

/**
 Is called if the BMPBitmovinResourceLoader has finished loading AES key data with an error.

 @param sender The BMPBitmovinResourceLoader which is calling the delegate method.
 @param error The NSError which occurred.
 */
- (void)bitmovinResourceLoader:(_BMPBitmovinResourceLoader *)sender didFinishLoadingAesKeyWithError:(NSError *)error;
@end

NS_ASSUME_NONNULL_END
