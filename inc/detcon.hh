#pragma once

#include <utility>
#include <tuple>
#include <fstream>

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4SDManager.hh"
#include "G4GenericMessenger.hh"

#include "TMath.h"

class G4VPhysicalVolume;

class G4LogicalVolume;

class detcon : public G4VUserDetectorConstruction {
public:
    detcon();
    virtual ~detcon();
    virtual G4VPhysicalVolume *Construct();
    virtual void DefineMaterials();
    virtual void DefineMessenger();

private:
    G4GenericMessenger *mMessenger = nullptr;

private:
    G4NistManager *nist = nullptr;
    G4Material *worldMat = nullptr;
    G4Material *al = nullptr;
    G4Material *ptp = nullptr;
    G4Material *dcf = nullptr;
    G4Material *tpb = nullptr;
    G4Material *kali = nullptr;

private:
    G4double worldSize = 15 * cm;
    G4double detIR = 4*cm;
    G4double wallThickness = 1*cm;
    G4double detOR = detIR + wallThickness;
    G4double detHalfHeight = 0.4*cm;
    G4double ptpHalfHeight = 50*um;
    G4double dcfHalfHeight = 0.1*cm;
    G4double tpbHalfHeight = 50*um;
    G4double pmtHalfHeight = 0.1*cm;

private:
    G4Box *solidWorld = nullptr;
    G4LogicalVolume* logicWorld = nullptr;
    G4VPhysicalVolume* physWorld = nullptr;

    G4Tubs *solidAl = nullptr;
    G4LogicalVolume* logicAl = nullptr;
    G4VPhysicalVolume* physAl = nullptr;

    G4Tubs *solidPTP = nullptr;
    G4LogicalVolume* logicPTP = nullptr;
    G4VPhysicalVolume* physPTP = nullptr;

    G4Tubs *solidDCF = nullptr;
    G4LogicalVolume* logicDCF = nullptr;
    G4VPhysicalVolume* physDCF = nullptr;

    G4Tubs *solidTPB = nullptr;
    G4LogicalVolume* logicTPB = nullptr;
    G4VPhysicalVolume* physTPB = nullptr;

    G4Tubs *solidPMT = nullptr;
    G4LogicalVolume* logicPMT = nullptr;
    G4VPhysicalVolume* physPMT = nullptr;
};
