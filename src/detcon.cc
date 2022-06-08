#include "detcon.hh"

detcon::detcon() : G4VUserDetectorConstruction() {}

detcon::~detcon() {}

G4VPhysicalVolume *detcon::Construct() {
    G4NistManager *nist = G4NistManager::Instance();
    G4bool checkOverlaps = true;

    // World
    G4double worldSize = 15 * cm;
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic");
    G4Box *solidWorld = new G4Box("solidWorld", 0.5 * worldSize, 0.5 * worldSize, 0.5 * worldSize);
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld", 0, false, 0, checkOverlaps);

    // Aluminum Case
    G4double detIR = 4*cm;
    G4double wallThickness = 1*cm;
    G4double detOR = detIR + wallThickness;
    G4double detHalfHeight = 0.4*cm;
    G4Material *al = nist->FindOrBuildMaterial("G4_Al");
    G4Tubs *solidAl = new G4Tubs("solidAl", detIR, detOR, detHalfHeight, 0, TMath::TwoPi());
    logicAl = new G4LogicalVolume(solidAl, al, "logicAl");
    physAl = new G4PVPlacement(0, G4ThreeVector(), logicAl, "physAl", logicWorld, false, 0, checkOverlaps);

    // PTP
    G4double ptpHalfHeight = 50*um;
    G4ThreeVector ptp_z_offset = G4ThreeVector(0, 0, detHalfHeight - ptpHalfHeight);
    G4Material *ptp = nist->FindOrBuildMaterial("G4_TERPHENYL");
    G4Tubs *solidPTP = new G4Tubs("solidPTP", 0, detIR, ptpHalfHeight, 0, TMath::TwoPi());
    logicPTP = new G4LogicalVolume(solidPTP, ptp, "logicPTP");
    physPTP = new G4PVPlacement(0, ptp_z_offset, logicPTP, "physPTP", logicWorld, false, 0, checkOverlaps);

    // DCF
    G4double dcfHalfHeight = 0.1*cm;
    G4ThreeVector dcf_z_offset = G4ThreeVector(0, 0, detHalfHeight - ptpHalfHeight * 2 - dcfHalfHeight);
    G4Material *dcf = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
    G4Tubs *solidDCF = new G4Tubs("solidDCF", 0, detIR, dcfHalfHeight, 0, TMath::TwoPi());
    logicDCF = new G4LogicalVolume(solidDCF, dcf, "logicDCF");
    physDCF = new G4PVPlacement(0, dcf_z_offset, logicDCF, "physDCF", logicWorld, false, 0, checkOverlaps);

    // PTP
    G4double tpbHalfHeight = 50*um;
    G4ThreeVector tpb_z_offset = G4ThreeVector(0, 0, detHalfHeight - ptpHalfHeight * 2 - dcfHalfHeight * 2 - tpbHalfHeight);
    G4Material *tpb = nist->FindOrBuildMaterial("G4_ANTHRACENE");
    G4Tubs *solidTPB = new G4Tubs("solidTPB", 0, detIR, tpbHalfHeight, 0, TMath::TwoPi());
    logicTPB = new G4LogicalVolume(solidTPB, tpb, "logicTPB");
    physTPB = new G4PVPlacement(0, tpb_z_offset, logicTPB, "physTPB", logicWorld, false, 0, checkOverlaps);

    // PMT
    G4double pmtHalfHeight = 0.1*cm;
    G4ThreeVector pmt_z_offset = G4ThreeVector(0, 0, - detHalfHeight + pmtHalfHeight);
    G4Material *kali = nist->FindOrBuildMaterial("G4_K");
    G4Tubs *solidPMT = new G4Tubs("solidPMT", 0, detIR, pmtHalfHeight, 0, TMath::TwoPi());
    logicPMT = new G4LogicalVolume(solidPMT, kali, "logicPMT");
    physPMT = new G4PVPlacement(0, pmt_z_offset, logicPMT, "physPMT", logicWorld, false, 0, checkOverlaps);

    return physWorld;
}

