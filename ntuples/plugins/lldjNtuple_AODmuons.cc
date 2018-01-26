#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"

using namespace std;

// (local) variables associated with tree branches
Int_t            nAODMu_                             ; 
vector<float>    AOD_muPt_                            ; 
vector<float>    AOD_muEn_                            ; 
vector<float>    AOD_muEta_                           ; 
vector<float>    AOD_muPhi_                           ; 
vector<int>      AOD_muCharge_                        ; 
vector<int>      AOD_muType_                          ; 
vector<UShort_t> AOD_muIDbit_                         ; 
vector<bool>     AOD_muPassLooseID_                   ; 
vector<bool>     AOD_muPassHipID_                     ; 
vector<bool>     AOD_muPassTighID_                    ; 
// vector<bool>     AOD_muPassSoftID_                   ; 
// vector<bool>     AOD_muPassHighPtID_                 ; 
// vector<float>    AOD_muPVIndex_                      ; 
vector<int>     AOD_muNumberOfMissingInnerHits_       ; 
vector<int>     AOD_muNumberOfMissingMiddleHits_      ; 
vector<int>     AOD_muNumberOfMissingOuterHits_       ; 
//vector<int>     AOD_muNumberOfValidHits_              ; 
//vector<float>   AOD_muNormalizedChi2_                 ; 
vector<int>     AOD_muNumberOfMatchedStations_        ; 
vector<int>     AOD_muNumberOfValidPixelHits_         ; 
vector<int>     AOD_muTrackerLayersWithMeasurement_   ; 
vector<int>     AOD_muIsGlobalMuon_                   ; 
vector<int>     AOD_muIsPFMuon_                       ; 
//vector<int>     AOD_muIsTightMuonWRTVtx_              ; 
vector<float>   AOD_muPFdBetaIsolation_               ; 

void lldjNtuple::branchesAODMuons(TTree* tree) {
 tree->Branch("nAODMu",                            &nAODMu_                            ) ; 
 tree->Branch("AOD_muPt",                           &AOD_muPt_                           ) ; 
 tree->Branch("AOD_muEn",                           &AOD_muEn_                           ) ; 
 tree->Branch("AOD_muEta",                          &AOD_muEta_                          ) ; 
 tree->Branch("AOD_muPhi",                          &AOD_muPhi_                          ) ; 
 tree->Branch("AOD_muCharge",                       &AOD_muCharge_                       ) ; 
 tree->Branch("AOD_muType",                         &AOD_muType_                         ) ; 
 tree->Branch("AOD_muIDbit",                        &AOD_muIDbit_                        ) ; 
 tree->Branch("AOD_muPassLooseID",                  &AOD_muPassLooseID_                  ) ; 
 tree->Branch("AOD_muPassHipID",                    &AOD_muPassHipID_                    ) ; 
 tree->Branch("AOD_muPassTighID",                   &AOD_muPassTighID_                   ) ; 
 //tree->Branch("AOD_muPVIndex",                      &AOD_muPVIndex_                      ) ; 
 tree->Branch("AOD_muNumberOfMissingInnerHits",     &AOD_muNumberOfMissingInnerHits_     ) ; 
 tree->Branch("AOD_muNumberOfMissingMiddleHits",    &AOD_muNumberOfMissingMiddleHits_    ) ; 
 tree->Branch("AOD_muNumberOfMissingOuterHits",     &AOD_muNumberOfMissingOuterHits_     ) ; 
 //tree->Branch("AOD_muNumberOfValidHits",            &AOD_muNumberOfValidHits_            ) ; 
 //tree->Branch("AOD_muNormalizedChi2",               &AOD_muNormalizedChi2_               ) ; 
 tree->Branch("AOD_muNumberOfMatchedStations",      &AOD_muNumberOfMatchedStations_      ) ; 
 tree->Branch("AOD_muNumberOfValidPixelHits",       &AOD_muNumberOfValidPixelHits_       ) ; 
 tree->Branch("AOD_muTrackerLayersWithMeasurement", &AOD_muTrackerLayersWithMeasurement_ ) ; 
 tree->Branch("AOD_muIsGlobalMuon",                 &AOD_muIsGlobalMuon_                 ) ; 
 tree->Branch("AOD_muIsPFMuon",                     &AOD_muIsPFMuon_                     ) ; 
 //tree->Branch("AOD_muIsTightMuonWRTVtx",            &AOD_muIsTightMuonWRTVtx_            ) ; 
 tree->Branch("AOD_muPFdBetaIsolation",             &AOD_muPFdBetaIsolation_             ) ; 
}

//void lldjNtuple::fillAODMuons(const edm::Event& e, reco::Vertex vtx) {
void lldjNtuple::fillAODMuons(const edm::Event& e) {

 // cleanup from previous execution
 nAODMu_ = 0;
 AOD_muPt_                          .clear() ; 
 AOD_muEn_                          .clear() ; 
 AOD_muEta_                         .clear() ; 
 AOD_muPhi_                         .clear() ; 
 AOD_muCharge_                      .clear() ; 
 AOD_muType_                        .clear() ; 
 AOD_muIDbit_                       .clear() ; 
 AOD_muPassLooseID_                 .clear() ; 
 AOD_muPassHipID_                .clear() ; 
 AOD_muPassTighID_                  .clear() ; 
 //AOD_muPVIndex_                     .clear() ; 
 AOD_muNumberOfMissingInnerHits_    .clear() ; 
 AOD_muNumberOfMissingMiddleHits_   .clear() ; 
 AOD_muNumberOfMissingOuterHits_    .clear() ; 
 //AOD_muNumberOfValidHits_           .clear() ; 
 //AOD_muNormalizedChi2_              .clear() ; 
 AOD_muNumberOfMatchedStations_     .clear() ; 
 AOD_muNumberOfValidPixelHits_      .clear() ; 
 AOD_muTrackerLayersWithMeasurement_.clear() ; 
 AOD_muIsGlobalMuon_                .clear() ; 
 AOD_muIsPFMuon_                    .clear() ; 
 //AOD_muIsTightMuonWRTVtx_           .clear() ; 
 AOD_muPFdBetaIsolation_            .clear() ; 

 edm::Handle<edm::View<pat::Muon> > muonHandle;
 e.getByToken(muonCollection_, muonHandle);

 if (!muonHandle.isValid()) {
   edm::LogWarning("lldjNtuple") << "no pat::Muons in event";
  return;
 }

 for (edm::View<pat::Muon>::const_iterator iMu = muonHandle->begin(); iMu != muonHandle->end(); ++iMu) {

  nAODMu_++;
  Float_t pt = iMu->pt();
  Float_t eta = iMu->eta();

  if (pt < 20) continue;
  if (fabs(eta) > 2.1) continue;
  if (! (iMu->isPFMuon() || iMu->isGlobalMuon() || iMu->isTrackerMuon())) continue;

  const reco::Muon &recoMu = dynamic_cast<const reco::Muon &>(*iMu);

  if( !recoMu.innerTrack().isNull() ){
   AOD_muNumberOfMissingInnerHits_    .push_back( recoMu.innerTrack ()->hitPattern ().trackerLayersWithoutMeasurement (reco::HitPattern::MISSING_INNER_HITS) ) ; 
   AOD_muNumberOfMissingMiddleHits_   .push_back( recoMu.innerTrack ()->hitPattern ().trackerLayersWithoutMeasurement (reco::HitPattern::TRACK_HITS        ) ) ; 
   AOD_muNumberOfMissingOuterHits_    .push_back( recoMu.innerTrack ()->hitPattern ().trackerLayersWithoutMeasurement (reco::HitPattern::MISSING_OUTER_HITS) ) ; 
   AOD_muNumberOfValidPixelHits_      .push_back( recoMu.innerTrack ()->hitPattern ().numberOfValidPixelHits       ()   ) ; 
   AOD_muTrackerLayersWithMeasurement_.push_back( recoMu.innerTrack ()->hitPattern ().trackerLayersWithMeasurement ()   ) ; 
  }
  //muNumberOfValidHits_           .push_back( recoMu.innerTrack ()->hitPattern ().trackerLayersWithoutMeasurement (reco::HitPattern::)              ) ; 
  //muNormalizedChi2_              .push_back( recoMu.globalTrack().normalizedChi2 ()   ) ; 

  bool goodGlob = iMu->isGlobalMuon() && 
                  iMu->globalTrack()->normalizedChi2() < 3 && 
                  iMu->combinedQuality().chi2LocalPosition < 12 && 
                  iMu->combinedQuality().trkKink < 20; 
  bool isMedium = muon::isLooseMuon(recoMu) && 
                  iMu->innerTrack()->validFraction() > 0.49 && 
                  muon::segmentCompatibility(recoMu) > (goodGlob ? 0.303 : 0.451); 

  AOD_muPt_    .push_back(pt);
  AOD_muEn_    .push_back(iMu->energy());
  AOD_muEta_   .push_back(iMu->eta());
  AOD_muPhi_   .push_back(iMu->phi());
  AOD_muCharge_.push_back(iMu->charge());
  AOD_muType_  .push_back(iMu->type());
  // AOD_muD0_    .push_back(iMu->muonBestTrack()->dxy(pv));
  // AOD_muDz_    .push_back(iMu->muonBestTrack()->dz(pv));
  // AOD_muSIP_   .push_back(fabs(iMu->dB(pat::Muon::PV3D))/iMu->edB(pat::Muon::PV3D));

  UShort_t tmpmuIDbit = 0;

  if (iMu->isLooseMuon())     setbit(tmpmuIDbit, 0);
  if (iMu->isMediumMuon())    setbit(tmpmuIDbit, 1);
  //if (iMu->isTightMuon(vtx))  setbit(tmpmuIDbit, 2);
  //if (iMu->isSoftMuon(vtx))   setbit(tmpmuIDbit, 3);
  //if (iMu->isHighPtMuon(vtx)) setbit(tmpmuIDbit, 4);
  AOD_muIDbit_.push_back(tmpmuIDbit);

  AOD_muPassHipID_ .push_back( isMedium )   ;

  AOD_muIsGlobalMuon_                .push_back(iMu->  isGlobalMuon () ) ; 
  AOD_muIsPFMuon_                    .push_back(iMu->  isPFMuon     () ) ; 
  //AOD_muIsTightMuonWRTVtx_           .push_back(iMu->  isTightMuonWRTVtx ()  ) ; 

  Float_t muPFChIso      = iMu->pfIsolationR04().sumChargedHadronPt ;
  Float_t muPFPhoIso     = iMu->pfIsolationR04().sumPhotonEt        ;
  Float_t muPFNeuIso     = iMu->pfIsolationR04().sumNeutralHadronEt ;
  Float_t muPFPUIso      = iMu->pfIsolationR04().sumPUPt            ;
  Float_t pfdBetaIso     = ( muPFChIso + max(0.0,muPFNeuIso + muPFPhoIso - 0.5*muPFPUIso ) ) / pt ;

  AOD_muPFdBetaIsolation_     .push_back( pfdBetaIso     ) ; 

//  const pat::PackedCandidate &ppfMu = dynamic_cast<const pat::PackedCandidate &>(*iMu);
//
//  if (!ppfMu.vertexRef().isNull() && ppfMu.vertexRef().isAvailable()){
//   AOD_muPVIndex_ .push_back(ppfMu.vertexRef().index());
//  }

 }
}
