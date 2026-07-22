<<<<<<< HEAD:docs/README_1.21.16.md
### Version 1.21.16
=======
### Version 1.21.15
>>>>>>> e5d542c3fa2901da73047c4e48999641eb233fc8:docs/README_1.21.15.md
Change log: WISDK bổ sung 1 tham số mới khi request quảng cáo. Tham số này được gửi lên backend cho tất cả các định dạng:

- **Banner Ad** (`WI3rdBannerAdData`)
- **In-Stream Ad** (`WIAdsRequestData`)
- **Welcome Ad** (`WIWelcomeAdData`)

| Tham số | Kiểu | Query gửi lên backend | Ý nghĩa |
|---|---|---|---|
| `userId` | `String` | `uid` | ID người dùng |
| `userImpressionLimit` | `Int` | `uil` | Giới hạn số lần hiển thị quảng cáo theo user trong ngày |
| `adPendingTime` | `Int` | `apt` | Thời gian chờ xuất hiện giữa 2 lần quảng cáo, đơn vị giây |

> **Breaking change:** `adPendingTime` là tham số **bắt buộc**, không có giá trị mặc định. Mọi nơi khởi tạo `WIAdsRequestData`, `WI3rdBannerAdData`, `WIWelcomeAdData` (cả 2 init) đều phải bổ sung, nếu không sẽ lỗi biên dịch.

#### 1. SDK
```gradle
pod 'WISDK', '1.21.16'
```

---

## Thay đổi cho In-Stream Ad

`WIAdsRequestData` thêm `adPendingTime` ngay sau `userImpressionLimit`:

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
    adPendingTime: 30,          // MỚI
    segments: "abc,123,123"
)
```

---

## Thay đổi cho Banner Ad

`WI3rdBannerAdData` thêm `adPendingTime` ngay sau `userImpressionLimit`:

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
    adPendingTime: 30,          // MỚI
    segments: "123,123,123"
)
```

---

## Thay đổi cho Welcome Ad

`WIWelcomeAdData` thêm `adPendingTime` ngay sau `userImpressionLimit` (cả 2 init đều đổi):

```swift
let adData = WIWelcomeAdData(
    accountId: String(14),
    transId: "123123123",
    age: 0,
    gender: WIGender.NONE,
    userId: "m10001",
    userImpressionLimit: 30,
    adPendingTime: 30,          // MỚI
    domainUrl: "",
    env: WIEnvironment.SANDBOX,
    segments: "123,123,123,123"
)
```

---

## Checklist tích hợp

<<<<<<< HEAD:docs/README_1.21.16.md
- [ ] Cập nhật WISDK lên phiên bản mới nhất (>= v1.21.16)
- [ ] Bổ sung tham số `adPendingTime` cho mọi init của `WIAdsRequestData`, `WI3rdBannerAdData`, `WIWelcomeAdData`
=======
- [ ] Cập nhật WISDK lên phiên bản mới nhất (>= v1.21.15)
- [ ] Bổ sung tham số `adPendingTimes` cho mọi init của `WIAdsRequestData`, `WI3rdBannerAdData`, `WIWelcomeAdData`
>>>>>>> e5d542c3fa2901da73047c4e48999641eb233fc8:docs/README_1.21.15.md
- [ ] Build và kiểm tra request gửi lên backend có chứa `apt`
