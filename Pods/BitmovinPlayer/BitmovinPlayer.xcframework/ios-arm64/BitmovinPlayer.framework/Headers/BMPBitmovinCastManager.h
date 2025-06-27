//
// Bitmovin Player iOS SDK
// Copyright (C) 2017, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import <BitmovinPlayer/BMPBitmovinCastManagerListener.h>

@protocol GCKSessionManagerListener;
@class GCKMediaStatus;
@class GCKMediaMetadata;
@class GCKDevice;
@class GCKCastChannel;
@class BMPBitmovinCastManagerOptions;

NS_ASSUME_NONNULL_BEGIN

/**
 * IMPORTANT: Methods from BMPBitmovinCastManager need to be called from the main thread.
 *
 * Singleton providing access to GoogleCast related features. The BMPBitmovinCastManager needs to be initialized by calling
 * BMPBitmovinCastManager#initializeCasting in the AppDelegate of the application which should support casting.
 */
NS_SWIFT_NAME(BitmovinCastManager)
__TVOS_PROHIBITED
@interface BMPBitmovinCastManager : NSObject
@property (nonatomic, readonly) BOOL isConnected;
@property (nonatomic, readonly) BOOL isConnecting;
@property (nonatomic, readonly) BOOL isCastAvailable;
@property (nonatomic, readonly, nullable) GCKMediaStatus *currentMediaStatus;
@property (nonatomic, readonly, nullable) GCKMediaMetadata *currentMediaMetadata;
@property (nonatomic, readonly, nullable) GCKDevice *currentDevice;
@property (nonatomic, readonly) BOOL isPlaying;
@property (nonatomic, readonly) BOOL isPaused;
@property (nonatomic, readonly) BOOL isMuted;
@property (nonatomic, readonly) BOOL isStalled;
@property (nonatomic, readonly) NSTimeInterval currentTime;
@property (nonatomic, readonly) NSTimeInterval duration;
@property (nonatomic, readonly, nullable, strong) GCKCastChannel *defaultChannel;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
+ (instancetype)sharedInstance;
+ (BOOL)isInitialized;
/**
 Uses default Bitmovin receiver app
 */
+ (void)initializeCasting;
/**
 Uses given receiver app
 @param applicationId ID of receiver application
 */
+ (void)initializeCasting:(NSString *)applicationId NS_SWIFT_NAME(initializeCasting(applicationId:)) __deprecated_msg("Use BMPBitmovinCastManager#initializeCasting(options:) instead.");
/**
 Uses given receiver app
 @param applicationId ID of receiver application
 @param messageNamespace Custom namespace
 */
+ (void)initializeCasting:(NSString *)applicationId
         messageNamespace:(nullable NSString *)messageNamespace NS_SWIFT_NAME(initializeCasting(applicationId:messageNamespace:)) __deprecated_msg("Use BMPBitmovinCastManager#initializeCasting(options:) instead.");
/**
 Initialize `BitmovinCastManager` based on the provided `BitmovinCastManagerOptions`.
 @param options `BMPBitmovinCastManagerOptions` to use for initializing `BMPBitmovinCastManager`
 */
+ (void)initializeCastingWithOptions:(BMPBitmovinCastManagerOptions *)options NS_SWIFT_NAME(initializeCasting(options:));
- (void)loadMedia;
- (void)loadMedia:(BOOL)autoplay NS_SWIFT_NAME(loadMedia(autoplay:));
- (void)loadMedia:(BOOL)autoplay position:(NSTimeInterval)position NS_SWIFT_NAME(loadMedia(autoplay:position:));
- (void)unload;
- (void)showDialog;
- (void)addListener:(id<BMPBitmovinCastManagerListener>)listener NS_SWIFT_NAME(add(listener:));
- (void)removeListener:(id<BMPBitmovinCastManagerListener>)listener NS_SWIFT_NAME(remove(listener:));
- (void)play;
- (void)pause;
- (void)seek:(NSTimeInterval)time NS_SWIFT_NAME(seek(time:));
- (void)_seek:(NSTimeInterval)time completionHandler:(nullable void(^)(void))completionHandler NS_SWIFT_NAME(_seek(time:completionHandler:));
- (void)seekToItemWithItemId:(NSUInteger)itemId
                     andTime:(NSTimeInterval)time NS_SWIFT_NAME(seekToItem(itemId:time:));
- (void)_seekToItemWithItemId:(NSUInteger)itemId
                      andTime:(NSTimeInterval)time
            completionHandler:(nullable void(^)(void))completionHandler NS_SWIFT_NAME(_seekToItem(itemId:time:completionHandler:));
- (NSUInteger)getItemIdAtIndex:(NSUInteger)index NS_SWIFT_NAME(getItemId(index:));

/**
 Sends the given message to the cast receiver.
 The receiver can pick up the message on the namespace returned by defaultChannel.protocolNamespace.

 @param message The message to send.
 @return true if the message could be sent successfully.
 */
- (BOOL)sendMessage:(NSString *)message NS_SWIFT_NAME(sendMessage(_:));
/**
 Sends the given message to the cast receiver on the provided namespace.
 If no namespace is provided, the one returned by defaultChannel.protocolNamespace is used.

 @param message The message to send.
 @param messageNamespace The namespace the message should be send on.
 @return true if the message could be sent successfully.
 */
- (BOOL)sendMessage:(NSString *)message withNamespace:(nullable NSString *)messageNamespace NS_SWIFT_NAME(sendMessage(_:withNamespace:));
/**
 Sends the given metadata wrapped in a metadata message object to the cast receiver on the configured message namespace.
 The provided metadata must be serializable using NSJSONSerialization.

 @param metadata The metadata to send. Must be serializable using NSJSONSerialization.
 @return true if the message could be sent successfully.
 */
- (BOOL)sendMetadata:(NSDictionary *)metadata NS_SWIFT_NAME(send(metadata:));
@end

NS_ASSUME_NONNULL_END
