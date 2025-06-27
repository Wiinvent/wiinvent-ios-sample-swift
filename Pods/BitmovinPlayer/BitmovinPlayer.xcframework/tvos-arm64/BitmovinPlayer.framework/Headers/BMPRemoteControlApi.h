//
// Bitmovin Player iOS SDK
// Copyright (C) 2017, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>

/**
 * Provides the means to initiate and manage casting of video to a cast-compatible remote device.
 */
NS_SWIFT_NAME(RemoteControlApi)
@protocol BMPRemoteControlApi <NSObject>
/**
 * Returns `true` if the video is currently casted to a device and not played locally, or `false` if the video is played locally.
 *
 * @return True if the video is currently casted to a device.
 */
@property (nonatomic, readonly) BOOL isCasting;

/**
 * Returns `true` if the player is currently connecting to a device, but the cast session is not yet established.
 *
 * @return True if the player is currently connecting to a device.
 */
@property (nonatomic, readonly) BOOL isWaitingForDevice;

/**
 * Returns `true` if casting to another device (such as a ChromeCast) is available, otherwise false.
 * Please note that this function only returns `true` after the CastAvailableEvent event has fired.
 *
 * @return True if casting to another device is available.
 */
@property (nonatomic, readonly) BOOL isCastAvailable;

/**
 * Stops casting the current video if it is casting at the moment (i.e. RemoteControlApi#isCasting() returns true). Has no effect if RemoteControlApi#isCasting() returns false.
 */
- (void)castStop;

/**
 * Initiates casting the current video to a cast-compatible device. The user has to choose to which device it should be sent.
 */
- (void)castVideo;
@end
