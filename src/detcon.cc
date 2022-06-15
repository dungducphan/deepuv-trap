#include "detcon.hh"

detcon::detcon() : G4VUserDetectorConstruction(),
                   worldSize(15*cm),
                   detIR(4*cm),
                   wallThickness(1*cm),
                   detHalfHeight(0.4*cm),
                   ptpHalfHeight(50*um),
                   dcfHalfHeight(0.1*cm),
                   tpbHalfHeight(50*um),
                   pmtHalfHeight(0.1*cm) {
    DefineMessenger();
    DefineMaterials();
}

detcon::~detcon() {}

void detcon::DefineMessenger() {
    mMessenger = new G4GenericMessenger(this, "/detCon/", "Detector Geometry Messenger");
    mMessenger->DeclareProperty("detIR",         detIR,         "Detector case inner radius");
    mMessenger->DeclareProperty("wallThickness", wallThickness, "Detector case thickness");
    mMessenger->DeclareProperty("detHalfHeight", detHalfHeight, "Detector half height");
    mMessenger->DeclareProperty("ptpHalfHeight", ptpHalfHeight, "PTP layer half height");
    mMessenger->DeclareProperty("dcfHalfHeight", dcfHalfHeight, "DCF layer half height");
    mMessenger->DeclareProperty("tpbHalfHeight", tpbHalfHeight, "TPB layer half height");
    mMessenger->DeclareProperty("pmtHalfHeight", pmtHalfHeight, "PMT layer half height");
}

void detcon::DefineMaterials() {
    nist = G4NistManager::Instance();
    vacuum   = nist->FindOrBuildMaterial("G4_Galactic");
    al       = nist->FindOrBuildMaterial("G4_Al");
    ptp      = nist->FindOrBuildMaterial("G4_TERPHENYL");
    dcf      = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
    tpb      = nist->FindOrBuildMaterial("G4_ANTHRACENE");
    kali     = nist->FindOrBuildMaterial("G4_K");

    G4double photonEnergy[4] = {1E-2*eV, 0.1 * eV, 1 * eV, 10 * eV};
    G4double refractiveIndex[4];
    for (int idx = 0; idx < 4; idx++) refractiveIndex[idx] = 1.0;

    // MPT of non-refractive
    G4MaterialPropertiesTable* MPT_non_refractive = new G4MaterialPropertiesTable();
    MPT_non_refractive->AddProperty("RINDEX", photonEnergy, refractiveIndex, 4)->GetSpline();
    vacuum->SetMaterialPropertiesTable(MPT_non_refractive);
    tpb->SetMaterialPropertiesTable(MPT_non_refractive);
    ptp->SetMaterialPropertiesTable(MPT_non_refractive);
    kali->SetMaterialPropertiesTable(MPT_non_refractive);

    // MPT of refractive
    for (int idx = 0; idx < 4; idx++) refractiveIndex[idx] = 1.5;
    G4MaterialPropertiesTable* MPT_refractive = new G4MaterialPropertiesTable();
    MPT_refractive->AddProperty("RINDEX", photonEnergy, refractiveIndex, 4)->GetSpline();
    dcf->SetMaterialPropertiesTable(MPT_refractive);
}

G4VPhysicalVolume *detcon::Construct() {
    G4bool checkOverlaps = true;

    // World
    solidWorld = new G4Box("solidWorld", 0.5 * worldSize, 0.5 * worldSize, 0.5 * worldSize);
    logicWorld = new G4LogicalVolume(solidWorld, vacuum, "logicWorld");
    physWorld  = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld", 0, false, 0, checkOverlaps);

    // Aluminum Case
    detOR  = detIR + wallThickness;
    solidAl = new G4Tubs("solidAl", detIR, detOR, detHalfHeight, 0, TMath::TwoPi());
    logicAl = new G4LogicalVolume(solidAl, al, "logicAl");
    physAl  = new G4PVPlacement(0, G4ThreeVector(), logicAl, "physAl", logicWorld, false, 0, checkOverlaps);

    // PTP
    G4ThreeVector* ptp_z_offset = new G4ThreeVector(0, 0, detHalfHeight - ptpHalfHeight);
    solidPTP  = new G4Tubs("solidPTP", 0, detIR, ptpHalfHeight, 0, TMath::TwoPi());
    logicPTP  = new G4LogicalVolume(solidPTP, ptp, "logicPTP");
    physPTP   = new G4PVPlacement(0, *ptp_z_offset, logicPTP, "physPTP", logicWorld, false, 0, checkOverlaps);

    // DCF
    G4ThreeVector* dcf_z_offset = new G4ThreeVector(0, 0, detHalfHeight - ptpHalfHeight * 2 - dcfHalfHeight);
    solidDCF = new G4Tubs("solidDCF", 0, detIR, dcfHalfHeight, 0, TMath::TwoPi());
    logicDCF = new G4LogicalVolume(solidDCF, dcf, "logicDCF");
    physDCF  = new G4PVPlacement(0, *dcf_z_offset, logicDCF, "physDCF", logicWorld, false, 0, checkOverlaps);

    // PTP
    G4ThreeVector* tpb_z_offset = new G4ThreeVector(0, 0, detHalfHeight - ptpHalfHeight * 2 - dcfHalfHeight * 2 - tpbHalfHeight);
    solidTPB = new G4Tubs("solidTPB", 0, detIR, tpbHalfHeight, 0, TMath::TwoPi());
    logicTPB = new G4LogicalVolume(solidTPB, tpb, "logicTPB");
    physTPB  = new G4PVPlacement(0, *tpb_z_offset, logicTPB, "physTPB", logicWorld, false, 0, checkOverlaps);

    // PMT
    G4ThreeVector* pmt_z_offset = new G4ThreeVector(0, 0, - detHalfHeight + pmtHalfHeight);
    solidPMT = new G4Tubs("solidPMT", 0, detIR, pmtHalfHeight, 0, TMath::TwoPi());
    logicPMT = new G4LogicalVolume(solidPMT, kali, "logicPMT");
    physPMT  = new G4PVPlacement(0, *pmt_z_offset, logicPMT, "physPMT", logicWorld, false, 0, checkOverlaps);

    return physWorld;
}

