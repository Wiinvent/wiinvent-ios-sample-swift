# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

A UIKit demo app that integrates the **WISDK** (Wiinvent's iOS ad SDK, distributed via CocoaPods). Its purpose is to show partner developers how to wire up each WISDK ad format. It is a reference/sample project — the code is intentionally demonstrative, with inline Vietnamese comments explaining each SDK parameter. When changing sample code, preserve those explanatory comments since they are the actual product documentation.

The WISDK version is pinned in `Podfile` (currently `1.21.11`); the per-version integration guides are the `README_1.21.*.md` files at the repo root. When bumping the SDK, update both the Podfile pin and add a new `README_<version>.md`.

## Build & run

This is a CocoaPods project — **always open/build the `.xcworkspace`, never the `.xcodeproj`** (the `.xcodeproj` alone won't link the pods).

```bash
pod install                         # after changing Podfile
open wiinvent-ios-sample-swift.xcworkspace

# Build from CLI
xcodebuild -workspace wiinvent-ios-sample-swift.xcworkspace \
  -scheme wiinvent-ios-sample-swift \
  -sdk iphonesimulator -configuration Debug build

# Run tests (single test: append -only-testing:<Target>/<Class>/<method>)
xcodebuild test -workspace wiinvent-ios-sample-swift.xcworkspace \
  -scheme wiinvent-ios-sample-swift \
  -destination 'platform=iOS Simulator,name=iPhone 15'
```

Dependencies pulled in transitively by WISDK: `GoogleAds-IMA-iOS-SDK` (Google IMA, used for VAST/friendly-obstruction handling) and `TokenGenerator`. Podfile sets `BUILD_LIBRARY_FOR_DISTRIBUTION=YES` and `ONLY_ACTIVE_ARCH=NO` in `post_install`. `Pods/` is checked into git (per CocoaPods guidance).

## Demo configuration

Every sample hard-codes the same test setup: `accountId: 14`, `env: .SANDBOX`, `logLevel: .BODY`. These are demo values — real integrations fetch account/env/timeout config from the partner backend. `README_1.21.8.md` has the authoritative table of every request parameter and its meaning.

## Architecture

`ViewController` is the root menu (four programmatically-created buttons). Each button opens one ad-format demo. The SDK exposes its features through **singleton managers** (`WIAdsInStreamManager.shared()`, `WIWelcomeAdManager.shared()`) plus **per-screen manager instances** for banners, and communicates back via delegate protocols. The recurring integration pattern across all formats is: init/create manager → build a `WI*AdData`/`WI*RequestData` value → `requestAds(...)` → handle events through a delegate → clean up (`destroy()`/`cleanUp()`) on teardown.

### In-Stream ads — `src/DetailView.swift`
The most involved sample. A `UIView` loaded from `DetailView.xib` that owns its own `AVPlayer` content playback and drives `WIAdsInStreamManager.shared()`. Key points a future change must respect:
- Ads are requested **once** in `didMoveToSuperview` (guarded by `didRequestAds`), not in `initView`.
- **Friendly obstructions**: any view drawn over the ad container (here the skip button) must be registered as an `IMAFriendlyObstruction` and passed to `requestAds`, or IMA viewability breaks.
- The app owns the skip-button UI (`Tv360SkipAdsButton`, a `WiAdsSkipButton` subclass). The SDK tells it when to show/hide/pause/resume via the `WIAdsInStreamLoaderDelegate` callbacks (`wiShowSkipButton`, `wiRemoveSkipButton`, `wiPauseSkipButton`, `wiResumeSkipButton`). The pause/resume pair (added in 1.21.11 for the Report Ad feature) keeps the skip countdown in sync with the report bottom sheet — implementing them is optional but expected.
- App lifecycle: `movedToBackground()`/`resume()` must be forwarded from the app's foreground/background notifications, and content play/pause is driven by `wiManagerRequestPlayContent`/`wiManagerRequestPauseContent`.

### Welcome ads — `ViewController.initWelcomeAd()`
Vertical full-screen welcome ad. `WIWelcomeAdManager.shared().requestAds(...)` renders into a container view; results come back through `WIWelcomeAdDelegate` (`onDisplayAds`, `onNoAds`, `onAdsWelcomeClick`, etc.). Removed via `WIWelcomeAdManager.shared().remove()`.

### Banner ads — `src/banner/WI3rdBannerSample/`
Two distinct managers for two distinct use cases (`WI3rdBannerAdDelegate` in both cases reports `changeRatio` for sizing, `click`, `skipAd`, and no-ad):
- **`WI3rdBannerAdManager`** (per-instance) — for standalone container views, e.g. the pause/overlay banner and large/medium banners in `Player/WI3rdBannerSamplePlayerViewController`. Call `destroy()` / `destroyPauseBanner()` on teardown.
- **`WI3rdBannerReusableManager`** — for banners embedded as `UITableView`/`UICollectionView` cells (`Table/` and `Collection/` controllers). Flow: `registerCell(for:)` in setup → `request(ads:)` with an array of `WI3rdBannerAdData` (identified by `position`), whose completion returns the position ids that filled so you can insert rows → forward `cellForRowAt`/`heightForRowAt` to the manager → `cleanUp()` on reload/deinit.

Banner ad sizes are an enum: `.HOMEPAGE_BANNER`, `.SUBPAGE_BANNER`, `.PAUSE_BANNER` (older docs also reference `.MEDIUM_BANNER`/`.LARGE_BANNER`).

### Bitmovin in-stream — `src/BitmovinDetailView.swift`
Scaffolding for a Bitmovin-player-based in-stream sample, but **entirely commented out** and its menu button is a no-op. The `BitmovinPlayer` pod is commented out in the Podfile. Treat this as a not-yet-enabled path; don't assume it compiles or runs.

### Helpers — `src/base/`
- `StoryboardInstantiable` — `instantiate()` pattern loading a VC from a same-named storyboard (used by all banner controllers).
- `NibInstantiatable` (defined in `ViewController.swift`) — `fromNib()` for the xib-backed `DetailView`/`BitmovinDetailView`.
- `AVPlayerView` — a `UIView` backed by `AVPlayerLayer` for the banner player sample.
