
### Version 1.21.4
Change log: hỗ trợ thêm 2 quảng cáo liên tiếp & welcome chạy vast tag

#### 1. SDK
```gralde
pod 'WISDK', '1.21.4'
```

#### 2. Hướng dẫn cập nhật
#### 2.1 Hai quảng cáo chạy liên tiếp cập nhật config sau:
    Chỉnh sửa init bỏ biến alwaysCustomSkip

    ==> WIAdsInStreamManager.shared().initInstream(accountId: 14, env: WIEnvironment.SANDBOX, vastLoadTimeout: 5, loadVideoTimeout: 5, bufferingVideoTimeout: 5, bitrate: 2000, logLevel: WILevelLog.BODY, enablePiP: false, skipDuration: 6)

#### 2.2 Triển khai code như hàm initWelcomeAd trong file ViewController
