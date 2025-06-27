//
// Bitmovin Player iOS SDK
// Copyright (C) 2017, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
@protocol BMPPlayerListener;

NS_ASSUME_NONNULL_BEGIN

/**
 * Manages listeners to specific `PlayerEvent`s and notifies those listeners when such an event is being
 * emitted.
 * Listeners need to conform to the `PlayerListener` protocol.
 * See `PlayerListener` about possible event method implementations.
 */
NS_SWIFT_NAME(PlayerEventHandler)
@protocol BMPPlayerEventHandler <NSObject>
/**
 * Adds a `PlayerEvent` listener.
 *
 * @param listener The event listener to be added.
 */
- (void)addPlayerListener:(id<BMPPlayerListener>)listener NS_SWIFT_NAME(add(listener:));

/**
 * Removes a `PlayerEvent` listener.
 *
 * @param listener The event listener to be removed.
 */
- (void)removePlayerListener:(id<BMPPlayerListener>)listener NS_SWIFT_NAME(remove(listener:));
@end

NS_ASSUME_NONNULL_END
