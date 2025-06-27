//
// Bitmovin Player iOS SDK
// Copyright (C) 2017, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>

/**
 * Following constants enumerate the different available HTTPRequest types which can be handled in the
 * BMPNetworkConfig.
 */

typedef NSString * BMPHttpRequestType NS_TYPED_ENUM NS_SWIFT_NAME(HttpRequestType);
NS_SWIFT_NAME(HttpRequestType.drmLicenseFairplay) static BMPHttpRequestType const BMPHttpRequestTypeDrmLicenseFairplay = @"drm/license/fairplay";
NS_SWIFT_NAME(HttpRequestType.drmCertificateFairplay) static BMPHttpRequestType const BMPHttpRequestTypeDrmCertificateFairplay = @"drm/certificate/fairplay";
NS_SWIFT_NAME(HttpRequestType.mediaThumbnails) static BMPHttpRequestType const BMPHttpRequestTypeMediaThumbnails = @"media/thumbnails";
NS_SWIFT_NAME(HttpRequestType.mediaSubtitles) static BMPHttpRequestType const BMPHttpRequestTypeMediaSubtitles = @"media/subtitles";
NS_SWIFT_NAME(HttpRequestType.manifestHlsMaster) static BMPHttpRequestType const BMPHttpRequestTypeManifestHlsMaster = @"manifest/hls/master";
NS_SWIFT_NAME(HttpRequestType.manifestHlsVariant) static BMPHttpRequestType const BMPHttpRequestTypeManifestHlsVariant = @"manifest/hls/variant";
NS_SWIFT_NAME(HttpRequestType.keyHlsAes) static BMPHttpRequestType const BMPHttpRequestTypeKeyHlsAes = @"key/hls/aes";
NS_SWIFT_NAME(HttpRequestType.unknown) static BMPHttpRequestType const BMPHttpRequestTypeUnknown = @"unknown";
