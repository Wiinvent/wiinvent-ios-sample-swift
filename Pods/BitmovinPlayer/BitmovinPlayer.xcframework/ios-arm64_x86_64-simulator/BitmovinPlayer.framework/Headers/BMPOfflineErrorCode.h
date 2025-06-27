//
// Bitmovin Player iOS SDK
// Copyright (C) 2021, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSErrorDomain const BMPBitmovinOfflineErrorDomain NS_SWIFT_NAME(BitmovinOfflineErrorDomain);

/**
 * This enum represents the offline error codes.
 */
typedef NS_ERROR_ENUM(BMPBitmovinOfflineErrorDomain, BMPOfflineErrorCode) {
    /**
     * A general offline related error code when a more specific error code could not be determined.
     */
    BMPOfflineErrorCodeGeneral = 3001,
    /**
     * There is not enough disk space left to proceed with downloading content.
     */
    BMPOfflineErrorCodeInsufficientStorage = 3003,
    /**
     * Failed to obtain a persistable content key for the DRM license.
     */
    BMPOfflineErrorCodeFailedPersistingDrmLicense = 3004,
    /**
     * The used `SourceConfig` is not supported for download. A `SourceConfig` is only valid for download when it's configured using an HLS asset.
     */
    BMPOfflineErrorCodeUnsupportedSourceConfig = 3009,
    /**
     * Content URL migration has failed.
     */
    BMPOfflineErrorCodeContentUrlMigrationFailed = 3010
} NS_SWIFT_NAME(OfflineError);

NS_ASSUME_NONNULL_END
