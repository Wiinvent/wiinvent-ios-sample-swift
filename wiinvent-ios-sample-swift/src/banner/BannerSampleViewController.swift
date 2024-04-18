import UIKit
import WISDK

final class BannerSampleViewController: UIViewController, StoryboardInstantiable {
    // MARK: - IBOutlet
    @IBOutlet weak var firstBannerAdView: UIView!
    @IBOutlet weak var firstBannerAdViewCSHeight: NSLayoutConstraint!
    @IBOutlet weak var secondBannerAdView: UIView!
    @IBOutlet weak var secondBannerAdViewCSHeight: NSLayoutConstraint!
    @IBOutlet weak var thirdBannerAdView: UIView!
    @IBOutlet weak var thirdBannerAdViewCSHeight: NSLayoutConstraint!
    
    // MARK: - Variable
    private lazy var bannerAdManager = {
        let manager = WI3rdBannerAdManager(delegate: self, levelLog: .BODY)
        return manager
    }()
    
    // MARK: - Life Cycle
    static func instantiate() -> Self {
        let vc = instantiateViewController()
        vc.modalPresentationStyle = .fullScreen
        return vc
    }
    
    deinit {
        bannerAdManager.destroy()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        loadBannerAd()
    }
    
    // MARK: - Action
    @IBAction func onClosePressed(_ sender: UIButton) {
        dismiss(animated: true)
    }
    
    // MARK: - Ad
    private func loadBannerAd() {
        loadFirstBannerAd()
        loadSecondBannerAd()
        loadThirdBannerAd()
    }
    
    private func loadFirstBannerAd() {
        bannerAdManager.requestAds(
            requestData: .init(
                accountId: String(14),
                env: .SANDBOX,
                channelId: "998989",
                streamId: "8080",
                transId: "1111",
                contentType: WIContentType.FILM,
                title: "Title phim 1",
                category: "Category 1,Category 2",
                keyword: "keyword1,keyword2",
                age: 30,
                gender: WIGender.MALE,
                adSize: .BANNER,
                uid20: ""
            ),
            containerView: firstBannerAdView,
            timeoutInSecond: 10
        )
    }
    
    private func loadSecondBannerAd() {
        bannerAdManager.requestAds(
            requestData: .init(
                accountId: String(14),
                env: .SANDBOX,
                channelId: "998989",
                streamId: "8080",
                transId: "1111",
                contentType: WIContentType.FILM,
                title: "Title phim 1",
                category: "Category 1,Category 2",
                keyword: "keyword1,keyword2",
                age: 30,
                gender: WIGender.MALE,
                adSize: .LARGE_BANNER,
                uid20: ""
            ),
            containerView: secondBannerAdView,
            timeoutInSecond: 10
        )
    }
    
    private func loadThirdBannerAd() {
        bannerAdManager.requestAds(
            requestData: .init(
                accountId: String(14),
                env: .SANDBOX,
                channelId: "998989",
                streamId: "8080",
                transId: "1111",
                contentType: WIContentType.FILM,
                title: "Title phim 1",
                category: "Category 1,Category 2",
                keyword: "keyword1,keyword2",
                age: 30,
                gender: WIGender.MALE,
                adSize: .RECTANGLE,
                uid20: ""
            ),
            containerView: thirdBannerAdView,
            timeoutInSecond: 10
        )
    }
}

// MARK: - WI3rdBannerAdDelegate
extension BannerSampleViewController: WI3rdBannerAdDelegate {
    func wi3rdBannerAdManager(_ manager: WI3rdBannerAdManager, hasNoAdsAt containerView: UIView?) {
        print(#function)
    }
    
    func wi3rdBannerAdManager(_ manager: WI3rdBannerAdManager, at containerView: UIView?, changeRatio ratio: CGFloat) {
        let height = view.bounds.width / ratio
        if containerView == firstBannerAdView {
            firstBannerAdViewCSHeight.constant = height
        } else if containerView == secondBannerAdView {
            secondBannerAdViewCSHeight.constant = height
        } else if containerView == thirdBannerAdView {
            thirdBannerAdViewCSHeight.constant = height
        }
    }
    
    func wi3rdBannerAdManager(_ manager: WI3rdBannerAdManager, click url: String) {
        guard 
            let url = URL(string: url),
            UIApplication.shared.canOpenURL(url)
        else {
            return
        }
        UIApplication.shared.open(url)
    }
}
