#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"

using namespace std;
using namespace edm;

void setbit(UShort_t& x, UShort_t bit) {
  UShort_t a = 1;
  x |= (a << bit);
}

lldjNtuple::lldjNtuple(const edm::ParameterSet& ps) {

  // electrons
  electronCollection_        = consumes<View<pat::Electron> >          (ps.getParameter<InputTag>("electronSrc"));
  rhoLabel_                  = consumes<double>                        (ps.getParameter<InputTag>("rhoLabel"));
  // electron ID 
  eleVetoIdMapToken_       = consumes<edm::ValueMap<bool> >(ps.getParameter<edm::InputTag>("eleVetoIdMap"));
  eleLooseIdMapToken_      = consumes<edm::ValueMap<bool> >(ps.getParameter<edm::InputTag>("eleLooseIdMap"));
  eleMediumIdMapToken_     = consumes<edm::ValueMap<bool> >(ps.getParameter<edm::InputTag>("eleMediumIdMap"));
  eleTightIdMapToken_      = consumes<edm::ValueMap<bool> >(ps.getParameter<edm::InputTag>("eleTightIdMap"));
  eleHLTIdMapToken_        = consumes<edm::ValueMap<bool> >(ps.getParameter<edm::InputTag>("eleHLTIdMap"));
  //eleHEEPIdMapToken_       = consumes<edm::ValueMap<bool> >(ps.getParameter<edm::InputTag>("eleHEEPIdMap"));
  //eleMVAValuesMapToken_    = consumes<edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("eleMVAValuesMap"));
  //eleMVAHZZValuesMapToken_ = consumes<edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("eleMVAHZZValuesMap"));
  //elePFClusEcalIsoToken_   = mayConsume<edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("elePFClusEcalIsoProducer"));
  //elePFClusHcalIsoToken_   = mayConsume<edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("elePFClusHcalIsoProducer"));

  // global event
  rhoCentralLabel_           = consumes<double>                        (ps.getParameter<InputTag>("rhoCentralLabel"));
  puCollection_              = consumes<vector<PileupSummaryInfo> >    (ps.getParameter<InputTag>("pileupCollection"));
  vtxLabel_                  = consumes<reco::VertexCollection>        (ps.getParameter<InputTag>("VtxLabel"));
  trgResultsLabel_           = consumes<edm::TriggerResults>           (ps.getParameter<InputTag>("triggerResults"));
  trgResultsProcess_         =                                          ps.getParameter<InputTag>("triggerResults").process();

  // jets
  jetsAK4Label_              = consumes<View<pat::Jet> >               (ps.getParameter<InputTag>("ak4JetSrc"));
  AODak4CaloJetsLabel_       = consumes<View<reco::CaloJet> >          (ps.getParameter<InputTag>("AODak4CaloJetsSrc"));  
  AODak4PFJetsLabel_         = consumes<View<reco::PFJet>   >          (ps.getParameter<InputTag>("AODak4PFJetsSrc"));    
  AODak4PFJetsCHSLabel_      = consumes<View<reco::PFJet>   >          (ps.getParameter<InputTag>("AODak4PFJetsCHSSrc")); 

  // met
  patTrgResultsLabel_        = consumes<edm::TriggerResults>           (ps.getParameter<InputTag>("patTriggerResults"));
  BadChCandFilterToken_      = consumes<bool>                          (ps.getParameter<InputTag>("BadChargedCandidateFilter"));
  BadPFMuonFilterToken_      = consumes<bool>                          (ps.getParameter<edm::InputTag>("BadPFMuonFilter"));
  pfMETlabel_                = consumes<View<pat::MET> >               (ps.getParameter<InputTag>("pfMETLabel"));

  // muons
  muonCollection_            = consumes<View<pat::Muon> >              (ps.getParameter<InputTag>("muonSrc"));

  // photons
  photonCollection_          = consumes<View<pat::Photon> >            (ps.getParameter<InputTag>("photonSrc"));


  //triggerObjectsLabel_       = consumes<pat::TriggerObjectStandAloneCollection>(ps.getParameter<edm::InputTag>("triggerEvent"));


  //beamspotToken_             = consumes<reco::BeamSpot>(ps.getUntrackedParameter<edm::InputTag> ("beamspot",edm::InputTag("offlineBeamSpot")));

  //doGenParticles_            = ps.getParameter<bool>("doGenParticles");
  //dumpJets_                  = ps.getParameter<bool>("dumpJets");
  //dumpSubJets_               = ps.getParameter<bool>("dumpSubJets");
  //dumpSoftDrop_              = ps.getParameter<bool>("dumpSoftDrop");
  //dumpTaus_                  = ps.getParameter<bool>("dumpTaus");
  ////dumpPDFSystWeight_         = ps.getParameter<bool>("dumpPDFSystWeight");


   //  // Photon ID in VID framwork 
   //  phoLooseIdMapToken_             = consumes<edm::ValueMap<bool> >(ps.getParameter<edm::InputTag>("phoLooseIdMap"));
   //  phoMediumIdMapToken_            = consumes<edm::ValueMap<bool> >(ps.getParameter<edm::InputTag>("phoMediumIdMap"));
   //  phoTightIdMapToken_             = consumes<edm::ValueMap<bool> >(ps.getParameter<edm::InputTag>("phoTightIdMap"));
   //  phoMVAValuesMapToken_           = consumes<edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoMVAValuesMap")); 
   //  phoChargedIsolationToken_       = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoChargedIsolation"));
   //  phoNeutralHadronIsolationToken_ = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoNeutralHadronIsolation"));
   //  phoPhotonIsolationToken_        = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoPhotonIsolation"));
   //  phoWorstChargedIsolationToken_  = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoWorstChargedIsolation"));

   /////  //trgEventLabel_             = consumes<trigger::TriggerEvent>         (ps.getParameter<InputTag>("triggerEvent"));
   /////  //theBeamSpot_(consumes<reco::BeamSpot>(theBeamSpotTag_)),
   ///////  //development_               = ps.getParameter<bool>("development");
   ///////  //addFilterInfoAOD_          = ps.getParameter<bool>("addFilterInfoAOD");
   ///////  addFilterInfoMINIAOD_      = ps.getParameter<bool>("addFilterInfoMINIAOD");  // MET Filter
   ///////  //doNoHFMET_                 = ps.getParameter<bool>("doNoHFMET");
   /////  //runOnParticleGun_          = ps.getParameter<bool>("runOnParticleGun");
   /////  //runOnSherpa_               = ps.getParameter<bool>("runOnSherpa");
   /////  //dumpPhotons_               = ps.getParameter<bool>("dumpPhotons");
   /////  //isAOD_                     = ps.getParameter<bool>("isAOD");
   /////  //runHFElectrons_            = ps.getParameter<bool>("runHFElectrons");
   ////////
   ////////  trgFilterDeltaPtCut_       = ps.getParameter<double>("trgFilterDeltaPtCut");
   ////////  trgFilterDeltaRCut_        = ps.getParameter<double>("trgFilterDeltaRCut");
   ///////  vtxBSLabel_                = consumes<reco::VertexCollection>        (ps.getParameter<InputTag>("VtxBSLabel"));
   ///////  generatorLabel_            = consumes<GenEventInfoProduct>           (ps.getParameter<InputTag>("generatorLabel"));
   ///////  lheEventLabel_             = consumes<LHEEventProduct>               (ps.getParameter<InputTag>("LHEEventLabel"));
   ///////  genParticlesCollection_    = consumes<vector<reco::GenParticle> >    (ps.getParameter<InputTag>("genParticleSrc"));
   ///////  //calibelectronCollection_   = consumes<View<pat::Electron> >          (ps.getParameter<InputTag>("calibelectronSrc"));
   ///////  //gsfTracks_                 = consumes<View<reco::GsfTrack>>          (ps.getParameter<InputTag>("gsfTrackSrc"));
   ///////
   ///////
   ///////  calibphotonCollection_     = consumes<View<pat::Photon> >            (ps.getParameter<InputTag>("calibphotonSrc"));
   ///////  ebReducedRecHitCollection_ = consumes<EcalRecHitCollection>          (ps.getParameter<InputTag>("ebReducedRecHitCollection"));
   ///////  eeReducedRecHitCollection_ = consumes<EcalRecHitCollection>          (ps.getParameter<InputTag>("eeReducedRecHitCollection"));
   ///////  esReducedRecHitCollection_ = consumes<EcalRecHitCollection>          (ps.getParameter<InputTag>("esReducedRecHitCollection")); 
   ///////  recophotonCollection_      = consumes<reco::PhotonCollection>        (ps.getParameter<InputTag>("recoPhotonSrc"));
   ///////  tracklabel_                = consumes<reco::TrackCollection>         (ps.getParameter<InputTag>("TrackLabel"));
   ///////  //gsfElectronlabel_          = consumes<reco::GsfElectronCollection>   (ps.getParameter<InputTag>("gsfElectronLabel"));
   ///////  tauCollection_             = consumes<vector<pat::Tau> >             (ps.getParameter<InputTag>("tauSrc"));
   ///////  pfAllParticles_            = consumes<reco::PFCandidateCollection>   (ps.getParameter<InputTag>("PFAllCandidates"));
   ///////  pckPFCandidateCollection_  = consumes<pat::PackedCandidateCollection>(ps.getParameter<InputTag>("packedPFCands"));
   ///////  pckPFCdsLabel_             = consumes<vector<pat::PackedCandidate>>  (ps.getParameter<InputTag>("packedPFCands"));
   ///////  recoCdsLabel_              = consumes<View<reco::Candidate>>         (ps.getParameter<InputTag>("packedPFCands"));
   ///////
   ///////  jetsAK8Label_              = consumes<View<pat::Jet> >               (ps.getParameter<InputTag>("ak8JetSrc"));
   ///////  //boostedDoubleSVLabel_      = consumes<reco::JetTagCollection>        (ps.getParameter<InputTag>("boostedDoubleSVLabel"));
   ///////  newparticles_              =                                          ps.getParameter< vector<int > >("newParticles");
   ///////  jecAK8PayloadNames_        =                                          ps.getParameter<std::vector<std::string> >("jecAK8PayloadNames"); 
   ///////
   ///////  //pfLooseId_                 = ps.getParameter<ParameterSet>("pfLooseId");
   ///////
   /////  ////cicPhotonId_ = new CiCPhotonID(ps);
   /////  //phoChargedIsolationToken_CITK_       = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoChargedIsolation_CITK"));
   /////  //phoPhotonIsolationToken_CITK_        = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoPhotonIsolation_CITK"));
   /////  //phoNeutralHadronIsolationToken_CITK_ = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoNeutralHadronIsolation_CITK"));
   /////  //
   /////  //phoChargedIsolationToken_PUPPI_       = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoChargedIsolation_PUPPI"));
   /////  //phoNeutralHadronIsolationToken_PUPPI_ = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoNeutralHadronIsolation_PUPPI"));
   /////  //phoPhotonIsolationToken_PUPPI_        = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoPhotonIsolation_PUPPI"));

  Service<TFileService> fs;
  tree_    = fs->make<TTree>("EventTree", "Event data (30 August 2017)");
  hEvents_ = fs->make<TH1F>("hEvents",    "total processed events",   1,  0,   2);

  // make branches for tree
  branchesGlobalEvent(tree_);
  ///branchesPhotons(tree_);
  branchesElectrons(tree_);
  branchesMuons(tree_);

  branchesJets(tree_);   
  branchesMET(tree_);
}

lldjNtuple::~lldjNtuple() {
}

void lldjNtuple::analyze(const edm::Event& e, const edm::EventSetup& es) {

 //# https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyResolution
 jetResolution_   = JME::JetResolution::get(es, "AK4PFchs_pt");
 jetResolutionSF_ = JME::JetResolutionScaleFactor::get(es, "AK4PFchs");

 fillGlobalEvent(e, es);
 ////fillPhotons(e, es);
 fillElectrons(e, es);

 // muons use vtx for isolation
 edm::Handle<reco::VertexCollection> vtxHandle;
 e.getByToken(vtxLabel_, vtxHandle);
 reco::Vertex vtx;
 // best-known primary vertex coordinates
 math::XYZPoint pv(0, 0, 0); 
 for (vector<reco::Vertex>::const_iterator v = vtxHandle->begin(); v != vtxHandle->end(); ++v) {
   // replace isFake() for miniAOD since it requires tracks while miniAOD vertices don't have tracks:
   // Vertex.h: bool isFake() const {return (chi2_==0 && ndof_==0 && tracks_.empty());}
   bool isFake = (v->chi2() == 0 && v->ndof() == 0); 

   if (!isFake) {
     pv.SetXYZ(v->x(), v->y(), v->z());
     vtx = *v; 
     break;
   }   
 }
 fillMuons(e, vtx); //muons use vtx for isolation

 fillJets(e,es);
 fillMET(e, es);

 hEvents_->Fill(1.);
 tree_->Fill();
}


// void lldjNtuple::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
// {
//   //The following says we do not know what parameters are allowed so do no validation
//   // Please change this to state exactly what you do use, even if it is no parameters
//   edm::ParameterSetDescription desc;
//   desc.setUnknown();
//   descriptions.addDefault(desc);
// }

DEFINE_FWK_MODULE(lldjNtuple);
