#include "CalibCalorimetry/HcalTPGAlgos/interface/HcaluLUTTPGCoder.h"
#include "Geometry/HcalTowerAlgo/src/HcalHardcodeGeometryData.h"
#include "FWCore/Utilities/interface/Exception.h"
#include <iostream>
#include <fstream>
<<<<<<< HcaluLUTTPGCoder.cc
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "CalibFormats/HcalObjects/interface/HcalCoderDb.h"
#include "CalibFormats/HcalObjects/interface/HcalCalibrations.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"
#include "Geometry/CaloTopology/interface/HcalTopology.h"
#include <cmath>
=======
#include <cmath>

static const int INPUT_LUT_SIZE = 128;
>>>>>>> 1.10

HcaluLUTTPGCoder::HcaluLUTTPGCoder(const char* filename) {
<<<<<<< HcaluLUTTPGCoder.cc
  AllocateLUTs();
  getRecHitCalib(filename);
=======
  // generateILUTs();
  loadILUTs(filename);
>>>>>>> 1.10
}

HcaluLUTTPGCoder::HcaluLUTTPGCoder(const char* filename, const char* fname2) {
	throw cms::Exception("PROBLEM: This constructor should never be invoked!");
}
<<<<<<< HcaluLUTTPGCoder.cc

void HcaluLUTTPGCoder::compress(const IntegerCaloSamples& ics, const std::vector<bool>& featureBits, HcalTriggerPrimitiveDigi& tp) const {
	throw cms::Exception("PROBLEM: This method should never be invoked!");
}

HcaluLUTTPGCoder::~HcaluLUTTPGCoder() {
  for (int i = 0; i < nluts; i++) {
    if (inputLUT[i] != 0) delete inputLUT[i];
  }
  std::cout << "LUT memory has been freed" << std::endl;
}

void HcaluLUTTPGCoder::AllocateLUTs() {
  HcalTopology theTopo;
  HcalDetId did;
  for (int i = 0; i < nluts; i++) inputLUT[i] = 0;
  int maxid = 0, minid = 0x7FFFFFFF, rawid = 0;
  for (int ieta=-41; ieta <= 41; ieta++) {
    for (int iphi = 1; iphi <= 72; iphi++) {
      for (int depth = 1; depth <= 3; depth++) {
		did=HcalDetId(HcalBarrel,ieta,iphi,depth);
		if (theTopo.valid(did)) {
			rawid = GetLUTID(HcalBarrel, ieta, iphi, depth);
			inputLUT[rawid] = new LUT[INPUT_LUT_SIZE];
			if (rawid < minid) minid = rawid;
			if (rawid > maxid) maxid = rawid;
		}
//        if (theTopo.valid(did)) std::cout << "HB id = " << did.rawId() << "; (ieta,iphi,depth) = (" << ieta << "," << iphi << "," << depth << ")" << std::endl;

		did=HcalDetId(HcalEndcap,ieta,iphi,depth);
		if (theTopo.valid(did)) {
			rawid = GetLUTID(HcalEndcap, ieta, iphi, depth);
			inputLUT[rawid] = new LUT[INPUT_LUT_SIZE];
			if (rawid < minid) minid = rawid;
			if (rawid > maxid) maxid = rawid;
		}
//        if (theTopo.valid(did)) std::cout << "HE id = " << did.rawId() << "; (ieta,iphi,depth) = (" << ieta << "," << iphi << "," << depth << ")" << std::endl;
		did=HcalDetId(HcalForward,ieta,iphi,depth);
		if (theTopo.valid(did)) {
			rawid = GetLUTID(HcalForward, ieta, iphi, depth);
			inputLUT[rawid] = new LUT[INPUT_LUT_SIZE];
			if (rawid < minid) minid = rawid;
			if (rawid > maxid) maxid = rawid;
		}
//		  if (theTopo.valid(did)) std::cout << "HF id = " << did.rawId() << "; (ieta,iphi,depth) = (" << ieta << "," << iphi << "," << depth << ")" << std::endl;
      }
    }
  }
  std::cout << "LUT's have been allocated; LUT id spans " << minid << " to " << maxid << std::endl;

}

int HcaluLUTTPGCoder::GetLUTID(HcalSubdetector id, int ieta, int iphi, int depth) const {
  int detid = 0;
  if (id == HcalEndcap) detid = 1;
  else if (id == HcalForward) detid = 2;
  return iphi + 72 * ((ieta + 41) + 83 * (depth + 3 * detid)) - 7777;
}

void HcaluLUTTPGCoder::getRecHitCalib(const char* filename)  {
  //char *filename = "CalibCalorimetry/HcalTPGAlgos/data/RecHit-TPG-calib.dat";
=======

bool HcaluLUTTPGCoder::getadc2fCLUT() {
  char *filename = "CalibCalorimetry/HcalTPGAlgos/data/adc2fC.dat";
>>>>>>> 1.10
  std::ifstream userfile;
  userfile.open(filename);
  int tool;
  float Rec_calib_[87];
  std::cout << "before reading RecHit-TPG-calib.dat" << std::endl;
 
  if (userfile) {
<<<<<<< HcaluLUTTPGCoder.cc
    userfile >> tool;
=======
  userfile >> tool;

  if (tool != INPUT_LUT_SIZE) {
	  std::cout << "Wrong adc2fC LUT size: " << tool << " (expect 128)" << std::endl;
	return false;
  }
  for (int j=0; j<INPUT_LUT_SIZE; j++) {
	  userfile >> adc2fCLUT_[j]; // Read the ADC to fC LUT
	  // std::cout << adc2fCLUT_[j] << std::endl;
  }
  std::cout << "(1)Finished reading adc2fCLUT" << std::endl;

  userfile.close();
  std::cout << "(3)Finished reading adc2fCLUT" << std::endl;
  return true;
  }
  else {
    std::cout << "Problem!" << std::endl;
 return false;
  }
}

bool HcaluLUTTPGCoder::getped() {
        ped_ = 4.23729;
        ped_HF = 1.5625;
	return true;
}

bool HcaluLUTTPGCoder::getgain() {
	gain_ = 0.075;
	return true;
}

void HcaluLUTTPGCoder::generateILUTs() {
  if (!getadc2fCLUT()) throw cms::Exception("Missing/corrupted adc2fC LUT file");
  std::cout << "adc to fC LUT loaded..." << std::endl;
  
  if (!getped()) throw cms::Exception("Missing ped value");
  std::cout << "Pedestal = " << ped_ << " and HF:" << ped_HF << std::endl;
  if (!getgain()) throw cms::Exception("Missing gain value");
  std::cout << "Gain = " << gain_ << std::endl;
  
  //std::cout << adc2fCLUT_[0][127] << std::endl;
  char *filename = "test.dat";  
  std::ofstream myuserfile;
  myuserfile.open(filename, std::ofstream::out);
  std::cout << "File " << filename << " has been opened..." << std::endl;
  
  myuserfile << "29" << std::endl;
      
  myuserfile << "1	21	27	29	30	31	32	33	34	35	36	37	38	39	40	41	42	43	44	45	46	47	48	49	50	51	52	53	54" << std::endl;
  myuserfile << "20	26	28	29	30	31	32	33	34	35	36	37	38	39	40	41	42	43	44	45	46	47	48	49	50	51	52	53	54" << std::endl;

    
  //for (int i = 0; i < INPUT_LUT_SIZE; i++) {
    //std::cout << adc2fCLUT_[i] << std::endl;
 // }
  

  float cosheta[13], lsb = 1./16.;
  for (int i = 0; i < 13; i++) {
    cosheta[i] = cosh((theHFEtaBounds[i+1] + theHFEtaBounds[i])/2.);
  }
  for (int i = 0; i < INPUT_LUT_SIZE; i++) {
    
	  myuserfile << std::max(0,int((adc2fCLUT_[i] - ped_)/1.)) << " " << std::max(0,int((adc2fCLUT_[i] - ped_)/2.)) << " " << std::max(0,int((adc2fCLUT_[i] - ped_)/5.)) << " ";
>>>>>>> 1.10

    if (tool != 86) {
      std::cout << "Wrong RecHit calibration filesize: " << tool << " (expect 86)" << std::endl;
    }
    for (int j=1; j<87; j++) {
        userfile >> Rec_calib_[j]; // Read the Calib factors
	Rcalib[j] = Rec_calib_[j] ;
    }
   
    std::cout << "Finished reading RecHit-TPG-calib.dat" << std::endl;
    userfile.close();  
  }
  else  std::cout << "File " << filename << " with RecHit calibration factors not found" << std::endl;
}

void HcaluLUTTPGCoder::getConditions(const edm::EventSetup& es) const {
  //
  // Using Jeremy's template
  //
  edm::ESHandle<HcalDbService> conditions;
  es.get<HcalDbRecord>().get(conditions);
  const HcalQIEShape* shape = conditions->getHcalShape();
  HcalCalibrations calibrations;
  int id;
  float divide;
  HcalTopology theTopo;

  float cosheta_[41], lsb_ = 1./16.;
  for (int i = 0; i < 13; i++) cosheta_[i+29] = cosh((theHFEtaBounds[i+1] + theHFEtaBounds[i])/2.);
    
  for (int depth = 1; depth <= 3; depth++) {
//    std::cout << "Scanning depth = " << depth << std::endl;
    for (int iphi = 1; iphi <= 72; iphi++) {
//      std::cout <<   "Scanning iphi = " << iphi << std::endl;
      divide = 1.*nominal_gain;
      for (int ieta=-16; ieta <= 16; ieta++) {
		HcalDetId cell(HcalBarrel,ieta,iphi,depth);
		if (theTopo.valid(cell)) {  
			id = GetLUTID(HcalBarrel,ieta,iphi,depth);
			if (inputLUT[id] == 0) throw cms::Exception("PROBLEM: inputLUT has not been initialized for HB, ieta, iphi, depth, id = ") << ieta << "," << iphi << "," << depth << "," << id << std::endl;
			conditions->makeHcalCalibration (cell, &calibrations);
			const HcalQIECoder* channelCoder = conditions->getHcalCoder (cell);
			HcalCoderDb coder (*channelCoder, *shape);
			float ped_ = (calibrations.pedestal(0)+calibrations.pedestal(1)+calibrations.pedestal(2)+calibrations.pedestal(3))/4;
			float gain_= (calibrations.gain(0)+calibrations.gain(1)+calibrations.gain(2)+calibrations.gain(3))/4;          
			//if (iphi == 1) std::cout << "HB gain = " << gain_ << " for ieta = " << ieta << " depth = " << depth << std::endl;
			HBHEDataFrame frame(cell);
			frame.setSize(1);
			CaloSamples samples(cell, 1);
			for (int j = 0; j <= 0x7F; j++) {
				HcalQIESample adc(j);
				frame.setSample(0,adc);
				coder.adc2fC(frame,samples);
				float adc2fC_ = samples[0];
				if (ieta <0 )inputLUT[id][j] = (LUT) std::min(std::max(0,int((adc2fC_ - ped_)*gain_*Rcalib[abs(ieta)]/divide)), 0x3FF);
				else inputLUT[id][j] = (LUT) std::min(std::max(0,int((adc2fC_ - ped_)*gain_*Rcalib[abs(ieta)+43]/divide)), 0x3FF);
			}
//          for (int j = 0; j < 128; j += 127) std::cout << "LUT(HB," << ieta << "," << iphi << "," << depth << "[" << j << "] = " << inputLUT[id][j] << std::endl;
		}
      }
      for (int ieta=-29; ieta <= 29; ieta++) {
		HcalDetId cell(HcalEndcap,ieta,iphi,depth);
		if (theTopo.valid(cell)) {  
			if (abs(ieta) < 21) divide = 1.*nominal_gain;
			else if (abs(ieta) < 27) divide = 2.*nominal_gain;
			else divide = 5.*nominal_gain;
			id = GetLUTID(HcalEndcap,ieta,iphi,depth);
			if (inputLUT[id] == 0) throw cms::Exception("PROBLEM: inputLUT has not been initialized for HB, ieta, iphi, depth, id = ") << ieta << "," << iphi << "," << depth << "," << id << std::endl;
			conditions->makeHcalCalibration (cell, &calibrations);
			const HcalQIECoder* channelCoder = conditions->getHcalCoder (cell);
			HcalCoderDb coder (*channelCoder, *shape);
			float ped_ = (calibrations.pedestal(0)+calibrations.pedestal(1)+calibrations.pedestal(2)+calibrations.pedestal(3))/4;
			float gain_= (calibrations.gain(0)+calibrations.gain(1)+calibrations.gain(2)+calibrations.gain(3))/4;          
			//if (iphi == 1) std::cout << "HE gain = " << gain_ << " for ieta = " << ieta << " depth = " << depth << std::endl;
			HBHEDataFrame frame(cell);
			frame.setSize(1);
			CaloSamples samples(cell, 1);
			for (int j = 0; j <= 0x7F; j++) {
				HcalQIESample adc(j);
				frame.setSample(0,adc);
				coder.adc2fC(frame,samples);
				float adc2fC_ = samples[0];
				if ( ieta < 0 ) inputLUT[id][j] = (LUT) std::min(std::max(0,int((adc2fC_ - ped_)*gain_*Rcalib[abs(ieta)+1]/divide)), 0x3FF);
				else inputLUT[id][j] = (LUT) std::min(std::max(0,int((adc2fC_ - ped_)*gain_*Rcalib[abs(ieta)+43]/divide)), 0x3FF);
		    }
//            for (int j = 0; j < 128; j += 127) std::cout << "LUT(HE," << ieta << "," << iphi << "," << depth << "[" << j << "] = " << inputLUT[id][j] << std::endl;
		}
      }        
      for (int ieta=-41; ieta <= 41; ieta++) {
		HcalDetId cell(HcalForward,ieta,iphi,depth);
		if (theTopo.valid(cell)) {  
			id = GetLUTID(HcalForward,ieta,iphi,depth);
			if (inputLUT[id] == 0) throw cms::Exception("PROBLEM: inputLUT has not been initialized for HB, ieta, iphi, depth, id = ") << ieta << "," << iphi << "," << depth << "," << id << std::endl;
			conditions->makeHcalCalibration (cell, &calibrations);
			const HcalQIECoder* channelCoder = conditions->getHcalCoder (cell);
			HcalCoderDb coder (*channelCoder, *shape);
			float ped_ = (calibrations.pedestal(0)+calibrations.pedestal(1)+calibrations.pedestal(2)+calibrations.pedestal(3))/4;
			float gain_= (calibrations.gain(0)+calibrations.gain(1)+calibrations.gain(2)+calibrations.gain(3))/4;          
			//if (iphi == 1) std::cout << "HF gain = " << gain_ << " for ieta = " << ieta << " depth = " << depth << std::endl;


			HFDataFrame frame(cell);
			frame.setSize(1);
			CaloSamples samples(cell, 1);

			for (int j = 0; j <= 0x7F; j++) {
				HcalQIESample adc(j);
				frame.setSample(0,adc);
				coder.adc2fC(frame,samples);
				float adc2fC_ = samples[0];
				if (ieta < 0 ) inputLUT[id][j] = (LUT) std::min(std::max(0,int((adc2fC_ - ped_)*Rcalib[abs(ieta)+2]*gain_/lsb_/cosheta_[abs(ieta)])), 0x3FF);
				else inputLUT[id][j] = (LUT) std::min(std::max(0,int((adc2fC_ - ped_)*Rcalib[abs(ieta)+45]*gain_/lsb_/cosheta_[abs(ieta)])), 0x3FF);
			}
			//for (int j = 0; j < 128; j += 127) std::cout << "LUT(HF," << ieta << "," << iphi << "," << depth << "[" << j << "] = " << inputLUT[id][j] << std::endl;
		}
	  }
    }
  }
}

void HcaluLUTTPGCoder::adc2Linear(const HBHEDataFrame& df, IntegerCaloSamples& ics) const {
  int id = GetLUTID(df.id().subdet(), df.id().ieta(), df.id().iphi(), df.id().depth());
  if (inputLUT[id]==0) {
    throw cms::Exception("Missing Data") << "No LUT for " << df.id();
  } else {
    for (int i=0; i<df.size(); i++){
      if (df[i].adc() >= INPUT_LUT_SIZE || df[i].adc() < 0) throw cms::Exception("ADC overflow for HBHE tower: ") << i << " adc= " << df[i].adc();
      ics[i]=inputLUT[id][df[i].adc()];
    }
  }
}

void HcaluLUTTPGCoder::adc2Linear(const HFDataFrame& df, IntegerCaloSamples& ics)  const{
  int id = GetLUTID(df.id().subdet(), df.id().ieta(), df.id().iphi(), df.id().depth());
  if (inputLUT[id]==0) {
    throw cms::Exception("Missing Data") << "No LUT for " << df.id();
  } else {
    for (int i=0; i<df.size(); i++){
      if (df[i].adc() >= INPUT_LUT_SIZE || df[i].adc() < 0)
        throw cms::Exception("ADC overflow for HF tower: ") << i << " adc= " << df[i].adc();
      ics[i]=inputLUT[id][df[i].adc()];
    }
  }
}
