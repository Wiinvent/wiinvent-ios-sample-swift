//
// Bitmovin Player iOS SDK
// Copyright (C) 2021, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSErrorDomain const BMPBitmovinSourceWarningDomain NS_SWIFT_NAME(BitmovinSourceWarningDomain);

/**
 * This enum represents the warning codes that can be associated with SourceWarningEvent.
 */
typedef NS_ERROR_ENUM(BMPBitmovinSourceWarningDomain, BMPSourceWarningCode) {
    /**
     * It was not possible to load a thumbnail track because the URI was not valid or the communication with the server
     * failed.
     * The message of the according SourceWarningEvent provides more information.
     */
    BMPSourceWarningCodeThumbnailLoadingFailed = 2002,
    /**
     * It was not possible to parse a thumbnail track.
     * The message of the according SourceWarningEvent provides more information.
     */
    BMPSourceWarningCodeThumbnailParsingFailed = 2003,
    /**
     * It was not possible to load a subtitle track because the URI was not valid or the communication with the server
     * failed.
     * The message of the according SourceWarningEvent provides more information.
     */
    BMPSourceWarningCodeSubtitleLoadingFailed = 2004,
    /**
     * It was not possible to parse a subtitle track.
     * The message of the according SourceWarningEvent provides more information.
     */
    BMPSourceWarningCodeSubtitleParsingFailed = 2005,
    /**
     * The HLS variant playlist attribute is missing.
     */
    BMPSourceWarningCodeHlsPlaylistTypeTagMissing = 1207
} NS_SWIFT_NAME(SourceWarning);

NS_ASSUME_NONNULL_END
