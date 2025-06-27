//
// Bitmovin Player iOS SDK
// Copyright (C) 2017, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>
#import "_BMPAdvertisingService.h"
#import "_BMPDefaultService.h"
#import "_BMPNamespacedServiceLocator.h"

@class _BMPAVPlayer;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(_DefaultAdvertisingService)
@interface _BMPDefaultAdvertisingService : _BMPDefaultService <_BMPAdvertisingService>
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)initWithServiceLocator:(id<_BMPNamespacedServiceLocator>)serviceLocator
                                player:(_BMPAVPlayer *)player NS_DESIGNATED_INITIALIZER;
@end

NS_ASSUME_NONNULL_END
