//
// Bitmovin Player iOS SDK
// Copyright (C) 2021, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSErrorDomain const BMPBitmovinPlayerWarningDomain NS_SWIFT_NAME(BitmovinPlayerWarningDomain);

/**
 * This enum represents the warning codes that can be associated with PlayerWarningEvent.
 */
typedef NS_ERROR_ENUM(BMPBitmovinPlayerWarningDomain, BMPPlayerWarningCode) {
    /**
     * A general player warning code when a more specific warning code could not be determined.
     */
    BMPPlayerWarningCodeGeneral = 1001,
    /**
     * Failed to set up for remote playback. One possible reason is that the cast sender library version is not supported.
     */
    BMPPlayerWarningCodeSetupRemotePlaybackFailed = 1002
} NS_SWIFT_NAME(PlayerWarning);

NS_ASSUME_NONNULL_END
