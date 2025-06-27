//
// Bitmovin Player iOS SDK
// Copyright (C) 2021, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSErrorDomain const BMPBitmovinPlayerErrorDomain NS_SWIFT_NAME(BitmovinPlayerErrorDomain);

/**
 * This enum represents the error codes that can be associated with PlayerErrorEvent.
 */
typedef NS_ERROR_ENUM(BMPBitmovinPlayerErrorDomain, BMPPlayerErrorCode) {
    /**
     * Verification of the player license key failed.
     * A valid license must be provided in the Info.plist file or in the PlayerConfiguration.
     */
    BMPPlayerErrorCodeLicenseKeyNotFound = 1002,
    /**
     * The license request failed or was denied by the server. One possible reason is that the Bundle ID of the app is not authorized for the
     * specified player license key. Make sure that the Bundle ID of the application is registered for the license
     * key provided in the Info.plist file or in the PlayerConfiguration. This can be done in the Bitmovin dashboard.
     */
    BMPPlayerErrorCodeLicenseAuthenticationFailed = 1003,
    /**
     * A general error code for Advertising errors.
     */
    BMPPlayerErrorCodeAdvertising = 1004,
    /**
     * Failed to deserialize object to JSON.
     */
    BMPPlayerErrorCodeJsonDeserializationFailed = 1099,
    /**
     * A general error code for network errors.
     */
    BMPPlayerErrorCodeNetworkGeneral = 1200
} NS_SWIFT_NAME(PlayerError);

NS_ASSUME_NONNULL_END
