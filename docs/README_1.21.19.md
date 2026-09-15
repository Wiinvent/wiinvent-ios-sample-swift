### Version 1.21.19

# Overlay Banner (Pause Banner) — Hướng dẫn tích hợp

## Tổng quan

`WIAdBannerManager` là API dành cho **quảng cáo overlay hiển thị khi người dùng tạm dừng video**.

Backend quyết định dạng banner nào được trả về, và **mỗi dạng có một vị trí riêng trên player**:

| Dạng | Vị trí trên player |
|---|---|
| `PAUSE_BANNER` | dưới, canh giữa |
| `CENTER_BANNER` | canh giữa player |
| `TRANSPARENT_BANNER` | canh giữa theo chiều dọc, sát lề phải |

Vì vậy quy trình là: **ứng dụng gửi một request → SDK trả về view đã dựng sẵn kèm vị trí → ứng dụng tự gắn view vào giao diện của mình.**

SDK **không** tự gắn view vào cây giao diện của ứng dụng và **không** yêu cầu một view phủ lên player. Ứng dụng toàn quyền quyết định layout.

> Nếu bạn đã quen `GADBannerView` của Google Ad Manager thì mô hình ở đây tương tự: banner là một object ứng dụng sở hữu và tự đặt chỗ.

---

## Cài đặt

```ruby
pod 'WISDK', '1.21.19'
```

---

## Các kiểu dữ liệu công khai

| Kiểu | Vai trò |
|---|---|
| `WIAdBannerManager` | Gửi request, quản lý vòng đời banner |
| `WIAdBannerRequest` | Thông tin request |
| `WIAdBannerDelegate` | Nhận kết quả |
| `WIAdBannerPlacement` | Gói kết quả: view + vị trí + kích thước |
| `WIAdBannerView` | View quảng cáo, ứng dụng tự gắn vào giao diện |
| `WIAdBannerPosition` | `.bottomCenter` / `.center` / `.centerRight` |
| `WIAdBannerSize` | `.PAUSE_BANNER` / `.CENTER_BANNER` / `.TRANSPARENT_BANNER` |
| `WIAdBannerError` + `WIAdBannerErrorCode` | Thông tin lỗi |

---

## Tích hợp

### Bước 1 — Khởi tạo manager

Mỗi màn hình player dùng một instance riêng. Manager **không giữ** delegate (weak reference) nên không gây retain cycle.

```swift
import WISDK

final class PlayerViewController: UIViewController {
    private var bannerAdManager: WIAdBannerManager?
    private var adConstraints: [NSLayoutConstraint] = []

    override func viewDidLoad() {
        super.viewDidLoad()
        bannerAdManager = WIAdBannerManager(delegate: self)
    }

    deinit {
        bannerAdManager?.destroy()
    }
}
```

### Bước 2 — Request khi người dùng pause, gỡ khi play lại

```swift
@IBAction func onPlayPausePressed(_ sender: UIButton) {
    isPlaying.toggle()
    if isPlaying {
        bannerAdManager?.destroyPauseBanner()   // SDK tự gỡ view khỏi giao diện
    } else {
        requestPauseBanner()
    }
}

private func requestPauseBanner() {
    let request = WIAdBannerRequest(
        position: "POSITION_ID",
        accountId: "ACCOUNT_ID",
        env: .PRODUCTION,
        channelId: "998989",
        streamId: "119",
        transId: "1111",
        contentType: .FILM,
        title: "Tên nội dung đang xem",
        category: "Category 1,Category 2",
        keyword: "keyword1,keyword2",
        age: 30,
        gender: .MALE,
        // Khai báo những dạng banner ứng dụng của bạn render được.
        validAdSizes: [.PAUSE_BANNER, .CENTER_BANNER, .TRANSPARENT_BANNER],
        userId: "m10001",
        userImpressionLimit: 30,
        segments: "123,123,123"
    )
    bannerAdManager?.requestAd(request)
}
```

**`validAdSizes`** — chỉ khai những dạng bạn thực sự dựng được vị trí. Dạng không khai báo sẽ không được hiển thị. Nếu chỉ hỗ trợ banner dưới đáy, khai `[.PAUSE_BANNER]`.

### Bước 3 — Gắn view khi nhận được quảng cáo

Đây là phần thay thế cho việc truyền sẵn container trước đây.

```swift
extension PlayerViewController: WIAdBannerDelegate {
    func wiAdBannerManager(_ manager: WIAdBannerManager, didReceive placement: WIAdBannerPlacement) {
        let adView = placement.adView
        playerView.addSubview(adView)

        // Chỉ cần 2 ràng buộc VỊ TRÍ, chọn theo placement.position
        var constraints: [NSLayoutConstraint]
        switch placement.position {
        case .bottomCenter:
            constraints = [
                adView.centerXAnchor.constraint(equalTo: playerView.centerXAnchor),
                adView.bottomAnchor.constraint(equalTo: playerView.bottomAnchor, constant: -16),
            ]
        case .center:
            constraints = [
                adView.centerXAnchor.constraint(equalTo: playerView.centerXAnchor),
                adView.centerYAnchor.constraint(equalTo: playerView.centerYAnchor),
            ]
        case .centerRight:
            constraints = [
                adView.trailingAnchor.constraint(equalTo: playerView.trailingAnchor, constant: -16),
                adView.centerYAnchor.constraint(equalTo: playerView.centerYAnchor),
            ]
        }

        NSLayoutConstraint.activate(constraints)
        adConstraints = constraints   // giữ lại để gỡ ở bước 4
    }
}
```

#### Kích thước — chọn một trong hai cách

**Cách 1 (khuyến nghị): để SDK tự lo.** Không set width/height. Banner tự tính kích thước theo player.

```swift
adView.referenceView = playerView
```

`referenceView` là view làm mốc để tính kích thước, thường là khung video. Nếu không set, SDK dùng view cha mà bạn vừa gắn vào.

> Lưu ý: hãy trỏ `referenceView` tới **đúng khung hình video**. Nếu trỏ vào một view bọc lớn hơn (chứa cả thanh điều khiển) thì banner sẽ được tính theo view đó.

**Cách 2: tự tính.** Dùng khi bạn bố trí bằng frame hoặc muốn tự kiểm soát.

```swift
let size = placement.size(inPlayerSize: playerView.bounds.size)
constraints += [
    adView.widthAnchor.constraint(equalToConstant: size.width),
    adView.heightAnchor.constraint(equalToConstant: size.height),
]
```

#### Tránh vùng safe area

Khi player chạy fullscreen, mép dưới và mép phải có thể trùng với home indicator hoặc Dynamic Island. Nên neo banner vào phần giao giữa player và safe area:

```swift
// Tạo một lần trong viewDidLoad
view.addLayoutGuide(adAreaGuide)
let safe = view.safeAreaLayoutGuide
NSLayoutConstraint.activate([
    adAreaGuide.topAnchor.constraint(greaterThanOrEqualTo: playerView.topAnchor),
    adAreaGuide.topAnchor.constraint(greaterThanOrEqualTo: safe.topAnchor),
    adAreaGuide.leadingAnchor.constraint(greaterThanOrEqualTo: playerView.leadingAnchor),
    adAreaGuide.leadingAnchor.constraint(greaterThanOrEqualTo: safe.leadingAnchor),
    adAreaGuide.bottomAnchor.constraint(lessThanOrEqualTo: playerView.bottomAnchor),
    adAreaGuide.bottomAnchor.constraint(lessThanOrEqualTo: safe.bottomAnchor),
    adAreaGuide.trailingAnchor.constraint(lessThanOrEqualTo: playerView.trailingAnchor),
    adAreaGuide.trailingAnchor.constraint(lessThanOrEqualTo: safe.trailingAnchor),
])

// Và bám sát player khi safe area không siết
for constraint in [
    adAreaGuide.topAnchor.constraint(equalTo: playerView.topAnchor),
    adAreaGuide.leadingAnchor.constraint(equalTo: playerView.leadingAnchor),
    adAreaGuide.bottomAnchor.constraint(equalTo: playerView.bottomAnchor),
    adAreaGuide.trailingAnchor.constraint(equalTo: playerView.trailingAnchor),
] {
    constraint.priority = .defaultHigh
    constraint.isActive = true
}
```

Sau đó ở bước 3 neo banner vào `adAreaGuide` thay cho `playerView`, nhưng **`referenceView` vẫn để là `playerView`** (kích thước tính theo player, vị trí tránh safe area).

### Bước 4 — Dọn constraint khi SDK gỡ view

SDK tự gỡ view khỏi giao diện khi người dùng play lại, khi bấm nút đóng, hoặc khi player đổi kích thước. Sau đó báo lại cho ứng dụng:

```swift
func wiAdBannerManager(_ manager: WIAdBannerManager, didRemove bannerView: WIAdBannerView) {
    NSLayoutConstraint.deactivate(adConstraints)
    adConstraints = []
}
```

### Bước 5 — Xử lý trường hợp không có quảng cáo

```swift
func wiAdBannerManager(_ manager: WIAdBannerManager, didFailToReceiveAdWithError error: Error) {
    // Không có quảng cáo phù hợp. Giữ player sạch, không hiển thị gì.
    if let bannerError = error as? WIAdBannerError {
        print("Banner error:", bannerError.bannerErrorCode)
    }
}
```

`WIAdBannerErrorCode` gồm: `.network`, `.decode`, `.noFill`, `.unknownAdSize`, `.unsupportedAdSize`, `.adSizeNotRequested`, `.renderTimeout`, `.cancelled`. Ứng dụng xử lý giống nhau cho mọi mã — mã lỗi chỉ để ghi log và debug.

---

## Các callback tuỳ chọn

```swift
/// Được hỏi ngay trước didReceive. Trả về false để bỏ qua quảng cáo.
/// Dùng khi response về muộn mà người dùng đã bấm play lại.
func wiAdBannerManagerShouldDisplayAd(_ manager: WIAdBannerManager) -> Bool {
    !isPlaying
}

/// Lượt hiển thị đã được ghi nhận.
func wiAdBannerManager(_ m: WIAdBannerManager, didRecordImpressionFor v: WIAdBannerView) { }

/// Người dùng bấm nút đóng trên banner.
func wiAdBannerManager(_ m: WIAdBannerManager, didSkip v: WIAdBannerView) { }

/// Người dùng bấm vào quảng cáo. Chỉ gọi với campaign cấu hình xử lý phía ứng dụng;
/// các campaign mở trình duyệt sẽ được SDK mở sẵn và không gọi callback này.
func wiAdBannerManager(_ m: WIAdBannerManager, didClick url: String) { }
```

---

## Xoay màn hình và đổi kích thước player

**Ứng dụng không cần làm gì thêm.**

SDK tự phát hiện player đổi kích thước — xoay màn hình, vào/ra fullscreen, Split View, Picture in Picture — và **tự co giãn banner tại chỗ**. Quảng cáo đang hiển thị được giữ nguyên: không bị gỡ ra gắn lại, không nháy, không phát sinh callback nào.

Nếu bạn muốn lấy quảng cáo mới cho hướng màn hình mới thì tự gọi `requestAd` — đó là quyền quyết định của ứng dụng:

```swift
override func viewWillTransition(to size: CGSize, with coordinator: UIViewControllerTransitionCoordinator) {
    super.viewWillTransition(to: size, with: coordinator)
    coordinator.animate(alongsideTransition: nil) { [weak self] _ in
        self?.requestPauseBanner()
    }
}
```

---

## API quản lý vòng đời

| Hàm | Tác dụng |
|---|---|
| `destroyPauseBanner()` | Gỡ banner đang hiển thị. Dùng khi người dùng play lại |
| `destroy()` | Gỡ banner và huỷ request đang chờ. Gọi trong `deinit` |
| `destroy(_ bannerView:)` | Gỡ một banner cụ thể |
| `cancelPendingRequests()` | Huỷ request đang chờ, không đụng banner đang hiển thị |

---

## Nút đóng và nút báo cáo

SDK tự gắn sẵn vào banner:

- **Badge "QC"** ở góc trên trái
- **Nút báo cáo** ở góc trên phải — mở bottom sheet báo cáo quảng cáo
- **Nút đóng (✕)** cạnh nút báo cáo

Nút đóng **không hiện ngay**. Nó xuất hiện sau một khoảng chờ do hệ thống quảng cáo cấu hình cho từng chiến dịch; nếu chiến dịch không cấu hình khoảng chờ thì banner không có nút đóng. Ứng dụng không cần và không nên tự vẽ nút đóng.

Khoảng chờ này **không bị đặt lại khi xoay màn hình**. Kể cả khi ứng dụng tự gọi `requestAd` lại trong cùng một lần tạm dừng, phần thời gian đã chờ vẫn được tính tiếp.

Khi người dùng bấm nút đóng, SDK gỡ banner rồi gọi `didSkip` và `didRemove`.

---

## Lượt hiển thị (impression)

Lượt hiển thị chỉ được ghi nhận **khi banner thực sự xuất hiện trên màn hình**. Nếu ứng dụng nhận `didReceive` nhưng không gắn view vào giao diện thì không có lượt hiển thị nào được tính.

Đây là điểm khác so với cách tích hợp banner cũ, và là lý do **việc gắn view ở bước 3 là bắt buộc** nếu bạn muốn quảng cáo được ghi nhận.

---

## Objective-C

`WIAdBannerSize` là enum nên mảng của nó không bridge sang Objective-C. Truyền qua `NSNumber`:

```objc
WIAdBannerRequest *request =
    [[WIAdBannerRequest alloc] initWithPosition:@"POSITION_ID"
                                      accountId:@"ACCOUNT_ID"
                                            env:WIEnvironmentPRODUCTION
                                      channelId:@"998989"
                                       streamId:@"119"
                                        transId:@"1111"
                                    contentType:WIContentTypeFILM
                                          title:@"Tên nội dung"
                                       category:@"Category 1"
                                        keyword:@""
                                            age:30
                                         gender:WIGenderMALE
                              validAdSizeValues:WIAdBannerRequest.defaultAdSizeValues
                                         userId:@"m10001"
                            userImpressionLimit:30
                                       segments:@""
                                   cacheTimeSec:300];

WIAdBannerManager *manager = [[WIAdBannerManager alloc] initWithDelegate:self];
[manager requestAd:request timeoutInSecond:10];
```

`WIAdBannerRequest.defaultAdSizeValues` là danh sách đầy đủ các dạng SDK hỗ trợ.

---

## Checklist trước khi release

- [ ] Gọi `destroy()` trong `deinit` của màn hình player
- [ ] Gắn view vào giao diện trong `didReceive` — nếu không, không có lượt hiển thị
- [ ] Gỡ constraint trong `didRemove`
- [ ] Chỉ khai trong `validAdSizes` những dạng đã dựng đủ 3 vị trí
- [ ] Set `referenceView` đúng khung video nếu dùng cách 1
- [ ] Kiểm tra cả 3 dạng banner ở cả màn hình dọc và ngang
- [ ] Kiểm tra nút đóng và nút báo cáo không bị che và bấm được ở mọi hướng màn hình
- [ ] Bấm pause/play liên tục nhiều lần, xác nhận không có banner nào hiển thị khi đang phát
- [ ] Xoay màn hình khi banner đang hiện: banner co giãn theo, không nháy, nút đóng không mất

---

## Những lỗi thường gặp

| Hiện tượng | Nguyên nhân |
|---|---|
| Banner không hiển thị dù có `didReceive` | Chưa gắn view vào giao diện, hoặc gắn nhưng thiếu constraint vị trí |
| Banner có vị trí nhưng kích thước bằng 0 | Dùng cách 1 nhưng chưa set `referenceView`, và view cha không có kích thước xác định |
| Banner sai kích thước khi fullscreen | `referenceView` đang trỏ vào view bọc thay vì khung video |
| Banner bị home indicator che | Neo trực tiếp vào player thay vì phần giao với safe area |
| Không có lượt hiển thị | View chưa được gắn vào giao diện |
| Banner còn trên màn hình sau khi play | Chưa gọi `destroyPauseBanner()` khi play lại |
| Banner nháy khi xoay màn hình | Ứng dụng đang tự gọi `requestAd` trong `viewWillTransition`; bỏ đi nếu không thực sự cần quảng cáo mới |
| Không thấy nút đóng | Chiến dịch không cấu hình khoảng chờ hiện nút đóng — không phải lỗi tích hợp |

---

## Hỗ trợ

Khi báo lỗi, vui lòng kèm:

- Phiên bản SDK và phiên bản iOS
- Dạng banner gặp lỗi (`placement.adSize`)
- Hướng màn hình và trạng thái player (fullscreen hay không)
- Ảnh chụp màn hình

Bật log chi tiết khi debug:

```swift
WILogger.isEnabled = true
let manager = WIAdBannerManager(delegate: self, levelLog: .BODY)
```
