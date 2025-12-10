import UIKit
import WISDK

extension WI3rdBannerSampleCollectionViewController {
    enum Item {
        case bannerAd(String)
        case other
    }
}

final class WI3rdBannerSampleCollectionViewController: UIViewController, StoryboardInstantiable {
    // MARK: - Outlet
    @IBOutlet weak var collectionView: UICollectionView!
    
    // MARK: - Variable
    private lazy var items: [Item] = []
    private var adManager: WI3rdBannerReusableManager? {
        willSet {
            adManager?.cleanUp()
        }
    }
    
    // MARK: - Life Cycle
    static func instantiate() -> Self {
        let vc = instantiateViewController()
        vc.modalPresentationStyle = .fullScreen
        return vc
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupCollectionView()
        loadData()
    }
    
    deinit {
        adManager = nil
    }
    
    // MARK: - Layout
    private func setupCollectionView() {
        WI3rdBannerReusableManager.registerCell(for: collectionView)
        
        let control = UIRefreshControl()
        control.tintColor = .white
        control.addTarget(target, action: #selector(onRefresh), for: .valueChanged)
        collectionView.refreshControl = control
        collectionView.contentInset = .init(top: 0, left: 12, bottom: 0, right: 12)
    }
    
    // MARK: - Action
    @IBAction func onClosePressed(_ sender: UIButton) {
        dismiss(animated: true)
    }
    
    @objc private func onRefresh() {
        loadData()
        collectionView.refreshControl?.endRefreshing()
    }
}

// MARK: - Data
extension WI3rdBannerSampleCollectionViewController {
    private func loadData() {
        items = (0..<50).map { _ in Item.other }
        collectionView.reloadData()
        
        loadAd()
    }
    
    private func loadAd() {
        let ad1 = WI3rdBannerAdData(
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
            padding: .zero
        )
        
        let ad2 = WI3rdBannerAdData(
            position: "subpage2",
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
            padding: .zero
        )
        
        let adManager = WI3rdBannerReusableManager()
        adManager.request(ads: [ad1, ad2]) { [weak self] pids in
            var indexPaths: [IndexPath] = []
            for pid in pids {
                switch pid {
                case "subpage1":
                    self?.items.insert(.bannerAd(pid), at: 0)
                    indexPaths.append(.init(row: 0, section: 0))
                case "subpage2":
                    self?.items.insert(.bannerAd(pid), at: 4)
                    indexPaths.append(.init(row: 4, section: 0))
                default:
                    break
                }
            }
            if !indexPaths.isEmpty {
                self?.collectionView.insertItems(at: indexPaths)
            }
        }
        self.adManager = adManager
    }
}

// MARK: - UICollectionViewDataSource
extension WI3rdBannerSampleCollectionViewController: UICollectionViewDataSource {
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        items.count
    }
    
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        let item = items[indexPath.row]
        switch item {
        case .bannerAd(let adId):
            guard let cell = adManager?.collectionView(collectionView, cellForItemAt: indexPath, adId: adId) else {
                fatalError("dequeueReusableCell failed")
            }
            return cell
        case .other:
            return collectionView.dequeueReusableCell(withReuseIdentifier: "WI3rdSampleCollectionOtherCell", for: indexPath)
        }
    }
}

// MARK: - UICollectionViewDelegateFlowLayout
extension WI3rdBannerSampleCollectionViewController: UICollectionViewDelegateFlowLayout {
    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, sizeForItemAt indexPath: IndexPath) -> CGSize {
        let item = items[indexPath.row]
        switch item {
        case .bannerAd(let adId):
            let size = adManager?.collectionView(collectionView, layout: collectionViewLayout, sizeForItemAt: indexPath, adId: adId)
            return size ?? .zero
        case .other:
            let width = (collectionView.bounds.width - 12 * 4) / 3
            return .init(width: width, height: 200)
        }
    }
    
    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, minimumLineSpacingForSectionAt section: Int) -> CGFloat {
        12
    }
    
    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, minimumInteritemSpacingForSectionAt section: Int) -> CGFloat {
        12
    }
}
