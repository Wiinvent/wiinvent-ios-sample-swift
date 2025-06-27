//
// Bitmovin Player iOS SDK
// Copyright (C) 2021, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>

/// :nodoc:
/** Types of cancelation reasons for download tasks */
typedef NS_ENUM(NSUInteger, _BMPAssetDownloadTaskCancelationReason) {
    // Task was canceled via our API
    _BMPAssetDownloadTaskCancelationReasonApiIntention = 0,
    // Task was canceled in order to recreate it to the corresponding session which either restricts downloads to WiFi or not
    _BMPAssetDownloadTaskCancelationReasonRecreatingForWiFiRestriction,
    // Task was canceled in order to migrate to another asset URL
    _BMPAssetDownloadTaskCancelationReasonMigratingContentUrl
} NS_SWIFT_NAME(_AssetDownloadTaskCancelationReason);
