//
// Bitmovin Player iOS SDK
// Copyright (C) 2017, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, _BMPServiceNamespace) {
    _BMPServiceNamespaceNone = 0,
    _BMPServiceNamespaceGlobal,
    _BMPServiceNamespaceNativePlayer,
    _BMPServiceNamespaceGoogleCastController
} NS_SWIFT_NAME(_ServiceNamespace);

NS_ASSUME_NONNULL_END
