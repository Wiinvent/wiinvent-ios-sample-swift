//
// Bitmovin Player iOS SDK
// Copyright (C) 2021, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSErrorDomain const BMPBitmovinSourceErrorDomain NS_SWIFT_NAME(BitmovinSourceErrorDomain);

/**
 * This enum represents the error codes that can be associated with SourceErrorEvent.
 */
typedef NS_ERROR_ENUM(BMPBitmovinSourceErrorDomain, BMPSourceErrorCode) {
    /**
     * A general source error code when a more specific error code could not be determined.
     */
    BMPSourceErrorCodeGeneral = 2001,
    /**
     * Failed to start playing the source.
     */
    BMPSourceErrorCodePlaybackFailed = 2101,
    /**
     * A general error indicating that the current DRM session failed for some reason.
     * The message of the according SourceErrorEvent provides more information.
     */
    BMPSourceErrorCodeDrmGeneral = 2301,
    /**
     * The required DRM configuration is missing.
     */
    BMPSourceErrorCodeDrmConfigMissing = 2302,
    /**
     * No DRM licence URL provided.
     */
    BMPSourceErrorCodeNoDrmLicenseServerUrlProvided = 2303,
    /*
     * No DRM certificate URL provided.
     */
    BMPSourceErrorCodeNoDrmCertificateServerUrlProvided = 2309,
    /**
     * The response to the DRM license request failed with an invalid HTTP response code.
     * The message of the according SourceErrorEvent provides more information.
     */
    BMPSourceErrorCodeDrmLicenseRequestFailed = 2306,
    /**
     * The response to the DRM certificate request failed with an invalid HTTP response code.
     * The message of the according SourceErrorEvent provides more information.
     */
    BMPSourceErrorCodeDrmCertificateRequestFailed = 2307,
    /**
     * Failed to download playlist.
     */
    BMPSourceErrorCodeManifestDownloadFailed = 2202
} NS_SWIFT_NAME(SourceError);

NS_ASSUME_NONNULL_END
