//
// Bitmovin Player iOS SDK
// Copyright (C) 2018, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(_ErrorFactory)
@interface _BMPErrorFactory : NSObject
/// :nodoc:
- (instancetype)init NS_UNAVAILABLE;
/// :nodoc:
+ (instancetype)new NS_UNAVAILABLE;
+ (NSError *)createPlayerErrorForMissingKeyInJsonData:(NSString *)key;
+ (NSError *)createPlayerJsonDataErrorWithMessage:(nullable NSString *)message;
+ (NSError *)createPlayerJsonDeserializationNotImplementedErrorForClass:(NSString *)className;
+ (NSError *)createGeneralPlayerErrorWithMessage:(nullable NSString *)message;
+ (NSError *)createGeneralSourceDrmErrorWithMessage:(nullable NSString *)message;
+ (NSError *)createSourceDrmMissingConfigErrorWithMessage:(nullable NSString *)userInfo;
+ (NSError *)createSourceDrmCertificateRequestFailedError;
+ (NSError *)createSourceDrmLicenseRequestFailedError;
+ (NSError *)createSourceDrmNoLicenseServerUrlProvidedError;
+ (NSError *)createSourceDrmNoCertificateServerUrlProvidedError;
+ (NSError *)createOfflineInsufficientStorageError;
+ (NSError *)createOfflineFailedPersistingContentKeyError;
+ (NSError *)createOfflineFailedPostProcessingError;
+ (NSError *)createUnsupportedSourceConfigForDownloadError;
+ (NSError *)createPlayerGeneralNetworkErrorWithMessage:(nullable NSString *)message;
+ (NSError *)createOfflineFailedContentUrlMigrationErrorWithMessage:(NSString *)message;
@end

NS_ASSUME_NONNULL_END
