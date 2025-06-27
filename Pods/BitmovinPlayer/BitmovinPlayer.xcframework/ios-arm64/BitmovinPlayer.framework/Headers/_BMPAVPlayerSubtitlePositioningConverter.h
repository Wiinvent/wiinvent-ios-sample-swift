//
// Bitmovin Player iOS SDK
// Copyright (C) 2020, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
@class BMPVttProperties;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(_AVPlayerSubtitlePositioningConverter)
@interface _BMPAVPlayerSubtitlePositioningConverter : NSObject
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
+ (BMPVttProperties *)vttPropertiesFromAttributedString:(NSAttributedString *)attributedString;
@end

NS_ASSUME_NONNULL_END
