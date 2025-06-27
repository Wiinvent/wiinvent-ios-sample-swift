//
// Bitmovin Player iOS SDK
// Copyright (C) 2017, Bitmovin GmbH, All Rights Reserved
//
// This source code and its use and distribution, is subject to the terms
// and conditions of the applicable license agreement.
//

#import <Foundation/Foundation.h>

@class BMPPlayerView;
@class PictureInPictureEnterEvent;
@class PictureInPictureEnteredEvent;
@class PictureInPictureExitEvent;
@class PictureInPictureExitedEvent;
@class BMPScalingModeChangedEvent;
@class BMPFullscreenEnterEvent;
@class BMPFullscreenExitEvent;
@class BMPFullscreenEnabledEvent;
@class BMPFullscreenDisabledEvent;
@class BMPControlsShowEvent;
@class BMPControlsHideEvent;

NS_ASSUME_NONNULL_BEGIN

/**
 * Defines listener methods for all events available for the PlayerView. See the documentation of the single listener
 * methods for further information.
 */
NS_SWIFT_NAME(UserInterfaceListener)
@protocol BMPUserInterfaceListener <NSObject>
@optional
/**
 * Is called when the player enters fullscreen mode.
 *
 * @param event An object holding specific event data.
 * @param view The player view instance which is associated with the emitted event
 */
- (void)onFullscreenEnter:(BMPFullscreenEnterEvent *)event view:(BMPPlayerView *)view;

/**
 * Is called when the player exits fullscreen mode.
 *
 * @param event An object holding specific event data.
 * @param view The player view instance which is associated with the emitted event
 */
- (void)onFullscreenExit:(BMPFullscreenExitEvent *)event view:(BMPPlayerView *)view;

/**
 * Is called when a fullscreen handler has been set.
 *
 * @param event An object holding specific event data.
 * @param view The player view instance which is associated with the emitted event
 */
- (void)onFullscreenEnabled:(BMPFullscreenEnabledEvent *)event view:(BMPPlayerView *)view;

/**
 * Is called when the current fullscreen handler was removed.
 *
 * @param event An object holding specific event data.
 * @param view The player view instance which is associated with the emitted event
 */
- (void)onFullscreenDisabled:(BMPFullscreenDisabledEvent *)event view:(BMPPlayerView *)view;

/**
 * Fires when the UI controls are showing.
 *
 * @param event An object holding specific event data.
 * @param view The player view instance which is associated with the emitted event
 */
- (void)onControlsShow:(BMPControlsShowEvent *)event view:(BMPPlayerView *)view;

/**
 * Fires when the UI controls are hiding.
 *
 * @param event An object holding specific event data.
 * @param view The player view instance which is associated with the emitted event
 */
- (void)onControlsHide:(BMPControlsHideEvent *)event view:(BMPPlayerView *)view;

/**
 * Is called when the `PlayerView` is about to enter Picture in Picture mode.
 *
 * @param event An object holding specific event data.
 * @param view The player view instance which is associated with the emitted event
 */
- (void)onPictureInPictureEnter:(PictureInPictureEnterEvent *)event view:(BMPPlayerView *)view NS_SWIFT_NAME(onPictureInPictureEnter(_:view:));

/**
 * Is called when the `PlayerView` finished entering Picture in Picture mode.
 *
 * @param event An object holding specific event data.
 * @param view The player view instance which is associated with the emitted event
 */
- (void)onPictureInPictureEntered:(PictureInPictureEnteredEvent *)event view:(BMPPlayerView *)view NS_SWIFT_NAME(onPictureInPictureEntered(_:view:));

/**
 * Is called when the `PlayerView` is about to exit Picture in Picture mode.
 *
 * @param event An object holding specific event data.
 * @param view The player view instance which is associated with the emitted event
 */
- (void)onPictureInPictureExit:(PictureInPictureExitEvent *)event view:(BMPPlayerView *)view NS_SWIFT_NAME(onPictureInPictureExit(_:view:));

/**
 * Is called when the `PlayerView` finished exiting Picture in Picture mode.
 *
 * @param event An object holding specific event data.
 * @param view The player view instance which is associated with the emitted event
 */
- (void)onPictureInPictureExited:(PictureInPictureExitedEvent *)event view:(BMPPlayerView *)view NS_SWIFT_NAME(onPictureInPictureExited(_:view:));

/**
 * Is called when the `ScalingMode` of the `PlayerView` changed.
 *
 * @param event An object holding specific event data.
 * @param view The player view instance which is associated with the emitted event
 */
- (void)onScalingModeChanged:(BMPScalingModeChangedEvent *)event view:(BMPPlayerView *)view NS_SWIFT_NAME(onScalingModeChanged(_:view:));
@end

NS_ASSUME_NONNULL_END
