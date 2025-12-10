
### Version 1.21.8
Change log: Hỗ trợ quảng cáo banner

#### 1. SDK
```gralde
pod 'WISDK', '1.21.8'
```

#### 2. Hướng dẫn cập nhật
#### 2.1 Tích hợp quảng cáo display dùng cho trang chủ, chi tiết (dùng cho tableview, collection)

```java
 private func loadAd() {
  
  // Khơi tạo các tham số 
  let bannerLarge = WI3rdBannerAdData(
      position: "subpage1",
      accountId: String(14),
      env: .SANDBOX,
      channelId: "",
      streamId: "",
      transId: "1111",
      contentType: WIContentType.FILM,
      title: "Highlights Áo vs Thổ Nhĩ Kỳ | Giao Hữu Quốc Tế 2024",
      category: "Category 1,Category 2",
      keyword: "keyword1,keyword2",
      age: 30,
      gender: WIGender.MALE,
      adSize: .MEDIUM_BANNER,
      uid20: "",
      segments: "123,123,123",
      bannerType: .display,
      padding: .init(top: 0, left: 12, bottom: 0, right: 12)
        )
  // Request lấy campaign quảng cáo và lắng nghe các sự kiện 
  let adManager = WI3rdBannerReusableManager()
  adManager.request(ads: [bannerLarge]) { [weak self] pids in
    var indexPaths: [IndexPath] = []
    for pid in pids {
      switch pid {
        case "subpage1":
          self?.items.insert(.bannerAd(pid), at: 0)
          indexPaths.append(.init(row: 0, section: 0))
        case "subpage2":
          self?.items.insert(.bannerAd(pid), at: 2)
          indexPaths.append(.init(row: 2, section: 0))
        default:
          break
      }
    }
    if !indexPaths.isEmpty {
      self?.tableView.insertRows(at: indexPaths, with: .none)
    }
  }
  self.adManager = adManager
}
```

Code mẫu full WI3rdBannerSampleCollectionViewController

#### 2.2 Tích hợp quảng cáo overlays (dùng cho quảng cáo pause player)
```java
    private var bannerAdManager: WI3rdBannerAdManager?

    // Khoi tao 
    private func setupAdManager() {
      self.bannerAdManager = WI3rdBannerAdManager(delegate: self, levelLog: .BODY)
    }
    
    //thuc hien request 
    private func loadBannerAdOverlay() {
      bannerAdManager?.requestAds(
          requestData: .init(
          position: "",
          accountId: String(14),
          env: .SANDBOX,
          channelId: "",
          streamId: "",
          transId: "1111",
          contentType: WIContentType.FILM,
          title: "Highlights Áo vs Thổ Nhĩ Kỳ | Giao Hữu Quốc Tế 2024",
          category: "Category 1,Category 2",
          keyword: "keyword1,keyword2",
          age: 30,
          gender: WIGender.MALE,
          adSize: .PAUSE_BANNER,
          uid20: "",
          segments: "123,123,123",
          bannerType: .overlay
            ),
      containerView: overlayAdView,
          timeoutInSecond: 10
        )
    }
```

Code mẫu full WI3rdBannerSamplePlayerViewController

#### 3. Mô tả các tham số

| Key                   | Description                                                                       |       Type |
|:----------------------|:----------------------------------------------------------------------------------|-----------:|
| tenantId / accountId  | id đối tác được cung cấp bởi wiinvent                                             |    integer |
| position              | Id vị trí quảng cáo, dùng để phân biệt các vị trí quảng cáo trong một màn hình    |     string |
| channelId             | Danh sách id của category của nội dung & cách nhau bằng dấu ","                   |     string |
| category              | Danh sach tiêu đề category của nội dung & cách nhau bằng dấu ","                  |     string |
| streamId              | Id nội dung                                                                       |     string |
| title                 | Tiêu đề của nội dung                                                              |     string |
| vastLoadTimeout       | Vast Load Timeout                                                                 |    integer |
| mediaLoadTimeout      | Media Load Timeout                                                                |    integer |
| bufferingVideoTimeout | Buffering Video Timeout                                                           |    integer |                                  
| partnerSkipOffset     | Skip Ad Duration                                                                  |    integer |                                  
| env                   | Môi trường sanbox hoặc production                                                 |   constant |
| thirdPartyToken       | JWT Token from partner                                                            |     string |
| alwaysCustomSkip      | Biến hiển thị nút skip mặc định hay custom                                        |    boolean |
| bitrate               | max bitrate cho quảng cáo tvc                                                     |     number |
| tranId                | Mã giao dịch tạo từ server đối tác - client liên hệ server để biết thêm thông tin |     string |
| keyword               | Từ khoá tìm kiếm của nội dung (nếu có)                                            |     string |
| age                   | Tuổi (Nếu có)                                                                     |     number |
| gender                | Giới tính (nếu có)                                                                |   constant |
| uid20                 | Unified id 2.0 (nếu có)                                                           |     string |
| domainUrl             | link resource cdn của định dạng banner welcome                                    |     string |
| logLevel              | level của log , môi trường PRODUCTION cần set về mức NONE                         |     string |
| adSize                | Loại banner theo kích thước                                                       |   constant |
| contentType           | Loại nội dung là film, video hoặc tv                                              |   constant |
| bannerType            | Có 2 loại display và overlay                                                      |   constant |

#### 4. Hằng số

| Key         | Description                                                                                    |
|:------------|:-----------------------------------------------------------------------------------------------|
| env         | Environment.SANDBOX <br/> WI.Environment.PRODUCTION                                            |
| contentType | WIContentType.TV <br/>WIContentType.FILM <br/>WIContentType.VIDEO <br/>WIContentType.SHORT_VOD |
| gender      | WIGender.MALE <br/> WIGender.FEMALE <br/> WIGender.OTHER <br/> WIGender.NONE                   |
| logLevel    | LevelLog.NONE <br/> LevelLog.BODY                                                              |
| adSize      | .PAUSE_BANNER <br/> .MEDIUM_BANNER <br/> .LARGE_BANNER                                         |