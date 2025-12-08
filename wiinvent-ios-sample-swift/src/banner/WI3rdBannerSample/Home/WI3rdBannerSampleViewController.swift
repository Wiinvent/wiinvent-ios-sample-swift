import UIKit

final class WI3rdBannerSampleViewController: UIViewController, StoryboardInstantiable {
    
    @IBAction func onPlayerPressed(_ sender: UIButton) {
        let vc = WI3rdBannerSamplePlayerViewController.instantiate()
        present(vc, animated: true)
    }
    
    @IBAction func onTableViewPressed(_ sender: UIButton) {
        let vc = WI3rdBannerSampleTableViewController.instantiate()
        present(vc, animated: true)
    }
    
    @IBAction func onCollectionViewPressed(_ sender: UIButton) {
        let vc = WI3rdBannerSampleCollectionViewController.instantiate()
        present(vc, animated: true)
    }
    
    @IBAction func onClosePressed(_ sender: UIButton) {
        dismiss(animated: true)
    }
    
    static func instantiate() -> Self {
        let vc = instantiateViewController()
        vc.modalPresentationStyle = .fullScreen
        return vc
    }
}
