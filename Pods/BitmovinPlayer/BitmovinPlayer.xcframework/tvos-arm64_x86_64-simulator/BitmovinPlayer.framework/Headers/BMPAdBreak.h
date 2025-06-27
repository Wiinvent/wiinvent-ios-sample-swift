//
// Bitmovin Player iOS SDK
// Copyright (C) 2019, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <BitmovinPlayer/BMPAdConfig.h>
#import <BitmovinPlayer/BMPAd.h>
#import <BitmovinPlayer/_BMPJsonEncodable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Contains information about an ad break.
 */
NS_SWIFT_NAME(AdBreak)
@protocol BMPAdBreak <BMPAdConfig, _BMPJsonEncodable>

/**
 * The identifier of the corresponding `AdBreakConfig`.
 * If the AdBreak was generated out of a VMAP tag, then the ID present in the
 * VMAP tag will be taken. If none is present in the VMAP tag, it will be generated.
 *
 * @return The identifier of the corresponding `AdBreakConfig`.
 * @see BMPAdBreakConfig
 */
@property (nonatomic, readonly) NSString *identifier;

/**
 * The time in seconds in the media timeline the `AdBreak` is scheduled for.
 *
 * @return The time in seconds in the media timeline the `AdBreak` is scheduled for.
 */
@property (nonatomic, readonly) NSTimeInterval scheduleTime;

/**
 * The ads scheduled for this `AdBreak`.
 *
 * @return The ads scheduled for this `AdBreak`.
 * @see BMPAd
 * @note This contains only ads that have already been started. Therefore, it is expected to be empty when `AdBreakStartedEvent` is seen.
 */
@property (nonatomic, readonly) NSArray<id<BMPAd>> *ads;

/**
 * Total number of ads in the ad break.
 *
 * @return The total number of ads in the `AdBreak`.
 */
@property (nonatomic, readonly) NSUInteger totalNumberOfAds;

/**
 * Adds an AdItem to the ads Array
 */
- (void)registerAd:(id<BMPAd>)adItem;
@end

NS_ASSUME_NONNULL_END
