//
// Bitmovin Player iOS SDK
// Copyright (C) 2021, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

@protocol BMPPlayer;
@class BMPPlayerConfig;

NS_ASSUME_NONNULL_BEGIN

/**
 * Factory to create a `Player` instance.
 */
NS_SWIFT_UNAVAILABLE("Use PlayerFactory instead")
@interface BMPPlayerFactory : NSObject
/**
 * Returns the player SDK version number.
 */
@property (class, nonatomic, readonly) NSString *sdkVersion;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * Creates a player instance configured via the provided PlayerConfig.
 */
+ (id<BMPPlayer>)createWithPlayerConfig:(BMPPlayerConfig *)playerConfig NS_SWIFT_NAME(create(playerConfig:));

/**
 * Creates a player instance with the default PlayerConfig.
 */
+ (id<BMPPlayer>)create;
@end

NS_ASSUME_NONNULL_END
