# Report Ad — Hướng dẫn tích hợp

### Version 1.21.11
Change log: WISDK hỗ trợ tính năng hiển thị quảng cáo welcome dạng dọc **Report Ad** cho phép người dùng báo cáo quảng cáo không phù hợp. Tính năng này đã được tích hợp sẵn trong SDK cho các định dạng:

- **Banner Ad** (Image & WebView)
- **In-Stream Ad** (AVPlayer & Bitmovin)
- **Welcome Ad**

**Report button và bottom sheet được SDK tự động xử lý.** Ứng dụng không cần thêm code để hiện report button.

Tuy nhiên, với **In-Stream Ad**, ứng dụng cần implement thêm 2 delegate method mới để skip button pause/resume đúng khi người dùng đang báo cáo.

#### 1. SDK
```gralde
pod 'WISDK', '1.21.11'
```

---

## Thay đổi cho In-Stream Ad

### Implement delegate methods mới

`WIAdsInStreamLoaderDelegate` có thêm 2 optional method:

```swift
@objc optional func wiPauseSkipButton()
@objc optional func wiResumeSkipButton()
```

Ứng dụng **nên** implement 2 method này để skip button countdown dừng lại khi người dùng mở report, và tiếp tục đếm khi đóng.

**Ví dụ:**

```swift
// Trong class conform WIAdsInStreamLoaderDelegate
func wiPauseSkipButton() {
    skipButton?.pause()   // Tạm dừng countdown của skip button
}

func wiResumeSkipButton() {
    skipButton?.resume()  // Tiếp tục countdown của skip button
}
```

> **Lưu ý:** 2 method này là `optional`. Nếu không implement, report vẫn hoạt động bình thường nhưng skip button sẽ tiếp tục đếm ngược trong khi bottom sheet đang hiện.

---

## Thay đổi cho Banner Ad

**Không cần thay đổi gì.** Report button tự động hiện sau khi ad load thành công.

---

## Thay đổi cho Welcome Ad

**Không cần thay đổi gì.** Report button tự động hiện khi welcome ad hiển thị. Button tự động bị xóa khi gọi `WIWelcomeAdManager.shared().remove()`.

---

## Checklist tích hợp

- [ ] Cập nhật WISDK lên phiên bản mới nhất (>= v1.21.11)
- [ ] **(In-Stream)** Implement `wiPauseSkipButton()` và `wiResumeSkipButton()` trong delegate
- [ ] Build và kiểm tra report button hiện trên mọi định dạng quảng cáo
- [ ] Kiểm tra bottom sheet hoạt động: chọn lý do, gửi, toast xác nhận
