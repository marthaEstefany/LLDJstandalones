#!/bin/bash

outdir="${CMSSW_BASE}/src/LLDJstandalones/lists"
 
xcDY50="71310"              # +-70 # LO https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#DY_Z
xcDY5to50_HT70to100="301.2"  # +-0.8  # LO https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#DY_Z             
xcDY5to50_HT100to200="224.2" # +- 5.7
xcDY5to50_HT200to400="37.2"  # +- 1.1
xcDY5to50_HT400to600="3.581" # +-0.118 
xcDY5to50_HT600toInf="1.124" # +-0.038 
xcGJets_HT40To100="20790"    # +-9                 
xcGJets_HT100To200="9238"    # +-4              
xcGJets_HT200To400="2305"    # +-0.7               
xcGJets_HT400To600="274.4"   # +-0.2               
xcGJets_HT600ToInf="93.46"   # +-0.06            
xcST_s="3.36"       #+0.13 -0.12 NLO                          
xcSTbar_t="81.2"    # 26.3+1.32-1.18  = (LEPTON DECAY = 26.3) / ( 3 x 10.80% [PDG])
xcST_t="136.8"      # 44.33+1.76-1.49 = (LEPTON DECAY = 44.3) / ( 3 x 10.80% [PDG]) 
xcSTbar_tW="35.85"  # +-0.9, +-1.7 NNLO
xcST_tW="35.85"     # +-0.9, +-1.7 NNLO                     
xcTTJets="831.76"   #NNLO
xcWW="10.32"      # not sure VV.. https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeVInclusive
xcZZ="63.0"                   
xcWZ="118.7"                  
xcZH_HToBB_ZToLL="1"                 
xcggZH_HToBB_ZToLL="1"               
xcggZH_HToSSTobbbb_MS40_ctauS100="1" 
xcggZH_HToSSTodddd_MS40_ctauS100="1" 
xcWJetsToLNu="61526.7"   # https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#W_jets                  
xcSingleElectron="1"                 
xcSingleMuon="1" 

countalist () {
 #if [ $1 = true ]
 #then
  printf "Making %s\n" $1
  root -l -b -q 'countevents.cxx("'$1'")'
  printf "crosssection: %s\n" $2 >> ${listdir}/$1.info
 #fi
}
 
countalist  "DY50"                            ${xcDY50}                            
countalist  "DY5to50_HT100to200"              ${xcDY5to50_HT100to200}              
countalist  "DY5to50_HT200to400"              ${xcDY5to50_HT200to400}              
countalist  "DY5to50_HT400to600"              ${xcDY5to50_HT400to600}              
countalist  "DY5to50_HT600toInf"              ${xcDY5to50_HT600toInf}              
countalist  "DY5to50_HT70to100"               ${xcDY5to50_HT70to100}               
countalist  "GJets_HT40To100"                 ${xcGJets_HT40To100}                 
countalist  "GJets_HT100To200"                ${xcGJets_HT100To200}                
countalist  "GJets_HT200To400"                ${xcGJets_HT200To400}                
countalist  "GJets_HT400To600"                ${xcGJets_HT400To600}                
countalist  "GJets_HT600ToInf"                ${xcGJets_HT600ToInf}                
countalist  "ST_s"                            ${xcST_s}                            
countalist  "STbar_t"                         ${xcSTbar_t}                         
countalist  "ST_t"                            ${xcST_t}                            
countalist  "STbar_tW"                        ${xcSTbar_tW}                        
countalist  "ST_tW"                           ${xcST_tW}                           
countalist  "TTJets"                          ${xcTTJets}                          
countalist  "WW"                              ${xcWW}                              
countalist  "WZ"                              ${xcWZ}                              
countalist  "ZZ"                              ${xcZZ}                              
countalist  "ZH_HToBB_ZToLL"                  ${xcZH_HToBB_ZToLL}                  
countalist  "ggZH_HToBB_ZToLL"                ${xcggZH_HToBB_ZToLL}                
countalist  "ggZH_HToSSTobbbb_MS40_ctauS100"  ${xcggZH_HToSSTobbbb_MS40_ctauS100}  
countalist  "ggZH_HToSSTodddd_MS40_ctauS100"  ${xcggZH_HToSSTodddd_MS40_ctauS100}  
countalist  "WJetsToLNu"                      ${xcWJetsToLNu}                      
countalist  "SingleElectron"                  ${xcSingleElectron}                  
countalist  "SingleMuon"                      ${xcSingleMuon}                      

