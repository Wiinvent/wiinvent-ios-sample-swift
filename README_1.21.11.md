# Report Ad — Huong dan tich hop

## Tong quan

Tu phien ban v1.21.11, WISDK ho tro tinh nang **Report Ad** cho phep nguoi dung bao cao quang cao khong phu hop. Tinh nang nay da duoc tich hop san trong SDK cho cac dinh dang:

- **Banner Ad** (Image & WebView)
- **In-Stream Ad** (AVPlayer & Bitmovin)
- **Welcome Ad**

**Report button va bottom sheet duoc SDK tu dong xu ly.** Ung dung khong can them code de hien report button.

Tuy nhien, voi **In-Stream Ad**, ung dung can implement them 2 delegate method moi de skip button pause/resume dung khi nguoi dung dang bao cao.

---

## Thay doi cho In-Stream Ad

### Implement delegate methods moi

`WIAdsInStreamLoaderDelegate` co them 2 optional method:

```swift
@objc optional func wiPauseSkipButton()
@objc optional func wiResumeSkipButton()
```

Ung dung **nen** implement 2 method nay de skip button countdown dung lai khi nguoi dung mo report, va tiep tuc dem khi dong.

**Vi du:**

```swift
// Trong class conform WIAdsInStreamLoaderDelegate
func wiPauseSkipButton() {
    skipButton?.pause()   // Tam dung countdown cua skip button
}

func wiResumeSkipButton() {
    skipButton?.resume()  // Tiep tuc countdown cua skip button
}
```

> **Luu y:** 2 method nay la `optional`. Neu khong implement, report van hoat dong binh thuong nhung skip button se tiep tuc dem nguoc trong khi bottom sheet dang hien.

---

## Thay doi cho Banner Ad

**Khong can thay doi gi.** Report button tu dong hien sau khi ad load thanh cong.

---

## Thay doi cho Welcome Ad

**Khong can thay doi gi.** Report button tu dong hien khi welcome ad hien thi. Button tu dong bi xoa khi goi `WIWelcomeAdManager.shared().remove()`.

---

## Checklist tich hop

- [ ] Cap nhat WISDK len phien ban moi nhat (>= v1.21.11)
- [ ] **(In-Stream)** Implement `wiPauseSkipButton()` va `wiResumeSkipButton()` trong delegate
- [ ] Build va kiem tra report button hien tren moi dinh dang quang cao
- [ ] Kiem tra bottom sheet hoat dong: chon ly do, gui, toast xac nhan
