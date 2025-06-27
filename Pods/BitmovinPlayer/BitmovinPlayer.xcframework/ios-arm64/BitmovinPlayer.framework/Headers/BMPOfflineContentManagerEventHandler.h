//
// Bitmovin Player iOS SDK
// Copyright (C) 2021, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

@protocol BMPOfflineContentManagerListener;

NS_ASSUME_NONNULL_BEGIN

/**
 Manages listeners to specific `OfflineContentManager`s and notifies those listeners
 */
NS_SWIFT_NAME(OfflineContentManagerEventHandler)
@protocol BMPOfflineContentManagerEventHandler <NSObject>
/**
 Adds a listener to the `OfflineContentManager`.

 @param listener The listener to add.
 */
- (void)addListener:(id<BMPOfflineContentManagerListener>)listener NS_SWIFT_NAME(add(listener:));
/**
 Removes a listener from the `OfflineContentManager`.

 @param listener The listener to remove.
 */
- (void)removeListener:(id<BMPOfflineContentManagerListener>)listener NS_SWIFT_NAME(remove(listener:));
@end

NS_ASSUME_NONNULL_END
