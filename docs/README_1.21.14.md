### Version 1.21.14
Change log: WISDK bổ sung 1 tham số mới khi request quảng cáo. Tham số này được gửi lên backend cho tất cả các định dạng:

- **Banner Ad** (`WI3rdBannerAdData`)
- **In-Stream Ad** (`WIAdsRequestData`)
- **Welcome Ad** (`WIWelcomeAdData`)

| Tham số | Kiểu | Query gửi lên backend | Ý nghĩa |
|---|---|---|---|
| `adPendingTimes` | `Int` | `apt` | Số lần chờ hiển thị quảng cáo |

> **Breaking change:** `adPendingTimes` là tham số **bắt buộc**, không có giá trị mặc định. Mọi nơi khởi tạo `WIAdsRequestData`, `WI3rdBannerAdData`, `WIWelcomeAdData` (cả 2 init) đều phải bổ sung, nếu không sẽ lỗi biên dịch.

#### 1. SDK
```gradle
pod 'WISDK', '1.21.14'
```

---

## Thay đổi cho In-Stream Ad

`WIAdsRequestData` thêm `adPendingTimes` ngay sau `userImpressionLimit`:

```swift
let requestData = WIAdsRequestData(
    channelId: "998989",
    streamId: "119",
    transId: "1111",
    contentType: WIContentType.FILM,
    title: "...",
    category: "Category1,Category2",
    keyword: "",
    age: 0,
    gender: WIGender.NONE,
    userId: "m10001",
    userImpressionLimit: 30,
    adPendingTimes: 3,          // MỚI
    segments: "abc,123,123"
)
```

---

## Thay đổi cho Banner Ad

`WI3rdBannerAdData` thêm `adPendingTimes` ngay sau `userImpressionLimit`:

```swift
let adData = WI3rdBannerAdData(
    position: "...",
    env: .SANDBOX,
    transId: "1111",
    contentType: .TV,
    title: "...",
    category: "...",
    keyword: "...",
    age: 30,
    gender: .MALE,
    adSize: .HOMEPAGE_BANNER,
    userId: "m10001",
    userImpressionLimit: 30,
    adPendingTimes: 3,          // MỚI
    segments: "123,123,123"
)
```

---

## Thay đổi cho Welcome Ad

`WIWelcomeAdData` thêm `adPendingTimes` ngay sau `userImpressionLimit` (cả 2 init đều đổi):

```swift
let adData = WIWelcomeAdData(
    accountId: String(14),
    transId: "123123123",
    age: 0,
    gender: WIGender.NONE,
    userId: "m10001",
    userImpressionLimit: 30,
    adPendingTimes: 3,          // MỚI
    domainUrl: "",
    env: WIEnvironment.SANDBOX,
    segments: "123,123,123,123"
)
```

---

## Checklist tích hợp

- [ ] Cập nhật WISDK lên phiên bản mới nhất (>= v1.21.14)
- [ ] Bổ sung tham số `adPendingTimes` cho mọi init của `WIAdsRequestData`, `WI3rdBannerAdData`, `WIWelcomeAdData`
- [ ] Build và kiểm tra request gửi lên backend có chứa `apt`
