#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "LLDJstandalones/ntuples/interface/lldjNtuple.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "CLHEP/Random/RandomEngine.h"
#include "CLHEP/Random/RandGauss.h"

//#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
//#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
//#include "TrackingTools/TrajectoryState/interface/TrajectoryStateTransform.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "DataFormats/TrackReco/interface/TrackBase.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
//#include <CandidateBoostedDoubleSecondaryVertexComputer.h>
#include "RecoTracker/DebugTools/interface/GetTrackTrajInfo.h"
//////#include <GetTrackTrajInfo.h>

using namespace std;
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzVector;

// ak4 jets
Int_t          nJet_;
vector<float>  jetPt_;
vector<float>  jetEn_;
vector<float>  jetEta_;
vector<float>  jetPhi_;
vector<float>  jetRawPt_;
vector<float>  jetRawEn_;
vector<float>  jetMt_;
vector<float>  jetArea_;
vector<float>  jetLeadTrackPt_;
vector<float>  jetLeadTrackEta_;
vector<float>  jetLeadTrackPhi_;
vector<int>    jetLepTrackPID_;
vector<float>  jetLepTrackPt_;
vector<float>  jetLepTrackEta_;
vector<float>  jetLepTrackPhi_;
vector<float>  jetCHF_;
vector<float>  jetNHF_;
vector<float>  jetCEF_;
vector<float>  jetNEF_;
vector<int>    jetNCH_;
vector<int>    jetNNP_;
vector<float>  jetMUF_;
vector<float>  jetHFHAE_;
vector<float>  jetHFEME_;
vector<int>    jetNConstituents_;
vector<float>  jetVtxPt_;
vector<float>  jetVtxMass_;
vector<float>  jetVtxNtrks_;
vector<float>  jetVtx3DVal_;
vector<float>  jetVtx3DSig_;
vector<float>  jetCSV2BJetTags_; // recommended
vector<float>  jetJetProbabilityBJetTags_;
vector<float>  jetpfCombinedMVAV2BJetTags_;
vector<int>    jetPartonID_;
vector<int>    jetHadFlvr_;
vector<bool>   jetPFLooseId_;
vector<int>    jetID_; 
vector<float>  jetPUID_;
vector<int>    jetPUFullID_;
vector<float>  jetJECUnc_;
vector<float>  jetP4Smear_;
vector<float>  jetP4SmearUp_;
vector<float>  jetP4SmearDo_;
vector<UInt_t> jetFiredTrgs_;

// Displaced Jet Variables
vector<float>  jetAlphaD_;
vector<float>  jetAlphaMaxD_;
vector<float>  jetSumIP_;
vector<float>  jetSumIPSig_;
vector<float>  jetLog10IPSig_;
vector<float>  jetMedianLog10IPSig_;
vector<float>  jetTrackAngle_;
vector<float>  jetLogTrackAngle_;
vector<float>  jetMedianLogTrackAngle_;
vector<float>  jetTotalTrackAngle_;
vector<float>  jetAlphaMax_;
vector<float>  jetAlphaMax2_;
vector<float>  jetAlphaMaxP_;
vector<float>  jetAlphaMaxP2_;
vector<float>  jetDauVertex_x_;
vector<float>  jetDauVertex_y_;
vector<float>  jetDauVertex_z_;
vector<float>  jetDauVertex_r_;
vector<float>  alphaMax_jetDauVertex_r_;

// Alpha Maxs
vector<float>  jetAlphaMax_PV3onPV2_ ; 
vector<float>  jetAlphaMax_PV3onNeu_ ; 
vector<float>  jetAlphaMax_PV3onAll_ ; 
vector<float>  jetAlphaMax_PV2onNeu_ ; 
vector<float>  jetAlphaMax_PV2onAll_ ; 

vector<float>  jetAlpha2Max_PV3onPV2_ ; 
vector<float>  jetAlpha2Max_PV3onNeu_ ; 
vector<float>  jetAlpha2Max_PV3onAll_ ; 
vector<float>  jetAlpha2Max_PV2onNeu_ ; 
vector<float>  jetAlpha2Max_PV2onAll_ ; 

// Track Info
vector<vector<float>> jetTrackPt_;
vector<vector<float>> jetTrackEta_;
vector<vector<float>> jetTrackPhi_;
vector<vector<int>>   jetTrackPDGID_;
vector<vector<int>>   jetTrackMomPDGID_;

//gen-info for ak4
vector<float>  jetGenJetEn_;
vector<float>  jetGenJetPt_;
vector<float>  jetGenJetEta_;
vector<float>  jetGenJetPhi_;
vector<int>    jetGenPartonID_;
vector<float>  jetGenEn_;
vector<float>  jetGenPt_;
vector<float>  jetGenEta_;
vector<float>  jetGenPhi_;
vector<int>    jetGenPartonMomID_;

// //fat-jets (ak8)
// Int_t         nAK8Jet_;
// vector<float> AK8JetPt_;
// vector<float> AK8JetEn_;
// vector<float> AK8JetRawPt_;
// vector<float> AK8JetRawEn_;
// vector<float> AK8JetEta_;
// vector<float> AK8JetPhi_;
// vector<float> AK8JetMass_;
// vector<float> AK8Jet_tau1_;
// vector<float> AK8Jet_tau2_;
// vector<float> AK8Jet_tau3_;
// vector<float> AK8JetCHF_;
// vector<float> AK8JetNHF_;
// vector<float> AK8JetCEF_;
// vector<float> AK8JetNEF_;
// vector<int>   AK8JetNCH_;
// vector<int>   AK8JetNNP_;
// vector<float> AK8JetMUF_;
// vector<int>   AK8Jetnconstituents_;
// vector<bool>  AK8JetPFLooseId_;
// vector<bool>  AK8JetPFTightLepVetoId_;
// vector<float> AK8JetSoftDropMass_;
// vector<float> AK8JetSoftDropMassCorr_;
// vector<float> AK8JetPrunedMass_;
// vector<float> AK8JetPrunedMassCorr_;
// vector<float> AK8JetpfBoostedDSVBTag_;
// vector<float> AK8JetDSVnewV4_;
// vector<float> AK8JetCSV_;
// vector<float> AK8JetJECUnc_;
// vector<float> AK8JetL2L3corr_;
// 
// //gen-info for ak8
// vector<int>   AK8JetPartonID_;
// vector<int>   AK8JetHadFlvr_;
// vector<int>   AK8JetGenJetIndex_;
// vector<float> AK8JetGenJetEn_;
// vector<float> AK8JetGenJetPt_;
// vector<float> AK8JetGenJetEta_;
// vector<float> AK8JetGenJetPhi_;
// vector<int>   AK8JetGenPartonID_;
// vector<float> AK8JetGenEn_;
// vector<float> AK8JetGenPt_;
// vector<float> AK8JetGenEta_;
// vector<float> AK8JetGenPhi_;
// vector<int>   AK8JetGenPartonMomID_;
// vector<float> AK8JetP4Smear_;
// vector<float> AK8JetP4SmearUp_;
// vector<float> AK8JetP4SmearDo_;
// 
// //soft drop subjets
// vector<int>             nAK8SDSJ_ ;
// vector< vector<float> > AK8SDSJPt_ ;
// vector< vector<float> > AK8SDSJEta_ ;
// vector< vector<float> > AK8SDSJMass_ ;
// vector< vector<float> > AK8SDSJPhi_ ;
// vector< vector<float> > AK8SDSJE_ ;
// vector< vector<int > >  AK8SDSJCharge_ ;
// vector< vector<int > >  AK8SDSJFlavour_;
// vector< vector<float> > AK8SDSJCSV_ ;
// 
// //puppi
// vector<float> AK8puppiPt_;
// vector<float> AK8puppiMass_;
// vector<float> AK8puppiEta_;
// vector<float> AK8puppiPhi_;
// vector<float> AK8puppiTau1_;
// vector<float> AK8puppiTau2_;
// vector<float> AK8puppiTau3_;
// vector<float> AK8puppiSDL2L3corr_;
// vector<float> AK8puppiSDMass_;
// vector<float> AK8puppiSDMassL2L3Corr_;
// 
// //puppi + soft drop subjets
// vector<int>             nAK8puppiSDSJ_ ;
// vector< vector<float> > AK8puppiSDSJPt_ ;
// vector< vector<float> > AK8puppiSDSJEta_ ;
// vector< vector<float> > AK8puppiSDSJMass_ ;
// vector< vector<float> > AK8puppiSDSJPhi_ ;
// vector< vector<float> > AK8puppiSDSJE_ ;
// vector< vector<int > >  AK8puppiSDSJCharge_ ;
// vector< vector<int > >  AK8puppiSDSJFlavour_;
// vector< vector<float> > AK8puppiSDSJCSV_ ;

void lldjNtuple::branchesJets(TTree* tree) {
  
  tree->Branch("nJet",            &nJet_);
  tree->Branch("jetPt",           &jetPt_);
  tree->Branch("jetEn",           &jetEn_);
  tree->Branch("jetEta",          &jetEta_);
  tree->Branch("jetPhi",          &jetPhi_);
  tree->Branch("jetRawPt",        &jetRawPt_);
  tree->Branch("jetRawEn",        &jetRawEn_);
  tree->Branch("jetMt",           &jetMt_);
  tree->Branch("jetArea",         &jetArea_);
  tree->Branch("jetLeadTrackPt",  &jetLeadTrackPt_);
  tree->Branch("jetLeadTrackEta", &jetLeadTrackEta_);
  tree->Branch("jetLeadTrackPhi", &jetLeadTrackPhi_);
  tree->Branch("jetLepTrackPID",  &jetLepTrackPID_);
  tree->Branch("jetLepTrackPt",   &jetLepTrackPt_);
  tree->Branch("jetLepTrackEta",  &jetLepTrackEta_);
  tree->Branch("jetLepTrackPhi",  &jetLepTrackPhi_);
  tree->Branch("jetCSV2BJetTags", &jetCSV2BJetTags_);
  tree->Branch("jetJetProbabilityBJetTags", &jetJetProbabilityBJetTags_);
  tree->Branch("jetpfCombinedMVAV2BJetTags", &jetpfCombinedMVAV2BJetTags_);

  // Displaced Jet Variables
  tree->Branch("jetAlphaMax", &jetAlphaMax_);
  tree->Branch("jetAlphaMax2", &jetAlphaMax2_);
  tree->Branch("jetAlphaMaxP", &jetAlphaMaxP_);
  tree->Branch("jetAlphaMaxP2", &jetAlphaMaxP2_);
  tree->Branch("jetDauVertex_x", &jetDauVertex_x_);
  tree->Branch("jetDauVertex_y", &jetDauVertex_y_);
  tree->Branch("jetDauVertex_z", &jetDauVertex_z_);
  tree->Branch("jetDauVertex_r", &jetDauVertex_r_);
  tree->Branch("alphaMax_jetDauVertex_r", &alphaMax_jetDauVertex_r_);  

  // Alpha Maxs
  tree->Branch("jetAlphaMax_PV3onPV2", &jetAlphaMax_PV3onPV2_ ); 
  tree->Branch("jetAlphaMax_PV3onNeu", &jetAlphaMax_PV3onNeu_ ); 
  tree->Branch("jetAlphaMax_PV3onAll", &jetAlphaMax_PV3onAll_ ); 
  tree->Branch("jetAlphaMax_PV2onNeu", &jetAlphaMax_PV2onNeu_ ); 
  tree->Branch("jetAlphaMax_PV2onAll", &jetAlphaMax_PV2onAll_ ); 

  tree->Branch("jetAlpha2Max_PV3onPV2", &jetAlpha2Max_PV3onPV2_ ); 
  tree->Branch("jetAlpha2Max_PV3onNeu", &jetAlpha2Max_PV3onNeu_ ); 
  tree->Branch("jetAlpha2Max_PV3onAll", &jetAlpha2Max_PV3onAll_ ); 
  tree->Branch("jetAlpha2Max_PV2onNeu", &jetAlpha2Max_PV2onNeu_ ); 
  tree->Branch("jetAlpha2Max_PV2onAll", &jetAlpha2Max_PV2onAll_ ); 


  tree->Branch("jetAlphaD",               &jetAlphaD_);
  tree->Branch("jetAlphaMaxD",            &jetAlphaMaxD_);
  tree->Branch("jetLog10IPSig",           &jetLog10IPSig_);
  tree->Branch("jetMedianLog10IPSig",     &jetMedianLog10IPSig_);
  tree->Branch("jetSumIP",                &jetSumIP_);
  tree->Branch("jetSumIPSig",             &jetSumIPSig_);
  tree->Branch("jetTrackAngle",           &jetTrackAngle_);
  tree->Branch("jetLogTrackAngle",        &jetLogTrackAngle_);
  tree->Branch("jetMedianLogTrackAngle",  &jetMedianLogTrackAngle_); 
  tree->Branch("jetTotalTrackAngle",      &jetTotalTrackAngle_);

  tree->Branch("jetTrackPt",              &jetTrackPt_);
  tree->Branch("jetTrackEta",             &jetTrackEta_);
  tree->Branch("jetTrackPhi",             &jetTrackPhi_);
  tree->Branch("jetTrackPDGID",           &jetTrackPDGID_);
  tree->Branch("jetTrackMomPDGID",        &jetTrackMomPDGID_);
  tree->Branch("jetNConstituents",        &jetNConstituents_);

  //link the variable in c++ code to variable in branch
  if (doGenParticles_){
    tree->Branch("jetPartonID",       &jetPartonID_);
    tree->Branch("jetHadFlvr",        &jetHadFlvr_);
    tree->Branch("jetGenJetEn",       &jetGenJetEn_);
    tree->Branch("jetGenJetPt",       &jetGenJetPt_);
    tree->Branch("jetGenJetEta",      &jetGenJetEta_);
    tree->Branch("jetGenJetPhi",      &jetGenJetPhi_);
    tree->Branch("jetGenPartonID",    &jetGenPartonID_);
    tree->Branch("jetGenEn",          &jetGenEn_);
    tree->Branch("jetGenPt",          &jetGenPt_);
    tree->Branch("jetGenEta",         &jetGenEta_);
    tree->Branch("jetGenPhi",         &jetGenPhi_);
    tree->Branch("jetGenPartonMomID", &jetGenPartonMomID_);
    tree->Branch("jetP4Smear",        &jetP4Smear_);
    tree->Branch("jetP4SmearUp",      &jetP4SmearUp_);
    tree->Branch("jetP4SmearDo",      &jetP4SmearDo_);
  }  
  tree->Branch("jetPFLooseId", &jetPFLooseId_);
  tree->Branch("jetID",        &jetID_);
  tree->Branch("jetPUID",      &jetPUID_);
  tree->Branch("jetPUFullID",  &jetPUFullID_);
  tree->Branch("jetJECUnc",    &jetJECUnc_);
  tree->Branch("jetFiredTrgs", &jetFiredTrgs_);
  tree->Branch("jetCHF",       &jetCHF_);
  tree->Branch("jetNHF",       &jetNHF_);
  tree->Branch("jetCEF",       &jetCEF_);
  tree->Branch("jetNEF",       &jetNEF_);
  tree->Branch("jetNCH",       &jetNCH_);
  tree->Branch("jetNNP",       &jetNNP_);
  tree->Branch("jetMUF",       &jetMUF_);
  tree->Branch("jetVtxPt",     &jetVtxPt_);
  tree->Branch("jetVtxMass",   &jetVtxMass_);
  tree->Branch("jetVtxNtrks",  &jetVtxNtrks_);
  tree->Branch("jetVtx3DVal",  &jetVtx3DVal_);
  tree->Branch("jetVtx3DSig",  &jetVtx3DSig_);
  if (development_) {
    tree->Branch("jetHFHAE",         &jetHFHAE_);
    tree->Branch("jetHFEME",         &jetHFEME_);
  }

 //  // SubJet
 //  if (dumpSubJets_) {
 //    tree->Branch("nAK8Jet",                  &nAK8Jet_);
 //    tree->Branch("AK8JetPt",                 &AK8JetPt_);
 //    tree->Branch("AK8JetEn",                 &AK8JetEn_);
 //    tree->Branch("AK8JetRawPt",              &AK8JetRawPt_);
 //    tree->Branch("AK8JetRawEn",              &AK8JetRawEn_);
 //    tree->Branch("AK8JetEta",                &AK8JetEta_);
 //    tree->Branch("AK8JetPhi",                &AK8JetPhi_);
 //    tree->Branch("AK8JetMass",               &AK8JetMass_);
 //    tree->Branch("AK8Jet_tau1",              &AK8Jet_tau1_);
 //    tree->Branch("AK8Jet_tau2",              &AK8Jet_tau2_);
 //    tree->Branch("AK8Jet_tau3",              &AK8Jet_tau3_);
 //    tree->Branch("AK8JetCHF",                &AK8JetCHF_);
 //    tree->Branch("AK8JetNHF",                &AK8JetNHF_);
 //    tree->Branch("AK8JetCEF",                &AK8JetCEF_);
 //    tree->Branch("AK8JetNEF",                &AK8JetNEF_);
 //    tree->Branch("AK8JetNCH",                &AK8JetNCH_);
 //    tree->Branch("AK8JetNNP",                &AK8JetNNP_);
 //    tree->Branch("AK8JetMUF",                &AK8JetMUF_);
 //    tree->Branch("AK8Jetnconstituents",      &AK8Jetnconstituents_);
 //    tree->Branch("AK8JetPFLooseId",          &AK8JetPFLooseId_);
 //    tree->Branch("AK8JetPFTightLepVetoId",   &AK8JetPFTightLepVetoId_);
 //    tree->Branch("AK8JetSoftDropMass",    &AK8JetSoftDropMass_);
 //    tree->Branch("AK8JetSoftDropMassCorr",&AK8JetSoftDropMassCorr_);
 //    tree->Branch("AK8JetPrunedMass",      &AK8JetPrunedMass_);
 //    tree->Branch("AK8JetPrunedMassCorr",      &AK8JetPrunedMassCorr_);
 //    tree->Branch("AK8JetpfBoostedDSVBTag",   &AK8JetpfBoostedDSVBTag_);
 //    tree->Branch("AK8JetDSVnewV4",   &AK8JetDSVnewV4_);
 //    tree->Branch("AK8JetCSV",        &AK8JetCSV_);
 //    tree->Branch("AK8JetJECUnc",             &AK8JetJECUnc_);
 //    tree->Branch("AK8JetL2L3corr",             &AK8JetL2L3corr_);
 //    tree->Branch("AK8puppiPt", &AK8puppiPt_);
 //    tree->Branch("AK8puppiMass", &AK8puppiMass_);
 //    tree->Branch("AK8puppiEta", &AK8puppiEta_);
 //    tree->Branch("AK8puppiPhi", &AK8puppiPhi_);
 //    tree->Branch("AK8puppiTau1", &AK8puppiTau1_);
 //    tree->Branch("AK8puppiTau2", &AK8puppiTau2_);
 //    tree->Branch("AK8puppiTau3", &AK8puppiTau3_);
 //    tree->Branch("AK8puppiSDL2L3corr", &AK8puppiSDL2L3corr_);
 //    tree->Branch("AK8puppiSDMass", &AK8puppiSDMass_);
 //    tree->Branch("AK8puppiSDMassL2L3Corr", &AK8puppiSDMassL2L3Corr_);
 //
 //    if (doGenParticles_){
 //      tree->Branch("AK8JetPartonID", &AK8JetPartonID_);
 //      tree->Branch("AK8JetHadFlvr", &AK8JetHadFlvr_);
 //      tree->Branch("AK8JetGenJetIndex", &AK8JetGenJetIndex_);
 //      tree->Branch("AK8JetGenJetEn", &AK8JetGenJetEn_);
 //      tree->Branch("AK8JetGenJetPt", &AK8JetGenJetPt_);
 //      tree->Branch("AK8JetGenJetEta", &AK8JetGenJetEta_);
 //      tree->Branch("AK8JetGenJetPhi", &AK8JetGenJetPhi_);
 //      tree->Branch("AK8JetGenPartonID", &AK8JetGenPartonID_);
 //      tree->Branch("AK8JetGenEn", &AK8JetGenEn_);
 //      tree->Branch("AK8JetGenPt", &AK8JetGenPt_);
 //      tree->Branch("AK8JetGenEta", &AK8JetGenEta_);
 //      tree->Branch("AK8JetGenPhi", &AK8JetGenPhi_);
 //      tree->Branch("AK8JetGenPartonMomID", &AK8JetGenPartonMomID_);
 //      tree->Branch("AK8JetP4Smear",        &AK8JetP4Smear_);
 //      tree->Branch("AK8JetP4SmearUp",      &AK8JetP4SmearUp_);
 //      tree->Branch("AK8JetP4SmearDo",      &AK8JetP4SmearDo_);
 //    }
 //    tree->Branch("nAK8SDSJ",       &nAK8SDSJ_);
 //    tree->Branch("AK8SDSJPt",      &AK8SDSJPt_);
 //    tree->Branch("AK8SDSJEta",     &AK8SDSJEta_);
 //    tree->Branch("AK8SDSJPhi",     &AK8SDSJPhi_);
 //    tree->Branch("AK8SDSJMass",    &AK8SDSJMass_);
 //    tree->Branch("AK8SDSJE",       &AK8SDSJE_);
 //    tree->Branch("AK8SDSJCharge",  &AK8SDSJCharge_);
 //    tree->Branch("AK8SDSJFlavour", &AK8SDSJFlavour_);
 //    tree->Branch("AK8SDSJCSV",     &AK8SDSJCSV_);
 //    tree->Branch("nAK8puppiSDSJ",       &nAK8puppiSDSJ_);
 //    tree->Branch("AK8puppiSDSJPt",      &AK8puppiSDSJPt_);
 //    tree->Branch("AK8puppiSDSJEta",     &AK8puppiSDSJEta_);
 //    tree->Branch("AK8puppiSDSJPhi",     &AK8puppiSDSJPhi_);
 //    tree->Branch("AK8puppiSDSJMass",    &AK8puppiSDSJMass_);
 //    tree->Branch("AK8puppiSDSJE",       &AK8puppiSDSJE_);
 //    tree->Branch("AK8puppiSDSJCharge",  &AK8puppiSDSJCharge_);
 //    tree->Branch("AK8puppiSDSJFlavour", &AK8puppiSDSJFlavour_);
 //    tree->Branch("AK8puppiSDSJCSV",     &AK8puppiSDSJCSV_);
 //  }
}

//fills jets .clear() to empty vector of old data
void lldjNtuple::fillJets(const edm::Event& e, const edm::EventSetup& es) {

  bool dodebug = false;

  // cleanup from previous execution
  jetPt_                                  .clear();
  jetEn_                                  .clear();
  jetEta_                                 .clear();
  jetPhi_                                 .clear();
  jetRawPt_                               .clear();
  jetRawEn_                               .clear();
  jetMt_                                  .clear();
  jetArea_                                .clear();
  jetLeadTrackPt_                         .clear();
  jetLeadTrackEta_                        .clear();
  jetLeadTrackPhi_                        .clear();
  jetLepTrackPt_                          .clear();
  jetLepTrackPID_                         .clear();
  jetLepTrackEta_                         .clear();
  jetLepTrackPhi_                         .clear();
  jetCSV2BJetTags_                        .clear();
  jetJetProbabilityBJetTags_              .clear();
  jetpfCombinedMVAV2BJetTags_             .clear();
  jetPartonID_                            .clear();
  jetHadFlvr_                             .clear();
  jetPFLooseId_                           .clear();
  jetID_                                  .clear();
  jetPUID_                                .clear();
  jetPUFullID_                            .clear();
  jetJECUnc_                              .clear();
  jetP4Smear_                             .clear();
  jetP4SmearUp_                           .clear();
  jetP4SmearDo_                           .clear();
  jetFiredTrgs_                           .clear();
  jetCHF_                                 .clear();
  jetNHF_                                 .clear();
  jetCEF_                                 .clear();
  jetNEF_                                 .clear();
  jetNCH_                                 .clear();
  jetNNP_                                 .clear();
  jetMUF_                                 .clear();
  jetVtxPt_                               .clear();
  jetVtxMass_                             .clear();
  jetVtxNtrks_                            .clear();
  jetVtx3DVal_                            .clear();
  jetVtx3DSig_                            .clear();
  if (development_) {
    jetHFHAE_                               .clear();
    jetHFEME_                               .clear();
  }

  // Displaced Jet Variables
  jetAlphaMaxD_                           .clear();
  jetAlphaD_                              .clear();
  jetLog10IPSig_                          .clear();
  jetMedianLog10IPSig_                    .clear();
  jetSumIP_                               .clear();
  jetSumIPSig_                            .clear();
  jetTrackAngle_                          .clear();  
  jetLogTrackAngle_                       .clear();
  jetMedianLogTrackAngle_                 .clear();
  jetTotalTrackAngle_                     .clear(); 
  
  jetAlphaMax_       .clear();
  jetAlphaMax2_      .clear();
  jetAlphaMaxP_      .clear();
  jetAlphaMaxP2_     .clear();
  jetDauVertex_x_             .clear();
  jetDauVertex_y_             .clear();
  jetDauVertex_z_             .clear();
  jetDauVertex_r_         .clear();
  alphaMax_jetDauVertex_r_.clear();

  // Alpha Maxs
  jetAlphaMax_PV3onPV2_ .clear(); 
  jetAlphaMax_PV3onNeu_ .clear(); 
  jetAlphaMax_PV3onAll_ .clear(); 
  jetAlphaMax_PV2onNeu_ .clear(); 
  jetAlphaMax_PV2onAll_ .clear(); 

  jetAlpha2Max_PV3onPV2_ .clear(); 
  jetAlpha2Max_PV3onNeu_ .clear(); 
  jetAlpha2Max_PV3onAll_ .clear(); 
  jetAlpha2Max_PV2onNeu_ .clear(); 
  jetAlpha2Max_PV2onAll_ .clear(); 

  jetTrackPt_          .clear();
  jetTrackEta_         .clear();
  jetTrackPhi_         .clear();
  jetTrackPDGID_       .clear();
  jetTrackMomPDGID_    .clear();
  jetNConstituents_    .clear();

  jetGenJetEn_      .clear();
  jetGenJetPt_      .clear();
  jetGenJetEta_     .clear();
  jetGenJetPhi_     .clear();
  jetGenPartonID_   .clear();
  jetGenEn_         .clear();
  jetGenPt_         .clear();
  jetGenEta_        .clear();
  jetGenPhi_        .clear();
  jetGenPartonMomID_.clear();
  
//   // SubJet
//   AK8JetPt_                .clear();
//   AK8JetEn_                .clear();
//   AK8JetRawPt_             .clear();
//   AK8JetRawEn_             .clear();
//   AK8JetEta_               .clear();
//   AK8JetPhi_               .clear();
//   AK8JetMass_              .clear();
//   AK8Jet_tau1_             .clear();
//   AK8Jet_tau2_             .clear();
//   AK8Jet_tau3_             .clear();
//   AK8JetCHF_               .clear();
//   AK8JetNHF_               .clear();
//   AK8JetCEF_               .clear();
//   AK8JetNEF_               .clear();
//   AK8JetNCH_               .clear();
//   AK8JetNNP_               .clear();
//   AK8Jetnconstituents_     .clear();
//   AK8JetMUF_               .clear();
//   AK8JetPFLooseId_         .clear();
//   AK8JetPFTightLepVetoId_  .clear();
//   AK8JetSoftDropMass_      .clear();
//   AK8JetSoftDropMassCorr_  .clear();
//   AK8JetPrunedMass_        .clear();
//   AK8JetPrunedMassCorr_    .clear();
//   AK8JetpfBoostedDSVBTag_  .clear();
//   AK8JetDSVnewV4_          .clear();
//   AK8JetCSV_               .clear();
//   AK8JetJECUnc_            .clear();
//   AK8JetL2L3corr_          .clear();
// 
//   AK8puppiPt_              .clear();
//   AK8puppiMass_            .clear();
//   AK8puppiEta_             .clear();
//   AK8puppiPhi_             .clear();
//   AK8puppiTau1_            .clear();
//   AK8puppiTau2_            .clear();
//   AK8puppiTau3_            .clear();
//   AK8puppiSDL2L3corr_      .clear();
//   AK8puppiSDMass_          .clear();
//   AK8puppiSDMassL2L3Corr_  .clear();
// 
//   AK8JetPartonID_          .clear();
//   AK8JetHadFlvr_           .clear();
//   AK8JetGenJetIndex_       .clear();
//   AK8JetGenJetEn_          .clear();
//   AK8JetGenJetPt_          .clear();
//   AK8JetGenJetEta_         .clear();
//   AK8JetGenJetPhi_         .clear();
//   AK8JetGenPartonID_       .clear();
//   AK8JetGenEn_             .clear();
//   AK8JetGenPt_             .clear();
//   AK8JetGenEta_            .clear();
//   AK8JetGenPhi_            .clear();
//   AK8JetGenPartonMomID_    .clear();
//   AK8JetP4Smear_           .clear();
//   AK8JetP4SmearUp_         .clear();
//   AK8JetP4SmearDo_         .clear();
// 
//   nAK8SDSJ_                .clear();
//   AK8SDSJPt_               .clear();
//   AK8SDSJEta_              .clear();
//   AK8SDSJPhi_              .clear();
//   AK8SDSJMass_             .clear();
//   AK8SDSJCharge_           .clear();
//   AK8SDSJE_                .clear();
//   AK8SDSJFlavour_          .clear();
//   AK8SDSJCSV_              .clear();
// 
//   nAK8puppiSDSJ_           .clear();
//   AK8puppiSDSJPt_          .clear();
//   AK8puppiSDSJEta_         .clear();
//   AK8puppiSDSJPhi_         .clear();
//   AK8puppiSDSJMass_        .clear();
//   AK8puppiSDSJCharge_      .clear();
//   AK8puppiSDSJE_           .clear();
//   AK8puppiSDSJFlavour_     .clear();
//   AK8puppiSDSJCSV_         .clear();

  nJet_ = 0;
  
  edm::Handle<reco::TrackCollection> trackHandle;
  e.getByToken(tracklabel_,trackHandle);

  edm::Handle<edm::View<pat::Jet> > jetHandle;
  e.getByToken(jetsAK4Label_, jetHandle);

  if (!jetHandle.isValid()) {
    edm::LogWarning("lldjNtuple") << "no pat::Jets (AK4) in event";
    return;
  }

  //access beamspot
  edm::Handle<reco::BeamSpot> bsHandle;
  e.getByLabel("offlineBeamSpot", bsHandle);
  reco::BeamSpot beamSpot;
  //test if found beamspot
  if ( bsHandle.isValid() )
  {
   beamSpot = *bsHandle;
  } else
  {
    edm::LogWarning("lldjNtuple")
      << "No beam spot available from EventSetup \n";
  }
  //make beampsot point
  math::XYZPoint bsPoint(beamSpot.x0(),beamSpot.y0(), beamSpot.z0());

  edm::Handle<vector<reco::GenParticle> > genParticlesHandle;
  if(doGenParticles_)e.getByToken(genParticlesCollection_, genParticlesHandle);
  
  edm::Handle<double> rhoHandle;
  e.getByToken(rhoLabel_, rhoHandle);
  float rho = *(rhoHandle.product());
  
  edm::Handle<reco::VertexCollection> vtxHandle;
  e.getByToken(vtxLabel_, vtxHandle);
  if (!vtxHandle.isValid()) edm::LogWarning("lldjNtuple") << "Primary vertices info not unavailable";

  // Accessing the JEC uncertainties 
  //ak4  
  edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
  es.get<JetCorrectionsRecord>().get("AK4PFchs",JetCorParColl); 
  JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"];
  JetCorrectionUncertainty *jecUnc=0;
  jecUnc = new JetCorrectionUncertainty(JetCorPar);
  // //ak8
  // edm::ESHandle<JetCorrectorParametersCollection> AK8JetCorParColl;
  // es.get<JetCorrectionsRecord>().get("AK8PFchs",AK8JetCorParColl);
  // JetCorrectorParameters const & AK8JetCorPar = (*AK8JetCorParColl)["Uncertainty"];
  // JetCorrectionUncertainty *AK8jecUnc=0;
  // AK8jecUnc = new JetCorrectionUncertainty(AK8JetCorPar);
  
  //start jets Lvdp
  int nrjet = 0;
  int IP0Sum = 0;
  int TA0Sum = 0;

  if(dodebug){ printf("Starting loop over jets\n"); }
  unsigned int tmp_jetnr = 0; 
  //******Jets Loop****
  for (edm::View<pat::Jet>::const_iterator iJet = jetHandle->begin(); iJet != jetHandle->end(); ++iJet) {
    tmp_jetnr++;
    if(dodebug){ printf(" Jet Nr: %u \n",tmp_jetnr); }

    //get jet axis for track angle
    TVector3 JetAxis(iJet->px(),iJet->py(),iJet->pz());
 
    //declare new vars    
    float dxy;
    float dxyerr;
    float SumIP = 0.0;
    float SumIPSig = 0.0;
    float MedianLog10IPSig = 0.0;
    float TotalTrackAngle = 0.0;
    float MedianLogTrackAngle = 0.0;
   
    //float emEnergyFrac       = iJet->chargedEmEnergyFraction() + iJet->neutralEmEnergyFraction(); //cout << "EM: "<<emEnergyFrac<<endl; 
    //float hadronicEnergyFrac = iJet->chargedHadronEnergyFraction() + iJet->neutralHadronEnergyFraction(); //cout << "had: "<<hadronicEnergyFrac<<endl;
    
    nrjet++;
    // if (iJet->pt() <= 20 || fabs(iJet->eta()) >= 2.4 || iJet->chargedEmEnergyFraction()>=.9||iJet->neutralEmEnergyFraction()>=.9 || iJet->neutralHadronEnergyFraction()>=.9||iJet->chargedHadronEnergyFraction()>=.9) continue;
    if(dodebug){printf(" pt: %f\n",iJet->pt()); }
    jetPt_.push_back(    iJet->pt());
    //cout << endl<< iJet->pt()<<" *****jet constituents: "<<iJet->getJetConstituents().size() <<endl;
    //cout<<endl<<"JetPT: "<<iJet->pt() <<"Event "<<e.id().event()<<endl;
    jetEn_.push_back(    iJet->energy());
    jetEta_.push_back(   iJet->eta());
    jetPhi_.push_back(   iJet->phi());
    jetRawPt_.push_back( (*iJet).correctedJet("Uncorrected").pt());
    jetRawEn_.push_back( (*iJet).correctedJet("Uncorrected").energy());
    jetMt_.push_back(    iJet->mt());
    jetArea_.push_back(  iJet->jetArea());
    jetCEF_.push_back(   iJet->chargedEmEnergyFraction());
    jetNEF_.push_back(   iJet->neutralEmEnergyFraction());
    jetCHF_.push_back(   iJet->chargedHadronEnergyFraction());
    jetNHF_.push_back(   iJet->neutralHadronEnergyFraction());
    jetNCH_.push_back(   iJet->chargedMultiplicity());
    jetNNP_.push_back(   iJet->neutralMultiplicity());
    jetMUF_.push_back(   iJet->muonEnergyFraction());
    //jetNConstituents_.push_back(iJet->numberOfDaughters());
    jetNConstituents_.push_back(iJet->getJetConstituents().size());
    if (development_) {
      jetHFHAE_.push_back( iJet->HFHadronEnergy());
      jetHFEME_.push_back( iJet->HFEMEnergy());
    }

    if (fabs(iJet->eta()) < 5.2) {
      jecUnc->setJetEta(iJet->eta());
      jecUnc->setJetPt(iJet->pt()); // here you must use the CORRECTED jet pt
      jetJECUnc_.push_back(jecUnc->getUncertainty(true));
    } else {
      jetJECUnc_.push_back(-1.);
    }

    jetFiredTrgs_.push_back(matchJetTriggerFilters(iJet->pt(), iJet->eta(), iJet->phi()));    

    //Searching for leading track and lepton
    float leadTrkPt  = -99;
    float leadTrkEta = -99;
    float leadTrkPhi = -99;
    int   lepTrkPID  = -99;
    float lepTrkPt   = -99;
    float lepTrkEta  = -99;
    float lepTrkPhi  = -99;

    vector<float> sumtracksfPV2(vtxHandle->size(),  0.);
    vector<float> sum2tracksfPV2(vtxHandle->size(), 0.);
    vector<float> sumtracksfPV3(vtxHandle->size(),  0.);
    vector<float> sum2tracksfPV3(vtxHandle->size(), 0.);
    vector<float> sumtracksMinDzVtx(vtxHandle->size() ,  0);
    vector<float> sum2tracksMinDzVtx(vtxHandle->size() , 0);
    float sumneutraltracks   = 0 ;
    float sum2neutraltracks  = 0 ;
    float sumalltracks       = 0 ;
    float sum2alltracks      = 0 ;

    //IP stuff
    bool IPtest = false;
    float dxySig = -1.;

    float daughterPt = -1;
    float daughterEta = -99;
    float daughterPhi = -99;
    float promptTotal   = 0 ;
    float promptTotal2  = 0 ;
    int   daughterPDGID = 0;

    if(dodebug){ printf("  Looping over Tracks\n"); }
    unsigned int tmp_tracknr = 0; 

    vector<float> tmpTrackPt;
    vector<float> tmpTrackEta;
    vector<float> tmpTrackPhi;
    vector<int>   tmpTrackPDGID;
    vector<int>   tmpTrackMomPDGID;

    //***looping over tracks***
    for (unsigned id = 0; id < iJet->getJetConstituents().size(); id++) {

      // daughter of iJet is reco::Candidate
      const edm::Ptr<reco::Candidate> daughter = iJet->getJetConstituents().at(id);

      //cast daughter as (pat::PackedCandidate)daughter2 to access member functions
      const pat::PackedCandidate &daughter2 = dynamic_cast<const pat::PackedCandidate &>(*iJet->getJetConstituents().at(id));

      const reco::VertexRef vref = daughter2.vertexRef();

      if (daughter.isNonnull() && daughter.isAvailable()) 
      {
        tmp_tracknr++;
        if(dodebug){ printf("   Track Nr: %u \n",tmp_tracknr); }

        // set common variables
        daughterPt = daughter->pt(); 
        daughterEta = daughter->eta();
        daughterPhi = daughter->phi();
        daughterPDGID = daughter2.pdgId();
        if(dodebug){ printf("   pt %f, eta %f, phi %f PDGID %i\n", daughterPt,daughterEta,daughterPhi,daughterPDGID); }
        if(dodebug){
         cout<<"*************** Daughter Loop Details ************"<<endl;
                 cout <<"VertexRefIndex: "<<vref.index()<<" Pt: "<<daughter->pt()
                      <<" Charge: "<<daughter->charge()<<" daughterPDGID: "<<daughter2.pdgId()
                      <<" fromPv(): "<<daughter2.fromPV()
                      << " pvAssociationQuality(): " <<daughter2.pvAssociationQuality()
                      /*<<"motherRef"<<iJet->genParton()->motherRef()->pdgId()*/<<endl;
         cout<<"*************** Daughter Loop Details end*********"<<endl;
        }

        tmpTrackPt    .push_back( daughterPt    );
        tmpTrackEta   .push_back( daughterEta   );
        tmpTrackPhi   .push_back( daughterPhi   );
        tmpTrackPDGID .push_back( daughterPDGID );

        //jetTrackPDGID_.push_back(daughter2.pdgId());

        // r = transverse vertex distance
        math::XYZPoint jetDauVertex = daughter2.vertex();
        float jetDauVertex_r = sqrt(pow(jetDauVertex.x(),2)+pow(jetDauVertex.y(),2));
	jetDauVertex_x_.push_back(jetDauVertex.x());
	jetDauVertex_y_.push_back(jetDauVertex.y());
	jetDauVertex_z_.push_back(jetDauVertex.z());
	jetDauVertex_r_.push_back(jetDauVertex_r);

        // set lead soft lepton (track) variables
	if (abs(daughter->pdgId()) == 11 || abs(daughter->pdgId()) == 13) {
	  if (daughterPt > lepTrkPt) {
	    lepTrkPID = daughter->pdgId();
	    lepTrkPt  = daughterPt;
	    lepTrkEta = daughterEta;
	    lepTrkPhi = daughterPhi;
	  }
	}  

        // set lead (neutral) track variables
	if (daughter->charge() != 0 && daughterPt > leadTrkPt) {
	  leadTrkPt  = daughterPt;
	  leadTrkEta = daughterEta;
	  leadTrkPhi = daughterPhi;
	}

        // Displaced Jet Variables
        // restrict to neutral tracks 
        // should we include cut : daughter2.fromPV() > 1
        if (daughter->charge() != 0)
        {

          // Impact Parameter
          dxy = fabs(daughter2.dxy());//bsPoint));//*****why this at beamspot and dxyerr at PV?
          dxyerr = daughter2.dxyError();
          if(dxyerr>0){ dxySig = dxy/dxyerr; IPtest = true; }
	  if (IPtest ==true){
	    SumIP += dxy;
	    SumIPSig +=dxySig;
	    //cout <<"************dxy: " <<dxy<< " dxyerr: "<<dxyerr<< " dxySig: "<<dxySig<<" log10dxySig: "<< log10(dxySig) <<endl; 
	    jetLog10IPSig_.push_back( log10(dxySig) );
	  }     

	  // Alpha----------------------
          int vtxIDminTrackDz=-1;
          float minPvDz = 10000.0; 

          // loop over vertices (already looping over tracks and jets)
          if(dodebug){ printf("   Looping over vertices\n"); }
	  for(unsigned int k = 0; k < vtxHandle->size(); ++k){

            // variation with fromPV > 1
	    if(daughter2.fromPV(k) >1){
              if(dodebug){ printf("      (2+) associated with vtx %u\n",k); }

	      sumtracksfPV2[k]  += daughterPt;
	      sum2tracksfPV2[k] += daughterPt*daughterPt;
	    }

            // variation with fromPV > 2
	    if(daughter2.fromPV(k) >2){
              if(dodebug){ printf("      -(3+) associated with vtx %u\n",k); }
              // what is this beta about? 
	      promptTotal   += daughterPt;
	      promptTotal2  += daughterPt*daughterPt;

	      sumtracksfPV3[k]  += daughterPt;
	      sum2tracksfPV3[k] += daughterPt*daughterPt;
	    }

            // vtxIDminTrackDz is the ID of the vtx with smallest dZ to this specific jet daughter
            // will need two loops
            //  first find the vtx id for min dz with track (must go through all vtxs)
            //  then (still looping over tracks) add track pt to sumtracksMinDZ[ vtx id w/ min dz to track ]
            std::cout<<"  vtx trk DZ = "<<daughter2.dz(vtxHandle->at(k).position())<<std::endl;
            if(fabs(daughter2.dz(vtxHandle->at(k).position())) < minPvDz) {
             minPvDz = fabs(daughter2.dz(vtxHandle->at(k).position()));
             vtxIDminTrackDz = k;
            }
	  }  // end looping over vertices
          printf(" end of vertices, minPVDz was %f at id %i \n", minPvDz,vtxIDminTrackDz); 

          // vtxIDminTrackDz is ID of the best vtx for this track, add track pt to alpha numerator for this vtx
          sumtracksMinDzVtx[vtxIDminTrackDz]  += daughterPt;
          sum2tracksMinDzVtx[vtxIDminTrackDz] += daughterPt*daughterPt;

          sumneutraltracks += daughterPt;
          sum2neutraltracks += daughterPt*daughterPt;

	  //track angle stuff  ----- FIXME
	  //get point of closest approach
	  math::XYZPoint CA = daughter2.vertex();
	  TVector3 Tang(CA.x(),CA.y(),CA.z());
	  //jetTrackPhi_.push_back(daughter2.phiAtVtx());
	  jetTrackAngle_.push_back(Tang.Angle(JetAxis)); //acos(Tang*JetAxis/(MagTang*MagJetAxis)));
	  jetLogTrackAngle_.push_back( log(fabs(Tang.Angle(JetAxis))) );//not sure if log or log10
	  TotalTrackAngle += Tang.Angle(JetAxis);
	  // reco::TransientTrack tt(trackHandle->at(id),magneticField_); 

        printf(" end of track, minPVDz was at id %i \n", vtxIDminTrackDz); 
        } // if (daughter->charge!=0)

        sumalltracks += daughterPt;
        sum2alltracks += daughterPt*daughterPt;

      } // if daughter exists, nonnull
    } // loop over tracks

    // if you want to save this to the ntuple, it should be vector< vector< float > > 
    //  don't forget that we have multiple jets
    jetAlphaD_.clear();

    //save alpha = sum over tracks associated with vtx / all tracks
    if(sumalltracks>0)
    {
     for(unsigned z =0; z <sumtracksMinDzVtx.size(); z++)
     {
      std::cout<<"sum["<<z<<"] = "<<sumtracksMinDzVtx[z]<<" sumalltracks = "<<sumalltracks<<" div = "<<sumtracksMinDzVtx[z]/sumalltracks<<std::endl;
      jetAlphaD_.push_back(sumtracksMinDzVtx[z]/sumalltracks);
     }
    }
    else { jetAlphaD_.push_back(-99.9); }

    //set alphaMax variable out of range of true alpha max
    float alphaM = -99.9;
    //find the maximum 
    for (unsigned y = 0; y<jetAlphaD_.size(); y++)
    {
     if(jetAlphaD_[y]>alphaM){ alphaM = jetAlphaD_[y];}
    }	
    std::cout<<"  max = "<<alphaM<<std::endl;
    jetAlphaMaxD_.push_back(alphaM);



    if(alphaM<0){
     for(unsigned z =0; z <sumtracksMinDzVtx.size(); z++)
     {
      std::cout<<sumtracksMinDzVtx[z]/sumalltracks<<" "<<sumtracksMinDzVtx[z]<<" "<<sumalltracks<<std::endl;
     }
    }

    //      vector<float> alphaNum_ = vector<float>(vtxHandle->size(),0.0);
    //alphaNum_.clear();
    // push back vector of track variables for this specific jet
    jetTrackPt_    .push_back( tmpTrackPt    );
    jetTrackEta_   .push_back( tmpTrackEta   );
    jetTrackPhi_   .push_back( tmpTrackPhi   );
    jetTrackPDGID_ .push_back( tmpTrackPDGID );

    //if(dodebug){ 
    // printf("   Done Loopong over tracks\n"); 
    // //for(unsigned int k = 0; k < sumtracksfPV2->size(); ++k){
    // for(unsigned int k = 0; k < sumtracksfPV2.size(); ++k){
    //    printf("    sum trackpt vtx %u  pt %f / %f \n", k,  sumtracksfPV2[k], sumalltracks );
    //  }
    // }

    float alphaMax = -1;
    float alphaMax2 = -1;
    float apMax =-1;
    float apMax2 = -1;
    float beta = 1.0 - promptTotal/sumalltracks;
    float beta2 = 1.0 - promptTotal2/sum2alltracks;
    for(int i = 0; i < (int)sumtracksfPV2.size(); i++){
      //if(sumtracksfPV2[i] = 0)continue;
      if(sumtracksfPV2[i] > alphaMax) alphaMax = sumtracksfPV2[i];
      if(sum2tracksfPV2[i] > alphaMax2) alphaMax2 = sum2tracksfPV2[i];
      float ap = sumtracksfPV2[i] / (sumtracksfPV2[i] + beta);
      float ap2 = sum2tracksfPV2[i] / (sum2tracksfPV2[i] + beta2);
      if(ap > apMax) apMax = ap;
      if(ap2 > apMax2) apMax2 = ap2;
    }

    float jetAlphaMax_PV3onPV2 = -1;
    float jetAlphaMax_PV3onNeu = -1;
    float jetAlphaMax_PV3onAll = -1;
    float jetAlphaMax_PV2onNeu = -1;
    float jetAlphaMax_PV2onAll = -1;

    float jetAlpha_PV3onPV2 = -1;
    float jetAlpha_PV3onNeu = -1;
    float jetAlpha_PV3onAll = -1;
    float jetAlpha_PV2onNeu = -1;
    float jetAlpha_PV2onAll = -1;

    float jetAlpha2Max_PV3onPV2 = -1;
    float jetAlpha2Max_PV3onNeu = -1;
    float jetAlpha2Max_PV3onAll = -1;
    float jetAlpha2Max_PV2onNeu = -1;
    float jetAlpha2Max_PV2onAll = -1;

    float jetAlpha2_PV3onPV2 = -1;
    float jetAlpha2_PV3onNeu = -1;
    float jetAlpha2_PV3onAll = -1;
    float jetAlpha2_PV2onNeu = -1;
    float jetAlpha2_PV2onAll = -1;

    for(unsigned int q = 0; q < sumtracksfPV3.size(); q++){
      jetAlpha_PV3onPV2  = sumtracksfPV3[q]  / sumtracksfPV2[q] ;
      jetAlpha2_PV3onPV2 = sum2tracksfPV3[q] / sum2tracksfPV2[q];
      if(jetAlpha_PV3onPV2  > jetAlphaMax_PV3onPV2 ){ jetAlphaMax_PV3onPV2  = jetAlpha_PV3onPV2; }
      if(jetAlpha2_PV3onPV2 > jetAlpha2Max_PV3onPV2){ jetAlpha2Max_PV3onPV2 = jetAlpha2_PV3onPV2; }
    }

    for(unsigned int q = 0; q < sumtracksfPV3.size(); q++){
      jetAlpha_PV3onNeu  = sumtracksfPV3[q]  / sumneutraltracks ;
      jetAlpha2_PV3onNeu = sum2tracksfPV3[q] / sum2neutraltracks;
      if(jetAlpha_PV3onNeu  > jetAlphaMax_PV3onNeu ){ jetAlphaMax_PV3onNeu  = jetAlpha_PV3onNeu; }
      if(jetAlpha2_PV3onNeu > jetAlpha2Max_PV3onNeu){ jetAlpha2Max_PV3onNeu = jetAlpha2_PV3onNeu; }
    }

    for(unsigned int q = 0; q < sumtracksfPV3.size(); q++){
      jetAlpha_PV3onAll  = sumtracksfPV3[q]  / sumalltracks ;
      jetAlpha2_PV3onAll = sum2tracksfPV3[q] / sum2alltracks;
      if(jetAlpha_PV3onAll  > jetAlphaMax_PV3onAll ){ jetAlphaMax_PV3onAll  = jetAlpha_PV3onAll; }
      if(jetAlpha2_PV3onAll > jetAlpha2Max_PV3onAll){ jetAlpha2Max_PV3onAll = jetAlpha2_PV3onAll; }
    }

    for(unsigned int q = 0; q < sumtracksfPV2.size(); q++){
      jetAlpha_PV2onNeu  = sumtracksfPV2[q]  / sumneutraltracks ;
      jetAlpha2_PV2onNeu = sum2tracksfPV2[q] / sum2neutraltracks;
      if(jetAlpha_PV2onNeu  > jetAlphaMax_PV2onNeu ){ jetAlphaMax_PV2onNeu  = jetAlpha_PV2onNeu; }
      if(jetAlpha2_PV2onNeu > jetAlpha2Max_PV2onNeu){ jetAlpha2Max_PV2onNeu = jetAlpha2_PV2onNeu; }
    }

    for(unsigned int q = 0; q < sumtracksfPV2.size(); q++){
      jetAlpha_PV2onAll  = sumtracksfPV2[q]  / sumalltracks ;
      jetAlpha2_PV2onAll = sum2tracksfPV2[q] / sum2alltracks;
      if(jetAlpha_PV2onAll  > jetAlphaMax_PV2onAll ){ jetAlphaMax_PV2onAll  = jetAlpha_PV2onAll; }
      if(jetAlpha2_PV2onAll > jetAlpha2Max_PV2onAll){ jetAlpha2Max_PV2onAll = jetAlpha2_PV2onAll; }
    }


//        sumalltracks += daughterPt;
//        sum2alltracks += daughterPt*daughterPt;
//        sumneutraltracks += daughterPt;
//        sum2neutraltracks += daughterPt*daughterPt;
//	sumtracksfPV2[k]  += daughterPt;
//	sum2tracksfPV2[k] += daughterPt*daughterPt;
//	sumtracksfPV3[k]  += daughterPt;
//	sum2tracksfPV3[k] += daughterPt*daughterPt;


    jetAlphaMax_PV3onPV2_ .push_back(jetAlphaMax_PV3onPV2); 
    jetAlphaMax_PV3onNeu_ .push_back(jetAlphaMax_PV3onNeu); 
    jetAlphaMax_PV3onAll_ .push_back(jetAlphaMax_PV3onAll); 
    jetAlphaMax_PV2onNeu_ .push_back(jetAlphaMax_PV2onNeu); 
    jetAlphaMax_PV2onAll_ .push_back(jetAlphaMax_PV2onAll); 

    jetAlpha2Max_PV3onPV2_ .push_back(jetAlpha2Max_PV3onPV2);
    jetAlpha2Max_PV3onNeu_ .push_back(jetAlpha2Max_PV3onNeu);
    jetAlpha2Max_PV3onAll_ .push_back(jetAlpha2Max_PV3onAll);
    jetAlpha2Max_PV2onNeu_ .push_back(jetAlpha2Max_PV2onNeu);
    jetAlpha2Max_PV2onAll_ .push_back(jetAlpha2Max_PV2onAll);


    jetAlphaMax_.push_back(alphaMax / sumalltracks);
    jetAlphaMax2_.push_back(alphaMax2 / sum2alltracks);
    jetAlphaMaxP_.push_back(apMax);
    jetAlphaMaxP2_.push_back(apMax2);
	 
    jetLeadTrackPt_ .push_back(leadTrkPt);
    jetLeadTrackEta_.push_back(leadTrkEta);
    jetLeadTrackPhi_.push_back(leadTrkPhi);
    jetLepTrackPID_ .push_back(lepTrkPID);
    jetLepTrackPt_  .push_back(lepTrkPt);
    jetLepTrackEta_ .push_back(lepTrkEta);
    jetLepTrackPhi_ .push_back(lepTrkPhi);    
    jetVtxPt_       .push_back(sqrt(pow(iJet->userFloat("vtxPx"),2)+pow(iJet->userFloat("vtxPy"),2)));
    jetVtxMass_     .push_back(iJet->userFloat("vtxMass"));
    jetVtxNtrks_    .push_back(iJet->userFloat("vtxNtracks"));
    jetVtx3DVal_    .push_back(iJet->userFloat("vtx3DVal"));
    jetVtx3DSig_    .push_back(iJet->userFloat("vtx3DSig"));
    
    //b-tagging
    jetCSV2BJetTags_           .push_back(iJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
    jetJetProbabilityBJetTags_ .push_back(iJet->bDiscriminator("pfJetProbabilityBJetTags"));
    jetpfCombinedMVAV2BJetTags_.push_back(iJet->bDiscriminator("pfCombinedMVAV2BJetTags"));
  
    //parton id
    jetPartonID_.push_back(iJet->partonFlavour());
    jetHadFlvr_.push_back(iJet->hadronFlavour());

    //jet PF Loose ID
    float NHF      = iJet->neutralHadronEnergyFraction();
    float NEMF     = iJet->neutralEmEnergyFraction();
    float NumConst = iJet->chargedMultiplicity()+iJet->neutralMultiplicity();
    float CHF      = iJet->chargedHadronEnergyFraction();
    float CHM      = iJet->chargedMultiplicity();
    float CEMF     = iJet->chargedEmEnergyFraction();
    float NNP      = iJet->neutralMultiplicity();

    bool looseJetID = false;    
    bool tightJetID = false;
    if (fabs(iJet->eta()) <= 2.7) {
      looseJetID = (NHF<0.99 && NEMF<0.99 && NumConst>1) && ((fabs(iJet->eta())<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || fabs(iJet->eta())>2.4);
      tightJetID = (NHF<0.90 && NEMF<0.90 && NumConst>1) && ((fabs(iJet->eta())<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || fabs(iJet->eta())>2.4);
    } else if (fabs(iJet->eta()) <= 3.0) {
      looseJetID = (NEMF>0.01 && NHF<0.98 && NNP>2);
      tightJetID = (NEMF>0.01 && NHF<0.98 && NNP>2);
    } else {
      looseJetID = (NEMF<0.90 && NNP>10); 
      tightJetID = (NEMF<0.90 && NNP>10);
    }
    jetPFLooseId_.push_back(looseJetID);
    Int_t jetIDdecision = 0;
    if (looseJetID) jetIDdecision += pow(2, 1);
    if (tightJetID) jetIDdecision += pow(2, 2);
    jetID_.push_back(jetIDdecision);    
    //int i;
    // PUJet ID from slimmedJets
    jetPUID_.push_back(iJet->userFloat("pileupJetId:fullDiscriminant"));
    jetPUFullID_.push_back(iJet->userInt("pileupJetId:fullId"));

    // Displaced Jet Variable : median jet log IP significance
    /*
    cout<<endl;
    cout<<endl;
    cout<<"***********"<<" Event: "<<e.id().event()<<" Jet: "<<nrjet<<", "<<nJet_<<"**************" <<endl;
    cout<<"Un-Sorted("<<jetLog10IPSig_.size()<<"): ";
    for (i=0; i<jetLog10IPSig_.size(); i++)
      {
       cout<<jetLog10IPSig_[i]<<", ";
      }
    cout<<endl;
    */

    // must sort IPsig to be able to find median
    sort(jetLog10IPSig_.begin(), jetLog10IPSig_.end());
    sort(jetLogTrackAngle_.begin(), jetLogTrackAngle_.end());

    //bool skim = false
    //for(i=0; i<jetLog10IPSig_.begin();i++){
    /*
    cout<<endl;
    cout<<"Last element(b): "<<jetLog10IPSig_[jetLog10IPSig_.size()-1]<<endl;
    if(jetLog10IPSig_.size()>1 && jetLog10IPSig_[jetLog10IPSig_.size()-1] >=9999999.0) jetLog10IPSig_.pop_back();
    cout<<endl;
    cout<<"Last element(a): "<<jetLog10IPSig_[jetLog10IPSig_.size()-1]<<endl;

    cout<<"Sorted("<<jetLog10IPSig_.size()<<"): ";
    for (i=0; i<jetLog10IPSig_.size(); i++)
    {
     cout<<jetLog10IPSig_[i]<<", "; 
    }
    */    

    //Now find median
    //Note .at() threw error
    if(jetLog10IPSig_.size() == 0){
      IP0Sum+=1;
      jetMedianLog10IPSig_.push_back(-99.9); 
     // if(fabs(MedianLog10IPSig)>99.0){cout<<"IF "<<MedianLog10IPSig<<" "<<jetLog10IPSig_.size()<<endl;}
    }
    else if(jetLog10IPSig_.size()%2 ==0){
      //cout<<"elseif"<<" "<<jetLog10IPSig_.size()<<endl;
      //cout<<"jetLog10IPSig_.size()/2) -1"<< jetLog10IPSig_.size()/2) -1 <<endl;
      //cout<<"
      MedianLog10IPSig = 0.5*( jetLog10IPSig_.at( (jetLog10IPSig_.size()/2) -1 ) 
                             + jetLog10IPSig_.at(  jetLog10IPSig_.size()/2     ));
      jetMedianLog10IPSig_.push_back(MedianLog10IPSig);
      //if(fabs(MedianLog10IPSig)>99.0){cout<<"elseif"<<MedianLog10IPSig<<" "<<jetLog10IPSig_.size()<<endl;}
    }
    else{
     // cout<<"ELSE"<<" "<<jetLog10IPSig_.size()<<endl;
      MedianLog10IPSig =       jetLog10IPSig_.at( (jetLog10IPSig_.size()-1)/2 );
      jetMedianLog10IPSig_.push_back(MedianLog10IPSig);
     // if(fabs(MedianLog10IPSig)>99.0){cout<<"ELSE"<<MedianLog10IPSig<<" "<<jetLog10IPSig_.size()<<endl;}
    }
    

    // Track Angle still broken FIXME
    //cout <<" TotalTA: " << TotalTrackAngle<<endl;
    //TrackAngle_Median
    if(jetLogTrackAngle_.size() == 0){
    TA0Sum+=1;
    //cout<<" IF_TA "<<MedianLogTrackAngle<<" "<<jetLogTrackAngle_.size()<<endl;
    }
    else if(jetLogTrackAngle_.size()%2 ==0)
    {
    MedianLogTrackAngle = 0.5*( jetLogTrackAngle_[(jetLogTrackAngle_.size()/2) -1]
                              + jetLogTrackAngle_[ jetLogTrackAngle_.size()/2    ]);
    //if(MedianLogTrackAngle>10000.0 || MedianLogTrackAngle<-10000.0)cout <<"**************"<<MedianLogTrackAngle<<" "<<jetLogTrackAngle_.size()<<endl;
    jetMedianLogTrackAngle_.push_back(MedianLogTrackAngle);
    //cout<<" elseif_TA: "<<MedianLogTrackAngle<<" "<<jetLogTrackAngle_.size()<<endl;
    }
    else
    {
    MedianLogTrackAngle =       jetLogTrackAngle_[(jetLogTrackAngle_.size()-1)/2];
    //if(MedianLogTrackAngle>10000.0 || MedianLogTrackAngle<-10000.0)cout<<"**************" <<MedianLogTrackAngle<<" "<<jetLogTrackAngle_.size()<<endl;
    jetMedianLogTrackAngle_.push_back(MedianLogTrackAngle);
    //cout<<" ELSE_TA: "<<MedianLogTrackAngle<<" "<<jetLogTrackAngle_.size()<<endl;
    }    

    //jetMedianLog10IPSig_.push_back(MedianLog10IPSig);
    jetSumIP_.push_back(SumIP);
    jetSumIPSig_.push_back(SumIPSig);

    if(jetLogTrackAngle_.size()>0/*TAIsGood.size() >0*/)jetTotalTrackAngle_.push_back(TotalTrackAngle);


    // gen jet and parton
    if (doGenParticles_ && genParticlesHandle.isValid()) {
      int jetGenPartonID    = -99;
      int jetGenPartonMomID = -99;
      float jetGenEn        = -999.;
      float jetGenPt        = -999.;
      float jetGenEta       = -999.;
      float jetGenPhi       = -999.;      
      if ((*iJet).genParton()) {
	jetGenPartonID = (*iJet).genParton()->pdgId();
	jetGenEn = (*iJet).genParton()->energy(); 	jetGenPt = (*iJet).genParton()->pt();
	jetGenEta = (*iJet).genParton()->eta();
	jetGenPhi = (*iJet).genParton()->phi();
	if ((*iJet).genParton()->mother()) {
	  jetGenPartonMomID = (*iJet).genParton()->mother()->pdgId();
	}
      }
      
      jetGenPartonID_.push_back(jetGenPartonID);
      jetGenPartonMomID_.push_back(jetGenPartonMomID);
      jetGenEn_ .push_back(jetGenEn);
      jetGenPt_ .push_back(jetGenPt);
      jetGenEta_ .push_back(jetGenEta);
      jetGenPhi_ .push_back(jetGenPhi);
      
      float jetGenJetEn  = -999.;
      float jetGenJetPt  = -999.;
      float jetGenJetEta = -999.;
      float jetGenJetPhi = -999.;
      if ((*iJet).genJet()) {
	jetGenJetEn = (*iJet).genJet()->energy();
	jetGenJetPt = (*iJet).genJet()->pt();
	jetGenJetEta = (*iJet).genJet()->eta();
	jetGenJetPhi = (*iJet).genJet()->phi();
      }
      jetGenJetEn_.push_back(jetGenJetEn);
      jetGenJetPt_.push_back(jetGenJetPt);
      jetGenJetEta_.push_back(jetGenJetEta);
      jetGenJetPhi_.push_back(jetGenJetPhi);
      
      // access jet resolution       
      JME::JetParameters parameters;
      parameters.setJetPt(iJet->pt()).setJetEta(iJet->eta()).setRho(rho);
      float jetResolution = jetResolution_.getResolution(parameters);

      edm::Service<edm::RandomNumberGenerator> rng;
      if (!rng.isAvailable()) edm::LogError("JET : random number generator is missing !");
      CLHEP::HepRandomEngine & engine = rng->getEngine( e.streamID() );
      float rnd = CLHEP::RandGauss::shoot(&engine, 0., jetResolution);

      float jetResolutionSF   = jetResolutionSF_.getScaleFactor(parameters);
      float jetResolutionSFUp = jetResolutionSF_.getScaleFactor(parameters, Variation::UP);
      float jetResolutionSFDo = jetResolutionSF_.getScaleFactor(parameters, Variation::DOWN);

      float jetP4Smear   = -1.;
      float jetP4SmearUp = -1.;
      float jetP4SmearDo = -1.;
      if (jetGenJetPt > 0 && deltaR(iJet->eta(), iJet->phi(), jetGenJetEta, jetGenJetPhi) < 0.2 && fabs(iJet->pt()-jetGenJetPt) < 3*jetResolution*iJet->pt()) {
	jetP4Smear   = 1. + (jetResolutionSF   - 1.)*(iJet->pt() - jetGenJetPt)/iJet->pt();
	jetP4SmearUp = 1. + (jetResolutionSFUp - 1.)*(iJet->pt() - jetGenJetPt)/iJet->pt();
	jetP4SmearDo = 1. + (jetResolutionSFDo - 1.)*(iJet->pt() - jetGenJetPt)/iJet->pt();
      } else {
	jetP4Smear   = 1. + rnd*sqrt(max(pow(jetResolutionSF,   2)-1, 0.));
        jetP4SmearUp = 1. + rnd*sqrt(max(pow(jetResolutionSFUp, 2)-1, 0.));
	jetP4SmearDo = 1. + rnd*sqrt(max(pow(jetResolutionSFDo, 2)-1, 0.));
      }
      jetP4Smear_  .push_back(jetP4Smear);
      jetP4SmearUp_.push_back(jetP4SmearUp);
      jetP4SmearDo_.push_back(jetP4SmearDo);
    }
    
    nJet_++;
  }///******End Jets Loop******

  if(dodebug){
   printf("    After jet loop, check all track vars\n");
   for(unsigned int k = 0; k < jetTrackPt_.size(); ++k){
    for(unsigned int l = 0; l < jetTrackPt_.at(k).size(); ++l){
     printf("    pt %f, eta %f, phi %f PDGID %i\n",
     jetTrackPt_.at(k).at(l), jetTrackEta_.at(k).at(l),
     jetTrackPhi_.at(k).at(l), jetTrackPDGID_.at(k).at(l) );
    }
   }
  }

  //cout <<"********Empties: IP: "<<IP0Sum<<"     TA: "<<TA0Sum<<endl;    

  // if (dumpSubJets_) {
  //   edm::Handle<edm::View<pat::Jet> > jetsAK8;
  //   e.getByToken(jetsAK8Label_, jetsAK8);
  //   
  //   if (!jetsAK8.isValid()) {
  //     edm::LogWarning("lldjNtuple") << "no pat::Jets (AK8AK8) in event";
  //     return;
  //   }
  //   
  //   //Double B-tagger 
////     edm::Handle<reco::JetTagCollection> pfBoostedDoubleSecondaryVertex; 
////     e.getByToken(boostedDoubleSVLabel_, pfBoostedDoubleSecondaryVertex); 
  //   
  //   //https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetWtagging#Recipes_to_apply_JEC_on_the_prun
  //   
  //   std::vector<JetCorrectorParameters> vPar;
  //   for ( std::vector<std::string>::const_iterator payloadBegin = jecAK8PayloadNames_.begin(), payloadEnd = jecAK8PayloadNames_.end(), ipayload = payloadBegin; ipayload != payloadEnd; ++ipayload ) {
  //     JetCorrectorParameters pars(*ipayload);
  //   vPar.push_back(pars);
  //   }
  //   
  //   // Make the FactorizedJetCorrector
  //   jecAK8_ = boost::shared_ptr<FactorizedJetCorrector> ( new FactorizedJetCorrector(vPar) );
  //   jecAK8pSD_ = boost::shared_ptr<FactorizedJetCorrector> ( new FactorizedJetCorrector(vPar) );
  //      
  //   nAK8Jet_ = 0;
  //   //jet substructure
  //   int nsubjets = 0;
  //   std::vector<float> vecSDSJcsv ;
  //   std::vector<float> vecSDSJpt ;
  //   std::vector<float> vecSDSJeta ;
  //   std::vector<float> vecSDSJmass ;
  //   std::vector<float> vecSDSJphi ;
  //   std::vector<float> vecSDSJe ;
  //   std::vector<int > vecSDSJcharge ;
  //   std::vector<int > vecSDSJflavour;

  //   int nPuppiSJs = 0;
  //   std::vector<float> vecPuppiSDSJcsv ;
  //   std::vector<float> vecPuppiSDSJpt ;
  //   std::vector<float> vecPuppiSDSJeta ;
  //   std::vector<float> vecPuppiSDSJmass ;
  //   std::vector<float> vecPuppiSDSJphi ;
  //   std::vector<float> vecPuppiSDSJe ;
  //   std::vector<int > vecPuppiSDSJcharge ;
  //   std::vector<int > vecPuppiSDSJflavour;

  //   edm::View<pat::Jet>::const_iterator beginAK8 = jetsAK8->begin();
  //   edm::View<pat::Jet>::const_iterator endAK8 = jetsAK8->end();
  //   edm::View<pat::Jet>::const_iterator ijetAK8 = beginAK8;
  //   int ijetRef = -1;
  //   // Loop over the "hard" jets
  //   for(ijetAK8 = beginAK8; ijetAK8 != endAK8; ++ijetAK8 ) {
  //     ijetRef++;
  //     if( ijetAK8->pt() < 30.0 ) continue;
  //     nAK8Jet_++;
  //     AK8JetPt_.push_back( ijetAK8->pt() );
  //     AK8JetEn_.push_back( ijetAK8->energy() );
  //     AK8JetMass_.push_back( ijetAK8->mass() );
  //     AK8JetRawPt_.push_back( (*ijetAK8).correctedJet("Uncorrected").pt() );
  //     AK8JetRawEn_.push_back( (*ijetAK8).correctedJet("Uncorrected").energy() );
  //     AK8JetEta_.push_back( ijetAK8->eta() );
  //     AK8JetPhi_.push_back( ijetAK8->phi() );
  //     AK8Jet_tau1_.push_back( ijetAK8->userFloat("NjettinessAK8:tau1") );
  //     AK8Jet_tau2_.push_back( ijetAK8->userFloat("NjettinessAK8:tau2") );
  //     AK8Jet_tau3_.push_back( ijetAK8->userFloat("NjettinessAK8:tau3") );
  //     AK8JetCHF_.push_back( ijetAK8->chargedHadronEnergyFraction()); // 0.0
  //     AK8JetNHF_.push_back( ijetAK8->neutralHadronEnergyFraction()); //0.99
  //     AK8JetCEF_.push_back( ijetAK8->chargedEmEnergyFraction()); //0.99
  //     AK8JetNEF_.push_back( ijetAK8->neutralEmEnergyFraction()); //0.99
  //     AK8JetNCH_.push_back( ijetAK8->chargedMultiplicity()); //0
  //     AK8JetNNP_.push_back( ijetAK8->neutralMultiplicity()); //0
  //     AK8Jetnconstituents_.push_back( ijetAK8->chargedMultiplicity() + ijetAK8->neutralMultiplicity()); //1  
  //     AK8JetMUF_.push_back(ijetAK8->muonEnergyFraction());
  //     //https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID#Recommendations_for_13_TeV_data
  //     //LooseID
  //     bool AK8jetID = true;
  //     if (fabs(ijetAK8->eta()) <= 2.7) {
  //       if (!(ijetAK8->neutralHadronEnergyFraction() < 0.99))                       AK8jetID = false;
  //       if (!(ijetAK8->neutralEmEnergyFraction() < 0.99))                           AK8jetID = false;
  //       if (!((ijetAK8->chargedMultiplicity() + ijetAK8->neutralMultiplicity()) > 1))  AK8jetID = false;
  //       if (fabs(ijetAK8->eta()) <= 2.4) {
  //         if (!(ijetAK8->chargedHadronEnergyFraction() > 0))  AK8jetID = false;
  //         if (!(ijetAK8->chargedMultiplicity() > 0))          AK8jetID = false;
  //         if (!(ijetAK8->chargedEmEnergyFraction() < 0.99))   AK8jetID = false;
  //       }
  //     }
  //     else if (fabs(ijetAK8->eta()) > 2.7 && fabs(ijetAK8->eta()) <= 3.0) {
  //       if (!(ijetAK8->neutralEmEnergyFraction() > 0.01))     AK8jetID = false;
  //       if (!(ijetAK8->neutralHadronEnergyFraction() < 0.98)) AK8jetID = false;
  //       if (!(ijetAK8->neutralMultiplicity() > 2))            AK8jetID = false;
  //     }
  //     else if (fabs(ijetAK8->eta()) > 3.0) {
  //       if (!(ijetAK8->neutralEmEnergyFraction() < 0.90))  AK8jetID = false;
  //       if (!(ijetAK8->neutralMultiplicity() > 10))        AK8jetID = false;
  //     }
  //     AK8JetPFLooseId_.push_back(AK8jetID);
  //     //TightIDMuon Fraction
  //     bool AK8jetIDTightLepVeto = true;
  //     if (fabs(ijetAK8->eta()) <= 3.0) {
  //       if (!(ijetAK8->neutralHadronEnergyFraction() < 0.90))                       AK8jetIDTightLepVeto = false;
  //       if (!(ijetAK8->neutralEmEnergyFraction() < 0.90))                           AK8jetIDTightLepVeto = false;
  //       if (!((ijetAK8->chargedMultiplicity() + ijetAK8->neutralMultiplicity()) > 1))  AK8jetIDTightLepVeto = false;
  //       if (!(ijetAK8->muonEnergyFraction()<0.8))                                   AK8jetIDTightLepVeto = false;
  //       if (fabs(ijetAK8->eta()) <= 2.4) {
  //         if (!(ijetAK8->chargedHadronEnergyFraction() > 0))  AK8jetIDTightLepVeto = false;
  //         if (!(ijetAK8->chargedMultiplicity() > 0))          AK8jetIDTightLepVeto = false;
  //         if (!(ijetAK8->chargedEmEnergyFraction() < 0.90))   AK8jetIDTightLepVeto = false;
  //       }
  //     }
  //     AK8JetPFTightLepVetoId_.push_back(AK8jetIDTightLepVeto);

  //     AK8JetpfBoostedDSVBTag_.push_back(ijetAK8->bDiscriminator("pfBoostedDoubleSecondaryVertexAK8BJetTags"));
  //     AK8JetDSVnewV4_.push_back(ijetAK8->bDiscriminator("newV4pfBoostedDoubleSecondaryVertexAK8BJetTags"));
  //     AK8JetCSV_.push_back(ijetAK8->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
  //     //AK8JetpfBoostedDSVBTag_.push_back(     (*pfBoostedDoubleSecondaryVertex).value(ijetRef));

  //     const LorentzVector uncorrJet = (*ijetAK8).correctedP4(0);
  //     jecAK8_->setJetEta(uncorrJet.eta());
  //     jecAK8_->setJetPt ( uncorrJet.pt() );
  //     jecAK8_->setJetE  ( uncorrJet.energy() );
  //     jecAK8_->setJetA  ( (*ijetAK8).jetArea() );
  //     jecAK8_->setRho   ( rho );
  //     jecAK8_->setNPV   ( vtxHandle->size() );

  //     float corr = jecAK8_->getCorrection();
  //     AK8JetL2L3corr_.push_back(corr);
  //           
  //     AK8JetSoftDropMass_.push_back(ijetAK8->userFloat("ak8PFJetsCHSSoftDropMass"));
  //     AK8JetPrunedMass_.push_back(ijetAK8->userFloat("ak8PFJetsCHSPrunedMass"));
  //     AK8JetSoftDropMassCorr_.push_back(corr*(ijetAK8->userFloat("ak8PFJetsCHSSoftDropMass")));
  //     AK8JetPrunedMassCorr_.push_back(corr*(ijetAK8->userFloat("ak8PFJetsCHSPrunedMass")));

  //     //JEC uncertainty
  //     if (fabs(ijetAK8->eta()) < 5.2) {
  //       AK8jecUnc->setJetEta(ijetAK8->eta());
  //       AK8jecUnc->setJetPt(ijetAK8->pt()); // here you must use the CORRECTED jet pt
  //       AK8JetJECUnc_.push_back(AK8jecUnc->getUncertainty(true));
  //     } else {
  //       AK8JetJECUnc_.push_back(-1.);
  //     }

  //     //save gen-info for ak8 jets
  //     //parton id                                                                                                                                                           
  //     AK8JetPartonID_.push_back(ijetAK8->partonFlavour());
  //     AK8JetHadFlvr_.push_back(ijetAK8->hadronFlavour());
  //     int AK8JetGenPartonID = -99;
  //     int AK8JetGenPartonMomID = -99;
  //     float AK8JetGenEn = -999.;
  //     float AK8JetGenPt = -999.;
  //     float AK8JetGenEta = -999.;
  //     float AK8JetGenPhi = -999.;
  //     if (doGenParticles_ && genParticlesHandle.isValid() ) {
  //       if ((*ijetAK8).genParton()) {
  //         AK8JetGenPartonID = (*ijetAK8).genParton()->pdgId();
  //         AK8JetGenEn = (*ijetAK8).genParton()->energy();
  //         AK8JetGenPt = (*ijetAK8).genParton()->pt();
  //         AK8JetGenEta = (*ijetAK8).genParton()->eta();
  //         AK8JetGenPhi = (*ijetAK8).genParton()->phi();
  //         if ((*ijetAK8).genParton()->mother()) {
  //           AK8JetGenPartonMomID = (*ijetAK8).genParton()->mother()->pdgId();
  //         }
  //       }
  //     }
  //     AK8JetGenPartonID_.push_back(AK8JetGenPartonID);
  //     AK8JetGenPartonMomID_.push_back(AK8JetGenPartonMomID);
  //     AK8JetGenEn_ .push_back(AK8JetGenEn);
  //     AK8JetGenPt_ .push_back(AK8JetGenPt);
  //     AK8JetGenEta_ .push_back(AK8JetGenEta);
  //     AK8JetGenPhi_ .push_back(AK8JetGenPhi);
  //     int AK8JetGenJetIndex = -1;
  //     float AK8JetGenJetEn = -999.;
  //     float AK8JetGenJetPt = -999.;
  //     float AK8JetGenJetEta = -999.;
  //     float AK8JetGenJetPhi = -999.;
  //     if (doGenParticles_ && genParticlesHandle.isValid() ) {
  //       if ((*ijetAK8).genJet()) {
  //         AK8JetGenJetIndex = 1;
  //         AK8JetGenJetEn = (*ijetAK8).genJet()->energy();
  //         AK8JetGenJetPt = (*ijetAK8).genJet()->pt();
  //         AK8JetGenJetEta = (*ijetAK8).genJet()->eta();
  //         AK8JetGenJetPhi = (*ijetAK8).genJet()->phi();
  //       }
  //       // access AK8jet resolution       
  //       JME::JetParameters AK8parameters;
  //       AK8parameters.setJetPt(ijetAK8->pt()).setJetEta(ijetAK8->eta()).setRho(rho);
  //       float AK8jetResolution = AK8jetResolution_.getResolution(AK8parameters);

  //       edm::Service<edm::RandomNumberGenerator> rng;
  //       if (!rng.isAvailable()) edm::LogError("JET : random number generator is missing !");
  //       CLHEP::HepRandomEngine & engine = rng->getEngine( e.streamID() );
  //       float rnd = CLHEP::RandGauss::shoot(&engine, 0., AK8jetResolution);

  //       float AK8jetResolutionSF   = AK8jetResolutionSF_.getScaleFactor(AK8parameters);
  //       float AK8jetResolutionSFUp = AK8jetResolutionSF_.getScaleFactor(AK8parameters, Variation::UP);
  //       float AK8jetResolutionSFDo = AK8jetResolutionSF_.getScaleFactor(AK8parameters, Variation::DOWN);

  //       float AK8JetP4Smear   = -1.;
  //       float AK8JetP4SmearUp = -1.;
  //       float AK8JetP4SmearDo = -1.;
  //       if (AK8JetGenJetPt > 0 && deltaR(ijetAK8->eta(), ijetAK8->phi(), AK8JetGenJetEta, AK8JetGenJetPhi) < 0.4 && fabs(ijetAK8->pt()-AK8JetGenJetPt) < 3*AK8jetResolution*ijetAK8->pt()) {
  //         AK8JetP4Smear   = 1. + (AK8jetResolutionSF   - 1.)*(ijetAK8->pt() - AK8JetGenJetPt)/ijetAK8->pt();
  //         AK8JetP4SmearUp = 1. + (AK8jetResolutionSFUp - 1.)*(ijetAK8->pt() - AK8JetGenJetPt)/ijetAK8->pt();
  //         AK8JetP4SmearDo = 1. + (AK8jetResolutionSFDo - 1.)*(ijetAK8->pt() - AK8JetGenJetPt)/ijetAK8->pt();
  //       } else {
  //         AK8JetP4Smear   = 1. + rnd*sqrt(max(pow(AK8jetResolutionSF,   2)-1, 0.));
  //         AK8JetP4SmearUp = 1. + rnd*sqrt(max(pow(AK8jetResolutionSFUp, 2)-1, 0.));
  //         AK8JetP4SmearDo = 1. + rnd*sqrt(max(pow(AK8jetResolutionSFDo, 2)-1, 0.));
  //       }
  //       AK8JetP4Smear_  .push_back(AK8JetP4Smear);
  //       AK8JetP4SmearUp_.push_back(AK8JetP4SmearUp);
  //       AK8JetP4SmearDo_.push_back(AK8JetP4SmearDo);
  //     }
  //     AK8JetGenJetIndex_.push_back(AK8JetGenJetIndex);
  //     AK8JetGenJetEn_.push_back(AK8JetGenJetEn);
  //     AK8JetGenJetPt_.push_back(AK8JetGenJetPt);
  //     AK8JetGenJetEta_.push_back(AK8JetGenJetEta);
  //     AK8JetGenJetPhi_.push_back(AK8JetGenJetPhi);
  //     
  //     //save Softdrop subjet info Lvdp
  //     vecSDSJcsv.clear();
  //     vecSDSJpt.clear();
  //     vecSDSJeta.clear();
  //     vecSDSJmass.clear();
  //     vecSDSJphi.clear();
  //     vecSDSJe.clear();
  //     vecSDSJcharge.clear();
  //     vecSDSJflavour.clear();
  //     nsubjets = 0;
  //     if(dumpSoftDrop_) {
  //       auto const & sdSubjets = ijetAK8->subjets("SoftDrop");
  //       for ( auto const & SDSJ : sdSubjets ) {
  //         nsubjets++;
  //         vecSDSJpt.push_back(SDSJ->pt());
  //         vecSDSJeta.push_back(SDSJ->eta());
  //         vecSDSJmass.push_back(SDSJ->mass());
  //         vecSDSJphi.push_back(SDSJ->phi());
  //         vecSDSJe.push_back(SDSJ->energy());
  //         vecSDSJflavour.push_back(abs(SDSJ->partonFlavour()));
  //         vecSDSJcharge.push_back(SDSJ->charge());
  //         vecSDSJcsv.push_back(SDSJ->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags") );
  //       }
  //     }
  //     nAK8SDSJ_.push_back(nsubjets);
  //     AK8SDSJPt_.push_back(vecSDSJpt);
  //     AK8SDSJEta_.push_back(vecSDSJeta);
  //     AK8SDSJPhi_.push_back(vecSDSJphi);
  //     AK8SDSJMass_.push_back(vecSDSJmass);
  //     AK8SDSJE_.push_back(vecSDSJe);
  //     AK8SDSJCharge_.push_back(vecSDSJcharge);
  //     AK8SDSJFlavour_.push_back(vecSDSJflavour);
  //     AK8SDSJCSV_.push_back(vecSDSJcsv);


//// for some r&d on puppi + softdrop

  //     AK8puppiPt_.push_back( ijetAK8->userFloat("ak8PFJetsPuppiValueMap:pt"));
  //     AK8puppiMass_.push_back( ijetAK8->userFloat("ak8PFJetsPuppiValueMap:mass"));
  //     AK8puppiEta_.push_back( ijetAK8->userFloat("ak8PFJetsPuppiValueMap:eta"));
  //     AK8puppiPhi_.push_back( ijetAK8->userFloat("ak8PFJetsPuppiValueMap:phi"));
  //     AK8puppiTau1_.push_back( ijetAK8->userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau1"));
  //     AK8puppiTau2_.push_back( ijetAK8->userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau2"));
  //     AK8puppiTau3_.push_back( ijetAK8->userFloat("ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau3"));

  //     //save puppi-Softdrop subjet info Lvdp
  //     vecPuppiSDSJcsv.clear();
  //     vecPuppiSDSJpt.clear();
  //     vecPuppiSDSJeta.clear();
  //     vecPuppiSDSJmass.clear();
  //     vecPuppiSDSJphi.clear();
  //     vecPuppiSDSJe.clear();
  //     vecPuppiSDSJcharge.clear();
  //     vecPuppiSDSJflavour.clear();
  //     nPuppiSJs = 0;

  //     TLorentzVector puppi_softdrop, puppi_softdrop_subjet;
  //     auto const & sdSubjetsPuppi = ijetAK8->subjets("SoftDropPuppi");
  //     for ( auto const & puppiSDSJ : sdSubjetsPuppi ) {
  //       nPuppiSJs++;
  //       vecPuppiSDSJpt.push_back(puppiSDSJ->pt());
  //       vecPuppiSDSJeta.push_back(puppiSDSJ->eta());
  //       vecPuppiSDSJmass.push_back(puppiSDSJ->mass());
  //       vecPuppiSDSJphi.push_back(puppiSDSJ->phi());
  //       vecPuppiSDSJe.push_back(puppiSDSJ->energy());
  //       vecPuppiSDSJflavour.push_back(abs(puppiSDSJ->partonFlavour()));
  //       vecPuppiSDSJcharge.push_back(puppiSDSJ->charge());
  //       vecPuppiSDSJcsv.push_back(puppiSDSJ->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags") );

  //       puppi_softdrop_subjet.SetPtEtaPhiM(puppiSDSJ->correctedP4(0).pt(),puppiSDSJ->correctedP4(0).eta(),puppiSDSJ->correctedP4(0).phi(),puppiSDSJ->correctedP4(0).mass());
  //       puppi_softdrop+=puppi_softdrop_subjet;
  //     }
//// fir L2L3 corrections
  //     jecAK8pSD_->setJetEta( puppi_softdrop.Eta() );
  //     jecAK8pSD_->setJetPt ( puppi_softdrop.Pt() );
  //     jecAK8pSD_->setJetE  ( puppi_softdrop.E() );
  //     jecAK8pSD_->setJetA  ( (*ijetAK8).jetArea() );
  //     jecAK8pSD_->setRho   ( rho );
  //     jecAK8pSD_->setNPV   ( vtxHandle->size() );

  //     float corr_puppiSD = jecAK8pSD_->getCorrection();
  //     AK8puppiSDL2L3corr_.push_back(corr_puppiSD);
  //     AK8puppiSDMass_.push_back(puppi_softdrop.M());
  //     AK8puppiSDMassL2L3Corr_.push_back(corr_puppiSD*puppi_softdrop.M());

  //     nAK8puppiSDSJ_.push_back(nPuppiSJs);
  //     AK8puppiSDSJPt_.push_back(vecPuppiSDSJpt);
  //     AK8puppiSDSJEta_.push_back(vecPuppiSDSJeta);
  //     AK8puppiSDSJPhi_.push_back(vecPuppiSDSJphi);
  //     AK8puppiSDSJMass_.push_back(vecPuppiSDSJmass);
  //     AK8puppiSDSJE_.push_back(vecPuppiSDSJe);
  //     AK8puppiSDSJCharge_.push_back(vecPuppiSDSJcharge);
  //     AK8puppiSDSJFlavour_.push_back(vecPuppiSDSJflavour);
  //     AK8puppiSDSJCSV_.push_back(vecPuppiSDSJcsv);
  //   }
  // }
  delete jecUnc;
  //delete AK8jecUnc;
}//}if statement on event#
