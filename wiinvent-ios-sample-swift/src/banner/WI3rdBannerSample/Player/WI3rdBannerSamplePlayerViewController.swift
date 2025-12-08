import UIKit
import WISDK
import AVFoundation

final class WI3rdBannerSamplePlayerViewController: UIViewController, StoryboardInstantiable, WILoggable {
    // MARK: - IBOutlet
    @IBOutlet weak var largeAdView: UIView!
    @IBOutlet weak var largeAdViewCSHeight: NSLayoutConstraint!
    @IBOutlet weak var largeRequestButton: UIButton!
    
    @IBOutlet weak var mediumAdView: UIView!
    @IBOutlet weak var mediumAdViewCSHeight: NSLayoutConstraint!
    @IBOutlet weak var mediumRequestButton: UIButton!
    
    @IBOutlet weak var playerView: AVPlayerView!
    @IBOutlet weak var pauseButton: UIButton!
    @IBOutlet weak var overlayAdView: UIView!
    @IBOutlet weak var overlayAdViewCSHeight: NSLayoutConstraint!
        
    // MARK: - Variable
    private var bannerAdManager: WI3rdBannerAdManager?
    
    private lazy var isPlaying = false {
        didSet {
            if isPlaying {
                pauseButton.setImage(.init(systemName: "pause.fill"), for: .normal)
                playerView.player?.play()
            } else {
                pauseButton.setImage(.init(systemName: "play.fill"), for: .normal)
                playerView.player?.pause()
            }
            log("Player:", isPlaying ? "playing" : "paused")
        }
    }
    
    // MARK: - Life Cycle
    static func instantiate() -> Self {
        let vc = instantiateViewController()
        vc.modalPresentationStyle = .fullScreen
        return vc
    }
    
    deinit {
        bannerAdManager?.destroy()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupAdManager()
        setupPlayer()
    }
    
    // MARK: - Action
    @IBAction func onClosePressed(_ sender: UIButton) {
        dismiss(animated: true)
    }
    
    @IBAction func onPausePressed(_ sender: UIButton) {
        isPlaying.toggle()
        if isPlaying {
            bannerAdManager?.destroyPauseBanner()
        } else {
            loadBannerAdOverlay()
        }
    }
    
    @IBAction func onRemoveAdsPressed(_ sender: UIButton) {
        bannerAdManager?.destroy()
    }
    
    @IBAction func onRequestLargePressed(_ sender: UIButton) {
        largeRequestButton.isHidden = true
        loadBannerLarge()
    }
    
    @IBAction func onRequestMediumPressed(_ sender: UIButton) {
        mediumRequestButton.isHidden = true
        loadBannerMedium()
    }
    
    // MARK: - Ad
    private func setupAdManager() {
        self.bannerAdManager = WI3rdBannerAdManager(delegate: self, levelLog: .BODY)
    }
    
    private func loadBannerLarge() {
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
                adSize: .LARGE_BANNER,
                uid20: "",
                segments: "123,123,123",
                bannerType: .display
            ),
            containerView: largeAdView,
            timeoutInSecond: 10
        )
    }
    
    private func loadBannerMedium() {
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
                adSize: .MEDIUM_BANNER,
                uid20: "",
                segments: "123,123,123",
                bannerType: .display
            ),
            containerView: mediumAdView,
            timeoutInSecond: 10
        )
    }
    
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
}

// MARK: - Player
extension WI3rdBannerSamplePlayerViewController {
    private func setupPlayer() {
        let url = URL(string: "http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/BigBuckBunny.mp4")!
        let player = AVPlayer(url: url)
        playerView.player = player
        isPlaying = true
    }
}

// MARK: - WI3rdBannerAdDelegate
extension WI3rdBannerSamplePlayerViewController: WI3rdBannerAdDelegate {
    func wi3rdBannerAdManager(_ manager: WI3rdBannerAdManager, hasNoAdsAt containerView: UIView?) {
        print(#function)
    }
    
    func wi3rdBannerAdManager(_ manager: WI3rdBannerAdManager, at containerView: UIView?, changeRatio ratio: CGFloat) {
        let height = view.bounds.width / ratio
        if containerView == largeAdView {
            largeAdViewCSHeight.constant = height
        } else if containerView == mediumAdView {
            mediumAdViewCSHeight.constant = height
        } else if containerView == overlayAdView {
            overlayAdViewCSHeight.constant = height
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
    
    func wi3rdBannerAdManager(_ manager: WI3rdBannerAdManager, hasNoAdAt containerView: UIView?) {
        print(#function)
    }
    
    func wi3rdBannerAdManager(_ manager: WI3rdBannerAdManager, skipAdAt containerView: UIView?) {
        print(#function)
        if containerView == largeAdView {
            largeAdViewCSHeight.constant = 0
        } else if containerView == mediumAdView {
            mediumAdViewCSHeight.constant = 0
        } else if containerView == overlayAdView {
            overlayAdViewCSHeight.constant = 0
        }
    }
    
    func wi3rdBannerAdManager(_ manager: WI3rdBannerAdManager, pauseBannerVisibleAt containerView: UIView?) -> Bool {
        return !isPlaying
    }
}
