### Version 1.21.13
Change log: WISDK bổ sung 2 tham số mới khi request quảng cáo, cho phép truyền định danh người dùng và giới hạn hiển thị (impression). 2 tham số này được gửi lên backend cho tất cả các định dạng:

- **Banner Ad** (`WI3rdBannerAdData`)
- **In-Stream Ad** (`WIAdsRequestData`)
- **Welcome Ad** (`WIWelcomeAdData`)

| Tham số | Kiểu | Query gửi lên backend | Ý nghĩa |
|---|---|---|---|
| `userId` | `String` | `uid` | Định danh người dùng |
| `userImpressionLimit` | `Int` | `uil` | Giới hạn số lần hiển thị (impression) |

> **Breaking change:** Tham số `uid20` cũ đã bị **loại bỏ** khỏi tất cả init của `WIAdsRequestData`, `WI3rdBannerAdData`, `WIWelcomeAdData`. Ứng dụng đang dùng `uid20` cần đổi sang `userId` và bổ sung `userImpressionLimit`.

#### 1. SDK
```gradle
pod 'WISDK', '1.21.13'
```

---

## Thay đổi cho In-Stream Ad

`WIAdsRequestData` thay `uid20` bằng `userId` và thêm `userImpressionLimit`:

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
    userId: "m10001",           // trước đây là uid20
    userImpressionLimit: 30,     // MỚI
    segments: "abc,123,123"
)
```

---

## Thay đổi cho Banner Ad

`WI3rdBannerAdData` thay `uid20` bằng `userId` và thêm `userImpressionLimit`:

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
    userId: "m10001",           // trước đây là uid20
    userImpressionLimit: 30,     // MỚI
    segments: "123,123,123"
)
```

---

## Thay đổi cho Welcome Ad

`WIWelcomeAdData` thay `uid20` bằng `userId` và thêm `userImpressionLimit` (cả 2 init đều đổi):

```swift
let adData = WIWelcomeAdData(
    accountId: String(14),
    transId: "123123123",
    age: 0,
    gender: WIGender.NONE,
    userId: "m10001",           // trước đây là uid20
    userImpressionLimit: 30,     // MỚI
    domainUrl: "",
    env: WIEnvironment.SANDBOX,
    segments: "123,123,123,123"
)
```

---

## Checklist tích hợp

- [ ] Cập nhật WISDK lên phiên bản mới nhất (>= v1.21.13)
- [ ] Đổi `uid20` → `userId` ở mọi nơi khởi tạo `WIAdsRequestData`, `WI3rdBannerAdData`, `WIWelcomeAdData`
- [ ] Bổ sung tham số `userImpressionLimit` cho các init trên
- [ ] Build và kiểm tra request gửi lên backend có chứa `uid` và `uil`
